// Configuration for the Juce library.
// Edit as needed by uncommenting and changing the value to 0 or 1

// Settings
//#define  JUCE_FORCE_DEBUG
//#define  JUCE_LOG_ASSERTIONS
//#define  JUCE_ENABLE_REPAINT_DEBUGGING
//#define  JUCE_CHECK_MEMORY_LEAKS
//#define  JUCE_CATCH_UNHANDLED_EXCEPTIONS

// All Platforms
#define  JUCE_OPENGL 0
#define  JUCE_USE_FLAC 0
#define  JUCE_USE_OGGVORBIS 0

// Trying to turn these off causes compile errors
//#define  JUCE_INCLUDE_ZLIB_CODE
//#define  JUCE_INCLUDE_FLAC_CODE
//#define  JUCE_INCLUDE_OGGVORBIS_CODE
//#define  JUCE_INCLUDE_PNGLIB_CODE
//#define  JUCE_INCLUDE_JPEGLIB_CODE

// Windows and MacOS
#define  JUCE_QUICKTIME 0
#define  JUCE_USE_CDBURNER 0
#define  JUCE_USE_CDREADER 0
#define  JUCE_USE_CAMERA 0
#define  JUCE_WEB_BROWSER 0

// Windows
//#define  JUCE_ASIO
//#define  JUCE_WASAPI
//#define  JUCE_DIRECTSOUND
//#define  JUCE_DIRECTSHOW
//#define  JUCE_MEDIAFOUNDATION
//#define  JUCE_DIRECT2D

// MacOS
#define  JUCE_SUPPORT_CARBON 0

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
