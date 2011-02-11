/*
"A Collection of Useful C++ Classes for Digital Signal Processing"
By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

Copyright (c) 2009-2011 by Vincent Falco All Rights Reserved Worldwide

License: MIT License (http://www.opensource.org/licenses/mit-license.php)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/

#ifndef DSPFILTERS_UTILITIES_H
#define DSPFILTERS_UTILITIES_H

#include "DspFilters/Common.h"

namespace Dsp {

/*
  Utilities

  These routines are handy for manipulating buffers of samples.
*/

//------------------------------------------------------------------------------

// Add src samples to dest, without clip or overflow checking.
template <class Td,
          class Ts>
void add (int samples,
          Td* dest,
          Ts const* src,
          int destSkip = 0,
          int srcSkip = 0)
{
  if (srcSkip !=0 || destSkip != 0)
  {
    ++srcSkip;
    ++destSkip;
    while (--samples >= 0)
    {
      *dest = static_cast<Td>(*src);
      dest += destSkip;
      src += srcSkip;
    }
  }
  else
  {
    while (--samples >= 0)
      *dest++ += static_cast<Td>(*src++);
  }
}

// Multichannel add
template <typename Td,
          typename Ts>
void add (int channels,
          int samples,
          Td* const* dest,
          Ts const* const* src)
{
  for (int i = channels; --i >= 0;)
    add (samples, dest[i], src[i]);
}

//--------------------------------------------------------------------------

// Copy samples from src to dest, which may not overlap. Performs an implicit
// type conversion if Ts and Td are different (for example, float to double).
template <typename Td,
          typename Ts>
void copy (int samples,
           Td* dest,
           Ts const* src,
           int destSkip = 0,
           int srcSkip = 0)
{
  if (srcSkip != 0)
  {
    if (destSkip != 0)
    {
      ++srcSkip;
      ++destSkip;
      while (--samples >= 0)
      {
        *dest++ = *src++;
        dest += destSkip;
        src += srcSkip;
      }
    }
    else
    {
      ++srcSkip;
      while (--samples >= 0)
      {
        *dest++ = *src++;
        src += srcSkip;
      }
    }
  }
  else if (destSkip != 0)
  {
    ++destSkip;
    while (--samples >= 0)
    {
      *dest = *src++;
      dest += destSkip;
    }
  }
  else
  {
    while (--samples >= 0)
      *dest++ = *src++;
  }
}

// Wrapper that uses memcpy if there is no skip and the types are the same
template <typename Ty>
void copy (int samples,
           Ty* dest,
           Ty const* src,
           int destSkip = 0,
           int srcSkip = 0)
{
  if (destSkip != 0 || srcSkip != 0)
    copy<Ty,Ty> (samples, dest, src, destSkip, srcSkip);
  else
    ::memcpy (dest, src, samples * sizeof(src[0]));
}

// Copy a set of channels from src to dest, with implicit type conversion.
template <typename Td,
          typename Ts>
void copy (int channels,
           int samples,
           Td* const* dest,
           Ts const* const* src,
           int destSkip = 0,
           int srcSkip = 0)
{
  for (int i = channels; --i >= 0;)
    copy (samples, dest[i], src[i], destSkip, srcSkip);
}

//--------------------------------------------------------------------------

// Deinterleave channels. Performs implicit type conversion.
template<typename Td, typename Ts>
void deinterleave (int channels,
                   int samples,
                   Td* const* dest,
                   Ts const* src)
{
  assert (channels > 1);

  switch (channels)
  {
  case 2:
    {
      Td* l = dest[0];
      Td* r = dest[1];
	    int n = (samples + 7) / 8;
	    switch (samples % 8)
      {
	    case 0:
              do
              {	
                *l++ = *src++; *r++ = *src++;
	    case 7:		*l++ = *src++; *r++ = *src++;
	    case 6:		*l++ = *src++; *r++ = *src++;
	    case 5:		*l++ = *src++; *r++ = *src++;
	    case 4:		*l++ = *src++; *r++ = *src++;
	    case 3:		*l++ = *src++; *r++ = *src++;
	    case 2:		*l++ = *src++; *r++ = *src++;
	    case 1:		*l++ = *src++; *r++ = *src++;
		          }
              while (--n > 0);
	    }
    }
    break;

  default:
    {
      for (int i = channels; --i >= 0;)
        copy (samples, dest[i], src + i, 0, channels - 1);
    }
    break;
  };
}

// Convenience for a stereo pair of channels
template <typename Td,
          typename Ts>
void deinterleave (int samples,
                   Td* left,
                   Td* right,
                   Ts const* src)
{
  Td* dest[2];
  dest[0] = left;
  dest[1] = right;
  deinterleave (2, samples, dest, src);
}

//--------------------------------------------------------------------------

// Fade src into dest
template <typename Td,
          typename Ts,
          typename Ty>
void fade (int samples,
           Td* dest,
           Ts const* src,
           Ty start = 0,
           Ty end = 1)
{
  Ty t = start;
  Ty dt = (end - start) / samples;

  while (--samples >= 0)
  {
    *dest++ = static_cast<Td>(*dest + t * (*src++ - *dest));
    t += dt;
  }
}

// Fade src channels into dest channels
template <typename Td,
          typename Ts,
          typename Ty>
