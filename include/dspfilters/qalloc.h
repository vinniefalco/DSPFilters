//------------------------------------------------------------------------------
/*
    "A Collection of Useful C++ Classes for Digital Signal Processing"
    By Vinnie Falco

    Official project location:
    https://github.com/vinniefalco/DSPFilters

    This file is part of DSPFilters: https://github.com/vinniefalco/DSPFilters
    Copyright 2009, Vinnie Falco <vinnie.falco@gmail.com>

    Distributed under the terms of the ISC License:

    Permission to use, copy, modify, and/or distribute this software for any
    purpose  with  or without fee is hereby granted, provided that the above
    copyright notice and this permission notice appear in all copies.

    THE  SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
    WITH  REGARD  TO  THIS  SOFTWARE  INCLUDING  ALL  IMPLIED  WARRANTIES  OF
    MERCHANTABILITY  AND  FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
    ANY  SPECIAL ,  DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
    WHATSOEVER  RESULTING  FROM  LOSS  OF USE, DATA OR PROFITS, WHETHER IN AN
    ACTION  OF  CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/
//==============================================================================

#ifndef DSPFILTERS_QALLOC_H_INCLUDED
#define DSPFILTERS_QALLOC_H_INCLUDED

#include <cstdint>
#include <cstdlib>
#include <limits>
#include <memory>
#include <new>

namespace dspfilters {
namespace detail {

template <class = void>
class qalloc_impl
{
private:
    class block
    {
    private:
        std::size_t count_ = 0;
        std::size_t bytes_;
        std::size_t remain_;
        std::uint8_t* free_;

    public:
        block* next;

        block (block const&) = delete;
        block& operator= (block const&) = delete;

        explicit
        block (std::size_t bytes);

        void*
        allocate (std::size_t n);
        
        bool
        deallocate();

        static
        block*
        get (void* p);
    };

    block* used_ = nullptr;
    block* free_ = nullptr;

public:
    enum
    {
        block_size = 256 * 1024
    };

    qalloc_impl() = default;
    qalloc_impl (qalloc_impl const&) = delete;
    qalloc_impl& operator= (qalloc_impl const&) = delete;

    ~qalloc_impl();

    void*
    allocate (std::size_t n);

    void
    deallocate (void* p);
};

} // detail

template <class T>
class qalloc_type
{
private:
    template <class U>
    friend class qalloc_type;

    std::shared_ptr<
        detail::qalloc_impl<>> impl_;

public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = T const*;
    using reference = typename
        std::add_lvalue_reference<T>::type;
    using const_reference = typename
        std::add_lvalue_reference<T const>::type;

    template <class U>
    struct rebind
    {
        using other = qalloc_type<U>;
    };

    qalloc_type (qalloc_type const&) = default;
    qalloc_type& operator= (qalloc_type const&) = default;
#ifndef _MSC_VER
    qalloc_type (qalloc_type&& other) = default;
    qalloc_type& operator= (qalloc_type&&) = default;
#endif

    qalloc_type();

    template <class U>
    qalloc_type (qalloc_type<U> const& u);

    T*
    allocate (std::size_t n);

    template <class U>
    U*
    alloc (std::size_t n);

    void
    deallocate (T* p, std::size_t n);

    template <class U>
    void
    dealloc (U* p, std::size_t n);

    void
    destroy (T* t);

    template <class U>
    bool
    operator== (qalloc_type<U> const& u);

    template <class U>
    bool
    operator!= (qalloc_type<U> const& u);
};

/** Allocator optimized for delete in temporal order.

    This allocator is optimized for the case where objects
    are deleted in approximately the same order that they
    were created.
*/
using qalloc = qalloc_type<int>;

//------------------------------------------------------------------------------

