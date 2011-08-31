#!/bin/bash
#
# License: MIT License (http://www.opensource.org/licenses/mit-license.php)
# Copyright (c) 2009 by Vincent Falco
#
# This shell script will produce a Juce amalgamation broken up into four source files
# and a handful of supporting files. First you need to build the Juce amalgamator,
# or use a pre-built one, and you need to make sure it can be found in your $PATH.
# Put the shell script just above the juce directory ($JUCE in this script) and run it.
#
# After the script finishes, there will be some new files in your juce/ directory.
# It will create the following files, which will let you use Juce in your project.
# Each of these files is labeled with usage instructions at the top.
#
#   AppConfig.h
#   JuceHeader.h
#   JuceLibraryCode1.mm
#   JuceLibraryCode2.mm
#   JuceLibraryCode3.mm
#   JuceLibraryCode4.mm
#   JuceLibraryCode1.cpp
#   JuceLibraryCode2.cpp
#   JuceLibraryCode3.cpp
#   JuceLibraryCode4.cpp
#
# In addition, the script produces these files, which you don't use directly but
# must be present in order to work. They contain the amalgamated Juce source tree.
#
#   juce_amalgamated.h
#   juce_amalgamated1.cpp
#   juce_amalgamated2.cpp
#   juce_amalgamated3.cpp
#   juce_amalgamated4.cpp
#
# In your project, all these files must be placed together in the same directory
# and you might need to add a preprocessor #include path so that you can
# include "JuceHeader.h"
#
# The use of Juce is covered by a separate license, see the appropriate
# Juce files for details, or visit
# http://www.rawmaterialsoftware.com
#

# some conveniences
JUCE=juce/
AMAL=amalgamation/
DEST=juce_amalgamation/
NAME=juce_amalgamated
CONF="AppConfig.h"
HEAD="JuceHeader.h"
LIBN="JuceLibraryCode"

# create a default app config if needed
if [ ! -f "${JUCE}${CONF}" ]; then
cat << EOF > "${JUCE}${CONF}";
// Configuration for the Juce library.
// Edit as needed by uncommenting and changing the value to 0 or 1

// Settings
//#define  JUCE_FORCE_DEBUG
//#define  JUCE_LOG_ASSERTIONS
//#define  JUCE_ENABLE_REPAINT_DEBUGGING
//#define  JUCE_CHECK_MEMORY_LEAKS
//#define  JUCE_CATCH_UNHANDLED_EXCEPTIONS

// All Platforms
//#define  JUCE_OPENGL
//#define  JUCE_USE_FLAC
//#define  JUCE_USE_OGGVORBIS

// Trying to turn these off causes compile errors
//#define  JUCE_INCLUDE_ZLIB_CODE
//#define  JUCE_INCLUDE_FLAC_CODE
//#define  JUCE_INCLUDE_OGGVORBIS_CODE
//#define  JUCE_INCLUDE_PNGLIB_CODE
//#define  JUCE_INCLUDE_JPEGLIB_CODE

// Windows and MacOS
//#define  JUCE_QUICKTIME
//#define  JUCE_USE_CDBURNER
//#define  JUCE_USE_CDREADER
//#define  JUCE_USE_CAMERA
//#define  JUCE_WEB_BROWSER

// Windows
//#define  JUCE_ASIO
//#define  JUCE_WASAPI
//#define  JUCE_DIRECTSOUND
//#define  JUCE_DIRECTSHOW
//#define  JUCE_MEDIAFOUNDATION
//#define  JUCE_DIRECT2D

// MacOS
//#define  JUCE_SUPPORT_CARBON

// Linux
//#define  JUCE_ALSA
//#define  JUCE_USE_XINERAMA
//#define  JUCE_USE_XSHM
//#define  JUCE_USE_XRENDER
//#define  JUCE_USE_XCURSOR

// Plugins
#define    JUCE_PLUGINHOST_VST 0
#define    JUCE_PLUGINHOST_AU 0

//#define  JUCE_ONLY_BUILD_CORE_LIBRARY
EOF
fi

# create a default juce header if needed
if [ ! -f "${JUCE}${HEAD}" ]; then
cat << EOF > "${JUCE}${HEAD}";
// #include this header in your source files to use Juce

#ifndef __JUCEHEADER_AMALGAMATION_HEADER__
#define __JUCEHEADER_AMALGAMATION_HEADER__

#include "AppConfig.h"
#include "juce_amalgamated.h"

#endif
EOF
fi

# create the .mm files included in mac projects

if [ ! -f "${JUCE}${LIBN}1.mm" ]; then
cat << EOF > "${JUCE}${LIBN}1.mm";
// Add this to your MacOS or iOS project to use Juce

#include "${CONF}"
#include "${NAME}1.cpp"
EOF
fi

if [ ! -f "${JUCE}${LIBN}2.mm" ]; then
cat << EOF > "${JUCE}${LIBN}2.mm";
// Add this to your MacOS or iOS project to use Juce

#include "${CONF}"
#include "${NAME}2.cpp"
EOF
fi

if [ ! -f "${JUCE}${LIBN}3.mm" ]; then
cat << EOF > "${JUCE}${LIBN}3.mm";
// Add this to your MacOS or iOS project to use Juce

#include "${CONF}"
#include "${NAME}3.cpp"
EOF
fi

if [ ! -f "${JUCE}${LIBN}4.mm" ]; then
cat << EOF > "${JUCE}${LIBN}4.mm";
// Add this to your MacOS or iOS project to use Juce

#include "${CONF}"
#include "${NAME}4.cpp"
EOF
fi

# create the .cpp files included in other projects

if [ ! -f "${JUCE}${LIBN}1.cpp" ]; then
cat << EOF > "${JUCE}${LIBN}1.cpp";
// Add this to your project to use Juce
// MacOS or iOS projects should not include this file.

#include "${CONF}"
#include "${NAME}1.cpp"
EOF
fi

if [ ! -f "${JUCE}${LIBN}2.cpp" ]; then
cat << EOF > "${JUCE}${LIBN}2.cpp";
// Add this to your project to use Juce
// MacOS or iOS projects should not include this file.

#include "${CONF}"
#include "${NAME}2.cpp"
EOF
fi

if [ ! -f "${JUCE}${LIBN}3.cpp" ]; then
cat << EOF > "${JUCE}${LIBN}3.cpp";
// Add this to your project to use Juce
// MacOS or iOS projects should not include this file.

#include "${CONF}"
#include "${NAME}3.cpp"
EOF
fi

if [ ! -f "${JUCE}${LIBN}4.cpp" ]; then
cat << EOF > "${JUCE}${LIBN}4.cpp";
// Add this to your project to use Juce
// MacOS or iOS projects should not include this file.

#include "${CONF}"
#include "${NAME}4.cpp"
EOF
fi

# first sync the juce amalgamation to produce juce_amalgamated.h
amalgamator "${JUCE}"

# Now produce a split amalgamation
amalgamator "${JUCE}${AMAL}${NAME}_template.h" "${JUCE}${AMAL}${NAME}1.cpp" "${JUCE}${NAME}1.cpp" -d
amalgamator "${JUCE}${AMAL}${NAME}_template.h" "${JUCE}${AMAL}${NAME}2.cpp" "${JUCE}${NAME}2.cpp" -d
amalgamator "${JUCE}${AMAL}${NAME}_template.h" "${JUCE}${AMAL}${NAME}3.cpp" "${JUCE}${NAME}3.cpp" -d
amalgamator "${JUCE}${AMAL}${NAME}_template.h" "${JUCE}${AMAL}${NAME}4.cpp" "${JUCE}${NAME}4.cpp" -d

# done
