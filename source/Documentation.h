


/*

DspFilters Documentation

Biquad
  Represents the coefficients of a second order section.

State
DirectFormI
DirectFormII
  Contains state information necessary to process samples

Design
  Anything with this word is part of the gui-friendly layer,
  which supports introspection and polymorphism. Filter must
  derive from a Design in order to pick up the functions
  necessary for the templates to work.

Filters and Designs get combined in order to produce the polymorphic objects.


"A Collection of Useful C++ Classes for Digital Signal Processing"

"Techniques for digital signal processing are well guarded and held
close to the chest, as they have valuable applications for multimedia
content. The black art of Infinite Impulse Response ("IIR") filtering
has remained shrouded in secrecy with little publicly available source
code....until now." - Vincent Falco

Building on the work of cherished luminaries such as Sophocles Orfanidis,
Andreas Antoniou, Martin Holters, and Udo Zolzer, this library harnesses
the power of C++ templates to obtain the holy grail of digital signal
processing: the realization of multichannel IIR filters of arbitrary order
and prescribed specifications with various response types such as
Butterworth, Chebyshev, and Elliptic functions. The library is provided
under the MIT license and is therefore fully compatible with proprietary
usage.

Classes are designed as independent re-usable building blocks. Use some
or all of the provided features, or extend the functionality by writing
your own objects that plug into the robust framework. Only the code
that you need will get linked into your application. Here's a list of
features:

- Exclusive focus on IIR filters instead of boring FIR filters (/yawn)
- Complete implementation of all "RBJ Biquad" Cookbook filter formulas
- Butterworth, Chebyshev, Elliptic, Bessel designs
- Low Pass, High Pass, Band Pass, Band Stop transformations
- Low, High, and Band Shelf filter implementations for all types
- Smooth interpolation of filter settings, pole/zeros, and
  biquad coefficients to achieve seamless parameter changes
- Representation of digital filters using poles and zeros
- Realization using Direct Form I, Direct Form II, or user provided class
- Fully factored to minimize template instantiations
- "Design" layer provides runtime introspection into a filter
- Utility template functions for manipulating buffers of sample data
- No calls to malloc or new, great for embedded systems
- No external dependencies, just the standard C++ library!

An accompanying demonstration application, which works on most popular
platforms by using the seperately licensed Juce library, exercises all the
functionality of the library, including these features:

- Dynamic interface creates itself using filter introspection capabilities
- Audio playback with real time application of a selected filter
- Live time stretching and amplitude modulation without clicks or popping
- Charts to show magnitude, phase response and pole/zero placement
- Thread safety "best practices" for audio applications

If you've been searching in futility on the Internet for some source code
that does exactly what you need it to do, then look no further because
this is the jackpot! Whether you are a student of C++ or digital signal
processing, a writer of audio plugins, or even a VST synthesizer coder,
"A Collection of Useful C++ Classes for Digital Signal Processing" has
something for you!

Bibliography:

[1] "Spectral Transformations for digital filters"
     A. G. Constantinides, B.Sc.(Eng.) Ph.D.
     (Proceedings of the IEEE, vol. 117, pp. 1585-1590, August 1970)



*/


