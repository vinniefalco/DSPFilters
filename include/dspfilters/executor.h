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

#ifndef DSPFILTERS_EXECUTOR_H_INCLUDED
#define DSPFILTERS_EXECUTOR_H_INCLUDED

#include <dspfilters/qalloc.h>
#include <type_traits>
#include <utility>

namespace dspfilters {

namespace detail {

template <class = void>
class executor_impl
{
private:
    struct item
    {
        item* next = nullptr;
        virtual ~item() = default;
        virtual void operator()() = 0;
    };

    template <class F>
    class item_impl : public item
    {
        F f_;
    public:
        explicit item_impl (F&& f);
        explicit item_impl (F const& f);
        void operator()();
    };

    qalloc alloc_;
    item* head_ = nullptr;
    item* tail_ = nullptr;

public:
    executor_impl() = default;
    executor_impl (executor_impl const&) = delete;
    executor_impl& operator= (executor_impl const&) = delete;

    ~executor_impl();

    /** Run one pending function

        @return `true` if a function was executed
    */
    bool
    run_one();

    /** Run all pending functions

        @return `true` if any functions were executed
    */
    bool
    run();

    /** Post a function.

        The function will be executed in the next
        call to `run_one` or `run`. Functions are
        executed in the order they are posted.
    */
    template <class F>
    void
    post (F&& f);
};

//------------------------------------------------------------------------------

template <class _>
template <class F>
executor_impl<_>::item_impl<F>::item_impl(F&& f)
    : f_ (std::move(f))
{
}

template <class _>
template <class F>
executor_impl<_>::item_impl<F>::item_impl(F const& f)
    : f_ (f)
{
}

template <class _>
template <class F>
void
executor_impl<_>::item_impl<F>::operator()()
{
    f_();
};

template <class _>
executor_impl<_>::~executor_impl()
{
    while(head_)
    {
        auto const item = head_;
        head_ = head_->next;
        item->~item();
        alloc_.dealloc(item, 1);
    }
}

template <class _>
bool
executor_impl<_>::run_one()
{
    auto const item = head_;
    if (! item)
        return false;
    head_ = head_->next;
    if (! head_)
        tail_ = nullptr;
    (*item)();
    item->~item();
    alloc_.dealloc(item, 1);
    return true;
}

template <class _>
bool
executor_impl<_>::run()
{
    if (! run_one())
        return false;
    for(;;)
        if (! run_one())
            break;
    return true;
}

template <class _>
template <class F>
void
executor_impl<_>::post (F&& f)
{
    using T = item_impl<typename
        std::decay<F>::type>;
    auto const item =
        new(alloc_.alloc<T>(1)) T(
            std::forward<F>(f));
    if (tail_)
    {
        tail_->next = item;
        tail_ = item;
    }
    else
    {
        head_ = item;
        tail_ = item;
    }
}

} // detail

using executor = detail::executor_impl<>;

} // dspfilters

#endif
