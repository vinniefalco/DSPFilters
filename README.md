## A Collection of Useful C++ Classes for Digital Signal Processing

> "Techniques for digital signal processing are well guarded and held
> close to the chest, as they have valuable applications for multimedia
> content. The black art of Infinite Impulse Response ("IIR") filtering
> has remained veiled in secrecy with little publicly available source
> code...until now."

<a href="https://github.com/downloads/vinniefalco/DSPFilters/DSPFiltersComplete.zip">
<img src="https://github.com/vinniefalco/vinniefalco.github.com/raw/master/images/DownloadNow.png">
</a>

### What is this?

Building on the work of cherished luminaries such as Sophocles Orfanidis,
Andreas Antoniou, Martin Holters, and Udo Zolzer, this library harnesses
the power of C++ templates to solve a useful problem in Digital Signal
Processing: the realization of multichannel IIR filters of arbitrary order
and prescribed specifications with various properties such as Butterworth,
Chebyshev, Elliptic, and Optimum-L (Legendre) responses. The library is
provided under the MIT license and is therefore fully compatible with
proprietary usage.

Classes are designed as independent re-usable building blocks. Use some or
all of the provided features, or extend the functionality by writing your
own objects that plug into the robust framework. Only the code that you
need will get linked into your application. Here's a list of features:

- Exclusive focus on IIR filters instead of boring FIR filters
- Complete implementation of all "RBJ Biquad" Cookbook filter formulas
- Butterworth, Chebyshev, Elliptic, Bessel, Legendre designs
- Low Pass, High Pass, Band Pass, Band Stop transformations
- Low, High, and Band Shelf filter implementations for most types
- Smooth interpolation of filter settings, pole/zeros, and biquad
  coefficients to achieve seamless parameter changes
- Representation of digital filters using poles and zeros
- Realization using Direct Form I, Direct Form II, or user provided class
- Fully factored to minimize template instantiations
- "Design" layer provides runtime introspection into a filter
- Utility template functions for manipulating buffers of sample data
- No calls to malloc or new, great for embedded systems
- No external dependencies, just the standard C++ library!

Using these filters is easy:

    // Create a Chebyshev type I Band Stop filter of order 3
    // with state for processing 2 channels of audio.
    Dsp::SimpleFilter <Dsp::ChebyshevI::BandStop <3>, 2> f;
    f.setup (3,    // order
             44100,// sample rate
             4000, // center frequency
             880,  // band width
             1);   // ripple dB
    f.process (numSamples, arrayOfChannels);

An accompanying demonstration program that works on most popular
platforms by using the separately licensed Juce application framework
(included), exercises all the functionality of the library, including
these features:

- Dynamic interface creates itself using filter introspection capabilities
- Audio playback with real time application of a selected filter
- Live time stretching and amplitude modulation without clicks or popping
- Charts to show magnitude, phase response and pole/zero placement
- Thread safety "best practices" for audio applications 

This is the provided DSP Filters Demo application, which demonstrates the
features of the library and uses the Juce application framework to run on
all popular platforms:

<img src="https://github.com/vinniefalco/DSPFilters/raw/gh-pages/images/DSPFiltersScreenshot.png">

If you've been searching in futility on the Internet for some source code
for implementing high order filters, then look no further because this is
it! Whether you are a student of C++ or digital signal processing, a writer
of audio plugins, or even a VST synthesizer coder, "A Collection of Useful
C++ Classes for Digital Signal Processing" might have something for you!

### DSP Filters on the Web

DSP Filters Official Discussion Forum<br>
http://www.kvraudio.com/forum/viewtopic.php?t=249926

DSP and Audio Plugin Discussion Forum<br>
http://www.kvraudio.com/forum/viewforum.php?f=33

Juce Official Discussion Forum<br>
http://www.rawmaterialsoftware.com/index.php

Juce Official Site<br>
http://www.rawmaterialsoftware.com

### Terms and Conditions
DSP Filters Library and DSP Demo Application Copyright (c) 2009 by
[Vinnie Falco](http://github.com/vinniefalco)<br>
Source code is provided under the
[MIT License](http://www.opensource.org/licenses/mit-license.php)<br>
The [Juce Library](http://www.rawmaterialsoftware.com) is licensed
separately, from [Raw Material Software](http://rawmaterialsoftware.com).
