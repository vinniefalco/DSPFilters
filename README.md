# A Collection of Useful C++ Classes for Digital Signal Processing

"Techniques for digital signal processing are well guarded and held close to the chest, as they have valuable applications for multimedia content. The black art of Infinite Impulse Response ("IIR") filtering has remained veiled in secrecy with little publicly available source code...until now."

A production of OneGuy™, the Free Software Gurus?

What is this?

Building on the work of cherished luminaries such as Sophocles Orfanidis, Andreas Antoniou, Martin Holters, and Udo Zolzer, this library harnesses the power of C++ templates to solve a useful problem in digital signal processing: the realization of multichannel IIR filters of arbitrary order and prescribed specifications with various properties such as Butterworth, Chebyshev, Elliptic, and Optimum-L (Legendre) responses. The library is provided under the MIT license and is therefore fully compatible with proprietary usage.

Classes are designed as independent re-usable building blocks. Use some or all of the provided features, or extend the functionality by writing your own objects that plug into the robust framework. Only the code that you need will get linked into your application. Here's a list of features:

    Exclusive focus on IIR filters instead of boring FIR filters
    Complete implementation of all "RBJ Biquad" Cookbook filter formulas
    Butterworth, Chebyshev, Elliptic, Bessel, Legendre designs
    Low Pass, High Pass, Band Pass, Band Stop transformations
    Low, High, and Band Shelf filter implementations for most types
    Smooth interpolation of filter settings, pole/zeros, and biquad coefficients to achieve seamless parameter changes
    Representation of digital filters using poles and zeros
    Realization using Direct Form I, Direct Form II, or user provided class
    Fully factored to minimize template instantiations
    "Design" layer provides runtime introspection into a filter
    Utility template functions for manipulating buffers of sample data
    No calls to malloc or new, great for embedded systems
    No external dependencies, just the standard C++ library!
    Documentation! 

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

An accompanying demonstration program that works on most popular platforms by using the separately licensed Juce application framework (included), exercises all the functionality of the library, including these features:

    Dynamic interface creates itself using filter introspection capabilities
    Audio playback with real time application of a selected filter
    Live time stretching and amplitude modulation without clicks or popping
    Charts to show magnitude, phase response and pole/zero placement
    Thread safety "best practices" for audio applications 

Here's a screenshot of the DSP Filters Demo application:

If you've been searching in futility on the Internet for some source code for implementing high order filters, then look no further because this is it! Whether you are a student of C++ or digital signal processing, a writer of audio plugins, or even a VST synthesizer coder, "A Collection of Useful C++ Classes for Digital Signal Processing" might have something for you!

UPDATED Friday August 19th

Now includes an XCode4 project, which lets you build the DSP Filters Demo application for Macintosh 32/64 bit, iPad or iPhone simulator, and iPhone, iPad, and iPod! This project can be used as a starting point for building your own multi-platform application by removing the demo source files and adding in your own code, while keeping the Juce framework!

This is the application running on an iPad: 


/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vincent Falco

*******************************************************************************/

XCode4 Users:

  Make a new workspace and add the project in
    shared/DSPFiltersDemo/Builds/XCode4/

  Output files go into DerivedData like usual.

  Instructions to customize shared build settings is in
    user/settings/XCode4/

--------------------------------------------------------------------------------

Visual Studio 2008 Users:

  Open the workspace located in
    user/Workspaces/VisualStudio2008

Visual Studio 2010 Users:

  Open the workspace located in
    user/Workspaces/VisualStudio2008

All Visual Studio Users:

  Intermediate and Product files will be placed in a new
  directory in the same place as the solution. The name of
  the directory is "$(SolutionName)-Output"

  To create your own workspace for the demo (if you want it
  outside the repo, or you want to add it to your existing
  workspace), add all three of the project files appropraite
  for your IDE. Then choose Project->Project Dependencies and
  make DSPFiltersDemo dependent on DSPFilters and JuceAmalgam.

  It is also possible to add DSPFilters and/or JuceAmalgam to
  your workspace without the demo. Both produce static libraries
  and neither is dependent on the other.

  If you want to customize the own build settings (.vsprops and
  .props files), make a copy of the user/ directory that is not
  connected to the svn repo (for example, delete all the hidden
  .svn directories), and change your DSPFilters working copy root
  to "trunk/shared" instead. Put the "user" directory in the same
  directory that contains the "trunk/shared" working copy. Now you
  can check the "user" directory into your own private SVN repo
  and play with the build settings (and copy them to your own
  private projects). When you update and rebuild DSPFilters, it
  will use your settings instead.

  I use the svn:externals in my private repo so that DSPFilters
  looks like a seamless part of my repository even though it is
  hosted on Google Code. Using the technique of connecting your
  working copy to "trunk/shared" and adding it to svn:externals
  of your private repo, you can now add the copy of the "users"
  directory with your own property sheets to your private repo
  as I have done. When you do an "svn update" on the root of your
  repo, you will automatically pick up DSPFilters changes,
  including changes to the project files, and when you build it
  will continue to use your customized property sheets.

  This works for all builds, including the MacOS and iOS ones.