namespace detail {

template <class T>
qalloc_impl<T>::block::block (std::size_t bytes)
    : bytes_ (bytes - sizeof(*this))
    , remain_ (bytes_)
    , free_ (reinterpret_cast<
        std::uint8_t*>(this + 1))
{
}

template <class T>
void*
qalloc_impl<T>::block::allocate (std::size_t n)
{
    n = sizeof(block*) + n;
    if (remain_ < n)
        return nullptr;
    auto p = reinterpret_cast<
        block**>(free_);
    *p = this;
    ++count_;
    free_ += n;
    remain_ -= n;
    return p + 1;
}

template <class T>
bool
qalloc_impl<T>::block::deallocate()
{
    --count_;
    if (count_ > 0)
        return false;
    remain_ = bytes_;
    free_ = reinterpret_cast<
        std::uint8_t*>(this + 1);
    return true;
}

template <class T>
inline
auto
qalloc_impl<T>::block::get (void* p) ->
    block*
{
    return reinterpret_cast<
        block**>(p)[-1];
}

template <class T>
qalloc_impl<T>::~qalloc_impl()
{
    if (used_)
        std::free(used_);
    while (free_)
    {
        auto const next = free_->next;
        free_->~block();
        std::free(free_);
        free_ = next;
    }
}

template <class T>
void*
qalloc_impl<T>::allocate (std::size_t n)
{
    if (used_)
    {
        auto const p = used_->allocate(n);
        if (p)
            return p;
        used_ = nullptr;
    }
    if (free_)
    {
        auto const p = free_->allocate(n);
        if (p)
        {
            used_ = free_;
            free_ = free_->next;
            return p;
        }
    }
    auto const bytes = std::max<std::size_t>(
        block_size, sizeof(block) +
            sizeof(block*) + n);
    block* const b =
        new(std::malloc(bytes)) block(bytes);
    if (! b)
        throw std::bad_alloc();
    used_ = b;
    // VFALCO This has to succeed
    return used_->allocate(n);
}

template <class T>
void
qalloc_impl<T>::deallocate (void* p)
{
    auto const block = block::get(p);
    if (block->deallocate())
    {
        if (used_ == block)
            used_ = nullptr;
        block->next = free_;
        free_ = block;
    }
}

} // detail

//------------------------------------------------------------------------------

template <class T>
qalloc_type<T>::qalloc_type()
    : impl_ (std::make_shared<
        detail::qalloc_impl<>>())
{
}

template <class T>
template <class U>
qalloc_type<T>::qalloc_type(
        qalloc_type<U> const& u)
    : impl_ (u.impl_)
{
}

template <class T>
T*
qalloc_type<T>::allocate (std::size_t n)
{
    if (n > std::numeric_limits<
            std::size_t>::max() / sizeof(T))
        throw std::bad_alloc();
    auto const bytes = n * sizeof(T);
    return static_cast<T*>(
        impl_->allocate(bytes));
}

template <class T>
template <class U>
U*
qalloc_type<T>::alloc (std::size_t n)
{
    static_assert(std::alignment_of<U>::value <=
        sizeof(void*), "");
    if (n > std::numeric_limits<
            std::size_t>::max() / sizeof(U))
        throw std::bad_alloc();
    auto const bytes = n * sizeof(U);
    return static_cast<U*>(
        impl_->allocate(bytes));
}

template <class T>
inline
void
qalloc_type<T>::deallocate(
    T* p, std::size_t n)
{
    impl_->deallocate(p);
}

template <class T>
template <class U>
inline
void
qalloc_type<T>::dealloc(
    U* p, std::size_t n)
{
    impl_->deallocate(p);
}

template <class T>
inline
void
qalloc_type<T>::destroy (T* t)
{
    t->~T();
}

template <class T>
template <class U>
inline
bool
qalloc_type<T>::operator==(
    qalloc_type<U> const& u)
{
    return impl_.get() == u.impl_.get();
}

template <class T>
template <class U>
inline
bool
qalloc_type<T>::operator!=(
    qalloc_type<U> const& u)
{
    return ! (*this == u);
}

} // dspfilters

#endif
