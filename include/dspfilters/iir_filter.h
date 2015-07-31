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

#ifndef DSPFILTERS_IIR_FILTER_H_INCLUDED
#define DSPFILTERS_IIR_FILTER_H_INCLUDED

#include <vector>

namespace dsp {

template <class Float>
struct biquad
{
    double a0_, a1_, a2_, b0_, b1_, b2_;

    Float a0() const { return a0_; }
    Float a1() const { return a1_ * a0_; }
    Float a2() const { return a2_ * a0_; }
    Float b0() const { return b0_ * a0_; }
    Float b1() const { return b1_ * a0_; }
    Float b2() const { return b2_ * a0_; }
};

/** State for Direct Form I */
template <class Float>
struct df1_state
{
    Float x1, x2, y1, y2;
};

using cascade = std::vector<biquad>;

template <class = void>
void
reset (cascade& c)
{
}

} // dspfilters

#endif