void fade (int channels,
           int samples,
           Td* const* dest,
           Ts const* const* src,
           Ty start = 0,
           Ty end = 1)
{
  for (int i = channels; --i >= 0;)
    fade (samples, dest[i], src[i], start, end);
}

//--------------------------------------------------------------------------

// Interleave separate channels from source pointers to destination
// (Destination requires channels*frames samples of storage). Performs
// implicit type conversion.
template <typename Td,
          typename Ts>
void interleave (int channels,
                 size_t samples,
                 Td* dest,
                 Ts const* const* src)
{
  assert (channels>1);

  switch (channels)
  {
  case 2:
    {
      const Ts* l = src[0];
      const Ts* r = src[1];

      int n = (samples + 7) / 8;
	    switch (samples % 8)
      {
	    case 0:
              do
              {	
                *dest++ = *l++; *dest++ = *r++;
	    case 7:		*dest++ = *l++; *dest++ = *r++;
	    case 6:		*dest++ = *l++; *dest++ = *r++;
	    case 5:		*dest++ = *l++; *dest++ = *r++;
	    case 4:		*dest++ = *l++; *dest++ = *r++;
	    case 3:		*dest++ = *l++; *dest++ = *r++;
	    case 2:		*dest++ = *l++; *dest++ = *r++;
	    case 1:		*dest++ = *l++; *dest++ = *r++;
		          }
              while (--n > 0);
	    }
    }
    break;

  default:
    {
      for (int i = channels; --i >= 0;)
        copy (1, samples, dest + i, src[i], channels - 1, 0);
    }
    break;
  };
}

//--------------------------------------------------------------------------

// Convenience for a stereo channel pair
template <typename Td,
          typename Ts>
void interleave (int samples,
                 Td* dest,
                 Ts const* left,
                 Ts const* right)
{
  const Ts* src[2];
  src[0] = left;
  src[1] = right;
  interleave (2, samples, dest, src);
}

//--------------------------------------------------------------------------

// Multiply samples by a constant, without clip or overflow checking.
template <typename Td,
          typename Ty>
void multiply (int samples,
               Td* dest,
               Ty factor,
               int destSkip = 0)
{
  if (destSkip != 0)
  {
    ++destSkip;
    while (--samples >= 0)
    {
      *dest = static_cast<Td>(*dest * factor);
      dest += destSkip;
    }
  }
  else
  {
    while (--samples >= 0)
      *dest++ = static_cast<Td>(*dest * factor);
  }
}

// Multiply a set of channels by a constant.
template <typename Td,
          typename Ty>
void multiply (int channels,
               int samples,
               Td* const* dest,
               Ty factor,
               int destSkip = 0)
{
  for (int i = channels; --i >= 0;)
    multiply (samples, dest[i], factor, destSkip);
}

//--------------------------------------------------------------------------

// Copy samples from src to dest in reversed order. Performs implicit
// type conversion. src and dest may not overlap.
template <typename Td,
          typename Ts>
void reverse (int samples,
              Td* dest,
              Ts const* src,
              int destSkip = 0,
              int srcSkip = 0 )
{
  src += (srcSkip + 1) * samples;

  if (srcSkip != 0 || destSkip == 0)
  {
    ++srcSkip;
    ++destSkip;
    while (--samples >= 0)
    {
      src -= srcSkip;
      *dest = *src;
      dest += destSkip;
    }
  }
  else
  {
    while (--samples >= 0)
      *dest++ = *--src;
  }
}

template<typename Td, typename Ts>
void reverse (int channels, size_t frames, Td* const* dest, const Ts* const* src)
{
  for (int i = channels; --i >= 0;)
    reverse (frames, dest[i], src[i]);
}

//--------------------------------------------------------------------------

#if 0
/*
 * this stuff all depends on is_pod which is not always available
 *
 */
namespace detail {

template <typename Ty,
          bool isPod>
struct zero
{
  static void process (int samples,
                       Ty* dest,
                       int destSkip)
  {
    if (destSkip != 0)
    {
      ++destSkip;
      while (--samples >= 0)
      {
        *dest = Ty();
        dest += destSkip;
      }
    }
    else
    {
      std::fill (dest, dest + samples, Ty());
    }
  }
};

template<typename Ty>
struct zero<Ty, true>
{
  static void process (int samples,
                       Ty* dest,
                       int destSkip)
  {
    if (destSkip != 0)
      zero<Ty,false>::process (samples, dest, destSkip);
    else
      ::memset (dest, 0, samples * sizeof(dest[0]));
  }
};

}

// Fill a channel with zeros. This works even if Ty is not a basic type.
template <typename Ty>
void zero (int samples,
           Ty* dest,
           int destSkip = 0)
{
  detail::zero<Ty, tr1::is_pod<Ty>::value>::process (samples, dest, destSkip );
}

#else
// Fill a channel with zeros. This works even if Ty is not a basic type.
template <typename Ty>
void zero (int samples,
           Ty* dest,
           int destSkip = 0)
{
    if (destSkip != 0)
    {
      ++destSkip;
      while (--samples >= 0)
      {
        *dest = Ty();
        dest += destSkip;
      }
    }
    else
    {
      std::fill (dest, dest + samples, Ty());
    }
}

#endif

// Fill a set of channels with zero.
template <typename Ty>
void zero (int channels,
           int samples,
           Ty* const* dest,
           int destSkip = 0)
{
  for (int i = channels; --i >= 0;)
    zero (samples, dest[i], destSkip);
}

}

#endif
