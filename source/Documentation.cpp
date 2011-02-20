/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.h for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vincent Falco

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

********************************************************************************

="A Collection of Useful C++ Classes for Digital Signal Processing"=
_By Vincent Falco_

_"Techniques for digital signal processing are well guarded and held
close to the chest, as they have valuable applications for multimedia
content. The black art of Infinite Impulse Response ("IIR") filtering
has remained shrouded in secrecy with little publicly available source
code....until now."_

----
Building on the work of cherished luminaries such as Sophocles Orfanidis, Andreas Antoniou, Martin Holters, and Udo Zolzer, this library harnesses the power of C++ templates to solve a useful problem in digital signal processing: the realization of multichannel IIR filters of arbitrary order and prescribed specifications with various properties such as Butterworth, Chebyshev, and Elliptic responses. The library is provided under the MIT license and is therefore fully compatible with proprietary usage.

Classes are designed as independent re-usable building blocks. Use some or all of the provided features, or extend the functionality by writing your own objects that plug into the robust framework. Only the code that you need will get linked into your application. Here's a list of features:

	* Exclusive focus on IIR filters instead of boring FIR filters
	* Complete implementation of all "RBJ Biquad" Cookbook filter formulas
	* Butterworth, Chebyshev, Elliptic, Bessel designs
	* Low Pass, High Pass, Band Pass, Band Stop transformations
	* Low, High, and Band Shelf filter implementations for all types
	* Smooth interpolation of filter settings, pole/zeros, and biquad coefficients to achieve seamless parameter changes
	* Representation of digital filters using poles and zeros
	* Realization using Direct Form I, Direct Form II, or user provided class
	* Fully factored to minimize template instantiations
	* "Design" layer provides runtime introspection into a filter
	* Utility template functions for manipulating buffers of sample data
	* No calls to malloc or new, great for embedded systems
	* No external dependencies, just the standard C++ library!

An accompanying demonstration application, which works on most popular platforms by using the separately licensed Juce source library (included), exercises all the functionality of the library, including these features:

	* Dynamic interface creates itself using filter introspection capabilities
	* Audio playback with real time application of a selected filter
	* Live time stretching and amplitude modulation without clicks or popping
	* Charts to show magnitude, phase response and pole/zero placement
	* Thread safety "best practices" for audio applications

Using these filters is easy:

{{{
    // Create a Chebyshev type I Band Stop filter of order 3
    // with state for processing 2 channels of audio.
    Dsp::SimpleFilter <Dsp::ChebyshevI::BandStop <3>, 2> f;
    f.setup (3,    // order
             44100,// sample rate
             4000, // center frequency
             880,  // band width
             1);   // ripple dB
    f.process (numSamples, arrayOfChannels);
}}}

If you've been searching in futility on the Internet for some source code for implementing high order filters, then look no further because this is it! Whether you are a student of C++ or digital signal processing, a writer of audio plugins, or even a VST synthesizer coder, "A Collection of Useful C++ Classes for Digital Signal Processing" might have something for you!

-----
Notes
-----

Please direct all comments this DSP and Plug-in Development forum:

http://www.kvraudio.com/forum/viewforum.php?f=33

-------
Credits
-------

All of this code was written by the author Vincent Falco except where marked.

Some filter ideas are based on a java applet (http://www.falstad.com/dfilter/)
developed by Paul Falstad.

------------
Bibliography
------------

"High-Order Digital Parametric Equalizer Design"
 Sophocles J. Orfanidis
 (Journal of the Audio Engineering Society, vol 53. pp 1026-1046)

http://crca.ucsd.edu/~msp/techniques/v0.08/book-html/node1.html
 
"Spectral Transformations for digital filters"
 A. G. Constantinides, B.Sc.(Eng.) Ph.D.
 (Proceedings of the IEEE, vol. 117, pp. 1585-1590, August 1970)

*******************************************************************************/

//
// Usage Examples
//
// This shows you how to operate the filters
//

// This is the only include you need
#include "DspFilters/Dsp.h"

namespace {

void UsageExamples ()
{
  // create a two channel audio buffer
  int numSamples = 2000;
  float* audioData[2];
  audioData[0] = new float[numSamples];
  audioData[1] = new float[numSamples];

  // create a 2-channel RBJ Low Pass with parameter smoothing
  // and apply it to the audio data
  {
    // "1024" is the number of samples over which to fade parameter changes
    Dsp::Filter* f = new Dsp::SmoothedFilterDesign
      <Dsp::RBJ::Design::LowPass, 2> (1024);
    Dsp::Params params;
    params[0] = 44100; // sample rate
    params[1] = 4000; // cutoff frequency
    params[2] = 1.25; // Q
    f->setParams (params);
    f->process (numSamples, audioData);
  }
 
  // set up a 2-channel RBJ High Pass with parameter smoothing,
  // but bypass virtual function overhead
  {
    // the difference here is that we don't go through a pointer.
    Dsp::SmoothedFilterDesign <Dsp::RBJ::Design::LowPass, 2> f (1024);
    Dsp::Params params;
    params[0] = 44100; // sample rate
    params[1] = 4000; // cutoff frequency
    params[2] = 1.25; // Q
    f.setParams (params);
    f.process (numSamples, audioData);
  }

  // create a 2-channel Butterworth Band Pass of order 4,
  // with parameter smoothing and apply it to the audio data.
  // Output samples are generated using Direct Form II realization.
  {
    Dsp::Filter* f = new Dsp::SmoothedFilterDesign
      <Dsp::Butterworth::Design::BandPass <4>, 2, Dsp::DirectFormII> (1024);
    Dsp::Params params;
    params[0] = 44100; // sample rate
    params[1] = 4; // order
    params[2] = 4000; // center frequency
    params[3] = 880; // band width
    f->setParams (params);
    f->process (numSamples, audioData);
  }
 
  // create a 2-channel Inverse Chebyshev Low Shelf of order 5
  // and passband ripple 0.1dB, without parameter smoothing and apply it.
  {
    Dsp::Filter* f = new Dsp::FilterDesign
      <Dsp::ChebyshevII::Design::LowShelf <5>, 2>;
    Dsp::Params params;
    params[0] = 44100; // sample rate
    params[1] = 5; // order
    params[2] = 4000; // corner frequency
    params[3] = 6; // shelf gain
    params[4] = 0.1; // passband ripple
    f->setParams (params);
    f->process (numSamples, audioData);
  }
 
  // create an abstract Butterworth High Pass of order 4.
  // This one can't process channels, it can only be used for analysis
  // (i.e. extract poles and zeros).
  {
    Dsp::Filter* f = new Dsp::FilterDesign
      <Dsp::Butterworth::Design::HighPass <4> >;
    Dsp::Params params;
    params[0] = 44100; // sample rate
    params[1] = 4; // order
    params[2] = 4000; // cutoff frequency
    f->setParams (params);
    // this will cause a runtime assertion
    f->process (numSamples, audioData);
  }

  // Use the simple filter API to create a Chebyshev Band Stop of order 3
  // and 1dB ripple in the passband. The simle API has a smaller
  // footprint, but no introspection or smoothing.
  {
    // Note we use the raw filter instead of the one
    // from the Design namespace.
    Dsp::SimpleFilter <Dsp::ChebyshevI::BandStop <3>, 2> f;
    f.setup (3,    // order
             44100,// sample rate
             4000, // center frequency
             880,  // band width
             1);   // ripple dB
    f.process (numSamples, audioData);
  }
}

}
