/* bypass certain compile time usage checks */
#define JUCE_AMALGAMATED_INCLUDE 1

#include "AppConfig.h"


/*** Start of inlined file: juce_cryptography.cpp ***/
#if defined (__JUCE_CRYPTOGRAPHY_JUCEHEADER__) && ! JUCE_AMALGAMATED_INCLUDE
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
	already included any other headers - just put it inside a file on its own, possibly with your config
	flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
	header files that the compiler may be using.
 */
 #error "Incorrect use of JUCE cpp file"
#endif

// Your project must contain an AppConfig.h file with your project-specific settings in it,
// and your header search path must make it accessible to the module's files.
#include "AppConfig.h"


/*** Start of inlined file: juce_cryptography.h ***/
#ifndef __JUCE_CRYPTOGRAPHY_JUCEHEADER__
#define __JUCE_CRYPTOGRAPHY_JUCEHEADER__


/*** Start of inlined file: juce_core.h ***/
#ifndef __JUCE_CORE_JUCEHEADER__
#define __JUCE_CORE_JUCEHEADER__


/*** Start of inlined file: juce_TargetPlatform.h ***/
#ifndef __JUCE_TARGETPLATFORM_JUCEHEADER__
#define __JUCE_TARGETPLATFORM_JUCEHEADER__

/*  This file figures out which platform is being built, and defines some macros
	that the rest of the code can use for OS-specific compilation.

	Macros that will be set here are:

	- One of JUCE_WINDOWS, JUCE_MAC JUCE_LINUX, JUCE_IOS, JUCE_ANDROID, etc.
	- Either JUCE_32BIT or JUCE_64BIT, depending on the architecture.
	- Either JUCE_LITTLE_ENDIAN or JUCE_BIG_ENDIAN.
	- Either JUCE_INTEL or JUCE_PPC
	- Either JUCE_GCC or JUCE_MSVC
*/

/* This line is here as a sanity-check to catch syntax errors caused by mistakes in 3rd-party
   header files that have been included before this one. If you hit an error at this line, there
   must be some kind of syntax problem in whatever code immediately precedes this header.

   It also causes an error if you attempt to build using a C or obj-C compiler rather than a C++ one.
*/
namespace JuceDummyNamespace {}

#if (defined (_WIN32) || defined (_WIN64))
  #define       JUCE_WIN32 1
  #define       JUCE_WINDOWS 1
#elif defined (JUCE_ANDROID)
  #undef        JUCE_ANDROID
  #define       JUCE_ANDROID 1
#elif defined (LINUX) || defined (__linux__)
  #define     JUCE_LINUX 1
#elif defined (__APPLE_CPP__) || defined(__APPLE_CC__)
  #define Point CarbonDummyPointName // (workaround to avoid definition of "Point" by old Carbon headers)
  #define Component CarbonDummyCompName
  #include <CoreFoundation/CoreFoundation.h> // (needed to find out what platform we're using)
  #undef Point
  #undef Component

  #if TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR
	#define     JUCE_IPHONE 1
	#define     JUCE_IOS 1
  #else
	#define     JUCE_MAC 1
  #endif
#else
  #error "Unknown platform!"
#endif

#if JUCE_WINDOWS
  #ifdef _MSC_VER
	#ifdef _WIN64
	  #define JUCE_64BIT 1
	#else
	  #define JUCE_32BIT 1
	#endif
  #endif

  #ifdef _DEBUG
	#define JUCE_DEBUG 1
  #endif

  #ifdef __MINGW32__
	#define JUCE_MINGW 1
  #endif

  /** If defined, this indicates that the processor is little-endian. */
  #define JUCE_LITTLE_ENDIAN 1

  #define JUCE_INTEL 1
#endif

#if JUCE_MAC || JUCE_IOS

  #if defined (DEBUG) || defined (_DEBUG) || ! (defined (NDEBUG) || defined (_NDEBUG))
	#define JUCE_DEBUG 1
  #endif

  #if ! (defined (DEBUG) || defined (_DEBUG) || defined (NDEBUG) || defined (_NDEBUG))
	#warning "Neither NDEBUG or DEBUG has been defined - you should set one of these to make it clear whether this is a release build,"
  #endif

  #ifdef __LITTLE_ENDIAN__
	#define JUCE_LITTLE_ENDIAN 1
  #else
	#define JUCE_BIG_ENDIAN 1
  #endif
#endif

#if JUCE_MAC

  #if defined (__ppc__) || defined (__ppc64__)
	#define JUCE_PPC 1
  #else
	#define JUCE_INTEL 1
  #endif

  #ifdef __LP64__
	#define JUCE_64BIT 1
  #else
	#define JUCE_32BIT 1
  #endif

  #if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_4
	#error "Building for OSX 10.3 is no longer supported!"
  #endif

  #ifndef MAC_OS_X_VERSION_10_5
	#error "To build with 10.4 compatibility, use a 10.5 or 10.6 SDK and set the deployment target to 10.4"
  #endif

#endif

#if JUCE_LINUX || JUCE_ANDROID

  #ifdef _DEBUG
	#define JUCE_DEBUG 1
  #endif

  // Allow override for big-endian Linux platforms
  #if defined (__LITTLE_ENDIAN__) || ! defined (JUCE_BIG_ENDIAN)
	#define JUCE_LITTLE_ENDIAN 1
	#undef JUCE_BIG_ENDIAN
  #else
	#undef JUCE_LITTLE_ENDIAN
	#define JUCE_BIG_ENDIAN 1
  #endif

  #if defined (__LP64__) || defined (_LP64)
	#define JUCE_64BIT 1
  #else
	#define JUCE_32BIT 1
  #endif

  #if __MMX__ || __SSE__ || __amd64__
	#define JUCE_INTEL 1
  #endif
#endif

// Compiler type macros.

#ifdef __GNUC__
  #define JUCE_GCC 1
#elif defined (_MSC_VER)
  #define JUCE_MSVC 1

  #if _MSC_VER < 1500
	#define JUCE_VC8_OR_EARLIER 1

	#if _MSC_VER < 1400
	  #define JUCE_VC7_OR_EARLIER 1

	  #if _MSC_VER < 1300
		#warning "MSVC 6.0 is no longer supported!"
	  #endif
	#endif
  #endif

  #if JUCE_64BIT || ! JUCE_VC7_OR_EARLIER
	#define JUCE_USE_INTRINSICS 1
  #endif
#else
  #error unknown compiler
#endif

#endif   // __JUCE_TARGETPLATFORM_JUCEHEADER__

/*** End of inlined file: juce_TargetPlatform.h ***/

/** Config: JUCE_FORCE_DEBUG

	Normally, JUCE_DEBUG is set to 1 or 0 based on compiler and project settings,
	but if you define this value, you can override this to force it to be true or false.
*/
#ifndef JUCE_FORCE_DEBUG
 //#define JUCE_FORCE_DEBUG 0
#endif

/** Config: JUCE_LOG_ASSERTIONS

	If this flag is enabled, the the jassert and jassertfalse macros will always use Logger::writeToLog()
	to write a message when an assertion happens.

	Enabling it will also leave this turned on in release builds. When it's disabled,
	however, the jassert and jassertfalse macros will not be compiled in a
	release build.

	@see jassert, jassertfalse, Logger
*/
#ifndef JUCE_LOG_ASSERTIONS
 #define JUCE_LOG_ASSERTIONS 0
#endif

/** Config: JUCE_CHECK_MEMORY_LEAKS

	Enables a memory-leak check for certain objects when the app terminates. See the LeakedObjectDetector
	class and the JUCE_LEAK_DETECTOR macro for more details about enabling leak checking for specific classes.
*/
#if JUCE_DEBUG && ! defined (JUCE_CHECK_MEMORY_LEAKS)
 #define JUCE_CHECK_MEMORY_LEAKS 1
#endif

/** Config: JUCE_DONT_AUTOLINK_TO_WIN32_LIBRARIES

	In a Visual C++  build, this can be used to stop the required system libs being
	automatically added to the link stage.
*/
#ifndef JUCE_DONT_AUTOLINK_TO_WIN32_LIBRARIES
 #define JUCE_DONT_AUTOLINK_TO_WIN32_LIBRARIES 0
#endif

/*  Config: JUCE_INCLUDE_ZLIB_CODE
	This can be used to disable Juce's embedded 3rd-party zlib code.
	You might need to tweak this if you're linking to an external zlib library in your app,
	but for normal apps, this option should be left alone.

	If you disable this, you might also want to set a value for JUCE_ZLIB_INCLUDE_PATH, to
	specify the path where your zlib headers live.
*/
#ifndef JUCE_INCLUDE_ZLIB_CODE
 #define JUCE_INCLUDE_ZLIB_CODE 1
#endif

#ifndef JUCE_ZLIB_INCLUDE_PATH
 #define JUCE_ZLIB_INCLUDE_PATH <zlib.h>
#endif

/*  Config: JUCE_CATCH_UNHANDLED_EXCEPTIONS
	If enabled, this will add some exception-catching code to forward unhandled exceptions
	to your JUCEApplication::unhandledException() callback.
*/
#ifndef JUCE_CATCH_UNHANDLED_EXCEPTIONS
 //#define JUCE_CATCH_UNHANDLED_EXCEPTIONS 1
#endif

#if JUCE_MSVC
 #pragma warning (disable: 4251) // (DLL build warning, must be disabled before pushing the warning state)

 #pragma pack (push, 8) // this is set explicitly in case the app is using a different packing size.
 #pragma warning (push)
 #pragma warning (disable: 4786) // (long class name warning)
 #ifdef __INTEL_COMPILER
  #pragma warning (disable: 1125)
 #endif
#endif


/*** Start of inlined file: juce_StandardHeader.h ***/
#ifndef __JUCE_STANDARDHEADER_JUCEHEADER__
#define __JUCE_STANDARDHEADER_JUCEHEADER__

/** Current JUCE version number.

	See also SystemStats::getJUCEVersion() for a string version.
*/
#define JUCE_MAJOR_VERSION      2
#define JUCE_MINOR_VERSION      0
#define JUCE_BUILDNUMBER        18

/** Current Juce version number.

	Bits 16 to 32 = major version.
	Bits 8 to 16 = minor version.
	Bits 0 to 8 = point release.

	See also SystemStats::getJUCEVersion() for a string version.
*/
#define JUCE_VERSION            ((JUCE_MAJOR_VERSION << 16) + (JUCE_MINOR_VERSION << 8) + JUCE_BUILDNUMBER)

#ifndef DOXYGEN
 // These are old macros that are now deprecated: you should just use the juce namespace directly.
 #define JUCE_NAMESPACE juce
 #define BEGIN_JUCE_NAMESPACE    namespace juce {
 #define END_JUCE_NAMESPACE      }
#endif


/*** Start of inlined file: juce_PlatformDefs.h ***/
#ifndef __JUCE_PLATFORMDEFS_JUCEHEADER__
#define __JUCE_PLATFORMDEFS_JUCEHEADER__

/*  This file defines miscellaneous macros for debugging, assertions, etc.
*/

#ifdef JUCE_FORCE_DEBUG
 #undef JUCE_DEBUG

 #if JUCE_FORCE_DEBUG
  #define JUCE_DEBUG 1
 #endif
#endif

/** This macro defines the C calling convention used as the standard for Juce calls. */
#if JUCE_MSVC
 #define JUCE_CALLTYPE   __stdcall
 #define JUCE_CDECL      __cdecl
#else
 #define JUCE_CALLTYPE
 #define JUCE_CDECL
#endif

// Debugging and assertion macros

#if JUCE_LOG_ASSERTIONS
 #define juce_LogCurrentAssertion    juce_LogAssertion (__FILE__, __LINE__);
#elif JUCE_DEBUG
 #define juce_LogCurrentAssertion    std::cerr << "JUCE Assertion failure in " << __FILE__ << ", line " << __LINE__ << std::endl;
#else
 #define juce_LogCurrentAssertion
#endif

#if JUCE_MAC || JUCE_IOS || JUCE_LINUX || JUCE_ANDROID
  /** This will try to break into the debugger if the app is currently being debugged.
	  If called by an app that's not being debugged, the behaiour isn't defined - it may crash or not, depending
	  on the platform.
	  @see jassert()
  */
  #define juce_breakDebugger        { ::kill (0, SIGTRAP); }
#elif JUCE_USE_INTRINSICS
  #ifndef __INTEL_COMPILER
	#pragma intrinsic (__debugbreak)
  #endif
  #define juce_breakDebugger        { __debugbreak(); }
#elif JUCE_GCC
  #define juce_breakDebugger        { asm("int $3"); }
#else
  #define juce_breakDebugger        { __asm int 3 }
#endif

#if JUCE_DEBUG || DOXYGEN
  /** Writes a string to the standard error stream.
	  This is only compiled in a debug build.
	  @see Logger::outputDebugString
  */
  #define DBG(dbgtext)              { juce::String tempDbgBuf; tempDbgBuf << dbgtext; juce::Logger::outputDebugString (tempDbgBuf); }

  /** This will always cause an assertion failure.
	  It is only compiled in a debug build, (unless JUCE_LOG_ASSERTIONS is enabled for your build).
	  @see jassert
  */
  #define jassertfalse              { juce_LogCurrentAssertion; if (juce::juce_isRunningUnderDebugger()) juce_breakDebugger; }

  /** Platform-independent assertion macro.

	  This macro gets turned into a no-op when you're building with debugging turned off, so be
	  careful that the expression you pass to it doesn't perform any actions that are vital for the
	  correct behaviour of your program!
	  @see jassertfalse
  */
  #define jassert(expression)       { if (! (expression)) jassertfalse; }

#else

  // If debugging is disabled, these dummy debug and assertion macros are used..

  #define DBG(dbgtext)
  #define jassertfalse              { juce_LogCurrentAssertion }

  #if JUCE_LOG_ASSERTIONS
   #define jassert(expression)      { if (! (expression)) jassertfalse; }
  #else
   #define jassert(a)               {}
  #endif

#endif

#ifndef DOXYGEN
namespace juce
{
	template <bool b> struct JuceStaticAssert;
	template <> struct JuceStaticAssert <true> { static void dummy() {} };
}
#endif

/** A compile-time assertion macro.
	If the expression parameter is false, the macro will cause a compile error. (The actual error
	message that the compiler generates may be completely bizarre and seem to have no relation to
	the place where you put the static_assert though!)
*/
#define static_jassert(expression)      juce::JuceStaticAssert<expression>::dummy();

/** This is a shorthand macro for declaring stubs for a class's copy constructor and operator=.

	For example, instead of
	@code
	class MyClass
	{
		etc..

	private:
		MyClass (const MyClass&);
		MyClass& operator= (const MyClass&);
	};@endcode

	..you can just write:

	@code
	class MyClass
	{
		etc..

	private:
		JUCE_DECLARE_NON_COPYABLE (MyClass);
	};@endcode
*/
#define JUCE_DECLARE_NON_COPYABLE(className) \
	className (const className&);\
	className& operator= (const className&)

/** This is a shorthand way of writing both a JUCE_DECLARE_NON_COPYABLE and
	JUCE_LEAK_DETECTOR macro for a class.
*/
#define JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(className) \
	JUCE_DECLARE_NON_COPYABLE(className);\
	JUCE_LEAK_DETECTOR(className)

/** This macro can be added to class definitions to disable the use of new/delete to
	allocate the object on the heap, forcing it to only be used as a stack or member variable.
*/
#define JUCE_PREVENT_HEAP_ALLOCATION \
   private: \
	static void* operator new (size_t); \
	static void operator delete (void*);

#if ! DOXYGEN
 #define JUCE_JOIN_MACRO_HELPER(a, b) a ## b
 #define JUCE_STRINGIFY_MACRO_HELPER(a) #a
#endif

/** A good old-fashioned C macro concatenation helper.
	This combines two items (which may themselves be macros) into a single string,
	avoiding the pitfalls of the ## macro operator.
*/
#define JUCE_JOIN_MACRO(item1, item2)  JUCE_JOIN_MACRO_HELPER (item1, item2)

/** A handy C macro for stringifying any symbol, rather than just a macro parameter.
*/
#define JUCE_STRINGIFY(item)  JUCE_STRINGIFY_MACRO_HELPER (item)

#if JUCE_CATCH_UNHANDLED_EXCEPTIONS

  #define JUCE_TRY try

  #define JUCE_CATCH_ALL            catch (...) {}
  #define JUCE_CATCH_ALL_ASSERT     catch (...) { jassertfalse; }

  #if ! JUCE_MODULE_AVAILABLE_juce_gui_basics
	#define JUCE_CATCH_EXCEPTION    JUCE_CATCH_ALL
  #else
	/** Used in try-catch blocks, this macro will send exceptions to the JUCEApplication
		object so they can be logged by the application if it wants to.
	*/
	#define JUCE_CATCH_EXCEPTION \
	  catch (const std::exception& e)  \
	  { \
		  JUCEApplication::sendUnhandledException (&e, __FILE__, __LINE__); \
	  } \
	  catch (...) \
	  { \
		  JUCEApplication::sendUnhandledException (nullptr, __FILE__, __LINE__); \
	  }
  #endif

#else

  #define JUCE_TRY
  #define JUCE_CATCH_EXCEPTION
  #define JUCE_CATCH_ALL
  #define JUCE_CATCH_ALL_ASSERT

#endif

#if JUCE_DEBUG || DOXYGEN
  /** A platform-independent way of forcing an inline function.
	  Use the syntax: @code
	  forcedinline void myfunction (int x)
	  @endcode
  */
  #define forcedinline  inline
#else
  #if JUCE_MSVC
   #define forcedinline       __forceinline
  #else
   #define forcedinline       inline __attribute__((always_inline))
  #endif
#endif

#if JUCE_MSVC || DOXYGEN
  /** This can be placed before a stack or member variable declaration to tell the compiler
	  to align it to the specified number of bytes. */
  #define JUCE_ALIGN(bytes)   __declspec (align (bytes))
#else
  #define JUCE_ALIGN(bytes)   __attribute__ ((aligned (bytes)))
#endif

// Cross-compiler deprecation macros..
#if DOXYGEN || (JUCE_MSVC && ! JUCE_NO_DEPRECATION_WARNINGS)
 /** This can be used to wrap a function which has been deprecated. */
 #define JUCE_DEPRECATED(functionDef)     __declspec(deprecated) functionDef
#elif JUCE_GCC  && ! JUCE_NO_DEPRECATION_WARNINGS
 #define JUCE_DEPRECATED(functionDef)     functionDef __attribute__ ((deprecated))
#else
 #define JUCE_DEPRECATED(functionDef)     functionDef
#endif

#if JUCE_ANDROID && ! DOXYGEN
 #define JUCE_MODAL_LOOPS_PERMITTED 0
#else
 /** Some operating environments don't provide a modal loop mechanism, so this flag can be
	 used to disable any functions that try to run a modal loop. */
 #define JUCE_MODAL_LOOPS_PERMITTED 1
#endif

// Here, we'll check for C++11 compiler support, and if it's not available, define
// a few workarounds, so that we can still use some of the newer language features.
#if defined (__GXX_EXPERIMENTAL_CXX0X__) && defined (__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5))
 #define JUCE_COMPILER_SUPPORTS_NOEXCEPT 1
 #define JUCE_COMPILER_SUPPORTS_NULLPTR 1
 #define JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS 1
#endif

#if defined (__clang__) && defined (__has_feature)
 #if __has_feature (cxx_nullptr)
  #define JUCE_COMPILER_SUPPORTS_NULLPTR 1
 #endif

 #if __has_feature (cxx_noexcept)
  #define JUCE_COMPILER_SUPPORTS_NOEXCEPT 1
 #endif

 #if __has_feature (cxx_rvalue_references)
  #define JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS 1
 #endif
#endif

#if defined (_MSC_VER) && _MSC_VER >= 1600
 #define JUCE_COMPILER_SUPPORTS_NOEXCEPT 0
 #define JUCE_COMPILER_SUPPORTS_NULLPTR 1
 #define JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS 1
#endif

// Declare some fake versions of nullptr and noexcept, for older compilers:
#if ! (DOXYGEN || JUCE_COMPILER_SUPPORTS_NOEXCEPT)
 #define noexcept  throw()
#endif

#if ! (DOXYGEN || JUCE_COMPILER_SUPPORTS_NULLPTR)
 #define nullptr (0)
#endif

#endif   // __JUCE_PLATFORMDEFS_JUCEHEADER__

/*** End of inlined file: juce_PlatformDefs.h ***/

// Now we'll include any OS headers we need.. (at this point we are outside the Juce namespace).
#if JUCE_MSVC
 #pragma warning (push)
 #pragma warning (disable: 4514 4245 4100)
#endif

#include <cstdlib>
#include <cstdarg>
#include <climits>
#include <limits>
#include <cmath>
#include <cwchar>
#include <stdexcept>
#include <typeinfo>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>

#if JUCE_USE_INTRINSICS
 #include <intrin.h>
#endif

#if JUCE_MAC || JUCE_IOS
 #include <libkern/OSAtomic.h>
#endif

#if JUCE_LINUX
 #include <signal.h>

 #if __INTEL_COMPILER
  #if __ia64__
   #include <ia64intrin.h>
  #else
   #include <ia32intrin.h>
  #endif
 #endif
#endif

#if JUCE_MSVC && JUCE_DEBUG
 #include <crtdbg.h>
#endif

#if JUCE_MSVC
 #include <malloc.h>
 #pragma warning (pop)
#endif

#if JUCE_ANDROID
 #include <sys/atomics.h>
 #include <byteswap.h>
#endif

// DLL building settings on Windows
#if JUCE_MSVC
 #ifdef JUCE_DLL_BUILD
  #define JUCE_API __declspec (dllexport)
  #pragma warning (disable: 4251)
 #elif defined (JUCE_DLL)
  #define JUCE_API __declspec (dllimport)
  #pragma warning (disable: 4251)
 #endif
 #ifdef __INTEL_COMPILER
  #pragma warning (disable: 1125) // (virtual override warning)
 #endif
#elif defined (__GNUC__) && ((__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
 #ifdef JUCE_DLL_BUILD
  #define JUCE_API __attribute__ ((visibility("default")))
 #endif
#endif

#ifndef JUCE_API
 /** This macro is added to all juce public class declarations. */
 #define JUCE_API
#endif

/** This macro is added to all juce public function declarations. */
#define JUCE_PUBLIC_FUNCTION        JUCE_API JUCE_CALLTYPE

/** This turns on some non-essential bits of code that should prevent old code from compiling
	in cases where method signatures have changed, etc.
*/
#if (! defined (JUCE_CATCH_DEPRECATED_CODE_MISUSE)) && JUCE_DEBUG && ! DOXYGEN
 #define JUCE_CATCH_DEPRECATED_CODE_MISUSE 1
#endif

// Now include some basics that are needed by most of the Juce classes...
BEGIN_JUCE_NAMESPACE

extern JUCE_API bool JUCE_CALLTYPE juce_isRunningUnderDebugger();

#if JUCE_LOG_ASSERTIONS
 extern JUCE_API void juce_LogAssertion (const char* filename, int lineNum) noexcept;
#endif


/*** Start of inlined file: juce_Memory.h ***/
#ifndef __JUCE_MEMORY_JUCEHEADER__
#define __JUCE_MEMORY_JUCEHEADER__

#if JUCE_MSVC || DOXYGEN
 /** This is a compiler-independent way of declaring a variable as being thread-local.

	 E.g.
	 @code
	 juce_ThreadLocal int myVariable;
	 @endcode
 */
 #define juce_ThreadLocal    __declspec(thread)
#else
 #define juce_ThreadLocal    __thread
#endif

#if JUCE_MINGW
 /** This allocator is not defined in mingw gcc. */
 #define alloca              __builtin_alloca
#endif

/** Fills a block of memory with zeros. */
inline void zeromem (void* memory, size_t numBytes) noexcept        { memset (memory, 0, numBytes); }

/** Overwrites a structure or object with zeros. */
template <typename Type>
inline void zerostruct (Type& structure) noexcept                   { memset (&structure, 0, sizeof (structure)); }

/** Delete an object pointer, and sets the pointer to null.

	Remember that it's not good c++ practice to use delete directly - always try to use a ScopedPointer
	or other automatic lieftime-management system rather than resorting to deleting raw pointers!
*/
template <typename Type>
inline void deleteAndZero (Type& pointer)                           { delete pointer; pointer = nullptr; }

/** A handy function which adds a number of bytes to any type of pointer and returns the result.
	This can be useful to avoid casting pointers to a char* and back when you want to move them by
	a specific number of bytes,
*/
template <typename Type>
inline Type* addBytesToPointer (Type* pointer, int bytes) noexcept  { return (Type*) (((char*) pointer) + bytes); }

/** A handy function which returns the difference between any two pointers, in bytes.
	The address of the second pointer is subtracted from the first, and the difference in bytes is returned.
*/
template <typename Type1, typename Type2>
inline int getAddressDifference (Type1* pointer1, Type2* pointer2) noexcept  { return (int) (((const char*) pointer1) - (const char*) pointer2); }

/** If a pointer is non-null, this returns a new copy of the object that it points to, or safely returns
	nullptr if the pointer is null.
*/
template <class Type>
inline Type* createCopyIfNotNull (Type* pointer)     { return pointer != nullptr ? new Type (*pointer) : nullptr; }

/* In a Windows DLL build, we'll expose some malloc/free functions that live inside the DLL, and use these for
   allocating all the objects - that way all juce objects in the DLL and in the host will live in the same heap,
   avoiding problems when an object is created in one module and passed across to another where it is deleted.
   By piggy-backing on the JUCE_LEAK_DETECTOR macro, these allocators can be injected into most juce classes.
*/
#if JUCE_MSVC && defined (JUCE_DLL) && ! DOXYGEN
 extern JUCE_API void* juceDLL_malloc (size_t);
 extern JUCE_API void  juceDLL_free (void*);

 #define JUCE_LEAK_DETECTOR(OwnerClass)  public:\
			  static void* operator new (size_t sz)           { return juce::juceDLL_malloc ((int) sz); } \
			  static void* operator new (size_t, void* p)     { return p; } \
			  static void operator delete (void* p)           { juce::juceDLL_free (p); } \
			  static void operator delete (void*, void*)      {}
#endif

/** (Deprecated) This was a Windows-specific way of checking for object leaks - now please
	use the JUCE_LEAK_DETECTOR instead.
*/
#ifndef juce_UseDebuggingNewOperator
 #define juce_UseDebuggingNewOperator
#endif

#endif   // __JUCE_MEMORY_JUCEHEADER__

/*** End of inlined file: juce_Memory.h ***/


/*** Start of inlined file: juce_MathsFunctions.h ***/
#ifndef __JUCE_MATHSFUNCTIONS_JUCEHEADER__
#define __JUCE_MATHSFUNCTIONS_JUCEHEADER__

/*
	This file sets up some handy mathematical typdefs and functions.
*/

// Definitions for the int8, int16, int32, int64 and pointer_sized_int types.

/** A platform-independent 8-bit signed integer type. */
typedef signed char                 int8;
/** A platform-independent 8-bit unsigned integer type. */
typedef unsigned char               uint8;
/** A platform-independent 16-bit signed integer type. */
typedef signed short                int16;
/** A platform-independent 16-bit unsigned integer type. */
typedef unsigned short              uint16;
/** A platform-independent 32-bit signed integer type. */
typedef signed int                  int32;
/** A platform-independent 32-bit unsigned integer type. */
typedef unsigned int                uint32;

#if JUCE_MSVC
  /** A platform-independent 64-bit integer type. */
  typedef __int64                   int64;
  /** A platform-independent 64-bit unsigned integer type. */
  typedef unsigned __int64          uint64;
  /** A platform-independent macro for writing 64-bit literals, needed because
	  different compilers have different syntaxes for this.

	  E.g. writing literal64bit (0x1000000000) will translate to 0x1000000000LL for
	  GCC, or 0x1000000000 for MSVC.
  */
  #define literal64bit(longLiteral)     ((__int64) longLiteral)
#else
  /** A platform-independent 64-bit integer type. */
  typedef long long                 int64;
  /** A platform-independent 64-bit unsigned integer type. */
  typedef unsigned long long        uint64;
  /** A platform-independent macro for writing 64-bit literals, needed because
	  different compilers have different syntaxes for this.

	  E.g. writing literal64bit (0x1000000000) will translate to 0x1000000000LL for
	  GCC, or 0x1000000000 for MSVC.
  */
  #define literal64bit(longLiteral)     (longLiteral##LL)
#endif

#if JUCE_64BIT
  /** A signed integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
  typedef int64                     pointer_sized_int;
  /** An unsigned integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
  typedef uint64                    pointer_sized_uint;
#elif JUCE_MSVC
  /** A signed integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
  typedef _W64 int                  pointer_sized_int;
  /** An unsigned integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
  typedef _W64 unsigned int         pointer_sized_uint;
#else
  /** A signed integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
  typedef int                       pointer_sized_int;
  /** An unsigned integer type that's guaranteed to be large enough to hold a pointer without truncating it. */
  typedef unsigned int              pointer_sized_uint;
#endif

#if JUCE_MSVC
  typedef pointer_sized_int ssize_t;
#endif

// Some indispensible min/max functions

/** Returns the larger of two values. */
template <typename Type>
inline Type jmax (const Type a, const Type b)                                               { return (a < b) ? b : a; }

/** Returns the larger of three values. */
template <typename Type>
inline Type jmax (const Type a, const Type b, const Type c)                                 { return (a < b) ? ((b < c) ? c : b) : ((a < c) ? c : a); }

/** Returns the larger of four values. */
template <typename Type>
inline Type jmax (const Type a, const Type b, const Type c, const Type d)                   { return jmax (a, jmax (b, c, d)); }

/** Returns the smaller of two values. */
template <typename Type>
inline Type jmin (const Type a, const Type b)                                               { return (b < a) ? b : a; }

/** Returns the smaller of three values. */
template <typename Type>
inline Type jmin (const Type a, const Type b, const Type c)                                 { return (b < a) ? ((c < b) ? c : b) : ((c < a) ? c : a); }

/** Returns the smaller of four values. */
template <typename Type>
inline Type jmin (const Type a, const Type b, const Type c, const Type d)                   { return jmin (a, jmin (b, c, d)); }

/** Scans an array of values, returning the minimum value that it contains. */
template <typename Type>
const Type findMinimum (const Type* data, int numValues)
{
	if (numValues <= 0)
		return Type();

	Type result (*data++);

	while (--numValues > 0) // (> 0 rather than >= 0 because we've already taken the first sample)
	{
		const Type& v = *data++;
		if (v < result)  result = v;
	}

	return result;
}

/** Scans an array of values, returning the maximum value that it contains. */
template <typename Type>
const Type findMaximum (const Type* values, int numValues)
{
	if (numValues <= 0)
		return Type();

	Type result (*values++);

	while (--numValues > 0) // (> 0 rather than >= 0 because we've already taken the first sample)
	{
		const Type& v = *values++;
		if (result < v)  result = v;
	}

	return result;
}

/** Scans an array of values, returning the minimum and maximum values that it contains. */
template <typename Type>
void findMinAndMax (const Type* values, int numValues, Type& lowest, Type& highest)
{
	if (numValues <= 0)
	{
		lowest = Type();
		highest = Type();
	}
	else
	{
		Type mn (*values++);
		Type mx (mn);

		while (--numValues > 0) // (> 0 rather than >= 0 because we've already taken the first sample)
		{
			const Type& v = *values++;

			if (mx < v)  mx = v;
			if (v < mn)  mn = v;
		}

		lowest = mn;
		highest = mx;
	}
}

/** Constrains a value to keep it within a given range.

	This will check that the specified value lies between the lower and upper bounds
	specified, and if not, will return the nearest value that would be in-range. Effectively,
	it's like calling jmax (lowerLimit, jmin (upperLimit, value)).

	Note that it expects that lowerLimit <= upperLimit. If this isn't true,
	the results will be unpredictable.

	@param lowerLimit           the minimum value to return
	@param upperLimit           the maximum value to return
	@param valueToConstrain     the value to try to return
	@returns    the closest value to valueToConstrain which lies between lowerLimit
				and upperLimit (inclusive)
	@see jlimit0To, jmin, jmax
*/
template <typename Type>
inline Type jlimit (const Type lowerLimit,
					const Type upperLimit,
					const Type valueToConstrain) noexcept
{
	jassert (lowerLimit <= upperLimit); // if these are in the wrong order, results are unpredictable..

	return (valueToConstrain < lowerLimit) ? lowerLimit
										   : ((upperLimit < valueToConstrain) ? upperLimit
																			  : valueToConstrain);
}

/** Returns true if a value is at least zero, and also below a specified upper limit.
	This is basically a quicker way to write:
	@code valueToTest >= 0 && valueToTest < upperLimit
	@endcode
*/
template <typename Type>
inline bool isPositiveAndBelow (Type valueToTest, Type upperLimit) noexcept
{
	jassert (Type() <= upperLimit); // makes no sense to call this if the upper limit is itself below zero..
	return Type() <= valueToTest && valueToTest < upperLimit;
}

template <>
inline bool isPositiveAndBelow (const int valueToTest, const int upperLimit) noexcept
{
	jassert (upperLimit >= 0); // makes no sense to call this if the upper limit is itself below zero..
	return static_cast <unsigned int> (valueToTest) < static_cast <unsigned int> (upperLimit);
}

/** Returns true if a value is at least zero, and also less than or equal to a specified upper limit.
	This is basically a quicker way to write:
	@code valueToTest >= 0 && valueToTest <= upperLimit
	@endcode
*/
template <typename Type>
inline bool isPositiveAndNotGreaterThan (Type valueToTest, Type upperLimit) noexcept
{
	jassert (Type() <= upperLimit); // makes no sense to call this if the upper limit is itself below zero..
	return Type() <= valueToTest && valueToTest <= upperLimit;
}

template <>
inline bool isPositiveAndNotGreaterThan (const int valueToTest, const int upperLimit) noexcept
{
	jassert (upperLimit >= 0); // makes no sense to call this if the upper limit is itself below zero..
	return static_cast <unsigned int> (valueToTest) <= static_cast <unsigned int> (upperLimit);
}

/** Handy function to swap two values. */
template <typename Type>
inline void swapVariables (Type& variable1, Type& variable2)
{
	std::swap (variable1, variable2);
}

/** Handy function for getting the number of elements in a simple const C array.
	E.g.
	@code
	static int myArray[] = { 1, 2, 3 };

	int numElements = numElementsInArray (myArray) // returns 3
	@endcode
*/
template <typename Type, int N>
inline int numElementsInArray (Type (&array)[N])
{
	(void) array; // (required to avoid a spurious warning in MS compilers)
	(void) sizeof (0[array]); // This line should cause an error if you pass an object with a user-defined subscript operator
	return N;
}

// Some useful maths functions that aren't always present with all compilers and build settings.

/** Using juce_hypot is easier than dealing with the different types of hypot function
	that are provided by the various platforms and compilers. */
template <typename Type>
inline Type juce_hypot (Type a, Type b) noexcept
{
   #if JUCE_WINDOWS
	return static_cast <Type> (_hypot (a, b));
   #else
	return static_cast <Type> (hypot (a, b));
   #endif
}

/** 64-bit abs function. */
inline int64 abs64 (const int64 n) noexcept
{
	return (n >= 0) ? n : -n;
}

/** This templated negate function will negate pointers as well as integers */
template <typename Type>
inline Type juce_negate (Type n) noexcept
{
	return sizeof (Type) == 1 ? (Type) -(signed char) n
		: (sizeof (Type) == 2 ? (Type) -(short) n
		: (sizeof (Type) == 4 ? (Type) -(int) n
		: ((Type) -(int64) n)));
}

/** This templated negate function will negate pointers as well as integers */
template <typename Type>
inline Type* juce_negate (Type* n) noexcept
{
	return (Type*) -(pointer_sized_int) n;
}

/** A predefined value for Pi, at double-precision.

	@see float_Pi
*/
const double  double_Pi  = 3.1415926535897932384626433832795;

/** A predefined value for Pi, at sngle-precision.

	@see double_Pi
*/
const float   float_Pi   = 3.14159265358979323846f;

/** The isfinite() method seems to vary between platforms, so this is a
	platform-independent function for it.
*/
template <typename FloatingPointType>
inline bool juce_isfinite (FloatingPointType value)
{
   #if JUCE_WINDOWS
	return _finite (value);
   #elif JUCE_ANDROID
	return isfinite (value);
   #else
	return std::isfinite (value);
   #endif
}

#if JUCE_MSVC
 #pragma optimize ("t", off)
 #pragma float_control (precise, on, push)
#endif

/** Fast floating-point-to-integer conversion.

	This is faster than using the normal c++ cast to convert a float to an int, and
	it will round the value to the nearest integer, rather than rounding it down
	like the normal cast does.

	Note that this routine gets its speed at the expense of some accuracy, and when
	rounding values whose floating point component is exactly 0.5, odd numbers and
	even numbers will be rounded up or down differently.
*/
template <typename FloatType>
inline int roundToInt (const FloatType value) noexcept
{
	union { int asInt[2]; double asDouble; } n;
	n.asDouble = ((double) value) + 6755399441055744.0;

   #if JUCE_BIG_ENDIAN
	return n.asInt [1];
   #else
	return n.asInt [0];
   #endif
}

#if JUCE_MSVC
 #pragma float_control (pop)
 #pragma optimize ("", on)  // resets optimisations to the project defaults
#endif

/** Fast floating-point-to-integer conversion.

	This is a slightly slower and slightly more accurate version of roundDoubleToInt(). It works
	fine for values above zero, but negative numbers are rounded the wrong way.
*/
inline int roundToIntAccurate (const double value) noexcept
{
	return roundToInt (value + 1.5e-8);
}

/** Fast floating-point-to-integer conversion.

	This is faster than using the normal c++ cast to convert a double to an int, and
	it will round the value to the nearest integer, rather than rounding it down
	like the normal cast does.

	Note that this routine gets its speed at the expense of some accuracy, and when
	rounding values whose floating point component is exactly 0.5, odd numbers and
	even numbers will be rounded up or down differently. For a more accurate conversion,
	see roundDoubleToIntAccurate().
*/
inline int roundDoubleToInt (const double value) noexcept
{
	return roundToInt (value);
}

/** Fast floating-point-to-integer conversion.

	This is faster than using the normal c++ cast to convert a float to an int, and
	it will round the value to the nearest integer, rather than rounding it down
	like the normal cast does.

	Note that this routine gets its speed at the expense of some accuracy, and when
	rounding values whose floating point component is exactly 0.5, odd numbers and
	even numbers will be rounded up or down differently.
*/
inline int roundFloatToInt (const float value) noexcept
{
	return roundToInt (value);
}

/** Returns true if the specified integer is a power-of-two.
*/
template <typename IntegerType>
bool isPowerOfTwo (IntegerType value)
{
   return (value & (value - 1)) == 0;
}

/** Returns the next power-of-two which is equal to or greater than the given integer.
*/
inline int nextPowerOfTwo (int n)
{
	--n;
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	return n + 1;
}

/** Performs a modulo operation, but can cope with the dividend being negative.
	The divisor must be greater than zero.
*/
template <typename IntegerType>
int negativeAwareModulo (IntegerType dividend, const IntegerType divisor) noexcept
{
	jassert (divisor > 0);
	dividend %= divisor;
	return (dividend < 0) ? (dividend + divisor) : dividend;
}

#if (JUCE_INTEL && JUCE_32BIT) || defined (DOXYGEN)
 /** This macro can be applied to a float variable to check whether it contains a denormalised
	 value, and to normalise it if necessary.
	 On CPUs that aren't vulnerable to denormalisation problems, this will have no effect.
 */
 #define JUCE_UNDENORMALISE(x)   x += 1.0f; x -= 1.0f;
#else
 #define JUCE_UNDENORMALISE(x)
#endif

/** This namespace contains a few template classes for helping work out class type variations.
*/
namespace TypeHelpers
{
   #if JUCE_VC8_OR_EARLIER
	#define PARAMETER_TYPE(type) const type&
   #else
	/** The ParameterType struct is used to find the best type to use when passing some kind
		of object as a parameter.

		Of course, this is only likely to be useful in certain esoteric template situations.

		Because "typename TypeHelpers::ParameterType<SomeClass>::type" is a bit of a mouthful, there's
		a PARAMETER_TYPE(SomeClass) macro that you can use to get the same effect.

		E.g. "myFunction (PARAMETER_TYPE (int), PARAMETER_TYPE (MyObject))"
		would evaluate to "myfunction (int, const MyObject&)", keeping any primitive types as
		pass-by-value, but passing objects as a const reference, to avoid copying.
	*/
	template <typename Type> struct ParameterType                   { typedef const Type& type; };

   #if ! DOXYGEN
	template <typename Type> struct ParameterType <Type&>           { typedef Type& type; };
	template <typename Type> struct ParameterType <Type*>           { typedef Type* type; };
	template <>              struct ParameterType <char>            { typedef char type; };
	template <>              struct ParameterType <unsigned char>   { typedef unsigned char type; };
	template <>              struct ParameterType <short>           { typedef short type; };
	template <>              struct ParameterType <unsigned short>  { typedef unsigned short type; };
	template <>              struct ParameterType <int>             { typedef int type; };
	template <>              struct ParameterType <unsigned int>    { typedef unsigned int type; };
	template <>              struct ParameterType <long>            { typedef long type; };
	template <>              struct ParameterType <unsigned long>   { typedef unsigned long type; };
	template <>              struct ParameterType <int64>           { typedef int64 type; };
	template <>              struct ParameterType <uint64>          { typedef uint64 type; };
	template <>              struct ParameterType <bool>            { typedef bool type; };
	template <>              struct ParameterType <float>           { typedef float type; };
	template <>              struct ParameterType <double>          { typedef double type; };
   #endif

	/** A helpful macro to simplify the use of the ParameterType template.
		@see ParameterType
	*/
	#define PARAMETER_TYPE(a)    typename TypeHelpers::ParameterType<a>::type
   #endif

	/** These templates are designed to take a type, and if it's a double, they return a double
		type; for anything else, they return a float type.
	*/
	template <typename Type> struct SmallestFloatType             { typedef float  type; };
	template <>              struct SmallestFloatType <double>    { typedef double type; };
}

#endif   // __JUCE_MATHSFUNCTIONS_JUCEHEADER__

/*** End of inlined file: juce_MathsFunctions.h ***/


/*** Start of inlined file: juce_ByteOrder.h ***/
#ifndef __JUCE_BYTEORDER_JUCEHEADER__
#define __JUCE_BYTEORDER_JUCEHEADER__

/** Contains static methods for converting the byte order between different
	endiannesses.
*/
class JUCE_API  ByteOrder
{
public:

	/** Swaps the upper and lower bytes of a 16-bit integer. */
	static uint16 swap (uint16 value);

	/** Reverses the order of the 4 bytes in a 32-bit integer. */
	static uint32 swap (uint32 value);

	/** Reverses the order of the 8 bytes in a 64-bit integer. */
	static uint64 swap (uint64 value);

	/** Swaps the byte order of a 16-bit int if the CPU is big-endian */
	static uint16 swapIfBigEndian (uint16 value);

	/** Swaps the byte order of a 32-bit int if the CPU is big-endian */
	static uint32 swapIfBigEndian (uint32 value);

	/** Swaps the byte order of a 64-bit int if the CPU is big-endian */
	static uint64 swapIfBigEndian (uint64 value);

	/** Swaps the byte order of a 16-bit int if the CPU is little-endian */
	static uint16 swapIfLittleEndian (uint16 value);

	/** Swaps the byte order of a 32-bit int if the CPU is little-endian */
	static uint32 swapIfLittleEndian (uint32 value);

	/** Swaps the byte order of a 64-bit int if the CPU is little-endian */
	static uint64 swapIfLittleEndian (uint64 value);

	/** Turns 4 bytes into a little-endian integer. */
	static uint32 littleEndianInt (const void* bytes);

	/** Turns 2 bytes into a little-endian integer. */
	static uint16 littleEndianShort (const void* bytes);

	/** Turns 4 bytes into a big-endian integer. */
	static uint32 bigEndianInt (const void* bytes);

	/** Turns 2 bytes into a big-endian integer. */
	static uint16 bigEndianShort (const void* bytes);

	/** Converts 3 little-endian bytes into a signed 24-bit value (which is sign-extended to 32 bits). */
	static int littleEndian24Bit (const char* bytes);

	/** Converts 3 big-endian bytes into a signed 24-bit value (which is sign-extended to 32 bits). */
	static int bigEndian24Bit (const char* bytes);

	/** Copies a 24-bit number to 3 little-endian bytes. */
	static void littleEndian24BitToChars (int value, char* destBytes);

	/** Copies a 24-bit number to 3 big-endian bytes. */
	static void bigEndian24BitToChars (int value, char* destBytes);

	/** Returns true if the current CPU is big-endian. */
	static bool isBigEndian();

private:
	ByteOrder();

	JUCE_DECLARE_NON_COPYABLE (ByteOrder);
};

#if JUCE_USE_INTRINSICS && ! defined (__INTEL_COMPILER)
 #pragma intrinsic (_byteswap_ulong)
#endif

inline uint16 ByteOrder::swap (uint16 n)
{
   #if JUCE_USE_INTRINSICSxxx // agh - the MS compiler has an internal error when you try to use this intrinsic!
	return static_cast <uint16> (_byteswap_ushort (n));
   #else
	return static_cast <uint16> ((n << 8) | (n >> 8));
   #endif
}

inline uint32 ByteOrder::swap (uint32 n)
{
   #if JUCE_MAC || JUCE_IOS
	return OSSwapInt32 (n);
   #elif JUCE_GCC && JUCE_INTEL
	asm("bswap %%eax" : "=a"(n) : "a"(n));
	return n;
   #elif JUCE_USE_INTRINSICS
	return _byteswap_ulong (n);
   #elif JUCE_MSVC
	__asm {
		mov eax, n
		bswap eax
		mov n, eax
	}
	return n;
   #elif JUCE_ANDROID
	return bswap_32 (n);
   #else
	return (n << 24) | (n >> 24) | ((n & 0xff00) << 8) | ((n & 0xff0000) >> 8);
   #endif
}

inline uint64 ByteOrder::swap (uint64 value)
{
   #if JUCE_MAC || JUCE_IOS
	return OSSwapInt64 (value);
   #elif JUCE_USE_INTRINSICS
	return _byteswap_uint64 (value);
   #else
	return (((int64) swap ((uint32) value)) << 32) | swap ((uint32) (value >> 32));
   #endif
}

#if JUCE_LITTLE_ENDIAN
 inline uint16 ByteOrder::swapIfBigEndian (const uint16 v)                                  { return v; }
 inline uint32 ByteOrder::swapIfBigEndian (const uint32 v)                                  { return v; }
 inline uint64 ByteOrder::swapIfBigEndian (const uint64 v)                                  { return v; }
 inline uint16 ByteOrder::swapIfLittleEndian (const uint16 v)                               { return swap (v); }
 inline uint32 ByteOrder::swapIfLittleEndian (const uint32 v)                               { return swap (v); }
 inline uint64 ByteOrder::swapIfLittleEndian (const uint64 v)                               { return swap (v); }
 inline uint32 ByteOrder::littleEndianInt (const void* const bytes)                         { return *static_cast <const uint32*> (bytes); }
 inline uint16 ByteOrder::littleEndianShort (const void* const bytes)                       { return *static_cast <const uint16*> (bytes); }
 inline uint32 ByteOrder::bigEndianInt (const void* const bytes)                            { return swap (*static_cast <const uint32*> (bytes)); }
 inline uint16 ByteOrder::bigEndianShort (const void* const bytes)                          { return swap (*static_cast <const uint16*> (bytes)); }
 inline bool ByteOrder::isBigEndian()                                                       { return false; }
#else
 inline uint16 ByteOrder::swapIfBigEndian (const uint16 v)                                  { return swap (v); }
 inline uint32 ByteOrder::swapIfBigEndian (const uint32 v)                                  { return swap (v); }
 inline uint64 ByteOrder::swapIfBigEndian (const uint64 v)                                  { return swap (v); }
 inline uint16 ByteOrder::swapIfLittleEndian (const uint16 v)                               { return v; }
 inline uint32 ByteOrder::swapIfLittleEndian (const uint32 v)                               { return v; }
 inline uint64 ByteOrder::swapIfLittleEndian (const uint64 v)                               { return v; }
 inline uint32 ByteOrder::littleEndianInt (const void* const bytes)                         { return swap (*static_cast <const uint32*> (bytes)); }
 inline uint16 ByteOrder::littleEndianShort (const void* const bytes)                       { return swap (*static_cast <const uint16*> (bytes)); }
 inline uint32 ByteOrder::bigEndianInt (const void* const bytes)                            { return *static_cast <const uint32*> (bytes); }
 inline uint16 ByteOrder::bigEndianShort (const void* const bytes)                          { return *static_cast <const uint16*> (bytes); }
 inline bool ByteOrder::isBigEndian()                                                       { return true; }
#endif

inline int  ByteOrder::littleEndian24Bit (const char* const bytes)                          { return (((int) bytes[2]) << 16) | (((int) (uint8) bytes[1]) << 8) | ((int) (uint8) bytes[0]); }
inline int  ByteOrder::bigEndian24Bit (const char* const bytes)                             { return (((int) bytes[0]) << 16) | (((int) (uint8) bytes[1]) << 8) | ((int) (uint8) bytes[2]); }
inline void ByteOrder::littleEndian24BitToChars (const int value, char* const destBytes)    { destBytes[0] = (char)(value & 0xff); destBytes[1] = (char)((value >> 8) & 0xff); destBytes[2] = (char)((value >> 16) & 0xff); }
inline void ByteOrder::bigEndian24BitToChars (const int value, char* const destBytes)       { destBytes[0] = (char)((value >> 16) & 0xff); destBytes[1] = (char)((value >> 8) & 0xff); destBytes[2] = (char)(value & 0xff); }

#endif   // __JUCE_BYTEORDER_JUCEHEADER__

/*** End of inlined file: juce_ByteOrder.h ***/


/*** Start of inlined file: juce_Logger.h ***/
#ifndef __JUCE_LOGGER_JUCEHEADER__
#define __JUCE_LOGGER_JUCEHEADER__


/*** Start of inlined file: juce_String.h ***/
#ifndef __JUCE_STRING_JUCEHEADER__
#define __JUCE_STRING_JUCEHEADER__


/*** Start of inlined file: juce_CharacterFunctions.h ***/
#ifndef __JUCE_CHARACTERFUNCTIONS_JUCEHEADER__
#define __JUCE_CHARACTERFUNCTIONS_JUCEHEADER__

#if JUCE_WINDOWS && ! DOXYGEN
 #define JUCE_NATIVE_WCHAR_IS_UTF8      0
 #define JUCE_NATIVE_WCHAR_IS_UTF16     1
 #define JUCE_NATIVE_WCHAR_IS_UTF32     0
#else
 /** This macro will be set to 1 if the compiler's native wchar_t is an 8-bit type. */
 #define JUCE_NATIVE_WCHAR_IS_UTF8      0
 /** This macro will be set to 1 if the compiler's native wchar_t is a 16-bit type. */
 #define JUCE_NATIVE_WCHAR_IS_UTF16     0
 /** This macro will be set to 1 if the compiler's native wchar_t is a 32-bit type. */
 #define JUCE_NATIVE_WCHAR_IS_UTF32     1
#endif

#if JUCE_NATIVE_WCHAR_IS_UTF32 || DOXYGEN
 /** A platform-independent 32-bit unicode character type. */
 typedef wchar_t        juce_wchar;
#else
 typedef uint32         juce_wchar;
#endif

/** This macro is deprecated, but preserved for compatibility with old code. */
#define JUCE_T(stringLiteral)   (L##stringLiteral)

#if JUCE_DEFINE_T_MACRO
 /** The 'T' macro is an alternative for using the "L" prefix in front of a string literal.

	 This macro is deprecated, but available for compatibility with old code if you set
	 JUCE_DEFINE_T_MACRO = 1. The fastest, most portable and best way to write your string
	 literals is as standard char strings, using escaped utf-8 character sequences for extended
	 characters, rather than trying to store them as wide-char strings.
 */
 #define T(stringLiteral)   JUCE_T(stringLiteral)
#endif

#undef max
#undef min

/**
	A set of methods for manipulating characters and character strings.

	These are defined as wrappers around the basic C string handlers, to provide
	a clean, cross-platform layer, (because various platforms differ in the
	range of C library calls that they provide).

	@see String
*/
class JUCE_API  CharacterFunctions
{
public:

	static juce_wchar toUpperCase (juce_wchar character) noexcept;
	static juce_wchar toLowerCase (juce_wchar character) noexcept;

	static bool isUpperCase (juce_wchar character) noexcept;
	static bool isLowerCase (juce_wchar character) noexcept;

	static bool isWhitespace (char character) noexcept;
	static bool isWhitespace (juce_wchar character) noexcept;

	static bool isDigit (char character) noexcept;
	static bool isDigit (juce_wchar character) noexcept;

	static bool isLetter (char character) noexcept;
	static bool isLetter (juce_wchar character) noexcept;

	static bool isLetterOrDigit (char character) noexcept;
	static bool isLetterOrDigit (juce_wchar character) noexcept;

	/** Returns 0 to 16 for '0' to 'F", or -1 for characters that aren't a legal hex digit. */
	static int getHexDigitValue (juce_wchar digit) noexcept;

	template <typename CharPointerType>
	static double readDoubleValue (CharPointerType& text) noexcept
	{
		double result[3] = { 0 }, accumulator[2] = { 0 };
		int exponentAdjustment[2] = { 0 }, exponentAccumulator[2] = { -1, -1 };
		int exponent = 0, decPointIndex = 0, digit = 0;
		int lastDigit = 0, numSignificantDigits = 0;
		bool isNegative = false, digitsFound = false;
		const int maxSignificantDigits = 15 + 2;

		text = text.findEndOfWhitespace();
		juce_wchar c = *text;

		switch (c)
		{
			case '-':   isNegative = true; // fall-through..
			case '+':   c = *++text;
		}

		switch (c)
		{
			case 'n':
			case 'N':
				if ((text[1] == 'a' || text[1] == 'A') && (text[2] == 'n' || text[2] == 'N'))
					return std::numeric_limits<double>::quiet_NaN();
				break;

			case 'i':
			case 'I':
				if ((text[1] == 'n' || text[1] == 'N') && (text[2] == 'f' || text[2] == 'F'))
					return std::numeric_limits<double>::infinity();
				break;
		}

		for (;;)
		{
			if (text.isDigit())
			{
				lastDigit = digit;
				digit = (int) text.getAndAdvance() - '0';
				digitsFound = true;

				if (decPointIndex != 0)
					exponentAdjustment[1]++;

				if (numSignificantDigits == 0 && digit == 0)
					continue;

				if (++numSignificantDigits > maxSignificantDigits)
				{
					if (digit > 5)
						++accumulator [decPointIndex];
					else if (digit == 5 && (lastDigit & 1) != 0)
						++accumulator [decPointIndex];

					if (decPointIndex > 0)
						exponentAdjustment[1]--;
					else
						exponentAdjustment[0]++;

					while (text.isDigit())
					{
						++text;
						if (decPointIndex == 0)
							exponentAdjustment[0]++;
					}
				}
				else
				{
					const double maxAccumulatorValue = (double) ((std::numeric_limits<unsigned int>::max() - 9) / 10);
					if (accumulator [decPointIndex] > maxAccumulatorValue)
					{
						result [decPointIndex] = mulexp10 (result [decPointIndex], exponentAccumulator [decPointIndex])
													+ accumulator [decPointIndex];
						accumulator [decPointIndex] = 0;
						exponentAccumulator [decPointIndex] = 0;
					}

					accumulator [decPointIndex] = accumulator[decPointIndex] * 10 + digit;
					exponentAccumulator [decPointIndex]++;
				}
			}
			else if (decPointIndex == 0 && *text == '.')
			{
				++text;
				decPointIndex = 1;

				if (numSignificantDigits > maxSignificantDigits)
				{
					while (text.isDigit())
						++text;
					break;
				}
			}
			else
			{
				break;
			}
		}

		result[0] = mulexp10 (result[0], exponentAccumulator[0]) + accumulator[0];

		if (decPointIndex != 0)
			result[1] = mulexp10 (result[1], exponentAccumulator[1]) + accumulator[1];

		c = *text;
		if ((c == 'e' || c == 'E') && digitsFound)
		{
			bool negativeExponent = false;

			switch (*++text)
			{
				case '-':   negativeExponent = true; // fall-through..
				case '+':   ++text;
			}

			while (text.isDigit())
				exponent = (exponent * 10) + ((int) text.getAndAdvance() - '0');

			if (negativeExponent)
				exponent = -exponent;
		}

		double r = mulexp10 (result[0], exponent + exponentAdjustment[0]);
		if (decPointIndex != 0)
			r += mulexp10 (result[1], exponent - exponentAdjustment[1]);

		return isNegative ? -r : r;
	}

	template <typename CharPointerType>
	static double getDoubleValue (const CharPointerType& text) noexcept
	{
		CharPointerType t (text);
		return readDoubleValue (t);
	}

	template <typename IntType, typename CharPointerType>
	static IntType getIntValue (const CharPointerType& text) noexcept
	{
		IntType v = 0;
		CharPointerType s (text.findEndOfWhitespace());

		const bool isNeg = *s == '-';
		if (isNeg)
			++s;

		for (;;)
		{
			const juce_wchar c = s.getAndAdvance();

			if (c >= '0' && c <= '9')
				v = v * 10 + (IntType) (c - '0');
			else
				break;
		}

		return isNeg ? -v : v;
	}

	template <typename CharPointerType>
	static size_t lengthUpTo (CharPointerType text, const size_t maxCharsToCount) noexcept
	{
		size_t len = 0;

		while (len < maxCharsToCount && text.getAndAdvance() != 0)
			++len;

		return len;
	}

	template <typename CharPointerType>
	static size_t lengthUpTo (CharPointerType start, const CharPointerType& end) noexcept
	{
		size_t len = 0;

		while (start < end && start.getAndAdvance() != 0)
			++len;

		return len;
	}

	template <typename DestCharPointerType, typename SrcCharPointerType>
	static void copyAll (DestCharPointerType& dest, SrcCharPointerType src) noexcept
	{
		for (;;)
		{
			const juce_wchar c = src.getAndAdvance();

			if (c == 0)
				break;

			dest.write (c);
		}

		dest.writeNull();
	}

	template <typename DestCharPointerType, typename SrcCharPointerType>
	static int copyWithDestByteLimit (DestCharPointerType& dest, SrcCharPointerType src, int maxBytes) noexcept
	{
		typename DestCharPointerType::CharType const* const startAddress = dest.getAddress();
		maxBytes -= sizeof (typename DestCharPointerType::CharType); // (allow for a terminating null)

		for (;;)
		{
			const juce_wchar c = src.getAndAdvance();
			const int bytesNeeded = (int) DestCharPointerType::getBytesRequiredFor (c);

			maxBytes -= bytesNeeded;
			if (c == 0 || maxBytes < 0)
				break;

			dest.write (c);
		}

		dest.writeNull();

		return (int) (getAddressDifference (dest.getAddress(), startAddress) + sizeof (typename DestCharPointerType::CharType));
	}

	template <typename DestCharPointerType, typename SrcCharPointerType>
	static void copyWithCharLimit (DestCharPointerType& dest, SrcCharPointerType src, int maxChars) noexcept
	{
		while (--maxChars > 0)
		{
			const juce_wchar c = src.getAndAdvance();
			if (c == 0)
				break;

			dest.write (c);
		}

		dest.writeNull();
	}

	template <typename CharPointerType1, typename CharPointerType2>
	static int compare (CharPointerType1 s1, CharPointerType2 s2) noexcept
	{
		for (;;)
		{
			const int c1 = (int) s1.getAndAdvance();
			const int c2 = (int) s2.getAndAdvance();

			const int diff = c1 - c2;
			if (diff != 0)
				return diff < 0 ? -1 : 1;
			else if (c1 == 0)
				break;
		}

		return 0;
	}

	template <typename CharPointerType1, typename CharPointerType2>
	static int compareUpTo (CharPointerType1 s1, CharPointerType2 s2, int maxChars) noexcept
	{
		while (--maxChars >= 0)
		{
			const int c1 = (int) s1.getAndAdvance();
			const int c2 = (int) s2.getAndAdvance();

			const int diff = c1 - c2;
			if (diff != 0)
				return diff < 0 ? -1 : 1;
			else if (c1 == 0)
				break;
		}

		return 0;
	}

	template <typename CharPointerType1, typename CharPointerType2>
	static int compareIgnoreCase (CharPointerType1 s1, CharPointerType2 s2) noexcept
	{
		for (;;)
		{
			int c1 = (int) s1.toUpperCase();
			int c2 = (int) s2.toUpperCase();
			++s1;
			++s2;

			const int diff = c1 - c2;
			if (diff != 0)
				return diff < 0 ? -1 : 1;
			else if (c1 == 0)
				break;
		}

		return 0;
	}

	template <typename CharPointerType1, typename CharPointerType2>
	static int compareIgnoreCaseUpTo (CharPointerType1 s1, CharPointerType2 s2, int maxChars) noexcept
	{
		while (--maxChars >= 0)
		{
			int c1 = s1.toUpperCase();
			int c2 = s2.toUpperCase();
			++s1;
			++s2;

			const int diff = c1 - c2;
			if (diff != 0)
				return diff < 0 ? -1 : 1;
			else if (c1 == 0)
				break;
		}

		return 0;
	}

	template <typename CharPointerType1, typename CharPointerType2>
	static int indexOf (CharPointerType1 haystack, const CharPointerType2& needle) noexcept
	{
		int index = 0;
		const int needleLength = (int) needle.length();

		for (;;)
		{
			if (haystack.compareUpTo (needle, needleLength) == 0)
				return index;

			if (haystack.getAndAdvance() == 0)
				return -1;

			++index;
		}
	}

	template <typename CharPointerType1, typename CharPointerType2>
	static int indexOfIgnoreCase (CharPointerType1 haystack, const CharPointerType2& needle) noexcept
	{
		int index = 0;
		const int needleLength = (int) needle.length();

		for (;;)
		{
			if (haystack.compareIgnoreCaseUpTo (needle, needleLength) == 0)
				return index;

			if (haystack.getAndAdvance() == 0)
				return -1;

			++index;
		}
	}

	template <typename Type>
	static int indexOfChar (Type text, const juce_wchar charToFind) noexcept
	{
		int i = 0;

		while (! text.isEmpty())
		{
			if (text.getAndAdvance() == charToFind)
				return i;

			++i;
		}

		return -1;
	}

	template <typename Type>
	static int indexOfCharIgnoreCase (Type text, juce_wchar charToFind) noexcept
	{
		charToFind = CharacterFunctions::toLowerCase (charToFind);
		int i = 0;

		while (! text.isEmpty())
		{
			if (text.toLowerCase() == charToFind)
				return i;

			++text;
			++i;
		}

		return -1;
	}

	template <typename Type>
	static Type findEndOfWhitespace (const Type& text) noexcept
	{
		Type p (text);

		while (p.isWhitespace())
			++p;

		return p;
	}

	template <typename Type>
	static Type findEndOfToken (const Type& text, const Type& breakCharacters, const Type& quoteCharacters)
	{
		Type t (text);
		juce_wchar currentQuoteChar = 0;

		while (! t.isEmpty())
		{
			const juce_wchar c = t.getAndAdvance();

			if (currentQuoteChar == 0 && breakCharacters.indexOf (c) >= 0)
			{
				--t;
				break;
			}

			if (quoteCharacters.indexOf (c) >= 0)
			{
				if (currentQuoteChar == 0)
					currentQuoteChar = c;
				else if (currentQuoteChar == c)
					currentQuoteChar = 0;
			}
		}

		return t;
	}

private:
	static double mulexp10 (const double value, int exponent) noexcept;
};

#endif   // __JUCE_CHARACTERFUNCTIONS_JUCEHEADER__

/*** End of inlined file: juce_CharacterFunctions.h ***/

#ifndef JUCE_STRING_UTF_TYPE
 #define JUCE_STRING_UTF_TYPE 8
#endif

#if JUCE_MSVC
 #pragma warning (push)
 #pragma warning (disable: 4514 4996)
#endif


/*** Start of inlined file: juce_Atomic.h ***/
#ifndef __JUCE_ATOMIC_JUCEHEADER__
#define __JUCE_ATOMIC_JUCEHEADER__

/**
	Simple class to hold a primitive value and perform atomic operations on it.

	The type used must be a 32 or 64 bit primitive, like an int, pointer, etc.
	There are methods to perform most of the basic atomic operations.
*/
template <typename Type>
class Atomic
{
public:
	/** Creates a new value, initialised to zero. */
	inline Atomic() noexcept
		: value (0)
	{
	}

	/** Creates a new value, with a given initial value. */
	inline Atomic (const Type initialValue) noexcept
		: value (initialValue)
	{
	}

	/** Copies another value (atomically). */
	inline Atomic (const Atomic& other) noexcept
		: value (other.get())
	{
	}

	/** Destructor. */
	inline ~Atomic() noexcept
	{
		// This class can only be used for types which are 32 or 64 bits in size.
		static_jassert (sizeof (Type) == 4 || sizeof (Type) == 8);
	}

	/** Atomically reads and returns the current value. */
	Type get() const noexcept;

	/** Copies another value onto this one (atomically). */
	inline Atomic& operator= (const Atomic& other) noexcept         { exchange (other.get()); return *this; }

	/** Copies another value onto this one (atomically). */
	inline Atomic& operator= (const Type newValue) noexcept         { exchange (newValue); return *this; }

	/** Atomically sets the current value. */
	void set (Type newValue) noexcept                               { exchange (newValue); }

	/** Atomically sets the current value, returning the value that was replaced. */
	Type exchange (Type value) noexcept;

	/** Atomically adds a number to this value, returning the new value. */
	Type operator+= (Type amountToAdd) noexcept;

	/** Atomically subtracts a number from this value, returning the new value. */
	Type operator-= (Type amountToSubtract) noexcept;

	/** Atomically increments this value, returning the new value. */
	Type operator++() noexcept;

	/** Atomically decrements this value, returning the new value. */
	Type operator--() noexcept;

	/** Atomically compares this value with a target value, and if it is equal, sets
		this to be equal to a new value.

		This operation is the atomic equivalent of doing this:
		@code
		bool compareAndSetBool (Type newValue, Type valueToCompare)
		{
			if (get() == valueToCompare)
			{
				set (newValue);
				return true;
			}

			return false;
		}
		@endcode

		@returns true if the comparison was true and the value was replaced; false if
				 the comparison failed and the value was left unchanged.
		@see compareAndSetValue
	*/
	bool compareAndSetBool (Type newValue, Type valueToCompare) noexcept;

	/** Atomically compares this value with a target value, and if it is equal, sets
		this to be equal to a new value.

		This operation is the atomic equivalent of doing this:
		@code
		Type compareAndSetValue (Type newValue, Type valueToCompare)
		{
			Type oldValue = get();
			if (oldValue == valueToCompare)
				set (newValue);

			return oldValue;
		}
		@endcode

		@returns the old value before it was changed.
		@see compareAndSetBool
	*/
	Type compareAndSetValue (Type newValue, Type valueToCompare) noexcept;

	/** Implements a memory read/write barrier. */
	static void memoryBarrier() noexcept;

   #if JUCE_64BIT
	JUCE_ALIGN (8)
   #else
	JUCE_ALIGN (4)
   #endif

	/** The raw value that this class operates on.
		This is exposed publically in case you need to manipulate it directly
		for performance reasons.
	*/
	volatile Type value;

private:
	static inline Type castFrom32Bit (int32 value) noexcept   { return *(Type*) &value; }
	static inline Type castFrom64Bit (int64 value) noexcept   { return *(Type*) &value; }
	static inline int32 castTo32Bit (Type value) noexcept     { return *(int32*) &value; }
	static inline int64 castTo64Bit (Type value) noexcept     { return *(int64*) &value; }

	Type operator++ (int); // better to just use pre-increment with atomics..
	Type operator-- (int);
};

/*
	The following code is in the header so that the atomics can be inlined where possible...
*/
#if JUCE_IOS || (JUCE_MAC && (JUCE_PPC || defined (__clang__) || __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 2)))
  #define JUCE_ATOMICS_MAC 1        // Older OSX builds using gcc4.1 or earlier

  #if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_5
	#define JUCE_MAC_ATOMICS_VOLATILE
  #else
	#define JUCE_MAC_ATOMICS_VOLATILE volatile
  #endif

  #if JUCE_PPC || JUCE_IOS
	// None of these atomics are available for PPC or for iPhoneOS 3.1 or earlier!!
	template <typename Type> static Type OSAtomicAdd64Barrier (Type b, JUCE_MAC_ATOMICS_VOLATILE Type* a) noexcept  { jassertfalse; return *a += b; }
	template <typename Type> static Type OSAtomicIncrement64Barrier (JUCE_MAC_ATOMICS_VOLATILE Type* a) noexcept    { jassertfalse; return ++*a; }
	template <typename Type> static Type OSAtomicDecrement64Barrier (JUCE_MAC_ATOMICS_VOLATILE Type* a) noexcept    { jassertfalse; return --*a; }
	template <typename Type> static bool OSAtomicCompareAndSwap64Barrier (Type old, Type newValue, JUCE_MAC_ATOMICS_VOLATILE Type* value) noexcept
		{ jassertfalse; if (old == *value) { *value = newValue; return true; } return false; }
	#define JUCE_64BIT_ATOMICS_UNAVAILABLE 1
  #endif

#elif JUCE_GCC
  #define JUCE_ATOMICS_GCC 1        // GCC with intrinsics

  #if JUCE_IOS || JUCE_ANDROID // (64-bit ops will compile but not link on these mobile OSes)
	#define JUCE_64BIT_ATOMICS_UNAVAILABLE 1
  #endif

#else
  #define JUCE_ATOMICS_WINDOWS 1    // Windows with intrinsics

  #if JUCE_USE_INTRINSICS
	#ifndef __INTEL_COMPILER
	 #pragma intrinsic (_InterlockedExchange, _InterlockedIncrement, _InterlockedDecrement, _InterlockedCompareExchange, \
						_InterlockedCompareExchange64, _InterlockedExchangeAdd, _ReadWriteBarrier)
	#endif
	#define juce_InterlockedExchange(a, b)              _InterlockedExchange(a, b)
	#define juce_InterlockedIncrement(a)                _InterlockedIncrement(a)
	#define juce_InterlockedDecrement(a)                _InterlockedDecrement(a)
	#define juce_InterlockedExchangeAdd(a, b)           _InterlockedExchangeAdd(a, b)
	#define juce_InterlockedCompareExchange(a, b, c)    _InterlockedCompareExchange(a, b, c)
	#define juce_InterlockedCompareExchange64(a, b, c)  _InterlockedCompareExchange64(a, b, c)
	#define juce_MemoryBarrier _ReadWriteBarrier
  #else
	long juce_InterlockedExchange (volatile long* a, long b) noexcept;
	long juce_InterlockedIncrement (volatile long* a) noexcept;
	long juce_InterlockedDecrement (volatile long* a) noexcept;
	long juce_InterlockedExchangeAdd (volatile long* a, long b) noexcept;
	long juce_InterlockedCompareExchange (volatile long* a, long b, long c) noexcept;
	__int64 juce_InterlockedCompareExchange64 (volatile __int64* a, __int64 b, __int64 c) noexcept;
	inline void juce_MemoryBarrier() noexcept  { long x = 0; juce_InterlockedIncrement (&x); }
  #endif

  #if JUCE_64BIT
	#ifndef __INTEL_COMPILER
	 #pragma intrinsic (_InterlockedExchangeAdd64, _InterlockedExchange64, _InterlockedIncrement64, _InterlockedDecrement64)
	#endif
	#define juce_InterlockedExchangeAdd64(a, b)     _InterlockedExchangeAdd64(a, b)
	#define juce_InterlockedExchange64(a, b)        _InterlockedExchange64(a, b)
	#define juce_InterlockedIncrement64(a)          _InterlockedIncrement64(a)
	#define juce_InterlockedDecrement64(a)          _InterlockedDecrement64(a)
  #else
	// None of these atomics are available in a 32-bit Windows build!!
	template <typename Type> static Type juce_InterlockedExchangeAdd64 (volatile Type* a, Type b) noexcept  { jassertfalse; Type old = *a; *a += b; return old; }
	template <typename Type> static Type juce_InterlockedExchange64 (volatile Type* a, Type b) noexcept     { jassertfalse; Type old = *a; *a = b; return old; }
	template <typename Type> static Type juce_InterlockedIncrement64 (volatile Type* a) noexcept            { jassertfalse; return ++*a; }
	template <typename Type> static Type juce_InterlockedDecrement64 (volatile Type* a) noexcept            { jassertfalse; return --*a; }
	#define JUCE_64BIT_ATOMICS_UNAVAILABLE 1
  #endif
#endif

#if JUCE_MSVC
  #pragma warning (push)
  #pragma warning (disable: 4311)  // (truncation warning)
#endif

template <typename Type>
inline Type Atomic<Type>::get() const noexcept
{
  #if JUCE_ATOMICS_MAC
	return sizeof (Type) == 4 ? castFrom32Bit ((int32) OSAtomicAdd32Barrier ((int32_t) 0, (JUCE_MAC_ATOMICS_VOLATILE int32_t*) &value))
							  : castFrom64Bit ((int64) OSAtomicAdd64Barrier ((int64_t) 0, (JUCE_MAC_ATOMICS_VOLATILE int64_t*) &value));
  #elif JUCE_ATOMICS_WINDOWS
	return sizeof (Type) == 4 ? castFrom32Bit ((int32) juce_InterlockedExchangeAdd ((volatile long*) &value, (long) 0))
							  : castFrom64Bit ((int64) juce_InterlockedExchangeAdd64 ((volatile __int64*) &value, (__int64) 0));
  #elif JUCE_ATOMICS_GCC
	return sizeof (Type) == 4 ? castFrom32Bit ((int32) __sync_add_and_fetch ((volatile int32*) &value, 0))
							  : castFrom64Bit ((int64) __sync_add_and_fetch ((volatile int64*) &value, 0));
  #endif
}

template <typename Type>
inline Type Atomic<Type>::exchange (const Type newValue) noexcept
{
  #if JUCE_ATOMICS_MAC || JUCE_ATOMICS_GCC
	Type currentVal = value;
	while (! compareAndSetBool (newValue, currentVal)) { currentVal = value; }
	return currentVal;
  #elif JUCE_ATOMICS_WINDOWS
	return sizeof (Type) == 4 ? castFrom32Bit ((int32) juce_InterlockedExchange ((volatile long*) &value, (long) castTo32Bit (newValue)))
							  : castFrom64Bit ((int64) juce_InterlockedExchange64 ((volatile __int64*) &value, (__int64) castTo64Bit (newValue)));
  #endif
}

template <typename Type>
inline Type Atomic<Type>::operator+= (const Type amountToAdd) noexcept
{
  #if JUCE_ATOMICS_MAC
	return sizeof (Type) == 4 ? (Type) OSAtomicAdd32Barrier ((int32_t) castTo32Bit (amountToAdd), (JUCE_MAC_ATOMICS_VOLATILE int32_t*) &value)
							  : (Type) OSAtomicAdd64Barrier ((int64_t) amountToAdd, (JUCE_MAC_ATOMICS_VOLATILE int64_t*) &value);
  #elif JUCE_ATOMICS_WINDOWS
	return sizeof (Type) == 4 ? (Type) (juce_InterlockedExchangeAdd ((volatile long*) &value, (long) amountToAdd) + (long) amountToAdd)
							  : (Type) (juce_InterlockedExchangeAdd64 ((volatile __int64*) &value, (__int64) amountToAdd) + (__int64) amountToAdd);
  #elif JUCE_ATOMICS_GCC
	return (Type) __sync_add_and_fetch (&value, amountToAdd);
  #endif
}

template <typename Type>
inline Type Atomic<Type>::operator-= (const Type amountToSubtract) noexcept
{
	return operator+= (juce_negate (amountToSubtract));
}

template <typename Type>
inline Type Atomic<Type>::operator++() noexcept
{
  #if JUCE_ATOMICS_MAC
	return sizeof (Type) == 4 ? (Type) OSAtomicIncrement32Barrier ((JUCE_MAC_ATOMICS_VOLATILE int32_t*) &value)
							  : (Type) OSAtomicIncrement64Barrier ((JUCE_MAC_ATOMICS_VOLATILE int64_t*) &value);
  #elif JUCE_ATOMICS_WINDOWS
	return sizeof (Type) == 4 ? (Type) juce_InterlockedIncrement ((volatile long*) &value)
							  : (Type) juce_InterlockedIncrement64 ((volatile __int64*) &value);
  #elif JUCE_ATOMICS_GCC
	return (Type) __sync_add_and_fetch (&value, 1);
  #endif
}

template <typename Type>
inline Type Atomic<Type>::operator--() noexcept
{
  #if JUCE_ATOMICS_MAC
	return sizeof (Type) == 4 ? (Type) OSAtomicDecrement32Barrier ((JUCE_MAC_ATOMICS_VOLATILE int32_t*) &value)
							  : (Type) OSAtomicDecrement64Barrier ((JUCE_MAC_ATOMICS_VOLATILE int64_t*) &value);
  #elif JUCE_ATOMICS_WINDOWS
	return sizeof (Type) == 4 ? (Type) juce_InterlockedDecrement ((volatile long*) &value)
							  : (Type) juce_InterlockedDecrement64 ((volatile __int64*) &value);
  #elif JUCE_ATOMICS_GCC
	return (Type) __sync_add_and_fetch (&value, -1);
  #endif
}

template <typename Type>
inline bool Atomic<Type>::compareAndSetBool (const Type newValue, const Type valueToCompare) noexcept
{
  #if JUCE_ATOMICS_MAC
	return sizeof (Type) == 4 ? OSAtomicCompareAndSwap32Barrier ((int32_t) castTo32Bit (valueToCompare), (int32_t) castTo32Bit (newValue), (JUCE_MAC_ATOMICS_VOLATILE int32_t*) &value)
							  : OSAtomicCompareAndSwap64Barrier ((int64_t) castTo64Bit (valueToCompare), (int64_t) castTo64Bit (newValue), (JUCE_MAC_ATOMICS_VOLATILE int64_t*) &value);
  #elif JUCE_ATOMICS_WINDOWS
	return compareAndSetValue (newValue, valueToCompare) == valueToCompare;
  #elif JUCE_ATOMICS_GCC
	return sizeof (Type) == 4 ? __sync_bool_compare_and_swap ((volatile int32*) &value, castTo32Bit (valueToCompare), castTo32Bit (newValue))
							  : __sync_bool_compare_and_swap ((volatile int64*) &value, castTo64Bit (valueToCompare), castTo64Bit (newValue));
  #endif
}

template <typename Type>
inline Type Atomic<Type>::compareAndSetValue (const Type newValue, const Type valueToCompare) noexcept
{
  #if JUCE_ATOMICS_MAC
	for (;;) // Annoying workaround for only having a bool CAS operation..
	{
		if (compareAndSetBool (newValue, valueToCompare))
			return valueToCompare;

		const Type result = value;
		if (result != valueToCompare)
			return result;
	}

  #elif JUCE_ATOMICS_WINDOWS
	return sizeof (Type) == 4 ? castFrom32Bit ((int32) juce_InterlockedCompareExchange ((volatile long*) &value, (long) castTo32Bit (newValue), (long) castTo32Bit (valueToCompare)))
							  : castFrom64Bit ((int64) juce_InterlockedCompareExchange64 ((volatile __int64*) &value, (__int64) castTo64Bit (newValue), (__int64) castTo64Bit (valueToCompare)));
  #elif JUCE_ATOMICS_GCC
	return sizeof (Type) == 4 ? castFrom32Bit ((int32) __sync_val_compare_and_swap ((volatile int32*) &value, castTo32Bit (valueToCompare), castTo32Bit (newValue)))
							  : castFrom64Bit ((int64) __sync_val_compare_and_swap ((volatile int64*) &value, castTo64Bit (valueToCompare), castTo64Bit (newValue)));
  #endif
}

template <typename Type>
inline void Atomic<Type>::memoryBarrier() noexcept
{
  #if JUCE_ATOMICS_MAC
	OSMemoryBarrier();
  #elif JUCE_ATOMICS_GCC
	__sync_synchronize();
  #elif JUCE_ATOMICS_WINDOWS
	juce_MemoryBarrier();
  #endif
}

#if JUCE_MSVC
  #pragma warning (pop)
#endif

#endif   // __JUCE_ATOMIC_JUCEHEADER__

/*** End of inlined file: juce_Atomic.h ***/


/*** Start of inlined file: juce_CharPointer_UTF8.h ***/
#ifndef __JUCE_CHARPOINTER_UTF8_JUCEHEADER__
#define __JUCE_CHARPOINTER_UTF8_JUCEHEADER__

/**
	Wraps a pointer to a null-terminated UTF-8 character string, and provides
	various methods to operate on the data.
	@see CharPointer_UTF16, CharPointer_UTF32
*/
class CharPointer_UTF8
{
public:
	typedef char CharType;

	inline explicit CharPointer_UTF8 (const CharType* const rawPointer) noexcept
		: data (const_cast <CharType*> (rawPointer))
	{
	}

	inline CharPointer_UTF8 (const CharPointer_UTF8& other) noexcept
		: data (other.data)
	{
	}

	inline CharPointer_UTF8& operator= (const CharPointer_UTF8& other) noexcept
	{
		data = other.data;
		return *this;
	}

	inline CharPointer_UTF8& operator= (const CharType* text) noexcept
	{
		data = const_cast <CharType*> (text);
		return *this;
	}

	/** This is a pointer comparison, it doesn't compare the actual text. */
	inline bool operator== (const CharPointer_UTF8& other) const noexcept { return data == other.data; }
	inline bool operator!= (const CharPointer_UTF8& other) const noexcept { return data != other.data; }
	inline bool operator<= (const CharPointer_UTF8& other) const noexcept { return data <= other.data; }
	inline bool operator<  (const CharPointer_UTF8& other) const noexcept { return data <  other.data; }
	inline bool operator>= (const CharPointer_UTF8& other) const noexcept { return data >= other.data; }
	inline bool operator>  (const CharPointer_UTF8& other) const noexcept { return data >  other.data; }

	/** Returns the address that this pointer is pointing to. */
	inline CharType* getAddress() const noexcept        { return data; }

	/** Returns the address that this pointer is pointing to. */
	inline operator const CharType*() const noexcept    { return data; }

	/** Returns true if this pointer is pointing to a null character. */
	inline bool isEmpty() const noexcept                { return *data == 0; }

	/** Returns the unicode character that this pointer is pointing to. */
	juce_wchar operator*() const noexcept
	{
		const signed char byte = (signed char) *data;

		if (byte >= 0)
			return (juce_wchar) (uint8) byte;

		uint32 n = (uint32) (uint8) byte;
		uint32 mask = 0x7f;
		uint32 bit = 0x40;
		size_t numExtraValues = 0;

		while ((n & bit) != 0 && bit > 0x10)
		{
			mask >>= 1;
			++numExtraValues;
			bit >>= 1;
		}

		n &= mask;

		for (size_t i = 1; i <= numExtraValues; ++i)
		{
			const uint8 nextByte = (uint8) data [i];

			if ((nextByte & 0xc0) != 0x80)
				break;

			n <<= 6;
			n |= (nextByte & 0x3f);
		}

		return (juce_wchar) n;
	}

	/** Moves this pointer along to the next character in the string. */
	CharPointer_UTF8& operator++() noexcept
	{
		const signed char n = (signed char) *data++;

		if (n < 0)
		{
			juce_wchar bit = 0x40;

			while ((n & bit) != 0 && bit > 0x8)
			{
				++data;
				bit >>= 1;
			}
		}

		return *this;
	}

	/** Moves this pointer back to the previous character in the string. */
	CharPointer_UTF8& operator--() noexcept
	{
		const char n = *--data;

		if ((n & 0xc0) == 0xc0)
		{
			int count = 3;

			do
			{
				--data;
			}
			while ((*data & 0xc0) == 0xc0 && --count >= 0);
		}

		return *this;
	}

	/** Returns the character that this pointer is currently pointing to, and then
		advances the pointer to point to the next character. */
	juce_wchar getAndAdvance() noexcept
	{
		const signed char byte = (signed char) *data++;

		if (byte >= 0)
			return (juce_wchar) (uint8) byte;

		uint32 n = (uint32) (uint8) byte;
		uint32 mask = 0x7f;
		uint32 bit = 0x40;
		int numExtraValues = 0;

		while ((n & bit) != 0 && bit > 0x8)
		{
			mask >>= 1;
			++numExtraValues;
			bit >>= 1;
		}

		n &= mask;

		while (--numExtraValues >= 0)
		{
			const uint32 nextByte = (uint32) (uint8) *data++;

			if ((nextByte & 0xc0) != 0x80)
				break;

			n <<= 6;
			n |= (nextByte & 0x3f);
		}

		return (juce_wchar) n;
	}

	/** Moves this pointer along to the next character in the string. */
	CharPointer_UTF8 operator++ (int) noexcept
	{
		CharPointer_UTF8 temp (*this);
		++*this;
		return temp;
	}

	/** Moves this pointer forwards by the specified number of characters. */
	void operator+= (int numToSkip) noexcept
	{
		if (numToSkip < 0)
		{
			while (++numToSkip <= 0)
				--*this;
		}
		else
		{
			while (--numToSkip >= 0)
				++*this;
		}
	}

	/** Moves this pointer backwards by the specified number of characters. */
	void operator-= (int numToSkip) noexcept
	{
		operator+= (-numToSkip);
	}

	/** Returns the character at a given character index from the start of the string. */
	juce_wchar operator[] (int characterIndex) const noexcept
	{
		CharPointer_UTF8 p (*this);
		p += characterIndex;
		return *p;
	}

	/** Returns a pointer which is moved forwards from this one by the specified number of characters. */
	CharPointer_UTF8 operator+ (int numToSkip) const noexcept
	{
		CharPointer_UTF8 p (*this);
		p += numToSkip;
		return p;
	}

	/** Returns a pointer which is moved backwards from this one by the specified number of characters. */
	CharPointer_UTF8 operator- (int numToSkip) const noexcept
	{
		CharPointer_UTF8 p (*this);
		p += -numToSkip;
		return p;
	}

	/** Returns the number of characters in this string. */
	size_t length() const noexcept
	{
		const CharType* d = data;
		size_t count = 0;

		for (;;)
		{
			const uint32 n = (uint32) (uint8) *d++;

			if ((n & 0x80) != 0)
			{
				uint32 bit = 0x40;

				while ((n & bit) != 0)
				{
					++d;
					bit >>= 1;

					if (bit == 0)
						break; // illegal utf-8 sequence
				}
			}
			else if (n == 0)
				break;

			++count;
		}

		return count;
	}

	/** Returns the number of characters in this string, or the given value, whichever is lower. */
	size_t lengthUpTo (const size_t maxCharsToCount) const noexcept
	{
		return CharacterFunctions::lengthUpTo (*this, maxCharsToCount);
	}

	/** Returns the number of characters in this string, or up to the given end pointer, whichever is lower. */
	size_t lengthUpTo (const CharPointer_UTF8& end) const noexcept
	{
		return CharacterFunctions::lengthUpTo (*this, end);
	}

	/** Returns the number of bytes that are used to represent this string.
		This includes the terminating null character.
	*/
	size_t sizeInBytes() const noexcept
	{
		jassert (data != nullptr);
		return strlen (data) + 1;
	}

	/** Returns the number of bytes that would be needed to represent the given
		unicode character in this encoding format.
	*/
	static size_t getBytesRequiredFor (const juce_wchar charToWrite) noexcept
	{
		size_t num = 1;
		const uint32 c = (uint32) charToWrite;

		if (c >= 0x80)
		{
			++num;
			if (c >= 0x800)
			{
				++num;
				if (c >= 0x10000)
					++num;
			}
		}

		return num;
	}

	/** Returns the number of bytes that would be needed to represent the given
		string in this encoding format.
		The value returned does NOT include the terminating null character.
	*/
	template <class CharPointer>
	static size_t getBytesRequiredFor (CharPointer text) noexcept
	{
		size_t count = 0;
		juce_wchar n;

		while ((n = text.getAndAdvance()) != 0)
			count += getBytesRequiredFor (n);

		return count;
	}

	/** Returns a pointer to the null character that terminates this string. */
	CharPointer_UTF8 findTerminatingNull() const noexcept
	{
		return CharPointer_UTF8 (data + strlen (data));
	}

	/** Writes a unicode character to this string, and advances this pointer to point to the next position. */
	void write (const juce_wchar charToWrite) noexcept
	{
		const uint32 c = (uint32) charToWrite;

		if (c >= 0x80)
		{
			int numExtraBytes = 1;
			if (c >= 0x800)
			{
				++numExtraBytes;
				if (c >= 0x10000)
					++numExtraBytes;
			}

			*data++ = (CharType) ((0xff << (7 - numExtraBytes)) | (c >> (numExtraBytes * 6)));

			while (--numExtraBytes >= 0)
				*data++ = (CharType) (0x80 | (0x3f & (c >> (numExtraBytes * 6))));
		}
		else
		{
			*data++ = (CharType) c;
		}
	}

	/** Writes a null character to this string (leaving the pointer's position unchanged). */
	inline void writeNull() const noexcept
	{
		*data = 0;
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes. */
	template <typename CharPointer>
	void writeAll (const CharPointer& src) noexcept
	{
		CharacterFunctions::copyAll (*this, src);
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes. */
	void writeAll (const CharPointer_UTF8& src) noexcept
	{
		const CharType* s = src.data;

		while ((*data = *s) != 0)
		{
			++data;
			++s;
		}
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes.
		The maxDestBytes parameter specifies the maximum number of bytes that can be written
		to the destination buffer before stopping.
	*/
	template <typename CharPointer>
	int writeWithDestByteLimit (const CharPointer& src, const int maxDestBytes) noexcept
	{
		return CharacterFunctions::copyWithDestByteLimit (*this, src, maxDestBytes);
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes.
		The maxChars parameter specifies the maximum number of characters that can be
		written to the destination buffer before stopping (including the terminating null).
	*/
	template <typename CharPointer>
	void writeWithCharLimit (const CharPointer& src, const int maxChars) noexcept
	{
		CharacterFunctions::copyWithCharLimit (*this, src, maxChars);
	}

	/** Compares this string with another one. */
	template <typename CharPointer>
	int compare (const CharPointer& other) const noexcept
	{
		return CharacterFunctions::compare (*this, other);
	}

	/** Compares this string with another one, up to a specified number of characters. */
	template <typename CharPointer>
	int compareUpTo (const CharPointer& other, const int maxChars) const noexcept
	{
		return CharacterFunctions::compareUpTo (*this, other, maxChars);
	}

	/** Compares this string with another one. */
	template <typename CharPointer>
	int compareIgnoreCase (const CharPointer& other) const noexcept
	{
		return CharacterFunctions::compareIgnoreCase (*this, other);
	}

	/** Compares this string with another one. */
	int compareIgnoreCase (const CharPointer_UTF8& other) const noexcept
	{
	   #if JUCE_WINDOWS
		return stricmp (data, other.data);
	   #else
		return strcasecmp (data, other.data);
	   #endif
	}

	/** Compares this string with another one, up to a specified number of characters. */
	template <typename CharPointer>
	int compareIgnoreCaseUpTo (const CharPointer& other, const int maxChars) const noexcept
	{
		return CharacterFunctions::compareIgnoreCaseUpTo (*this, other, maxChars);
	}

	/** Returns the character index of a substring, or -1 if it isn't found. */
	template <typename CharPointer>
	int indexOf (const CharPointer& stringToFind) const noexcept
	{
		return CharacterFunctions::indexOf (*this, stringToFind);
	}

	/** Returns the character index of a unicode character, or -1 if it isn't found. */
	int indexOf (const juce_wchar charToFind) const noexcept
	{
		return CharacterFunctions::indexOfChar (*this, charToFind);
	}

	/** Returns the character index of a unicode character, or -1 if it isn't found. */
	int indexOf (const juce_wchar charToFind, const bool ignoreCase) const noexcept
	{
		return ignoreCase ? CharacterFunctions::indexOfCharIgnoreCase (*this, charToFind)
						  : CharacterFunctions::indexOfChar (*this, charToFind);
	}

	/** Returns true if the first character of this string is whitespace. */
	bool isWhitespace() const noexcept      { return *data == ' ' || (*data <= 13 && *data >= 9); }
	/** Returns true if the first character of this string is a digit. */
	bool isDigit() const noexcept           { return *data >= '0' && *data <= '9'; }
	/** Returns true if the first character of this string is a letter. */
	bool isLetter() const noexcept          { return CharacterFunctions::isLetter (operator*()) != 0; }
	/** Returns true if the first character of this string is a letter or digit. */
	bool isLetterOrDigit() const noexcept   { return CharacterFunctions::isLetterOrDigit (operator*()) != 0; }
	/** Returns true if the first character of this string is upper-case. */
	bool isUpperCase() const noexcept       { return CharacterFunctions::isUpperCase (operator*()) != 0; }
	/** Returns true if the first character of this string is lower-case. */
	bool isLowerCase() const noexcept       { return CharacterFunctions::isLowerCase (operator*()) != 0; }

	/** Returns an upper-case version of the first character of this string. */
	juce_wchar toUpperCase() const noexcept { return CharacterFunctions::toUpperCase (operator*()); }
	/** Returns a lower-case version of the first character of this string. */
	juce_wchar toLowerCase() const noexcept { return CharacterFunctions::toLowerCase (operator*()); }

	/** Parses this string as a 32-bit integer. */
	int getIntValue32() const noexcept      { return atoi (data); }

	/** Parses this string as a 64-bit integer. */
	int64 getIntValue64() const noexcept
	{
	   #if JUCE_LINUX || JUCE_ANDROID
		return atoll (data);
	   #elif JUCE_WINDOWS
		return _atoi64 (data);
	   #else
		return CharacterFunctions::getIntValue <int64, CharPointer_UTF8> (*this);
	   #endif
	}

	/** Parses this string as a floating point double. */
	double getDoubleValue() const noexcept  { return CharacterFunctions::getDoubleValue (*this); }

	/** Returns the first non-whitespace character in the string. */
	CharPointer_UTF8 findEndOfWhitespace() const noexcept   { return CharacterFunctions::findEndOfWhitespace (*this); }

	/** Returns true if the given unicode character can be represented in this encoding. */
	static bool canRepresent (juce_wchar character) noexcept
	{
		return ((unsigned int) character) < (unsigned int) 0x10ffff;
	}

	/** Returns true if this data contains a valid string in this encoding. */
	static bool isValidString (const CharType* dataToTest, int maxBytesToRead)
	{
		while (--maxBytesToRead >= 0 && *dataToTest != 0)
		{
			const signed char byte = (signed char) *dataToTest;

			if (byte < 0)
			{
				uint32 n = (uint32) (uint8) byte;
				uint32 mask = 0x7f;
				uint32 bit = 0x40;
				int numExtraValues = 0;

				while ((n & bit) != 0)
				{
					if (bit <= 0x10)
						return false;

					mask >>= 1;
					++numExtraValues;
					bit >>= 1;
				}

				n &= mask;

				while (--numExtraValues >= 0)
				{
					const uint32 nextByte = (uint32) (uint8) *dataToTest++;

					if ((nextByte & 0xc0) != 0x80)
						return false;
				}
			}
		}

		return true;
	}

	/** Atomically swaps this pointer for a new value, returning the previous value. */
	CharPointer_UTF8 atomicSwap (const CharPointer_UTF8& newValue)
	{
		return CharPointer_UTF8 (reinterpret_cast <Atomic<CharType*>&> (data).exchange (newValue.data));
	}

	/** These values are the byte-order-mark (BOM) values for a UTF-8 stream. */
	enum
	{
		byteOrderMark1 = 0xef,
		byteOrderMark2 = 0xbb,
		byteOrderMark3 = 0xbf
	};

private:
	CharType* data;
};

#endif   // __JUCE_CHARPOINTER_UTF8_JUCEHEADER__

/*** End of inlined file: juce_CharPointer_UTF8.h ***/


/*** Start of inlined file: juce_CharPointer_UTF16.h ***/
#ifndef __JUCE_CHARPOINTER_UTF16_JUCEHEADER__
#define __JUCE_CHARPOINTER_UTF16_JUCEHEADER__

/**
	Wraps a pointer to a null-terminated UTF-16 character string, and provides
	various methods to operate on the data.
	@see CharPointer_UTF8, CharPointer_UTF32
*/
class CharPointer_UTF16
{
public:
   #if JUCE_NATIVE_WCHAR_IS_UTF16
	typedef wchar_t CharType;
   #else
	typedef int16 CharType;
   #endif

	inline explicit CharPointer_UTF16 (const CharType* const rawPointer) noexcept
		: data (const_cast <CharType*> (rawPointer))
	{
	}

	inline CharPointer_UTF16 (const CharPointer_UTF16& other) noexcept
		: data (other.data)
	{
	}

	inline CharPointer_UTF16& operator= (const CharPointer_UTF16& other) noexcept
	{
		data = other.data;
		return *this;
	}

	inline CharPointer_UTF16& operator= (const CharType* text) noexcept
	{
		data = const_cast <CharType*> (text);
		return *this;
	}

	/** This is a pointer comparison, it doesn't compare the actual text. */
	inline bool operator== (const CharPointer_UTF16& other) const noexcept { return data == other.data; }
	inline bool operator!= (const CharPointer_UTF16& other) const noexcept { return data != other.data; }
	inline bool operator<= (const CharPointer_UTF16& other) const noexcept { return data <= other.data; }
	inline bool operator<  (const CharPointer_UTF16& other) const noexcept { return data <  other.data; }
	inline bool operator>= (const CharPointer_UTF16& other) const noexcept { return data >= other.data; }
	inline bool operator>  (const CharPointer_UTF16& other) const noexcept { return data >  other.data; }

	/** Returns the address that this pointer is pointing to. */
	inline CharType* getAddress() const noexcept        { return data; }

	/** Returns the address that this pointer is pointing to. */
	inline operator const CharType*() const noexcept    { return data; }

	/** Returns true if this pointer is pointing to a null character. */
	inline bool isEmpty() const noexcept                { return *data == 0; }

	/** Returns the unicode character that this pointer is pointing to. */
	juce_wchar operator*() const noexcept
	{
		uint32 n = (uint32) (uint16) *data;

		if (n >= 0xd800 && n <= 0xdfff && ((uint32) (uint16) data[1]) >= 0xdc00)
			n = 0x10000 + (((n - 0xd800) << 10) | (((uint32) (uint16) data[1]) - 0xdc00));

		return (juce_wchar) n;
	}

	/** Moves this pointer along to the next character in the string. */
	CharPointer_UTF16& operator++() noexcept
	{
		const juce_wchar n = *data++;

		if (n >= 0xd800 && n <= 0xdfff && ((uint32) (uint16) *data) >= 0xdc00)
			++data;

		return *this;
	}

	/** Moves this pointer back to the previous character in the string. */
	CharPointer_UTF16& operator--() noexcept
	{
		const juce_wchar n = *--data;

		if (n >= 0xdc00 && n <= 0xdfff)
			--data;

		return *this;
	}

	/** Returns the character that this pointer is currently pointing to, and then
		advances the pointer to point to the next character. */
	juce_wchar getAndAdvance() noexcept
	{
		uint32 n = (uint32) (uint16) *data++;

		if (n >= 0xd800 && n <= 0xdfff && ((uint32) (uint16) *data) >= 0xdc00)
			n = 0x10000 + ((((n - 0xd800) << 10) | (((uint32) (uint16) *data++) - 0xdc00)));

		return (juce_wchar) n;
	}

	/** Moves this pointer along to the next character in the string. */
	CharPointer_UTF16 operator++ (int) noexcept
	{
		CharPointer_UTF16 temp (*this);
		++*this;
		return temp;
	}

	/** Moves this pointer forwards by the specified number of characters. */
	void operator+= (int numToSkip) noexcept
	{
		if (numToSkip < 0)
		{
			while (++numToSkip <= 0)
				--*this;
		}
		else
		{
			while (--numToSkip >= 0)
				++*this;
		}
	}

	/** Moves this pointer backwards by the specified number of characters. */
	void operator-= (int numToSkip) noexcept
	{
		operator+= (-numToSkip);
	}

	/** Returns the character at a given character index from the start of the string. */
	juce_wchar operator[] (const int characterIndex) const noexcept
	{
		CharPointer_UTF16 p (*this);
		p += characterIndex;
		return *p;
	}

	/** Returns a pointer which is moved forwards from this one by the specified number of characters. */
	CharPointer_UTF16 operator+ (const int numToSkip) const noexcept
	{
		CharPointer_UTF16 p (*this);
		p += numToSkip;
		return p;
	}

	/** Returns a pointer which is moved backwards from this one by the specified number of characters. */
	CharPointer_UTF16 operator- (const int numToSkip) const noexcept
	{
		CharPointer_UTF16 p (*this);
		p += -numToSkip;
		return p;
	}

	/** Writes a unicode character to this string, and advances this pointer to point to the next position. */
	void write (juce_wchar charToWrite) noexcept
	{
		if (charToWrite >= 0x10000)
		{
			charToWrite -= 0x10000;
			*data++ = (CharType) (0xd800 + (charToWrite >> 10));
			*data++ = (CharType) (0xdc00 + (charToWrite & 0x3ff));
		}
		else
		{
			*data++ = (CharType) charToWrite;
		}
	}

	/** Writes a null character to this string (leaving the pointer's position unchanged). */
	inline void writeNull() const noexcept
	{
		*data = 0;
	}

	/** Returns the number of characters in this string. */
	size_t length() const noexcept
	{
		const CharType* d = data;
		size_t count = 0;

		for (;;)
		{
			const int n = *d++;

			if (n >= 0xd800 && n <= 0xdfff)
			{
				if (*d++ == 0)
					break;
			}
			else if (n == 0)
				break;

			++count;
		}

		return count;
	}

	/** Returns the number of characters in this string, or the given value, whichever is lower. */
	size_t lengthUpTo (const size_t maxCharsToCount) const noexcept
	{
		return CharacterFunctions::lengthUpTo (*this, maxCharsToCount);
	}

	/** Returns the number of characters in this string, or up to the given end pointer, whichever is lower. */
	size_t lengthUpTo (const CharPointer_UTF16& end) const noexcept
	{
		return CharacterFunctions::lengthUpTo (*this, end);
	}

	/** Returns the number of bytes that are used to represent this string.
		This includes the terminating null character.
	*/
	size_t sizeInBytes() const noexcept
	{
		return sizeof (CharType) * (findNullIndex (data) + 1);
	}

	/** Returns the number of bytes that would be needed to represent the given
		unicode character in this encoding format.
	*/
	static size_t getBytesRequiredFor (const juce_wchar charToWrite) noexcept
	{
		return (charToWrite >= 0x10000) ? (sizeof (CharType) * 2) : sizeof (CharType);
	}

	/** Returns the number of bytes that would be needed to represent the given
		string in this encoding format.
		The value returned does NOT include the terminating null character.
	*/
	template <class CharPointer>
	static size_t getBytesRequiredFor (CharPointer text) noexcept
	{
		size_t count = 0;
		juce_wchar n;

		while ((n = text.getAndAdvance()) != 0)
			count += getBytesRequiredFor (n);

		return count;
	}

	/** Returns a pointer to the null character that terminates this string. */
	CharPointer_UTF16 findTerminatingNull() const noexcept
	{
		const CharType* t = data;

		while (*t != 0)
			++t;

		return CharPointer_UTF16 (t);
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes. */
	template <typename CharPointer>
	void writeAll (const CharPointer& src) noexcept
	{
		CharacterFunctions::copyAll (*this, src);
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes. */
	void writeAll (const CharPointer_UTF16& src) noexcept
	{
		const CharType* s = src.data;

		while ((*data = *s) != 0)
		{
			++data;
			++s;
		}
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes.
		The maxDestBytes parameter specifies the maximum number of bytes that can be written
		to the destination buffer before stopping.
	*/
	template <typename CharPointer>
	int writeWithDestByteLimit (const CharPointer& src, const int maxDestBytes) noexcept
	{
		return CharacterFunctions::copyWithDestByteLimit (*this, src, maxDestBytes);
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes.
		The maxChars parameter specifies the maximum number of characters that can be
		written to the destination buffer before stopping (including the terminating null).
	*/
	template <typename CharPointer>
	void writeWithCharLimit (const CharPointer& src, const int maxChars) noexcept
	{
		CharacterFunctions::copyWithCharLimit (*this, src, maxChars);
	}

	/** Compares this string with another one. */
	template <typename CharPointer>
	int compare (const CharPointer& other) const noexcept
	{
		return CharacterFunctions::compare (*this, other);
	}

	/** Compares this string with another one, up to a specified number of characters. */
	template <typename CharPointer>
	int compareUpTo (const CharPointer& other, const int maxChars) const noexcept
	{
		return CharacterFunctions::compareUpTo (*this, other, maxChars);
	}

	/** Compares this string with another one. */
	template <typename CharPointer>
	int compareIgnoreCase (const CharPointer& other) const noexcept
	{
		return CharacterFunctions::compareIgnoreCase (*this, other);
	}

	/** Compares this string with another one, up to a specified number of characters. */
	template <typename CharPointer>
	int compareIgnoreCaseUpTo (const CharPointer& other, const int maxChars) const noexcept
	{
		return CharacterFunctions::compareIgnoreCaseUpTo (*this, other, maxChars);
	}

   #if JUCE_WINDOWS && ! DOXYGEN
	int compareIgnoreCase (const CharPointer_UTF16& other) const noexcept
	{
		return _wcsicmp (data, other.data);
	}

	int compareIgnoreCaseUpTo (const CharPointer_UTF16& other, int maxChars) const noexcept
	{
		return _wcsnicmp (data, other.data, (size_t) maxChars);
	}

	int indexOf (const CharPointer_UTF16& stringToFind) const noexcept
	{
		const CharType* const t = wcsstr (data, stringToFind.getAddress());
		return t == nullptr ? -1 : (int) (t - data);
	}
   #endif

	/** Returns the character index of a substring, or -1 if it isn't found. */
	template <typename CharPointer>
	int indexOf (const CharPointer& stringToFind) const noexcept
	{
		return CharacterFunctions::indexOf (*this, stringToFind);
	}

	/** Returns the character index of a unicode character, or -1 if it isn't found. */
	int indexOf (const juce_wchar charToFind) const noexcept
	{
		return CharacterFunctions::indexOfChar (*this, charToFind);
	}

	/** Returns the character index of a unicode character, or -1 if it isn't found. */
	int indexOf (const juce_wchar charToFind, const bool ignoreCase) const noexcept
	{
		return ignoreCase ? CharacterFunctions::indexOfCharIgnoreCase (*this, charToFind)
						  : CharacterFunctions::indexOfChar (*this, charToFind);
	}

	/** Returns true if the first character of this string is whitespace. */
	bool isWhitespace() const noexcept      { return CharacterFunctions::isWhitespace (operator*()) != 0; }
	/** Returns true if the first character of this string is a digit. */
	bool isDigit() const noexcept           { return CharacterFunctions::isDigit (operator*()) != 0; }
	/** Returns true if the first character of this string is a letter. */
	bool isLetter() const noexcept          { return CharacterFunctions::isLetter (operator*()) != 0; }
	/** Returns true if the first character of this string is a letter or digit. */
	bool isLetterOrDigit() const noexcept   { return CharacterFunctions::isLetterOrDigit (operator*()) != 0; }
	/** Returns true if the first character of this string is upper-case. */
	bool isUpperCase() const noexcept       { return CharacterFunctions::isUpperCase (operator*()) != 0; }
	/** Returns true if the first character of this string is lower-case. */
	bool isLowerCase() const noexcept       { return CharacterFunctions::isLowerCase (operator*()) != 0; }

	/** Returns an upper-case version of the first character of this string. */
	juce_wchar toUpperCase() const noexcept { return CharacterFunctions::toUpperCase (operator*()); }
	/** Returns a lower-case version of the first character of this string. */
	juce_wchar toLowerCase() const noexcept { return CharacterFunctions::toLowerCase (operator*()); }

	/** Parses this string as a 32-bit integer. */
	int getIntValue32() const noexcept
	{
	   #if JUCE_WINDOWS
		return _wtoi (data);
	   #else
		return CharacterFunctions::getIntValue <int, CharPointer_UTF16> (*this);
	   #endif
	}

	/** Parses this string as a 64-bit integer. */
	int64 getIntValue64() const noexcept
	{
	   #if JUCE_WINDOWS
		return _wtoi64 (data);
	   #else
		return CharacterFunctions::getIntValue <int64, CharPointer_UTF16> (*this);
	   #endif
	}

	/** Parses this string as a floating point double. */
	double getDoubleValue() const noexcept  { return CharacterFunctions::getDoubleValue (*this); }

	/** Returns the first non-whitespace character in the string. */
	CharPointer_UTF16 findEndOfWhitespace() const noexcept   { return CharacterFunctions::findEndOfWhitespace (*this); }

	/** Returns true if the given unicode character can be represented in this encoding. */
	static bool canRepresent (juce_wchar character) noexcept
	{
		return ((unsigned int) character) < (unsigned int) 0x10ffff
				 && (((unsigned int) character) < 0xd800 || ((unsigned int) character) > 0xdfff);
	}

	/** Returns true if this data contains a valid string in this encoding. */
	static bool isValidString (const CharType* dataToTest, int maxBytesToRead)
	{
		maxBytesToRead /= sizeof (CharType);

		while (--maxBytesToRead >= 0 && *dataToTest != 0)
		{
			const uint32 n = (uint32) (uint16) *dataToTest++;

			if (n >= 0xd800)
			{
				if (n > 0x10ffff)
					return false;

				if (n <= 0xdfff)
				{
					if (n > 0xdc00)
						return false;

					const uint32 nextChar = (uint32) (uint16) *dataToTest++;

					if (nextChar < 0xdc00 || nextChar > 0xdfff)
						return false;
				}
			}
		}

		return true;
	}

	/** Atomically swaps this pointer for a new value, returning the previous value. */
	CharPointer_UTF16 atomicSwap (const CharPointer_UTF16& newValue)
	{
		return CharPointer_UTF16 (reinterpret_cast <Atomic<CharType*>&> (data).exchange (newValue.data));
	}

	/** These values are the byte-order-mark (BOM) values for a UTF-16 stream. */
	enum
	{
		byteOrderMarkBE1 = 0xfe,
		byteOrderMarkBE2 = 0xff,
		byteOrderMarkLE1 = 0xff,
		byteOrderMarkLE2 = 0xfe
	};

private:
	CharType* data;

	static int findNullIndex (const CharType* const t) noexcept
	{
		int n = 0;

		while (t[n] != 0)
			++n;

		return n;
	}
};

#endif   // __JUCE_CHARPOINTER_UTF16_JUCEHEADER__

/*** End of inlined file: juce_CharPointer_UTF16.h ***/


/*** Start of inlined file: juce_CharPointer_UTF32.h ***/
#ifndef __JUCE_CHARPOINTER_UTF32_JUCEHEADER__
#define __JUCE_CHARPOINTER_UTF32_JUCEHEADER__

/**
	Wraps a pointer to a null-terminated UTF-32 character string, and provides
	various methods to operate on the data.
	@see CharPointer_UTF8, CharPointer_UTF16
*/
class CharPointer_UTF32
{
public:
	typedef juce_wchar CharType;

	inline explicit CharPointer_UTF32 (const CharType* const rawPointer) noexcept
		: data (const_cast <CharType*> (rawPointer))
	{
	}

	inline CharPointer_UTF32 (const CharPointer_UTF32& other) noexcept
		: data (other.data)
	{
	}

	inline CharPointer_UTF32& operator= (const CharPointer_UTF32& other) noexcept
	{
		data = other.data;
		return *this;
	}

	inline CharPointer_UTF32& operator= (const CharType* text) noexcept
	{
		data = const_cast <CharType*> (text);
		return *this;
	}

	/** This is a pointer comparison, it doesn't compare the actual text. */
	inline bool operator== (const CharPointer_UTF32& other) const noexcept { return data == other.data; }
	inline bool operator!= (const CharPointer_UTF32& other) const noexcept { return data != other.data; }
	inline bool operator<= (const CharPointer_UTF32& other) const noexcept { return data <= other.data; }
	inline bool operator<  (const CharPointer_UTF32& other) const noexcept { return data <  other.data; }
	inline bool operator>= (const CharPointer_UTF32& other) const noexcept { return data >= other.data; }
	inline bool operator>  (const CharPointer_UTF32& other) const noexcept { return data >  other.data; }

	/** Returns the address that this pointer is pointing to. */
	inline CharType* getAddress() const noexcept        { return data; }

	/** Returns the address that this pointer is pointing to. */
	inline operator const CharType*() const noexcept    { return data; }

	/** Returns true if this pointer is pointing to a null character. */
	inline bool isEmpty() const noexcept                { return *data == 0; }

	/** Returns the unicode character that this pointer is pointing to. */
	inline juce_wchar operator*() const noexcept        { return *data; }

	/** Moves this pointer along to the next character in the string. */
	inline CharPointer_UTF32& operator++() noexcept
	{
		++data;
		return *this;
	}

	/** Moves this pointer to the previous character in the string. */
	inline CharPointer_UTF32& operator--() noexcept
	{
		--data;
		return *this;
	}

	/** Returns the character that this pointer is currently pointing to, and then
		advances the pointer to point to the next character. */
	inline juce_wchar getAndAdvance() noexcept  { return *data++; }

	/** Moves this pointer along to the next character in the string. */
	CharPointer_UTF32 operator++ (int) noexcept
	{
		CharPointer_UTF32 temp (*this);
		++data;
		return temp;
	}

	/** Moves this pointer forwards by the specified number of characters. */
	inline void operator+= (const int numToSkip) noexcept
	{
		data += numToSkip;
	}

	inline void operator-= (const int numToSkip) noexcept
	{
		data -= numToSkip;
	}

	/** Returns the character at a given character index from the start of the string. */
	inline juce_wchar& operator[] (const int characterIndex) const noexcept
	{
		return data [characterIndex];
	}

	/** Returns a pointer which is moved forwards from this one by the specified number of characters. */
	CharPointer_UTF32 operator+ (const int numToSkip) const noexcept
	{
		return CharPointer_UTF32 (data + numToSkip);
	}

	/** Returns a pointer which is moved backwards from this one by the specified number of characters. */
	CharPointer_UTF32 operator- (const int numToSkip) const noexcept
	{
		return CharPointer_UTF32 (data - numToSkip);
	}

	/** Writes a unicode character to this string, and advances this pointer to point to the next position. */
	inline void write (const juce_wchar charToWrite) noexcept
	{
		*data++ = charToWrite;
	}

	inline void replaceChar (const juce_wchar newChar) noexcept
	{
		*data = newChar;
	}

	/** Writes a null character to this string (leaving the pointer's position unchanged). */
	inline void writeNull() const noexcept
	{
		*data = 0;
	}

	/** Returns the number of characters in this string. */
	size_t length() const noexcept
	{
	   #if JUCE_NATIVE_WCHAR_IS_UTF32 && ! JUCE_ANDROID
		return wcslen (data);
	   #else
		size_t n = 0;
		while (data[n] != 0)
			++n;
		return n;
	   #endif
	}

	/** Returns the number of characters in this string, or the given value, whichever is lower. */
	size_t lengthUpTo (const size_t maxCharsToCount) const noexcept
	{
		return CharacterFunctions::lengthUpTo (*this, maxCharsToCount);
	}

	/** Returns the number of characters in this string, or up to the given end pointer, whichever is lower. */
	size_t lengthUpTo (const CharPointer_UTF32& end) const noexcept
	{
		return CharacterFunctions::lengthUpTo (*this, end);
	}

	/** Returns the number of bytes that are used to represent this string.
		This includes the terminating null character.
	*/
	size_t sizeInBytes() const noexcept
	{
		return sizeof (CharType) * (length() + 1);
	}

	/** Returns the number of bytes that would be needed to represent the given
		unicode character in this encoding format.
	*/
	static inline size_t getBytesRequiredFor (const juce_wchar) noexcept
	{
		return sizeof (CharType);
	}

	/** Returns the number of bytes that would be needed to represent the given
		string in this encoding format.
		The value returned does NOT include the terminating null character.
	*/
	template <class CharPointer>
	static size_t getBytesRequiredFor (const CharPointer& text) noexcept
	{
		return sizeof (CharType) * text.length();
	}

	/** Returns a pointer to the null character that terminates this string. */
	CharPointer_UTF32 findTerminatingNull() const noexcept
	{
		return CharPointer_UTF32 (data + length());
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes. */
	template <typename CharPointer>
	void writeAll (const CharPointer& src) noexcept
	{
		CharacterFunctions::copyAll (*this, src);
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes. */
	void writeAll (const CharPointer_UTF32& src) noexcept
	{
		const CharType* s = src.data;

		while ((*data = *s) != 0)
		{
			++data;
			++s;
		}
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes.
		The maxDestBytes parameter specifies the maximum number of bytes that can be written
		to the destination buffer before stopping.
	*/
	template <typename CharPointer>
	int writeWithDestByteLimit (const CharPointer& src, const int maxDestBytes) noexcept
	{
		return CharacterFunctions::copyWithDestByteLimit (*this, src, maxDestBytes);
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes.
		The maxChars parameter specifies the maximum number of characters that can be
		written to the destination buffer before stopping (including the terminating null).
	*/
	template <typename CharPointer>
	void writeWithCharLimit (const CharPointer& src, const int maxChars) noexcept
	{
		CharacterFunctions::copyWithCharLimit (*this, src, maxChars);
	}

	/** Compares this string with another one. */
	template <typename CharPointer>
	int compare (const CharPointer& other) const noexcept
	{
		return CharacterFunctions::compare (*this, other);
	}

   #if JUCE_NATIVE_WCHAR_IS_UTF32 && ! JUCE_ANDROID
	/** Compares this string with another one. */
	int compare (const CharPointer_UTF32& other) const noexcept
	{
		return wcscmp (data, other.data);
	}
   #endif

	/** Compares this string with another one, up to a specified number of characters. */
	template <typename CharPointer>
	int compareUpTo (const CharPointer& other, const int maxChars) const noexcept
	{
		return CharacterFunctions::compareUpTo (*this, other, maxChars);
	}

	/** Compares this string with another one. */
	template <typename CharPointer>
	int compareIgnoreCase (const CharPointer& other) const
	{
		return CharacterFunctions::compareIgnoreCase (*this, other);
	}

	/** Compares this string with another one, up to a specified number of characters. */
	template <typename CharPointer>
	int compareIgnoreCaseUpTo (const CharPointer& other, const int maxChars) const noexcept
	{
		return CharacterFunctions::compareIgnoreCaseUpTo (*this, other, maxChars);
	}

	/** Returns the character index of a substring, or -1 if it isn't found. */
	template <typename CharPointer>
	int indexOf (const CharPointer& stringToFind) const noexcept
	{
		return CharacterFunctions::indexOf (*this, stringToFind);
	}

	/** Returns the character index of a unicode character, or -1 if it isn't found. */
	int indexOf (const juce_wchar charToFind) const noexcept
	{
		int i = 0;

		while (data[i] != 0)
		{
			if (data[i] == charToFind)
				return i;

			++i;
		}

		return -1;
	}

	/** Returns the character index of a unicode character, or -1 if it isn't found. */
	int indexOf (const juce_wchar charToFind, const bool ignoreCase) const noexcept
	{
		return ignoreCase ? CharacterFunctions::indexOfCharIgnoreCase (*this, charToFind)
						  : CharacterFunctions::indexOfChar (*this, charToFind);
	}

	/** Returns true if the first character of this string is whitespace. */
	bool isWhitespace() const               { return CharacterFunctions::isWhitespace (*data) != 0; }
	/** Returns true if the first character of this string is a digit. */
	bool isDigit() const                    { return CharacterFunctions::isDigit (*data) != 0; }
	/** Returns true if the first character of this string is a letter. */
	bool isLetter() const                   { return CharacterFunctions::isLetter (*data) != 0; }
	/** Returns true if the first character of this string is a letter or digit. */
	bool isLetterOrDigit() const            { return CharacterFunctions::isLetterOrDigit (*data) != 0; }
	/** Returns true if the first character of this string is upper-case. */
	bool isUpperCase() const                { return CharacterFunctions::isUpperCase (*data) != 0; }
	/** Returns true if the first character of this string is lower-case. */
	bool isLowerCase() const                { return CharacterFunctions::isLowerCase (*data) != 0; }

	/** Returns an upper-case version of the first character of this string. */
	juce_wchar toUpperCase() const noexcept { return CharacterFunctions::toUpperCase (*data); }
	/** Returns a lower-case version of the first character of this string. */
	juce_wchar toLowerCase() const noexcept { return CharacterFunctions::toLowerCase (*data); }

	/** Parses this string as a 32-bit integer. */
	int getIntValue32() const noexcept      { return CharacterFunctions::getIntValue <int, CharPointer_UTF32> (*this); }
	/** Parses this string as a 64-bit integer. */
	int64 getIntValue64() const noexcept    { return CharacterFunctions::getIntValue <int64, CharPointer_UTF32> (*this); }

	/** Parses this string as a floating point double. */
	double getDoubleValue() const noexcept  { return CharacterFunctions::getDoubleValue (*this); }

	/** Returns the first non-whitespace character in the string. */
	CharPointer_UTF32 findEndOfWhitespace() const noexcept   { return CharacterFunctions::findEndOfWhitespace (*this); }

	/** Returns true if the given unicode character can be represented in this encoding. */
	static bool canRepresent (juce_wchar character) noexcept
	{
		return ((unsigned int) character) < (unsigned int) 0x10ffff;
	}

	/** Returns true if this data contains a valid string in this encoding. */
	static bool isValidString (const CharType* dataToTest, int maxBytesToRead)
	{
		maxBytesToRead /= sizeof (CharType);

		while (--maxBytesToRead >= 0 && *dataToTest != 0)
			if (! canRepresent (*dataToTest++))
				return false;

		return true;
	}

	/** Atomically swaps this pointer for a new value, returning the previous value. */
	CharPointer_UTF32 atomicSwap (const CharPointer_UTF32& newValue)
	{
		return CharPointer_UTF32 (reinterpret_cast <Atomic<CharType*>&> (data).exchange (newValue.data));
	}

private:
	CharType* data;
};

#endif   // __JUCE_CHARPOINTER_UTF32_JUCEHEADER__

/*** End of inlined file: juce_CharPointer_UTF32.h ***/


/*** Start of inlined file: juce_CharPointer_ASCII.h ***/
#ifndef __JUCE_CHARPOINTER_ASCII_JUCEHEADER__
#define __JUCE_CHARPOINTER_ASCII_JUCEHEADER__

/**
	Wraps a pointer to a null-terminated ASCII character string, and provides
	various methods to operate on the data.

	A valid ASCII string is assumed to not contain any characters above 127.

	@see CharPointer_UTF8, CharPointer_UTF16, CharPointer_UTF32
*/
class CharPointer_ASCII
{
public:
	typedef char CharType;

	inline explicit CharPointer_ASCII (const CharType* const rawPointer) noexcept
		: data (const_cast <CharType*> (rawPointer))
	{
	}

	inline CharPointer_ASCII (const CharPointer_ASCII& other) noexcept
		: data (other.data)
	{
	}

	inline CharPointer_ASCII& operator= (const CharPointer_ASCII& other) noexcept
	{
		data = other.data;
		return *this;
	}

	inline CharPointer_ASCII& operator= (const CharType* text) noexcept
	{
		data = const_cast <CharType*> (text);
		return *this;
	}

	/** This is a pointer comparison, it doesn't compare the actual text. */
	inline bool operator== (const CharPointer_ASCII& other) const noexcept { return data == other.data; }
	inline bool operator!= (const CharPointer_ASCII& other) const noexcept { return data != other.data; }
	inline bool operator<= (const CharPointer_ASCII& other) const noexcept { return data <= other.data; }
	inline bool operator<  (const CharPointer_ASCII& other) const noexcept { return data <  other.data; }
	inline bool operator>= (const CharPointer_ASCII& other) const noexcept { return data >= other.data; }
	inline bool operator>  (const CharPointer_ASCII& other) const noexcept { return data >  other.data; }

	/** Returns the address that this pointer is pointing to. */
	inline CharType* getAddress() const noexcept        { return data; }

	/** Returns the address that this pointer is pointing to. */
	inline operator const CharType*() const noexcept    { return data; }

	/** Returns true if this pointer is pointing to a null character. */
	inline bool isEmpty() const noexcept                { return *data == 0; }

	/** Returns the unicode character that this pointer is pointing to. */
	inline juce_wchar operator*() const noexcept        { return (juce_wchar) (uint8) *data; }

	/** Moves this pointer along to the next character in the string. */
	inline CharPointer_ASCII& operator++() noexcept
	{
		++data;
		return *this;
	}

	/** Moves this pointer to the previous character in the string. */
	inline CharPointer_ASCII& operator--() noexcept
	{
		--data;
		return *this;
	}

	/** Returns the character that this pointer is currently pointing to, and then
		advances the pointer to point to the next character. */
	inline juce_wchar getAndAdvance() noexcept  { return (juce_wchar) (uint8) *data++; }

	/** Moves this pointer along to the next character in the string. */
	CharPointer_ASCII operator++ (int) noexcept
	{
		CharPointer_ASCII temp (*this);
		++data;
		return temp;
	}

	/** Moves this pointer forwards by the specified number of characters. */
	inline void operator+= (const int numToSkip) noexcept
	{
		data += numToSkip;
	}

	inline void operator-= (const int numToSkip) noexcept
	{
		data -= numToSkip;
	}

	/** Returns the character at a given character index from the start of the string. */
	inline juce_wchar operator[] (const int characterIndex) const noexcept
	{
		return (juce_wchar) (unsigned char) data [characterIndex];
	}

	/** Returns a pointer which is moved forwards from this one by the specified number of characters. */
	CharPointer_ASCII operator+ (const int numToSkip) const noexcept
	{
		return CharPointer_ASCII (data + numToSkip);
	}

	/** Returns a pointer which is moved backwards from this one by the specified number of characters. */
	CharPointer_ASCII operator- (const int numToSkip) const noexcept
	{
		return CharPointer_ASCII (data - numToSkip);
	}

	/** Writes a unicode character to this string, and advances this pointer to point to the next position. */
	inline void write (const juce_wchar charToWrite) noexcept
	{
		*data++ = (char) charToWrite;
	}

	inline void replaceChar (const juce_wchar newChar) noexcept
	{
		*data = (char) newChar;
	}

	/** Writes a null character to this string (leaving the pointer's position unchanged). */
	inline void writeNull() const noexcept
	{
		*data = 0;
	}

	/** Returns the number of characters in this string. */
	size_t length() const noexcept
	{
		return (size_t) strlen (data);
	}

	/** Returns the number of characters in this string, or the given value, whichever is lower. */
	size_t lengthUpTo (const size_t maxCharsToCount) const noexcept
	{
		return CharacterFunctions::lengthUpTo (*this, maxCharsToCount);
	}

	/** Returns the number of characters in this string, or up to the given end pointer, whichever is lower. */
	size_t lengthUpTo (const CharPointer_ASCII& end) const noexcept
	{
		return CharacterFunctions::lengthUpTo (*this, end);
	}

	/** Returns the number of bytes that are used to represent this string.
		This includes the terminating null character.
	*/
	size_t sizeInBytes() const noexcept
	{
		return length() + 1;
	}

	/** Returns the number of bytes that would be needed to represent the given
		unicode character in this encoding format.
	*/
	static inline size_t getBytesRequiredFor (const juce_wchar) noexcept
	{
		return 1;
	}

	/** Returns the number of bytes that would be needed to represent the given
		string in this encoding format.
		The value returned does NOT include the terminating null character.
	*/
	template <class CharPointer>
	static size_t getBytesRequiredFor (const CharPointer& text) noexcept
	{
		return text.length();
	}

	/** Returns a pointer to the null character that terminates this string. */
	CharPointer_ASCII findTerminatingNull() const noexcept
	{
		return CharPointer_ASCII (data + length());
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes. */
	template <typename CharPointer>
	void writeAll (const CharPointer& src) noexcept
	{
		CharacterFunctions::copyAll (*this, src);
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes. */
	void writeAll (const CharPointer_ASCII& src) noexcept
	{
		strcpy (data, src.data);
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes.
		The maxDestBytes parameter specifies the maximum number of bytes that can be written
		to the destination buffer before stopping.
	*/
	template <typename CharPointer>
	int writeWithDestByteLimit (const CharPointer& src, const int maxDestBytes) noexcept
	{
		return CharacterFunctions::copyWithDestByteLimit (*this, src, maxDestBytes);
	}

	/** Copies a source string to this pointer, advancing this pointer as it goes.
		The maxChars parameter specifies the maximum number of characters that can be
		written to the destination buffer before stopping (including the terminating null).
	*/
	template <typename CharPointer>
	void writeWithCharLimit (const CharPointer& src, const int maxChars) noexcept
	{
		CharacterFunctions::copyWithCharLimit (*this, src, maxChars);
	}

	/** Compares this string with another one. */
	template <typename CharPointer>
	int compare (const CharPointer& other) const noexcept
	{
		return CharacterFunctions::compare (*this, other);
	}

	/** Compares this string with another one. */
	int compare (const CharPointer_ASCII& other) const noexcept
	{
		return strcmp (data, other.data);
	}

	/** Compares this string with another one, up to a specified number of characters. */
	template <typename CharPointer>
	int compareUpTo (const CharPointer& other, const int maxChars) const noexcept
	{
		return CharacterFunctions::compareUpTo (*this, other, maxChars);
	}

	/** Compares this string with another one, up to a specified number of characters. */
	int compareUpTo (const CharPointer_ASCII& other, const int maxChars) const noexcept
	{
		return strncmp (data, other.data, (size_t) maxChars);
	}

	/** Compares this string with another one. */
	template <typename CharPointer>
	int compareIgnoreCase (const CharPointer& other) const
	{
		return CharacterFunctions::compareIgnoreCase (*this, other);
	}

	int compareIgnoreCase (const CharPointer_ASCII& other) const
	{
	   #if JUCE_WINDOWS
		return stricmp (data, other.data);
	   #else
		return strcasecmp (data, other.data);
	   #endif
	}

	/** Compares this string with another one, up to a specified number of characters. */
	template <typename CharPointer>
	int compareIgnoreCaseUpTo (const CharPointer& other, const int maxChars) const noexcept
	{
		return CharacterFunctions::compareIgnoreCaseUpTo (*this, other, maxChars);
	}

	/** Returns the character index of a substring, or -1 if it isn't found. */
	template <typename CharPointer>
	int indexOf (const CharPointer& stringToFind) const noexcept
	{
		return CharacterFunctions::indexOf (*this, stringToFind);
	}

	/** Returns the character index of a unicode character, or -1 if it isn't found. */
	int indexOf (const juce_wchar charToFind) const noexcept
	{
		int i = 0;

		while (data[i] != 0)
		{
			if (data[i] == (char) charToFind)
				return i;

			++i;
		}

		return -1;
	}

	/** Returns the character index of a unicode character, or -1 if it isn't found. */
	int indexOf (const juce_wchar charToFind, const bool ignoreCase) const noexcept
	{
		return ignoreCase ? CharacterFunctions::indexOfCharIgnoreCase (*this, charToFind)
						  : CharacterFunctions::indexOfChar (*this, charToFind);
	}

	/** Returns true if the first character of this string is whitespace. */
	bool isWhitespace() const               { return CharacterFunctions::isWhitespace (*data) != 0; }
	/** Returns true if the first character of this string is a digit. */
	bool isDigit() const                    { return CharacterFunctions::isDigit (*data) != 0; }
	/** Returns true if the first character of this string is a letter. */
	bool isLetter() const                   { return CharacterFunctions::isLetter (*data) != 0; }
	/** Returns true if the first character of this string is a letter or digit. */
	bool isLetterOrDigit() const            { return CharacterFunctions::isLetterOrDigit (*data) != 0; }
	/** Returns true if the first character of this string is upper-case. */
	bool isUpperCase() const                { return CharacterFunctions::isUpperCase ((juce_wchar) (uint8) *data) != 0; }
	/** Returns true if the first character of this string is lower-case. */
	bool isLowerCase() const                { return CharacterFunctions::isLowerCase ((juce_wchar) (uint8) *data) != 0; }

	/** Returns an upper-case version of the first character of this string. */
	juce_wchar toUpperCase() const noexcept { return CharacterFunctions::toUpperCase ((juce_wchar) (uint8) *data); }
	/** Returns a lower-case version of the first character of this string. */
	juce_wchar toLowerCase() const noexcept { return CharacterFunctions::toLowerCase ((juce_wchar) (uint8) *data); }

	/** Parses this string as a 32-bit integer. */
	int getIntValue32() const noexcept      { return atoi (data); }

	/** Parses this string as a 64-bit integer. */
	int64 getIntValue64() const noexcept
	{
	   #if JUCE_LINUX || JUCE_ANDROID
		return atoll (data);
	   #elif JUCE_WINDOWS
		return _atoi64 (data);
	   #else
		return CharacterFunctions::getIntValue <int64, CharPointer_ASCII> (*this);
	   #endif
	}

	/** Parses this string as a floating point double. */
	double getDoubleValue() const noexcept  { return CharacterFunctions::getDoubleValue (*this); }

	/** Returns the first non-whitespace character in the string. */
	CharPointer_ASCII findEndOfWhitespace() const noexcept   { return CharacterFunctions::findEndOfWhitespace (*this); }

	/** Returns true if the given unicode character can be represented in this encoding. */
	static bool canRepresent (juce_wchar character) noexcept
	{
		return ((unsigned int) character) < (unsigned int) 128;
	}

	/** Returns true if this data contains a valid string in this encoding. */
	static bool isValidString (const CharType* dataToTest, int maxBytesToRead)
	{
		while (--maxBytesToRead >= 0)
		{
			if (((signed char) *dataToTest) <= 0)
				return *dataToTest == 0;

			++dataToTest;
		}

		return true;
	}

private:
	CharType* data;
};

#endif   // __JUCE_CHARPOINTER_ASCII_JUCEHEADER__

/*** End of inlined file: juce_CharPointer_ASCII.h ***/

#if JUCE_MSVC
 #pragma warning (pop)
#endif

class OutputStream;

/**
	The JUCE String class!

	Using a reference-counted internal representation, these strings are fast
	and efficient, and there are methods to do just about any operation you'll ever
	dream of.

	@see StringArray, StringPairArray
*/
class JUCE_API  String
{
public:

	/** Creates an empty string.
		@see empty
	*/
	String() noexcept;

	/** Creates a copy of another string. */
	String (const String& other) noexcept;

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	String (String&& other) noexcept;
   #endif

	/** Creates a string from a zero-terminated ascii text string.

		The string passed-in must not contain any characters with a value above 127, because
		these can't be converted to unicode without knowing the original encoding that was
		used to create the string. If you attempt to pass-in values above 127, you'll get an
		assertion.

		To create strings with extended characters from UTF-8, you should explicitly call
		String (CharPointer_UTF8 ("my utf8 string..")). It's *highly* recommended that you
		use UTF-8 with escape characters in your source code to represent extended characters,
		because there's no other way to represent unicode strings in a way that isn't dependent
		on the compiler, source code editor and platform.
	*/
	String (const char* text);

	/** Creates a string from a string of 8-bit ascii characters.

		The string passed-in must not contain any characters with a value above 127, because
		these can't be converted to unicode without knowing the original encoding that was
		used to create the string. If you attempt to pass-in values above 127, you'll get an
		assertion.

		To create strings with extended characters from UTF-8, you should explicitly call
		String (CharPointer_UTF8 ("my utf8 string..")). It's *highly* recommended that you
		use UTF-8 with escape characters in your source code to represent extended characters,
		because there's no other way to represent unicode strings in a way that isn't dependent
		on the compiler, source code editor and platform.

		This will use up the the first maxChars characters of the string (or less if the string
		is actually shorter).
	*/
	String (const char* text, size_t maxChars);

	/** Creates a string from a whcar_t character string.
		Depending on the platform, this may be treated as either UTF-32 or UTF-16.
	*/
	String (const wchar_t* text);

	/** Creates a string from a whcar_t character string.
		Depending on the platform, this may be treated as either UTF-32 or UTF-16.
	*/
	String (const wchar_t* text, size_t maxChars);

	/** Creates a string from a UTF-8 character string */
	String (const CharPointer_UTF8& text);

	/** Creates a string from a UTF-8 character string */
	String (const CharPointer_UTF8& text, size_t maxChars);

	/** Creates a string from a UTF-8 character string */
	String (const CharPointer_UTF8& start, const CharPointer_UTF8& end);

	/** Creates a string from a UTF-16 character string */
	String (const CharPointer_UTF16& text);

	/** Creates a string from a UTF-16 character string */
	String (const CharPointer_UTF16& text, size_t maxChars);

	/** Creates a string from a UTF-16 character string */
	String (const CharPointer_UTF16& start, const CharPointer_UTF16& end);

	/** Creates a string from a UTF-32 character string */
	String (const CharPointer_UTF32& text);

	/** Creates a string from a UTF-32 character string */
	String (const CharPointer_UTF32& text, size_t maxChars);

	/** Creates a string from a UTF-32 character string */
	String (const CharPointer_UTF32& start, const CharPointer_UTF32& end);

	/** Creates a string from an ASCII character string */
	String (const CharPointer_ASCII& text);

	/** Creates a string from a single character. */
	static String charToString (juce_wchar character);

	/** Destructor. */
	~String() noexcept;

	/** This is an empty string that can be used whenever one is needed.

		It's better to use this than String() because it explains what's going on
		and is more efficient.
	*/
	static const String empty;

	/** This is the character encoding type used internally to store the string.

		By setting the value of JUCE_STRING_UTF_TYPE to 8, 16, or 32, you can change the
		internal storage format of the String class. UTF-8 uses the least space (if your strings
		contain few extended characters), but call operator[] involves iterating the string to find
		the required index. UTF-32 provides instant random access to its characters, but uses 4 bytes
		per character to store them. UTF-16 uses more space than UTF-8 and is also slow to index,
		but is the native wchar_t format used in Windows.

		It doesn't matter too much which format you pick, because the toUTF8(), toUTF16() and
		toUTF32() methods let you access the string's content in any of the other formats.
	*/
   #if (JUCE_STRING_UTF_TYPE == 32)
	typedef CharPointer_UTF32 CharPointerType;
   #elif (JUCE_STRING_UTF_TYPE == 16)
	typedef CharPointer_UTF16 CharPointerType;
   #elif (JUCE_STRING_UTF_TYPE == 8)
	typedef CharPointer_UTF8  CharPointerType;
   #else
	#error "You must set the value of JUCE_STRING_UTF_TYPE to be either 8, 16, or 32!"
   #endif

	/** Generates a probably-unique 32-bit hashcode from this string. */
	int hashCode() const noexcept;

	/** Generates a probably-unique 64-bit hashcode from this string. */
	int64 hashCode64() const noexcept;

	/** Returns the number of characters in the string. */
	int length() const noexcept;

	// Assignment and concatenation operators..

	/** Replaces this string's contents with another string. */
	String& operator= (const String& other) noexcept;

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	String& operator= (String&& other) noexcept;
   #endif

	/** Appends another string at the end of this one. */
	String& operator+= (const String& stringToAppend);
	/** Appends another string at the end of this one. */
	String& operator+= (const char* textToAppend);
	/** Appends another string at the end of this one. */
	String& operator+= (const wchar_t* textToAppend);
	/** Appends a decimal number at the end of this string. */
	String& operator+= (int numberToAppend);
	/** Appends a character at the end of this string. */
	String& operator+= (char characterToAppend);
	/** Appends a character at the end of this string. */
	String& operator+= (wchar_t characterToAppend);
   #if ! JUCE_NATIVE_WCHAR_IS_UTF32
	/** Appends a character at the end of this string. */
	String& operator+= (juce_wchar characterToAppend);
   #endif

	/** Appends a string to the end of this one.

		@param textToAppend     the string to add
		@param maxCharsToTake   the maximum number of characters to take from the string passed in
	*/
	void append (const String& textToAppend, size_t maxCharsToTake);

	/** Appends a string to the end of this one.

		@param textToAppend     the string to add
		@param maxCharsToTake   the maximum number of characters to take from the string passed in
	*/
	template <class CharPointer>
	void appendCharPointer (const CharPointer& textToAppend, size_t maxCharsToTake)
	{
		if (textToAppend.getAddress() != nullptr)
		{
			size_t extraBytesNeeded = 0;
			size_t numChars = 0;

			for (CharPointer t (textToAppend); numChars < maxCharsToTake && ! t.isEmpty();)
			{
				extraBytesNeeded += CharPointerType::getBytesRequiredFor (t.getAndAdvance());
				++numChars;
			}

			if (numChars > 0)
			{
				const size_t byteOffsetOfNull = getByteOffsetOfEnd();

				preallocateBytes (byteOffsetOfNull + extraBytesNeeded);
				CharPointerType (addBytesToPointer (text.getAddress(), (int) byteOffsetOfNull)).writeWithCharLimit (textToAppend, (int) (numChars + 1));
			}
		}
	}

	/** Appends a string to the end of this one. */
	template <class CharPointer>
	void appendCharPointer (const CharPointer& textToAppend)
	{
		if (textToAppend.getAddress() != nullptr)
		{
			size_t extraBytesNeeded = 0;

			for (CharPointer t (textToAppend); ! t.isEmpty();)
				extraBytesNeeded += CharPointerType::getBytesRequiredFor (t.getAndAdvance());

			if (extraBytesNeeded > 0)
			{
				const size_t byteOffsetOfNull = getByteOffsetOfEnd();

				preallocateBytes (byteOffsetOfNull + extraBytesNeeded);
				CharPointerType (addBytesToPointer (text.getAddress(), (int) byteOffsetOfNull)).writeAll (textToAppend);
			}
		}
	}

	// Comparison methods..

	/** Returns true if the string contains no characters.
		Note that there's also an isNotEmpty() method to help write readable code.
		@see containsNonWhitespaceChars()
	*/
	inline bool isEmpty() const noexcept                    { return text[0] == 0; }

	/** Returns true if the string contains at least one character.
		Note that there's also an isEmpty() method to help write readable code.
		@see containsNonWhitespaceChars()
	*/
	inline bool isNotEmpty() const noexcept                 { return text[0] != 0; }

	/** Case-insensitive comparison with another string. */
	bool equalsIgnoreCase (const String& other) const noexcept;

	/** Case-insensitive comparison with another string. */
	bool equalsIgnoreCase (const wchar_t* other) const noexcept;

	/** Case-insensitive comparison with another string. */
	bool equalsIgnoreCase (const char* other) const noexcept;

	/** Case-sensitive comparison with another string.
		@returns     0 if the two strings are identical; negative if this string comes before
					 the other one alphabetically, or positive if it comes after it.
	*/
	int compare (const String& other) const noexcept;

	/** Case-sensitive comparison with another string.
		@returns     0 if the two strings are identical; negative if this string comes before
					 the other one alphabetically, or positive if it comes after it.
	*/
	int compare (const char* other) const noexcept;

	/** Case-sensitive comparison with another string.
		@returns     0 if the two strings are identical; negative if this string comes before
					 the other one alphabetically, or positive if it comes after it.
	*/
	int compare (const wchar_t* other) const noexcept;

	/** Case-insensitive comparison with another string.
		@returns     0 if the two strings are identical; negative if this string comes before
					 the other one alphabetically, or positive if it comes after it.
	*/
	int compareIgnoreCase (const String& other) const noexcept;

	/** Lexicographic comparison with another string.

		The comparison used here is case-insensitive and ignores leading non-alphanumeric
		characters, making it good for sorting human-readable strings.

		@returns     0 if the two strings are identical; negative if this string comes before
					 the other one alphabetically, or positive if it comes after it.
	*/
	int compareLexicographically (const String& other) const noexcept;

	/** Tests whether the string begins with another string.
		If the parameter is an empty string, this will always return true.
		Uses a case-sensitive comparison.
	*/
	bool startsWith (const String& text) const noexcept;

	/** Tests whether the string begins with a particular character.
		If the character is 0, this will always return false.
		Uses a case-sensitive comparison.
	*/
	bool startsWithChar (juce_wchar character) const noexcept;

	/** Tests whether the string begins with another string.
		If the parameter is an empty string, this will always return true.
		Uses a case-insensitive comparison.
	*/
	bool startsWithIgnoreCase (const String& text) const noexcept;

	/** Tests whether the string ends with another string.
		If the parameter is an empty string, this will always return true.
		Uses a case-sensitive comparison.
	*/
	bool endsWith (const String& text) const noexcept;

	/** Tests whether the string ends with a particular character.
		If the character is 0, this will always return false.
		Uses a case-sensitive comparison.
	*/
	bool endsWithChar (juce_wchar character) const noexcept;

	/** Tests whether the string ends with another string.
		If the parameter is an empty string, this will always return true.
		Uses a case-insensitive comparison.
	*/
	bool endsWithIgnoreCase (const String& text) const noexcept;

	/** Tests whether the string contains another substring.
		If the parameter is an empty string, this will always return true.
		Uses a case-sensitive comparison.
	*/
	bool contains (const String& text) const noexcept;

	/** Tests whether the string contains a particular character.
		Uses a case-sensitive comparison.
	*/
	bool containsChar (juce_wchar character) const noexcept;

	/** Tests whether the string contains another substring.
		Uses a case-insensitive comparison.
	*/
	bool containsIgnoreCase (const String& text) const noexcept;

	/** Tests whether the string contains another substring as a distict word.

		@returns    true if the string contains this word, surrounded by
					non-alphanumeric characters
		@see indexOfWholeWord, containsWholeWordIgnoreCase
	*/
	bool containsWholeWord (const String& wordToLookFor) const noexcept;

	/** Tests whether the string contains another substring as a distict word.

		@returns    true if the string contains this word, surrounded by
					non-alphanumeric characters
		@see indexOfWholeWordIgnoreCase, containsWholeWord
	*/
	bool containsWholeWordIgnoreCase (const String& wordToLookFor) const noexcept;

	/** Finds an instance of another substring if it exists as a distict word.

		@returns    if the string contains this word, surrounded by non-alphanumeric characters,
					then this will return the index of the start of the substring. If it isn't
					found, then it will return -1
		@see indexOfWholeWordIgnoreCase, containsWholeWord
	*/
	int indexOfWholeWord (const String& wordToLookFor) const noexcept;

	/** Finds an instance of another substring if it exists as a distict word.

		@returns    if the string contains this word, surrounded by non-alphanumeric characters,
					then this will return the index of the start of the substring. If it isn't
					found, then it will return -1
		@see indexOfWholeWord, containsWholeWordIgnoreCase
	*/
	int indexOfWholeWordIgnoreCase (const String& wordToLookFor) const noexcept;

	/** Looks for any of a set of characters in the string.
		Uses a case-sensitive comparison.

		@returns    true if the string contains any of the characters from
					the string that is passed in.
	*/
	bool containsAnyOf (const String& charactersItMightContain) const noexcept;

	/** Looks for a set of characters in the string.
		Uses a case-sensitive comparison.

		@returns    Returns false if any of the characters in this string do not occur in
					the parameter string. If this string is empty, the return value will
					always be true.
	*/
	bool containsOnly (const String& charactersItMightContain) const noexcept;

	/** Returns true if this string contains any non-whitespace characters.

		This will return false if the string contains only whitespace characters, or
		if it's empty.

		It is equivalent to calling "myString.trim().isNotEmpty()".
	*/
	bool containsNonWhitespaceChars() const noexcept;

	/** Returns true if the string matches this simple wildcard expression.

		So for example String ("abcdef").matchesWildcard ("*DEF", true) would return true.

		This isn't a full-blown regex though! The only wildcard characters supported
		are "*" and "?". It's mainly intended for filename pattern matching.
	*/
	bool matchesWildcard (const String& wildcard, bool ignoreCase) const noexcept;

	// Substring location methods..

	/** Searches for a character inside this string.
		Uses a case-sensitive comparison.
		@returns    the index of the first occurrence of the character in this
					string, or -1 if it's not found.
	*/
	int indexOfChar (juce_wchar characterToLookFor) const noexcept;

	/** Searches for a character inside this string.
		Uses a case-sensitive comparison.
		@param startIndex           the index from which the search should proceed
		@param characterToLookFor   the character to look for
		@returns            the index of the first occurrence of the character in this
							string, or -1 if it's not found.
	*/
	int indexOfChar (int startIndex, juce_wchar characterToLookFor) const noexcept;

	/** Returns the index of the first character that matches one of the characters
		passed-in to this method.

		This scans the string, beginning from the startIndex supplied, and if it finds
		a character that appears in the string charactersToLookFor, it returns its index.

		If none of these characters are found, it returns -1.

		If ignoreCase is true, the comparison will be case-insensitive.

		@see indexOfChar, lastIndexOfAnyOf
	*/
	int indexOfAnyOf (const String& charactersToLookFor,
					  int startIndex = 0,
					  bool ignoreCase = false) const noexcept;

	/** Searches for a substring within this string.
		Uses a case-sensitive comparison.
		@returns    the index of the first occurrence of this substring, or -1 if it's not found.
					If textToLookFor is an empty string, this will always return 0.
	*/
	int indexOf (const String& textToLookFor) const noexcept;

	/** Searches for a substring within this string.
		Uses a case-sensitive comparison.
		@param startIndex       the index from which the search should proceed
		@param textToLookFor    the string to search for
		@returns                the index of the first occurrence of this substring, or -1 if it's not found.
								If textToLookFor is an empty string, this will always return -1.
	*/
	int indexOf (int startIndex, const String& textToLookFor) const noexcept;

	/** Searches for a substring within this string.
		Uses a case-insensitive comparison.
		@returns    the index of the first occurrence of this substring, or -1 if it's not found.
					If textToLookFor is an empty string, this will always return 0.
	*/
	int indexOfIgnoreCase (const String& textToLookFor) const noexcept;

	/** Searches for a substring within this string.
		Uses a case-insensitive comparison.
		@param startIndex       the index from which the search should proceed
		@param textToLookFor    the string to search for
		@returns                the index of the first occurrence of this substring, or -1 if it's not found.
								If textToLookFor is an empty string, this will always return -1.
	*/
	int indexOfIgnoreCase (int startIndex, const String& textToLookFor) const noexcept;

	/** Searches for a character inside this string (working backwards from the end of the string).
		Uses a case-sensitive comparison.
		@returns    the index of the last occurrence of the character in this string, or -1 if it's not found.
	*/
	int lastIndexOfChar (juce_wchar character) const noexcept;

	/** Searches for a substring inside this string (working backwards from the end of the string).
		Uses a case-sensitive comparison.
		@returns    the index of the start of the last occurrence of the substring within this string,
					or -1 if it's not found. If textToLookFor is an empty string, this will always return -1.
	*/
	int lastIndexOf (const String& textToLookFor) const noexcept;

	/** Searches for a substring inside this string (working backwards from the end of the string).
		Uses a case-insensitive comparison.
		@returns    the index of the start of the last occurrence of the substring within this string, or -1
					if it's not found. If textToLookFor is an empty string, this will always return -1.
	*/
	int lastIndexOfIgnoreCase (const String& textToLookFor) const noexcept;

	/** Returns the index of the last character in this string that matches one of the
		characters passed-in to this method.

		This scans the string backwards, starting from its end, and if it finds
		a character that appears in the string charactersToLookFor, it returns its index.

		If none of these characters are found, it returns -1.

		If ignoreCase is true, the comparison will be case-insensitive.

		@see lastIndexOf, indexOfAnyOf
	*/
	int lastIndexOfAnyOf (const String& charactersToLookFor,
						  bool ignoreCase = false) const noexcept;

	// Substring extraction and manipulation methods..

	/** Returns the character at this index in the string.
		In a release build, no checks are made to see if the index is within a valid range, so be
		careful! In a debug build, the index is checked and an assertion fires if it's out-of-range.

		Also beware that depending on the encoding format that the string is using internally, this
		method may execute in either O(1) or O(n) time, so be careful when using it in your algorithms.
		If you're scanning through a string to inspect its characters, you should never use this operator
		for random access, it's far more efficient to call getCharPointer() to return a pointer, and
		then to use that to iterate the string.
		@see getCharPointer
	*/
	const juce_wchar operator[] (int index) const noexcept;

	/** Returns the final character of the string.
		If the string is empty this will return 0.
	*/
	juce_wchar getLastCharacter() const noexcept;

	/** Returns a subsection of the string.

		If the range specified is beyond the limits of the string, as much as
		possible is returned.

		@param startIndex   the index of the start of the substring needed
		@param endIndex     all characters from startIndex up to (but not including)
							this index are returned
		@see fromFirstOccurrenceOf, dropLastCharacters, getLastCharacters, upToFirstOccurrenceOf
	*/
	String substring (int startIndex, int endIndex) const;

	/** Returns a section of the string, starting from a given position.

		@param startIndex   the first character to include. If this is beyond the end
							of the string, an empty string is returned. If it is zero or
							less, the whole string is returned.
		@returns            the substring from startIndex up to the end of the string
		@see dropLastCharacters, getLastCharacters, fromFirstOccurrenceOf, upToFirstOccurrenceOf, fromLastOccurrenceOf
	*/
	String substring (int startIndex) const;

	/** Returns a version of this string with a number of characters removed
		from the end.

		@param numberToDrop     the number of characters to drop from the end of the
								string. If this is greater than the length of the string,
								an empty string will be returned. If zero or less, the
								original string will be returned.
		@see substring, fromFirstOccurrenceOf, upToFirstOccurrenceOf, fromLastOccurrenceOf, getLastCharacter
	*/
	String dropLastCharacters (int numberToDrop) const;

	/** Returns a number of characters from the end of the string.

		This returns the last numCharacters characters from the end of the string. If the
		string is shorter than numCharacters, the whole string is returned.

		@see substring, dropLastCharacters, getLastCharacter
	*/
	String getLastCharacters (int numCharacters) const;

	/** Returns a section of the string starting from a given substring.

		This will search for the first occurrence of the given substring, and
		return the section of the string starting from the point where this is
		found (optionally not including the substring itself).

		e.g. for the string "123456", fromFirstOccurrenceOf ("34", true) would return "3456", and
									  fromFirstOccurrenceOf ("34", false) would return "56".

		If the substring isn't found, the method will return an empty string.

		If ignoreCase is true, the comparison will be case-insensitive.

		@see upToFirstOccurrenceOf, fromLastOccurrenceOf
	*/
	String fromFirstOccurrenceOf (const String& substringToStartFrom,
								  bool includeSubStringInResult,
										bool ignoreCase) const;

	/** Returns a section of the string starting from the last occurrence of a given substring.

		Similar to fromFirstOccurrenceOf(), but using the last occurrence of the substring, and
		unlike fromFirstOccurrenceOf(), if the substring isn't found, this method will
		return the whole of the original string.

		@see fromFirstOccurrenceOf, upToLastOccurrenceOf
	*/
	String fromLastOccurrenceOf (const String& substringToFind,
								 bool includeSubStringInResult,
								 bool ignoreCase) const;

	/** Returns the start of this string, up to the first occurrence of a substring.

		This will search for the first occurrence of a given substring, and then
		return a copy of the string, up to the position of this substring,
		optionally including or excluding the substring itself in the result.

		e.g. for the string "123456", upTo ("34", false) would return "12", and
									  upTo ("34", true) would return "1234".

		If the substring isn't found, this will return the whole of the original string.

		@see upToLastOccurrenceOf, fromFirstOccurrenceOf
	*/
	String upToFirstOccurrenceOf (const String& substringToEndWith,
								  bool includeSubStringInResult,
								  bool ignoreCase) const;

	/** Returns the start of this string, up to the last occurrence of a substring.

		Similar to upToFirstOccurrenceOf(), but this finds the last occurrence rather than the first.
		If the substring isn't found, this will return the whole of the original string.

		@see upToFirstOccurrenceOf, fromFirstOccurrenceOf
	*/
	String upToLastOccurrenceOf (const String& substringToFind,
								 bool includeSubStringInResult,
								 bool ignoreCase) const;

	/** Returns a copy of this string with any whitespace characters removed from the start and end. */
	String trim() const;

	/** Returns a copy of this string with any whitespace characters removed from the start. */
	String trimStart() const;

	/** Returns a copy of this string with any whitespace characters removed from the end. */
	String trimEnd() const;

	/** Returns a copy of this string, having removed a specified set of characters from its start.
		Characters are removed from the start of the string until it finds one that is not in the
		specified set, and then it stops.
		@param charactersToTrim     the set of characters to remove.
		@see trim, trimStart, trimCharactersAtEnd
	*/
	String trimCharactersAtStart (const String& charactersToTrim) const;

	/** Returns a copy of this string, having removed a specified set of characters from its end.
		Characters are removed from the end of the string until it finds one that is not in the
		specified set, and then it stops.
		@param charactersToTrim     the set of characters to remove.
		@see trim, trimEnd, trimCharactersAtStart
	*/
	String trimCharactersAtEnd (const String& charactersToTrim) const;

	/** Returns an upper-case version of this string. */
	String toUpperCase() const;

	/** Returns an lower-case version of this string. */
	String toLowerCase() const;

	/** Replaces a sub-section of the string with another string.

		This will return a copy of this string, with a set of characters
		from startIndex to startIndex + numCharsToReplace removed, and with
		a new string inserted in their place.

		Note that this is a const method, and won't alter the string itself.

		@param startIndex               the first character to remove. If this is beyond the bounds of the string,
										it will be constrained to a valid range.
		@param numCharactersToReplace   the number of characters to remove. If zero or less, no
										characters will be taken out.
		@param stringToInsert           the new string to insert at startIndex after the characters have been
										removed.
	*/
	String replaceSection (int startIndex,
						   int numCharactersToReplace,
						   const String& stringToInsert) const;

	/** Replaces all occurrences of a substring with another string.

		Returns a copy of this string, with any occurrences of stringToReplace
		swapped for stringToInsertInstead.

		Note that this is a const method, and won't alter the string itself.
	*/
	String replace (const String& stringToReplace,
					const String& stringToInsertInstead,
					bool ignoreCase = false) const;

	/** Returns a string with all occurrences of a character replaced with a different one. */
	String replaceCharacter (juce_wchar characterToReplace,
							 juce_wchar characterToInsertInstead) const;

	/** Replaces a set of characters with another set.

		Returns a string in which each character from charactersToReplace has been replaced
		by the character at the equivalent position in newCharacters (so the two strings
		passed in must be the same length).

		e.g. replaceCharacters ("abc", "def") replaces 'a' with 'd', 'b' with 'e', etc.

		Note that this is a const method, and won't affect the string itself.
	*/
	String replaceCharacters (const String& charactersToReplace,
							  const String& charactersToInsertInstead) const;

	/** Returns a version of this string that only retains a fixed set of characters.

		This will return a copy of this string, omitting any characters which are not
		found in the string passed-in.

		e.g. for "1122334455", retainCharacters ("432") would return "223344"

		Note that this is a const method, and won't alter the string itself.
	*/
	String retainCharacters (const String& charactersToRetain) const;

	/** Returns a version of this string with a set of characters removed.

		This will return a copy of this string, omitting any characters which are
		found in the string passed-in.

		e.g. for "1122334455", removeCharacters ("432") would return "1155"

		Note that this is a const method, and won't alter the string itself.
	*/
	String removeCharacters (const String& charactersToRemove) const;

	/** Returns a section from the start of the string that only contains a certain set of characters.

		This returns the leftmost section of the string, up to (and not including) the
		first character that doesn't appear in the string passed in.
	*/
	String initialSectionContainingOnly (const String& permittedCharacters) const;

	/** Returns a section from the start of the string that only contains a certain set of characters.

		This returns the leftmost section of the string, up to (and not including) the
		first character that occurs in the string passed in. (If none of the specified
		characters are found in the string, the return value will just be the original string).
	*/
	String initialSectionNotContaining (const String& charactersToStopAt) const;

	/** Checks whether the string might be in quotation marks.

		@returns    true if the string begins with a quote character (either a double or single quote).
					It is also true if there is whitespace before the quote, but it doesn't check the end of the string.
		@see unquoted, quoted
	*/
	bool isQuotedString() const;

	/** Removes quotation marks from around the string, (if there are any).

		Returns a copy of this string with any quotes removed from its ends. Quotes that aren't
		at the ends of the string are not affected. If there aren't any quotes, the original string
		is returned.

		Note that this is a const method, and won't alter the string itself.

		@see isQuotedString, quoted
	*/
	String unquoted() const;

	/** Adds quotation marks around a string.

		This will return a copy of the string with a quote at the start and end, (but won't
		add the quote if there's already one there, so it's safe to call this on strings that
		may already have quotes around them).

		Note that this is a const method, and won't alter the string itself.

		@param quoteCharacter   the character to add at the start and end
		@see isQuotedString, unquoted
	*/
	String quoted (juce_wchar quoteCharacter = '"') const;

	/** Creates a string which is a version of a string repeated and joined together.

		@param stringToRepeat         the string to repeat
		@param numberOfTimesToRepeat  how many times to repeat it
	*/
	static String repeatedString (const String& stringToRepeat,
								  int numberOfTimesToRepeat);

	/** Returns a copy of this string with the specified character repeatedly added to its
		beginning until the total length is at least the minimum length specified.
	*/
	String paddedLeft (juce_wchar padCharacter, int minimumLength) const;

	/** Returns a copy of this string with the specified character repeatedly added to its
		end until the total length is at least the minimum length specified.
	*/
	String paddedRight (juce_wchar padCharacter, int minimumLength) const;

	/** Creates a string from data in an unknown format.

		This looks at some binary data and tries to guess whether it's Unicode
		or 8-bit characters, then returns a string that represents it correctly.

		Should be able to handle Unicode endianness correctly, by looking at
		the first two bytes.
	*/
	static String createStringFromData (const void* data, int size);

	/** Creates a String from a printf-style parameter list.

		I don't like this method. I don't use it myself, and I recommend avoiding it and
		using the operator<< methods or pretty much anything else instead. It's only provided
		here because of the popular unrest that was stirred-up when I tried to remove it...

		If you're really determined to use it, at least make sure that you never, ever,
		pass any String objects to it as parameters. And bear in mind that internally, depending
		on the platform, it may be using wchar_t or char character types, so that even string
		literals can't be safely used as parameters if you're writing portable code.
	*/
	static String formatted (const String formatString, ... );

	// Numeric conversions..

	/** Creates a string containing this signed 32-bit integer as a decimal number.
		@see getIntValue, getFloatValue, getDoubleValue, toHexString
	*/
	explicit String (int decimalInteger);

	/** Creates a string containing this unsigned 32-bit integer as a decimal number.
		@see getIntValue, getFloatValue, getDoubleValue, toHexString
	*/
	explicit String (unsigned int decimalInteger);

	/** Creates a string containing this signed 16-bit integer as a decimal number.
		@see getIntValue, getFloatValue, getDoubleValue, toHexString
	*/
	explicit String (short decimalInteger);

	/** Creates a string containing this unsigned 16-bit integer as a decimal number.
		@see getIntValue, getFloatValue, getDoubleValue, toHexString
	*/
	explicit String (unsigned short decimalInteger);

	/** Creates a string containing this signed 64-bit integer as a decimal number.
		@see getLargeIntValue, getFloatValue, getDoubleValue, toHexString
	*/
	explicit String (int64 largeIntegerValue);

	/** Creates a string containing this unsigned 64-bit integer as a decimal number.
		@see getLargeIntValue, getFloatValue, getDoubleValue, toHexString
	*/
	explicit String (uint64 largeIntegerValue);

	/** Creates a string representing this floating-point number.
		@param floatValue               the value to convert to a string
		@see getDoubleValue, getIntValue
	*/
	explicit String (float floatValue);

	/** Creates a string representing this floating-point number.
		@param doubleValue              the value to convert to a string
		@see getFloatValue, getIntValue
	*/
	explicit String (double doubleValue);

	/** Creates a string representing this floating-point number.
		@param floatValue               the value to convert to a string
		@param numberOfDecimalPlaces    if this is > 0, it will format the number using that many
										decimal places, and will not use exponent notation. If 0 or
										less, it will use exponent notation if necessary.
		@see getDoubleValue, getIntValue
	*/
	String (float floatValue, int numberOfDecimalPlaces);

	/** Creates a string representing this floating-point number.
		@param doubleValue              the value to convert to a string
		@param numberOfDecimalPlaces    if this is > 0, it will format the number using that many
										decimal places, and will not use exponent notation. If 0 or
										less, it will use exponent notation if necessary.
		@see getFloatValue, getIntValue
	*/
	String (double doubleValue, int numberOfDecimalPlaces);

	/** Reads the value of the string as a decimal number (up to 32 bits in size).

		@returns the value of the string as a 32 bit signed base-10 integer.
		@see getTrailingIntValue, getHexValue32, getHexValue64
	*/
	int getIntValue() const noexcept;

	/** Reads the value of the string as a decimal number (up to 64 bits in size).

		@returns the value of the string as a 64 bit signed base-10 integer.
	*/
	int64 getLargeIntValue() const noexcept;

	/** Parses a decimal number from the end of the string.

		This will look for a value at the end of the string.
		e.g. for "321 xyz654" it will return 654; for "2 3 4" it'll return 4.

		Negative numbers are not handled, so "xyz-5" returns 5.

		@see getIntValue
	*/
	int getTrailingIntValue() const noexcept;

	/** Parses this string as a floating point number.

		@returns    the value of the string as a 32-bit floating point value.
		@see getDoubleValue
	*/
	float getFloatValue() const noexcept;

	/** Parses this string as a floating point number.

		@returns    the value of the string as a 64-bit floating point value.
		@see getFloatValue
	*/
	double getDoubleValue() const noexcept;

	/** Parses the string as a hexadecimal number.

		Non-hexadecimal characters in the string are ignored.

		If the string contains too many characters, then the lowest significant
		digits are returned, e.g. "ffff12345678" would produce 0x12345678.

		@returns    a 32-bit number which is the value of the string in hex.
	*/
	int getHexValue32() const noexcept;

	/** Parses the string as a hexadecimal number.

		Non-hexadecimal characters in the string are ignored.

		If the string contains too many characters, then the lowest significant
		digits are returned, e.g. "ffff1234567812345678" would produce 0x1234567812345678.

		@returns    a 64-bit number which is the value of the string in hex.
	*/
	int64 getHexValue64() const noexcept;

	/** Creates a string representing this 32-bit value in hexadecimal. */
	static String toHexString (int number);

	/** Creates a string representing this 64-bit value in hexadecimal. */
	static String toHexString (int64 number);

	/** Creates a string representing this 16-bit value in hexadecimal. */
	static String toHexString (short number);

	/** Creates a string containing a hex dump of a block of binary data.

		@param data         the binary data to use as input
		@param size         how many bytes of data to use
		@param groupSize    how many bytes are grouped together before inserting a
							space into the output. e.g. group size 0 has no spaces,
							group size 1 looks like: "be a1 c2 ff", group size 2 looks
							like "bea1 c2ff".
	*/
	static String toHexString (const void* data, int size, int groupSize = 1);

	/** Returns the character pointer currently being used to store this string.

		Because it returns a reference to the string's internal data, the pointer
		that is returned must not be stored anywhere, as it can be deleted whenever the
		string changes.
	*/
	inline const CharPointerType& getCharPointer() const noexcept    { return text; }

	/** Returns a pointer to a UTF-8 version of this string.

		Because it returns a reference to the string's internal data, the pointer
		that is returned must not be stored anywhere, as it can be deleted whenever the
		string changes.

		To find out how many bytes you need to store this string as UTF-8, you can call
		CharPointer_UTF8::getBytesRequiredFor (myString.getCharPointer())

		@see getCharPointer, toUTF16, toUTF32
	*/
	CharPointer_UTF8 toUTF8() const;

	/** Returns a pointer to a UTF-32 version of this string.

		Because it returns a reference to the string's internal data, the pointer
		that is returned must not be stored anywhere, as it can be deleted whenever the
		string changes.

		To find out how many bytes you need to store this string as UTF-16, you can call
		CharPointer_UTF16::getBytesRequiredFor (myString.getCharPointer())

		@see getCharPointer, toUTF8, toUTF32
	*/
	CharPointer_UTF16 toUTF16() const;

	/** Returns a pointer to a UTF-32 version of this string.

		Because it returns a reference to the string's internal data, the pointer
		that is returned must not be stored anywhere, as it can be deleted whenever the
		string changes.

		@see getCharPointer, toUTF8, toUTF16
	*/
	CharPointer_UTF32 toUTF32() const;

	/** Returns a pointer to a wchar_t version of this string.

		Because it returns a reference to the string's internal data, the pointer
		that is returned must not be stored anywhere, as it can be deleted whenever the
		string changes.

		Bear in mind that the wchar_t type is different on different platforms, so on
		Windows, this will be equivalent to calling toUTF16(), on unix it'll be the same
		as calling toUTF32(), etc.

		@see getCharPointer, toUTF8, toUTF16, toUTF32
	*/
	const wchar_t* toWideCharPointer() const;

	/** Creates a String from a UTF-8 encoded buffer.
		If the size is < 0, it'll keep reading until it hits a zero.
	*/
	static String fromUTF8 (const char* utf8buffer, int bufferSizeBytes = -1);

	/** Returns the number of bytes required to represent this string as UTF8.
		The number returned does NOT include the trailing zero.
		@see toUTF8, copyToUTF8
	*/
	int getNumBytesAsUTF8() const noexcept;

	/** Copies the string to a buffer as UTF-8 characters.

		Returns the number of bytes copied to the buffer, including the terminating null
		character.

		To find out how many bytes you need to store this string as UTF-8, you can call
		CharPointer_UTF8::getBytesRequiredFor (myString.getCharPointer())

		@param destBuffer       the place to copy it to; if this is a null pointer, the method just
								returns the number of bytes required (including the terminating null character).
		@param maxBufferSizeBytes  the size of the destination buffer, in bytes. If the string won't fit, it'll
								put in as many as it can while still allowing for a terminating null char at the
								end, and will return the number of bytes that were actually used.
		@see CharPointer_UTF8::writeWithDestByteLimit
	*/
	int copyToUTF8 (CharPointer_UTF8::CharType* destBuffer, int maxBufferSizeBytes) const noexcept;

	/** Copies the string to a buffer as UTF-16 characters.

		Returns the number of bytes copied to the buffer, including the terminating null
		character.

		To find out how many bytes you need to store this string as UTF-16, you can call
		CharPointer_UTF16::getBytesRequiredFor (myString.getCharPointer())

		@param destBuffer       the place to copy it to; if this is a null pointer, the method just
								returns the number of bytes required (including the terminating null character).
		@param maxBufferSizeBytes  the size of the destination buffer, in bytes. If the string won't fit, it'll
								put in as many as it can while still allowing for a terminating null char at the
								end, and will return the number of bytes that were actually used.
		@see CharPointer_UTF16::writeWithDestByteLimit
	*/
	int copyToUTF16 (CharPointer_UTF16::CharType* destBuffer, int maxBufferSizeBytes) const noexcept;

	/** Copies the string to a buffer as UTF-16 characters.

		Returns the number of bytes copied to the buffer, including the terminating null
		character.

		To find out how many bytes you need to store this string as UTF-32, you can call
		CharPointer_UTF32::getBytesRequiredFor (myString.getCharPointer())

		@param destBuffer       the place to copy it to; if this is a null pointer, the method just
								returns the number of bytes required (including the terminating null character).
		@param maxBufferSizeBytes  the size of the destination buffer, in bytes. If the string won't fit, it'll
								put in as many as it can while still allowing for a terminating null char at the
								end, and will return the number of bytes that were actually used.
		@see CharPointer_UTF32::writeWithDestByteLimit
	*/
	int copyToUTF32 (CharPointer_UTF32::CharType* destBuffer, int maxBufferSizeBytes) const noexcept;

	/** Increases the string's internally allocated storage.

		Although the string's contents won't be affected by this call, it will
		increase the amount of memory allocated internally for the string to grow into.

		If you're about to make a large number of calls to methods such
		as += or <<, it's more efficient to preallocate enough extra space
		beforehand, so that these methods won't have to keep resizing the string
		to append the extra characters.

		@param numBytesNeeded   the number of bytes to allocate storage for. If this
								value is less than the currently allocated size, it will
								have no effect.
	*/
	void preallocateBytes (size_t numBytesNeeded);

	/** Swaps the contents of this string with another one.
		This is a very fast operation, as no allocation or copying needs to be done.
	*/
	void swapWith (String& other) noexcept;

   #if JUCE_MAC || JUCE_IOS || DOXYGEN
	/** MAC ONLY - Creates a String from an OSX CFString. */
	static String fromCFString (CFStringRef cfString);

	/** MAC ONLY - Converts this string to a CFString.
		Remember that you must use CFRelease() to free the returned string when you're
		finished with it.
	*/
	CFStringRef toCFString() const;

	/** MAC ONLY - Returns a copy of this string in which any decomposed unicode characters have
		been converted to their precomposed equivalents. */
	String convertToPrecomposedUnicode() const;
   #endif

private:

	CharPointerType text;

	struct PreallocationBytes
	{
		explicit PreallocationBytes (size_t);
		size_t numBytes;
	};

	explicit String (const PreallocationBytes&); // This constructor preallocates a certain amount of memory
	void appendFixedLength (const char* text, int numExtraChars);
	size_t getByteOffsetOfEnd() const noexcept;
	JUCE_DEPRECATED (String (const String& stringToCopy, size_t charsToAllocate));

	// This private cast operator should prevent strings being accidentally cast
	// to bools (this is possible because the compiler can add an implicit cast
	// via a const char*)
	operator bool() const noexcept  { return false; }
};

/** Concatenates two strings. */
JUCE_API String JUCE_CALLTYPE operator+ (const char* string1,     const String& string2);
/** Concatenates two strings. */
JUCE_API String JUCE_CALLTYPE operator+ (const wchar_t* string1,  const String& string2);
/** Concatenates two strings. */
JUCE_API String JUCE_CALLTYPE operator+ (char string1,            const String& string2);
/** Concatenates two strings. */
JUCE_API String JUCE_CALLTYPE operator+ (wchar_t string1,         const String& string2);
#if ! JUCE_NATIVE_WCHAR_IS_UTF32
/** Concatenates two strings. */
JUCE_API String JUCE_CALLTYPE operator+ (juce_wchar string1,      const String& string2);
#endif

/** Concatenates two strings. */
JUCE_API String JUCE_CALLTYPE operator+ (String string1, const String& string2);
/** Concatenates two strings. */
JUCE_API String JUCE_CALLTYPE operator+ (String string1, const char* string2);
/** Concatenates two strings. */
JUCE_API String JUCE_CALLTYPE operator+ (String string1, const wchar_t* string2);
/** Concatenates two strings. */
JUCE_API String JUCE_CALLTYPE operator+ (String string1, char characterToAppend);
/** Concatenates two strings. */
JUCE_API String JUCE_CALLTYPE operator+ (String string1, wchar_t characterToAppend);
#if ! JUCE_NATIVE_WCHAR_IS_UTF32
/** Concatenates two strings. */
JUCE_API String JUCE_CALLTYPE operator+ (String string1, juce_wchar characterToAppend);
#endif

/** Appends a character at the end of a string. */
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, char characterToAppend);
/** Appends a character at the end of a string. */
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, wchar_t characterToAppend);
#if ! JUCE_NATIVE_WCHAR_IS_UTF32
/** Appends a character at the end of a string. */
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, juce_wchar characterToAppend);
#endif

/** Appends a string to the end of the first one. */
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, const char* string2);
/** Appends a string to the end of the first one. */
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, const wchar_t* string2);
/** Appends a string to the end of the first one. */
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, const String& string2);

/** Appends a decimal number at the end of a string. */
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, short number);
/** Appends a decimal number at the end of a string. */
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, int number);
/** Appends a decimal number at the end of a string. */
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, long number);
/** Appends a decimal number at the end of a string. */
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, float number);
/** Appends a decimal number at the end of a string. */
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, double number);

/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator== (const String& string1, const String& string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator== (const String& string1, const char* string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator== (const String& string1, const wchar_t* string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator== (const String& string1, const CharPointer_UTF8& string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator== (const String& string1, const CharPointer_UTF16& string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator== (const String& string1, const CharPointer_UTF32& string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator!= (const String& string1, const String& string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator!= (const String& string1, const char* string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator!= (const String& string1, const wchar_t* string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator!= (const String& string1, const CharPointer_UTF8& string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator!= (const String& string1, const CharPointer_UTF16& string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator!= (const String& string1, const CharPointer_UTF32& string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator>  (const String& string1, const String& string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator<  (const String& string1, const String& string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator>= (const String& string1, const String& string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator<= (const String& string1, const String& string2) noexcept;

/** This operator allows you to write a juce String directly to std output streams.
	This is handy for writing strings to std::cout, std::cerr, etc.
*/
template <class traits>
std::basic_ostream <char, traits>& JUCE_CALLTYPE operator<< (std::basic_ostream <char, traits>& stream, const String& stringToWrite)
{
	return stream << stringToWrite.toUTF8().getAddress();
}

/** This operator allows you to write a juce String directly to std output streams.
	This is handy for writing strings to std::wcout, std::wcerr, etc.
*/
template <class traits>
std::basic_ostream <wchar_t, traits>& JUCE_CALLTYPE operator<< (std::basic_ostream <wchar_t, traits>& stream, const String& stringToWrite)
{
	return stream << stringToWrite.toWideCharPointer();
}

/** Writes a string to an OutputStream as UTF8. */
JUCE_API OutputStream& JUCE_CALLTYPE operator<< (OutputStream& stream, const String& stringToWrite);

#endif   // __JUCE_STRING_JUCEHEADER__

/*** End of inlined file: juce_String.h ***/

/**
	Acts as an application-wide logging class.

	A subclass of Logger can be created and passed into the Logger::setCurrentLogger
	method and this will then be used by all calls to writeToLog.

	The logger class also contains methods for writing messages to the debugger's
	output stream.

	@see FileLogger
*/
class JUCE_API  Logger
{
public:

	/** Destructor. */
	virtual ~Logger();

	/** Sets the current logging class to use.

		Note that the object passed in won't be deleted when no longer needed.
		A null pointer can be passed-in to disable any logging.

		If deleteOldLogger is set to true, the existing logger will be
		deleted (if there is one).
	*/
	static void JUCE_CALLTYPE setCurrentLogger (Logger* newLogger,
												bool deleteOldLogger = false);

	/** Writes a string to the current logger.

		This will pass the string to the logger's logMessage() method if a logger
		has been set.

		@see logMessage
	*/
	static void JUCE_CALLTYPE writeToLog (const String& message);

	/** Writes a message to the standard error stream.

		This can be called directly, or by using the DBG() macro in
		juce_PlatformDefs.h (which will avoid calling the method in non-debug builds).
	*/
	static void JUCE_CALLTYPE outputDebugString (const String& text);

protected:

	Logger();

	/** This is overloaded by subclasses to implement custom logging behaviour.

		@see setCurrentLogger
	*/
	virtual void logMessage (const String& message) = 0;

private:
	static Logger* currentLogger;
};

#endif   // __JUCE_LOGGER_JUCEHEADER__

/*** End of inlined file: juce_Logger.h ***/


/*** Start of inlined file: juce_LeakedObjectDetector.h ***/
#ifndef __JUCE_LEAKEDOBJECTDETECTOR_JUCEHEADER__
#define __JUCE_LEAKEDOBJECTDETECTOR_JUCEHEADER__

/**
	Embedding an instance of this class inside another class can be used as a low-overhead
	way of detecting leaked instances.

	This class keeps an internal static count of the number of instances that are
	active, so that when the app is shutdown and the static destructors are called,
	it can check whether there are any left-over instances that may have been leaked.

	To use it, use the JUCE_LEAK_DETECTOR macro as a simple way to put one in your
	class declaration. Have a look through the juce codebase for examples, it's used
	in most of the classes.
*/
template <class OwnerClass>
class LeakedObjectDetector
{
public:

	LeakedObjectDetector() noexcept                                 { ++(getCounter().numObjects); }
	LeakedObjectDetector (const LeakedObjectDetector&) noexcept     { ++(getCounter().numObjects); }

	~LeakedObjectDetector()
	{
		if (--(getCounter().numObjects) < 0)
		{
			DBG ("*** Dangling pointer deletion! Class: " << getLeakedObjectClassName());

			/** If you hit this, then you've managed to delete more instances of this class than you've
				created.. That indicates that you're deleting some dangling pointers.

				Note that although this assertion will have been triggered during a destructor, it might
				not be this particular deletion that's at fault - the incorrect one may have happened
				at an earlier point in the program, and simply not been detected until now.

				Most errors like this are caused by using old-fashioned, non-RAII techniques for
				your object management. Tut, tut. Always, always use ScopedPointers, OwnedArrays,
				ReferenceCountedObjects, etc, and avoid the 'delete' operator at all costs!
			*/
			jassertfalse;
		}
	}

private:

	class LeakCounter
	{
	public:
		LeakCounter() noexcept {}

		~LeakCounter()
		{
			if (numObjects.value > 0)
			{
				DBG ("*** Leaked objects detected: " << numObjects.value << " instance(s) of class " << getLeakedObjectClassName());

				/** If you hit this, then you've leaked one or more objects of the type specified by
					the 'OwnerClass' template parameter - the name should have been printed by the line above.

					If you're leaking, it's probably because you're using old-fashioned, non-RAII techniques for
					your object management. Tut, tut. Always, always use ScopedPointers, OwnedArrays,
					ReferenceCountedObjects, etc, and avoid the 'delete' operator at all costs!
				*/
				jassertfalse;
			}
		}

		Atomic<int> numObjects;
	};

	static const char* getLeakedObjectClassName()
	{
		return OwnerClass::getLeakedObjectClassName();
	}

	static LeakCounter& getCounter() noexcept
	{
		static LeakCounter counter;
		return counter;
	}
};

#if DOXYGEN || ! defined (JUCE_LEAK_DETECTOR)
 #if (DOXYGEN || JUCE_CHECK_MEMORY_LEAKS)
  /** This macro lets you embed a leak-detecting object inside a class.

	  To use it, simply declare a JUCE_LEAK_DETECTOR(YourClassName) inside a private section
	  of the class declaration. E.g.

	  @code
	  class MyClass
	  {
	  public:
		  MyClass();
		  void blahBlah();

	  private:
		  JUCE_LEAK_DETECTOR (MyClass);
	  };@endcode

	  @see JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR, LeakedObjectDetector
  */
  #define JUCE_LEAK_DETECTOR(OwnerClass) \
		friend class juce::LeakedObjectDetector<OwnerClass>; \
		static const char* getLeakedObjectClassName() noexcept { return #OwnerClass; } \
		juce::LeakedObjectDetector<OwnerClass> JUCE_JOIN_MACRO (leakDetector, __LINE__);
 #else
  #define JUCE_LEAK_DETECTOR(OwnerClass)
 #endif
#endif

#endif   // __JUCE_LEAKEDOBJECTDETECTOR_JUCEHEADER__

/*** End of inlined file: juce_LeakedObjectDetector.h ***/

// unbelievably, some system headers actually use macros to define these symbols:
#undef check
#undef TYPE_BOOL

#if JUCE_MAC || JUCE_IOS || DOXYGEN

 /** A handy C++ wrapper that creates and deletes an NSAutoreleasePool object using RAII.
	 You should use the JUCE_AUTORELEASEPOOL macro to create a local auto-release pool on the stack.
 */
 class JUCE_API  ScopedAutoReleasePool
 {
 public:
	 ScopedAutoReleasePool();
	 ~ScopedAutoReleasePool();

 private:
	 void* pool;

	 JUCE_DECLARE_NON_COPYABLE (ScopedAutoReleasePool);
 };

 /** A macro that can be used to easily declare a local ScopedAutoReleasePool object for RAII-based obj-C autoreleasing. */
 #define JUCE_AUTORELEASEPOOL  const juce::ScopedAutoReleasePool JUCE_JOIN_MACRO (autoReleasePool_, __LINE__);

#else
 #define JUCE_AUTORELEASEPOOL
#endif

END_JUCE_NAMESPACE

#endif   // __JUCE_STANDARDHEADER_JUCEHEADER__

/*** End of inlined file: juce_StandardHeader.h ***/

namespace juce
{

// START_AUTOINCLUDE containers, files, json, logging, maths, memory, misc, network,
// streams, system, text, threads, time, unit_tests, xml, zip
#ifndef __JUCE_ABSTRACTFIFO_JUCEHEADER__

/*** Start of inlined file: juce_AbstractFifo.h ***/
#ifndef __JUCE_ABSTRACTFIFO_JUCEHEADER__
#define __JUCE_ABSTRACTFIFO_JUCEHEADER__

/**
	Encapsulates the logic required to implement a lock-free FIFO.

	This class handles the logic needed when building a single-reader, single-writer FIFO.

	It doesn't actually hold any data itself, but your FIFO class can use one of these to manage
	its position and status when reading or writing to it.

	To use it, you can call prepareToWrite() to determine the position within your own buffer that
	an incoming block of data should be stored, and prepareToRead() to find out when the next
	outgoing block should be read from.

	e.g.
	@code
	class MyFifo
	{
	public:
		MyFifo()  : abstractFifo (1024)
		{
		}

		void addToFifo (const int* someData, int numItems)
		{
			int start1, size1, start2, size2;
			abstractFifo.prepareToWrite (numItems, start1, size1, start2, size2);

			if (size1 > 0)
				copySomeData (myBuffer + start1, someData, size1);

			if (size2 > 0)
				copySomeData (myBuffer + start2, someData + size1, size2);

			abstractFifo.finishedWrite (size1 + size2);
		}

		void readFromFifo (int* someData, int numItems)
		{
			int start1, size1, start2, size2;
			abstractFifo.prepareToRead (numSamples, start1, size1, start2, size2);

			if (size1 > 0)
				copySomeData (someData, myBuffer + start1, size1);

			if (size2 > 0)
				copySomeData (someData + size1, myBuffer + start2, size2);

			abstractFifo.finishedRead (size1 + size2);
		}

	private:
		AbstractFifo abstractFifo;
		int myBuffer [1024];
	};
	@endcode
*/
class JUCE_API  AbstractFifo
{
public:

	/** Creates a FIFO to manage a buffer with the specified capacity. */
	AbstractFifo (int capacity) noexcept;

	/** Destructor */
	~AbstractFifo();

	/** Returns the total size of the buffer being managed. */
	int getTotalSize() const noexcept;

	/** Returns the number of items that can currently be added to the buffer without it overflowing. */
	int getFreeSpace() const noexcept;

	/** Returns the number of items that can currently be read from the buffer. */
	int getNumReady() const noexcept;

	/** Clears the buffer positions, so that it appears empty. */
	void reset() noexcept;

	/** Changes the buffer's total size.
		Note that this isn't thread-safe, so don't call it if there's any danger that it
		might overlap with a call to any other method in this class!
	*/
	void setTotalSize (int newSize) noexcept;

	/** Returns the location within the buffer at which an incoming block of data should be written.

		Because the section of data that you want to add to the buffer may overlap the end
		and wrap around to the start, two blocks within your buffer are returned, and you
		should copy your data into the first one, with any remaining data spilling over into
		the second.

		If the number of items you ask for is too large to fit within the buffer's free space, then
		blockSize1 + blockSize2 may add up to a lower value than numToWrite. If this happens, you
		may decide to keep waiting and re-trying the method until there's enough space available.

		After calling this method, if you choose to write your data into the blocks returned, you
		must call finishedWrite() to tell the FIFO how much data you actually added.

		e.g.
		@code
		void addToFifo (const int* someData, int numItems)
		{
			int start1, size1, start2, size2;
			prepareToWrite (numItems, start1, size1, start2, size2);

			if (size1 > 0)
				copySomeData (myBuffer + start1, someData, size1);

			if (size2 > 0)
				copySomeData (myBuffer + start2, someData + size1, size2);

			finishedWrite (size1 + size2);
		}
		@endcode

		@param numToWrite       indicates how many items you'd like to add to the buffer
		@param startIndex1      on exit, this will contain the start index in your buffer at which your data should be written
		@param blockSize1       on exit, this indicates how many items can be written to the block starting at startIndex1
		@param startIndex2      on exit, this will contain the start index in your buffer at which any data that didn't fit into
								the first block should be written
		@param blockSize2       on exit, this indicates how many items can be written to the block starting at startIndex2
		@see finishedWrite
	*/
	void prepareToWrite (int numToWrite, int& startIndex1, int& blockSize1, int& startIndex2, int& blockSize2) const noexcept;

	/** Called after reading from the FIFO, to indicate that this many items have been added.
		@see prepareToWrite
	*/
	void finishedWrite (int numWritten) noexcept;

	/** Returns the location within the buffer from which the next block of data should be read.

		Because the section of data that you want to read from the buffer may overlap the end
		and wrap around to the start, two blocks within your buffer are returned, and you
		should read from both of them.

		If the number of items you ask for is greater than the amount of data available, then
		blockSize1 + blockSize2 may add up to a lower value than numWanted. If this happens, you
		may decide to keep waiting and re-trying the method until there's enough data available.

		After calling this method, if you choose to read the data, you must call finishedRead() to
		tell the FIFO how much data you have consumed.

		e.g.
		@code
		void readFromFifo (int* someData, int numItems)
		{
			int start1, size1, start2, size2;
			prepareToRead (numSamples, start1, size1, start2, size2);

			if (size1 > 0)
				copySomeData (someData, myBuffer + start1, size1);

			if (size2 > 0)
				copySomeData (someData + size1, myBuffer + start2, size2);

			finishedRead (size1 + size2);
		}
		@endcode

		@param numWanted        indicates how many items you'd like to add to the buffer
		@param startIndex1      on exit, this will contain the start index in your buffer at which your data should be written
		@param blockSize1       on exit, this indicates how many items can be written to the block starting at startIndex1
		@param startIndex2      on exit, this will contain the start index in your buffer at which any data that didn't fit into
								the first block should be written
		@param blockSize2       on exit, this indicates how many items can be written to the block starting at startIndex2
		@see finishedRead
	*/
	void prepareToRead (int numWanted, int& startIndex1, int& blockSize1, int& startIndex2, int& blockSize2) const noexcept;

	/** Called after reading from the FIFO, to indicate that this many items have now been consumed.
		@see prepareToRead
	*/
	void finishedRead (int numRead) noexcept;

private:

	int bufferSize;
	Atomic <int> validStart, validEnd;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AbstractFifo);
};

#endif   // __JUCE_ABSTRACTFIFO_JUCEHEADER__

/*** End of inlined file: juce_AbstractFifo.h ***/


#endif
#ifndef __JUCE_ARRAY_JUCEHEADER__

/*** Start of inlined file: juce_Array.h ***/
#ifndef __JUCE_ARRAY_JUCEHEADER__
#define __JUCE_ARRAY_JUCEHEADER__


/*** Start of inlined file: juce_ArrayAllocationBase.h ***/
#ifndef __JUCE_ARRAYALLOCATIONBASE_JUCEHEADER__
#define __JUCE_ARRAYALLOCATIONBASE_JUCEHEADER__


/*** Start of inlined file: juce_HeapBlock.h ***/
#ifndef __JUCE_HEAPBLOCK_JUCEHEADER__
#define __JUCE_HEAPBLOCK_JUCEHEADER__

#ifndef DOXYGEN
namespace HeapBlockHelper
{
	template <bool shouldThrow>
	struct ThrowOnFail          { static void check (void*) {} };

	template<>
	struct ThrowOnFail <true>   { static void check (void* data) { if (data == nullptr) throw std::bad_alloc(); } };
}
#endif

/**
	Very simple container class to hold a pointer to some data on the heap.

	When you need to allocate some heap storage for something, always try to use
	this class instead of allocating the memory directly using malloc/free.

	A HeapBlock<char> object can be treated in pretty much exactly the same way
	as an char*, but as long as you allocate it on the stack or as a class member,
	it's almost impossible for it to leak memory.

	It also makes your code much more concise and readable than doing the same thing
	using direct allocations,

	E.g. instead of this:
	@code
		int* temp = (int*) malloc (1024 * sizeof (int));
		memcpy (temp, xyz, 1024 * sizeof (int));
		free (temp);
		temp = (int*) calloc (2048 * sizeof (int));
		temp[0] = 1234;
		memcpy (foobar, temp, 2048 * sizeof (int));
		free (temp);
	@endcode

	..you could just write this:
	@code
		HeapBlock <int> temp (1024);
		memcpy (temp, xyz, 1024 * sizeof (int));
		temp.calloc (2048);
		temp[0] = 1234;
		memcpy (foobar, temp, 2048 * sizeof (int));
	@endcode

	The class is extremely lightweight, containing only a pointer to the
	data, and exposes malloc/realloc/calloc/free methods that do the same jobs
	as their less object-oriented counterparts. Despite adding safety, you probably
	won't sacrifice any performance by using this in place of normal pointers.

	The throwOnFailure template parameter can be set to true if you'd like the class
	to throw a std::bad_alloc exception when an allocation fails. If this is false,
	then a failed allocation will just leave the heapblock with a null pointer (assuming
	that the system's malloc() function doesn't throw).

	@see Array, OwnedArray, MemoryBlock
*/
template <class ElementType, bool throwOnFailure = false>
class HeapBlock
{
public:

	/** Creates a HeapBlock which is initially just a null pointer.

		After creation, you can resize the array using the malloc(), calloc(),
		or realloc() methods.
	*/
	HeapBlock() noexcept  : data (nullptr)
	{
	}

	/** Creates a HeapBlock containing a number of elements.

		The contents of the block are undefined, as it will have been created by a
		malloc call.

		If you want an array of zero values, you can use the calloc() method instead.
	*/
	explicit HeapBlock (const size_t numElements)
		: data (static_cast <ElementType*> (::malloc (numElements * sizeof (ElementType))))
	{
		throwOnAllocationFailure();
	}

	/** Destructor.

		This will free the data, if any has been allocated.
	*/
	~HeapBlock()
	{
		::free (data);
	}

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	HeapBlock (HeapBlock&& other) noexcept
		: data (other.data)
	{
		other.data = nullptr;
	}

	HeapBlock& operator= (HeapBlock&& other) noexcept
	{
		std::swap (data, other.data);
		return *this;
	}
   #endif

	/** Returns a raw pointer to the allocated data.
		This may be a null pointer if the data hasn't yet been allocated, or if it has been
		freed by calling the free() method.
	*/
	inline operator ElementType*() const noexcept                           { return data; }

	/** Returns a raw pointer to the allocated data.
		This may be a null pointer if the data hasn't yet been allocated, or if it has been
		freed by calling the free() method.
	*/
	inline ElementType* getData() const noexcept                            { return data; }

	/** Returns a void pointer to the allocated data.
		This may be a null pointer if the data hasn't yet been allocated, or if it has been
		freed by calling the free() method.
	*/
	inline operator void*() const noexcept                                  { return static_cast <void*> (data); }

	/** Returns a void pointer to the allocated data.
		This may be a null pointer if the data hasn't yet been allocated, or if it has been
		freed by calling the free() method.
	*/
	inline operator const void*() const noexcept                            { return static_cast <const void*> (data); }

	/** Lets you use indirect calls to the first element in the array.
		Obviously this will cause problems if the array hasn't been initialised, because it'll
		be referencing a null pointer.
	*/
	inline ElementType* operator->() const  noexcept                        { return data; }

	/** Returns a reference to one of the data elements.
		Obviously there's no bounds-checking here, as this object is just a dumb pointer and
		has no idea of the size it currently has allocated.
	*/
	template <typename IndexType>
	inline ElementType& operator[] (IndexType index) const noexcept         { return data [index]; }

	/** Returns a pointer to a data element at an offset from the start of the array.
		This is the same as doing pointer arithmetic on the raw pointer itself.
	*/
	template <typename IndexType>
	inline ElementType* operator+ (IndexType index) const noexcept          { return data + index; }

	/** Compares the pointer with another pointer.
		This can be handy for checking whether this is a null pointer.
	*/
	inline bool operator== (const ElementType* const otherPointer) const noexcept   { return otherPointer == data; }

	/** Compares the pointer with another pointer.
		This can be handy for checking whether this is a null pointer.
	*/
	inline bool operator!= (const ElementType* const otherPointer) const noexcept   { return otherPointer != data; }

	/** Allocates a specified amount of memory.

		This uses the normal malloc to allocate an amount of memory for this object.
		Any previously allocated memory will be freed by this method.

		The number of bytes allocated will be (newNumElements * elementSize). Normally
		you wouldn't need to specify the second parameter, but it can be handy if you need
		to allocate a size in bytes rather than in terms of the number of elements.

		The data that is allocated will be freed when this object is deleted, or when you
		call free() or any of the allocation methods.
	*/
	void malloc (const size_t newNumElements, const size_t elementSize = sizeof (ElementType))
	{
		::free (data);
		data = static_cast <ElementType*> (::malloc (newNumElements * elementSize));
		throwOnAllocationFailure();
	}

	/** Allocates a specified amount of memory and clears it.
		This does the same job as the malloc() method, but clears the memory that it allocates.
	*/
	void calloc (const size_t newNumElements, const size_t elementSize = sizeof (ElementType))
	{
		::free (data);
		data = static_cast <ElementType*> (::calloc (newNumElements, elementSize));
		throwOnAllocationFailure();
	}

	/** Allocates a specified amount of memory and optionally clears it.
		This does the same job as either malloc() or calloc(), depending on the
		initialiseToZero parameter.
	*/
	void allocate (const size_t newNumElements, const bool initialiseToZero)
	{
		::free (data);

		if (initialiseToZero)
			data = static_cast <ElementType*> (::calloc (newNumElements, sizeof (ElementType)));
		else
			data = static_cast <ElementType*> (::malloc (newNumElements * sizeof (ElementType)));

		throwOnAllocationFailure();
	}

	/** Re-allocates a specified amount of memory.

		The semantics of this method are the same as malloc() and calloc(), but it
		uses realloc() to keep as much of the existing data as possible.
	*/
	void realloc (const size_t newNumElements, const size_t elementSize = sizeof (ElementType))
	{
		if (data == nullptr)
			data = static_cast <ElementType*> (::malloc (newNumElements * elementSize));
		else
			data = static_cast <ElementType*> (::realloc (data, newNumElements * elementSize));

		throwOnAllocationFailure();
	}

	/** Frees any currently-allocated data.
		This will free the data and reset this object to be a null pointer.
	*/
	void free()
	{
		::free (data);
		data = nullptr;
	}

	/** Swaps this object's data with the data of another HeapBlock.
		The two objects simply exchange their data pointers.
	*/
	template <bool otherBlockThrows>
	void swapWith (HeapBlock <ElementType, otherBlockThrows>& other) noexcept
	{
		std::swap (data, other.data);
	}

	/** This fills the block with zeros, up to the number of elements specified.
		Since the block has no way of knowing its own size, you must make sure that the number of
		elements you specify doesn't exceed the allocated size.
	*/
	void clear (size_t numElements) noexcept
	{
		zeromem (data, sizeof (ElementType) * numElements);
	}

private:

	ElementType* data;

	void throwOnAllocationFailure() const
	{
		HeapBlockHelper::ThrowOnFail<throwOnFailure>::check (data);
	}

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HeapBlock);

	JUCE_PREVENT_HEAP_ALLOCATION; // Creating a 'new HeapBlock' would be missing the point!
};

#endif   // __JUCE_HEAPBLOCK_JUCEHEADER__

/*** End of inlined file: juce_HeapBlock.h ***/

/**
	Implements some basic array storage allocation functions.

	This class isn't really for public use - it's used by the other
	array classes, but might come in handy for some purposes.

	It inherits from a critical section class to allow the arrays to use
	the "empty base class optimisation" pattern to reduce their footprint.

	@see Array, OwnedArray, ReferenceCountedArray
*/
template <class ElementType, class TypeOfCriticalSectionToUse>
class ArrayAllocationBase  : public TypeOfCriticalSectionToUse
{
public:

	/** Creates an empty array. */
	ArrayAllocationBase() noexcept
		: numAllocated (0)
	{
	}

	/** Destructor. */
	~ArrayAllocationBase() noexcept
	{
	}

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	ArrayAllocationBase (ArrayAllocationBase<ElementType, TypeOfCriticalSectionToUse>&& other) noexcept
		: elements (static_cast <HeapBlock <ElementType>&&> (other.elements)),
		  numAllocated (other.numAllocated)
	{
	}

	ArrayAllocationBase& operator= (ArrayAllocationBase<ElementType, TypeOfCriticalSectionToUse>&& other) noexcept
	{
		elements = static_cast <HeapBlock <ElementType>&&> (other.elements);
		numAllocated = other.numAllocated;
		return *this;
	}
   #endif

	/** Changes the amount of storage allocated.

		This will retain any data currently held in the array, and either add or
		remove extra space at the end.

		@param numElements  the number of elements that are needed
	*/
	void setAllocatedSize (const int numElements)
	{
		if (numAllocated != numElements)
		{
			if (numElements > 0)
				elements.realloc ((size_t) numElements);
			else
				elements.free();

			numAllocated = numElements;
		}
	}

	/** Increases the amount of storage allocated if it is less than a given amount.

		This will retain any data currently held in the array, but will add
		extra space at the end to make sure there it's at least as big as the size
		passed in. If it's already bigger, no action is taken.

		@param minNumElements  the minimum number of elements that are needed
	*/
	void ensureAllocatedSize (const int minNumElements)
	{
		if (minNumElements > numAllocated)
			setAllocatedSize ((minNumElements + minNumElements / 2 + 8) & ~7);
	}

	/** Minimises the amount of storage allocated so that it's no more than
		the given number of elements.
	*/
	void shrinkToNoMoreThan (const int maxNumElements)
	{
		if (maxNumElements < numAllocated)
			setAllocatedSize (maxNumElements);
	}

	/** Swap the contents of two objects. */
	void swapWith (ArrayAllocationBase <ElementType, TypeOfCriticalSectionToUse>& other) noexcept
	{
		elements.swapWith (other.elements);
		std::swap (numAllocated, other.numAllocated);
	}

	HeapBlock <ElementType> elements;
	int numAllocated;

private:
	JUCE_DECLARE_NON_COPYABLE (ArrayAllocationBase);
};

#endif   // __JUCE_ARRAYALLOCATIONBASE_JUCEHEADER__

/*** End of inlined file: juce_ArrayAllocationBase.h ***/


/*** Start of inlined file: juce_ElementComparator.h ***/
#ifndef __JUCE_ELEMENTCOMPARATOR_JUCEHEADER__
#define __JUCE_ELEMENTCOMPARATOR_JUCEHEADER__

/**
	Sorts a range of elements in an array.

	The comparator object that is passed-in must define a public method with the following
	signature:
	@code
	int compareElements (ElementType first, ElementType second);
	@endcode

	..and this method must return:
	  - a value of < 0 if the first comes before the second
	  - a value of 0 if the two objects are equivalent
	  - a value of > 0 if the second comes before the first

	To improve performance, the compareElements() method can be declared as static or const.

	@param comparator       an object which defines a compareElements() method
	@param array            the array to sort
	@param firstElement     the index of the first element of the range to be sorted
	@param lastElement      the index of the last element in the range that needs
							sorting (this is inclusive)
	@param retainOrderOfEquivalentItems     if true, the order of items that the
							comparator deems the same will be maintained - this will be
							a slower algorithm than if they are allowed to be moved around.

	@see sortArrayRetainingOrder
*/
template <class ElementType, class ElementComparator>
static void sortArray (ElementComparator& comparator,
					   ElementType* const array,
					   int firstElement,
					   int lastElement,
					   const bool retainOrderOfEquivalentItems)
{
	(void) comparator;  // if you pass in an object with a static compareElements() method, this
						// avoids getting warning messages about the parameter being unused

	if (lastElement > firstElement)
	{
		if (retainOrderOfEquivalentItems)
		{
			for (int i = firstElement; i < lastElement; ++i)
			{
				if (comparator.compareElements (array[i], array [i + 1]) > 0)
				{
					std::swap (array[i], array[i + 1]);

					if (i > firstElement)
						i -= 2;
				}
			}
		}
		else
		{
			int fromStack[30], toStack[30];
			int stackIndex = 0;

			for (;;)
			{
				const int size = (lastElement - firstElement) + 1;

				if (size <= 8)
				{
					int j = lastElement;
					int maxIndex;

					while (j > firstElement)
					{
						maxIndex = firstElement;
						for (int k = firstElement + 1; k <= j; ++k)
							if (comparator.compareElements (array[k], array [maxIndex]) > 0)
								maxIndex = k;

						std::swap (array[j], array[maxIndex]);
						--j;
					}
				}
				else
				{
					const int mid = firstElement + (size >> 1);
					std::swap (array[mid], array[firstElement]);

					int i = firstElement;
					int j = lastElement + 1;

					for (;;)
					{
						while (++i <= lastElement
								&& comparator.compareElements (array[i], array [firstElement]) <= 0)
						{}

						while (--j > firstElement
								&& comparator.compareElements (array[j], array [firstElement]) >= 0)
						{}

						if (j < i)
							break;

						std::swap (array[i], array[j]);
					}

					std::swap (array[j], array[firstElement]);

					if (j - 1 - firstElement >= lastElement - i)
					{
						if (firstElement + 1 < j)
						{
							fromStack [stackIndex] = firstElement;
							toStack [stackIndex] = j - 1;
							++stackIndex;
						}

						if (i < lastElement)
						{
							firstElement = i;
							continue;
						}
					}
					else
					{
						if (i < lastElement)
						{
							fromStack [stackIndex] = i;
							toStack [stackIndex] = lastElement;
							++stackIndex;
						}

						if (firstElement + 1 < j)
						{
							lastElement = j - 1;
							continue;
						}
					}
				}

				if (--stackIndex < 0)
					break;

				jassert (stackIndex < numElementsInArray (fromStack));

				firstElement = fromStack [stackIndex];
				lastElement = toStack [stackIndex];
			}
		}
	}
}

/**
	Searches a sorted array of elements, looking for the index at which a specified value
	should be inserted for it to be in the correct order.

	The comparator object that is passed-in must define a public method with the following
	signature:
	@code
	int compareElements (ElementType first, ElementType second);
	@endcode

	..and this method must return:
	  - a value of < 0 if the first comes before the second
	  - a value of 0 if the two objects are equivalent
	  - a value of > 0 if the second comes before the first

	To improve performance, the compareElements() method can be declared as static or const.

	@param comparator       an object which defines a compareElements() method
	@param array            the array to search
	@param newElement       the value that is going to be inserted
	@param firstElement     the index of the first element to search
	@param lastElement      the index of the last element in the range (this is non-inclusive)
*/
template <class ElementType, class ElementComparator>
static int findInsertIndexInSortedArray (ElementComparator& comparator,
										 ElementType* const array,
										 const ElementType newElement,
										 int firstElement,
										 int lastElement)
{
	jassert (firstElement <= lastElement);

	(void) comparator;  // if you pass in an object with a static compareElements() method, this
						// avoids getting warning messages about the parameter being unused

	while (firstElement < lastElement)
	{
		if (comparator.compareElements (newElement, array [firstElement]) == 0)
		{
			++firstElement;
			break;
		}
		else
		{
			const int halfway = (firstElement + lastElement) >> 1;

			if (halfway == firstElement)
			{
				if (comparator.compareElements (newElement, array [halfway]) >= 0)
					++firstElement;

				break;
			}
			else if (comparator.compareElements (newElement, array [halfway]) >= 0)
			{
				firstElement = halfway;
			}
			else
			{
				lastElement = halfway;
			}
		}
	}

	return firstElement;
}

/**
	A simple ElementComparator class that can be used to sort an array of
	objects that support the '<' operator.

	This will work for primitive types and objects that implement operator<().

	Example: @code
	Array <int> myArray;
	DefaultElementComparator<int> sorter;
	myArray.sort (sorter);
	@endcode

	@see ElementComparator
*/
template <class ElementType>
class DefaultElementComparator
{
private:
	typedef PARAMETER_TYPE (ElementType) ParameterType;

public:
	static int compareElements (ParameterType first, ParameterType second)
	{
		return (first < second) ? -1 : ((second < first) ? 1 : 0);
	}
};

#endif   // __JUCE_ELEMENTCOMPARATOR_JUCEHEADER__

/*** End of inlined file: juce_ElementComparator.h ***/


/*** Start of inlined file: juce_CriticalSection.h ***/
#ifndef __JUCE_CRITICALSECTION_JUCEHEADER__
#define __JUCE_CRITICALSECTION_JUCEHEADER__


/*** Start of inlined file: juce_ScopedLock.h ***/
#ifndef __JUCE_SCOPEDLOCK_JUCEHEADER__
#define __JUCE_SCOPEDLOCK_JUCEHEADER__

/**
	Automatically locks and unlocks a mutex object.

	Use one of these as a local variable to provide RAII-based locking of a mutex.

	The templated class could be a CriticalSection, SpinLock, or anything else that
	provides enter() and exit() methods.

	e.g. @code
	CriticalSection myCriticalSection;

	for (;;)
	{
		const GenericScopedLock<CriticalSection> myScopedLock (myCriticalSection);
		// myCriticalSection is now locked

		...do some stuff...

		// myCriticalSection gets unlocked here.
	}
	@endcode

	@see GenericScopedUnlock, CriticalSection, SpinLock, ScopedLock, ScopedUnlock
*/
template <class LockType>
class GenericScopedLock
{
public:

	/** Creates a GenericScopedLock.

		As soon as it is created, this will acquire the lock, and when the GenericScopedLock
		object is deleted, the lock will be released.

		Make sure this object is created and deleted by the same thread,
		otherwise there are no guarantees what will happen! Best just to use it
		as a local stack object, rather than creating one with the new() operator.
	*/
	inline explicit GenericScopedLock (const LockType& lock) noexcept : lock_ (lock)     { lock.enter(); }

	/** Destructor.
		The lock will be released when the destructor is called.
		Make sure this object is created and deleted by the same thread, otherwise there are
		no guarantees what will happen!
	*/
	inline ~GenericScopedLock() noexcept                                                 { lock_.exit(); }

private:

	const LockType& lock_;

	JUCE_DECLARE_NON_COPYABLE (GenericScopedLock);
};

/**
	Automatically unlocks and re-locks a mutex object.

	This is the reverse of a GenericScopedLock object - instead of locking the mutex
	for the lifetime of this object, it unlocks it.

	Make sure you don't try to unlock mutexes that aren't actually locked!

	e.g. @code

	CriticalSection myCriticalSection;

	for (;;)
	{
		const GenericScopedLock<CriticalSection> myScopedLock (myCriticalSection);
		// myCriticalSection is now locked

		... do some stuff with it locked ..

		while (xyz)
		{
			... do some stuff with it locked ..

			const GenericScopedUnlock<CriticalSection> unlocker (myCriticalSection);

			// myCriticalSection is now unlocked for the remainder of this block,
			// and re-locked at the end.

			...do some stuff with it unlocked ...
		}

		// myCriticalSection gets unlocked here.
	}
	@endcode

	@see GenericScopedLock, CriticalSection, ScopedLock, ScopedUnlock
*/
template <class LockType>
class GenericScopedUnlock
{
public:

	/** Creates a GenericScopedUnlock.

		As soon as it is created, this will unlock the CriticalSection, and
		when the ScopedLock object is deleted, the CriticalSection will
		be re-locked.

		Make sure this object is created and deleted by the same thread,
		otherwise there are no guarantees what will happen! Best just to use it
		as a local stack object, rather than creating one with the new() operator.
	*/
	inline explicit GenericScopedUnlock (const LockType& lock) noexcept : lock_ (lock)   { lock.exit(); }

	/** Destructor.

		The CriticalSection will be unlocked when the destructor is called.

		Make sure this object is created and deleted by the same thread,
		otherwise there are no guarantees what will happen!
	*/
	inline ~GenericScopedUnlock() noexcept                                               { lock_.enter(); }

private:

	const LockType& lock_;

	JUCE_DECLARE_NON_COPYABLE (GenericScopedUnlock);
};

/**
	Automatically locks and unlocks a mutex object.

	Use one of these as a local variable to provide RAII-based locking of a mutex.

	The templated class could be a CriticalSection, SpinLock, or anything else that
	provides enter() and exit() methods.

	e.g. @code

	CriticalSection myCriticalSection;

	for (;;)
	{
		const GenericScopedTryLock<CriticalSection> myScopedTryLock (myCriticalSection);

		// Unlike using a ScopedLock, this may fail to actually get the lock, so you
		// should test this with the isLocked() method before doing your thread-unsafe
		// action..
		if (myScopedTryLock.isLocked())
		{
		   ...do some stuff...
		}
		else
		{
			..our attempt at locking failed because another thread had already locked it..
		}

		// myCriticalSection gets unlocked here (if it was locked)
	}
	@endcode

	@see CriticalSection::tryEnter, GenericScopedLock, GenericScopedUnlock
*/
template <class LockType>
class GenericScopedTryLock
{
public:

	/** Creates a GenericScopedTryLock.

		As soon as it is created, this will attempt to acquire the lock, and when the
		GenericScopedTryLock is deleted, the lock will be released (if the lock was
		successfully acquired).

		Make sure this object is created and deleted by the same thread,
		otherwise there are no guarantees what will happen! Best just to use it
		as a local stack object, rather than creating one with the new() operator.
	*/
	inline explicit GenericScopedTryLock (const LockType& lock) noexcept
		: lock_ (lock), lockWasSuccessful (lock.tryEnter()) {}

	/** Destructor.

		The mutex will be unlocked (if it had been successfully locked) when the
		destructor is called.

		Make sure this object is created and deleted by the same thread,
		otherwise there are no guarantees what will happen!
	*/
	inline ~GenericScopedTryLock() noexcept         { if (lockWasSuccessful) lock_.exit(); }

	/** Returns true if the mutex was successfully locked. */
	bool isLocked() const noexcept                  { return lockWasSuccessful; }

private:

	const LockType& lock_;
	const bool lockWasSuccessful;

	JUCE_DECLARE_NON_COPYABLE (GenericScopedTryLock);
};

#endif   // __JUCE_SCOPEDLOCK_JUCEHEADER__

/*** End of inlined file: juce_ScopedLock.h ***/

/**
	A mutex class.

	A CriticalSection acts as a re-entrant mutex lock. The best way to lock and unlock
	one of these is by using RAII in the form of a local ScopedLock object - have a look
	through the codebase for many examples of how to do this.

	@see ScopedLock, ScopedTryLock, ScopedUnlock, SpinLock, ReadWriteLock, Thread, InterProcessLock
*/
class JUCE_API  CriticalSection
{
public:

	/** Creates a CriticalSection object. */
	CriticalSection() noexcept;

	/** Destructor.
		If the critical section is deleted whilst locked, any subsequent behaviour
		is unpredictable.
	*/
	~CriticalSection() noexcept;

	/** Acquires the lock.

		If the lock is already held by the caller thread, the method returns immediately.
		If the lock is currently held by another thread, this will wait until it becomes free.

		It's strongly recommended that you never call this method directly - instead use the
		ScopedLock class to manage the locking using an RAII pattern instead.

		@see exit, tryEnter, ScopedLock
	*/
	void enter() const noexcept;

	/** Attempts to lock this critical section without blocking.

		This method behaves identically to CriticalSection::enter, except that the caller thread
		does not wait if the lock is currently held by another thread but returns false immediately.

		@returns false if the lock is currently held by another thread, true otherwise.
		@see enter
	*/
	bool tryEnter() const noexcept;

	/** Releases the lock.

		If the caller thread hasn't got the lock, this can have unpredictable results.

		If the enter() method has been called multiple times by the thread, each
		call must be matched by a call to exit() before other threads will be allowed
		to take over the lock.

		@see enter, ScopedLock
	*/
	void exit() const noexcept;

	/** Provides the type of scoped lock to use with a CriticalSection. */
	typedef GenericScopedLock <CriticalSection>       ScopedLockType;

	/** Provides the type of scoped unlocker to use with a CriticalSection. */
	typedef GenericScopedUnlock <CriticalSection>     ScopedUnlockType;

	/** Provides the type of scoped try-locker to use with a CriticalSection. */
	typedef GenericScopedTryLock <CriticalSection>    ScopedTryLockType;

private:

   #if JUCE_WINDOWS
	// To avoid including windows.h in the public JUCE headers, we'll just allocate a
	// block of memory here that's big enough to be used internally as a windows critical
	// section structure.
	#if JUCE_64BIT
	 uint8 internal [44];
	#else
	 uint8 internal [24];
	#endif
   #else
	mutable pthread_mutex_t internal;
   #endif

	JUCE_DECLARE_NON_COPYABLE (CriticalSection);
};

/**
	A class that can be used in place of a real CriticalSection object, but which
	doesn't perform any locking.

	This is currently used by some templated classes, and most compilers should
	manage to optimise it out of existence.

	@see CriticalSection, Array, OwnedArray, ReferenceCountedArray
*/
class JUCE_API  DummyCriticalSection
{
public:
	inline DummyCriticalSection() noexcept      {}
	inline ~DummyCriticalSection() noexcept     {}

	inline void enter() const noexcept          {}
	inline bool tryEnter() const noexcept       { return true; }
	inline void exit() const noexcept           {}

	/** A dummy scoped-lock type to use with a dummy critical section. */
	struct ScopedLockType
	{
		ScopedLockType (const DummyCriticalSection&) noexcept {}
	};

	/** A dummy scoped-unlocker type to use with a dummy critical section. */
	typedef ScopedLockType ScopedUnlockType;

private:
	JUCE_DECLARE_NON_COPYABLE (DummyCriticalSection);
};

/**
	Automatically locks and unlocks a CriticalSection object.

	Use one of these as a local variable to provide RAII-based locking of a CriticalSection.

	e.g. @code

	CriticalSection myCriticalSection;

	for (;;)
	{
		const ScopedLock myScopedLock (myCriticalSection);
		// myCriticalSection is now locked

		...do some stuff...

		// myCriticalSection gets unlocked here.
	}
	@endcode

	@see CriticalSection, ScopedUnlock
*/
typedef CriticalSection::ScopedLockType  ScopedLock;

/**
	Automatically unlocks and re-locks a CriticalSection object.

	This is the reverse of a ScopedLock object - instead of locking the critical
	section for the lifetime of this object, it unlocks it.

	Make sure you don't try to unlock critical sections that aren't actually locked!

	e.g. @code

	CriticalSection myCriticalSection;

	for (;;)
	{
		const ScopedLock myScopedLock (myCriticalSection);
		// myCriticalSection is now locked

		... do some stuff with it locked ..

		while (xyz)
		{
			... do some stuff with it locked ..

			const ScopedUnlock unlocker (myCriticalSection);

			// myCriticalSection is now unlocked for the remainder of this block,
			// and re-locked at the end.

			...do some stuff with it unlocked ...
		}

		// myCriticalSection gets unlocked here.
	}
	@endcode

	@see CriticalSection, ScopedLock
*/
typedef CriticalSection::ScopedUnlockType  ScopedUnlock;

/**
	Automatically tries to lock and unlock a CriticalSection object.

	Use one of these as a local variable to control access to a CriticalSection.

	e.g. @code
	CriticalSection myCriticalSection;

	for (;;)
	{
		const ScopedTryLock myScopedTryLock (myCriticalSection);

		// Unlike using a ScopedLock, this may fail to actually get the lock, so you
		// should test this with the isLocked() method before doing your thread-unsafe
		// action..
		if (myScopedTryLock.isLocked())
		{
		   ...do some stuff...
		}
		else
		{
			..our attempt at locking failed because another thread had already locked it..
		}

		// myCriticalSection gets unlocked here (if it was locked)
	}
	@endcode

	@see CriticalSection::tryEnter, ScopedLock, ScopedUnlock, ScopedReadLock
*/
typedef CriticalSection::ScopedTryLockType  ScopedTryLock;

#endif   // __JUCE_CRITICALSECTION_JUCEHEADER__

/*** End of inlined file: juce_CriticalSection.h ***/

/**
	Holds a resizable array of primitive or copy-by-value objects.

	Examples of arrays are: Array<int>, Array<Rectangle> or Array<MyClass*>

	The Array class can be used to hold simple, non-polymorphic objects as well as primitive types - to
	do so, the class must fulfil these requirements:
	- it must have a copy constructor and assignment operator
	- it must be able to be relocated in memory by a memcpy without this causing any problems - so
	  objects whose functionality relies on external pointers or references to themselves can be used.

	You can of course have an array of pointers to any kind of object, e.g. Array <MyClass*>, but if
	you do this, the array doesn't take any ownership of the objects - see the OwnedArray class or the
	ReferenceCountedArray class for more powerful ways of holding lists of objects.

	For holding lists of strings, you can use Array\<String\>, but it's usually better to use the
	specialised class StringArray, which provides more useful functions.

	To make all the array's methods thread-safe, pass in "CriticalSection" as the templated
	TypeOfCriticalSectionToUse parameter, instead of the default DummyCriticalSection.

	@see OwnedArray, ReferenceCountedArray, StringArray, CriticalSection
*/
template <typename ElementType,
		  typename TypeOfCriticalSectionToUse = DummyCriticalSection>
class Array
{
private:
	typedef PARAMETER_TYPE (ElementType) ParameterType;

public:

	/** Creates an empty array. */
	Array() noexcept
	   : numUsed (0)
	{
	}

	/** Creates a copy of another array.
		@param other    the array to copy
	*/
	Array (const Array<ElementType, TypeOfCriticalSectionToUse>& other)
	{
		const ScopedLockType lock (other.getLock());
		numUsed = other.numUsed;
		data.setAllocatedSize (other.numUsed);

		for (int i = 0; i < numUsed; ++i)
			new (data.elements + i) ElementType (other.data.elements[i]);
	}

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	Array (Array<ElementType, TypeOfCriticalSectionToUse>&& other) noexcept
		: data (static_cast <ArrayAllocationBase<ElementType, TypeOfCriticalSectionToUse>&&> (other.data)),
		  numUsed (other.numUsed)
	{
		other.numUsed = 0;
	}
   #endif

	/** Initalises from a null-terminated C array of values.

		@param values   the array to copy from
	*/
	template <typename TypeToCreateFrom>
	explicit Array (const TypeToCreateFrom* values)
	   : numUsed (0)
	{
		while (*values != TypeToCreateFrom())
			add (*values++);
	}

	/** Initalises from a C array of values.

		@param values       the array to copy from
		@param numValues    the number of values in the array
	*/
	template <typename TypeToCreateFrom>
	Array (const TypeToCreateFrom* values, int numValues)
	   : numUsed (numValues)
	{
		data.setAllocatedSize (numValues);

		for (int i = 0; i < numValues; ++i)
			new (data.elements + i) ElementType (values[i]);
	}

	/** Destructor. */
	~Array()
	{
		deleteAllElements();
	}

	/** Copies another array.
		@param other    the array to copy
	*/
	Array& operator= (const Array& other)
	{
		if (this != &other)
		{
			Array<ElementType, TypeOfCriticalSectionToUse> otherCopy (other);
			swapWithArray (otherCopy);
		}

		return *this;
	}

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	Array& operator= (Array&& other) noexcept
	{
		data = static_cast <ArrayAllocationBase<ElementType, TypeOfCriticalSectionToUse>&&> (other.data);
		numUsed = other.numUsed;
		other.numUsed = 0;
		return *this;
	}
   #endif

	/** Compares this array to another one.
		Two arrays are considered equal if they both contain the same set of
		elements, in the same order.
		@param other    the other array to compare with
	*/
	template <class OtherArrayType>
	bool operator== (const OtherArrayType& other) const
	{
		const ScopedLockType lock (getLock());
		const typename OtherArrayType::ScopedLockType lock2 (other.getLock());

		if (numUsed != other.numUsed)
			return false;

		for (int i = numUsed; --i >= 0;)
			if (! (data.elements [i] == other.data.elements [i]))
				return false;

		return true;
	}

	/** Compares this array to another one.
		Two arrays are considered equal if they both contain the same set of
		elements, in the same order.
		@param other    the other array to compare with
	*/
	template <class OtherArrayType>
	bool operator!= (const OtherArrayType& other) const
	{
		return ! operator== (other);
	}

	/** Removes all elements from the array.
		This will remove all the elements, and free any storage that the array is
		using. To clear the array without freeing the storage, use the clearQuick()
		method instead.

		@see clearQuick
	*/
	void clear()
	{
		const ScopedLockType lock (getLock());
		deleteAllElements();
		data.setAllocatedSize (0);
		numUsed = 0;
	}

	/** Removes all elements from the array without freeing the array's allocated storage.

		@see clear
	*/
	void clearQuick()
	{
		const ScopedLockType lock (getLock());
		deleteAllElements();
		numUsed = 0;
	}

	/** Returns the current number of elements in the array.
	*/
	inline int size() const noexcept
	{
		return numUsed;
	}

	/** Returns one of the elements in the array.
		If the index passed in is beyond the range of valid elements, this
		will return zero.

		If you're certain that the index will always be a valid element, you
		can call getUnchecked() instead, which is faster.

		@param index    the index of the element being requested (0 is the first element in the array)
		@see getUnchecked, getFirst, getLast
	*/
	ElementType operator[] (const int index) const
	{
		const ScopedLockType lock (getLock());
		return isPositiveAndBelow (index, numUsed) ? data.elements [index]
												   : ElementType();
	}

	/** Returns one of the elements in the array, without checking the index passed in.

		Unlike the operator[] method, this will try to return an element without
		checking that the index is within the bounds of the array, so should only
		be used when you're confident that it will always be a valid index.

		@param index    the index of the element being requested (0 is the first element in the array)
		@see operator[], getFirst, getLast
	*/
	inline ElementType getUnchecked (const int index) const
	{
		const ScopedLockType lock (getLock());
		jassert (isPositiveAndBelow (index, numUsed));
		return data.elements [index];
	}

	/** Returns a direct reference to one of the elements in the array, without checking the index passed in.

		This is like getUnchecked, but returns a direct reference to the element, so that
		you can alter it directly. Obviously this can be dangerous, so only use it when
		absolutely necessary.

		@param index    the index of the element being requested (0 is the first element in the array)
		@see operator[], getFirst, getLast
	*/
	inline ElementType& getReference (const int index) const noexcept
	{
		const ScopedLockType lock (getLock());
		jassert (isPositiveAndBelow (index, numUsed));
		return data.elements [index];
	}

	/** Returns the first element in the array, or 0 if the array is empty.

		@see operator[], getUnchecked, getLast
	*/
	inline ElementType getFirst() const
	{
		const ScopedLockType lock (getLock());
		return (numUsed > 0) ? data.elements [0]
							 : ElementType();
	}

	/** Returns the last element in the array, or 0 if the array is empty.

		@see operator[], getUnchecked, getFirst
	*/
	inline ElementType getLast() const
	{
		const ScopedLockType lock (getLock());
		return (numUsed > 0) ? data.elements [numUsed - 1]
							 : ElementType();
	}

	/** Returns a pointer to the actual array data.
		This pointer will only be valid until the next time a non-const method
		is called on the array.
	*/
	inline ElementType* getRawDataPointer() noexcept
	{
		return data.elements;
	}

	/** Returns a pointer to the first element in the array.
		This method is provided for compatibility with standard C++ iteration mechanisms.
	*/
	inline ElementType* begin() const noexcept
	{
		return data.elements;
	}

	/** Returns a pointer to the element which follows the last element in the array.
		This method is provided for compatibility with standard C++ iteration mechanisms.
	*/
	inline ElementType* end() const noexcept
	{
		return data.elements + numUsed;
	}

	/** Finds the index of the first element which matches the value passed in.

		This will search the array for the given object, and return the index
		of its first occurrence. If the object isn't found, the method will return -1.

		@param elementToLookFor   the value or object to look for
		@returns                  the index of the object, or -1 if it's not found
	*/
	int indexOf (ParameterType elementToLookFor) const
	{
		const ScopedLockType lock (getLock());
		const ElementType* e = data.elements.getData();
		const ElementType* const end_ = e + numUsed;

		for (; e != end_; ++e)
			if (elementToLookFor == *e)
				return static_cast <int> (e - data.elements.getData());

		return -1;
	}

	/** Returns true if the array contains at least one occurrence of an object.

		@param elementToLookFor     the value or object to look for
		@returns                    true if the item is found
	*/
	bool contains (ParameterType elementToLookFor) const
	{
		const ScopedLockType lock (getLock());
		const ElementType* e = data.elements.getData();
		const ElementType* const end_ = e + numUsed;

		for (; e != end_; ++e)
			if (elementToLookFor == *e)
				return true;

		return false;
	}

	/** Appends a new element at the end of the array.

		@param newElement       the new object to add to the array
		@see set, insert, addIfNotAlreadyThere, addSorted, addUsingDefaultSort, addArray
	*/
	void add (ParameterType newElement)
	{
		const ScopedLockType lock (getLock());
		data.ensureAllocatedSize (numUsed + 1);
		new (data.elements + numUsed++) ElementType (newElement);
	}

	/** Inserts a new element into the array at a given position.

		If the index is less than 0 or greater than the size of the array, the
		element will be added to the end of the array.
		Otherwise, it will be inserted into the array, moving all the later elements
		along to make room.

		@param indexToInsertAt    the index at which the new element should be
								  inserted (pass in -1 to add it to the end)
		@param newElement         the new object to add to the array
		@see add, addSorted, addUsingDefaultSort, set
	*/
	void insert (int indexToInsertAt, ParameterType newElement)
	{
		const ScopedLockType lock (getLock());
		data.ensureAllocatedSize (numUsed + 1);

		if (isPositiveAndBelow (indexToInsertAt, numUsed))
		{
			ElementType* const insertPos = data.elements + indexToInsertAt;
			const int numberToMove = numUsed - indexToInsertAt;

			if (numberToMove > 0)
				memmove (insertPos + 1, insertPos, numberToMove * sizeof (ElementType));

			new (insertPos) ElementType (newElement);
			++numUsed;
		}
		else
		{
			new (data.elements + numUsed++) ElementType (newElement);
		}
	}

	/** Inserts multiple copies of an element into the array at a given position.

		If the index is less than 0 or greater than the size of the array, the
		element will be added to the end of the array.
		Otherwise, it will be inserted into the array, moving all the later elements
		along to make room.

		@param indexToInsertAt    the index at which the new element should be inserted
		@param newElement         the new object to add to the array
		@param numberOfTimesToInsertIt  how many copies of the value to insert
		@see insert, add, addSorted, set
	*/
	void insertMultiple (int indexToInsertAt, ParameterType newElement,
						 int numberOfTimesToInsertIt)
	{
		if (numberOfTimesToInsertIt > 0)
		{
			const ScopedLockType lock (getLock());
			data.ensureAllocatedSize (numUsed + numberOfTimesToInsertIt);
			ElementType* insertPos;

			if (isPositiveAndBelow (indexToInsertAt, numUsed))
			{
				insertPos = data.elements + indexToInsertAt;
				const int numberToMove = numUsed - indexToInsertAt;
				memmove (insertPos + numberOfTimesToInsertIt, insertPos, numberToMove * sizeof (ElementType));
			}
			else
			{
				insertPos = data.elements + numUsed;
			}

			numUsed += numberOfTimesToInsertIt;

			while (--numberOfTimesToInsertIt >= 0)
				new (insertPos++) ElementType (newElement);
		}
	}

	/** Inserts an array of values into this array at a given position.

		If the index is less than 0 or greater than the size of the array, the
		new elements will be added to the end of the array.
		Otherwise, they will be inserted into the array, moving all the later elements
		along to make room.

		@param indexToInsertAt      the index at which the first new element should be inserted
		@param newElements          the new values to add to the array
		@param numberOfElements     how many items are in the array
		@see insert, add, addSorted, set
	*/
	void insertArray (int indexToInsertAt,
					  const ElementType* newElements,
					  int numberOfElements)
	{
		if (numberOfElements > 0)
		{
			const ScopedLockType lock (getLock());
			data.ensureAllocatedSize (numUsed + numberOfElements);
			ElementType* insertPos;

			if (isPositiveAndBelow (indexToInsertAt, numUsed))
			{
				insertPos = data.elements + indexToInsertAt;
				const int numberToMove = numUsed - indexToInsertAt;
				memmove (insertPos + numberOfElements, insertPos, numberToMove * sizeof (ElementType));
			}
			else
			{
				insertPos = data.elements + numUsed;
			}

			numUsed += numberOfElements;

			while (--numberOfElements >= 0)
				new (insertPos++) ElementType (*newElements++);
		}
	}

	/** Appends a new element at the end of the array as long as the array doesn't
		already contain it.

		If the array already contains an element that matches the one passed in, nothing
		will be done.

		@param newElement   the new object to add to the array
	*/
	void addIfNotAlreadyThere (ParameterType newElement)
	{
		const ScopedLockType lock (getLock());

		if (! contains (newElement))
			add (newElement);
	}

	/** Replaces an element with a new value.

		If the index is less than zero, this method does nothing.
		If the index is beyond the end of the array, the item is added to the end of the array.

		@param indexToChange    the index whose value you want to change
		@param newValue         the new value to set for this index.
		@see add, insert
	*/
	void set (const int indexToChange, ParameterType newValue)
	{
		jassert (indexToChange >= 0);
		const ScopedLockType lock (getLock());

		if (isPositiveAndBelow (indexToChange, numUsed))
		{
			data.elements [indexToChange] = newValue;
		}
		else if (indexToChange >= 0)
		{
			data.ensureAllocatedSize (numUsed + 1);
			new (data.elements + numUsed++) ElementType (newValue);
		}
	}

	/** Replaces an element with a new value without doing any bounds-checking.

		This just sets a value directly in the array's internal storage, so you'd
		better make sure it's in range!

		@param indexToChange    the index whose value you want to change
		@param newValue         the new value to set for this index.
		@see set, getUnchecked
	*/
	void setUnchecked (const int indexToChange, ParameterType newValue)
	{
		const ScopedLockType lock (getLock());
		jassert (isPositiveAndBelow (indexToChange, numUsed));
		data.elements [indexToChange] = newValue;
	}

	/** Adds elements from an array to the end of this array.

		@param elementsToAdd        the array of elements to add
		@param numElementsToAdd     how many elements are in this other array
		@see add
	*/
	void addArray (const ElementType* elementsToAdd, int numElementsToAdd)
	{
		const ScopedLockType lock (getLock());

		if (numElementsToAdd > 0)
		{
			data.ensureAllocatedSize (numUsed + numElementsToAdd);

			while (--numElementsToAdd >= 0)
			{
				new (data.elements + numUsed) ElementType (*elementsToAdd++);
				++numUsed;
			}
		}
	}

	/** This swaps the contents of this array with those of another array.

		If you need to exchange two arrays, this is vastly quicker than using copy-by-value
		because it just swaps their internal pointers.
	*/
	void swapWithArray (Array& otherArray) noexcept
	{
		const ScopedLockType lock1 (getLock());
		const ScopedLockType lock2 (otherArray.getLock());

		data.swapWith (otherArray.data);
		swapVariables (numUsed, otherArray.numUsed);
	}

	/** Adds elements from another array to the end of this array.

		@param arrayToAddFrom       the array from which to copy the elements
		@param startIndex           the first element of the other array to start copying from
		@param numElementsToAdd     how many elements to add from the other array. If this
									value is negative or greater than the number of available elements,
									all available elements will be copied.
		@see add
	*/
	template <class OtherArrayType>
	void addArray (const OtherArrayType& arrayToAddFrom,
				   int startIndex = 0,
				   int numElementsToAdd = -1)
	{
		const typename OtherArrayType::ScopedLockType lock1 (arrayToAddFrom.getLock());

		{
			const ScopedLockType lock2 (getLock());

			if (startIndex < 0)
			{
				jassertfalse;
				startIndex = 0;
			}

			if (numElementsToAdd < 0 || startIndex + numElementsToAdd > arrayToAddFrom.size())
				numElementsToAdd = arrayToAddFrom.size() - startIndex;

			while (--numElementsToAdd >= 0)
				add (arrayToAddFrom.getUnchecked (startIndex++));
		}
	}

	/** This will enlarge or shrink the array to the given number of elements, by adding
		or removing items from its end.

		If the array is smaller than the given target size, empty elements will be appended
		until its size is as specified. If its size is larger than the target, items will be
		removed from its end to shorten it.
	*/
	void resize (const int targetNumItems)
	{
		jassert (targetNumItems >= 0);

		const int numToAdd = targetNumItems - numUsed;
		if (numToAdd > 0)
			insertMultiple (numUsed, ElementType(), numToAdd);
		else if (numToAdd < 0)
			removeRange (targetNumItems, -numToAdd);
	}

	/** Inserts a new element into the array, assuming that the array is sorted.

		This will use a comparator to find the position at which the new element
		should go. If the array isn't sorted, the behaviour of this
		method will be unpredictable.

		@param comparator   the comparator to use to compare the elements - see the sort()
							method for details about the form this object should take
		@param newElement   the new element to insert to the array
		@returns the index at which the new item was added
		@see addUsingDefaultSort, add, sort
	*/
	template <class ElementComparator>
	int addSorted (ElementComparator& comparator, ParameterType newElement)
	{
		const ScopedLockType lock (getLock());
		const int index = findInsertIndexInSortedArray (comparator, data.elements.getData(), newElement, 0, numUsed);
		insert (index, newElement);
		return index;
	}

	/** Inserts a new element into the array, assuming that the array is sorted.

		This will use the DefaultElementComparator class for sorting, so your ElementType
		must be suitable for use with that class. If the array isn't sorted, the behaviour of this
		method will be unpredictable.

		@param newElement   the new element to insert to the array
		@see addSorted, sort
	*/
	void addUsingDefaultSort (ParameterType newElement)
	{
		DefaultElementComparator <ElementType> comparator;
		addSorted (comparator, newElement);
	}

	/** Finds the index of an element in the array, assuming that the array is sorted.

		This will use a comparator to do a binary-chop to find the index of the given
		element, if it exists. If the array isn't sorted, the behaviour of this
		method will be unpredictable.

		@param comparator           the comparator to use to compare the elements - see the sort()
									method for details about the form this object should take
		@param elementToLookFor     the element to search for
		@returns                    the index of the element, or -1 if it's not found
		@see addSorted, sort
	*/
	template <class ElementComparator>
	int indexOfSorted (ElementComparator& comparator, ParameterType elementToLookFor) const
	{
		(void) comparator;  // if you pass in an object with a static compareElements() method, this
							// avoids getting warning messages about the parameter being unused

		const ScopedLockType lock (getLock());
		int start = 0;
		int end_ = numUsed;

		for (;;)
		{
			if (start >= end_)
			{
				return -1;
			}
			else if (comparator.compareElements (elementToLookFor, data.elements [start]) == 0)
			{
				return start;
			}
			else
			{
				const int halfway = (start + end_) >> 1;

				if (halfway == start)
					return -1;
				else if (comparator.compareElements (elementToLookFor, data.elements [halfway]) >= 0)
					start = halfway;
				else
					end_ = halfway;
			}
		}
	}

	/** Removes an element from the array.

		This will remove the element at a given index, and move back
		all the subsequent elements to close the gap.
		If the index passed in is out-of-range, nothing will happen.

		@param indexToRemove    the index of the element to remove
		@returns                the element that has been removed
		@see removeValue, removeRange
	*/
	ElementType remove (const int indexToRemove)
	{
		const ScopedLockType lock (getLock());

		if (isPositiveAndBelow (indexToRemove, numUsed))
		{
			--numUsed;

			ElementType* const e = data.elements + indexToRemove;
			ElementType removed (*e);
			e->~ElementType();
			const int numberToShift = numUsed - indexToRemove;

			if (numberToShift > 0)
				memmove (e, e + 1, numberToShift * sizeof (ElementType));

			if ((numUsed << 1) < data.numAllocated)
				minimiseStorageOverheads();

			return removed;
		}
		else
		{
			return ElementType();
		}
	}

	/** Removes an item from the array.

		This will remove the first occurrence of the given element from the array.
		If the item isn't found, no action is taken.

		@param valueToRemove   the object to try to remove
		@see remove, removeRange
	*/
	void removeValue (ParameterType valueToRemove)
	{
		const ScopedLockType lock (getLock());
		ElementType* const e = data.elements;

		for (int i = 0; i < numUsed; ++i)
		{
			if (valueToRemove == e[i])
			{
				remove (i);
				break;
			}
		}
	}

	/** Removes a range of elements from the array.

		This will remove a set of elements, starting from the given index,
		and move subsequent elements down to close the gap.

		If the range extends beyond the bounds of the array, it will
		be safely clipped to the size of the array.

		@param startIndex       the index of the first element to remove
		@param numberToRemove   how many elements should be removed
		@see remove, removeValue
	*/
	void removeRange (int startIndex, int numberToRemove)
	{
		const ScopedLockType lock (getLock());
		const int endIndex = jlimit (0, numUsed, startIndex + numberToRemove);
		startIndex = jlimit (0, numUsed, startIndex);

		if (endIndex > startIndex)
		{
			ElementType* const e = data.elements + startIndex;

			numberToRemove = endIndex - startIndex;
			for (int i = 0; i < numberToRemove; ++i)
				e[i].~ElementType();

			const int numToShift = numUsed - endIndex;
			if (numToShift > 0)
				memmove (e, e + numberToRemove, numToShift * sizeof (ElementType));

			numUsed -= numberToRemove;

			if ((numUsed << 1) < data.numAllocated)
				minimiseStorageOverheads();
		}
	}

	/** Removes the last n elements from the array.

		@param howManyToRemove   how many elements to remove from the end of the array
		@see remove, removeValue, removeRange
	*/
	void removeLast (int howManyToRemove = 1)
	{
		const ScopedLockType lock (getLock());

		if (howManyToRemove > numUsed)
			howManyToRemove = numUsed;

		for (int i = 1; i <= howManyToRemove; ++i)
			data.elements [numUsed - i].~ElementType();

		numUsed -= howManyToRemove;

		if ((numUsed << 1) < data.numAllocated)
			minimiseStorageOverheads();
	}

	/** Removes any elements which are also in another array.

		@param otherArray   the other array in which to look for elements to remove
		@see removeValuesNotIn, remove, removeValue, removeRange
	*/
	template <class OtherArrayType>
	void removeValuesIn (const OtherArrayType& otherArray)
	{
		const typename OtherArrayType::ScopedLockType lock1 (otherArray.getLock());
		const ScopedLockType lock2 (getLock());

		if (this == &otherArray)
		{
			clear();
		}
		else
		{
			if (otherArray.size() > 0)
			{
				for (int i = numUsed; --i >= 0;)
					if (otherArray.contains (data.elements [i]))
						remove (i);
			}
		}
	}

	/** Removes any elements which are not found in another array.

		Only elements which occur in this other array will be retained.

		@param otherArray    the array in which to look for elements NOT to remove
		@see removeValuesIn, remove, removeValue, removeRange
	*/
	template <class OtherArrayType>
	void removeValuesNotIn (const OtherArrayType& otherArray)
	{
		const typename OtherArrayType::ScopedLockType lock1 (otherArray.getLock());
		const ScopedLockType lock2 (getLock());

		if (this != &otherArray)
		{
			if (otherArray.size() <= 0)
			{
				clear();
			}
			else
			{
				for (int i = numUsed; --i >= 0;)
					if (! otherArray.contains (data.elements [i]))
						remove (i);
			}
		}
	}

	/** Swaps over two elements in the array.

		This swaps over the elements found at the two indexes passed in.
		If either index is out-of-range, this method will do nothing.

		@param index1   index of one of the elements to swap
		@param index2   index of the other element to swap
	*/
	void swap (const int index1,
			   const int index2)
	{
		const ScopedLockType lock (getLock());

		if (isPositiveAndBelow (index1, numUsed)
			 && isPositiveAndBelow (index2, numUsed))
		{
			swapVariables (data.elements [index1],
						   data.elements [index2]);
		}
	}

	/** Moves one of the values to a different position.

		This will move the value to a specified index, shuffling along
		any intervening elements as required.

		So for example, if you have the array { 0, 1, 2, 3, 4, 5 } then calling
		move (2, 4) would result in { 0, 1, 3, 4, 2, 5 }.

		@param currentIndex     the index of the value to be moved. If this isn't a
								valid index, then nothing will be done
		@param newIndex         the index at which you'd like this value to end up. If this
								is less than zero, the value will be moved to the end
								of the array
	*/
	void move (const int currentIndex, int newIndex) noexcept
	{
		if (currentIndex != newIndex)
		{
			const ScopedLockType lock (getLock());

			if (isPositiveAndBelow (currentIndex, numUsed))
			{
				if (! isPositiveAndBelow (newIndex, numUsed))
					newIndex = numUsed - 1;

				char tempCopy [sizeof (ElementType)];
				memcpy (tempCopy, data.elements + currentIndex, sizeof (ElementType));

				if (newIndex > currentIndex)
				{
					memmove (data.elements + currentIndex,
							 data.elements + currentIndex + 1,
							 (newIndex - currentIndex) * sizeof (ElementType));
				}
				else
				{
					memmove (data.elements + newIndex + 1,
							 data.elements + newIndex,
							 (currentIndex - newIndex) * sizeof (ElementType));
				}

				memcpy (data.elements + newIndex, tempCopy, sizeof (ElementType));
			}
		}
	}

	/** Reduces the amount of storage being used by the array.

		Arrays typically allocate slightly more storage than they need, and after
		removing elements, they may have quite a lot of unused space allocated.
		This method will reduce the amount of allocated storage to a minimum.
	*/
	void minimiseStorageOverheads()
	{
		const ScopedLockType lock (getLock());
		data.shrinkToNoMoreThan (numUsed);
	}

	/** Increases the array's internal storage to hold a minimum number of elements.

		Calling this before adding a large known number of elements means that
		the array won't have to keep dynamically resizing itself as the elements
		are added, and it'll therefore be more efficient.
	*/
	void ensureStorageAllocated (const int minNumElements)
	{
		const ScopedLockType lock (getLock());
		data.ensureAllocatedSize (minNumElements);
	}

	/** Sorts the elements in the array.

		This will use a comparator object to sort the elements into order. The object
		passed must have a method of the form:
		@code
		int compareElements (ElementType first, ElementType second);
		@endcode

		..and this method must return:
		  - a value of < 0 if the first comes before the second
		  - a value of 0 if the two objects are equivalent
		  - a value of > 0 if the second comes before the first

		To improve performance, the compareElements() method can be declared as static or const.

		@param comparator   the comparator to use for comparing elements.
		@param retainOrderOfEquivalentItems     if this is true, then items
							which the comparator says are equivalent will be
							kept in the order in which they currently appear
							in the array. This is slower to perform, but may
							be important in some cases. If it's false, a faster
							algorithm is used, but equivalent elements may be
							rearranged.

		@see addSorted, indexOfSorted, sortArray
	*/
	template <class ElementComparator>
	void sort (ElementComparator& comparator,
			   const bool retainOrderOfEquivalentItems = false) const
	{
		const ScopedLockType lock (getLock());
		(void) comparator;  // if you pass in an object with a static compareElements() method, this
							// avoids getting warning messages about the parameter being unused
		sortArray (comparator, data.elements.getData(), 0, size() - 1, retainOrderOfEquivalentItems);
	}

	/** Returns the CriticalSection that locks this array.
		To lock, you can call getLock().enter() and getLock().exit(), or preferably use
		an object of ScopedLockType as an RAII lock for it.
	*/
	inline const TypeOfCriticalSectionToUse& getLock() const noexcept      { return data; }

	/** Returns the type of scoped lock to use for locking this array */
	typedef typename TypeOfCriticalSectionToUse::ScopedLockType ScopedLockType;

private:

	ArrayAllocationBase <ElementType, TypeOfCriticalSectionToUse> data;
	int numUsed;

	inline void deleteAllElements() noexcept
	{
		for (int i = 0; i < numUsed; ++i)
			data.elements[i].~ElementType();
	}
};

#endif   // __JUCE_ARRAY_JUCEHEADER__

/*** End of inlined file: juce_Array.h ***/


#endif
#ifndef __JUCE_ARRAYALLOCATIONBASE_JUCEHEADER__

#endif
#ifndef __JUCE_DYNAMICOBJECT_JUCEHEADER__

/*** Start of inlined file: juce_DynamicObject.h ***/
#ifndef __JUCE_DYNAMICOBJECT_JUCEHEADER__
#define __JUCE_DYNAMICOBJECT_JUCEHEADER__


/*** Start of inlined file: juce_NamedValueSet.h ***/
#ifndef __JUCE_NAMEDVALUESET_JUCEHEADER__
#define __JUCE_NAMEDVALUESET_JUCEHEADER__


/*** Start of inlined file: juce_Variant.h ***/
#ifndef __JUCE_VARIANT_JUCEHEADER__
#define __JUCE_VARIANT_JUCEHEADER__


/*** Start of inlined file: juce_Identifier.h ***/
#ifndef __JUCE_IDENTIFIER_JUCEHEADER__
#define __JUCE_IDENTIFIER_JUCEHEADER__

class StringPool;

/**
	Represents a string identifier, designed for accessing properties by name.

	Identifier objects are very light and fast to copy, but slower to initialise
	from a string, so it's much faster to keep a static identifier object to refer
	to frequently-used names, rather than constructing them each time you need it.

	@see NamedPropertySet, ValueTree
*/
class JUCE_API  Identifier
{
public:
	/** Creates a null identifier. */
	Identifier() noexcept;

	/** Creates an identifier with a specified name.
		Because this name may need to be used in contexts such as script variables or XML
		tags, it must only contain ascii letters and digits, or the underscore character.
	*/
	Identifier (const char* name);

	/** Creates an identifier with a specified name.
		Because this name may need to be used in contexts such as script variables or XML
		tags, it must only contain ascii letters and digits, or the underscore character.
	*/
	Identifier (const String& name);

	/** Creates a copy of another identifier. */
	Identifier (const Identifier& other) noexcept;

	/** Creates a copy of another identifier. */
	Identifier& operator= (const Identifier& other) noexcept;

	/** Destructor */
	~Identifier();

	/** Compares two identifiers. This is a very fast operation. */
	inline bool operator== (const Identifier& other) const noexcept     { return name == other.name; }

	/** Compares two identifiers. This is a very fast operation. */
	inline bool operator!= (const Identifier& other) const noexcept     { return name != other.name; }

	/** Returns this identifier as a string. */
	String toString() const                                             { return name; }

	/** Returns this identifier's raw string pointer. */
	operator const String::CharPointerType() const noexcept             { return name; }

	/** Returns this identifier's raw string pointer. */
	const String::CharPointerType getCharPointer() const noexcept       { return name; }

	/** Checks a given string for characters that might not be valid in an Identifier.
		Since Identifiers are used as a script variables and XML attributes, they should only contain
		alphanumeric characters, underscores, or the '-' and ':' characters.
	*/
	static bool isValidIdentifier (const String& possibleIdentifier) noexcept;

private:

	String::CharPointerType name;

	static StringPool& getPool();
};

#endif   // __JUCE_IDENTIFIER_JUCEHEADER__

/*** End of inlined file: juce_Identifier.h ***/


/*** Start of inlined file: juce_OutputStream.h ***/
#ifndef __JUCE_OUTPUTSTREAM_JUCEHEADER__
#define __JUCE_OUTPUTSTREAM_JUCEHEADER__


/*** Start of inlined file: juce_NewLine.h ***/
#ifndef __JUCE_NEWLINE_JUCEHEADER__
#define __JUCE_NEWLINE_JUCEHEADER__

/** This class is used for represent a new-line character sequence.

	To write a new-line to a stream, you can use the predefined 'newLine' variable, e.g.
	@code
	myOutputStream << "Hello World" << newLine << newLine;
	@endcode

	The exact character sequence that will be used for the new-line can be set and
	retrieved with OutputStream::setNewLineString() and OutputStream::getNewLineString().
*/
class JUCE_API  NewLine
{
public:
	/** Returns the default new-line sequence that the library uses.
		@see OutputStream::setNewLineString()
	*/
	static const char* getDefault() noexcept        { return "\r\n"; }

	/** Returns the default new-line sequence that the library uses.
		@see getDefault()
	*/
	operator String() const                         { return getDefault(); }
};

/** A predefined object representing a new-line, which can be written to a string or stream.

	To write a new-line to a stream, you can use the predefined 'newLine' variable like this:
	@code
	myOutputStream << "Hello World" << newLine << newLine;
	@endcode
*/
extern NewLine newLine;

/** Writes a new-line sequence to a string.
	You can use the predefined object 'newLine' to invoke this, e.g.
	@code
	myString << "Hello World" << newLine << newLine;
	@endcode
*/
JUCE_API String& JUCE_CALLTYPE operator<< (String& string1, const NewLine&);

#endif   // __JUCE_NEWLINE_JUCEHEADER__

/*** End of inlined file: juce_NewLine.h ***/

class InputStream;
class MemoryBlock;
class File;

/**
	The base class for streams that write data to some kind of destination.

	Input and output streams are used throughout the library - subclasses can override
	some or all of the virtual functions to implement their behaviour.

	@see InputStream, MemoryOutputStream, FileOutputStream
*/
class JUCE_API  OutputStream
{
protected:

	OutputStream();

public:
	/** Destructor.

		Some subclasses might want to do things like call flush() during their
		destructors.
	*/
	virtual ~OutputStream();

	/** If the stream is using a buffer, this will ensure it gets written
		out to the destination. */
	virtual void flush() = 0;

	/** Tries to move the stream's output position.

		Not all streams will be able to seek to a new position - this will return
		false if it fails to work.

		@see getPosition
	*/
	virtual bool setPosition (int64 newPosition) = 0;

	/** Returns the stream's current position.

		@see setPosition
	*/
	virtual int64 getPosition() = 0;

	/** Writes a block of data to the stream.

		When creating a subclass of OutputStream, this is the only write method
		that needs to be overloaded - the base class has methods for writing other
		types of data which use this to do the work.

		@param dataToWrite      the target buffer to receive the data. This must not be null.
		@param numberOfBytes    the number of bytes to write. This must not be negative.
		@returns false if the write operation fails for some reason
	*/
	virtual bool write (const void* dataToWrite,
						int numberOfBytes) = 0;

	/** Writes a single byte to the stream.

		@see InputStream::readByte
	*/
	virtual void writeByte (char byte);

	/** Writes a boolean to the stream as a single byte.
		This is encoded as a binary byte (not as text) with a value of 1 or 0.
		@see InputStream::readBool
	*/
	virtual void writeBool (bool boolValue);

	/** Writes a 16-bit integer to the stream in a little-endian byte order.
		This will write two bytes to the stream: (value & 0xff), then (value >> 8).
		@see InputStream::readShort
	*/
	virtual void writeShort (short value);

	/** Writes a 16-bit integer to the stream in a big-endian byte order.
		This will write two bytes to the stream: (value >> 8), then (value & 0xff).
		@see InputStream::readShortBigEndian
	*/
	virtual void writeShortBigEndian (short value);

	/** Writes a 32-bit integer to the stream in a little-endian byte order.
		@see InputStream::readInt
	*/
	virtual void writeInt (int value);

	/** Writes a 32-bit integer to the stream in a big-endian byte order.
		@see InputStream::readIntBigEndian
	*/
	virtual void writeIntBigEndian (int value);

	/** Writes a 64-bit integer to the stream in a little-endian byte order.
		@see InputStream::readInt64
	*/
	virtual void writeInt64 (int64 value);

	/** Writes a 64-bit integer to the stream in a big-endian byte order.
		@see InputStream::readInt64BigEndian
	*/
	virtual void writeInt64BigEndian (int64 value);

	/** Writes a 32-bit floating point value to the stream in a binary format.
		The binary 32-bit encoding of the float is written as a little-endian int.
		@see InputStream::readFloat
	*/
	virtual void writeFloat (float value);

	/** Writes a 32-bit floating point value to the stream in a binary format.
		The binary 32-bit encoding of the float is written as a big-endian int.
		@see InputStream::readFloatBigEndian
	*/
	virtual void writeFloatBigEndian (float value);

	/** Writes a 64-bit floating point value to the stream in a binary format.
		The eight raw bytes of the double value are written out as a little-endian 64-bit int.
		@see InputStream::readDouble
	*/
	virtual void writeDouble (double value);

	/** Writes a 64-bit floating point value to the stream in a binary format.
		The eight raw bytes of the double value are written out as a big-endian 64-bit int.
		@see InputStream::readDoubleBigEndian
	*/
	virtual void writeDoubleBigEndian (double value);

	/** Writes a byte to the output stream a given number of times. */
	virtual void writeRepeatedByte (uint8 byte, int numTimesToRepeat);

	/** Writes a condensed binary encoding of a 32-bit integer.

		If you're storing a lot of integers which are unlikely to have very large values,
		this can save a lot of space, because values under 0xff will only take up 2 bytes,
		under 0xffff only 3 bytes, etc.

		The format used is: number of significant bytes + up to 4 bytes in little-endian order.

		@see InputStream::readCompressedInt
	*/
	virtual void writeCompressedInt (int value);

	/** Stores a string in the stream in a binary format.

		This isn't the method to use if you're trying to append text to the end of a
		text-file! It's intended for storing a string so that it can be retrieved later
		by InputStream::readString().

		It writes the string to the stream as UTF8, including the null termination character.

		For appending text to a file, instead use writeText, or operator<<

		@see InputStream::readString, writeText, operator<<
	*/
	virtual void writeString (const String& text);

	/** Writes a string of text to the stream.

		It can either write the text as UTF-8 or UTF-16, and can also add the UTF-16 byte-order-mark
		bytes (0xff, 0xfe) to indicate the endianness (these should only be used at the start
		of a file).

		The method also replaces '\\n' characters in the text with '\\r\\n'.
	*/
	virtual void writeText (const String& text,
							bool asUTF16,
							bool writeUTF16ByteOrderMark);

	/** Reads data from an input stream and writes it to this stream.

		@param source               the stream to read from
		@param maxNumBytesToWrite   the number of bytes to read from the stream (if this is
									less than zero, it will keep reading until the input
									is exhausted)
	*/
	virtual int writeFromInputStream (InputStream& source, int64 maxNumBytesToWrite);

	/** Sets the string that will be written to the stream when the writeNewLine()
		method is called.
		By default this will be set the the value of NewLine::getDefault().
	*/
	void setNewLineString (const String& newLineString);

	/** Returns the current new-line string that was set by setNewLineString(). */
	const String& getNewLineString() const noexcept         { return newLineString; }

private:

	String newLineString;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputStream);
};

/** Writes a number to a stream as 8-bit characters in the default system encoding. */
OutputStream& JUCE_CALLTYPE operator<< (OutputStream& stream, int number);

/** Writes a number to a stream as 8-bit characters in the default system encoding. */
OutputStream& JUCE_CALLTYPE operator<< (OutputStream& stream, double number);

/** Writes a character to a stream. */
OutputStream& JUCE_CALLTYPE operator<< (OutputStream& stream, char character);

/** Writes a null-terminated text string to a stream. */
OutputStream& JUCE_CALLTYPE operator<< (OutputStream& stream, const char* text);

/** Writes a block of data from a MemoryBlock to a stream. */
OutputStream& JUCE_CALLTYPE operator<< (OutputStream& stream, const MemoryBlock& data);

/** Writes the contents of a file to a stream. */
OutputStream& JUCE_CALLTYPE operator<< (OutputStream& stream, const File& fileToRead);

/** Writes the complete contents of an input stream to an output stream. */
OutputStream& JUCE_CALLTYPE operator<< (OutputStream& stream, InputStream& streamToRead);

/** Writes a new-line to a stream.
	You can use the predefined symbol 'newLine' to invoke this, e.g.
	@code
	myOutputStream << "Hello World" << newLine << newLine;
	@endcode
	@see OutputStream::setNewLineString
*/
OutputStream& JUCE_CALLTYPE operator<< (OutputStream& stream, const NewLine&);

#endif   // __JUCE_OUTPUTSTREAM_JUCEHEADER__

/*** End of inlined file: juce_OutputStream.h ***/


/*** Start of inlined file: juce_InputStream.h ***/
#ifndef __JUCE_INPUTSTREAM_JUCEHEADER__
#define __JUCE_INPUTSTREAM_JUCEHEADER__

class MemoryBlock;

/** The base class for streams that read data.

	Input and output streams are used throughout the library - subclasses can override
	some or all of the virtual functions to implement their behaviour.

	@see OutputStream, MemoryInputStream, BufferedInputStream, FileInputStream
*/
class JUCE_API  InputStream
{
public:
	/** Destructor. */
	virtual ~InputStream()  {}

	/** Returns the total number of bytes available for reading in this stream.

		Note that this is the number of bytes available from the start of the
		stream, not from the current position.

		If the size of the stream isn't actually known, this may return -1.
	*/
	virtual int64 getTotalLength() = 0;

	/** Returns true if the stream has no more data to read. */
	virtual bool isExhausted() = 0;

	/** Reads some data from the stream into a memory buffer.

		This is the only read method that subclasses actually need to implement, as the
		InputStream base class implements the other read methods in terms of this one (although
		it's often more efficient for subclasses to implement them directly).

		@param destBuffer       the destination buffer for the data. This must not be null.
		@param maxBytesToRead   the maximum number of bytes to read - make sure the
								memory block passed in is big enough to contain this
								many bytes. This value must not be negative.

		@returns    the actual number of bytes that were read, which may be less than
					maxBytesToRead if the stream is exhausted before it gets that far
	*/
	virtual int read (void* destBuffer, int maxBytesToRead) = 0;

	/** Reads a byte from the stream.

		If the stream is exhausted, this will return zero.

		@see OutputStream::writeByte
	*/
	virtual char readByte();

	/** Reads a boolean from the stream.

		The bool is encoded as a single byte - 1 for true, 0 for false.

		If the stream is exhausted, this will return false.

		@see OutputStream::writeBool
	*/
	virtual bool readBool();

	/** Reads two bytes from the stream as a little-endian 16-bit value.

		If the next two bytes read are byte1 and byte2, this returns
		(byte1 | (byte2 << 8)).

		If the stream is exhausted partway through reading the bytes, this will return zero.

		@see OutputStream::writeShort, readShortBigEndian
	*/
	virtual short readShort();

	/** Reads two bytes from the stream as a little-endian 16-bit value.

		If the next two bytes read are byte1 and byte2, this returns
		(byte2 | (byte1 << 8)).

		If the stream is exhausted partway through reading the bytes, this will return zero.

		@see OutputStream::writeShortBigEndian, readShort
	*/
	virtual short readShortBigEndian();

	/** Reads four bytes from the stream as a little-endian 32-bit value.

		If the next four bytes are byte1 to byte4, this returns
		(byte1 | (byte2 << 8) | (byte3 << 16) | (byte4 << 24)).

		If the stream is exhausted partway through reading the bytes, this will return zero.

		@see OutputStream::writeInt, readIntBigEndian
	*/
	virtual int readInt();

	/** Reads four bytes from the stream as a big-endian 32-bit value.

		If the next four bytes are byte1 to byte4, this returns
		(byte4 | (byte3 << 8) | (byte2 << 16) | (byte1 << 24)).

		If the stream is exhausted partway through reading the bytes, this will return zero.

		@see OutputStream::writeIntBigEndian, readInt
	*/
	virtual int readIntBigEndian();

	/** Reads eight bytes from the stream as a little-endian 64-bit value.

		If the next eight bytes are byte1 to byte8, this returns
		(byte1 | (byte2 << 8) | (byte3 << 16) | (byte4 << 24) | (byte5 << 32) | (byte6 << 40) | (byte7 << 48) | (byte8 << 56)).

		If the stream is exhausted partway through reading the bytes, this will return zero.

		@see OutputStream::writeInt64, readInt64BigEndian
	*/
	virtual int64 readInt64();

	/** Reads eight bytes from the stream as a big-endian 64-bit value.

		If the next eight bytes are byte1 to byte8, this returns
		(byte8 | (byte7 << 8) | (byte6 << 16) | (byte5 << 24) | (byte4 << 32) | (byte3 << 40) | (byte2 << 48) | (byte1 << 56)).

		If the stream is exhausted partway through reading the bytes, this will return zero.

		@see OutputStream::writeInt64BigEndian, readInt64
	*/
	virtual int64 readInt64BigEndian();

	/** Reads four bytes as a 32-bit floating point value.

		The raw 32-bit encoding of the float is read from the stream as a little-endian int.

		If the stream is exhausted partway through reading the bytes, this will return zero.

		@see OutputStream::writeFloat, readDouble
	*/
	virtual float readFloat();

	/** Reads four bytes as a 32-bit floating point value.

		The raw 32-bit encoding of the float is read from the stream as a big-endian int.

		If the stream is exhausted partway through reading the bytes, this will return zero.

		@see OutputStream::writeFloatBigEndian, readDoubleBigEndian
	*/
	virtual float readFloatBigEndian();

	/** Reads eight bytes as a 64-bit floating point value.

		The raw 64-bit encoding of the double is read from the stream as a little-endian int64.

		If the stream is exhausted partway through reading the bytes, this will return zero.

		@see OutputStream::writeDouble, readFloat
	*/
	virtual double readDouble();

	/** Reads eight bytes as a 64-bit floating point value.

		The raw 64-bit encoding of the double is read from the stream as a big-endian int64.

		If the stream is exhausted partway through reading the bytes, this will return zero.

		@see OutputStream::writeDoubleBigEndian, readFloatBigEndian
	*/
	virtual double readDoubleBigEndian();

	/** Reads an encoded 32-bit number from the stream using a space-saving compressed format.

		For small values, this is more space-efficient than using readInt() and OutputStream::writeInt()

		The format used is: number of significant bytes + up to 4 bytes in little-endian order.

		@see OutputStream::writeCompressedInt()
	*/
	virtual int readCompressedInt();

	/** Reads a UTF8 string from the stream, up to the next linefeed or carriage return.

		This will read up to the next "\n" or "\r\n" or end-of-stream.

		After this call, the stream's position will be left pointing to the next character
		following the line-feed, but the linefeeds aren't included in the string that
		is returned.
	*/
	virtual String readNextLine();

	/** Reads a zero-terminated UTF8 string from the stream.

		This will read characters from the stream until it hits a zero character or
		end-of-stream.

		@see OutputStream::writeString, readEntireStreamAsString
	*/
	virtual String readString();

	/** Tries to read the whole stream and turn it into a string.

		This will read from the stream's current position until the end-of-stream, and
		will try to make an educated guess about whether it's unicode or an 8-bit encoding.
	*/
	virtual String readEntireStreamAsString();

	/** Reads from the stream and appends the data to a MemoryBlock.

		@param destBlock            the block to append the data onto
		@param maxNumBytesToRead    if this is a positive value, it sets a limit to the number
									of bytes that will be read - if it's negative, data
									will be read until the stream is exhausted.
		@returns the number of bytes that were added to the memory block
	*/
	virtual int readIntoMemoryBlock (MemoryBlock& destBlock,
									 ssize_t maxNumBytesToRead = -1);

	/** Returns the offset of the next byte that will be read from the stream.

		@see setPosition
	*/
	virtual int64 getPosition() = 0;

	/** Tries to move the current read position of the stream.

		The position is an absolute number of bytes from the stream's start.

		Some streams might not be able to do this, in which case they should do
		nothing and return false. Others might be able to manage it by resetting
		themselves and skipping to the correct position, although this is
		obviously a bit slow.

		@returns  true if the stream manages to reposition itself correctly
		@see getPosition
	*/
	virtual bool setPosition (int64 newPosition) = 0;

	/** Reads and discards a number of bytes from the stream.

		Some input streams might implement this efficiently, but the base
		class will just keep reading data until the requisite number of bytes
		have been done.
	*/
	virtual void skipNextBytes (int64 numBytesToSkip);

protected:

	InputStream() noexcept {}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InputStream);
};

#endif   // __JUCE_INPUTSTREAM_JUCEHEADER__

/*** End of inlined file: juce_InputStream.h ***/

#ifndef DOXYGEN
 class ReferenceCountedObject;
 class DynamicObject;
#endif

/**
	A variant class, that can be used to hold a range of primitive values.

	A var object can hold a range of simple primitive values, strings, or
	any kind of ReferenceCountedObject. The var class is intended to act like
	the kind of values used in dynamic scripting languages.

	You can save/load var objects either in a small, proprietary binary format
	using writeToStream()/readFromStream(), or as JSON by using the JSON class.

	@see JSON, DynamicObject
*/
class JUCE_API  var
{
public:

	typedef const var (DynamicObject::*MethodFunction) (const var* arguments, int numArguments);
	typedef Identifier identifier;

	/** Creates a void variant. */
	var() noexcept;

	/** Destructor. */
	~var() noexcept;

	/** A static var object that can be used where you need an empty variant object. */
	static const var null;

	var (const var& valueToCopy);
	var (int value) noexcept;
	var (int64 value) noexcept;
	var (bool value) noexcept;
	var (double value) noexcept;
	var (const char* value);
	var (const wchar_t* value);
	var (const String& value);
	var (const Array<var>& value);
	var (ReferenceCountedObject* object);
	var (MethodFunction method) noexcept;

	var& operator= (const var& valueToCopy);
	var& operator= (int value);
	var& operator= (int64 value);
	var& operator= (bool value);
	var& operator= (double value);
	var& operator= (const char* value);
	var& operator= (const wchar_t* value);
	var& operator= (const String& value);
	var& operator= (const Array<var>& value);
	var& operator= (ReferenceCountedObject* object);
	var& operator= (MethodFunction method);

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	var (var&& other) noexcept;
	var (String&& value);
	var& operator= (var&& other) noexcept;
	var& operator= (String&& value);
   #endif

	void swapWith (var& other) noexcept;

	operator int() const noexcept;
	operator int64() const noexcept;
	operator bool() const noexcept;
	operator float() const noexcept;
	operator double() const noexcept;
	operator String() const;
	String toString() const;
	Array<var>* getArray() const noexcept;
	ReferenceCountedObject* getObject() const noexcept;
	DynamicObject* getDynamicObject() const noexcept;

	bool isVoid() const noexcept;
	bool isInt() const noexcept;
	bool isInt64() const noexcept;
	bool isBool() const noexcept;
	bool isDouble() const noexcept;
	bool isString() const noexcept;
	bool isObject() const noexcept;
	bool isArray() const noexcept;
	bool isMethod() const noexcept;

	/** Returns true if this var has the same value as the one supplied.
		Note that this ignores the type, so a string var "123" and an integer var with the
		value 123 are considered to be equal.
		@see equalsWithSameType
	*/
	bool equals (const var& other) const noexcept;

	/** Returns true if this var has the same value and type as the one supplied.
		This differs from equals() because e.g. "123" and 123 will be considered different.
		@see equals
	*/
	bool equalsWithSameType (const var& other) const noexcept;

	/** If the var is an array, this returns the number of elements.
		If the var isn't actually an array, this will return 0.
	*/
	int size() const;

	/** If the var is an array, this can be used to return one of its elements.
		To call this method, you must make sure that the var is actually an array, and
		that the index is a valid number. If these conditions aren't met, behaviour is
		undefined.
		For more control over the array's contents, you can call getArray() and manipulate
		it directly as an Array\<var\>.
	*/
	const var& operator[] (int arrayIndex) const;

	/** If the var is an array, this can be used to return one of its elements.
		To call this method, you must make sure that the var is actually an array, and
		that the index is a valid number. If these conditions aren't met, behaviour is
		undefined.
		For more control over the array's contents, you can call getArray() and manipulate
		it directly as an Array\<var\>.
	*/
	var& operator[] (int arrayIndex);

	/** Appends an element to the var, converting it to an array if it isn't already one.
		If the var isn't an array, it will be converted to one, and if its value was non-void,
		this value will be kept as the first element of the new array. The parameter value
		will then be appended to it.
		For more control over the array's contents, you can call getArray() and manipulate
		it directly as an Array\<var\>.
	*/
	void append (const var& valueToAppend);

	/** Inserts an element to the var, converting it to an array if it isn't already one.
		If the var isn't an array, it will be converted to one, and if its value was non-void,
		this value will be kept as the first element of the new array. The parameter value
		will then be inserted into it.
		For more control over the array's contents, you can call getArray() and manipulate
		it directly as an Array\<var\>.
	*/
	void insert (int index, const var& value);

	/** If the var is an array, this removes one of its elements.
		If the index is out-of-range or the var isn't an array, nothing will be done.
		For more control over the array's contents, you can call getArray() and manipulate
		it directly as an Array\<var\>.
	*/
	void remove (int index);

	/** Treating the var as an array, this resizes it to contain the specified number of elements.
		If the var isn't an array, it will be converted to one, and if its value was non-void,
		this value will be kept as the first element of the new array before resizing.
		For more control over the array's contents, you can call getArray() and manipulate
		it directly as an Array\<var\>.
	*/
	void resize (int numArrayElementsWanted);

	/** If the var is an array, this searches it for the first occurrence of the specified value,
		and returns its index.
		If the var isn't an array, or if the value isn't found, this returns -1.
	*/
	int indexOf (const var& value) const;

	/** If this variant is an object, this returns one of its properties. */
	var operator[] (const Identifier& propertyName) const;
	/** If this variant is an object, this returns one of its properties. */
	var operator[] (const char* propertyName) const;
	/** If this variant is an object, this returns one of its properties, or a default
		fallback value if the property is not set. */
	var getProperty (const Identifier& propertyName, const var& defaultReturnValue) const;

	/** If this variant is an object, this invokes one of its methods with no arguments. */
	var call (const Identifier& method) const;
	/** If this variant is an object, this invokes one of its methods with one argument. */
	var call (const Identifier& method, const var& arg1) const;
	/** If this variant is an object, this invokes one of its methods with 2 arguments. */
	var call (const Identifier& method, const var& arg1, const var& arg2) const;
	/** If this variant is an object, this invokes one of its methods with 3 arguments. */
	var call (const Identifier& method, const var& arg1, const var& arg2, const var& arg3);
	/** If this variant is an object, this invokes one of its methods with 4 arguments. */
	var call (const Identifier& method, const var& arg1, const var& arg2, const var& arg3, const var& arg4) const;
	/** If this variant is an object, this invokes one of its methods with 5 arguments. */
	var call (const Identifier& method, const var& arg1, const var& arg2, const var& arg3, const var& arg4, const var& arg5) const;
	/** If this variant is an object, this invokes one of its methods with a list of arguments. */
	var invoke (const Identifier& method, const var* arguments, int numArguments) const;

	/** Writes a binary representation of this value to a stream.
		The data can be read back later using readFromStream().
		@see JSON
	*/
	void writeToStream (OutputStream& output) const;

	/** Reads back a stored binary representation of a value.
		The data in the stream must have been written using writeToStream(), or this
		will have unpredictable results.
		@see JSON
	*/
	static var readFromStream (InputStream& input);

private:

	class VariantType;         friend class VariantType;
	class VariantType_Void;    friend class VariantType_Void;
	class VariantType_Int;     friend class VariantType_Int;
	class VariantType_Int64;   friend class VariantType_Int64;
	class VariantType_Double;  friend class VariantType_Double;
	class VariantType_Bool;    friend class VariantType_Bool;
	class VariantType_String;  friend class VariantType_String;
	class VariantType_Object;  friend class VariantType_Object;
	class VariantType_Array;   friend class VariantType_Array;
	class VariantType_Method;  friend class VariantType_Method;

	union ValueUnion
	{
		int intValue;
		int64 int64Value;
		bool boolValue;
		double doubleValue;
		char stringValue [sizeof (String)];
		ReferenceCountedObject* objectValue;
		Array<var>* arrayValue;
		MethodFunction methodValue;
	};

	const VariantType* type;
	ValueUnion value;

	Array<var>* convertToArray();
	friend class DynamicObject;
	var invokeMethod (DynamicObject*, const var*, int) const;
};

/** Compares the values of two var objects, using the var::equals() comparison. */
bool operator== (const var& v1, const var& v2) noexcept;
/** Compares the values of two var objects, using the var::equals() comparison. */
bool operator!= (const var& v1, const var& v2) noexcept;
bool operator== (const var& v1, const String& v2);
bool operator!= (const var& v1, const String& v2);
bool operator== (const var& v1, const char* v2);
bool operator!= (const var& v1, const char* v2);

#endif   // __JUCE_VARIANT_JUCEHEADER__

/*** End of inlined file: juce_Variant.h ***/


/*** Start of inlined file: juce_LinkedListPointer.h ***/
#ifndef __JUCE_LINKEDLISTPOINTER_JUCEHEADER__
#define __JUCE_LINKEDLISTPOINTER_JUCEHEADER__

/**
	Helps to manipulate singly-linked lists of objects.

	For objects that are designed to contain a pointer to the subsequent item in the
	list, this class contains methods to deal with the list. To use it, the ObjectType
	class that it points to must contain a LinkedListPointer called nextListItem, e.g.

	@code
	struct MyObject
	{
		int x, y, z;

		// A linkable object must contain a member with this name and type, which must be
		// accessible by the LinkedListPointer class. (This doesn't mean it has to be public -
		// you could make your class a friend of a LinkedListPointer<MyObject> instead).
		LinkedListPointer<MyObject> nextListItem;
	};

	LinkedListPointer<MyObject> myList;
	myList.append (new MyObject());
	myList.append (new MyObject());

	int numItems = myList.size(); // returns 2
	MyObject* lastInList = myList.getLast();
	@endcode
*/
template <class ObjectType>
class LinkedListPointer
{
public:

	/** Creates a null pointer to an empty list. */
	LinkedListPointer() noexcept
		: item (nullptr)
	{
	}

	/** Creates a pointer to a list whose head is the item provided. */
	explicit LinkedListPointer (ObjectType* const headItem) noexcept
		: item (headItem)
	{
	}

	/** Sets this pointer to point to a new list. */
	LinkedListPointer& operator= (ObjectType* const newItem) noexcept
	{
		item = newItem;
		return *this;
	}

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	LinkedListPointer (LinkedListPointer&& other) noexcept
		: item (other.item)
	{
		other.item = nullptr;
	}

	LinkedListPointer& operator= (LinkedListPointer&& other) noexcept
	{
		jassert (this != &other); // hopefully the compiler should make this situation impossible!

		item = other.item;
		other.item = nullptr;
		return *this;
	}
   #endif

	/** Returns the item which this pointer points to. */
	inline operator ObjectType*() const noexcept
	{
		return item;
	}

	/** Returns the item which this pointer points to. */
	inline ObjectType* get() const noexcept
	{
		return item;
	}

	/** Returns the last item in the list which this pointer points to.
		This will iterate the list and return the last item found. Obviously the speed
		of this operation will be proportional to the size of the list. If the list is
		empty the return value will be this object.
		If you're planning on appending a number of items to your list, it's much more
		efficient to use the Appender class than to repeatedly call getLast() to find the end.
	*/
	LinkedListPointer& getLast() noexcept
	{
		LinkedListPointer* l = this;

		while (l->item != nullptr)
			l = &(l->item->nextListItem);

		return *l;
	}

	/** Returns the number of items in the list.
		Obviously with a simple linked list, getting the size involves iterating the list, so
		this can be a lengthy operation - be careful when using this method in your code.
	*/
	int size() const noexcept
	{
		int total = 0;

		for (ObjectType* i = item; i != nullptr; i = i->nextListItem)
			++total;

		return total;
	}

	/** Returns the item at a given index in the list.
		Since the only way to find an item is to iterate the list, this operation can obviously
		be slow, depending on its size, so you should be careful when using this in algorithms.
	*/
	LinkedListPointer& operator[] (int index) noexcept
	{
		LinkedListPointer* l = this;

		while (--index >= 0 && l->item != nullptr)
			l = &(l->item->nextListItem);

		return *l;
	}

	/** Returns the item at a given index in the list.
		Since the only way to find an item is to iterate the list, this operation can obviously
		be slow, depending on its size, so you should be careful when using this in algorithms.
	*/
	const LinkedListPointer& operator[] (int index) const noexcept
	{
		const LinkedListPointer* l = this;

		while (--index >= 0 && l->item != nullptr)
			l = &(l->item->nextListItem);

		return *l;
	}

	/** Returns true if the list contains the given item. */
	bool contains (const ObjectType* const itemToLookFor) const noexcept
	{
		for (ObjectType* i = item; i != nullptr; i = i->nextListItem)
			if (itemToLookFor == i)
				return true;

		return false;
	}

	/** Inserts an item into the list, placing it before the item that this pointer
		currently points to.
	*/
	void insertNext (ObjectType* const newItem)
	{
		jassert (newItem != nullptr);
		jassert (newItem->nextListItem == nullptr);
		newItem->nextListItem = item;
		item = newItem;
	}

	/** Inserts an item at a numeric index in the list.
		Obviously this will involve iterating the list to find the item at the given index,
		so be careful about the impact this may have on execution time.
	*/
	void insertAtIndex (int index, ObjectType* newItem)
	{
		jassert (newItem != nullptr);
		LinkedListPointer* l = this;

		while (index != 0 && l->item != nullptr)
		{
			l = &(l->item->nextListItem);
			--index;
		}

		l->insertNext (newItem);
	}

	/** Replaces the object that this pointer points to, appending the rest of the list to
		the new object, and returning the old one.
	*/
	ObjectType* replaceNext (ObjectType* const newItem) noexcept
	{
		jassert (newItem != nullptr);
		jassert (newItem->nextListItem == nullptr);

		ObjectType* const oldItem = item;
		item = newItem;
		item->nextListItem = oldItem->nextListItem.item;
		oldItem->nextListItem = (ObjectType*) 0;
		return oldItem;
	}

	/** Adds an item to the end of the list.

		This operation involves iterating the whole list, so can be slow - if you need to
		append a number of items to your list, it's much more efficient to use the Appender
		class than to repeatedly call append().
	*/
	void append (ObjectType* const newItem)
	{
		getLast().item = newItem;
	}

	/** Creates copies of all the items in another list and adds them to this one.
		This will use the ObjectType's copy constructor to try to create copies of each
		item in the other list, and appends them to this list.
	*/
	void addCopyOfList (const LinkedListPointer& other)
	{
		LinkedListPointer* insertPoint = this;

		for (ObjectType* i = other.item; i != nullptr; i = i->nextListItem)
		{
			insertPoint->insertNext (new ObjectType (*i));
			insertPoint = &(insertPoint->item->nextListItem);
		}
	}

	/** Removes the head item from the list.
		This won't delete the object that is removed, but returns it, so the caller can
		delete it if necessary.
	*/
	ObjectType* removeNext() noexcept
	{
		ObjectType* const oldItem = item;

		if (oldItem != nullptr)
		{
			item = oldItem->nextListItem;
			oldItem->nextListItem = (ObjectType*) 0;
		}

		return oldItem;
	}

	/** Removes a specific item from the list.
		Note that this will not delete the item, it simply unlinks it from the list.
	*/
	void remove (ObjectType* const itemToRemove)
	{
		LinkedListPointer* const l = findPointerTo (itemToRemove);

		if (l != nullptr)
			l->removeNext();
	}

	/** Iterates the list, calling the delete operator on all of its elements and
		leaving this pointer empty.
	*/
	void deleteAll()
	{
		while (item != nullptr)
		{
			ObjectType* const oldItem = item;
			item = oldItem->nextListItem;
			delete oldItem;
		}
	}

	/** Finds a pointer to a given item.
		If the item is found in the list, this returns the pointer that points to it. If
		the item isn't found, this returns null.
	*/
	LinkedListPointer* findPointerTo (ObjectType* const itemToLookFor) noexcept
	{
		LinkedListPointer* l = this;

		while (l->item != nullptr)
		{
			if (l->item == itemToLookFor)
				return l;

			l = &(l->item->nextListItem);
		}

		return nullptr;
	}

	/** Copies the items in the list to an array.
		The destArray must contain enough elements to hold the entire list - no checks are
		made for this!
	*/
	void copyToArray (ObjectType** destArray) const noexcept
	{
		jassert (destArray != nullptr);

		for (ObjectType* i = item; i != nullptr; i = i->nextListItem)
			*destArray++ = i;
	}

	/** Swaps this pointer with another one */
	void swapWith (LinkedListPointer& other) noexcept
	{
		std::swap (item, other.item);
	}

	/**
		Allows efficient repeated insertions into a list.

		You can create an Appender object which points to the last element in your
		list, and then repeatedly call Appender::append() to add items to the end
		of the list in O(1) time.
	*/
	class Appender
	{
	public:
		/** Creates an appender which will add items to the given list.
		*/
		Appender (LinkedListPointer& endOfListPointer) noexcept
			: endOfList (&endOfListPointer)
		{
			// This can only be used to add to the end of a list.
			jassert (endOfListPointer.item == nullptr);
		}

		/** Appends an item to the list. */
		void append (ObjectType* const newItem) noexcept
		{
			*endOfList = newItem;
			endOfList = &(newItem->nextListItem);
		}

	private:
		LinkedListPointer* endOfList;

		JUCE_DECLARE_NON_COPYABLE (Appender);
	};

private:

	ObjectType* item;

	JUCE_DECLARE_NON_COPYABLE (LinkedListPointer);
};

#endif   // __JUCE_LINKEDLISTPOINTER_JUCEHEADER__

/*** End of inlined file: juce_LinkedListPointer.h ***/

class XmlElement;
#ifndef DOXYGEN
 class JSONFormatter;
#endif

/** Holds a set of named var objects.

	This can be used as a basic structure to hold a set of var object, which can
	be retrieved by using their identifier.
*/
class JUCE_API  NamedValueSet
{
public:
	/** Creates an empty set. */
	NamedValueSet() noexcept;

	/** Creates a copy of another set. */
	NamedValueSet (const NamedValueSet& other);

	/** Replaces this set with a copy of another set. */
	NamedValueSet& operator= (const NamedValueSet& other);

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	NamedValueSet (NamedValueSet&& other) noexcept;
	NamedValueSet& operator= (NamedValueSet&& other) noexcept;
   #endif

	/** Destructor. */
	~NamedValueSet();

	bool operator== (const NamedValueSet& other) const;
	bool operator!= (const NamedValueSet& other) const;

	/** Returns the total number of values that the set contains. */
	int size() const noexcept;

	/** Returns the value of a named item.
		If the name isn't found, this will return a void variant.
		@see getProperty
	*/
	const var& operator[] (const Identifier& name) const;

	/** Tries to return the named value, but if no such value is found, this will
		instead return the supplied default value.
	*/
	var getWithDefault (const Identifier& name, const var& defaultReturnValue) const;

	/** Changes or adds a named value.
		@returns    true if a value was changed or added; false if the
					value was already set the the value passed-in.
	*/
	bool set (const Identifier& name, const var& newValue);

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	/** Changes or adds a named value.
		@returns    true if a value was changed or added; false if the
					value was already set the the value passed-in.
	*/
	bool set (const Identifier& name, var&& newValue);
   #endif

	/** Returns true if the set contains an item with the specified name. */
	bool contains (const Identifier& name) const;

	/** Removes a value from the set.
		@returns    true if a value was removed; false if there was no value
					with the name that was given.
	*/
	bool remove (const Identifier& name);

	/** Returns the name of the value at a given index.
		The index must be between 0 and size() - 1.
	*/
	const Identifier getName (int index) const;

	/** Returns the value of the item at a given index.
		The index must be between 0 and size() - 1.
	*/
	const var& getValueAt (int index) const;

	/** Removes all values. */
	void clear();

	/** Returns a pointer to the var that holds a named value, or null if there is
		no value with this name.

		Do not use this method unless you really need access to the internal var object
		for some reason - for normal reading and writing always prefer operator[]() and set().
	*/
	var* getVarPointer (const Identifier& name) const noexcept;

	/** Sets properties to the values of all of an XML element's attributes. */
	void setFromXmlAttributes (const XmlElement& xml);

	/** Sets attributes in an XML element corresponding to each of this object's
		properties.
	*/
	void copyToXmlAttributes (XmlElement& xml) const;

private:

	class NamedValue
	{
	public:
		NamedValue() noexcept;
		NamedValue (const NamedValue&);
		NamedValue (const Identifier& name, const var& value);
		NamedValue& operator= (const NamedValue&);
	   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
		NamedValue (NamedValue&&) noexcept;
		NamedValue (const Identifier& name, var&& value);
		NamedValue& operator= (NamedValue&&) noexcept;
	   #endif
		bool operator== (const NamedValue& other) const noexcept;

		LinkedListPointer<NamedValue> nextListItem;
		Identifier name;
		var value;

	private:
		JUCE_LEAK_DETECTOR (NamedValue);
	};

	friend class LinkedListPointer<NamedValue>;
	LinkedListPointer<NamedValue> values;

	friend class JSONFormatter;
};

#endif   // __JUCE_NAMEDVALUESET_JUCEHEADER__

/*** End of inlined file: juce_NamedValueSet.h ***/


/*** Start of inlined file: juce_ReferenceCountedObject.h ***/
#ifndef __JUCE_REFERENCECOUNTEDOBJECT_JUCEHEADER__
#define __JUCE_REFERENCECOUNTEDOBJECT_JUCEHEADER__

/**
	Adds reference-counting to an object.

	To add reference-counting to a class, derive it from this class, and
	use the ReferenceCountedObjectPtr class to point to it.

	e.g. @code
	class MyClass : public ReferenceCountedObject
	{
		void foo();

		// This is a neat way of declaring a typedef for a pointer class,
		// rather than typing out the full templated name each time..
		typedef ReferenceCountedObjectPtr<MyClass> Ptr;
	};

	MyClass::Ptr p = new MyClass();
	MyClass::Ptr p2 = p;
	p = nullptr;
	p2->foo();
	@endcode

	Once a new ReferenceCountedObject has been assigned to a pointer, be
	careful not to delete the object manually.

	This class uses an Atomic<int> value to hold the reference count, so that it
	the pointers can be passed between threads safely. For a faster but non-thread-safe
	version, use SingleThreadedReferenceCountedObject instead.

	@see ReferenceCountedObjectPtr, ReferenceCountedArray, SingleThreadedReferenceCountedObject
*/
class JUCE_API  ReferenceCountedObject
{
public:

	/** Increments the object's reference count.

		This is done automatically by the smart pointer, but is public just
		in case it's needed for nefarious purposes.
	*/
	inline void incReferenceCount() noexcept
	{
		++refCount;
	}

	/** Decreases the object's reference count.

		If the count gets to zero, the object will be deleted.
	*/
	inline void decReferenceCount() noexcept
	{
		jassert (getReferenceCount() > 0);

		if (--refCount == 0)
			delete this;
	}

	/** Returns the object's current reference count. */
	inline int getReferenceCount() const noexcept       { return refCount.get(); }

protected:

	/** Creates the reference-counted object (with an initial ref count of zero). */
	ReferenceCountedObject()
	{
	}

	/** Destructor. */
	virtual ~ReferenceCountedObject()
	{
		// it's dangerous to delete an object that's still referenced by something else!
		jassert (getReferenceCount() == 0);
	}

	/** Resets the reference count to zero without deleting the object.
		You should probably never need to use this!
	*/
	void resetReferenceCount() noexcept
	{
		refCount = 0;
	}

private:

	Atomic <int> refCount;
};

/**
	Adds reference-counting to an object.

	This is efectively a version of the ReferenceCountedObject class, but which
	uses a non-atomic counter, and so is not thread-safe (but which will be more
	efficient).
	For more details on how to use it, see the ReferenceCountedObject class notes.

	@see ReferenceCountedObject, ReferenceCountedObjectPtr, ReferenceCountedArray
*/
class JUCE_API  SingleThreadedReferenceCountedObject
{
public:

	/** Increments the object's reference count.

		This is done automatically by the smart pointer, but is public just
		in case it's needed for nefarious purposes.
	*/
	inline void incReferenceCount() noexcept
	{
		++refCount;
	}

	/** Decreases the object's reference count.

		If the count gets to zero, the object will be deleted.
	*/
	inline void decReferenceCount() noexcept
	{
		jassert (getReferenceCount() > 0);

		if (--refCount == 0)
			delete this;
	}

	/** Returns the object's current reference count. */
	inline int getReferenceCount() const noexcept       { return refCount; }

protected:

	/** Creates the reference-counted object (with an initial ref count of zero). */
	SingleThreadedReferenceCountedObject() : refCount (0)  {}

	/** Destructor. */
	virtual ~SingleThreadedReferenceCountedObject()
	{
		// it's dangerous to delete an object that's still referenced by something else!
		jassert (getReferenceCount() == 0);
	}

private:

	int refCount;
};

/**
	A smart-pointer class which points to a reference-counted object.

	The template parameter specifies the class of the object you want to point to - the easiest
	way to make a class reference-countable is to simply make it inherit from ReferenceCountedObject,
	but if you need to, you could roll your own reference-countable class by implementing a pair of
	mathods called incReferenceCount() and decReferenceCount().

	When using this class, you'll probably want to create a typedef to abbreviate the full
	templated name - e.g.
	@code typedef ReferenceCountedObjectPtr<MyClass> MyClassPtr;@endcode

	@see ReferenceCountedObject, ReferenceCountedObjectArray
*/
template <class ReferenceCountedObjectClass>
class ReferenceCountedObjectPtr
{
public:
	/** The class being referenced by this pointer. */
	typedef ReferenceCountedObjectClass ReferencedType;

	/** Creates a pointer to a null object. */
	inline ReferenceCountedObjectPtr() noexcept
		: referencedObject (nullptr)
	{
	}

	/** Creates a pointer to an object.

		This will increment the object's reference-count if it is non-null.
	*/
	inline ReferenceCountedObjectPtr (ReferenceCountedObjectClass* const refCountedObject) noexcept
		: referencedObject (refCountedObject)
	{
		if (refCountedObject != nullptr)
			refCountedObject->incReferenceCount();
	}

	/** Copies another pointer.
		This will increment the object's reference-count (if it is non-null).
	*/
	inline ReferenceCountedObjectPtr (const ReferenceCountedObjectPtr& other) noexcept
		: referencedObject (other.referencedObject)
	{
		if (referencedObject != nullptr)
			referencedObject->incReferenceCount();
	}

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	/** Takes-over the object from another pointer. */
	inline ReferenceCountedObjectPtr (ReferenceCountedObjectPtr&& other) noexcept
		: referencedObject (other.referencedObject)
	{
		other.referencedObject = nullptr;
	}
   #endif

	/** Copies another pointer.
		This will increment the object's reference-count (if it is non-null).
	*/
	template <class DerivedClass>
	inline ReferenceCountedObjectPtr (const ReferenceCountedObjectPtr<DerivedClass>& other) noexcept
		: referencedObject (static_cast <ReferenceCountedObjectClass*> (other.getObject()))
	{
		if (referencedObject != nullptr)
			referencedObject->incReferenceCount();
	}

	/** Changes this pointer to point at a different object.

		The reference count of the old object is decremented, and it might be
		deleted if it hits zero. The new object's count is incremented.
	*/
	ReferenceCountedObjectPtr& operator= (const ReferenceCountedObjectPtr& other)
	{
		return operator= (other.referencedObject);
	}

	/** Changes this pointer to point at a different object.

		The reference count of the old object is decremented, and it might be
		deleted if it hits zero. The new object's count is incremented.
	*/
	template <class DerivedClass>
	ReferenceCountedObjectPtr& operator= (const ReferenceCountedObjectPtr<DerivedClass>& other)
	{
		return operator= (static_cast <ReferenceCountedObjectClass*> (other.getObject()));
	}

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	/** Takes-over the object from another pointer. */
	ReferenceCountedObjectPtr& operator= (ReferenceCountedObjectPtr&& other)
	{
		std::swap (referencedObject, other.referencedObject);
		return *this;
	}
   #endif

	/** Changes this pointer to point at a different object.

		The reference count of the old object is decremented, and it might be
		deleted if it hits zero. The new object's count is incremented.
	*/
	ReferenceCountedObjectPtr& operator= (ReferenceCountedObjectClass* const newObject)
	{
		if (referencedObject != newObject)
		{
			if (newObject != nullptr)
				newObject->incReferenceCount();

			ReferenceCountedObjectClass* const oldObject = referencedObject;
			referencedObject = newObject;

			if (oldObject != nullptr)
				oldObject->decReferenceCount();
		}

		return *this;
	}

	/** Destructor.

		This will decrement the object's reference-count, and may delete it if it
		gets to zero.
	*/
	inline ~ReferenceCountedObjectPtr()
	{
		if (referencedObject != nullptr)
			referencedObject->decReferenceCount();
	}

	/** Returns the object that this pointer references.
		The pointer returned may be zero, of course.
	*/
	inline operator ReferenceCountedObjectClass*() const noexcept
	{
		return referencedObject;
	}

	// the -> operator is called on the referenced object
	inline ReferenceCountedObjectClass* operator->() const noexcept
	{
		return referencedObject;
	}

	/** Returns the object that this pointer references.
		The pointer returned may be zero, of course.
	*/
	inline ReferenceCountedObjectClass* getObject() const noexcept
	{
		return referencedObject;
	}

private:

	ReferenceCountedObjectClass* referencedObject;
};

/** Compares two ReferenceCountedObjectPointers. */
template <class ReferenceCountedObjectClass>
bool operator== (const ReferenceCountedObjectPtr<ReferenceCountedObjectClass>& object1, ReferenceCountedObjectClass* const object2) noexcept
{
	return object1.getObject() == object2;
}

/** Compares two ReferenceCountedObjectPointers. */
template <class ReferenceCountedObjectClass>
bool operator== (const ReferenceCountedObjectPtr<ReferenceCountedObjectClass>& object1, const ReferenceCountedObjectPtr<ReferenceCountedObjectClass>& object2) noexcept
{
	return object1.getObject() == object2.getObject();
}

/** Compares two ReferenceCountedObjectPointers. */
template <class ReferenceCountedObjectClass>
bool operator== (ReferenceCountedObjectClass* object1, ReferenceCountedObjectPtr<ReferenceCountedObjectClass>& object2) noexcept
{
	return object1 == object2.getObject();
}

/** Compares two ReferenceCountedObjectPointers. */
template <class ReferenceCountedObjectClass>
bool operator!= (const ReferenceCountedObjectPtr<ReferenceCountedObjectClass>& object1, const ReferenceCountedObjectClass* object2) noexcept
{
	return object1.getObject() != object2;
}

/** Compares two ReferenceCountedObjectPointers. */
template <class ReferenceCountedObjectClass>
bool operator!= (const ReferenceCountedObjectPtr<ReferenceCountedObjectClass>& object1, ReferenceCountedObjectPtr<ReferenceCountedObjectClass>& object2) noexcept
{
	return object1.getObject() != object2.getObject();
}

/** Compares two ReferenceCountedObjectPointers. */
template <class ReferenceCountedObjectClass>
bool operator!= (ReferenceCountedObjectClass* object1, ReferenceCountedObjectPtr<ReferenceCountedObjectClass>& object2) noexcept
{
	return object1 != object2.getObject();
}

#endif   // __JUCE_REFERENCECOUNTEDOBJECT_JUCEHEADER__

/*** End of inlined file: juce_ReferenceCountedObject.h ***/

/**
	Represents a dynamically implemented object.

	This class is primarily intended for wrapping scripting language objects,
	but could be used for other purposes.

	An instance of a DynamicObject can be used to store named properties, and
	by subclassing hasMethod() and invokeMethod(), you can give your object
	methods.
*/
class JUCE_API  DynamicObject  : public ReferenceCountedObject
{
public:

	DynamicObject();

	/** Destructor. */
	virtual ~DynamicObject();

	/** Returns true if the object has a property with this name.
		Note that if the property is actually a method, this will return false.
	*/
	virtual bool hasProperty (const Identifier& propertyName) const;

	/** Returns a named property.

		This returns a void if no such property exists.
	*/
	virtual var getProperty (const Identifier& propertyName) const;

	/** Sets a named property. */
	virtual void setProperty (const Identifier& propertyName, const var& newValue);

	/** Removes a named property. */
	virtual void removeProperty (const Identifier& propertyName);

	/** Checks whether this object has the specified method.

		The default implementation of this just checks whether there's a property
		with this name that's actually a method, but this can be overridden for
		building objects with dynamic invocation.
	*/
	virtual bool hasMethod (const Identifier& methodName) const;

	/** Invokes a named method on this object.

		The default implementation looks up the named property, and if it's a method
		call, then it invokes it.

		This method is virtual to allow more dynamic invocation to used for objects
		where the methods may not already be set as properies.
	*/
	virtual var invokeMethod (const Identifier& methodName,
							  const var* parameters,
							  int numParameters);

	/** Sets up a method.

		This is basically the same as calling setProperty (methodName, (var::MethodFunction) myFunction), but
		helps to avoid accidentally invoking the wrong type of var constructor. It also makes
		the code easier to read,

		The compiler will probably force you to use an explicit cast your method to a (var::MethodFunction), e.g.
		@code
		setMethod ("doSomething", (var::MethodFunction) &MyClass::doSomething);
		@endcode
	*/
	void setMethod (const Identifier& methodName,
					var::MethodFunction methodFunction);

	/** Removes all properties and methods from the object. */
	void clear();

	/** Returns the NamedValueSet that holds the object's properties. */
	NamedValueSet& getProperties() noexcept     { return properties; }

private:

	NamedValueSet properties;

	JUCE_LEAK_DETECTOR (DynamicObject);
};

#endif   // __JUCE_DYNAMICOBJECT_JUCEHEADER__

/*** End of inlined file: juce_DynamicObject.h ***/


#endif
#ifndef __JUCE_ELEMENTCOMPARATOR_JUCEHEADER__

#endif
#ifndef __JUCE_HASHMAP_JUCEHEADER__

/*** Start of inlined file: juce_HashMap.h ***/
#ifndef __JUCE_HASHMAP_JUCEHEADER__
#define __JUCE_HASHMAP_JUCEHEADER__


/*** Start of inlined file: juce_OwnedArray.h ***/
#ifndef __JUCE_OWNEDARRAY_JUCEHEADER__
#define __JUCE_OWNEDARRAY_JUCEHEADER__

/** An array designed for holding objects.

	This holds a list of pointers to objects, and will automatically
	delete the objects when they are removed from the array, or when the
	array is itself deleted.

	Declare it in the form:  OwnedArray<MyObjectClass>

	..and then add new objects, e.g.   myOwnedArray.add (new MyObjectClass());

	After adding objects, they are 'owned' by the array and will be deleted when
	removed or replaced.

	To make all the array's methods thread-safe, pass in "CriticalSection" as the templated
	TypeOfCriticalSectionToUse parameter, instead of the default DummyCriticalSection.

	@see Array, ReferenceCountedArray, StringArray, CriticalSection
*/
template <class ObjectClass,
		  class TypeOfCriticalSectionToUse = DummyCriticalSection>

class OwnedArray
{
public:

	/** Creates an empty array. */
	OwnedArray() noexcept
		: numUsed (0)
	{
	}

	/** Deletes the array and also deletes any objects inside it.

		To get rid of the array without deleting its objects, use its
		clear (false) method before deleting it.
	*/
	~OwnedArray()
	{
		clear (true);
	}

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	OwnedArray (OwnedArray&& other) noexcept
		: data (static_cast <ArrayAllocationBase <ObjectClass*, TypeOfCriticalSectionToUse>&&> (other.data)),
		  numUsed (other.numUsed)
	{
		other.numUsed = 0;
	}

	OwnedArray& operator= (OwnedArray&& other) noexcept
	{
		data = static_cast <ArrayAllocationBase <ObjectClass*, TypeOfCriticalSectionToUse>&&> (other.data);
		numUsed = other.numUsed;
		other.numUsed = 0;
		return *this;
	}
   #endif

	/** Clears the array, optionally deleting the objects inside it first. */
	void clear (const bool deleteObjects = true)
	{
		const ScopedLockType lock (getLock());

		if (deleteObjects)
		{
			while (numUsed > 0)
				delete data.elements [--numUsed];
		}

		data.setAllocatedSize (0);
		numUsed = 0;
	}

	/** Returns the number of items currently in the array.
		@see operator[]
	*/
	inline int size() const noexcept
	{
		return numUsed;
	}

	/** Returns a pointer to the object at this index in the array.

		If the index is out-of-range, this will return a null pointer, (and
		it could be null anyway, because it's ok for the array to hold null
		pointers as well as objects).

		@see getUnchecked
	*/
	inline ObjectClass* operator[] (const int index) const noexcept
	{
		const ScopedLockType lock (getLock());
		return isPositiveAndBelow (index, numUsed) ? data.elements [index]
												   : static_cast <ObjectClass*> (nullptr);
	}

	/** Returns a pointer to the object at this index in the array, without checking whether the index is in-range.

		This is a faster and less safe version of operator[] which doesn't check the index passed in, so
		it can be used when you're sure the index if always going to be legal.
	*/
	inline ObjectClass* getUnchecked (const int index) const noexcept
	{
		const ScopedLockType lock (getLock());
		jassert (isPositiveAndBelow (index, numUsed));
		return data.elements [index];
	}

	/** Returns a pointer to the first object in the array.

		This will return a null pointer if the array's empty.
		@see getLast
	*/
	inline ObjectClass* getFirst() const noexcept
	{
		const ScopedLockType lock (getLock());
		return numUsed > 0 ? data.elements [0]
						   : static_cast <ObjectClass*> (nullptr);
	}

	/** Returns a pointer to the last object in the array.

		This will return a null pointer if the array's empty.
		@see getFirst
	*/
	inline ObjectClass* getLast() const noexcept
	{
		const ScopedLockType lock (getLock());
		return numUsed > 0 ? data.elements [numUsed - 1]
						   : static_cast <ObjectClass*> (nullptr);
	}

	/** Returns a pointer to the actual array data.
		This pointer will only be valid until the next time a non-const method
		is called on the array.
	*/
	inline ObjectClass** getRawDataPointer() noexcept
	{
		return data.elements;
	}

	/** Returns a pointer to the first element in the array.
		This method is provided for compatibility with standard C++ iteration mechanisms.
	*/
	inline ObjectClass** begin() const noexcept
	{
		return data.elements;
	}

	/** Returns a pointer to the element which follows the last element in the array.
		This method is provided for compatibility with standard C++ iteration mechanisms.
	*/
	inline ObjectClass** end() const noexcept
	{
		return data.elements + numUsed;
	}

	/** Finds the index of an object which might be in the array.

		@param objectToLookFor    the object to look for
		@returns                  the index at which the object was found, or -1 if it's not found
	*/
	int indexOf (const ObjectClass* const objectToLookFor) const noexcept
	{
		const ScopedLockType lock (getLock());
		ObjectClass* const* e = data.elements.getData();
		ObjectClass* const* const end_ = e + numUsed;

		for (; e != end_; ++e)
			if (objectToLookFor == *e)
				return static_cast <int> (e - data.elements.getData());

		return -1;
	}

	/** Returns true if the array contains a specified object.

		@param objectToLookFor      the object to look for
		@returns                    true if the object is in the array
	*/
	bool contains (const ObjectClass* const objectToLookFor) const noexcept
	{
		const ScopedLockType lock (getLock());
		ObjectClass* const* e = data.elements.getData();
		ObjectClass* const* const end_ = e + numUsed;

		for (; e != end_; ++e)
			if (objectToLookFor == *e)
				return true;

		return false;
	}

	/** Appends a new object to the end of the array.

		Note that the this object will be deleted by the OwnedArray when it
		is removed, so be careful not to delete it somewhere else.

		Also be careful not to add the same object to the array more than once,
		as this will obviously cause deletion of dangling pointers.

		@param newObject       the new object to add to the array
		@see set, insert, addIfNotAlreadyThere, addSorted
	*/
	void add (const ObjectClass* const newObject) noexcept
	{
		const ScopedLockType lock (getLock());
		data.ensureAllocatedSize (numUsed + 1);
		data.elements [numUsed++] = const_cast <ObjectClass*> (newObject);
	}

	/** Inserts a new object into the array at the given index.

		Note that the this object will be deleted by the OwnedArray when it
		is removed, so be careful not to delete it somewhere else.

		If the index is less than 0 or greater than the size of the array, the
		element will be added to the end of the array.
		Otherwise, it will be inserted into the array, moving all the later elements
		along to make room.

		Be careful not to add the same object to the array more than once,
		as this will obviously cause deletion of dangling pointers.

		@param indexToInsertAt      the index at which the new element should be inserted
		@param newObject            the new object to add to the array
		@see add, addSorted, addIfNotAlreadyThere, set
	*/
	void insert (int indexToInsertAt,
				 const ObjectClass* const newObject) noexcept
	{
		if (indexToInsertAt >= 0)
		{
			const ScopedLockType lock (getLock());

			if (indexToInsertAt > numUsed)
				indexToInsertAt = numUsed;

			data.ensureAllocatedSize (numUsed + 1);

			ObjectClass** const e = data.elements + indexToInsertAt;
			const int numToMove = numUsed - indexToInsertAt;

			if (numToMove > 0)
				memmove (e + 1, e, numToMove * sizeof (ObjectClass*));

			*e = const_cast <ObjectClass*> (newObject);
			++numUsed;
		}
		else
		{
			add (newObject);
		}
	}

	/** Appends a new object at the end of the array as long as the array doesn't
		already contain it.

		If the array already contains a matching object, nothing will be done.

		@param newObject   the new object to add to the array
	*/
	void addIfNotAlreadyThere (const ObjectClass* const newObject) noexcept
	{
		const ScopedLockType lock (getLock());

		if (! contains (newObject))
			add (newObject);
	}

	/** Replaces an object in the array with a different one.

		If the index is less than zero, this method does nothing.
		If the index is beyond the end of the array, the new object is added to the end of the array.

		Be careful not to add the same object to the array more than once,
		as this will obviously cause deletion of dangling pointers.

		@param indexToChange        the index whose value you want to change
		@param newObject            the new value to set for this index.
		@param deleteOldElement     whether to delete the object that's being replaced with the new one
		@see add, insert, remove
	*/
	void set (const int indexToChange,
			  const ObjectClass* const newObject,
			  const bool deleteOldElement = true)
	{
		if (indexToChange >= 0)
		{
			ObjectClass* toDelete = nullptr;

			{
				const ScopedLockType lock (getLock());

				if (indexToChange < numUsed)
				{
					if (deleteOldElement)
					{
						toDelete = data.elements [indexToChange];

						if (toDelete == newObject)
							toDelete = nullptr;
					}

					data.elements [indexToChange] = const_cast <ObjectClass*> (newObject);
				}
				else
				{
					data.ensureAllocatedSize (numUsed + 1);
					data.elements [numUsed++] = const_cast <ObjectClass*> (newObject);
				}
			}

			delete toDelete; // don't want to use a ScopedPointer here because if the
							 // object has a private destructor, both OwnedArray and
							 // ScopedPointer would need to be friend classes..
		}
		else
		{
			jassertfalse; // you're trying to set an object at a negative index, which doesn't have
						  // any effect - but since the object is not being added, it may be leaking..
		}
	}

	/** Adds elements from another array to the end of this array.

		@param arrayToAddFrom       the array from which to copy the elements
		@param startIndex           the first element of the other array to start copying from
		@param numElementsToAdd     how many elements to add from the other array. If this
									value is negative or greater than the number of available elements,
									all available elements will be copied.
		@see add
	*/
	template <class OtherArrayType>
	void addArray (const OtherArrayType& arrayToAddFrom,
				   int startIndex = 0,
				   int numElementsToAdd = -1)
	{
		const typename OtherArrayType::ScopedLockType lock1 (arrayToAddFrom.getLock());
		const ScopedLockType lock2 (getLock());

		if (startIndex < 0)
		{
			jassertfalse;
			startIndex = 0;
		}

		if (numElementsToAdd < 0 || startIndex + numElementsToAdd > arrayToAddFrom.size())
			numElementsToAdd = arrayToAddFrom.size() - startIndex;

		data.ensureAllocatedSize (numUsed + numElementsToAdd);

		while (--numElementsToAdd >= 0)
		{
			data.elements [numUsed] = arrayToAddFrom.getUnchecked (startIndex++);
			++numUsed;
		}
	}

	/** Adds copies of the elements in another array to the end of this array.

		The other array must be either an OwnedArray of a compatible type of object, or an Array
		containing pointers to the same kind of object. The objects involved must provide
		a copy constructor, and this will be used to create new copies of each element, and
		add them to this array.

		@param arrayToAddFrom       the array from which to copy the elements
		@param startIndex           the first element of the other array to start copying from
		@param numElementsToAdd     how many elements to add from the other array. If this
									value is negative or greater than the number of available elements,
									all available elements will be copied.
		@see add
	*/
	template <class OtherArrayType>
	void addCopiesOf (const OtherArrayType& arrayToAddFrom,
					  int startIndex = 0,
					  int numElementsToAdd = -1)
	{
		const typename OtherArrayType::ScopedLockType lock1 (arrayToAddFrom.getLock());
		const ScopedLockType lock2 (getLock());

		if (startIndex < 0)
		{
			jassertfalse;
			startIndex = 0;
		}

		if (numElementsToAdd < 0 || startIndex + numElementsToAdd > arrayToAddFrom.size())
			numElementsToAdd = arrayToAddFrom.size() - startIndex;

		data.ensureAllocatedSize (numUsed + numElementsToAdd);

		while (--numElementsToAdd >= 0)
		{
			data.elements [numUsed] = new ObjectClass (*arrayToAddFrom.getUnchecked (startIndex++));
			++numUsed;
		}
	}

	/** Inserts a new object into the array assuming that the array is sorted.

		This will use a comparator to find the position at which the new object
		should go. If the array isn't sorted, the behaviour of this
		method will be unpredictable.

		@param comparator   the comparator to use to compare the elements - see the sort method
							for details about this object's structure
		@param newObject    the new object to insert to the array
		@returns the index at which the new object was added
		@see add, sort, indexOfSorted
	*/
	template <class ElementComparator>
	int addSorted (ElementComparator& comparator, ObjectClass* const newObject) noexcept
	{
		(void) comparator;  // if you pass in an object with a static compareElements() method, this
							// avoids getting warning messages about the parameter being unused
		const ScopedLockType lock (getLock());
		const int index = findInsertIndexInSortedArray (comparator, data.elements.getData(), newObject, 0, numUsed);
		insert (index, newObject);
		return index;
	}

	/** Finds the index of an object in the array, assuming that the array is sorted.

		This will use a comparator to do a binary-chop to find the index of the given
		element, if it exists. If the array isn't sorted, the behaviour of this
		method will be unpredictable.

		@param comparator           the comparator to use to compare the elements - see the sort()
									method for details about the form this object should take
		@param objectToLookFor      the object to search for
		@returns                    the index of the element, or -1 if it's not found
		@see addSorted, sort
	*/
	template <class ElementComparator>
	int indexOfSorted (ElementComparator& comparator,
					   const ObjectClass* const objectToLookFor) const noexcept
	{
		(void) comparator;  // if you pass in an object with a static compareElements() method, this
							// avoids getting warning messages about the parameter being unused
		const ScopedLockType lock (getLock());

		int start = 0;
		int end_ = numUsed;

		for (;;)
		{
			if (start >= end_)
			{
				return -1;
			}
			else if (comparator.compareElements (objectToLookFor, data.elements [start]) == 0)
			{
				return start;
			}
			else
			{
				const int halfway = (start + end_) >> 1;

				if (halfway == start)
					return -1;
				else if (comparator.compareElements (objectToLookFor, data.elements [halfway]) >= 0)
					start = halfway;
				else
					end_ = halfway;
			}
		}
	}

	/** Removes an object from the array.

		This will remove the object at a given index (optionally also
		deleting it) and move back all the subsequent objects to close the gap.
		If the index passed in is out-of-range, nothing will happen.

		@param indexToRemove    the index of the element to remove
		@param deleteObject     whether to delete the object that is removed
		@see removeObject, removeRange
	*/
	void remove (const int indexToRemove,
				 const bool deleteObject = true)
	{
		ObjectClass* toDelete = nullptr;

		{
			const ScopedLockType lock (getLock());

			if (isPositiveAndBelow (indexToRemove, numUsed))
			{
				ObjectClass** const e = data.elements + indexToRemove;

				if (deleteObject)
					toDelete = *e;

				--numUsed;
				const int numToShift = numUsed - indexToRemove;

				if (numToShift > 0)
					memmove (e, e + 1, numToShift * sizeof (ObjectClass*));
			}
		}

		delete toDelete; // don't want to use a ScopedPointer here because if the
						 // object has a private destructor, both OwnedArray and
						 // ScopedPointer would need to be friend classes..

		if ((numUsed << 1) < data.numAllocated)
			minimiseStorageOverheads();
	}

	/** Removes and returns an object from the array without deleting it.

		This will remove the object at a given index and return it, moving back all
		the subsequent objects to close the gap. If the index passed in is out-of-range,
		nothing will happen.

		@param indexToRemove    the index of the element to remove
		@see remove, removeObject, removeRange
	*/
	ObjectClass* removeAndReturn (const int indexToRemove)
	{
		ObjectClass* removedItem = nullptr;
		const ScopedLockType lock (getLock());

		if (isPositiveAndBelow (indexToRemove, numUsed))
		{
			ObjectClass** const e = data.elements + indexToRemove;
			removedItem = *e;

			--numUsed;
			const int numToShift = numUsed - indexToRemove;

			if (numToShift > 0)
				memmove (e, e + 1, numToShift * sizeof (ObjectClass*));

			if ((numUsed << 1) < data.numAllocated)
				minimiseStorageOverheads();
		}

		return removedItem;
	}

	/** Removes a specified object from the array.

		If the item isn't found, no action is taken.

		@param objectToRemove   the object to try to remove
		@param deleteObject     whether to delete the object (if it's found)
		@see remove, removeRange
	*/
	void removeObject (const ObjectClass* const objectToRemove,
					   const bool deleteObject = true)
	{
		const ScopedLockType lock (getLock());
		ObjectClass** const e = data.elements.getData();

		for (int i = 0; i < numUsed; ++i)
		{
			if (objectToRemove == e[i])
			{
				remove (i, deleteObject);
				break;
			}
		}
	}

	/** Removes a range of objects from the array.

		This will remove a set of objects, starting from the given index,
		and move any subsequent elements down to close the gap.

		If the range extends beyond the bounds of the array, it will
		be safely clipped to the size of the array.

		@param startIndex       the index of the first object to remove
		@param numberToRemove   how many objects should be removed
		@param deleteObjects    whether to delete the objects that get removed
		@see remove, removeObject
	*/
	void removeRange (int startIndex,
					  const int numberToRemove,
					  const bool deleteObjects = true)
	{
		const ScopedLockType lock (getLock());
		const int endIndex = jlimit (0, numUsed, startIndex + numberToRemove);
		startIndex = jlimit (0, numUsed, startIndex);

		if (endIndex > startIndex)
		{
			if (deleteObjects)
			{
				for (int i = startIndex; i < endIndex; ++i)
				{
					delete data.elements [i];
					data.elements [i] = nullptr; // (in case one of the destructors accesses this array and hits a dangling pointer)
				}
			}

			const int rangeSize = endIndex - startIndex;
			ObjectClass** e = data.elements + startIndex;
			int numToShift = numUsed - endIndex;
			numUsed -= rangeSize;

			while (--numToShift >= 0)
			{
				*e = e [rangeSize];
				++e;
			}

			if ((numUsed << 1) < data.numAllocated)
				minimiseStorageOverheads();
		}
	}

	/** Removes the last n objects from the array.

		@param howManyToRemove   how many objects to remove from the end of the array
		@param deleteObjects     whether to also delete the objects that are removed
		@see remove, removeObject, removeRange
	*/
	void removeLast (int howManyToRemove = 1,
					 const bool deleteObjects = true)
	{
		const ScopedLockType lock (getLock());

		if (howManyToRemove >= numUsed)
			clear (deleteObjects);
		else
			removeRange (numUsed - howManyToRemove, howManyToRemove, deleteObjects);
	}

	/** Swaps a pair of objects in the array.

		If either of the indexes passed in is out-of-range, nothing will happen,
		otherwise the two objects at these positions will be exchanged.
	*/
	void swap (const int index1,
			   const int index2) noexcept
	{
		const ScopedLockType lock (getLock());

		if (isPositiveAndBelow (index1, numUsed)
			 && isPositiveAndBelow (index2, numUsed))
		{
			swapVariables (data.elements [index1],
						   data.elements [index2]);
		}
	}

	/** Moves one of the objects to a different position.

		This will move the object to a specified index, shuffling along
		any intervening elements as required.

		So for example, if you have the array { 0, 1, 2, 3, 4, 5 } then calling
		move (2, 4) would result in { 0, 1, 3, 4, 2, 5 }.

		@param currentIndex     the index of the object to be moved. If this isn't a
								valid index, then nothing will be done
		@param newIndex         the index at which you'd like this object to end up. If this
								is less than zero, it will be moved to the end of the array
	*/
	void move (const int currentIndex,
			   int newIndex) noexcept
	{
		if (currentIndex != newIndex)
		{
			const ScopedLockType lock (getLock());

			if (isPositiveAndBelow (currentIndex, numUsed))
			{
				if (! isPositiveAndBelow (newIndex, numUsed))
					newIndex = numUsed - 1;

				ObjectClass* const value = data.elements [currentIndex];

				if (newIndex > currentIndex)
				{
					memmove (data.elements + currentIndex,
							 data.elements + currentIndex + 1,
							 (newIndex - currentIndex) * sizeof (ObjectClass*));
				}
				else
				{
					memmove (data.elements + newIndex + 1,
							 data.elements + newIndex,
							 (currentIndex - newIndex) * sizeof (ObjectClass*));
				}

				data.elements [newIndex] = value;
			}
		}
	}

	/** This swaps the contents of this array with those of another array.

		If you need to exchange two arrays, this is vastly quicker than using copy-by-value
		because it just swaps their internal pointers.
	*/
	void swapWithArray (OwnedArray& otherArray) noexcept
	{
		const ScopedLockType lock1 (getLock());
		const ScopedLockType lock2 (otherArray.getLock());

		data.swapWith (otherArray.data);
		swapVariables (numUsed, otherArray.numUsed);
	}

	/** Reduces the amount of storage being used by the array.

		Arrays typically allocate slightly more storage than they need, and after
		removing elements, they may have quite a lot of unused space allocated.
		This method will reduce the amount of allocated storage to a minimum.
	*/
	void minimiseStorageOverheads() noexcept
	{
		const ScopedLockType lock (getLock());
		data.shrinkToNoMoreThan (numUsed);
	}

	/** Increases the array's internal storage to hold a minimum number of elements.

		Calling this before adding a large known number of elements means that
		the array won't have to keep dynamically resizing itself as the elements
		are added, and it'll therefore be more efficient.
	*/
	void ensureStorageAllocated (const int minNumElements) noexcept
	{
		const ScopedLockType lock (getLock());
		data.ensureAllocatedSize (minNumElements);
	}

	/** Sorts the elements in the array.

		This will use a comparator object to sort the elements into order. The object
		passed must have a method of the form:
		@code
		int compareElements (ElementType first, ElementType second);
		@endcode

		..and this method must return:
		  - a value of < 0 if the first comes before the second
		  - a value of 0 if the two objects are equivalent
		  - a value of > 0 if the second comes before the first

		To improve performance, the compareElements() method can be declared as static or const.

		@param comparator   the comparator to use for comparing elements.
		@param retainOrderOfEquivalentItems     if this is true, then items
							which the comparator says are equivalent will be
							kept in the order in which they currently appear
							in the array. This is slower to perform, but may
							be important in some cases. If it's false, a faster
							algorithm is used, but equivalent elements may be
							rearranged.
		@see sortArray, indexOfSorted
	*/
	template <class ElementComparator>
	void sort (ElementComparator& comparator,
			   const bool retainOrderOfEquivalentItems = false) const noexcept
	{
		(void) comparator;  // if you pass in an object with a static compareElements() method, this
							// avoids getting warning messages about the parameter being unused

		const ScopedLockType lock (getLock());
		sortArray (comparator, data.elements.getData(), 0, size() - 1, retainOrderOfEquivalentItems);
	}

	/** Returns the CriticalSection that locks this array.
		To lock, you can call getLock().enter() and getLock().exit(), or preferably use
		an object of ScopedLockType as an RAII lock for it.
	*/
	inline const TypeOfCriticalSectionToUse& getLock() const noexcept      { return data; }

	/** Returns the type of scoped lock to use for locking this array */
	typedef typename TypeOfCriticalSectionToUse::ScopedLockType ScopedLockType;

private:

	ArrayAllocationBase <ObjectClass*, TypeOfCriticalSectionToUse> data;
	int numUsed;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OwnedArray);
};

#endif   // __JUCE_OWNEDARRAY_JUCEHEADER__

/*** End of inlined file: juce_OwnedArray.h ***/


/*** Start of inlined file: juce_ScopedPointer.h ***/
#ifndef __JUCE_SCOPEDPOINTER_JUCEHEADER__
#define __JUCE_SCOPEDPOINTER_JUCEHEADER__

/**
	This class holds a pointer which is automatically deleted when this object goes
	out of scope.

	Once a pointer has been passed to a ScopedPointer, it will make sure that the pointer
	gets deleted when the ScopedPointer is deleted. Using the ScopedPointer on the stack or
	as member variables is a good way to use RAII to avoid accidentally leaking dynamically
	created objects.

	A ScopedPointer can be used in pretty much the same way that you'd use a normal pointer
	to an object. If you use the assignment operator to assign a different object to a
	ScopedPointer, the old one will be automatically deleted.

	A const ScopedPointer is guaranteed not to lose ownership of its object or change the
	object to which it points during its lifetime. This means that making a copy of a const
	ScopedPointer is impossible, as that would involve the new copy taking ownership from the
	old one.

	If you need to get a pointer out of a ScopedPointer without it being deleted, you
	can use the release() method.

	Something to note is the main difference between this class and the std::auto_ptr class,
	which is that ScopedPointer provides a cast-to-object operator, wheras std::auto_ptr
	requires that you always call get() to retrieve the pointer. The advantages of providing
	the cast is that you don't need to call get(), so can use the ScopedPointer in pretty much
	exactly the same way as a raw pointer. The disadvantage is that the compiler is free to
	use the cast in unexpected and sometimes dangerous ways - in particular, it becomes difficult
	to return a ScopedPointer as the result of a function. To avoid this causing errors,
	ScopedPointer contains an overloaded constructor that should cause a syntax error in these
	circumstances, but it does mean that instead of returning a ScopedPointer from a function,
	you'd need to return a raw pointer (or use a std::auto_ptr instead).
*/
template <class ObjectType>
class ScopedPointer
{
public:

	/** Creates a ScopedPointer containing a null pointer. */
	inline ScopedPointer() noexcept   : object (nullptr)
	{
	}

	/** Creates a ScopedPointer that owns the specified object. */
	inline ScopedPointer (ObjectType* const objectToTakePossessionOf) noexcept
		: object (objectToTakePossessionOf)
	{
	}

	/** Creates a ScopedPointer that takes its pointer from another ScopedPointer.

		Because a pointer can only belong to one ScopedPointer, this transfers
		the pointer from the other object to this one, and the other object is reset to
		be a null pointer.
	*/
	ScopedPointer (ScopedPointer& objectToTransferFrom) noexcept
		: object (objectToTransferFrom.object)
	{
		objectToTransferFrom.object = nullptr;
	}

	/** Destructor.
		This will delete the object that this ScopedPointer currently refers to.
	*/
	inline ~ScopedPointer()                                                         { delete object; }

	/** Changes this ScopedPointer to point to a new object.

		Because a pointer can only belong to one ScopedPointer, this transfers
		the pointer from the other object to this one, and the other object is reset to
		be a null pointer.

		If this ScopedPointer already points to an object, that object
		will first be deleted.
	*/
	ScopedPointer& operator= (ScopedPointer& objectToTransferFrom)
	{
		if (this != objectToTransferFrom.getAddress())
		{
			// Two ScopedPointers should never be able to refer to the same object - if
			// this happens, you must have done something dodgy!
			jassert (object == nullptr || object != objectToTransferFrom.object);

			ObjectType* const oldObject = object;
			object = objectToTransferFrom.object;
			objectToTransferFrom.object = nullptr;
			delete oldObject;
		}

		return *this;
	}

	/** Changes this ScopedPointer to point to a new object.

		If this ScopedPointer already points to an object, that object
		will first be deleted.

		The pointer that you pass is may be null.
	*/
	ScopedPointer& operator= (ObjectType* const newObjectToTakePossessionOf)
	{
		if (object != newObjectToTakePossessionOf)
		{
			ObjectType* const oldObject = object;
			object = newObjectToTakePossessionOf;
			delete oldObject;
		}

		return *this;
	}

	/** Returns the object that this ScopedPointer refers to. */
	inline operator ObjectType*() const noexcept                                    { return object; }

	/** Returns the object that this ScopedPointer refers to. */
	inline ObjectType* get() const noexcept                                         { return object; }

	/** Returns the object that this ScopedPointer refers to. */
	inline ObjectType& operator*() const noexcept                                   { return *object; }

	/** Lets you access methods and properties of the object that this ScopedPointer refers to. */
	inline ObjectType* operator->() const noexcept                                  { return object; }

	/** Removes the current object from this ScopedPointer without deleting it.
		This will return the current object, and set the ScopedPointer to a null pointer.
	*/
	ObjectType* release() noexcept                                                  { ObjectType* const o = object; object = nullptr; return o; }

	/** Swaps this object with that of another ScopedPointer.
		The two objects simply exchange their pointers.
	*/
	void swapWith (ScopedPointer <ObjectType>& other) noexcept
	{
		// Two ScopedPointers should never be able to refer to the same object - if
		// this happens, you must have done something dodgy!
		jassert (object != other.object);

		std::swap (object, other.object);
	}

	/** If the pointer is non-null, this will attempt to return a new copy of the object that is pointed to.
		If the pointer is null, this will safely return a nullptr.
	*/
	inline ObjectType* createCopy() const                                           { return createCopyIfNotNull (object); }

private:

	ObjectType* object;

	// (Required as an alternative to the overloaded & operator).
	const ScopedPointer* getAddress() const noexcept                                { return this; }

  #if ! JUCE_MSVC  // (MSVC can't deal with multiple copy constructors)
	/* These are private to stop people accidentally copying a const ScopedPointer (the compiler
	   would let you do so by implicitly casting the source to its raw object pointer).

	   A side effect of this is that you may hit a puzzling compiler error when you write something
	   like this:

		  ScopedPointer<MyClass> m = new MyClass();  // Compile error: copy constructor is private.

	   Even though the compiler would normally ignore the assignment here, it can't do so when the
	   copy constructor is private. It's very easy to fis though - just write it like this:

		  ScopedPointer<MyClass> m (new MyClass());  // Compiles OK

	   It's good practice to always use the latter form when writing your object declarations anyway,
	   rather than writing them as assignments and assuming (or hoping) that the compiler will be
	   smart enough to replace your construction + assignment with a single constructor.
	*/
	ScopedPointer (const ScopedPointer&);
	ScopedPointer& operator= (const ScopedPointer&);
  #endif
};

/** Compares a ScopedPointer with another pointer.
	This can be handy for checking whether this is a null pointer.
*/
template <class ObjectType>
bool operator== (const ScopedPointer<ObjectType>& pointer1, ObjectType* const pointer2) noexcept
{
	return static_cast <ObjectType*> (pointer1) == pointer2;
}

/** Compares a ScopedPointer with another pointer.
	This can be handy for checking whether this is a null pointer.
*/
template <class ObjectType>
bool operator!= (const ScopedPointer<ObjectType>& pointer1, ObjectType* const pointer2) noexcept
{
	return static_cast <ObjectType*> (pointer1) != pointer2;
}

#endif   // __JUCE_SCOPEDPOINTER_JUCEHEADER__

/*** End of inlined file: juce_ScopedPointer.h ***/

/**
	A simple class to generate hash functions for some primitive types, intended for
	use with the HashMap class.
	@see HashMap
*/
class DefaultHashFunctions
{
public:
	/** Generates a simple hash from an integer. */
	static int generateHash (const int key, const int upperLimit) noexcept        { return std::abs (key) % upperLimit; }
	/** Generates a simple hash from a string. */
	static int generateHash (const String& key, const int upperLimit) noexcept    { return (int) (((uint32) key.hashCode()) % upperLimit); }
	/** Generates a simple hash from a variant. */
	static int generateHash (const var& key, const int upperLimit) noexcept       { return generateHash (key.toString(), upperLimit); }
};

/**
	Holds a set of mappings between some key/value pairs.

	The types of the key and value objects are set as template parameters.
	You can also specify a class to supply a hash function that converts a key value
	into an hashed integer. This class must have the form:

	@code
	struct MyHashGenerator
	{
		static int generateHash (MyKeyType key, int upperLimit)
		{
			// The function must return a value 0 <= x < upperLimit
			return someFunctionOfMyKeyType (key) % upperLimit;
		}
	};
	@endcode

	Like the Array class, the key and value types are expected to be copy-by-value types, so
	if you define them to be pointer types, this class won't delete the objects that they
	point to.

	If you don't supply a class for the HashFunctionToUse template parameter, the
	default one provides some simple mappings for strings and ints.

	@code
	HashMap<int, String> hash;
	hash.set (1, "item1");
	hash.set (2, "item2");

	DBG (hash [1]); // prints "item1"
	DBG (hash [2]); // prints "item2"

	// This iterates the map, printing all of its key -> value pairs..
	for (HashMap<int, String>::Iterator i (hash); i.next();)
		DBG (i.getKey() << " -> " << i.getValue());
	@endcode

	@see CriticalSection, DefaultHashFunctions, NamedValueSet, SortedSet
*/
template <typename KeyType,
		  typename ValueType,
		  class HashFunctionToUse = DefaultHashFunctions,
		  class TypeOfCriticalSectionToUse = DummyCriticalSection>
class HashMap
{
private:
	typedef PARAMETER_TYPE (KeyType)   KeyTypeParameter;
	typedef PARAMETER_TYPE (ValueType) ValueTypeParameter;

public:

	/** Creates an empty hash-map.

		The numberOfSlots parameter specifies the number of hash entries the map will use. This
		will be the "upperLimit" parameter that is passed to your generateHash() function. The number
		of hash slots will grow automatically if necessary, or it can be remapped manually using remapTable().
	*/
	explicit HashMap (const int numberOfSlots = defaultHashTableSize)
	   : totalNumItems (0)
	{
		slots.insertMultiple (0, nullptr, numberOfSlots);
	}

	/** Destructor. */
	~HashMap()
	{
		clear();
	}

	/** Removes all values from the map.
		Note that this will clear the content, but won't affect the number of slots (see
		remapTable and getNumSlots).
	*/
	void clear()
	{
		const ScopedLockType sl (getLock());

		for (int i = slots.size(); --i >= 0;)
		{
			HashEntry* h = slots.getUnchecked(i);

			while (h != nullptr)
			{
				const ScopedPointer<HashEntry> deleter (h);
				h = h->nextEntry;
			}

			slots.set (i, nullptr);
		}

		totalNumItems = 0;
	}

	/** Returns the current number of items in the map. */
	inline int size() const noexcept
	{
		return totalNumItems;
	}

	/** Returns the value corresponding to a given key.
		If the map doesn't contain the key, a default instance of the value type is returned.
		@param keyToLookFor    the key of the item being requested
	*/
	inline const ValueType operator[] (KeyTypeParameter keyToLookFor) const
	{
		const ScopedLockType sl (getLock());

		for (const HashEntry* entry = slots.getUnchecked (generateHashFor (keyToLookFor)); entry != nullptr; entry = entry->nextEntry)
			if (entry->key == keyToLookFor)
				return entry->value;

		return ValueType();
	}

	/** Returns true if the map contains an item with the specied key. */
	bool contains (KeyTypeParameter keyToLookFor) const
	{
		const ScopedLockType sl (getLock());

		for (const HashEntry* entry = slots.getUnchecked (generateHashFor (keyToLookFor)); entry != nullptr; entry = entry->nextEntry)
			if (entry->key == keyToLookFor)
				return true;

		return false;
	}

	/** Returns true if the hash contains at least one occurrence of a given value. */
	bool containsValue (ValueTypeParameter valueToLookFor) const
	{
		const ScopedLockType sl (getLock());

		for (int i = getNumSlots(); --i >= 0;)
			for (const HashEntry* entry = slots.getUnchecked(i); entry != nullptr; entry = entry->nextEntry)
				if (entry->value == valueToLookFor)
					return true;

		return false;
	}

	/** Adds or replaces an element in the hash-map.
		If there's already an item with the given key, this will replace its value. Otherwise, a new item
		will be added to the map.
	*/
	void set (KeyTypeParameter newKey, ValueTypeParameter newValue)
	{
		const ScopedLockType sl (getLock());
		const int hashIndex = generateHashFor (newKey);

		HashEntry* const firstEntry = slots.getUnchecked (hashIndex);

		for (HashEntry* entry = firstEntry; entry != nullptr; entry = entry->nextEntry)
		{
			if (entry->key == newKey)
			{
				entry->value = newValue;
				return;
			}
		}

		slots.set (hashIndex, new HashEntry (newKey, newValue, firstEntry));
		++totalNumItems;

		if (totalNumItems > (getNumSlots() * 3) / 2)
			remapTable (getNumSlots() * 2);
	}

	/** Removes an item with the given key. */
	void remove (KeyTypeParameter keyToRemove)
	{
		const ScopedLockType sl (getLock());
		const int hashIndex = generateHashFor (keyToRemove);
		HashEntry* entry = slots.getUnchecked (hashIndex);
		HashEntry* previous = nullptr;

		while (entry != nullptr)
		{
			if (entry->key == keyToRemove)
			{
				const ScopedPointer<HashEntry> deleter (entry);

				entry = entry->nextEntry;

				if (previous != nullptr)
					previous->nextEntry = entry;
				else
					slots.set (hashIndex, entry);

				--totalNumItems;
			}
			else
			{
				previous = entry;
				entry = entry->nextEntry;
			}
		}
	}

	/** Removes all items with the given value. */
	void removeValue (ValueTypeParameter valueToRemove)
	{
		const ScopedLockType sl (getLock());

		for (int i = getNumSlots(); --i >= 0;)
		{
			HashEntry* entry = slots.getUnchecked(i);
			HashEntry* previous = nullptr;

			while (entry != nullptr)
			{
				if (entry->value == valueToRemove)
				{
					const ScopedPointer<HashEntry> deleter (entry);

					entry = entry->nextEntry;

					if (previous != nullptr)
						previous->nextEntry = entry;
					else
						slots.set (i, entry);

					--totalNumItems;
				}
				else
				{
					previous = entry;
					entry = entry->nextEntry;
				}
			}
		}
	}

	/** Remaps the hash-map to use a different number of slots for its hash function.
		Each slot corresponds to a single hash-code, and each one can contain multiple items.
		@see getNumSlots()
	*/
	void remapTable (int newNumberOfSlots)
	{
		HashMap newTable (newNumberOfSlots);

		for (int i = getNumSlots(); --i >= 0;)
			for (const HashEntry* entry = slots.getUnchecked(i); entry != nullptr; entry = entry->nextEntry)
				newTable.set (entry->key, entry->value);

		swapWith (newTable);
	}

	/** Returns the number of slots which are available for hashing.
		Each slot corresponds to a single hash-code, and each one can contain multiple items.
		@see getNumSlots()
	*/
	inline int getNumSlots() const noexcept
	{
		return slots.size();
	}

	/** Efficiently swaps the contents of two hash-maps. */
	void swapWith (HashMap& otherHashMap) noexcept
	{
		const ScopedLockType lock1 (getLock());
		const ScopedLockType lock2 (otherHashMap.getLock());

		slots.swapWithArray (otherHashMap.slots);
		std::swap (totalNumItems, otherHashMap.totalNumItems);
	}

	/** Returns the CriticalSection that locks this structure.
		To lock, you can call getLock().enter() and getLock().exit(), or preferably use
		an object of ScopedLockType as an RAII lock for it.
	*/
	inline const TypeOfCriticalSectionToUse& getLock() const noexcept      { return lock; }

	/** Returns the type of scoped lock to use for locking this array */
	typedef typename TypeOfCriticalSectionToUse::ScopedLockType ScopedLockType;

private:

	class HashEntry
	{
	public:
		HashEntry (KeyTypeParameter key_, ValueTypeParameter value_, HashEntry* const nextEntry_)
			: key (key_), value (value_), nextEntry (nextEntry_)
		{}

		const KeyType key;
		ValueType value;
		HashEntry* nextEntry;

		JUCE_DECLARE_NON_COPYABLE (HashEntry);
	};

public:

	/** Iterates over the items in a HashMap.

		To use it, repeatedly call next() until it returns false, e.g.
		@code
		HashMap <String, String> myMap;

		HashMap<String, String>::Iterator i (myMap);

		while (i.next())
		{
			DBG (i.getKey() << " -> " << i.getValue());
		}
		@endcode

		The order in which items are iterated bears no resemblence to the order in which
		they were originally added!

		Obviously as soon as you call any non-const methods on the original hash-map, any
		iterators that were created beforehand will cease to be valid, and should not be used.

		@see HashMap
	*/
	class Iterator
	{
	public:

		Iterator (const HashMap& hashMapToIterate)
			: hashMap (hashMapToIterate), entry (nullptr), index (0)
		{}

		/** Moves to the next item, if one is available.
			When this returns true, you can get the item's key and value using getKey() and
			getValue(). If it returns false, the iteration has finished and you should stop.
		*/
		bool next()
		{
			if (entry != nullptr)
				entry = entry->nextEntry;

			while (entry == nullptr)
			{
				if (index >= hashMap.getNumSlots())
					return false;

				entry = hashMap.slots.getUnchecked (index++);
			}

			return true;
		}

		/** Returns the current item's key.
			This should only be called when a call to next() has just returned true.
		*/
		KeyType getKey() const
		{
			return entry != nullptr ? entry->key : KeyType();
		}

		/** Returns the current item's value.
			This should only be called when a call to next() has just returned true.
		*/
		ValueType getValue() const
		{
			return entry != nullptr ? entry->value : ValueType();
		}

	private:

		const HashMap& hashMap;
		HashEntry* entry;
		int index;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Iterator);
	};

private:

	enum { defaultHashTableSize = 101 };
	friend class Iterator;

	Array <HashEntry*> slots;
	int totalNumItems;
	TypeOfCriticalSectionToUse lock;

	int generateHashFor (KeyTypeParameter key) const
	{
		const int hash = HashFunctionToUse::generateHash (key, getNumSlots());
		jassert (isPositiveAndBelow (hash, getNumSlots())); // your hash function is generating out-of-range numbers!
		return hash;
	}

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HashMap);
};

#endif   // __JUCE_HASHMAP_JUCEHEADER__

/*** End of inlined file: juce_HashMap.h ***/


#endif
#ifndef __JUCE_LINKEDLISTPOINTER_JUCEHEADER__

#endif
#ifndef __JUCE_NAMEDVALUESET_JUCEHEADER__

#endif
#ifndef __JUCE_OWNEDARRAY_JUCEHEADER__

#endif
#ifndef __JUCE_PROPERTYSET_JUCEHEADER__

/*** Start of inlined file: juce_PropertySet.h ***/
#ifndef __JUCE_PROPERTYSET_JUCEHEADER__
#define __JUCE_PROPERTYSET_JUCEHEADER__


/*** Start of inlined file: juce_StringPairArray.h ***/
#ifndef __JUCE_STRINGPAIRARRAY_JUCEHEADER__
#define __JUCE_STRINGPAIRARRAY_JUCEHEADER__


/*** Start of inlined file: juce_StringArray.h ***/
#ifndef __JUCE_STRINGARRAY_JUCEHEADER__
#define __JUCE_STRINGARRAY_JUCEHEADER__

/**
	A special array for holding a list of strings.

	@see String, StringPairArray
*/
class JUCE_API  StringArray
{
public:

	/** Creates an empty string array */
	StringArray() noexcept;

	/** Creates a copy of another string array */
	StringArray (const StringArray& other);

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	StringArray (StringArray&& other) noexcept;
   #endif

	/** Creates an array containing a single string. */
	explicit StringArray (const String& firstValue);

	/** Creates a copy of an array of string literals.
		@param strings          an array of strings to add. Null pointers in the array will be
								treated as empty strings
		@param numberOfStrings  how many items there are in the array
	*/
	StringArray (const char* const* strings, int numberOfStrings);

	/** Creates a copy of a null-terminated array of string literals.

		Each item from the array passed-in is added, until it encounters a null pointer,
		at which point it stops.
	*/
	explicit StringArray (const char* const* strings);

	/** Creates a copy of a null-terminated array of string literals.
		Each item from the array passed-in is added, until it encounters a null pointer,
		at which point it stops.
	*/
	explicit StringArray (const wchar_t* const* strings);

	/** Creates a copy of an array of string literals.
		@param strings          an array of strings to add. Null pointers in the array will be
								treated as empty strings
		@param numberOfStrings  how many items there are in the array
	*/
	StringArray (const wchar_t* const* strings, int numberOfStrings);

	/** Destructor. */
	~StringArray();

	/** Copies the contents of another string array into this one */
	StringArray& operator= (const StringArray& other);

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	StringArray& operator= (StringArray&& other) noexcept;
   #endif

	/** Compares two arrays.
		Comparisons are case-sensitive.
		@returns    true only if the other array contains exactly the same strings in the same order
	*/
	bool operator== (const StringArray& other) const noexcept;

	/** Compares two arrays.
		Comparisons are case-sensitive.
		@returns    false if the other array contains exactly the same strings in the same order
	*/
	bool operator!= (const StringArray& other) const noexcept;

	/** Returns the number of strings in the array */
	inline int size() const noexcept                                    { return strings.size(); };

	/** Returns one of the strings from the array.

		If the index is out-of-range, an empty string is returned.

		Obviously the reference returned shouldn't be stored for later use, as the
		string it refers to may disappear when the array changes.
	*/
	const String& operator[] (int index) const noexcept;

	/** Returns a reference to one of the strings in the array.
		This lets you modify a string in-place in the array, but you must be sure that
		the index is in-range.
	*/
	String& getReference (int index) noexcept;

	/** Searches for a string in the array.

		The comparison will be case-insensitive if the ignoreCase parameter is true.

		@returns    true if the string is found inside the array
	*/
	bool contains (const String& stringToLookFor,
				   bool ignoreCase = false) const;

	/** Searches for a string in the array.

		The comparison will be case-insensitive if the ignoreCase parameter is true.

		@param stringToLookFor  the string to try to find
		@param ignoreCase       whether the comparison should be case-insensitive
		@param startIndex       the first index to start searching from
		@returns                the index of the first occurrence of the string in this array,
								or -1 if it isn't found.
	*/
	int indexOf (const String& stringToLookFor,
				 bool ignoreCase = false,
				 int startIndex = 0) const;

	/** Appends a string at the end of the array. */
	void add (const String& stringToAdd);

	/** Inserts a string into the array.

		This will insert a string into the array at the given index, moving
		up the other elements to make room for it.
		If the index is less than zero or greater than the size of the array,
		the new string will be added to the end of the array.
	*/
	void insert (int index, const String& stringToAdd);

	/** Adds a string to the array as long as it's not already in there.

		The search can optionally be case-insensitive.
	*/
	void addIfNotAlreadyThere (const String& stringToAdd, bool ignoreCase = false);

	/** Replaces one of the strings in the array with another one.

		If the index is higher than the array's size, the new string will be
		added to the end of the array; if it's less than zero nothing happens.
	*/
	void set (int index, const String& newString);

	/** Appends some strings from another array to the end of this one.

		@param other                the array to add
		@param startIndex           the first element of the other array to add
		@param numElementsToAdd     the maximum number of elements to add (if this is
									less than zero, they are all added)
	*/
	void addArray (const StringArray& other,
				   int startIndex = 0,
				   int numElementsToAdd = -1);

	/** Breaks up a string into tokens and adds them to this array.

		This will tokenise the given string using whitespace characters as the
		token delimiters, and will add these tokens to the end of the array.

		@returns    the number of tokens added
	*/
	int addTokens (const String& stringToTokenise,
				   bool preserveQuotedStrings);

	/** Breaks up a string into tokens and adds them to this array.

		This will tokenise the given string (using the string passed in to define the
		token delimiters), and will add these tokens to the end of the array.

		@param stringToTokenise     the string to tokenise
		@param breakCharacters      a string of characters, any of which will be considered
									to be a token delimiter.
		@param quoteCharacters      if this string isn't empty, it defines a set of characters
									which are treated as quotes. Any text occurring
									between quotes is not broken up into tokens.
		@returns    the number of tokens added
	*/
	int addTokens (const String& stringToTokenise,
				   const String& breakCharacters,
				   const String& quoteCharacters);

	/** Breaks up a string into lines and adds them to this array.

		This breaks a string down into lines separated by \\n or \\r\\n, and adds each line
		to the array. Line-break characters are omitted from the strings that are added to
		the array.
	*/
	int addLines (const String& stringToBreakUp);

	/** Removes all elements from the array. */
	void clear();

	/** Removes a string from the array.

		If the index is out-of-range, no action will be taken.
	*/
	void remove (int index);

	/** Finds a string in the array and removes it.

		This will remove the first occurrence of the given string from the array. The
		comparison may be case-insensitive depending on the ignoreCase parameter.
	*/
	void removeString (const String& stringToRemove,
					   bool ignoreCase = false);

	/** Removes a range of elements from the array.

		This will remove a set of elements, starting from the given index,
		and move subsequent elements down to close the gap.

		If the range extends beyond the bounds of the array, it will
		be safely clipped to the size of the array.

		@param startIndex       the index of the first element to remove
		@param numberToRemove   how many elements should be removed
	*/
	void removeRange (int startIndex, int numberToRemove);

	/** Removes any duplicated elements from the array.

		If any string appears in the array more than once, only the first occurrence of
		it will be retained.

		@param ignoreCase   whether to use a case-insensitive comparison
	*/
	void removeDuplicates (bool ignoreCase);

	/** Removes empty strings from the array.

		@param removeWhitespaceStrings  if true, strings that only contain whitespace
										characters will also be removed
	*/
	void removeEmptyStrings (bool removeWhitespaceStrings = true);

	/** Moves one of the strings to a different position.

		This will move the string to a specified index, shuffling along
		any intervening elements as required.

		So for example, if you have the array { 0, 1, 2, 3, 4, 5 } then calling
		move (2, 4) would result in { 0, 1, 3, 4, 2, 5 }.

		@param currentIndex     the index of the value to be moved. If this isn't a
								valid index, then nothing will be done
		@param newIndex         the index at which you'd like this value to end up. If this
								is less than zero, the value will be moved to the end
								of the array
	*/
	void move (int currentIndex, int newIndex) noexcept;

	/** Deletes any whitespace characters from the starts and ends of all the strings. */
	void trim();

	/** Adds numbers to the strings in the array, to make each string unique.

		This will add numbers to the ends of groups of similar strings.
		e.g. if there are two "moose" strings, they will become "moose (1)" and "moose (2)"

		@param ignoreCaseWhenComparing      whether the comparison used is case-insensitive
		@param appendNumberToFirstInstance  whether the first of a group of similar strings
											also has a number appended to it.
		@param preNumberString              when adding a number, this string is added before the number.
											If you pass 0, a default string will be used, which adds
											brackets around the number.
		@param postNumberString             this string is appended after any numbers that are added.
											If you pass 0, a default string will be used, which adds
											brackets around the number.
	*/
	void appendNumbersToDuplicates (bool ignoreCaseWhenComparing,
									bool appendNumberToFirstInstance,
									CharPointer_UTF8 preNumberString = CharPointer_UTF8 (nullptr),
									CharPointer_UTF8 postNumberString = CharPointer_UTF8 (nullptr));

	/** Joins the strings in the array together into one string.

		This will join a range of elements from the array into a string, separating
		them with a given string.

		e.g. joinIntoString (",") will turn an array of "a" "b" and "c" into "a,b,c".

		@param separatorString      the string to insert between all the strings
		@param startIndex           the first element to join
		@param numberOfElements     how many elements to join together. If this is less
									than zero, all available elements will be used.
	*/
	String joinIntoString (const String& separatorString,
						   int startIndex = 0,
						   int numberOfElements = -1) const;

	/** Sorts the array into alphabetical order.

		@param ignoreCase       if true, the comparisons used will be case-sensitive.
	*/
	void sort (bool ignoreCase);

	/** Reduces the amount of storage being used by the array.

		Arrays typically allocate slightly more storage than they need, and after
		removing elements, they may have quite a lot of unused space allocated.
		This method will reduce the amount of allocated storage to a minimum.
	*/
	void minimiseStorageOverheads();

private:

	Array <String> strings;

	JUCE_LEAK_DETECTOR (StringArray);
};

#endif   // __JUCE_STRINGARRAY_JUCEHEADER__

/*** End of inlined file: juce_StringArray.h ***/

/**
	A container for holding a set of strings which are keyed by another string.

	@see StringArray
*/
class JUCE_API  StringPairArray
{
public:

	/** Creates an empty array */
	StringPairArray (bool ignoreCaseWhenComparingKeys = true);

	/** Creates a copy of another array */
	StringPairArray (const StringPairArray& other);

	/** Destructor. */
	~StringPairArray();

	/** Copies the contents of another string array into this one */
	StringPairArray& operator= (const StringPairArray& other);

	/** Compares two arrays.
		Comparisons are case-sensitive.
		@returns    true only if the other array contains exactly the same strings with the same keys
	*/
	bool operator== (const StringPairArray& other) const;

	/** Compares two arrays.
		Comparisons are case-sensitive.
		@returns    false if the other array contains exactly the same strings with the same keys
	*/
	bool operator!= (const StringPairArray& other) const;

	/** Finds the value corresponding to a key string.

		If no such key is found, this will just return an empty string. To check whether
		a given key actually exists (because it might actually be paired with an empty string), use
		the getAllKeys() method to obtain a list.

		Obviously the reference returned shouldn't be stored for later use, as the
		string it refers to may disappear when the array changes.

		@see getValue
	*/
	const String& operator[] (const String& key) const;

	/** Finds the value corresponding to a key string.

		If no such key is found, this will just return the value provided as a default.

		@see operator[]
	*/
	String getValue (const String& key, const String& defaultReturnValue) const;

	/** Returns a list of all keys in the array. */
	const StringArray& getAllKeys() const noexcept          { return keys; }

	/** Returns a list of all values in the array. */
	const StringArray& getAllValues() const noexcept        { return values; }

	/** Returns the number of strings in the array */
	inline int size() const noexcept                        { return keys.size(); };

	/** Adds or amends a key/value pair.

		If a value already exists with this key, its value will be overwritten,
		otherwise the key/value pair will be added to the array.
	*/
	void set (const String& key, const String& value);

	/** Adds the items from another array to this one.

		This is equivalent to using set() to add each of the pairs from the other array.
	*/
	void addArray (const StringPairArray& other);

	/** Removes all elements from the array. */
	void clear();

	/** Removes a string from the array based on its key.

		If the key isn't found, nothing will happen.
	*/
	void remove (const String& key);

	/** Removes a string from the array based on its index.

		If the index is out-of-range, no action will be taken.
	*/
	void remove (int index);

	/** Indicates whether to use a case-insensitive search when looking up a key string.
	*/
	void setIgnoresCase (bool shouldIgnoreCase);

	/** Returns a descriptive string containing the items.
		This is handy for dumping the contents of an array.
	*/
	String getDescription() const;

	/** Reduces the amount of storage being used by the array.

		Arrays typically allocate slightly more storage than they need, and after
		removing elements, they may have quite a lot of unused space allocated.
		This method will reduce the amount of allocated storage to a minimum.
	*/
	void minimiseStorageOverheads();

private:

	StringArray keys, values;
	bool ignoreCase;

	JUCE_LEAK_DETECTOR (StringPairArray);
};

#endif   // __JUCE_STRINGPAIRARRAY_JUCEHEADER__

/*** End of inlined file: juce_StringPairArray.h ***/


/*** Start of inlined file: juce_XmlElement.h ***/
#ifndef __JUCE_XMLELEMENT_JUCEHEADER__
#define __JUCE_XMLELEMENT_JUCEHEADER__


/*** Start of inlined file: juce_File.h ***/
#ifndef __JUCE_FILE_JUCEHEADER__
#define __JUCE_FILE_JUCEHEADER__


/*** Start of inlined file: juce_Time.h ***/
#ifndef __JUCE_TIME_JUCEHEADER__
#define __JUCE_TIME_JUCEHEADER__


/*** Start of inlined file: juce_RelativeTime.h ***/
#ifndef __JUCE_RELATIVETIME_JUCEHEADER__
#define __JUCE_RELATIVETIME_JUCEHEADER__

/** A relative measure of time.

	The time is stored as a number of seconds, at double-precision floating
	point accuracy, and may be positive or negative.

	If you need an absolute time, (i.e. a date + time), see the Time class.
*/
class JUCE_API  RelativeTime
{
public:

	/** Creates a RelativeTime.

		@param seconds  the number of seconds, which may be +ve or -ve.
		@see milliseconds, minutes, hours, days, weeks
	*/
	explicit RelativeTime (double seconds = 0.0) noexcept;

	/** Copies another relative time. */
	RelativeTime (const RelativeTime& other) noexcept;

	/** Copies another relative time. */
	RelativeTime& operator= (const RelativeTime& other) noexcept;

	/** Destructor. */
	~RelativeTime() noexcept;

	/** Creates a new RelativeTime object representing a number of milliseconds.
		@see minutes, hours, days, weeks
	*/
	static const RelativeTime milliseconds (int milliseconds) noexcept;

	/** Creates a new RelativeTime object representing a number of milliseconds.
		@see minutes, hours, days, weeks
	*/
	static const RelativeTime milliseconds (int64 milliseconds) noexcept;

	/** Creates a new RelativeTime object representing a number of minutes.
		@see milliseconds, hours, days, weeks
	*/
	static const RelativeTime minutes (double numberOfMinutes) noexcept;

	/** Creates a new RelativeTime object representing a number of hours.
		@see milliseconds, minutes, days, weeks
	*/
	static const RelativeTime hours (double numberOfHours) noexcept;

	/** Creates a new RelativeTime object representing a number of days.
		@see milliseconds, minutes, hours, weeks
	*/
	static const RelativeTime days (double numberOfDays) noexcept;

	/** Creates a new RelativeTime object representing a number of weeks.
		@see milliseconds, minutes, hours, days
	*/
	static const RelativeTime weeks (double numberOfWeeks) noexcept;

	/** Returns the number of milliseconds this time represents.
		@see milliseconds, inSeconds, inMinutes, inHours, inDays, inWeeks
	*/
	int64 inMilliseconds() const noexcept;

	/** Returns the number of seconds this time represents.
		@see inMilliseconds, inMinutes, inHours, inDays, inWeeks
	*/
	double inSeconds() const noexcept       { return seconds; }

	/** Returns the number of minutes this time represents.
		@see inMilliseconds, inSeconds, inHours, inDays, inWeeks
	*/
	double inMinutes() const noexcept;

	/** Returns the number of hours this time represents.
		@see inMilliseconds, inSeconds, inMinutes, inDays, inWeeks
	*/
	double inHours() const noexcept;

	/** Returns the number of days this time represents.
		@see inMilliseconds, inSeconds, inMinutes, inHours, inWeeks
	*/
	double inDays() const noexcept;

	/** Returns the number of weeks this time represents.
		@see inMilliseconds, inSeconds, inMinutes, inHours, inDays
	*/
	double inWeeks() const noexcept;

	/** Returns a readable textual description of the time.

		The exact format of the string returned will depend on
		the magnitude of the time - e.g.

		"1 min 4 secs", "1 hr 45 mins", "2 weeks 5 days", "140 ms"

		so that only the two most significant units are printed.

		The returnValueForZeroTime value is the result that is returned if the
		length is zero. Depending on your application you might want to use this
		to return something more relevant like "empty" or "0 secs", etc.

		@see inMilliseconds, inSeconds, inMinutes, inHours, inDays, inWeeks
	*/
	String getDescription (const String& returnValueForZeroTime = "0") const;

	/** Adds another RelativeTime to this one. */
	const RelativeTime& operator+= (const RelativeTime& timeToAdd) noexcept;
	/** Subtracts another RelativeTime from this one. */
	const RelativeTime& operator-= (const RelativeTime& timeToSubtract) noexcept;

	/** Adds a number of seconds to this time. */
	const RelativeTime& operator+= (double secondsToAdd) noexcept;
	/** Subtracts a number of seconds from this time. */
	const RelativeTime& operator-= (double secondsToSubtract) noexcept;

private:

	double seconds;
};

/** Compares two RelativeTimes. */
bool operator== (const RelativeTime& t1, const RelativeTime& t2) noexcept;
/** Compares two RelativeTimes. */
bool operator!= (const RelativeTime& t1, const RelativeTime& t2) noexcept;
/** Compares two RelativeTimes. */
bool operator>  (const RelativeTime& t1, const RelativeTime& t2) noexcept;
/** Compares two RelativeTimes. */
bool operator<  (const RelativeTime& t1, const RelativeTime& t2) noexcept;
/** Compares two RelativeTimes. */
bool operator>= (const RelativeTime& t1, const RelativeTime& t2) noexcept;
/** Compares two RelativeTimes. */
bool operator<= (const RelativeTime& t1, const RelativeTime& t2) noexcept;

/** Adds two RelativeTimes together. */
RelativeTime  operator+  (const RelativeTime&  t1, const RelativeTime& t2) noexcept;
/** Subtracts two RelativeTimes. */
RelativeTime  operator-  (const RelativeTime&  t1, const RelativeTime& t2) noexcept;

#endif   // __JUCE_RELATIVETIME_JUCEHEADER__

/*** End of inlined file: juce_RelativeTime.h ***/

/**
	Holds an absolute date and time.

	Internally, the time is stored at millisecond precision.

	@see RelativeTime
*/
class JUCE_API  Time
{
public:

	/** Creates a Time object.

		This default constructor creates a time of 1st January 1970, (which is
		represented internally as 0ms).

		To create a time object representing the current time, use getCurrentTime().

		@see getCurrentTime
	*/
	Time() noexcept;

	/** Creates a time based on a number of milliseconds.

		The internal millisecond count is set to 0 (1st January 1970). To create a
		time object set to the current time, use getCurrentTime().

		@param millisecondsSinceEpoch   the number of milliseconds since the unix
										'epoch' (midnight Jan 1st 1970).
		@see getCurrentTime, currentTimeMillis
	*/
	explicit Time (int64 millisecondsSinceEpoch) noexcept;

	/** Creates a time from a set of date components.

		The timezone is assumed to be whatever the system is using as its locale.

		@param year             the year, in 4-digit format, e.g. 2004
		@param month            the month, in the range 0 to 11
		@param day              the day of the month, in the range 1 to 31
		@param hours            hours in 24-hour clock format, 0 to 23
		@param minutes          minutes 0 to 59
		@param seconds          seconds 0 to 59
		@param milliseconds     milliseconds 0 to 999
		@param useLocalTime     if true, encode using the current machine's local time; if
								false, it will always work in GMT.
	*/
	Time (int year,
		  int month,
		  int day,
		  int hours,
		  int minutes,
		  int seconds = 0,
		  int milliseconds = 0,
		  bool useLocalTime = true) noexcept;

	/** Creates a copy of another Time object. */
	Time (const Time& other) noexcept;

	/** Destructor. */
	~Time() noexcept;

	/** Copies this time from another one. */
	Time& operator= (const Time& other) noexcept;

	/** Returns a Time object that is set to the current system time.

		@see currentTimeMillis
	*/
	static Time JUCE_CALLTYPE getCurrentTime() noexcept;

	/** Returns the time as a number of milliseconds.

		@returns    the number of milliseconds this Time object represents, since
					midnight jan 1st 1970.
		@see getMilliseconds
	*/
	int64 toMilliseconds() const noexcept                           { return millisSinceEpoch; }

	/** Returns the year.

		A 4-digit format is used, e.g. 2004.
	*/
	int getYear() const noexcept;

	/** Returns the number of the month.

		The value returned is in the range 0 to 11.
		@see getMonthName
	*/
	int getMonth() const noexcept;

	/** Returns the name of the month.

		@param threeLetterVersion   if true, it'll be a 3-letter abbreviation, e.g. "Jan"; if false
									it'll return the long form, e.g. "January"
		@see getMonth
	*/
	String getMonthName (bool threeLetterVersion) const;

	/** Returns the day of the month.
		The value returned is in the range 1 to 31.
	*/
	int getDayOfMonth() const noexcept;

	/** Returns the number of the day of the week.
		The value returned is in the range 0 to 6 (0 = sunday, 1 = monday, etc).
	*/
	int getDayOfWeek() const noexcept;

	/** Returns the number of the day of the year.
		The value returned is in the range 0 to 365.
	*/
	int getDayOfYear() const noexcept;

	/** Returns the name of the weekday.

		@param threeLetterVersion   if true, it'll return a 3-letter abbreviation, e.g. "Tue"; if
									false, it'll return the full version, e.g. "Tuesday".
	*/
	String getWeekdayName (bool threeLetterVersion) const;

	/** Returns the number of hours since midnight.

		This is in 24-hour clock format, in the range 0 to 23.

		@see getHoursInAmPmFormat, isAfternoon
	*/
	int getHours() const noexcept;

	/** Returns true if the time is in the afternoon.

		So it returns true for "PM", false for "AM".

		@see getHoursInAmPmFormat, getHours
	*/
	bool isAfternoon() const noexcept;

	/** Returns the hours in 12-hour clock format.

		This will return a value 1 to 12 - use isAfternoon() to find out
		whether this is in the afternoon or morning.

		@see getHours, isAfternoon
	*/
	int getHoursInAmPmFormat() const noexcept;

	/** Returns the number of minutes, 0 to 59. */
	int getMinutes() const noexcept;

	/** Returns the number of seconds, 0 to 59. */
	int getSeconds() const noexcept;

	/** Returns the number of milliseconds, 0 to 999.

		Unlike toMilliseconds(), this just returns the position within the
		current second rather than the total number since the epoch.

		@see toMilliseconds
	*/
	int getMilliseconds() const noexcept;

	/** Returns true if the local timezone uses a daylight saving correction. */
	bool isDaylightSavingTime() const noexcept;

	/** Returns a 3-character string to indicate the local timezone. */
	String getTimeZone() const noexcept;

	/** Quick way of getting a string version of a date and time.

		For a more powerful way of formatting the date and time, see the formatted() method.

		@param includeDate      whether to include the date in the string
		@param includeTime      whether to include the time in the string
		@param includeSeconds   if the time is being included, this provides an option not to include
								the seconds in it
		@param use24HourClock   if the time is being included, sets whether to use am/pm or 24
								hour notation.
		@see formatted
	*/
	String toString (bool includeDate,
					 bool includeTime,
					 bool includeSeconds = true,
					 bool use24HourClock = false) const noexcept;

	/** Converts this date/time to a string with a user-defined format.

		This uses the C strftime() function to format this time as a string. To save you
		looking it up, these are the escape codes that strftime uses (other codes might
		work on some platforms and not others, but these are the common ones):

		%a  is replaced by the locale's abbreviated weekday name.
		%A  is replaced by the locale's full weekday name.
		%b  is replaced by the locale's abbreviated month name.
		%B  is replaced by the locale's full month name.
		%c  is replaced by the locale's appropriate date and time representation.
		%d  is replaced by the day of the month as a decimal number [01,31].
		%H  is replaced by the hour (24-hour clock) as a decimal number [00,23].
		%I  is replaced by the hour (12-hour clock) as a decimal number [01,12].
		%j  is replaced by the day of the year as a decimal number [001,366].
		%m  is replaced by the month as a decimal number [01,12].
		%M  is replaced by the minute as a decimal number [00,59].
		%p  is replaced by the locale's equivalent of either a.m. or p.m.
		%S  is replaced by the second as a decimal number [00,61].
		%U  is replaced by the week number of the year (Sunday as the first day of the week) as a decimal number [00,53].
		%w  is replaced by the weekday as a decimal number [0,6], with 0 representing Sunday.
		%W  is replaced by the week number of the year (Monday as the first day of the week) as a decimal number [00,53]. All days in a new year preceding the first Monday are considered to be in week 0.
		%x  is replaced by the locale's appropriate date representation.
		%X  is replaced by the locale's appropriate time representation.
		%y  is replaced by the year without century as a decimal number [00,99].
		%Y  is replaced by the year with century as a decimal number.
		%Z  is replaced by the timezone name or abbreviation, or by no bytes if no timezone information exists.
		%%  is replaced by %.

		@see toString
	*/
	String formatted (const String& format) const;

	/** Adds a RelativeTime to this time. */
	Time& operator+= (const RelativeTime& delta);
	/** Subtracts a RelativeTime from this time. */
	Time& operator-= (const RelativeTime& delta);

	/** Tries to set the computer's clock.

		@returns    true if this succeeds, although depending on the system, the
					application might not have sufficient privileges to do this.
	*/
	bool setSystemTimeToThisTime() const;

	/** Returns the name of a day of the week.

		@param dayNumber            the day, 0 to 6 (0 = sunday, 1 = monday, etc)
		@param threeLetterVersion   if true, it'll return a 3-letter abbreviation, e.g. "Tue"; if
									false, it'll return the full version, e.g. "Tuesday".
	*/
	static String getWeekdayName (int dayNumber,
								  bool threeLetterVersion);

	/** Returns the name of one of the months.

		@param monthNumber  the month, 0 to 11
		@param threeLetterVersion   if true, it'll be a 3-letter abbreviation, e.g. "Jan"; if false
									it'll return the long form, e.g. "January"
	*/
	static String getMonthName (int monthNumber,
								bool threeLetterVersion);

	// Static methods for getting system timers directly..

	/** Returns the current system time.

		Returns the number of milliseconds since midnight jan 1st 1970.

		Should be accurate to within a few millisecs, depending on platform,
		hardware, etc.
	*/
	static int64 currentTimeMillis() noexcept;

	/** Returns the number of millisecs since a fixed event (usually system startup).

		This returns a monotonically increasing value which it unaffected by changes to the
		system clock. It should be accurate to within a few millisecs, depending on platform,
		hardware, etc.

		Being a 32-bit return value, it will of course wrap back to 0 after 2^32 seconds of
		uptime, so be careful to take that into account. If you need a 64-bit time, you can
		use currentTimeMillis() instead.

		@see getApproximateMillisecondCounter
	*/
	static uint32 getMillisecondCounter() noexcept;

	/** Returns the number of millisecs since a fixed event (usually system startup).

		This has the same function as getMillisecondCounter(), but returns a more accurate
		value, using a higher-resolution timer if one is available.

		@see getMillisecondCounter
	*/
	static double getMillisecondCounterHiRes() noexcept;

	/** Waits until the getMillisecondCounter() reaches a given value.

		This will make the thread sleep as efficiently as it can while it's waiting.
	*/
	static void waitForMillisecondCounter (uint32 targetTime) noexcept;

	/** Less-accurate but faster version of getMillisecondCounter().

		This will return the last value that getMillisecondCounter() returned, so doesn't
		need to make a system call, but is less accurate - it shouldn't be more than
		100ms away from the correct time, though, so is still accurate enough for a
		lot of purposes.

		@see getMillisecondCounter
	*/
	static uint32 getApproximateMillisecondCounter() noexcept;

	// High-resolution timers..

	/** Returns the current high-resolution counter's tick-count.

		This is a similar idea to getMillisecondCounter(), but with a higher
		resolution.

		@see getHighResolutionTicksPerSecond, highResolutionTicksToSeconds,
			 secondsToHighResolutionTicks
	*/
	static int64 getHighResolutionTicks() noexcept;

	/** Returns the resolution of the high-resolution counter in ticks per second.

		@see getHighResolutionTicks, highResolutionTicksToSeconds,
			 secondsToHighResolutionTicks
	*/
	static int64 getHighResolutionTicksPerSecond() noexcept;

	/** Converts a number of high-resolution ticks into seconds.

		@see getHighResolutionTicks, getHighResolutionTicksPerSecond,
			 secondsToHighResolutionTicks
	*/
	static double highResolutionTicksToSeconds (int64 ticks) noexcept;

	/** Converts a number seconds into high-resolution ticks.

		@see getHighResolutionTicks, getHighResolutionTicksPerSecond,
			 highResolutionTicksToSeconds
	*/
	static int64 secondsToHighResolutionTicks (double seconds) noexcept;

private:

	int64 millisSinceEpoch;
};

/** Adds a RelativeTime to a Time. */
JUCE_API Time operator+ (const Time& time, const RelativeTime& delta);
/** Adds a RelativeTime to a Time. */
JUCE_API Time operator+ (const RelativeTime& delta, const Time& time);

/** Subtracts a RelativeTime from a Time. */
JUCE_API Time operator- (const Time& time, const RelativeTime& delta);
/** Returns the relative time difference between two times. */
JUCE_API const RelativeTime operator- (const Time& time1, const Time& time2);

/** Compares two Time objects. */
JUCE_API bool operator== (const Time& time1, const Time& time2);
/** Compares two Time objects. */
JUCE_API bool operator!= (const Time& time1, const Time& time2);
/** Compares two Time objects. */
JUCE_API bool operator<  (const Time& time1, const Time& time2);
/** Compares two Time objects. */
JUCE_API bool operator<= (const Time& time1, const Time& time2);
/** Compares two Time objects. */
JUCE_API bool operator>  (const Time& time1, const Time& time2);
/** Compares two Time objects. */
JUCE_API bool operator>= (const Time& time1, const Time& time2);

#endif   // __JUCE_TIME_JUCEHEADER__

/*** End of inlined file: juce_Time.h ***/


/*** Start of inlined file: juce_MemoryBlock.h ***/
#ifndef __JUCE_MEMORYBLOCK_JUCEHEADER__
#define __JUCE_MEMORYBLOCK_JUCEHEADER__

/**
	A class to hold a resizable block of raw data.

*/
class JUCE_API  MemoryBlock
{
public:

	/** Create an uninitialised block with 0 size. */
	MemoryBlock() noexcept;

	/** Creates a memory block with a given initial size.

		@param initialSize          the size of block to create
		@param initialiseToZero     whether to clear the memory or just leave it uninitialised
	*/
	MemoryBlock (const size_t initialSize,
				 bool initialiseToZero = false);

	/** Creates a copy of another memory block. */
	MemoryBlock (const MemoryBlock& other);

	/** Creates a memory block using a copy of a block of data.

		@param dataToInitialiseFrom     some data to copy into this block
		@param sizeInBytes              how much space to use
	*/
	MemoryBlock (const void* dataToInitialiseFrom, size_t sizeInBytes);

	/** Destructor. */
	~MemoryBlock() noexcept;

	/** Copies another memory block onto this one.

		This block will be resized and copied to exactly match the other one.
	*/
	MemoryBlock& operator= (const MemoryBlock& other);

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	MemoryBlock (MemoryBlock&& other) noexcept;
	MemoryBlock& operator= (MemoryBlock&& other) noexcept;
   #endif

	/** Compares two memory blocks.

		@returns true only if the two blocks are the same size and have identical contents.
	*/
	bool operator== (const MemoryBlock& other) const noexcept;

	/** Compares two memory blocks.

		@returns true if the two blocks are different sizes or have different contents.
	*/
	bool operator!= (const MemoryBlock& other) const noexcept;

	/** Returns true if the data in this MemoryBlock matches the raw bytes passed-in.
	*/
	bool matches (const void* data, size_t dataSize) const noexcept;

	/** Returns a void pointer to the data.

		Note that the pointer returned will probably become invalid when the
		block is resized.
	*/
	void* getData() const noexcept                                  { return data; }

	/** Returns a byte from the memory block.

		This returns a reference, so you can also use it to set a byte.
	*/
	template <typename Type>
	char& operator[] (const Type offset) const noexcept             { return data [offset]; }

	/** Returns the block's current allocated size, in bytes. */
	size_t getSize() const noexcept                                 { return size; }

	/** Resizes the memory block.

		This will try to keep as much of the block's current content as it can,
		and can optionally be made to clear any new space that gets allocated at
		the end of the block.

		@param newSize                      the new desired size for the block
		@param initialiseNewSpaceToZero     if the block gets enlarged, this determines
											whether to clear the new section or just leave it
											uninitialised
		@see ensureSize
	*/
	void setSize (const size_t newSize,
				  bool initialiseNewSpaceToZero = false);

	/** Increases the block's size only if it's smaller than a given size.

		@param minimumSize                  if the block is already bigger than this size, no action
											will be taken; otherwise it will be increased to this size
		@param initialiseNewSpaceToZero     if the block gets enlarged, this determines
											whether to clear the new section or just leave it
											uninitialised
		@see setSize
	*/
	void ensureSize (const size_t minimumSize,
					 bool initialiseNewSpaceToZero = false);

	/** Fills the entire memory block with a repeated byte value.

		This is handy for clearing a block of memory to zero.
	*/
	void fillWith (uint8 valueToUse) noexcept;

	/** Adds another block of data to the end of this one.
		The data pointer must not be null. This block's size will be increased accordingly.
	*/
	void append (const void* data, size_t numBytes);

	/** Inserts some data into the block.
		The dataToInsert pointer must not be null. This block's size will be increased accordingly.
		If the insert position lies outside the valid range of the block, it will be clipped to
		within the range before being used.
	*/
	void insert (const void* dataToInsert, size_t numBytesToInsert, size_t insertPosition);

	/** Chops out a section  of the block.

		This will remove a section of the memory block and close the gap around it,
		shifting any subsequent data downwards and reducing the size of the block.

		If the range specified goes beyond the size of the block, it will be clipped.
	*/
	void removeSection (size_t startByte, size_t numBytesToRemove);

	/** Copies data into this MemoryBlock from a memory address.

		@param srcData              the memory location of the data to copy into this block
		@param destinationOffset    the offset in this block at which the data being copied should begin
		@param numBytes             how much to copy in (if this goes beyond the size of the memory block,
									it will be clipped so not to do anything nasty)
	*/
	void copyFrom (const void* srcData,
				   int destinationOffset,
				   size_t numBytes) noexcept;

	/** Copies data from this MemoryBlock to a memory address.

		@param destData         the memory location to write to
		@param sourceOffset     the offset within this block from which the copied data will be read
		@param numBytes         how much to copy (if this extends beyond the limits of the memory block,
								zeros will be used for that portion of the data)
	*/
	void copyTo (void* destData,
				 int sourceOffset,
				 size_t numBytes) const noexcept;

	/** Exchanges the contents of this and another memory block.
		No actual copying is required for this, so it's very fast.
	*/
	void swapWith (MemoryBlock& other) noexcept;

	/** Attempts to parse the contents of the block as a zero-terminated UTF8 string. */
	String toString() const;

	/** Parses a string of hexadecimal numbers and writes this data into the memory block.

		The block will be resized to the number of valid bytes read from the string.
		Non-hex characters in the string will be ignored.

		@see String::toHexString()
	*/
	void loadFromHexString (const String& sourceHexString);

	/** Sets a number of bits in the memory block, treating it as a long binary sequence. */
	void setBitRange (size_t bitRangeStart,
					  size_t numBits,
					  int binaryNumberToApply) noexcept;

	/** Reads a number of bits from the memory block, treating it as one long binary sequence */
	int getBitRange (size_t bitRangeStart,
					 size_t numBitsToRead) const noexcept;

	/** Returns a string of characters that represent the binary contents of this block.

		Uses a 64-bit encoding system to allow binary data to be turned into a string
		of simple non-extended characters, e.g. for storage in XML.

		@see fromBase64Encoding
	*/
	String toBase64Encoding() const;

	/** Takes a string of encoded characters and turns it into binary data.

		The string passed in must have been created by to64BitEncoding(), and this
		block will be resized to recreate the original data block.

		@see toBase64Encoding
	*/
	bool fromBase64Encoding  (const String& encodedString);

private:

	HeapBlock <char> data;
	size_t size;
	static const char* const encodingTable;

	JUCE_LEAK_DETECTOR (MemoryBlock);
};

#endif   // __JUCE_MEMORYBLOCK_JUCEHEADER__

/*** End of inlined file: juce_MemoryBlock.h ***/


/*** Start of inlined file: juce_Result.h ***/
#ifndef __JUCE_RESULT_JUCEHEADER__
#define __JUCE_RESULT_JUCEHEADER__

/**
	Represents the 'success' or 'failure' of an operation, and holds an associated
	error message to describe the error when there's a failure.

	E.g.
	@code
	Result myOperation()
	{
		if (doSomeKindOfFoobar())
			return Result::ok();
		else
			return Result::fail ("foobar didn't work!");
	}

	const Result result (myOperation());

	if (result.wasOk())
	{
		...it's all good...
	}
	else
	{
		warnUserAboutFailure ("The foobar operation failed! Error message was: "
								+ result.getErrorMessage());
	}
	@endcode
*/
class JUCE_API  Result
{
public:

	/** Creates and returns a 'successful' result. */
	static Result ok() noexcept;

	/** Creates a 'failure' result.
		If you pass a blank error message in here, a default "Unknown Error" message
		will be used instead.
	*/
	static Result fail (const String& errorMessage) noexcept;

	/** Returns true if this result indicates a success. */
	bool wasOk() const noexcept;

	/** Returns true if this result indicates a failure.
		You can use getErrorMessage() to retrieve the error message associated
		with the failure.
	*/
	bool failed() const noexcept;

	/** Returns true if this result indicates a success.
		This is equivalent to calling wasOk().
	*/
	operator bool() const noexcept;

	/** Returns true if this result indicates a failure.
		This is equivalent to calling failed().
	*/
	bool operator!() const noexcept;

	/** Returns the error message that was set when this result was created.
		For a successful result, this will be an empty string;
	*/
	const String& getErrorMessage() const noexcept;

	Result (const Result& other);
	Result& operator= (const Result& other);

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	Result (Result&& other) noexcept;
	Result& operator= (Result&& other) noexcept;
   #endif

	bool operator== (const Result& other) const noexcept;
	bool operator!= (const Result& other) const noexcept;

private:
	String errorMessage;

	explicit Result (const String& errorMessage) noexcept;

	// These casts are private to prevent people trying to use the Result object in numeric contexts
	operator int() const;
	operator void*() const;
};

#endif   // __JUCE_RESULT_JUCEHEADER__

/*** End of inlined file: juce_Result.h ***/

class FileInputStream;
class FileOutputStream;

/**
	Represents a local file or directory.

	This class encapsulates the absolute pathname of a file or directory, and
	has methods for finding out about the file and changing its properties.

	To read or write to the file, there are methods for returning an input or
	output stream.

	@see FileInputStream, FileOutputStream
*/
class JUCE_API  File
{
public:

	/** Creates an (invalid) file object.

		The file is initially set to an empty path, so getFullPath() will return
		an empty string, and comparing the file to File::nonexistent will return
		true.

		You can use its operator= method to point it at a proper file.
	*/
	File()   {}

	/** Creates a file from an absolute path.

		If the path supplied is a relative path, it is taken to be relative
		to the current working directory (see File::getCurrentWorkingDirectory()),
		but this isn't a recommended way of creating a file, because you
		never know what the CWD is going to be.

		On the Mac/Linux, the path can include "~" notation for referring to
		user home directories.
	*/
	File (const String& path);

	/** Creates a copy of another file object. */
	File (const File& other);

	/** Destructor. */
	~File()  {}

	/** Sets the file based on an absolute pathname.

		If the path supplied is a relative path, it is taken to be relative
		to the current working directory (see File::getCurrentWorkingDirectory()),
		but this isn't a recommended way of creating a file, because you
		never know what the CWD is going to be.

		On the Mac/Linux, the path can include "~" notation for referring to
		user home directories.
	*/
	File& operator= (const String& newFilePath);

	/** Copies from another file object. */
	File& operator= (const File& otherFile);

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	File (File&& otherFile) noexcept;
	File& operator= (File&& otherFile) noexcept;
   #endif

	/** This static constant is used for referring to an 'invalid' file. */
	static const File nonexistent;

	/** Checks whether the file actually exists.

		@returns    true if the file exists, either as a file or a directory.
		@see existsAsFile, isDirectory
	*/
	bool exists() const;

	/** Checks whether the file exists and is a file rather than a directory.

		@returns    true only if this is a real file, false if it's a directory
					or doesn't exist
		@see exists, isDirectory
	*/
	bool existsAsFile() const;

	/** Checks whether the file is a directory that exists.

		@returns    true only if the file is a directory which actually exists, so
					false if it's a file or doesn't exist at all
		@see exists, existsAsFile
	*/
	bool isDirectory() const;

	/** Returns the size of the file in bytes.

		@returns    the number of bytes in the file, or 0 if it doesn't exist.
	*/
	int64 getSize() const;

	/** Utility function to convert a file size in bytes to a neat string description.

		So for example 100 would return "100 bytes", 2000 would return "2 KB",
		2000000 would produce "2 MB", etc.
	*/
	static String descriptionOfSizeInBytes (int64 bytes);

	/** Returns the complete, absolute path of this file.

		This includes the filename and all its parent folders. On Windows it'll
		also include the drive letter prefix; on Mac or Linux it'll be a complete
		path starting from the root folder.

		If you just want the file's name, you should use getFileName() or
		getFileNameWithoutExtension().

		@see getFileName, getRelativePathFrom
	*/
	const String& getFullPathName() const noexcept          { return fullPath; }

	/** Returns the last section of the pathname.

		Returns just the final part of the path - e.g. if the whole path
		is "/moose/fish/foo.txt" this will return "foo.txt".

		For a directory, it returns the final part of the path - e.g. for the
		directory "/moose/fish" it'll return "fish".

		If the filename begins with a dot, it'll return the whole filename, e.g. for
		"/moose/.fish", it'll return ".fish"

		@see getFullPathName, getFileNameWithoutExtension
	*/
	String getFileName() const;

	/** Creates a relative path that refers to a file relatively to a given directory.

		e.g. File ("/moose/foo.txt").getRelativePathFrom (File ("/moose/fish/haddock"))
			 would return "../../foo.txt".

		If it's not possible to navigate from one file to the other, an absolute
		path is returned. If the paths are invalid, an empty string may also be
		returned.

		@param directoryToBeRelativeTo  the directory which the resultant string will
										be relative to. If this is actually a file rather than
										a directory, its parent directory will be used instead.
										If it doesn't exist, it's assumed to be a directory.
		@see getChildFile, isAbsolutePath
	*/
	String getRelativePathFrom (const File& directoryToBeRelativeTo) const;

	/** Returns the file's extension.

		Returns the file extension of this file, also including the dot.

		e.g. "/moose/fish/foo.txt" would return ".txt"

		@see hasFileExtension, withFileExtension, getFileNameWithoutExtension
	*/
	String getFileExtension() const;

	/** Checks whether the file has a given extension.

		@param extensionToTest  the extension to look for - it doesn't matter whether or
								not this string has a dot at the start, so ".wav" and "wav"
								will have the same effect. The comparison used is
								case-insensitve. To compare with multiple extensions, this
								parameter can contain multiple strings, separated by semi-colons -
								so, for example: hasFileExtension (".jpeg;png;gif") would return
								true if the file has any of those three extensions.

		@see getFileExtension, withFileExtension, getFileNameWithoutExtension
	*/
	bool hasFileExtension (const String& extensionToTest) const;

	/** Returns a version of this file with a different file extension.

		e.g. File ("/moose/fish/foo.txt").withFileExtension ("html") returns "/moose/fish/foo.html"

		@param newExtension     the new extension, either with or without a dot at the start (this
								doesn't make any difference). To get remove a file's extension altogether,
								pass an empty string into this function.

		@see getFileName, getFileExtension, hasFileExtension, getFileNameWithoutExtension
	*/
	File withFileExtension (const String& newExtension) const;

	/** Returns the last part of the filename, without its file extension.

		e.g. for "/moose/fish/foo.txt" this will return "foo".

		@see getFileName, getFileExtension, hasFileExtension, withFileExtension
	*/
	String getFileNameWithoutExtension() const;

	/** Returns a 32-bit hash-code that identifies this file.

		This is based on the filename. Obviously it's possible, although unlikely, that
		two files will have the same hash-code.
	*/
	int hashCode() const;

	/** Returns a 64-bit hash-code that identifies this file.

		This is based on the filename. Obviously it's possible, although unlikely, that
		two files will have the same hash-code.
	*/
	int64 hashCode64() const;

	/** Returns a file based on a relative path.

		This will find a child file or directory of the current object.

		e.g.
			File ("/moose/fish").getChildFile ("foo.txt") will produce "/moose/fish/foo.txt".
			File ("/moose/fish").getChildFile ("../foo.txt") will produce "/moose/foo.txt".

		If the string is actually an absolute path, it will be treated as such, e.g.
			File ("/moose/fish").getChildFile ("/foo.txt") will produce "/foo.txt"

		@see getSiblingFile, getParentDirectory, getRelativePathFrom, isAChildOf
	*/
	File getChildFile (String relativePath) const;

	/** Returns a file which is in the same directory as this one.

		This is equivalent to getParentDirectory().getChildFile (name).

		@see getChildFile, getParentDirectory
	*/
	File getSiblingFile (const String& siblingFileName) const;

	/** Returns the directory that contains this file or directory.

		e.g. for "/moose/fish/foo.txt" this will return "/moose/fish".
	*/
	File getParentDirectory() const;

	/** Checks whether a file is somewhere inside a directory.

		Returns true if this file is somewhere inside a subdirectory of the directory
		that is passed in. Neither file actually has to exist, because the function
		just checks the paths for similarities.

		e.g. File ("/moose/fish/foo.txt").isAChildOf ("/moose") is true.
			 File ("/moose/fish/foo.txt").isAChildOf ("/moose/fish") is also true.
	*/
	bool isAChildOf (const File& potentialParentDirectory) const;

	/** Chooses a filename relative to this one that doesn't already exist.

		If this file is a directory, this will return a child file of this
		directory that doesn't exist, by adding numbers to a prefix and suffix until
		it finds one that isn't already there.

		If the prefix + the suffix doesn't exist, it won't bother adding a number.

		e.g. File ("/moose/fish").getNonexistentChildFile ("foo", ".txt", true) might
			 return "/moose/fish/foo(2).txt" if there's already a file called "foo.txt".

		@param prefix                   the string to use for the filename before the number
		@param suffix                   the string to add to the filename after the number
		@param putNumbersInBrackets     if true, this will create filenames in the
										format "prefix(number)suffix", if false, it will leave the
										brackets out.
	*/
	File getNonexistentChildFile (const String& prefix,
								  const String& suffix,
								  bool putNumbersInBrackets = true) const;

	/** Chooses a filename for a sibling file to this one that doesn't already exist.

		If this file doesn't exist, this will just return itself, otherwise it
		will return an appropriate sibling that doesn't exist, e.g. if a file
		"/moose/fish/foo.txt" exists, this might return "/moose/fish/foo(2).txt".

		@param putNumbersInBrackets     whether to add brackets around the numbers that
										get appended to the new filename.
	*/
	File getNonexistentSibling (bool putNumbersInBrackets = true) const;

	/** Compares the pathnames for two files. */
	bool operator== (const File& otherFile) const;
	/** Compares the pathnames for two files. */
	bool operator!= (const File& otherFile) const;
	/** Compares the pathnames for two files. */
	bool operator< (const File& otherFile) const;
	/** Compares the pathnames for two files. */
	bool operator> (const File& otherFile) const;

	/** Checks whether a file can be created or written to.

		@returns    true if it's possible to create and write to this file. If the file
					doesn't already exist, this will check its parent directory to
					see if writing is allowed.
		@see setReadOnly
	*/
	bool hasWriteAccess() const;

	/** Changes the write-permission of a file or directory.

		@param shouldBeReadOnly     whether to add or remove write-permission
		@param applyRecursively     if the file is a directory and this is true, it will
									recurse through all the subfolders changing the permissions
									of all files
		@returns    true if it manages to change the file's permissions.
		@see hasWriteAccess
	*/
	bool setReadOnly (bool shouldBeReadOnly,
					  bool applyRecursively = false) const;

	/** Returns true if this file is a hidden or system file.

		The criteria for deciding whether a file is hidden are platform-dependent.
	*/
	bool isHidden() const;

	/** If this file is a link, this returns the file that it points to.

		If this file isn't actually link, it'll just return itself.
	*/
	File getLinkedTarget() const;

	/** Returns the last modification time of this file.

		@returns    the time, or an invalid time if the file doesn't exist.
		@see setLastModificationTime, getLastAccessTime, getCreationTime
	*/
	Time getLastModificationTime() const;

	/** Returns the last time this file was accessed.

		@returns    the time, or an invalid time if the file doesn't exist.
		@see setLastAccessTime, getLastModificationTime, getCreationTime
	*/
	Time getLastAccessTime() const;

	/** Returns the time that this file was created.

		@returns    the time, or an invalid time if the file doesn't exist.
		@see getLastModificationTime, getLastAccessTime
	*/
	Time getCreationTime() const;

	/** Changes the modification time for this file.

		@param newTime  the time to apply to the file
		@returns true if it manages to change the file's time.
		@see getLastModificationTime, setLastAccessTime, setCreationTime
	*/
	bool setLastModificationTime (const Time& newTime) const;

	/** Changes the last-access time for this file.

		@param newTime  the time to apply to the file
		@returns true if it manages to change the file's time.
		@see getLastAccessTime, setLastModificationTime, setCreationTime
	*/
	bool setLastAccessTime (const Time& newTime) const;

	/** Changes the creation date for this file.

		@param newTime  the time to apply to the file
		@returns true if it manages to change the file's time.
		@see getCreationTime, setLastModificationTime, setLastAccessTime
	*/
	bool setCreationTime (const Time& newTime) const;

	/** If possible, this will try to create a version string for the given file.

		The OS may be able to look at the file and give a version for it - e.g. with
		executables, bundles, dlls, etc. If no version is available, this will
		return an empty string.
	*/
	String getVersion() const;

	/** Creates an empty file if it doesn't already exist.

		If the file that this object refers to doesn't exist, this will create a file
		of zero size.

		If it already exists or is a directory, this method will do nothing.

		@returns    true if the file has been created (or if it already existed).
		@see createDirectory
	*/
	Result create() const;

	/** Creates a new directory for this filename.

		This will try to create the file as a directory, and fill also create
		any parent directories it needs in order to complete the operation.

		@returns    a result to indicate whether the directory was created successfully, or
					an error message if it failed.
		@see create
	*/
	Result createDirectory() const;

	/** Deletes a file.

		If this file is actually a directory, it may not be deleted correctly if it
		contains files. See deleteRecursively() as a better way of deleting directories.

		@returns    true if the file has been successfully deleted (or if it didn't exist to
					begin with).
		@see deleteRecursively
	*/
	bool deleteFile() const;

	/** Deletes a file or directory and all its subdirectories.

		If this file is a directory, this will try to delete it and all its subfolders. If
		it's just a file, it will just try to delete the file.

		@returns    true if the file and all its subfolders have been successfully deleted
					(or if it didn't exist to begin with).
		@see deleteFile
	*/
	bool deleteRecursively() const;

	/** Moves this file or folder to the trash.

		@returns true if the operation succeeded. It could fail if the trash is full, or
				 if the file is write-protected, so you should check the return value
				 and act appropriately.
	*/
	bool moveToTrash() const;

	/** Moves or renames a file.

		Tries to move a file to a different location.
		If the target file already exists, this will attempt to delete it first, and
		will fail if this can't be done.

		Note that the destination file isn't the directory to put it in, it's the actual
		filename that you want the new file to have.

		@returns    true if the operation succeeds
	*/
	bool moveFileTo (const File& targetLocation) const;

	/** Copies a file.

		Tries to copy a file to a different location.
		If the target file already exists, this will attempt to delete it first, and
		will fail if this can't be done.

		@returns    true if the operation succeeds
	*/
	bool copyFileTo (const File& targetLocation) const;

	/** Copies a directory.

		Tries to copy an entire directory, recursively.

		If this file isn't a directory or if any target files can't be created, this
		will return false.

		@param newDirectory    the directory that this one should be copied to. Note that this
							   is the name of the actual directory to create, not the directory
							   into which the new one should be placed, so there must be enough
							   write privileges to create it if it doesn't exist. Any files inside
							   it will be overwritten by similarly named ones that are copied.
	*/
	bool copyDirectoryTo (const File& newDirectory) const;

	/** Used in file searching, to specify whether to return files, directories, or both.
	*/
	enum TypesOfFileToFind
	{
		findDirectories             = 1,    /**< Use this flag to indicate that you want to find directories. */
		findFiles                   = 2,    /**< Use this flag to indicate that you want to find files. */
		findFilesAndDirectories     = 3,    /**< Use this flag to indicate that you want to find both files and directories. */
		ignoreHiddenFiles           = 4     /**< Add this flag to avoid returning any hidden files in the results. */
	};

	/** Searches inside a directory for files matching a wildcard pattern.

		Assuming that this file is a directory, this method will search it
		for either files or subdirectories whose names match a filename pattern.

		@param results                  an array to which File objects will be added for the
										files that the search comes up with
		@param whatToLookFor            a value from the TypesOfFileToFind enum, specifying whether to
										return files, directories, or both. If the ignoreHiddenFiles flag
										is also added to this value, hidden files won't be returned
		@param searchRecursively        if true, all subdirectories will be recursed into to do
										an exhaustive search
		@param wildCardPattern          the filename pattern to search for, e.g. "*.txt"
		@returns                        the number of results that have been found

		@see getNumberOfChildFiles, DirectoryIterator
	*/
	int findChildFiles (Array<File>& results,
						int whatToLookFor,
						bool searchRecursively,
						const String& wildCardPattern = "*") const;

	/** Searches inside a directory and counts how many files match a wildcard pattern.

		Assuming that this file is a directory, this method will search it
		for either files or subdirectories whose names match a filename pattern,
		and will return the number of matches found.

		This isn't a recursive call, and will only search this directory, not
		its children.

		@param whatToLookFor    a value from the TypesOfFileToFind enum, specifying whether to
								count files, directories, or both. If the ignoreHiddenFiles flag
								is also added to this value, hidden files won't be counted
		@param wildCardPattern  the filename pattern to search for, e.g. "*.txt"
		@returns                the number of matches found
		@see findChildFiles, DirectoryIterator
	*/
	int getNumberOfChildFiles (int whatToLookFor,
							   const String& wildCardPattern = "*") const;

	/** Returns true if this file is a directory that contains one or more subdirectories.
		@see isDirectory, findChildFiles
	*/
	bool containsSubDirectories() const;

	/** Creates a stream to read from this file.

		@returns    a stream that will read from this file (initially positioned at the
					start of the file), or 0 if the file can't be opened for some reason
		@see createOutputStream, loadFileAsData
	*/
	FileInputStream* createInputStream() const;

	/** Creates a stream to write to this file.

		If the file exists, the stream that is returned will be positioned ready for
		writing at the end of the file, so you might want to use deleteFile() first
		to write to an empty file.

		@returns    a stream that will write to this file (initially positioned at the
					end of the file), or 0 if the file can't be opened for some reason
		@see createInputStream, appendData, appendText
	*/
	FileOutputStream* createOutputStream (int bufferSize = 0x8000) const;

	/** Loads a file's contents into memory as a block of binary data.

		Of course, trying to load a very large file into memory will blow up, so
		it's better to check first.

		@param result   the data block to which the file's contents should be appended - note
						that if the memory block might already contain some data, you
						might want to clear it first
		@returns        true if the file could all be read into memory
	*/
	bool loadFileAsData (MemoryBlock& result) const;

	/** Reads a file into memory as a string.

		Attempts to load the entire file as a zero-terminated string.

		This makes use of InputStream::readEntireStreamAsString, which should
		automatically cope with unicode/acsii file formats.
	*/
	String loadFileAsString() const;

	/** Reads the contents of this file as text and splits it into lines, which are
		appended to the given StringArray.
	*/
	void readLines (StringArray& destLines) const;

	/** Appends a block of binary data to the end of the file.

		This will try to write the given buffer to the end of the file.

		@returns false if it can't write to the file for some reason
	*/
	bool appendData (const void* dataToAppend,
					 int numberOfBytes) const;

	/** Replaces this file's contents with a given block of data.

		This will delete the file and replace it with the given data.

		A nice feature of this method is that it's safe - instead of deleting
		the file first and then re-writing it, it creates a new temporary file,
		writes the data to that, and then moves the new file to replace the existing
		file. This means that if the power gets pulled out or something crashes,
		you're a lot less likely to end up with a corrupted or unfinished file..

		Returns true if the operation succeeds, or false if it fails.

		@see appendText
	*/
	bool replaceWithData (const void* dataToWrite,
						  int numberOfBytes) const;

	/** Appends a string to the end of the file.

		This will try to append a text string to the file, as either 16-bit unicode
		or 8-bit characters in the default system encoding.

		It can also write the 'ff fe' unicode header bytes before the text to indicate
		the endianness of the file.

		Any single \\n characters in the string are replaced with \\r\\n before it is written.

		@see replaceWithText
	*/
	bool appendText (const String& textToAppend,
					 bool asUnicode = false,
					 bool writeUnicodeHeaderBytes = false) const;

	/** Replaces this file's contents with a given text string.

		This will delete the file and replace it with the given text.

		A nice feature of this method is that it's safe - instead of deleting
		the file first and then re-writing it, it creates a new temporary file,
		writes the text to that, and then moves the new file to replace the existing
		file. This means that if the power gets pulled out or something crashes,
		you're a lot less likely to end up with an empty file..

		For an explanation of the parameters here, see the appendText() method.

		Returns true if the operation succeeds, or false if it fails.

		@see appendText
	*/
	bool replaceWithText (const String& textToWrite,
						  bool asUnicode = false,
						  bool writeUnicodeHeaderBytes = false) const;

	/** Attempts to scan the contents of this file and compare it to another file, returning
		true if this is possible and they match byte-for-byte.
	*/
	bool hasIdenticalContentTo (const File& other) const;

	/** Creates a set of files to represent each file root.

		e.g. on Windows this will create files for "c:\", "d:\" etc according
		to which ones are available. On the Mac/Linux, this will probably
		just add a single entry for "/".
	*/
	static void findFileSystemRoots (Array<File>& results);

	/** Finds the name of the drive on which this file lives.

		@returns the volume label of the drive, or an empty string if this isn't possible
	*/
	String getVolumeLabel() const;

	/** Returns the serial number of the volume on which this file lives.

		@returns the serial number, or zero if there's a problem doing this
	*/
	int getVolumeSerialNumber() const;

	/** Returns the number of bytes free on the drive that this file lives on.

		@returns the number of bytes free, or 0 if there's a problem finding this out
		@see getVolumeTotalSize
	*/
	int64 getBytesFreeOnVolume() const;

	/** Returns the total size of the drive that contains this file.

		@returns the total number of bytes that the volume can hold
		@see getBytesFreeOnVolume
	*/
	int64 getVolumeTotalSize() const;

	/** Returns true if this file is on a CD or DVD drive. */
	bool isOnCDRomDrive() const;

	/** Returns true if this file is on a hard disk.

		This will fail if it's a network drive, but will still be true for
		removable hard-disks.
	*/
	bool isOnHardDisk() const;

	/** Returns true if this file is on a removable disk drive.

		This might be a usb-drive, a CD-rom, or maybe a network drive.
	*/
	bool isOnRemovableDrive() const;

	/** Launches the file as a process.

		- if the file is executable, this will run it.

		- if it's a document of some kind, it will launch the document with its
		default viewer application.

		- if it's a folder, it will be opened in Explorer, Finder, or equivalent.

		@see revealToUser
	*/
	bool startAsProcess (const String& parameters = String::empty) const;

	/** Opens Finder, Explorer, or whatever the OS uses, to show the user this file's location.
		@see startAsProcess
	*/
	void revealToUser() const;

	/** A set of types of location that can be passed to the getSpecialLocation() method.
	*/
	enum SpecialLocationType
	{
		/** The user's home folder. This is the same as using File ("~"). */
		userHomeDirectory,

		/** The user's default documents folder. On Windows, this might be the user's
			"My Documents" folder. On the Mac it'll be their "Documents" folder. Linux
			doesn't tend to have one of these, so it might just return their home folder.
		*/
		userDocumentsDirectory,

		/** The folder that contains the user's desktop objects. */
		userDesktopDirectory,

		/** The folder in which applications store their persistent user-specific settings.
			On Windows, this might be "\Documents and Settings\username\Application Data".
			On the Mac, it might be "~/Library". If you're going to store your settings in here,
			always create your own sub-folder to put them in, to avoid making a mess.
		*/
		userApplicationDataDirectory,

		/** An equivalent of the userApplicationDataDirectory folder that is shared by all users
			of the computer, rather than just the current user.

			On the Mac it'll be "/Library", on Windows, it could be something like
			"\Documents and Settings\All Users\Application Data".

			Depending on the setup, this folder may be read-only.
		*/
		commonApplicationDataDirectory,

		/** The folder that should be used for temporary files.

			Always delete them when you're finished, to keep the user's computer tidy!
		*/
		tempDirectory,

		/** Returns this application's executable file.

			If running as a plug-in or DLL, this will (where possible) be the DLL rather than the
			host app.

			On the mac this will return the unix binary, not the package folder - see
			currentApplicationFile for that.

			See also invokedExecutableFile, which is similar, but if the exe was launched from a
			file link, invokedExecutableFile will return the name of the link.
		*/
		currentExecutableFile,

		/** Returns this application's location.

			If running as a plug-in or DLL, this will (where possible) be the DLL rather than the
			host app.

			On the mac this will return the package folder (if it's in one), not the unix binary
			that's inside it - compare with currentExecutableFile.
		*/
		currentApplicationFile,

		/** Returns the file that was invoked to launch this executable.
			This may differ from currentExecutableFile if the app was started from e.g. a link - this
			will return the name of the link that was used, whereas currentExecutableFile will return
			the actual location of the target executable.
		*/
		invokedExecutableFile,

		/** In a plugin, this will return the path of the host executable. */
		hostApplicationPath,

		/** The directory in which applications normally get installed.

			So on windows, this would be something like "c:\program files", on the
			Mac "/Applications", or "/usr" on linux.
		*/
		globalApplicationsDirectory,

		/** The most likely place where a user might store their music files.
		*/
		userMusicDirectory,

		/** The most likely place where a user might store their movie files.
		*/
		userMoviesDirectory,
	};

	/** Finds the location of a special type of file or directory, such as a home folder or
		documents folder.

		@see SpecialLocationType
	*/
	static File JUCE_CALLTYPE getSpecialLocation (const SpecialLocationType type);

	/** Returns a temporary file in the system's temp directory.

		This will try to return the name of a non-existent temp file.

		To get the temp folder, you can use getSpecialLocation (File::tempDirectory).
	*/
	static File createTempFile (const String& fileNameEnding);

	/** Returns the current working directory.

		@see setAsCurrentWorkingDirectory
	*/
	static File getCurrentWorkingDirectory();

	/** Sets the current working directory to be this file.

		For this to work the file must point to a valid directory.

		@returns true if the current directory has been changed.
		@see getCurrentWorkingDirectory
	*/
	bool setAsCurrentWorkingDirectory() const;

	/** The system-specific file separator character.

		On Windows, this will be '\', on Mac/Linux, it'll be '/'
	*/
	static const juce_wchar separator;

	/** The system-specific file separator character, as a string.

		On Windows, this will be '\', on Mac/Linux, it'll be '/'
	*/
	static const String separatorString;

	/** Removes illegal characters from a filename.

		This will return a copy of the given string after removing characters
		that are not allowed in a legal filename, and possibly shortening the
		string if it's too long.

		Because this will remove slashes, don't use it on an absolute pathname.

		@see createLegalPathName
	*/
	static String createLegalFileName (const String& fileNameToFix);

	/** Removes illegal characters from a pathname.

		Similar to createLegalFileName(), but this won't remove slashes, so can
		be used on a complete pathname.

		@see createLegalFileName
	*/
	static String createLegalPathName (const String& pathNameToFix);

	/** Indicates whether filenames are case-sensitive on the current operating system.
	*/
	static bool areFileNamesCaseSensitive();

	/** Returns true if the string seems to be a fully-specified absolute path.
	*/
	static bool isAbsolutePath (const String& path);

	/** Creates a file that simply contains this string, without doing the sanity-checking
		that the normal constructors do.

		Best to avoid this unless you really know what you're doing.
	*/
	static File createFileWithoutCheckingPath (const String& path);

	/** Adds a separator character to the end of a path if it doesn't already have one. */
	static String addTrailingSeparator (const String& path);

   #if JUCE_MAC || JUCE_IOS || DOXYGEN

	/** OSX ONLY - Finds the OSType of a file from the its resources. */
	OSType getMacOSType() const;

	/** OSX ONLY - Returns true if this file is actually a bundle. */
	bool isBundle() const;
   #endif

   #if JUCE_MAC || DOXYGEN
	/** OSX ONLY - Adds this file to the OSX dock */
	void addToDock() const;
   #endif

private:

	String fullPath;

	static String parseAbsolutePath (const String&);
	String getPathUpToLastSlash() const;

	Result createDirectoryInternal (const String&) const;
	bool copyInternal (const File&) const;
	bool moveInternal (const File&) const;
	bool setFileTimesInternal (int64 modificationTime, int64 accessTime, int64 creationTime) const;
	void getFileTimesInternal (int64& modificationTime, int64& accessTime, int64& creationTime) const;
	bool setFileReadOnlyInternal (bool shouldBeReadOnly) const;

	JUCE_LEAK_DETECTOR (File);
};

#endif   // __JUCE_FILE_JUCEHEADER__

/*** End of inlined file: juce_File.h ***/

/** A handy macro to make it easy to iterate all the child elements in an XmlElement.

	The parentXmlElement should be a reference to the parent XML, and the childElementVariableName
	will be the name of a pointer to each child element.

	E.g. @code
	XmlElement* myParentXml = createSomeKindOfXmlDocument();

	forEachXmlChildElement (*myParentXml, child)
	{
		if (child->hasTagName ("FOO"))
			doSomethingWithXmlElement (child);
	}

	@endcode

	@see forEachXmlChildElementWithTagName
*/
#define forEachXmlChildElement(parentXmlElement, childElementVariableName) \
\
	for (juce::XmlElement* childElementVariableName = (parentXmlElement).getFirstChildElement(); \
		 childElementVariableName != nullptr; \
		 childElementVariableName = childElementVariableName->getNextElement())

/** A macro that makes it easy to iterate all the child elements of an XmlElement
	which have a specified tag.

	This does the same job as the forEachXmlChildElement macro, but only for those
	elements that have a particular tag name.

	The parentXmlElement should be a reference to the parent XML, and the childElementVariableName
	will be the name of a pointer to each child element. The requiredTagName is the
	tag name to match.

	E.g. @code
	XmlElement* myParentXml = createSomeKindOfXmlDocument();

	forEachXmlChildElementWithTagName (*myParentXml, child, "MYTAG")
	{
		// the child object is now guaranteed to be a <MYTAG> element..
		doSomethingWithMYTAGElement (child);
	}

	@endcode

	@see forEachXmlChildElement
*/
#define forEachXmlChildElementWithTagName(parentXmlElement, childElementVariableName, requiredTagName) \
\
	for (juce::XmlElement* childElementVariableName = (parentXmlElement).getChildByName (requiredTagName); \
		 childElementVariableName != nullptr; \
		 childElementVariableName = childElementVariableName->getNextElementWithTagName (requiredTagName))

/** Used to build a tree of elements representing an XML document.

	An XML document can be parsed into a tree of XmlElements, each of which
	represents an XML tag structure, and which may itself contain other
	nested elements.

	An XmlElement can also be converted back into a text document, and has
	lots of useful methods for manipulating its attributes and sub-elements,
	so XmlElements can actually be used as a handy general-purpose data
	structure.

	Here's an example of parsing some elements: @code
	// check we're looking at the right kind of document..
	if (myElement->hasTagName ("ANIMALS"))
	{
		// now we'll iterate its sub-elements looking for 'giraffe' elements..
		forEachXmlChildElement (*myElement, e)
		{
			if (e->hasTagName ("GIRAFFE"))
			{
				// found a giraffe, so use some of its attributes..

				String giraffeName  = e->getStringAttribute ("name");
				int giraffeAge      = e->getIntAttribute ("age");
				bool isFriendly     = e->getBoolAttribute ("friendly");
			}
		}
	}
	@endcode

	And here's an example of how to create an XML document from scratch: @code
	// create an outer node called "ANIMALS"
	XmlElement animalsList ("ANIMALS");

	for (int i = 0; i < numAnimals; ++i)
	{
		// create an inner element..
		XmlElement* giraffe = new XmlElement ("GIRAFFE");

		giraffe->setAttribute ("name", "nigel");
		giraffe->setAttribute ("age", 10);
		giraffe->setAttribute ("friendly", true);

		// ..and add our new element to the parent node
		animalsList.addChildElement (giraffe);
	}

	// now we can turn the whole thing into a text document..
	String myXmlDoc = animalsList.createDocument (String::empty);
	@endcode

	@see XmlDocument
*/
class JUCE_API  XmlElement
{
public:

	/** Creates an XmlElement with this tag name. */
	explicit XmlElement (const String& tagName) noexcept;

	/** Creates a (deep) copy of another element. */
	XmlElement (const XmlElement& other);

	/** Creates a (deep) copy of another element. */
	XmlElement& operator= (const XmlElement& other);

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	XmlElement (XmlElement&& other) noexcept;
	XmlElement& operator= (XmlElement&& other) noexcept;
   #endif

	/** Deleting an XmlElement will also delete all its child elements. */
	~XmlElement() noexcept;

	/** Compares two XmlElements to see if they contain the same text and attiributes.

		The elements are only considered equivalent if they contain the same attiributes
		with the same values, and have the same sub-nodes.

		@param other                    the other element to compare to
		@param ignoreOrderOfAttributes  if true, this means that two elements with the
										same attributes in a different order will be
										considered the same; if false, the attributes must
										be in the same order as well
	*/
	bool isEquivalentTo (const XmlElement* other,
						 bool ignoreOrderOfAttributes) const noexcept;

	/** Returns an XML text document that represents this element.

		The string returned can be parsed to recreate the same XmlElement that
		was used to create it.

		@param dtdToUse         the DTD to add to the document
		@param allOnOneLine     if true, this means that the document will not contain any
								linefeeds, so it'll be smaller but not very easy to read.
		@param includeXmlHeader whether to add the "<?xml version..etc" line at the start of the
								document
		@param encodingType     the character encoding format string to put into the xml
								header
		@param lineWrapLength   the line length that will be used before items get placed on
								a new line. This isn't an absolute maximum length, it just
								determines how lists of attributes get broken up
		@see writeToStream, writeToFile
	*/
	String createDocument (const String& dtdToUse,
						   bool allOnOneLine = false,
						   bool includeXmlHeader = true,
						   const String& encodingType = "UTF-8",
						   int lineWrapLength = 60) const;

	/** Writes the document to a stream as UTF-8.

		@param output           the stream to write to
		@param dtdToUse         the DTD to add to the document
		@param allOnOneLine     if true, this means that the document will not contain any
								linefeeds, so it'll be smaller but not very easy to read.
		@param includeXmlHeader whether to add the "<?xml version..etc" line at the start of the
								document
		@param encodingType     the character encoding format string to put into the xml
								header
		@param lineWrapLength   the line length that will be used before items get placed on
								a new line. This isn't an absolute maximum length, it just
								determines how lists of attributes get broken up
		@see writeToFile, createDocument
	*/
	void writeToStream (OutputStream& output,
						const String& dtdToUse,
						bool allOnOneLine = false,
						bool includeXmlHeader = true,
						const String& encodingType = "UTF-8",
						int lineWrapLength = 60) const;

	/** Writes the element to a file as an XML document.

		To improve safety in case something goes wrong while writing the file, this
		will actually write the document to a new temporary file in the same
		directory as the destination file, and if this succeeds, it will rename this
		new file as the destination file (overwriting any existing file that was there).

		@param destinationFile  the file to write to. If this already exists, it will be
								overwritten.
		@param dtdToUse         the DTD to add to the document
		@param encodingType     the character encoding format string to put into the xml
								header
		@param lineWrapLength   the line length that will be used before items get placed on
								a new line. This isn't an absolute maximum length, it just
								determines how lists of attributes get broken up
		@returns    true if the file is written successfully; false if something goes wrong
					in the process
		@see createDocument
	*/
	bool writeToFile (const File& destinationFile,
					  const String& dtdToUse,
					  const String& encodingType = "UTF-8",
					  int lineWrapLength = 60) const;

	/** Returns this element's tag type name.

		E.g. for an element such as \<MOOSE legs="4" antlers="2">, this would return
		"MOOSE".

		@see hasTagName
	*/
	inline const String& getTagName() const noexcept            { return tagName; }

	/** Tests whether this element has a particular tag name.

		@param possibleTagName  the tag name you're comparing it with

		@see getTagName
	*/
	bool hasTagName (const String& possibleTagName) const noexcept;

	/** Returns the number of XML attributes this element contains.

		E.g. for an element such as \<MOOSE legs="4" antlers="2">, this would
		return 2.
	*/
	int getNumAttributes() const noexcept;

	/** Returns the name of one of the elements attributes.

		E.g. for an element such as \<MOOSE legs="4" antlers="2">, then
		getAttributeName(1) would return "antlers".

		@see getAttributeValue, getStringAttribute
	*/
	const String& getAttributeName (int attributeIndex) const noexcept;

	/** Returns the value of one of the elements attributes.

		E.g. for an element such as \<MOOSE legs="4" antlers="2">, then
		getAttributeName(1) would return "2".

		@see getAttributeName, getStringAttribute
	*/
	const String& getAttributeValue (int attributeIndex) const noexcept;

	// Attribute-handling methods..

	/** Checks whether the element contains an attribute with a certain name. */
	bool hasAttribute (const String& attributeName) const noexcept;

	/** Returns the value of a named attribute.

		@param attributeName        the name of the attribute to look up
	*/
	const String& getStringAttribute (const String& attributeName) const noexcept;

	/** Returns the value of a named attribute.

		@param attributeName        the name of the attribute to look up
		@param defaultReturnValue   a value to return if the element doesn't have an attribute
									with this name
	*/
	String getStringAttribute (const String& attributeName,
							   const String& defaultReturnValue) const;

	/** Compares the value of a named attribute with a value passed-in.

		@param attributeName            the name of the attribute to look up
		@param stringToCompareAgainst   the value to compare it with
		@param ignoreCase               whether the comparison should be case-insensitive
		@returns    true if the value of the attribute is the same as the string passed-in;
					false if it's different (or if no such attribute exists)
	*/
	bool compareAttribute (const String& attributeName,
						   const String& stringToCompareAgainst,
						   bool ignoreCase = false) const noexcept;

	/** Returns the value of a named attribute as an integer.

		This will try to find the attribute and convert it to an integer (using
		the String::getIntValue() method).

		@param attributeName        the name of the attribute to look up
		@param defaultReturnValue   a value to return if the element doesn't have an attribute
									with this name
		@see setAttribute
	*/
	int getIntAttribute (const String& attributeName,
						 int defaultReturnValue = 0) const;

	/** Returns the value of a named attribute as floating-point.

		This will try to find the attribute and convert it to an integer (using
		the String::getDoubleValue() method).

		@param attributeName        the name of the attribute to look up
		@param defaultReturnValue   a value to return if the element doesn't have an attribute
									with this name
		@see setAttribute
	*/
	double getDoubleAttribute (const String& attributeName,
							   double defaultReturnValue = 0.0) const;

	/** Returns the value of a named attribute as a boolean.

		This will try to find the attribute and interpret it as a boolean. To do this,
		it'll return true if the value is "1", "true", "y", etc, or false for other
		values.

		@param attributeName        the name of the attribute to look up
		@param defaultReturnValue   a value to return if the element doesn't have an attribute
									with this name
	*/
	bool getBoolAttribute (const String& attributeName,
						   bool defaultReturnValue = false) const;

	/** Adds a named attribute to the element.

		If the element already contains an attribute with this name, it's value will
		be updated to the new value. If there's no such attribute yet, a new one will
		be added.

		Note that there are other setAttribute() methods that take integers,
		doubles, etc. to make it easy to store numbers.

		@param attributeName        the name of the attribute to set
		@param newValue             the value to set it to
		@see removeAttribute
	*/
	void setAttribute (const String& attributeName,
					   const String& newValue);

	/** Adds a named attribute to the element, setting it to an integer value.

		If the element already contains an attribute with this name, it's value will
		be updated to the new value. If there's no such attribute yet, a new one will
		be added.

		Note that there are other setAttribute() methods that take integers,
		doubles, etc. to make it easy to store numbers.

		@param attributeName        the name of the attribute to set
		@param newValue             the value to set it to
	*/
	void setAttribute (const String& attributeName,
					   int newValue);

	/** Adds a named attribute to the element, setting it to a floating-point value.

		If the element already contains an attribute with this name, it's value will
		be updated to the new value. If there's no such attribute yet, a new one will
		be added.

		Note that there are other setAttribute() methods that take integers,
		doubles, etc. to make it easy to store numbers.

		@param attributeName        the name of the attribute to set
		@param newValue             the value to set it to
	*/
	void setAttribute (const String& attributeName,
					   double newValue);

	/** Removes a named attribute from the element.

		@param attributeName    the name of the attribute to remove
		@see removeAllAttributes
	*/
	void removeAttribute (const String& attributeName) noexcept;

	/** Removes all attributes from this element.
	*/
	void removeAllAttributes() noexcept;

	// Child element methods..

	/** Returns the first of this element's sub-elements.

		see getNextElement() for an example of how to iterate the sub-elements.

		@see forEachXmlChildElement
	*/
	XmlElement* getFirstChildElement() const noexcept       { return firstChildElement; }

	/** Returns the next of this element's siblings.

		This can be used for iterating an element's sub-elements, e.g.
		@code
		XmlElement* child = myXmlDocument->getFirstChildElement();

		while (child != nullptr)
		{
			...do stuff with this child..

			child = child->getNextElement();
		}
		@endcode

		Note that when iterating the child elements, some of them might be
		text elements as well as XML tags - use isTextElement() to work this
		out.

		Also, it's much easier and neater to use this method indirectly via the
		forEachXmlChildElement macro.

		@returns    the sibling element that follows this one, or zero if this is the last
					element in its parent

		@see getNextElement, isTextElement, forEachXmlChildElement
	*/
	inline XmlElement* getNextElement() const noexcept          { return nextListItem; }

	/** Returns the next of this element's siblings which has the specified tag
		name.

		This is like getNextElement(), but will scan through the list until it
		finds an element with the given tag name.

		@see getNextElement, forEachXmlChildElementWithTagName
	*/
	XmlElement* getNextElementWithTagName (const String& requiredTagName) const;

	/** Returns the number of sub-elements in this element.

		@see getChildElement
	*/
	int getNumChildElements() const noexcept;

	/** Returns the sub-element at a certain index.

		It's not very efficient to iterate the sub-elements by index - see
		getNextElement() for an example of how best to iterate.

		@returns the n'th child of this element, or 0 if the index is out-of-range
		@see getNextElement, isTextElement, getChildByName
	*/
	XmlElement* getChildElement (int index) const noexcept;

	/** Returns the first sub-element with a given tag-name.

		@param tagNameToLookFor     the tag name of the element you want to find
		@returns the first element with this tag name, or 0 if none is found
		@see getNextElement, isTextElement, getChildElement
	*/
	XmlElement* getChildByName (const String& tagNameToLookFor) const noexcept;

	/** Appends an element to this element's list of children.

		Child elements are deleted automatically when their parent is deleted, so
		make sure the object that you pass in will not be deleted by anything else,
		and make sure it's not already the child of another element.

		@see getFirstChildElement, getNextElement, getNumChildElements,
			 getChildElement, removeChildElement
	*/
	void addChildElement (XmlElement* newChildElement) noexcept;

	/** Inserts an element into this element's list of children.

		Child elements are deleted automatically when their parent is deleted, so
		make sure the object that you pass in will not be deleted by anything else,
		and make sure it's not already the child of another element.

		@param newChildNode     the element to add
		@param indexToInsertAt  the index at which to insert the new element - if this is
								below zero, it will be added to the end of the list
		@see addChildElement, insertChildElement
	*/
	void insertChildElement (XmlElement* newChildNode,
							 int indexToInsertAt) noexcept;

	/** Creates a new element with the given name and returns it, after adding it
		as a child element.

		This is a handy method that means that instead of writing this:
		@code
		XmlElement* newElement = new XmlElement ("foobar");
		myParentElement->addChildElement (newElement);
		@endcode

		..you could just write this:
		@code
		XmlElement* newElement = myParentElement->createNewChildElement ("foobar");
		@endcode
	*/
	XmlElement* createNewChildElement (const String& tagName);

	/** Replaces one of this element's children with another node.

		If the current element passed-in isn't actually a child of this element,
		this will return false and the new one won't be added. Otherwise, the
		existing element will be deleted, replaced with the new one, and it
		will return true.
	*/
	bool replaceChildElement (XmlElement* currentChildElement,
							  XmlElement* newChildNode) noexcept;

	/** Removes a child element.

		@param childToRemove            the child to look for and remove
		@param shouldDeleteTheChild     if true, the child will be deleted, if false it'll
										just remove it
	*/
	void removeChildElement (XmlElement* childToRemove,
							 bool shouldDeleteTheChild) noexcept;

	/** Deletes all the child elements in the element.

		@see removeChildElement, deleteAllChildElementsWithTagName
	*/
	void deleteAllChildElements() noexcept;

	/** Deletes all the child elements with a given tag name.

		@see removeChildElement
	*/
	void deleteAllChildElementsWithTagName (const String& tagName) noexcept;

	/** Returns true if the given element is a child of this one. */
	bool containsChildElement (const XmlElement* possibleChild) const noexcept;

	/** Recursively searches all sub-elements to find one that contains the specified
		child element.
	*/
	XmlElement* findParentElementOf (const XmlElement* elementToLookFor) noexcept;

	/** Sorts the child elements using a comparator.

		This will use a comparator object to sort the elements into order. The object
		passed must have a method of the form:
		@code
		int compareElements (const XmlElement* first, const XmlElement* second);
		@endcode

		..and this method must return:
		  - a value of < 0 if the first comes before the second
		  - a value of 0 if the two objects are equivalent
		  - a value of > 0 if the second comes before the first

		To improve performance, the compareElements() method can be declared as static or const.

		@param comparator   the comparator to use for comparing elements.
		@param retainOrderOfEquivalentItems     if this is true, then items which the comparator
							says are equivalent will be kept in the order in which they
							currently appear in the array. This is slower to perform, but
							may be important in some cases. If it's false, a faster algorithm
							is used, but equivalent elements may be rearranged.
	*/
	template <class ElementComparator>
	void sortChildElements (ElementComparator& comparator,
							bool retainOrderOfEquivalentItems = false)
	{
		const int num = getNumChildElements();

		if (num > 1)
		{
			HeapBlock <XmlElement*> elems (num);
			getChildElementsAsArray (elems);
			sortArray (comparator, (XmlElement**) elems, 0, num - 1, retainOrderOfEquivalentItems);
			reorderChildElements (elems, num);
		}
	}

	/** Returns true if this element is a section of text.

		Elements can either be an XML tag element or a secton of text, so this
		is used to find out what kind of element this one is.

		@see getAllText, addTextElement, deleteAllTextElements
	*/
	bool isTextElement() const noexcept;

	/** Returns the text for a text element.

		Note that if you have an element like this:

		@code<xyz>hello</xyz>@endcode

		then calling getText on the "xyz" element won't return "hello", because that is
		actually stored in a special text sub-element inside the xyz element. To get the
		"hello" string, you could either call getText on the (unnamed) sub-element, or
		use getAllSubText() to do this automatically.

		Note that leading and trailing whitespace will be included in the string - to remove
		if, just call String::trim() on the result.

		@see isTextElement, getAllSubText, getChildElementAllSubText
	*/
	const String& getText() const noexcept;

	/** Sets the text in a text element.

		Note that this is only a valid call if this element is a text element. If it's
		not, then no action will be performed. If you're trying to add text inside a normal
		element, you probably want to use addTextElement() instead.
	*/
	void setText (const String& newText);

	/** Returns all the text from this element's child nodes.

		This iterates all the child elements and when it finds text elements,
		it concatenates their text into a big string which it returns.

		E.g. @code<xyz>hello <x>there</x> world</xyz>@endcode
		if you called getAllSubText on the "xyz" element, it'd return "hello there world".

		Note that leading and trailing whitespace will be included in the string - to remove
		if, just call String::trim() on the result.

		@see isTextElement, getChildElementAllSubText, getText, addTextElement
	*/
	String getAllSubText() const;

	/** Returns all the sub-text of a named child element.

		If there is a child element with the given tag name, this will return
		all of its sub-text (by calling getAllSubText() on it). If there is
		no such child element, this will return the default string passed-in.

		@see getAllSubText
	*/
	String getChildElementAllSubText (const String& childTagName,
									  const String& defaultReturnValue) const;

	/** Appends a section of text to this element.

		@see isTextElement, getText, getAllSubText
	*/
	void addTextElement (const String& text);

	/** Removes all the text elements from this element.

		@see isTextElement, getText, getAllSubText, addTextElement
	*/
	void deleteAllTextElements() noexcept;

	/** Creates a text element that can be added to a parent element.
	*/
	static XmlElement* createTextElement (const String& text);

private:
	struct XmlAttributeNode
	{
		XmlAttributeNode (const XmlAttributeNode&) noexcept;
		XmlAttributeNode (const String& name, const String& value) noexcept;

		LinkedListPointer<XmlAttributeNode> nextListItem;
		String name, value;

		bool hasName (const String&) const noexcept;

	private:
		XmlAttributeNode& operator= (const XmlAttributeNode&);
	};

	friend class XmlDocument;
	friend class LinkedListPointer <XmlAttributeNode>;
	friend class LinkedListPointer <XmlElement>;
	friend class LinkedListPointer <XmlElement>::Appender;

	LinkedListPointer <XmlElement> nextListItem;
	LinkedListPointer <XmlElement> firstChildElement;
	LinkedListPointer <XmlAttributeNode> attributes;
	String tagName;

	XmlElement (int) noexcept;
	void copyChildrenAndAttributesFrom (const XmlElement&);
	void writeElementAsText (OutputStream&, int indentationLevel, int lineWrapLength) const;
	void getChildElementsAsArray (XmlElement**) const noexcept;
	void reorderChildElements (XmlElement**, int) noexcept;

	JUCE_LEAK_DETECTOR (XmlElement);
};

#endif   // __JUCE_XMLELEMENT_JUCEHEADER__

/*** End of inlined file: juce_XmlElement.h ***/

/**
	A set of named property values, which can be strings, integers, floating point, etc.

	Effectively, this just wraps a StringPairArray in an interface that makes it easier
	to load and save types other than strings.

	See the PropertiesFile class for a subclass of this, which automatically broadcasts change
	messages and saves/loads the list from a file.
*/
class JUCE_API  PropertySet
{
public:

	/** Creates an empty PropertySet.

		@param ignoreCaseOfKeyNames         if true, the names of properties are compared in a
											case-insensitive way
	*/
	PropertySet (bool ignoreCaseOfKeyNames = false);

	/** Creates a copy of another PropertySet.
	*/
	PropertySet (const PropertySet& other);

	/** Copies another PropertySet over this one.
	*/
	PropertySet& operator= (const PropertySet& other);

	/** Destructor. */
	virtual ~PropertySet();

	/** Returns one of the properties as a string.

		If the value isn't found in this set, then this will look for it in a fallback
		property set (if you've specified one with the setFallbackPropertySet() method),
		and if it can't find one there, it'll return the default value passed-in.

		@param keyName              the name of the property to retrieve
		@param defaultReturnValue   a value to return if the named property doesn't actually exist
	*/
	String getValue (const String& keyName,
					 const String& defaultReturnValue = String::empty) const noexcept;

	/** Returns one of the properties as an integer.

		If the value isn't found in this set, then this will look for it in a fallback
		property set (if you've specified one with the setFallbackPropertySet() method),
		and if it can't find one there, it'll return the default value passed-in.

		@param keyName              the name of the property to retrieve
		@param defaultReturnValue   a value to return if the named property doesn't actually exist
	*/
	int getIntValue (const String& keyName,
					 const int defaultReturnValue = 0) const noexcept;

	/** Returns one of the properties as an double.

		If the value isn't found in this set, then this will look for it in a fallback
		property set (if you've specified one with the setFallbackPropertySet() method),
		and if it can't find one there, it'll return the default value passed-in.

		@param keyName              the name of the property to retrieve
		@param defaultReturnValue   a value to return if the named property doesn't actually exist
	*/
	double getDoubleValue (const String& keyName,
						   const double defaultReturnValue = 0.0) const noexcept;

	/** Returns one of the properties as an boolean.

		The result will be true if the string found for this key name can be parsed as a non-zero
		integer.

		If the value isn't found in this set, then this will look for it in a fallback
		property set (if you've specified one with the setFallbackPropertySet() method),
		and if it can't find one there, it'll return the default value passed-in.

		@param keyName              the name of the property to retrieve
		@param defaultReturnValue   a value to return if the named property doesn't actually exist
	*/
	bool getBoolValue (const String& keyName,
					   const bool defaultReturnValue = false) const noexcept;

	/** Returns one of the properties as an XML element.

		The result will a new XMLElement object that the caller must delete. If may return 0 if the
		key isn't found, or if the entry contains an string that isn't valid XML.

		If the value isn't found in this set, then this will look for it in a fallback
		property set (if you've specified one with the setFallbackPropertySet() method),
		and if it can't find one there, it'll return the default value passed-in.

		@param keyName              the name of the property to retrieve
	*/
	XmlElement* getXmlValue (const String& keyName) const;

	/** Sets a named property.

		@param keyName      the name of the property to set. (This mustn't be an empty string)
		@param value        the new value to set it to
	*/
	void setValue (const String& keyName, const var& value);

	/** Sets a named property to an XML element.

		@param keyName      the name of the property to set. (This mustn't be an empty string)
		@param xml          the new element to set it to. If this is zero, the value will be set to
							an empty string
		@see getXmlValue
	*/
	void setValue (const String& keyName, const XmlElement* xml);

	/** This copies all the values from a source PropertySet to this one.
		This won't remove any existing settings, it just adds any that it finds in the source set.
	*/
	void addAllPropertiesFrom (const PropertySet& source);

	/** Deletes a property.

		@param keyName      the name of the property to delete. (This mustn't be an empty string)
	*/
	void removeValue (const String& keyName);

	/** Returns true if the properies include the given key. */
	bool containsKey (const String& keyName) const noexcept;

	/** Removes all values. */
	void clear();

	/** Returns the keys/value pair array containing all the properties. */
	StringPairArray& getAllProperties() noexcept                        { return properties; }

	/** Returns the lock used when reading or writing to this set */
	const CriticalSection& getLock() const noexcept                     { return lock; }

	/** Returns an XML element which encapsulates all the items in this property set.

		The string parameter is the tag name that should be used for the node.

		@see restoreFromXml
	*/
	XmlElement* createXml (const String& nodeName) const;

	/** Reloads a set of properties that were previously stored as XML.

		The node passed in must have been created by the createXml() method.

		@see createXml
	*/
	void restoreFromXml (const XmlElement& xml);

	/** Sets up a second PopertySet that will be used to look up any values that aren't
		set in this one.

		If you set this up to be a pointer to a second property set, then whenever one
		of the getValue() methods fails to find an entry in this set, it will look up that
		value in the fallback set, and if it finds it, it will return that.

		Make sure that you don't delete the fallback set while it's still being used by
		another set! To remove the fallback set, just call this method with a null pointer.

		@see getFallbackPropertySet
	*/
	void setFallbackPropertySet (PropertySet* fallbackProperties) noexcept;

	/** Returns the fallback property set.
		@see setFallbackPropertySet
	*/
	PropertySet* getFallbackPropertySet() const noexcept                { return fallbackProperties; }

protected:

	/** Subclasses can override this to be told when one of the properies has been changed. */
	virtual void propertyChanged();

private:

	StringPairArray properties;
	PropertySet* fallbackProperties;
	CriticalSection lock;
	bool ignoreCaseOfKeys;

	JUCE_LEAK_DETECTOR (PropertySet);
};

#endif   // __JUCE_PROPERTYSET_JUCEHEADER__

/*** End of inlined file: juce_PropertySet.h ***/


#endif
#ifndef __JUCE_REFERENCECOUNTEDARRAY_JUCEHEADER__

/*** Start of inlined file: juce_ReferenceCountedArray.h ***/
#ifndef __JUCE_REFERENCECOUNTEDARRAY_JUCEHEADER__
#define __JUCE_REFERENCECOUNTEDARRAY_JUCEHEADER__

/**
	Holds a list of objects derived from ReferenceCountedObject.

	A ReferenceCountedArray holds objects derived from ReferenceCountedObject,
	and takes care of incrementing and decrementing their ref counts when they
	are added and removed from the array.

	To make all the array's methods thread-safe, pass in "CriticalSection" as the templated
	TypeOfCriticalSectionToUse parameter, instead of the default DummyCriticalSection.

	@see Array, OwnedArray, StringArray
*/
template <class ObjectClass, class TypeOfCriticalSectionToUse = DummyCriticalSection>
class ReferenceCountedArray
{
public:
	typedef ReferenceCountedObjectPtr<ObjectClass> ObjectClassPtr;

	/** Creates an empty array.
		@see ReferenceCountedObject, Array, OwnedArray
	*/
	ReferenceCountedArray() noexcept
		: numUsed (0)
	{
	}

	/** Creates a copy of another array */
	template <class OtherObjectClass>
	ReferenceCountedArray (const ReferenceCountedArray<OtherObjectClass, TypeOfCriticalSectionToUse>& other) noexcept
	{
		const ScopedLockType lock (other.getLock());
		numUsed = other.size();
		data.setAllocatedSize (numUsed);
		memcpy (data.elements, other.getRawDataPointer(), numUsed * sizeof (ObjectClass*));

		for (int i = numUsed; --i >= 0;)
			if (data.elements[i] != nullptr)
				data.elements[i]->incReferenceCount();
	}

	/** Copies another array into this one.

		Any existing objects in this array will first be released.
	*/
	template <class OtherObjectClass>
	ReferenceCountedArray<ObjectClass, TypeOfCriticalSectionToUse>& operator= (const ReferenceCountedArray<OtherObjectClass, TypeOfCriticalSectionToUse>& other) noexcept
	{
		ReferenceCountedArray<ObjectClass, TypeOfCriticalSectionToUse> otherCopy (other);
		swapWithArray (otherCopy);
		return *this;
	}

	/** Destructor.
		Any objects in the array will be released, and may be deleted if not referenced from elsewhere.
	*/
	~ReferenceCountedArray()
	{
		clear();
	}

	/** Removes all objects from the array.

		Any objects in the array that are not referenced from elsewhere will be deleted.
	*/
	void clear()
	{
		const ScopedLockType lock (getLock());

		while (numUsed > 0)
			if (data.elements [--numUsed] != nullptr)
				data.elements [numUsed]->decReferenceCount();

		jassert (numUsed == 0);
		data.setAllocatedSize (0);
	}

	/** Returns the current number of objects in the array. */
	inline int size() const noexcept
	{
		return numUsed;
	}

	/** Returns a pointer to the object at this index in the array.

		If the index is out-of-range, this will return a null pointer, (and
		it could be null anyway, because it's ok for the array to hold null
		pointers as well as objects).

		@see getUnchecked
	*/
	inline ObjectClassPtr operator[] (const int index) const noexcept
	{
		return getObjectPointer (index);
	}

	/** Returns a pointer to the object at this index in the array, without checking
		whether the index is in-range.

		This is a faster and less safe version of operator[] which doesn't check the index passed in, so
		it can be used when you're sure the index if always going to be legal.
	*/
	inline ObjectClassPtr getUnchecked (const int index) const noexcept
	{
		return getObjectPointerUnchecked (index);
	}

	/** Returns a raw pointer to the object at this index in the array.

		If the index is out-of-range, this will return a null pointer, (and
		it could be null anyway, because it's ok for the array to hold null
		pointers as well as objects).

		@see getUnchecked
	*/
	inline ObjectClass* getObjectPointer (const int index) const noexcept
	{
		const ScopedLockType lock (getLock());
		return isPositiveAndBelow (index, numUsed) ? data.elements [index]
												   : nullptr;
	}

	/** Returns a raw pointer to the object at this index in the array, without checking
		whether the index is in-range.
	*/
	inline ObjectClass* getObjectPointerUnchecked (const int index) const noexcept
	{
		const ScopedLockType lock (getLock());
		jassert (isPositiveAndBelow (index, numUsed));
		return data.elements [index];
	}

	/** Returns a pointer to the first object in the array.

		This will return a null pointer if the array's empty.
		@see getLast
	*/
	inline ObjectClassPtr getFirst() const noexcept
	{
		const ScopedLockType lock (getLock());
		return numUsed > 0 ? data.elements [0]
						   : static_cast <ObjectClass*> (nullptr);
	}

	/** Returns a pointer to the last object in the array.

		This will return a null pointer if the array's empty.
		@see getFirst
	*/
	inline ObjectClassPtr getLast() const noexcept
	{
		const ScopedLockType lock (getLock());
		return numUsed > 0 ? data.elements [numUsed - 1]
						   : static_cast <ObjectClass*> (nullptr);
	}

	/** Returns a pointer to the actual array data.
		This pointer will only be valid until the next time a non-const method
		is called on the array.
	*/
	inline ObjectClass** getRawDataPointer() const noexcept
	{
		return data.elements;
	}

	/** Returns a pointer to the first element in the array.
		This method is provided for compatibility with standard C++ iteration mechanisms.
	*/
	inline ObjectClass** begin() const noexcept
	{
		return data.elements;
	}

	/** Returns a pointer to the element which follows the last element in the array.
		This method is provided for compatibility with standard C++ iteration mechanisms.
	*/
	inline ObjectClass** end() const noexcept
	{
		return data.elements + numUsed;
	}

	/** Finds the index of the first occurrence of an object in the array.

		@param objectToLookFor    the object to look for
		@returns                  the index at which the object was found, or -1 if it's not found
	*/
	int indexOf (const ObjectClass* const objectToLookFor) const noexcept
	{
		const ScopedLockType lock (getLock());
		ObjectClass** e = data.elements.getData();
		ObjectClass** const end_ = e + numUsed;

		while (e != end_)
		{
			if (objectToLookFor == *e)
				return static_cast <int> (e - data.elements.getData());

			++e;
		}

		return -1;
	}

	/** Returns true if the array contains a specified object.

		@param objectToLookFor      the object to look for
		@returns                    true if the object is in the array
	*/
	bool contains (const ObjectClass* const objectToLookFor) const noexcept
	{
		const ScopedLockType lock (getLock());
		ObjectClass** e = data.elements.getData();
		ObjectClass** const end_ = e + numUsed;

		while (e != end_)
		{
			if (objectToLookFor == *e)
				return true;

			++e;
		}

		return false;
	}

	/** Appends a new object to the end of the array.

		This will increase the new object's reference count.

		@param newObject       the new object to add to the array
		@see set, insert, addIfNotAlreadyThere, addSorted, addArray
	*/
	void add (ObjectClass* const newObject) noexcept
	{
		const ScopedLockType lock (getLock());
		data.ensureAllocatedSize (numUsed + 1);
		data.elements [numUsed++] = newObject;

		if (newObject != nullptr)
			newObject->incReferenceCount();
	}

	/** Inserts a new object into the array at the given index.

		If the index is less than 0 or greater than the size of the array, the
		element will be added to the end of the array.
		Otherwise, it will be inserted into the array, moving all the later elements
		along to make room.

		This will increase the new object's reference count.

		@param indexToInsertAt      the index at which the new element should be inserted
		@param newObject            the new object to add to the array
		@see add, addSorted, addIfNotAlreadyThere, set
	*/
	void insert (int indexToInsertAt,
				 ObjectClass* const newObject) noexcept
	{
		if (indexToInsertAt >= 0)
		{
			const ScopedLockType lock (getLock());

			if (indexToInsertAt > numUsed)
				indexToInsertAt = numUsed;

			data.ensureAllocatedSize (numUsed + 1);

			ObjectClass** const e = data.elements + indexToInsertAt;
			const int numToMove = numUsed - indexToInsertAt;

			if (numToMove > 0)
				memmove (e + 1, e, numToMove * sizeof (ObjectClass*));

			*e = newObject;

			if (newObject != nullptr)
				newObject->incReferenceCount();

			++numUsed;
		}
		else
		{
			add (newObject);
		}
	}

	/** Appends a new object at the end of the array as long as the array doesn't
		already contain it.

		If the array already contains a matching object, nothing will be done.

		@param newObject   the new object to add to the array
	*/
	void addIfNotAlreadyThere (ObjectClass* const newObject) noexcept
	{
		const ScopedLockType lock (getLock());
		if (! contains (newObject))
			add (newObject);
	}

	/** Replaces an object in the array with a different one.

		If the index is less than zero, this method does nothing.
		If the index is beyond the end of the array, the new object is added to the end of the array.

		The object being added has its reference count increased, and if it's replacing
		another object, then that one has its reference count decreased, and may be deleted.

		@param indexToChange        the index whose value you want to change
		@param newObject            the new value to set for this index.
		@see add, insert, remove
	*/
	void set (const int indexToChange,
			  ObjectClass* const newObject)
	{
		if (indexToChange >= 0)
		{
			const ScopedLockType lock (getLock());

			if (newObject != nullptr)
				newObject->incReferenceCount();

			if (indexToChange < numUsed)
			{
				if (data.elements [indexToChange] != nullptr)
					data.elements [indexToChange]->decReferenceCount();

				data.elements [indexToChange] = newObject;
			}
			else
			{
				data.ensureAllocatedSize (numUsed + 1);
				data.elements [numUsed++] = newObject;
			}
		}
	}

	/** Adds elements from another array to the end of this array.

		@param arrayToAddFrom       the array from which to copy the elements
		@param startIndex           the first element of the other array to start copying from
		@param numElementsToAdd     how many elements to add from the other array. If this
									value is negative or greater than the number of available elements,
									all available elements will be copied.
		@see add
	*/
	void addArray (const ReferenceCountedArray<ObjectClass, TypeOfCriticalSectionToUse>& arrayToAddFrom,
				   int startIndex = 0,
				   int numElementsToAdd = -1) noexcept
	{
		const ScopedLockType lock1 (arrayToAddFrom.getLock());

		{
			const ScopedLockType lock2 (getLock());

			if (startIndex < 0)
			{
				jassertfalse;
				startIndex = 0;
			}

			if (numElementsToAdd < 0 || startIndex + numElementsToAdd > arrayToAddFrom.size())
				numElementsToAdd = arrayToAddFrom.size() - startIndex;

			if (numElementsToAdd > 0)
			{
				data.ensureAllocatedSize (numUsed + numElementsToAdd);

				while (--numElementsToAdd >= 0)
					add (arrayToAddFrom.getUnchecked (startIndex++));
			}
		}
	}

	/** Inserts a new object into the array assuming that the array is sorted.

		This will use a comparator to find the position at which the new object
		should go. If the array isn't sorted, the behaviour of this
		method will be unpredictable.

		@param comparator   the comparator object to use to compare the elements - see the
							sort() method for details about this object's form
		@param newObject    the new object to insert to the array
		@returns the index at which the new object was added
		@see add, sort
	*/
	template <class ElementComparator>
	int addSorted (ElementComparator& comparator, ObjectClass* newObject) noexcept
	{
		const ScopedLockType lock (getLock());
		const int index = findInsertIndexInSortedArray (comparator, data.elements.getData(), newObject, 0, numUsed);
		insert (index, newObject);
		return index;
	}

	/** Inserts or replaces an object in the array, assuming it is sorted.

		This is similar to addSorted, but if a matching element already exists, then it will be
		replaced by the new one, rather than the new one being added as well.
	*/
	template <class ElementComparator>
	void addOrReplaceSorted (ElementComparator& comparator,
							 ObjectClass* newObject) noexcept
	{
		const ScopedLockType lock (getLock());
		const int index = findInsertIndexInSortedArray (comparator, data.elements.getData(), newObject, 0, numUsed);

		if (index > 0 && comparator.compareElements (newObject, data.elements [index - 1]) == 0)
			set (index - 1, newObject); // replace an existing object that matches
		else
			insert (index, newObject);  // no match, so insert the new one
	}

	/** Removes an object from the array.

		This will remove the object at a given index and move back all the
		subsequent objects to close the gap.

		If the index passed in is out-of-range, nothing will happen.

		The object that is removed will have its reference count decreased,
		and may be deleted if not referenced from elsewhere.

		@param indexToRemove    the index of the element to remove
		@see removeObject, removeRange
	*/
	void remove (const int indexToRemove)
	{
		const ScopedLockType lock (getLock());

		if (isPositiveAndBelow (indexToRemove, numUsed))
		{
			ObjectClass** const e = data.elements + indexToRemove;

			if (*e != nullptr)
				(*e)->decReferenceCount();

			--numUsed;
			const int numberToShift = numUsed - indexToRemove;

			if (numberToShift > 0)
				memmove (e, e + 1, numberToShift * sizeof (ObjectClass*));

			if ((numUsed << 1) < data.numAllocated)
				minimiseStorageOverheads();
		}
	}

	/** Removes and returns an object from the array.

		This will remove the object at a given index and return it, moving back all
		the subsequent objects to close the gap. If the index passed in is out-of-range,
		nothing will happen and a null pointer will be returned.

		@param indexToRemove    the index of the element to remove
		@see remove, removeObject, removeRange
	*/
	ObjectClassPtr removeAndReturn (const int indexToRemove)
	{
		ObjectClassPtr removedItem;
		const ScopedLockType lock (getLock());

		if (isPositiveAndBelow (indexToRemove, numUsed))
		{
			ObjectClass** const e = data.elements + indexToRemove;

			if (*e != nullptr)
			{
				removedItem = *e;
				(*e)->decReferenceCount();
			}

			--numUsed;
			const int numberToShift = numUsed - indexToRemove;

			if (numberToShift > 0)
				memmove (e, e + 1, numberToShift * sizeof (ObjectClass*));

			if ((numUsed << 1) < data.numAllocated)
				minimiseStorageOverheads();
		}

		return removedItem;
	}

	/** Removes the first occurrence of a specified object from the array.

		If the item isn't found, no action is taken. If it is found, it is
		removed and has its reference count decreased.

		@param objectToRemove   the object to try to remove
		@see remove, removeRange
	*/
	void removeObject (ObjectClass* const objectToRemove)
	{
		const ScopedLockType lock (getLock());
		remove (indexOf (objectToRemove));
	}

	/** Removes a range of objects from the array.

		This will remove a set of objects, starting from the given index,
		and move any subsequent elements down to close the gap.

		If the range extends beyond the bounds of the array, it will
		be safely clipped to the size of the array.

		The objects that are removed will have their reference counts decreased,
		and may be deleted if not referenced from elsewhere.

		@param startIndex       the index of the first object to remove
		@param numberToRemove   how many objects should be removed
		@see remove, removeObject
	*/
	void removeRange (const int startIndex,
					  const int numberToRemove)
	{
		const ScopedLockType lock (getLock());

		const int start = jlimit (0, numUsed, startIndex);
		const int end_   = jlimit (0, numUsed, startIndex + numberToRemove);

		if (end_ > start)
		{
			int i;
			for (i = start; i < end_; ++i)
			{
				if (data.elements[i] != nullptr)
				{
					data.elements[i]->decReferenceCount();
					data.elements[i] = nullptr; // (in case one of the destructors accesses this array and hits a dangling pointer)
				}
			}

			const int rangeSize = end_ - start;
			ObjectClass** e = data.elements + start;
			i = numUsed - end_;
			numUsed -= rangeSize;

			while (--i >= 0)
			{
				*e = e [rangeSize];
				++e;
			}

			if ((numUsed << 1) < data.numAllocated)
				minimiseStorageOverheads();
		}
	}

	/** Removes the last n objects from the array.

		The objects that are removed will have their reference counts decreased,
		and may be deleted if not referenced from elsewhere.

		@param howManyToRemove   how many objects to remove from the end of the array
		@see remove, removeObject, removeRange
	*/
	void removeLast (int howManyToRemove = 1)
	{
		const ScopedLockType lock (getLock());

		if (howManyToRemove > numUsed)
			howManyToRemove = numUsed;

		while (--howManyToRemove >= 0)
			remove (numUsed - 1);
	}

	/** Swaps a pair of objects in the array.

		If either of the indexes passed in is out-of-range, nothing will happen,
		otherwise the two objects at these positions will be exchanged.
	*/
	void swap (const int index1,
			   const int index2) noexcept
	{
		const ScopedLockType lock (getLock());

		if (isPositiveAndBelow (index1, numUsed)
			 && isPositiveAndBelow (index2, numUsed))
		{
			std::swap (data.elements [index1],
					   data.elements [index2]);
		}
	}

	/** Moves one of the objects to a different position.

		This will move the object to a specified index, shuffling along
		any intervening elements as required.

		So for example, if you have the array { 0, 1, 2, 3, 4, 5 } then calling
		move (2, 4) would result in { 0, 1, 3, 4, 2, 5 }.

		@param currentIndex     the index of the object to be moved. If this isn't a
								valid index, then nothing will be done
		@param newIndex         the index at which you'd like this object to end up. If this
								is less than zero, it will be moved to the end of the array
	*/
	void move (const int currentIndex,
			   int newIndex) noexcept
	{
		if (currentIndex != newIndex)
		{
			const ScopedLockType lock (getLock());

			if (isPositiveAndBelow (currentIndex, numUsed))
			{
				if (! isPositiveAndBelow (newIndex, numUsed))
					newIndex = numUsed - 1;

				ObjectClass* const value = data.elements [currentIndex];

				if (newIndex > currentIndex)
				{
					memmove (data.elements + currentIndex,
							 data.elements + currentIndex + 1,
							 (newIndex - currentIndex) * sizeof (ObjectClass*));
				}
				else
				{
					memmove (data.elements + newIndex + 1,
							 data.elements + newIndex,
							 (currentIndex - newIndex) * sizeof (ObjectClass*));
				}

				data.elements [newIndex] = value;
			}
		}
	}

	/** This swaps the contents of this array with those of another array.

		If you need to exchange two arrays, this is vastly quicker than using copy-by-value
		because it just swaps their internal pointers.
	*/
	void swapWithArray (ReferenceCountedArray& otherArray) noexcept
	{
		const ScopedLockType lock1 (getLock());
		const ScopedLockType lock2 (otherArray.getLock());

		data.swapWith (otherArray.data);
		std::swap (numUsed, otherArray.numUsed);
	}

	/** Compares this array to another one.

		@returns true only if the other array contains the same objects in the same order
	*/
	bool operator== (const ReferenceCountedArray& other) const noexcept
	{
		const ScopedLockType lock2 (other.getLock());
		const ScopedLockType lock1 (getLock());

		if (numUsed != other.numUsed)
			return false;

		for (int i = numUsed; --i >= 0;)
			if (data.elements [i] != other.data.elements [i])
				return false;

		return true;
	}

	/** Compares this array to another one.

		@see operator==
	*/
	bool operator!= (const ReferenceCountedArray<ObjectClass, TypeOfCriticalSectionToUse>& other) const noexcept
	{
		return ! operator== (other);
	}

	/** Sorts the elements in the array.

		This will use a comparator object to sort the elements into order. The object
		passed must have a method of the form:
		@code
		int compareElements (ElementType first, ElementType second);
		@endcode

		..and this method must return:
		  - a value of < 0 if the first comes before the second
		  - a value of 0 if the two objects are equivalent
		  - a value of > 0 if the second comes before the first

		To improve performance, the compareElements() method can be declared as static or const.

		@param comparator   the comparator to use for comparing elements.
		@param retainOrderOfEquivalentItems     if this is true, then items
							which the comparator says are equivalent will be
							kept in the order in which they currently appear
							in the array. This is slower to perform, but may
							be important in some cases. If it's false, a faster
							algorithm is used, but equivalent elements may be
							rearranged.

		@see sortArray
	*/
	template <class ElementComparator>
	void sort (ElementComparator& comparator,
			   const bool retainOrderOfEquivalentItems = false) const noexcept
	{
		(void) comparator;  // if you pass in an object with a static compareElements() method, this
							// avoids getting warning messages about the parameter being unused

		const ScopedLockType lock (getLock());
		sortArray (comparator, data.elements.getData(), 0, size() - 1, retainOrderOfEquivalentItems);
	}

	/** Reduces the amount of storage being used by the array.

		Arrays typically allocate slightly more storage than they need, and after
		removing elements, they may have quite a lot of unused space allocated.
		This method will reduce the amount of allocated storage to a minimum.
	*/
	void minimiseStorageOverheads() noexcept
	{
		const ScopedLockType lock (getLock());
		data.shrinkToNoMoreThan (numUsed);
	}

	/** Increases the array's internal storage to hold a minimum number of elements.

		Calling this before adding a large known number of elements means that
		the array won't have to keep dynamically resizing itself as the elements
		are added, and it'll therefore be more efficient.
	*/
	void ensureStorageAllocated (const int minNumElements)
	{
		const ScopedLockType lock (getLock());
		data.ensureAllocatedSize (minNumElements);
	}

	/** Returns the CriticalSection that locks this array.
		To lock, you can call getLock().enter() and getLock().exit(), or preferably use
		an object of ScopedLockType as an RAII lock for it.
	*/
	inline const TypeOfCriticalSectionToUse& getLock() const noexcept      { return data; }

	/** Returns the type of scoped lock to use for locking this array */
	typedef typename TypeOfCriticalSectionToUse::ScopedLockType ScopedLockType;

private:

	ArrayAllocationBase <ObjectClass*, TypeOfCriticalSectionToUse> data;
	int numUsed;
};

#endif   // __JUCE_REFERENCECOUNTEDARRAY_JUCEHEADER__

/*** End of inlined file: juce_ReferenceCountedArray.h ***/


#endif
#ifndef __JUCE_SCOPEDVALUESETTER_JUCEHEADER__

/*** Start of inlined file: juce_ScopedValueSetter.h ***/
#ifndef __JUCE_SCOPEDVALUESETTER_JUCEHEADER__
#define __JUCE_SCOPEDVALUESETTER_JUCEHEADER__

/**
	Helper class providing an RAII-based mechanism for temporarily setting and
	then re-setting a value.

	E.g. @code
	int x = 1;

	{
		ScopedValueSetter setter (x, 2);

		// x is now 2
	}

	// x is now 1 again

	{
		ScopedValueSetter setter (x, 3, 4);

		// x is now 3
	}

	// x is now 4
	@endcode

*/
template <typename ValueType>
class ScopedValueSetter
{
public:
	/** Creates a ScopedValueSetter that will immediately change the specified value to the
		given new value, and will then reset it to its original value when this object is deleted.
	*/
	ScopedValueSetter (ValueType& valueToSet,
					   const ValueType& newValue)
		: value (valueToSet),
		  originalValue (valueToSet)
	{
		valueToSet = newValue;
	}

	/** Creates a ScopedValueSetter that will immediately change the specified value to the
		given new value, and will then reset it to be valueWhenDeleted when this object is deleted.
	*/
	ScopedValueSetter (ValueType& valueToSet,
					   const ValueType& newValue,
					   const ValueType& valueWhenDeleted)
		: value (valueToSet),
		  originalValue (valueWhenDeleted)
	{
		valueToSet = newValue;
	}

	~ScopedValueSetter()
	{
		value = originalValue;
	}

private:

	ValueType& value;
	const ValueType originalValue;

	JUCE_DECLARE_NON_COPYABLE (ScopedValueSetter);
};

#endif   // __JUCE_SCOPEDVALUESETTER_JUCEHEADER__

/*** End of inlined file: juce_ScopedValueSetter.h ***/


#endif
#ifndef __JUCE_SORTEDSET_JUCEHEADER__

/*** Start of inlined file: juce_SortedSet.h ***/
#ifndef __JUCE_SORTEDSET_JUCEHEADER__
#define __JUCE_SORTEDSET_JUCEHEADER__

#if JUCE_MSVC
  #pragma warning (push)
  #pragma warning (disable: 4512)
#endif

/**
	Holds a set of unique primitive objects, such as ints or doubles.

	A set can only hold one item with a given value, so if for example it's a
	set of integers, attempting to add the same integer twice will do nothing
	the second time.

	Internally, the list of items is kept sorted (which means that whatever
	kind of primitive type is used must support the ==, <, >, <= and >= operators
	to determine the order), and searching the set for known values is very fast
	because it uses a binary-chop method.

	Note that if you're using a class or struct as the element type, it must be
	capable of being copied or moved with a straightforward memcpy, rather than
	needing construction and destruction code.

	To make all the set's methods thread-safe, pass in "CriticalSection" as the templated
	TypeOfCriticalSectionToUse parameter, instead of the default DummyCriticalSection.

	@see Array, OwnedArray, ReferenceCountedArray, StringArray, CriticalSection
*/
template <class ElementType, class TypeOfCriticalSectionToUse = DummyCriticalSection>
class SortedSet
{
public:

	/** Creates an empty set. */
	SortedSet() noexcept
	   : numUsed (0)
	{
	}

	/** Creates a copy of another set.
		@param other    the set to copy
	*/
	SortedSet (const SortedSet& other) noexcept
	{
		const ScopedLockType lock (other.getLock());
		numUsed = other.numUsed;
		data.setAllocatedSize (other.numUsed);
		memcpy (data.elements, other.data.elements, numUsed * sizeof (ElementType));
	}

	/** Destructor. */
	~SortedSet() noexcept
	{
	}

	/** Copies another set over this one.
		@param other    the set to copy
	*/
	SortedSet& operator= (const SortedSet& other) noexcept
	{
		if (this != &other)
		{
			const ScopedLockType lock1 (other.getLock());
			const ScopedLockType lock2 (getLock());

			data.ensureAllocatedSize (other.size());
			numUsed = other.numUsed;
			memcpy (data.elements, other.data.elements, numUsed * sizeof (ElementType));
			minimiseStorageOverheads();
		}

		return *this;
	}

	/** Compares this set to another one.

		Two sets are considered equal if they both contain the same set of
		elements.

		@param other    the other set to compare with
	*/
	bool operator== (const SortedSet<ElementType>& other) const noexcept
	{
		const ScopedLockType lock (getLock());

		if (numUsed != other.numUsed)
			return false;

		for (int i = numUsed; --i >= 0;)
			if (! (data.elements[i] == other.data.elements[i]))
				return false;

		return true;
	}

	/** Compares this set to another one.

		Two sets are considered equal if they both contain the same set of
		elements.

		@param other    the other set to compare with
	*/
	bool operator!= (const SortedSet<ElementType>& other) const noexcept
	{
		return ! operator== (other);
	}

	/** Removes all elements from the set.

		This will remove all the elements, and free any storage that the set is
		using. To clear it without freeing the storage, use the clearQuick()
		method instead.

		@see clearQuick
	*/
	void clear() noexcept
	{
		const ScopedLockType lock (getLock());
		data.setAllocatedSize (0);
		numUsed = 0;
	}

	/** Removes all elements from the set without freeing the array's allocated storage.

		@see clear
	*/
	void clearQuick() noexcept
	{
		const ScopedLockType lock (getLock());
		numUsed = 0;
	}

	/** Returns the current number of elements in the set.
	*/
	inline int size() const noexcept
	{
		return numUsed;
	}

	/** Returns one of the elements in the set.

		If the index passed in is beyond the range of valid elements, this
		will return zero.

		If you're certain that the index will always be a valid element, you
		can call getUnchecked() instead, which is faster.

		@param index    the index of the element being requested (0 is the first element in the set)
		@see getUnchecked, getFirst, getLast
	*/
	inline ElementType operator[] (const int index) const noexcept
	{
		const ScopedLockType lock (getLock());
		return isPositiveAndBelow (index, numUsed) ? data.elements [index]
												   : ElementType();
	}

	/** Returns one of the elements in the set, without checking the index passed in.
		Unlike the operator[] method, this will try to return an element without
		checking that the index is within the bounds of the set, so should only
		be used when you're confident that it will always be a valid index.

		@param index    the index of the element being requested (0 is the first element in the set)
		@see operator[], getFirst, getLast
	*/
	inline ElementType getUnchecked (const int index) const noexcept
	{
		const ScopedLockType lock (getLock());
		jassert (isPositiveAndBelow (index, numUsed));
		return data.elements [index];
	}

	/** Returns a direct reference to one of the elements in the set, without checking the index passed in.

		This is like getUnchecked, but returns a direct reference to the element, so that
		you can alter it directly. Obviously this can be dangerous, so only use it when
		absolutely necessary.

		@param index    the index of the element being requested (0 is the first element in the array)
	*/
	inline ElementType& getReference (const int index) const noexcept
	{
		const ScopedLockType lock (getLock());
		jassert (isPositiveAndBelow (index, numUsed));
		return data.elements [index];
	}

	/** Returns the first element in the set, or 0 if the set is empty.

		@see operator[], getUnchecked, getLast
	*/
	inline ElementType getFirst() const noexcept
	{
		const ScopedLockType lock (getLock());
		return numUsed > 0 ? data.elements [0] : ElementType();
	}

	/** Returns the last element in the set, or 0 if the set is empty.

		@see operator[], getUnchecked, getFirst
	*/
	inline ElementType getLast() const noexcept
	{
		const ScopedLockType lock (getLock());
		return numUsed > 0 ? data.elements [numUsed - 1] : ElementType();
	}

	/** Returns a pointer to the first element in the set.
		This method is provided for compatibility with standard C++ iteration mechanisms.
	*/
	inline ElementType* begin() const noexcept
	{
		return data.elements;
	}

	/** Returns a pointer to the element which follows the last element in the set.
		This method is provided for compatibility with standard C++ iteration mechanisms.
	*/
	inline ElementType* end() const noexcept
	{
		return data.elements + numUsed;
	}

	/** Finds the index of the first element which matches the value passed in.

		This will search the set for the given object, and return the index
		of its first occurrence. If the object isn't found, the method will return -1.

		@param elementToLookFor   the value or object to look for
		@returns                  the index of the object, or -1 if it's not found
	*/
	int indexOf (const ElementType elementToLookFor) const noexcept
	{
		const ScopedLockType lock (getLock());

		int start = 0;
		int end_ = numUsed;

		for (;;)
		{
			if (start >= end_)
			{
				return -1;
			}
			else if (elementToLookFor == data.elements [start])
			{
				return start;
			}
			else
			{
				const int halfway = (start + end_) >> 1;

				if (halfway == start)
					return -1;
				else if (elementToLookFor < data.elements [halfway])
					end_ = halfway;
				else
					start = halfway;
			}
		}
	}

	/** Returns true if the set contains at least one occurrence of an object.

		@param elementToLookFor     the value or object to look for
		@returns                    true if the item is found
	*/
	bool contains (const ElementType elementToLookFor) const noexcept
	{
		const ScopedLockType lock (getLock());

		int start = 0;
		int end_ = numUsed;

		for (;;)
		{
			if (start >= end_)
			{
				return false;
			}
			else if (elementToLookFor == data.elements [start])
			{
				return true;
			}
			else
			{
				const int halfway = (start + end_) >> 1;

				if (halfway == start)
					return false;
				else if (elementToLookFor < data.elements [halfway])
					end_ = halfway;
				else
					start = halfway;
			}
		}
	}

	/** Adds a new element to the set, (as long as it's not already in there).

		@param newElement       the new object to add to the set
		@see set, insert, addIfNotAlreadyThere, addSorted, addSet, addArray
	*/
	void add (const ElementType newElement) noexcept
	{
		const ScopedLockType lock (getLock());

		int start = 0;
		int end_ = numUsed;

		for (;;)
		{
			if (start >= end_)
			{
				jassert (start <= end_);
				insertInternal (start, newElement);
				break;
			}
			else if (newElement == data.elements [start])
			{
				break;
			}
			else
			{
				const int halfway = (start + end_) >> 1;

				if (halfway == start)
				{
					if (newElement < data.elements [halfway])
						insertInternal (start, newElement);
					else
						insertInternal (start + 1, newElement);

					break;
				}
				else if (newElement < data.elements [halfway])
					end_ = halfway;
				else
					start = halfway;
			}
		}
	}

	/** Adds elements from an array to this set.

		@param elementsToAdd        the array of elements to add
		@param numElementsToAdd     how many elements are in this other array
		@see add
	*/
	void addArray (const ElementType* elementsToAdd,
				   int numElementsToAdd) noexcept
	{
		const ScopedLockType lock (getLock());

		while (--numElementsToAdd >= 0)
			add (*elementsToAdd++);
	}

	/** Adds elements from another set to this one.

		@param setToAddFrom         the set from which to copy the elements
		@param startIndex           the first element of the other set to start copying from
		@param numElementsToAdd     how many elements to add from the other set. If this
									value is negative or greater than the number of available elements,
									all available elements will be copied.
		@see add
	*/
	template <class OtherSetType>
	void addSet (const OtherSetType& setToAddFrom,
				 int startIndex = 0,
				 int numElementsToAdd = -1) noexcept
	{
		const typename OtherSetType::ScopedLockType lock1 (setToAddFrom.getLock());

		{
			const ScopedLockType lock2 (getLock());
			jassert (this != &setToAddFrom);

			if (this != &setToAddFrom)
			{
				if (startIndex < 0)
				{
					jassertfalse;
					startIndex = 0;
				}

				if (numElementsToAdd < 0 || startIndex + numElementsToAdd > setToAddFrom.size())
					numElementsToAdd = setToAddFrom.size() - startIndex;

				addArray (setToAddFrom.elements + startIndex, numElementsToAdd);
			}
		}
	}

	/** Removes an element from the set.

		This will remove the element at a given index.
		If the index passed in is out-of-range, nothing will happen.

		@param indexToRemove    the index of the element to remove
		@returns                the element that has been removed
		@see removeValue, removeRange
	*/
	ElementType remove (const int indexToRemove) noexcept
	{
		const ScopedLockType lock (getLock());

		if (isPositiveAndBelow (indexToRemove, numUsed))
		{
			--numUsed;

			ElementType* const e = data.elements + indexToRemove;
			ElementType const removed = *e;
			const int numberToShift = numUsed - indexToRemove;

			if (numberToShift > 0)
				memmove (e, e + 1, numberToShift * sizeof (ElementType));

			if ((numUsed << 1) < data.numAllocated)
				minimiseStorageOverheads();

			return removed;
		}

		return ElementType();
	}

	/** Removes an item from the set.

		This will remove the given element from the set, if it's there.

		@param valueToRemove   the object to try to remove
		@see remove, removeRange
	*/
	void removeValue (const ElementType valueToRemove) noexcept
	{
		const ScopedLockType lock (getLock());
		remove (indexOf (valueToRemove));
	}

	/** Removes any elements which are also in another set.

		@param otherSet   the other set in which to look for elements to remove
		@see removeValuesNotIn, remove, removeValue, removeRange
	*/
	template <class OtherSetType>
	void removeValuesIn (const OtherSetType& otherSet) noexcept
	{
		const typename OtherSetType::ScopedLockType lock1 (otherSet.getLock());
		const ScopedLockType lock2 (getLock());

		if (this == &otherSet)
		{
			clear();
		}
		else
		{
			if (otherSet.size() > 0)
			{
				for (int i = numUsed; --i >= 0;)
					if (otherSet.contains (data.elements [i]))
						remove (i);
			}
		}
	}

	/** Removes any elements which are not found in another set.

		Only elements which occur in this other set will be retained.

		@param otherSet    the set in which to look for elements NOT to remove
		@see removeValuesIn, remove, removeValue, removeRange
	*/
	template <class OtherSetType>
	void removeValuesNotIn (const OtherSetType& otherSet) noexcept
	{
		const typename OtherSetType::ScopedLockType lock1 (otherSet.getLock());
		const ScopedLockType lock2 (getLock());

		if (this != &otherSet)
		{
			if (otherSet.size() <= 0)
			{
				clear();
			}
			else
			{
				for (int i = numUsed; --i >= 0;)
					if (! otherSet.contains (data.elements [i]))
						remove (i);
			}
		}
	}

	/** Reduces the amount of storage being used by the set.

		Sets typically allocate slightly more storage than they need, and after
		removing elements, they may have quite a lot of unused space allocated.
		This method will reduce the amount of allocated storage to a minimum.
	*/
	void minimiseStorageOverheads() noexcept
	{
		const ScopedLockType lock (getLock());
		data.shrinkToNoMoreThan (numUsed);
	}

	/** Increases the set's internal storage to hold a minimum number of elements.

		Calling this before adding a large known number of elements means that
		the set won't have to keep dynamically resizing itself as the elements
		are added, and it'll therefore be more efficient.
	*/
	void ensureStorageAllocated (const int minNumElements)
	{
		const ScopedLockType lock (getLock());
		data.ensureAllocatedSize (minNumElements);
	}

	/** Returns the CriticalSection that locks this array.
		To lock, you can call getLock().enter() and getLock().exit(), or preferably use
		an object of ScopedLockType as an RAII lock for it.
	*/
	inline const TypeOfCriticalSectionToUse& getLock() const noexcept      { return data; }

	/** Returns the type of scoped lock to use for locking this array */
	typedef typename TypeOfCriticalSectionToUse::ScopedLockType ScopedLockType;

private:

	ArrayAllocationBase <ElementType, TypeOfCriticalSectionToUse> data;
	int numUsed;

	void insertInternal (const int indexToInsertAt, const ElementType newElement) noexcept
	{
		data.ensureAllocatedSize (numUsed + 1);

		ElementType* const insertPos = data.elements + indexToInsertAt;
		const int numberToMove = numUsed - indexToInsertAt;

		if (numberToMove > 0)
			memmove (insertPos + 1, insertPos, numberToMove * sizeof (ElementType));

		*insertPos = newElement;
		++numUsed;
	}
};

#if JUCE_MSVC
  #pragma warning (pop)
#endif

#endif   // __JUCE_SORTEDSET_JUCEHEADER__

/*** End of inlined file: juce_SortedSet.h ***/


#endif
#ifndef __JUCE_SPARSESET_JUCEHEADER__

/*** Start of inlined file: juce_SparseSet.h ***/
#ifndef __JUCE_SPARSESET_JUCEHEADER__
#define __JUCE_SPARSESET_JUCEHEADER__


/*** Start of inlined file: juce_Range.h ***/
#ifndef __JUCE_RANGE_JUCEHEADER__
#define __JUCE_RANGE_JUCEHEADER__

/** A general-purpose range object, that simply represents any linear range with
	a start and end point.

	The templated parameter is expected to be a primitive integer or floating point
	type, though class types could also be used if they behave in a number-like way.
*/
template <typename ValueType>
class Range
{
public:

	/** Constructs an empty range. */
	Range() noexcept
		: start (ValueType()), end (ValueType())
	{
	}

	/** Constructs a range with given start and end values. */
	Range (const ValueType start_, const ValueType end_) noexcept
		: start (start_), end (jmax (start_, end_))
	{
	}

	/** Constructs a copy of another range. */
	Range (const Range& other) noexcept
		: start (other.start), end (other.end)
	{
	}

	/** Copies another range object. */
	Range& operator= (const Range& other) noexcept
	{
		start = other.start;
		end = other.end;
		return *this;
	}

	/** Destructor. */
	~Range() noexcept
	{
	}

	/** Returns the range that lies between two positions (in either order). */
	static Range between (const ValueType position1, const ValueType position2) noexcept
	{
		return (position1 < position2) ? Range (position1, position2)
									   : Range (position2, position1);
	}

	/** Returns a range with the specified start position and a length of zero. */
	static Range emptyRange (const ValueType start) noexcept
	{
		return Range (start, start);
	}

	/** Returns the start of the range. */
	inline ValueType getStart() const noexcept          { return start; }

	/** Returns the length of the range. */
	inline ValueType getLength() const noexcept         { return end - start; }

	/** Returns the end of the range. */
	inline ValueType getEnd() const noexcept            { return end; }

	/** Returns true if the range has a length of zero. */
	inline bool isEmpty() const noexcept                { return start == end; }

	/** Changes the start position of the range, leaving the end position unchanged.
		If the new start position is higher than the current end of the range, the end point
		will be pushed along to equal it, leaving an empty range at the new position.
	*/
	void setStart (const ValueType newStart) noexcept
	{
		start = newStart;
		if (end < newStart)
			end = newStart;
	}

	/** Returns a range with the same end as this one, but a different start.
		If the new start position is higher than the current end of the range, the end point
		will be pushed along to equal it, returning an empty range at the new position.
	*/
	Range withStart (const ValueType newStart) const noexcept
	{
		return Range (newStart, jmax (newStart, end));
	}

	/** Returns a range with the same length as this one, but moved to have the given start position. */
	Range movedToStartAt (const ValueType newStart) const noexcept
	{
		return Range (newStart, end + (newStart - start));
	}

	/** Changes the end position of the range, leaving the start unchanged.
		If the new end position is below the current start of the range, the start point
		will be pushed back to equal the new end point.
	*/
	void setEnd (const ValueType newEnd) noexcept
	{
		end = newEnd;
		if (newEnd < start)
			start = newEnd;
	}

	/** Returns a range with the same start position as this one, but a different end.
		If the new end position is below the current start of the range, the start point
		will be pushed back to equal the new end point.
	*/
	Range withEnd (const ValueType newEnd) const noexcept
	{
		return Range (jmin (start, newEnd), newEnd);
	}

	/** Returns a range with the same length as this one, but moved to have the given start position. */
	Range movedToEndAt (const ValueType newEnd) const noexcept
	{
		return Range (start + (newEnd - end), newEnd);
	}

	/** Changes the length of the range.
		Lengths less than zero are treated as zero.
	*/
	void setLength (const ValueType newLength) noexcept
	{
		end = start + jmax (ValueType(), newLength);
	}

	/** Returns a range with the same start as this one, but a different length.
		Lengths less than zero are treated as zero.
	*/
	Range withLength (const ValueType newLength) const noexcept
	{
		return Range (start, start + newLength);
	}

	/** Adds an amount to the start and end of the range. */
	inline const Range& operator+= (const ValueType amountToAdd) noexcept
	{
		start += amountToAdd;
		end += amountToAdd;
		return *this;
	}

	/** Subtracts an amount from the start and end of the range. */
	inline const Range& operator-= (const ValueType amountToSubtract) noexcept
	{
		start -= amountToSubtract;
		end -= amountToSubtract;
		return *this;
	}

	/** Returns a range that is equal to this one with an amount added to its
		start and end.
	*/
	Range operator+ (const ValueType amountToAdd) const noexcept
	{
		return Range (start + amountToAdd, end + amountToAdd);
	}

	/** Returns a range that is equal to this one with the specified amount
		subtracted from its start and end. */
	Range operator- (const ValueType amountToSubtract) const noexcept
	{
		return Range (start - amountToSubtract, end - amountToSubtract);
	}

	bool operator== (const Range& other) const noexcept     { return start == other.start && end == other.end; }
	bool operator!= (const Range& other) const noexcept     { return start != other.start || end != other.end; }

	/** Returns true if the given position lies inside this range. */
	bool contains (const ValueType position) const noexcept
	{
		return start <= position && position < end;
	}

	/** Returns the nearest value to the one supplied, which lies within the range. */
	ValueType clipValue (const ValueType value) const noexcept
	{
		return jlimit (start, end, value);
	}

	/** Returns true if the given range lies entirely inside this range. */
	bool contains (const Range& other) const noexcept
	{
		return start <= other.start && end >= other.end;
	}

	/** Returns true if the given range intersects this one. */
	bool intersects (const Range& other) const noexcept
	{
		return other.start < end && start < other.end;
	}

	/** Returns the range that is the intersection of the two ranges, or an empty range
		with an undefined start position if they don't overlap. */
	Range getIntersectionWith (const Range& other) const noexcept
	{
		return Range (jmax (start, other.start),
					  jmin (end, other.end));
	}

	/** Returns the smallest range that contains both this one and the other one. */
	Range getUnionWith (const Range& other) const noexcept
	{
		return Range (jmin (start, other.start),
					  jmax (end, other.end));
	}

	/** Returns a given range, after moving it forwards or backwards to fit it
		within this range.

		If the supplied range has a greater length than this one, the return value
		will be this range.

		Otherwise, if the supplied range is smaller than this one, the return value
		will be the new range, shifted forwards or backwards so that it doesn't extend
		beyond this one, but keeping its original length.
	*/
	Range constrainRange (const Range& rangeToConstrain) const noexcept
	{
		const ValueType otherLen = rangeToConstrain.getLength();
		return getLength() <= otherLen
				? *this
				: rangeToConstrain.movedToStartAt (jlimit (start, end - otherLen, rangeToConstrain.getStart()));
	}

private:

	ValueType start, end;
};

#endif   // __JUCE_RANGE_JUCEHEADER__

/*** End of inlined file: juce_Range.h ***/

/**
	Holds a set of primitive values, storing them as a set of ranges.

	This container acts like an array, but can efficiently hold large continguous
	ranges of values. It's quite a specialised class, mostly useful for things
	like keeping the set of selected rows in a listbox.

	The type used as a template paramter must be an integer type, such as int, short,
	int64, etc.
*/
template <class Type>
class SparseSet
{
public:

	/** Creates a new empty set. */
	SparseSet()
	{
	}

	/** Creates a copy of another SparseSet. */
	SparseSet (const SparseSet<Type>& other)
		: values (other.values)
	{
	}

	/** Clears the set. */
	void clear()
	{
		values.clear();
	}

	/** Checks whether the set is empty.

		This is much quicker than using (size() == 0).
	*/
	bool isEmpty() const noexcept
	{
		return values.size() == 0;
	}

	/** Returns the number of values in the set.

		Because of the way the data is stored, this method can take longer if there
		are a lot of items in the set. Use isEmpty() for a quick test of whether there
		are any items.
	*/
	Type size() const
	{
		Type total (0);

		for (int i = 0; i < values.size(); i += 2)
			total += values.getUnchecked (i + 1) - values.getUnchecked (i);

		return total;
	}

	/** Returns one of the values in the set.

		@param index    the index of the value to retrieve, in the range 0 to (size() - 1).
		@returns        the value at this index, or 0 if it's out-of-range
	*/
	Type operator[] (Type index) const
	{
		for (int i = 0; i < values.size(); i += 2)
		{
			const Type start (values.getUnchecked (i));
			const Type len (values.getUnchecked (i + 1) - start);

			if (index < len)
				return start + index;

			index -= len;
		}

		return Type();
	}

	/** Checks whether a particular value is in the set. */
	bool contains (const Type valueToLookFor) const
	{
		for (int i = 0; i < values.size(); ++i)
			if (valueToLookFor < values.getUnchecked(i))
				return (i & 1) != 0;

		return false;
	}

	/** Returns the number of contiguous blocks of values.
		@see getRange
	*/
	int getNumRanges() const noexcept
	{
		return values.size() >> 1;
	}

	/** Returns one of the contiguous ranges of values stored.
		@param rangeIndex   the index of the range to look up, between 0
							and (getNumRanges() - 1)
		@see getTotalRange
	*/
	const Range<Type> getRange (const int rangeIndex) const
	{
		if (isPositiveAndBelow (rangeIndex, getNumRanges()))
			return Range<Type> (values.getUnchecked (rangeIndex << 1),
								values.getUnchecked ((rangeIndex << 1) + 1));
		else
			return Range<Type>();
	}

	/** Returns the range between the lowest and highest values in the set.
		@see getRange
	*/
	Range<Type> getTotalRange() const
	{
		if (values.size() > 0)
		{
			jassert ((values.size() & 1) == 0);
			return Range<Type> (values.getUnchecked (0),
								values.getUnchecked (values.size() - 1));
		}

		return Range<Type>();
	}

	/** Adds a range of contiguous values to the set.
		e.g. addRange (Range \<int\> (10, 14)) will add (10, 11, 12, 13) to the set.
	*/
	void addRange (const Range<Type>& range)
	{
		jassert (range.getLength() >= 0);
		if (range.getLength() > 0)
		{
			removeRange (range);

			values.addUsingDefaultSort (range.getStart());
			values.addUsingDefaultSort (range.getEnd());

			simplify();
		}
	}

	/** Removes a range of values from the set.
		e.g. removeRange (Range\<int\> (10, 14)) will remove (10, 11, 12, 13) from the set.
	*/
	void removeRange (const Range<Type>& rangeToRemove)
	{
		jassert (rangeToRemove.getLength() >= 0);

		if (rangeToRemove.getLength() > 0
			 && values.size() > 0
			 && rangeToRemove.getStart() < values.getUnchecked (values.size() - 1)
			 && values.getUnchecked(0) < rangeToRemove.getEnd())
		{
			const bool onAtStart = contains (rangeToRemove.getStart() - 1);
			const Type lastValue (jmin (rangeToRemove.getEnd(), values.getLast()));
			const bool onAtEnd = contains (lastValue);

			for (int i = values.size(); --i >= 0;)
			{
				if (values.getUnchecked(i) <= lastValue)
				{
					while (values.getUnchecked(i) >= rangeToRemove.getStart())
					{
						values.remove (i);

						if (--i < 0)
							break;
					}

					break;
				}
			}

			if (onAtStart)   values.addUsingDefaultSort (rangeToRemove.getStart());
			if (onAtEnd)     values.addUsingDefaultSort (lastValue);

			simplify();
		}
	}

	/** Does an XOR of the values in a given range. */
	void invertRange (const Range<Type>& range)
	{
		SparseSet newItems;
		newItems.addRange (range);

		int i;
		for (i = getNumRanges(); --i >= 0;)
			newItems.removeRange (getRange (i));

		removeRange (range);

		for (i = newItems.getNumRanges(); --i >= 0;)
			addRange (newItems.getRange(i));
	}

	/** Checks whether any part of a given range overlaps any part of this set. */
	bool overlapsRange (const Range<Type>& range)
	{
		if (range.getLength() > 0)
		{
			for (int i = getNumRanges(); --i >= 0;)
			{
				if (values.getUnchecked ((i << 1) + 1) <= range.getStart())
					return false;

				if (values.getUnchecked (i << 1) < range.getEnd())
					return true;
			}
		}

		return false;
	}

	/** Checks whether the whole of a given range is contained within this one. */
	bool containsRange (const Range<Type>& range)
	{
		if (range.getLength() > 0)
		{
			for (int i = getNumRanges(); --i >= 0;)
			{
				if (values.getUnchecked ((i << 1) + 1) <= range.getStart())
					return false;

				if (values.getUnchecked (i << 1) <= range.getStart()
					 && range.getEnd() <= values.getUnchecked ((i << 1) + 1))
					return true;
			}
		}

		return false;
	}

	bool operator== (const SparseSet<Type>& other) noexcept
	{
		return values == other.values;
	}

	bool operator!= (const SparseSet<Type>& other) noexcept
	{
		return values != other.values;
	}

private:

	// alternating start/end values of ranges of values that are present.
	Array<Type, DummyCriticalSection> values;

	void simplify()
	{
		jassert ((values.size() & 1) == 0);

		for (int i = values.size(); --i > 0;)
			if (values.getUnchecked(i) == values.getUnchecked (i - 1))
				values.removeRange (--i, 2);
	}
};

#endif   // __JUCE_SPARSESET_JUCEHEADER__

/*** End of inlined file: juce_SparseSet.h ***/


#endif
#ifndef __JUCE_VARIANT_JUCEHEADER__

#endif
#ifndef __JUCE_DIRECTORYITERATOR_JUCEHEADER__

/*** Start of inlined file: juce_DirectoryIterator.h ***/
#ifndef __JUCE_DIRECTORYITERATOR_JUCEHEADER__
#define __JUCE_DIRECTORYITERATOR_JUCEHEADER__

/**
	Searches through a the files in a directory, returning each file that is found.

	A DirectoryIterator will search through a directory and its subdirectories using
	a wildcard filepattern match.

	If you may be finding a large number of files, this is better than
	using File::findChildFiles() because it doesn't block while it finds them
	all, and this is more memory-efficient.

	It can also guess how far it's got using a wildly inaccurate algorithm.
*/
class JUCE_API  DirectoryIterator
{
public:

	/** Creates a DirectoryIterator for a given directory.

		After creating one of these, call its next() method to get the
		first file - e.g. @code

		DirectoryIterator iter (File ("/animals/mooses"), true, "*.moose");

		while (iter.next())
		{
			File theFileItFound (iter.getFile());

			... etc
		}
		@endcode

		@param directory    the directory to search in
		@param isRecursive  whether all the subdirectories should also be searched
		@param wildCard     the file pattern to match
		@param whatToLookFor    a value from the File::TypesOfFileToFind enum, specifying
								whether to look for files, directories, or both.
	*/
	DirectoryIterator (const File& directory,
					   bool isRecursive,
					   const String& wildCard = "*",
					   int whatToLookFor = File::findFiles);

	/** Destructor. */
	~DirectoryIterator();

	/** Moves the iterator along to the next file.

		@returns    true if a file was found (you can then use getFile() to see what it was) - or
					false if there are no more matching files.
	*/
	bool next();

	/** Moves the iterator along to the next file, and returns various properties of that file.

		If you need to find out details about the file, it's more efficient to call this method than
		to call the normal next() method and then find out the details afterwards.

		All the parameters are optional, so pass null pointers for any items that you're not
		interested in.

		@returns    true if a file was found (you can then use getFile() to see what it was) - or
					false if there are no more matching files. If it returns false, then none of the
					parameters will be filled-in.
	*/
	bool next (bool* isDirectory,
			   bool* isHidden,
			   int64* fileSize,
			   Time* modTime,
			   Time* creationTime,
			   bool* isReadOnly);

	/** Returns the file that the iterator is currently pointing at.

		The result of this call is only valid after a call to next() has returned true.
	*/
	const File& getFile() const;

	/** Returns a guess of how far through the search the iterator has got.

		@returns    a value 0.0 to 1.0 to show the progress, although this won't be
					very accurate.
	*/
	float getEstimatedProgress() const;

private:

	class NativeIterator
	{
	public:
		NativeIterator (const File& directory, const String& wildCard);
		~NativeIterator();

		bool next (String& filenameFound,
				   bool* isDirectory, bool* isHidden, int64* fileSize,
				   Time* modTime, Time* creationTime, bool* isReadOnly);

		class Pimpl;

	private:
		friend class DirectoryIterator;
		friend class ScopedPointer<Pimpl>;
		ScopedPointer<Pimpl> pimpl;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NativeIterator);
	};

	friend class ScopedPointer<NativeIterator::Pimpl>;
	NativeIterator fileFinder;
	String wildCard, path;
	int index;
	mutable int totalNumFiles;
	const int whatToLookFor;
	const bool isRecursive;
	bool hasBeenAdvanced;
	ScopedPointer <DirectoryIterator> subIterator;
	File currentFile;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DirectoryIterator);
};

#endif   // __JUCE_DIRECTORYITERATOR_JUCEHEADER__

/*** End of inlined file: juce_DirectoryIterator.h ***/


#endif
#ifndef __JUCE_FILE_JUCEHEADER__

#endif
#ifndef __JUCE_FILEINPUTSTREAM_JUCEHEADER__

/*** Start of inlined file: juce_FileInputStream.h ***/
#ifndef __JUCE_FILEINPUTSTREAM_JUCEHEADER__
#define __JUCE_FILEINPUTSTREAM_JUCEHEADER__

/**
	An input stream that reads from a local file.

	@see InputStream, FileOutputStream, File::createInputStream
*/
class JUCE_API  FileInputStream  : public InputStream
{
public:

	/** Creates a FileInputStream.

		@param fileToRead   the file to read from - if the file can't be accessed for some
							reason, then the stream will just contain no data
	*/
	explicit FileInputStream (const File& fileToRead);

	/** Destructor. */
	~FileInputStream();

	/** Returns the file that this stream is reading from. */
	const File& getFile() const noexcept                { return file; }

	/** Returns the status of the file stream.
		The result will be ok if the file opened successfully. If an error occurs while
		opening or reading from the file, this will contain an error message.
	*/
	const Result& getStatus() const noexcept            { return status; }

	/** Returns true if the stream couldn't be opened for some reason.
		@see getResult()
	*/
	bool failedToOpen() const noexcept                  { return status.failed(); }

	/** Returns true if the stream opened without problems.
		@see getResult()
	*/
	bool openedOk() const noexcept                      { return status.wasOk(); }

	int64 getTotalLength();
	int read (void* destBuffer, int maxBytesToRead);
	bool isExhausted();
	int64 getPosition();
	bool setPosition (int64 pos);

private:

	File file;
	void* fileHandle;
	int64 currentPosition, totalSize;
	Result status;
	bool needToSeek;

	void openHandle();
	void closeHandle();
	size_t readInternal (void* buffer, size_t numBytes);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileInputStream);
};

#endif   // __JUCE_FILEINPUTSTREAM_JUCEHEADER__

/*** End of inlined file: juce_FileInputStream.h ***/


#endif
#ifndef __JUCE_FILEOUTPUTSTREAM_JUCEHEADER__

/*** Start of inlined file: juce_FileOutputStream.h ***/
#ifndef __JUCE_FILEOUTPUTSTREAM_JUCEHEADER__
#define __JUCE_FILEOUTPUTSTREAM_JUCEHEADER__

/**
	An output stream that writes into a local file.

	@see OutputStream, FileInputStream, File::createOutputStream
*/
class JUCE_API  FileOutputStream  : public OutputStream
{
public:

	/** Creates a FileOutputStream.

		If the file doesn't exist, it will first be created. If the file can't be
		created or opened, the failedToOpen() method will return
		true.

		If the file already exists when opened, the stream's write-postion will
		be set to the end of the file. To overwrite an existing file,
		use File::deleteFile() before opening the stream, or use setPosition(0)
		after it's opened (although this won't truncate the file).

		@see TemporaryFile
	*/
	FileOutputStream (const File& fileToWriteTo,
					  int bufferSizeToUse = 16384);

	/** Destructor. */
	~FileOutputStream();

	/** Returns the file that this stream is writing to.
	*/
	const File& getFile() const                         { return file; }

	/** Returns the status of the file stream.
		The result will be ok if the file opened successfully. If an error occurs while
		opening or writing to the file, this will contain an error message.
	*/
	const Result& getStatus() const noexcept            { return status; }

	/** Returns true if the stream couldn't be opened for some reason.
		@see getResult()
	*/
	bool failedToOpen() const noexcept                  { return status.failed(); }

	/** Returns true if the stream opened without problems.
		@see getResult()
	*/
	bool openedOk() const noexcept                      { return status.wasOk(); }

	/** Attempts to truncate the file to the current write position.
		To truncate a file to a specific size, first use setPosition() to seek to the
		appropriate location, and then call this method.
	*/
	Result truncate();

	void flush();
	int64 getPosition();
	bool setPosition (int64 pos);
	bool write (const void* data, int numBytes);
	void writeRepeatedByte (uint8 byte, int numTimesToRepeat);

private:

	File file;
	void* fileHandle;
	Result status;
	int64 currentPosition;
	int bufferSize, bytesInBuffer;
	HeapBlock <char> buffer;

	void openHandle();
	void closeHandle();
	void flushInternal();
	bool flushBuffer();
	int64 setPositionInternal (int64 newPosition);
	int writeInternal (const void* data, int numBytes);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileOutputStream);
};

#endif   // __JUCE_FILEOUTPUTSTREAM_JUCEHEADER__

/*** End of inlined file: juce_FileOutputStream.h ***/


#endif
#ifndef __JUCE_FILESEARCHPATH_JUCEHEADER__

/*** Start of inlined file: juce_FileSearchPath.h ***/
#ifndef __JUCE_FILESEARCHPATH_JUCEHEADER__
#define __JUCE_FILESEARCHPATH_JUCEHEADER__

/**
	Encapsulates a set of folders that make up a search path.

	@see File
*/
class JUCE_API  FileSearchPath
{
public:

	/** Creates an empty search path. */
	FileSearchPath();

	/** Creates a search path from a string of pathnames.

		The path can be semicolon- or comma-separated, e.g.
		"/foo/bar;/foo/moose;/fish/moose"

		The separate folders are tokenised and added to the search path.
	*/
	FileSearchPath (const String& path);

	/** Creates a copy of another search path. */
	FileSearchPath (const FileSearchPath& other);

	/** Destructor. */
	~FileSearchPath();

	/** Uses a string containing a list of pathnames to re-initialise this list.

		This search path is cleared and the semicolon- or comma-separated folders
		in this string are added instead. e.g. "/foo/bar;/foo/moose;/fish/moose"
	*/
	FileSearchPath& operator= (const String& path);

	/** Returns the number of folders in this search path.

		@see operator[]
	*/
	int getNumPaths() const;

	/** Returns one of the folders in this search path.

		The file returned isn't guaranteed to actually be a valid directory.

		@see getNumPaths
	*/
	File operator[] (int index) const;

	/** Returns the search path as a semicolon-separated list of directories. */
	String toString() const;

	/** Adds a new directory to the search path.

		The new directory is added to the end of the list if the insertIndex parameter is
		less than zero, otherwise it is inserted at the given index.
	*/
	void add (const File& directoryToAdd,
			  int insertIndex = -1);

	/** Adds a new directory to the search path if it's not already in there. */
	void addIfNotAlreadyThere (const File& directoryToAdd);

	/** Removes a directory from the search path. */
	void remove (int indexToRemove);

	/** Merges another search path into this one.

		This will remove any duplicate directories.
	*/
	void addPath (const FileSearchPath& other);

	/** Removes any directories that are actually subdirectories of one of the other directories in the search path.

		If the search is intended to be recursive, there's no point having nested folders in the search
		path, because they'll just get searched twice and you'll get duplicate results.

		e.g. if the path is "c:\abc\de;c:\abc", this method will simplify it to "c:\abc"
	*/
	void removeRedundantPaths();

	/** Removes any directories that don't actually exist. */
	void removeNonExistentPaths();

	/** Searches the path for a wildcard.

		This will search all the directories in the search path in order, adding any
		matching files to the results array.

		@param results                  an array to append the results to
		@param whatToLookFor            a value from the File::TypesOfFileToFind enum, specifying whether to
										return files, directories, or both.
		@param searchRecursively        whether to recursively search the subdirectories too
		@param wildCardPattern          a pattern to match against the filenames
		@returns the number of files added to the array
		@see File::findChildFiles
	*/
	int findChildFiles (Array<File>& results,
						int whatToLookFor,
						bool searchRecursively,
						const String& wildCardPattern = "*") const;

	/** Finds out whether a file is inside one of the path's directories.

		This will return true if the specified file is a child of one of the
		directories specified by this path. Note that this doesn't actually do any
		searching or check that the files exist - it just looks at the pathnames
		to work out whether the file would be inside a directory.

		@param fileToCheck      the file to look for
		@param checkRecursively if true, then this will return true if the file is inside a
								subfolder of one of the path's directories (at any depth). If false
								it will only return true if the file is actually a direct child
								of one of the directories.
		@see File::isAChildOf

	*/
	bool isFileInPath (const File& fileToCheck,
					   bool checkRecursively) const;

private:

	StringArray directories;

	void init (const String& path);

	JUCE_LEAK_DETECTOR (FileSearchPath);
};

#endif   // __JUCE_FILESEARCHPATH_JUCEHEADER__

/*** End of inlined file: juce_FileSearchPath.h ***/


#endif
#ifndef __JUCE_MEMORYMAPPEDFILE_JUCEHEADER__

/*** Start of inlined file: juce_MemoryMappedFile.h ***/
#ifndef __JUCE_MEMORYMAPPEDFILE_JUCEHEADER__
#define __JUCE_MEMORYMAPPEDFILE_JUCEHEADER__

/**
	Maps a file into virtual memory for easy reading and/or writing.
*/
class JUCE_API  MemoryMappedFile
{
public:
	/** The read/write flags used when opening a memory mapped file. */
	enum AccessMode
	{
		readOnly,   /**< Indicates that the memory can only be read. */
		readWrite   /**< Indicates that the memory can be read and written to - changes that are
						 made will be flushed back to disk at the whim of the OS. */
	};

	/** Opens a file and maps it to an area of virtual memory.

		The file should already exist, and should already be the size that you want to work with
		when you call this. If the file is resized after being opened, the behaviour is undefined.

		If the file exists and the operation succeeds, the getData() and getSize() methods will
		return the location and size of the data that can be read or written. Note that the entire
		file is not read into memory immediately - the OS simply creates a virtual mapping, which
		will lazily pull the data into memory when blocks are accessed.

		If the file can't be opened for some reason, the getData() method will return a null pointer.
	*/
	MemoryMappedFile (const File& file, AccessMode mode);

	/** Destructor. */
	~MemoryMappedFile();

	/** Returns the address at which this file has been mapped, or a null pointer if
		the file couldn't be successfully mapped.
	*/
	void* getData() const noexcept              { return address; }

	/** Returns the number of bytes of data that are available for reading or writing.
		This will normally be the size of the file.
	*/
	size_t getSize() const noexcept             { return length; }

private:

	void* address;
	size_t length;

   #if JUCE_WINDOWS
	void* fileHandle;
   #else
	int fileHandle;
   #endif

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MemoryMappedFile);
};

#endif   // __JUCE_MEMORYMAPPEDFILE_JUCEHEADER__

/*** End of inlined file: juce_MemoryMappedFile.h ***/


#endif
#ifndef __JUCE_TEMPORARYFILE_JUCEHEADER__

/*** Start of inlined file: juce_TemporaryFile.h ***/
#ifndef __JUCE_TEMPORARYFILE_JUCEHEADER__
#define __JUCE_TEMPORARYFILE_JUCEHEADER__

/**
	Manages a temporary file, which will be deleted when this object is deleted.

	This object is intended to be used as a stack based object, using its scope
	to make sure the temporary file isn't left lying around.

	For example:

	@code
	{
		File myTargetFile ("~/myfile.txt");

		// this will choose a file called something like "~/myfile_temp239348.txt"
		// which definitely doesn't exist at the time the constructor is called.
		TemporaryFile temp (myTargetFile);

		// create a stream to the temporary file, and write some data to it...
		ScopedPointer <FileOutputStream> out (temp.getFile().createOutputStream());

		if (out != nullptr)
		{
			out->write ( ...etc )
			out = nullptr; // (deletes the stream)

			// ..now we've finished writing, this will rename the temp file to
			// make it replace the target file we specified above.
			bool succeeded = temp.overwriteTargetFileWithTemporary();
		}

		// ..and even if something went wrong and our overwrite failed,
		// as the TemporaryFile object goes out of scope here, it'll make sure
		// that the temp file gets deleted.
	}
	@endcode

	@see File, FileOutputStream
*/
class JUCE_API  TemporaryFile
{
public:

	enum OptionFlags
	{
		useHiddenFile = 1,          /**< Indicates that the temporary file should be hidden -
										 i.e. its name should start with a dot. */
		putNumbersInBrackets = 2    /**< Indicates that when numbers are appended to make sure
										 the file is unique, they should go in brackets rather
										 than just being appended (see File::getNonexistentSibling() )*/
	};

	/** Creates a randomly-named temporary file in the default temp directory.

		@param suffix       a file suffix to use for the file
		@param optionFlags  a combination of the values listed in the OptionFlags enum
		The file will not be created until you write to it. And remember that when
		this object is deleted, the file will also be deleted!
	*/
	TemporaryFile (const String& suffix = String::empty,
				   int optionFlags = 0);

	/** Creates a temporary file in the same directory as a specified file.

		This is useful if you have a file that you want to overwrite, but don't
		want to harm the original file if the write operation fails. You can
		use this to create a temporary file next to the target file, then
		write to the temporary file, and finally use overwriteTargetFileWithTemporary()
		to replace the target file with the one you've just written.

		This class won't create any files until you actually write to them. And remember
		that when this object is deleted, the temporary file will also be deleted!

		@param targetFile   the file that you intend to overwrite - the temporary
							file will be created in the same directory as this
		@param optionFlags  a combination of the values listed in the OptionFlags enum
	*/
	TemporaryFile (const File& targetFile,
				   int optionFlags = 0);

	/** Destructor.

		When this object is deleted it will make sure that its temporary file is
		also deleted! If the operation fails, it'll throw an assertion in debug
		mode.
	*/
	~TemporaryFile();

	/** Returns the temporary file. */
	const File& getFile() const                 { return temporaryFile; }

	/** Returns the target file that was specified in the constructor. */
	const File& getTargetFile() const           { return targetFile; }

	/** Tries to move the temporary file to overwrite the target file that was
		specified in the constructor.

		If you used the constructor that specified a target file, this will attempt
		to replace that file with the temporary one.

		Before calling this, make sure:
		- that you've actually written to the temporary file
		- that you've closed any open streams that you were using to write to it
		- and that you don't have any streams open to the target file, which would
		  prevent it being overwritten

		If the file move succeeds, this returns false, and the temporary file will
		have disappeared. If it fails, the temporary file will probably still exist,
		but will be deleted when this object is destroyed.
	*/
	bool overwriteTargetFileWithTemporary() const;

	/** Attempts to delete the temporary file, if it exists.
		@returns true if the file is successfully deleted (or if it didn't exist).
	*/
	bool deleteTemporaryFile() const;

private:

	File temporaryFile, targetFile;

	void createTempFile (const File& parentDirectory, String name, const String& suffix, int optionFlags);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TemporaryFile);
};

#endif   // __JUCE_TEMPORARYFILE_JUCEHEADER__

/*** End of inlined file: juce_TemporaryFile.h ***/


#endif
#ifndef __JUCE_JSON_JUCEHEADER__

/*** Start of inlined file: juce_JSON.h ***/
#ifndef __JUCE_JSON_JUCEHEADER__
#define __JUCE_JSON_JUCEHEADER__

class InputStream;
class OutputStream;
class File;

/**
	Contains static methods for converting JSON-formatted text to and from var objects.

	The var class is structurally compatible with JSON-formatted data, so these
	functions allow you to parse JSON into a var object, and to convert a var
	object to JSON-formatted text.

	@see var
*/
class JSON
{
public:

	/** Parses a string of JSON-formatted text, and returns a result code containing
		any parse errors.

		This will return the parsed structure in the parsedResult parameter, and will
		return a Result object to indicate whether parsing was successful, and if not,
		it will contain an error message.

		If you're not interested in the error message, you can use one of the other
		shortcut parse methods, which simply return a var::null if the parsing fails.
	*/
	static Result parse (const String& text, var& parsedResult);

	/** Attempts to parse some JSON-formatted text, and returns the result as a var object.

		If the parsing fails, this simply returns var::null - if you need to find out more
		detail about the parse error, use the alternative parse() method which returns a Result.
	*/
	static var parse (const String& text);

	/** Attempts to parse some JSON-formatted text from a file, and returns the result
		as a var object.

		Note that this is just a short-cut for reading the entire file into a string and
		parsing the result.

		If the parsing fails, this simply returns var::null - if you need to find out more
		detail about the parse error, use the alternative parse() method which returns a Result.
	*/
	static var parse (const File& file);

	/** Attempts to parse some JSON-formatted text from a stream, and returns the result
		as a var object.

		Note that this is just a short-cut for reading the entire stream into a string and
		parsing the result.

		If the parsing fails, this simply returns var::null - if you need to find out more
		detail about the parse error, use the alternative parse() method which returns a Result.
	*/
	static var parse (InputStream& input);

	/** Returns a string which contains a JSON-formatted representation of the var object.
		If allOnOneLine is true, the result will be compacted into a single line of text
		with no carriage-returns. If false, it will be laid-out in a more human-readable format.
		@see writeToStream
	*/
	static String toString (const var& objectToFormat,
							bool allOnOneLine = false);

	/** Writes a JSON-formatted representation of the var object to the given stream.
		If allOnOneLine is true, the result will be compacted into a single line of text
		with no carriage-returns. If false, it will be laid-out in a more human-readable format.
		@see toString
	*/
	static void writeToStream (OutputStream& output,
							   const var& objectToFormat,
							   bool allOnOneLine = false);

private:

	JSON(); // This class can't be instantiated - just use its static methods.
};

#endif   // __JUCE_JSON_JUCEHEADER__

/*** End of inlined file: juce_JSON.h ***/


#endif
#ifndef __JUCE_FILELOGGER_JUCEHEADER__

/*** Start of inlined file: juce_FileLogger.h ***/
#ifndef __JUCE_FILELOGGER_JUCEHEADER__
#define __JUCE_FILELOGGER_JUCEHEADER__

/**
	A simple implemenation of a Logger that writes to a file.

	@see Logger
*/
class JUCE_API  FileLogger  : public Logger
{
public:

	/** Creates a FileLogger for a given file.

		@param fileToWriteTo    the file that to use - new messages will be appended
								to the file. If the file doesn't exist, it will be created,
								along with any parent directories that are needed.
		@param welcomeMessage   when opened, the logger will write a header to the log, along
								with the current date and time, and this welcome message
		@param maxInitialFileSizeBytes  if this is zero or greater, then if the file already exists
								but is larger than this number of bytes, then the start of the
								file will be truncated to keep the size down. This prevents a log
								file getting ridiculously large over time. The file will be truncated
								at a new-line boundary. If this value is less than zero, no size limit
								will be imposed; if it's zero, the file will always be deleted. Note that
								the size is only checked once when this object is created - any logging
								that is done later will be appended without any checking
	*/
	FileLogger (const File& fileToWriteTo,
				const String& welcomeMessage,
				const int maxInitialFileSizeBytes = 128 * 1024);

	/** Destructor. */
	~FileLogger();

	void logMessage (const String& message);

	File getLogFile() const               { return logFile; }

	/** Helper function to create a log file in the correct place for this platform.

		On Windows this will return a logger with a path such as:
		c:\\Documents and Settings\\username\\Application Data\\[logFileSubDirectoryName]\\[logFileName]

		On the Mac it'll create something like:
		~/Library/Logs/[logFileName]

		The method might return 0 if the file can't be created for some reason.

		@param logFileSubDirectoryName      if a subdirectory is needed, this is what it will be called -
											it's best to use the something like the name of your application here.
		@param logFileName                  the name of the file to create, e.g. "MyAppLog.txt". Don't just
											call it "log.txt" because if it goes in a directory with logs
											from other applications (as it will do on the Mac) then no-one
											will know which one is yours!
		@param welcomeMessage               a message that will be written to the log when it's opened.
		@param maxInitialFileSizeBytes      (see the FileLogger constructor for more info on this)
	*/
	static FileLogger* createDefaultAppLogger (const String& logFileSubDirectoryName,
											   const String& logFileName,
											   const String& welcomeMessage,
											   const int maxInitialFileSizeBytes = 128 * 1024);

private:

	File logFile;
	CriticalSection logLock;

	void trimFileSize (int maxFileSizeBytes) const;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileLogger);
};

#endif   // __JUCE_FILELOGGER_JUCEHEADER__

/*** End of inlined file: juce_FileLogger.h ***/


#endif
#ifndef __JUCE_LOGGER_JUCEHEADER__

#endif
#ifndef __JUCE_BIGINTEGER_JUCEHEADER__

/*** Start of inlined file: juce_BigInteger.h ***/
#ifndef __JUCE_BIGINTEGER_JUCEHEADER__
#define __JUCE_BIGINTEGER_JUCEHEADER__

class MemoryBlock;

/**
	An arbitrarily large integer class.

	A BigInteger can be used in a similar way to a normal integer, but has no size
	limit (except for memory and performance constraints).

	Negative values are possible, but the value isn't stored as 2s-complement, so
	be careful if you use negative values and look at the values of individual bits.
*/
class JUCE_API  BigInteger
{
public:

	/** Creates an empty BigInteger */
	BigInteger();

	/** Creates a BigInteger containing an integer value in its low bits.

		The low 32 bits of the number are initialised with this value.
	*/
	BigInteger (uint32 value);

	/** Creates a BigInteger containing an integer value in its low bits.

		The low 32 bits of the number are initialised with the absolute value
		passed in, and its sign is set to reflect the sign of the number.
	*/
	BigInteger (int32 value);

	/** Creates a BigInteger containing an integer value in its low bits.

		The low 64 bits of the number are initialised with the absolute value
		passed in, and its sign is set to reflect the sign of the number.
	*/
	BigInteger (int64 value);

	/** Creates a copy of another BigInteger. */
	BigInteger (const BigInteger& other);

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	BigInteger (BigInteger&& other) noexcept;
	BigInteger& operator= (BigInteger&& other) noexcept;
   #endif

	/** Destructor. */
	~BigInteger();

	/** Copies another BigInteger onto this one. */
	BigInteger& operator= (const BigInteger& other);

	/** Swaps the internal contents of this with another object. */
	void swapWith (BigInteger& other) noexcept;

	/** Returns the value of a specified bit in the number.
		If the index is out-of-range, the result will be false.
	*/
	bool operator[] (int bit) const noexcept;

	/** Returns true if no bits are set. */
	bool isZero() const noexcept;

	/** Returns true if the value is 1. */
	bool isOne() const noexcept;

	/** Attempts to get the lowest bits of the value as an integer.
		If the value is bigger than the integer limits, this will return only the lower bits.
	*/
	int toInteger() const noexcept;

	/** Resets the value to 0. */
	void clear();

	/** Clears a particular bit in the number. */
	void clearBit (int bitNumber) noexcept;

	/** Sets a specified bit to 1. */
	void setBit (int bitNumber);

	/** Sets or clears a specified bit. */
	void setBit (int bitNumber, bool shouldBeSet);

	/** Sets a range of bits to be either on or off.

		@param startBit     the first bit to change
		@param numBits      the number of bits to change
		@param shouldBeSet  whether to turn these bits on or off
	*/
	void setRange (int startBit, int numBits, bool shouldBeSet);

	/** Inserts a bit an a given position, shifting up any bits above it. */
	void insertBit (int bitNumber, bool shouldBeSet);

	/** Returns a range of bits as a new BigInteger.

		e.g. getBitRangeAsInt (0, 64) would return the lowest 64 bits.
		@see getBitRangeAsInt
	*/
	BigInteger getBitRange (int startBit, int numBits) const;

	/** Returns a range of bits as an integer value.

		e.g. getBitRangeAsInt (0, 32) would return the lowest 32 bits.

		Asking for more than 32 bits isn't allowed (obviously) - for that, use
		getBitRange().
	*/
	uint32 getBitRangeAsInt (int startBit, int numBits) const noexcept;

	/** Sets a range of bits to an integer value.

		Copies the given integer onto a range of bits, starting at startBit,
		and using up to numBits of the available bits.
	*/
	void setBitRangeAsInt (int startBit, int numBits, uint32 valueToSet);

	/** Shifts a section of bits left or right.

		@param howManyBitsLeft  how far to move the bits (+ve numbers shift it left, -ve numbers shift it right).
		@param startBit         the first bit to affect - if this is > 0, only bits above that index will be affected.
	*/
	void shiftBits (int howManyBitsLeft, int startBit);

	/** Returns the total number of set bits in the value. */
	int countNumberOfSetBits() const noexcept;

	/** Looks for the index of the next set bit after a given starting point.

		This searches from startIndex (inclusive) upwards for the first set bit,
		and returns its index. If no set bits are found, it returns -1.
	*/
	int findNextSetBit (int startIndex = 0) const noexcept;

	/** Looks for the index of the next clear bit after a given starting point.

		This searches from startIndex (inclusive) upwards for the first clear bit,
		and returns its index.
	*/
	int findNextClearBit (int startIndex = 0) const noexcept;

	/** Returns the index of the highest set bit in the number.
		If the value is zero, this will return -1.
	*/
	int getHighestBit() const noexcept;

	// All the standard arithmetic ops...

	BigInteger& operator+= (const BigInteger& other);
	BigInteger& operator-= (const BigInteger& other);
	BigInteger& operator*= (const BigInteger& other);
	BigInteger& operator/= (const BigInteger& other);
	BigInteger& operator|= (const BigInteger& other);
	BigInteger& operator&= (const BigInteger& other);
	BigInteger& operator^= (const BigInteger& other);
	BigInteger& operator%= (const BigInteger& other);
	BigInteger& operator<<= (int numBitsToShift);
	BigInteger& operator>>= (int numBitsToShift);
	BigInteger& operator++();
	BigInteger& operator--();
	BigInteger operator++ (int);
	BigInteger operator-- (int);

	BigInteger operator-() const;
	BigInteger operator+ (const BigInteger& other) const;
	BigInteger operator- (const BigInteger& other) const;
	BigInteger operator* (const BigInteger& other) const;
	BigInteger operator/ (const BigInteger& other) const;
	BigInteger operator| (const BigInteger& other) const;
	BigInteger operator& (const BigInteger& other) const;
	BigInteger operator^ (const BigInteger& other) const;
	BigInteger operator% (const BigInteger& other) const;
	BigInteger operator<< (int numBitsToShift) const;
	BigInteger operator>> (int numBitsToShift) const;

	bool operator== (const BigInteger& other) const noexcept;
	bool operator!= (const BigInteger& other) const noexcept;
	bool operator<  (const BigInteger& other) const noexcept;
	bool operator<= (const BigInteger& other) const noexcept;
	bool operator>  (const BigInteger& other) const noexcept;
	bool operator>= (const BigInteger& other) const noexcept;

	/** Does a signed comparison of two BigIntegers.

		Return values are:
			- 0 if the numbers are the same
			- < 0 if this number is smaller than the other
			- > 0 if this number is bigger than the other
	*/
	int compare (const BigInteger& other) const noexcept;

	/** Compares the magnitudes of two BigIntegers, ignoring their signs.

		Return values are:
			- 0 if the numbers are the same
			- < 0 if this number is smaller than the other
			- > 0 if this number is bigger than the other
	*/
	int compareAbsolute (const BigInteger& other) const noexcept;

	/** Divides this value by another one and returns the remainder.

		This number is divided by other, leaving the quotient in this number,
		with the remainder being copied to the other BigInteger passed in.
	*/
	void divideBy (const BigInteger& divisor, BigInteger& remainder);

	/** Returns the largest value that will divide both this value and the one passed-in.
	*/
	BigInteger findGreatestCommonDivisor (BigInteger other) const;

	/** Performs a combined exponent and modulo operation.

		This BigInteger's value becomes (this ^ exponent) % modulus.
	*/
	void exponentModulo (const BigInteger& exponent, const BigInteger& modulus);

	/** Performs an inverse modulo on the value.

		i.e. the result is (this ^ -1) mod (modulus).
	*/
	void inverseModulo (const BigInteger& modulus);

	/** Returns true if the value is less than zero.
		@see setNegative, negate
	*/
	bool isNegative() const noexcept;

	/** Changes the sign of the number to be positive or negative.
		@see isNegative, negate
	*/
	void setNegative (bool shouldBeNegative) noexcept;

	/** Inverts the sign of the number.
		@see isNegative, setNegative
	*/
	void negate() noexcept;

	/** Converts the number to a string.

		Specify a base such as 2 (binary), 8 (octal), 10 (decimal), 16 (hex).
		If minimumNumCharacters is greater than 0, the returned string will be
		padded with leading zeros to reach at least that length.
	*/
	String toString (int base, int minimumNumCharacters = 1) const;

	/** Reads the numeric value from a string.

		Specify a base such as 2 (binary), 8 (octal), 10 (decimal), 16 (hex).
		Any invalid characters will be ignored.
	*/
	void parseString (const String& text, int base);

	/** Turns the number into a block of binary data.

		The data is arranged as little-endian, so the first byte of data is the low 8 bits
		of the number, and so on.

		@see loadFromMemoryBlock
	*/
	MemoryBlock toMemoryBlock() const;

	/** Converts a block of raw data into a number.

		The data is arranged as little-endian, so the first byte of data is the low 8 bits
		of the number, and so on.

		@see toMemoryBlock
	*/
	void loadFromMemoryBlock (const MemoryBlock& data);

private:

	HeapBlock <uint32> values;
	size_t numValues;
	int highestBit;
	bool negative;

	void ensureSize (size_t numVals);
	void shiftLeft (int bits, int startBit);
	void shiftRight (int bits, int startBit);

	JUCE_LEAK_DETECTOR (BigInteger);
};

/** Writes a BigInteger to an OutputStream as a UTF8 decimal string. */
OutputStream& JUCE_CALLTYPE operator<< (OutputStream& stream, const BigInteger& value);

#ifndef DOXYGEN
 // For backwards compatibility, BitArray is defined as an alias for BigInteger.
 typedef BigInteger BitArray;
#endif

#endif   // __JUCE_BIGINTEGER_JUCEHEADER__

/*** End of inlined file: juce_BigInteger.h ***/


#endif
#ifndef __JUCE_EXPRESSION_JUCEHEADER__

/*** Start of inlined file: juce_Expression.h ***/
#ifndef __JUCE_EXPRESSION_JUCEHEADER__
#define __JUCE_EXPRESSION_JUCEHEADER__

/**
	A class for dynamically evaluating simple numeric expressions.

	This class can parse a simple C-style string expression involving floating point
	numbers, named symbols and functions. The basic arithmetic operations of +, -, *, /
	are supported, as well as parentheses, and any alphanumeric identifiers are
	assumed to be named symbols which will be resolved when the expression is
	evaluated.

	Expressions which use identifiers and functions require a subclass of
	Expression::Scope to be supplied when evaluating them, and this object
	is expected to be able to resolve the symbol names and perform the functions that
	are used.
*/
class JUCE_API  Expression
{
public:

	/** Creates a simple expression with a value of 0. */
	Expression();

	/** Destructor. */
	~Expression();

	/** Creates a simple expression with a specified constant value. */
	explicit Expression (double constant);

	/** Creates a copy of an expression. */
	Expression (const Expression& other);

	/** Copies another expression. */
	Expression& operator= (const Expression& other);

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	Expression (Expression&& other) noexcept;
	Expression& operator= (Expression&& other) noexcept;
   #endif

	/** Creates an expression by parsing a string.
		If there's a syntax error in the string, this will throw a ParseError exception.
		@throws ParseError
	*/
	explicit Expression (const String& stringToParse);

	/** Returns a string version of the expression. */
	String toString() const;

	/** Returns an expression which is an addtion operation of two existing expressions. */
	Expression operator+ (const Expression& other) const;
	/** Returns an expression which is a subtraction operation of two existing expressions. */
	Expression operator- (const Expression& other) const;
	/** Returns an expression which is a multiplication operation of two existing expressions. */
	Expression operator* (const Expression& other) const;
	/** Returns an expression which is a division operation of two existing expressions. */
	Expression operator/ (const Expression& other) const;
	/** Returns an expression which performs a negation operation on an existing expression. */
	Expression operator-() const;

	/** Returns an Expression which is an identifier reference. */
	static Expression symbol (const String& symbol);

	/** Returns an Expression which is a function call. */
	static Expression function (const String& functionName, const Array<Expression>& parameters);

	/** Returns an Expression which parses a string from a character pointer, and updates the pointer
		to indicate where it finished.

		The pointer is incremented so that on return, it indicates the character that follows
		the end of the expression that was parsed.

		If there's a syntax error in the string, this will throw a ParseError exception.
		@throws ParseError
	*/
	static Expression parse (String::CharPointerType& stringToParse);

	/** When evaluating an Expression object, this class is used to resolve symbols and
		perform functions that the expression uses.
	*/
	class JUCE_API  Scope
	{
	public:
		Scope();
		virtual ~Scope();

		/** Returns some kind of globally unique ID that identifies this scope. */
		virtual String getScopeUID() const;

		/** Returns the value of a symbol.
			If the symbol is unknown, this can throw an Expression::EvaluationError exception.
			The member value is set to the part of the symbol that followed the dot, if there is
			one, e.g. for "foo.bar", symbol = "foo" and member = "bar".
			@throws Expression::EvaluationError
		*/
		virtual Expression getSymbolValue (const String& symbol) const;

		/** Executes a named function.
			If the function name is unknown, this can throw an Expression::EvaluationError exception.
			@throws Expression::EvaluationError
		*/
		virtual double evaluateFunction (const String& functionName,
										 const double* parameters, int numParameters) const;

		/** Used as a callback by the Scope::visitRelativeScope() method.
			You should never create an instance of this class yourself, it's used by the
			expression evaluation code.
		*/
		class Visitor
		{
		public:
			virtual ~Visitor() {}
			virtual void visit (const Scope&) = 0;
		};

		/** Creates a Scope object for a named scope, and then calls a visitor
			to do some kind of processing with this new scope.

			If the name is valid, this method must create a suitable (temporary) Scope
			object to represent it, and must call the Visitor::visit() method with this
			new scope.
		*/
		virtual void visitRelativeScope (const String& scopeName, Visitor& visitor) const;
	};

	/** Evaluates this expression, without using a Scope.
		Without a Scope, no symbols can be used, and only basic functions such as sin, cos, tan,
		min, max are available.
		To find out about any errors during evaluation, use the other version of this method which
		takes a String parameter.
	*/
	double evaluate() const;

	/** Evaluates this expression, providing a scope that should be able to evaluate any symbols
		or functions that it uses.
		To find out about any errors during evaluation, use the other version of this method which
		takes a String parameter.
	*/
	double evaluate (const Scope& scope) const;

	/** Evaluates this expression, providing a scope that should be able to evaluate any symbols
		or functions that it uses.
	*/
	double evaluate (const Scope& scope, String& evaluationError) const;

	/** Attempts to return an expression which is a copy of this one, but with a constant adjusted
		to make the expression resolve to a target value.

		E.g. if the expression is "x + 10" and x is 5, then asking for a target value of 8 will return
		the expression "x + 3". Obviously some expressions can't be reversed in this way, in which
		case they might just be adjusted by adding a constant to the original expression.

		@throws Expression::EvaluationError
	*/
	Expression adjustedToGiveNewResult (double targetValue, const Scope& scope) const;

	/** Represents a symbol that is used in an Expression. */
	struct Symbol
	{
		Symbol (const String& scopeUID, const String& symbolName);
		bool operator== (const Symbol&) const noexcept;
		bool operator!= (const Symbol&) const noexcept;

		String scopeUID;    /**< The unique ID of the Scope that contains this symbol. */
		String symbolName;  /**< The name of the symbol. */
	};

	/** Returns a copy of this expression in which all instances of a given symbol have been renamed. */
	Expression withRenamedSymbol (const Symbol& oldSymbol, const String& newName, const Scope& scope) const;

	/** Returns true if this expression makes use of the specified symbol.
		If a suitable scope is supplied, the search will dereference and recursively check
		all symbols, so that it can be determined whether this expression relies on the given
		symbol at any level in its evaluation. If the scope parameter is null, this just checks
		whether the expression contains any direct references to the symbol.

		@throws Expression::EvaluationError
	*/
	bool referencesSymbol (const Symbol& symbol, const Scope& scope) const;

	/** Returns true if this expression contains any symbols. */
	bool usesAnySymbols() const;

	/** Returns a list of all symbols that may be needed to resolve this expression in the given scope. */
	void findReferencedSymbols (Array<Symbol>& results, const Scope& scope) const;

	/** An exception that can be thrown by Expression::parse(). */
	class ParseError  : public std::exception
	{
	public:
		ParseError (const String& message);

		String description;
	};

	/** Expression type.
		@see Expression::getType()
	*/
	enum Type
	{
		constantType,
		functionType,
		operatorType,
		symbolType
	};

	/** Returns the type of this expression. */
	Type getType() const noexcept;

	/** If this expression is a symbol, function or operator, this returns its identifier. */
	String getSymbolOrFunction() const;

	/** Returns the number of inputs to this expression.
		@see getInput
	*/
	int getNumInputs() const;

	/** Retrieves one of the inputs to this expression.
		@see getNumInputs
	*/
	Expression getInput (int index) const;

private:

	class Term;
	struct Helpers;
	friend class Term;
	friend struct Helpers;
	friend class ScopedPointer<Term>;
	friend class ReferenceCountedObjectPtr<Term>;
	ReferenceCountedObjectPtr<Term> term;

	explicit Expression (Term*);
};

#endif   // __JUCE_EXPRESSION_JUCEHEADER__

/*** End of inlined file: juce_Expression.h ***/


#endif
#ifndef __JUCE_MATHSFUNCTIONS_JUCEHEADER__

#endif
#ifndef __JUCE_RANDOM_JUCEHEADER__

/*** Start of inlined file: juce_Random.h ***/
#ifndef __JUCE_RANDOM_JUCEHEADER__
#define __JUCE_RANDOM_JUCEHEADER__

/**
	A random number generator.

	You can create a Random object and use it to generate a sequence of random numbers.
*/
class JUCE_API  Random
{
public:

	/** Creates a Random object based on a seed value.

		For a given seed value, the subsequent numbers generated by this object
		will be predictable, so a good idea is to set this value based
		on the time, e.g.

		new Random (Time::currentTimeMillis())
	*/
	explicit Random (int64 seedValue) noexcept;

	/** Creates a Random object using a random seed value.
		Internally, this calls setSeedRandomly() to randomise the seed.
	*/
	Random();

	/** Destructor. */
	~Random() noexcept;

	/** Returns the next random 32 bit integer.

		@returns a random integer from the full range 0x80000000 to 0x7fffffff
	*/
	int nextInt() noexcept;

	/** Returns the next random number, limited to a given range.
		The maxValue parameter may not be negative, or zero.
		@returns a random integer between 0 (inclusive) and maxValue (exclusive).
	*/
	int nextInt (int maxValue) noexcept;

	/** Returns the next 64-bit random number.

		@returns a random integer from the full range 0x8000000000000000 to 0x7fffffffffffffff
	*/
	int64 nextInt64() noexcept;

	/** Returns the next random floating-point number.

		@returns a random value in the range 0 to 1.0
	*/
	float nextFloat() noexcept;

	/** Returns the next random floating-point number.

		@returns a random value in the range 0 to 1.0
	*/
	double nextDouble() noexcept;

	/** Returns the next random boolean value.
	*/
	bool nextBool() noexcept;

	/** Returns a BigInteger containing a random number.

		@returns a random value in the range 0 to (maximumValue - 1).
	*/
	BigInteger nextLargeNumber (const BigInteger& maximumValue);

	/** Sets a range of bits in a BigInteger to random values. */
	void fillBitsRandomly (BigInteger& arrayToChange, int startBit, int numBits);

	/** Resets this Random object to a given seed value. */
	void setSeed (int64 newSeed) noexcept;

	/** Merges this object's seed with another value.
		This sets the seed to be a value created by combining the current seed and this
		new value.
	*/
	void combineSeed (int64 seedValue) noexcept;

	/** Reseeds this generator using a value generated from various semi-random system
		properties like the current time, etc.

		Because this function convolves the time with the last seed value, calling
		it repeatedly will increase the randomness of the final result.
	*/
	void setSeedRandomly();

	/** The overhead of creating a new Random object is fairly small, but if you want to avoid
		it, you can call this method to get a global shared Random object.

		It's not thread-safe though, so threads should use their own Random object, otherwise
		you run the risk of your random numbers becoming.. erm.. randomly corrupted..
	*/
	static Random& getSystemRandom() noexcept;

private:

	int64 seed;

	JUCE_LEAK_DETECTOR (Random);
};

#endif   // __JUCE_RANDOM_JUCEHEADER__

/*** End of inlined file: juce_Random.h ***/


#endif
#ifndef __JUCE_RANGE_JUCEHEADER__

#endif
#ifndef __JUCE_ATOMIC_JUCEHEADER__

#endif
#ifndef __JUCE_BYTEORDER_JUCEHEADER__

#endif
#ifndef __JUCE_HEAPBLOCK_JUCEHEADER__

#endif
#ifndef __JUCE_LEAKEDOBJECTDETECTOR_JUCEHEADER__

#endif
#ifndef __JUCE_MEMORY_JUCEHEADER__

#endif
#ifndef __JUCE_MEMORYBLOCK_JUCEHEADER__

#endif
#ifndef __JUCE_OPTIONALSCOPEDPOINTER_JUCEHEADER__

/*** Start of inlined file: juce_OptionalScopedPointer.h ***/
#ifndef __JUCE_OPTIONALSCOPEDPOINTER_JUCEHEADER__
#define __JUCE_OPTIONALSCOPEDPOINTER_JUCEHEADER__

/**
	Holds a pointer to an object which can optionally be deleted when this pointer
	goes out of scope.

	This acts in many ways like a ScopedPointer, but allows you to specify whether or
	not the object is deleted.

	@see ScopedPointer
*/
template <class ObjectType>
class OptionalScopedPointer
{
public:

	/** Creates an empty OptionalScopedPointer. */
	OptionalScopedPointer() : shouldDelete (false) {}

	/** Creates an OptionalScopedPointer to point to a given object, and specifying whether
		the OptionalScopedPointer will delete it.

		If takeOwnership is true, then the OptionalScopedPointer will act like a ScopedPointer,
		deleting the object when it is itself deleted. If this parameter is false, then the
		OptionalScopedPointer just holds a normal pointer to the object, and won't delete it.
	*/
	OptionalScopedPointer (ObjectType* objectToHold, bool takeOwnership)
		: object (objectToHold), shouldDelete (takeOwnership)
	{
	}

	/** Takes ownership of the object that another OptionalScopedPointer holds.

		Like a normal ScopedPointer, the objectToTransferFrom object will become null,
		as ownership of the managed object is transferred to this object.

		The flag to indicate whether or not to delete the managed object is also
		copied from the source object.
	*/
	OptionalScopedPointer (OptionalScopedPointer& objectToTransferFrom)
		: object (objectToTransferFrom.release()),
		  shouldDelete (objectToTransferFrom.shouldDelete)
	{
	}

	/** Takes ownership of the object that another OptionalScopedPointer holds.

		Like a normal ScopedPointer, the objectToTransferFrom object will become null,
		as ownership of the managed object is transferred to this object.

		The ownership flag that says whether or not to delete the managed object is also
		copied from the source object.
	*/
	OptionalScopedPointer& operator= (OptionalScopedPointer& objectToTransferFrom)
	{
		if (object != objectToTransferFrom.object)
		{
			clear();
			object = objectToTransferFrom.object;
		}

		shouldDelete = objectToTransferFrom.shouldDelete;
		return *this;
	}

	/** The destructor may or may not delete the object that is being held, depending on the
		takeOwnership flag that was specified when the object was first passed into an
		OptionalScopedPointer constructor.
	*/
	~OptionalScopedPointer()
	{
		clear();
	}

	/** Returns the object that this pointer is managing. */
	inline operator ObjectType*() const noexcept                    { return object; }

	/** Returns the object that this pointer is managing. */
	inline ObjectType& operator*() const noexcept                   { return *object; }

	/** Lets you access methods and properties of the object that this pointer is holding. */
	inline ObjectType* operator->() const noexcept                  { return object; }

	/** Removes the current object from this OptionalScopedPointer without deleting it.
		This will return the current object, and set this OptionalScopedPointer to a null pointer.
	*/
	ObjectType* release() noexcept                                  { return object.release(); }

	/** Resets this pointer to null, possibly deleting the object that it holds, if it has
		ownership of it.
	*/
	void clear()
	{
		if (! shouldDelete)
			object.release();
	}

	/** Swaps this object with another OptionalScopedPointer.
		The two objects simply exchange their states.
	*/
	void swapWith (OptionalScopedPointer<ObjectType>& other) noexcept
	{
		object.swapWith (other.object);
		std::swap (shouldDelete, other.shouldDelete);
	}

private:

	ScopedPointer<ObjectType> object;
	bool shouldDelete;
};

#endif   // __JUCE_OPTIONALSCOPEDPOINTER_JUCEHEADER__

/*** End of inlined file: juce_OptionalScopedPointer.h ***/


#endif
#ifndef __JUCE_REFERENCECOUNTEDOBJECT_JUCEHEADER__

#endif
#ifndef __JUCE_SCOPEDPOINTER_JUCEHEADER__

#endif
#ifndef __JUCE_SINGLETON_JUCEHEADER__

/*** Start of inlined file: juce_Singleton.h ***/
#ifndef __JUCE_SINGLETON_JUCEHEADER__
#define __JUCE_SINGLETON_JUCEHEADER__

/**
	Macro to declare member variables and methods for a singleton class.

	To use this, add the line juce_DeclareSingleton (MyClass, doNotRecreateAfterDeletion)
	to the class's definition.

	Then put a macro juce_ImplementSingleton (MyClass) along with the class's
	implementation code.

	It's also a very good idea to also add the call clearSingletonInstance() in your class's
	destructor, in case it is deleted by other means than deleteInstance()

	Clients can then call the static method MyClass::getInstance() to get a pointer
	to the singleton, or MyClass::getInstanceWithoutCreating() which will return 0 if
	no instance currently exists.

	e.g. @code

		class MySingleton
		{
		public:
			MySingleton()
			{
			}

			~MySingleton()
			{
				// this ensures that no dangling pointers are left when the
				// singleton is deleted.
				clearSingletonInstance();
			}

			juce_DeclareSingleton (MySingleton, false)
		};

		juce_ImplementSingleton (MySingleton)

		// example of usage:
		MySingleton* m = MySingleton::getInstance(); // creates the singleton if there isn't already one.

		...

		MySingleton::deleteInstance(); // safely deletes the singleton (if it's been created).

	@endcode

	If doNotRecreateAfterDeletion = true, it won't allow the object to be created more
	than once during the process's lifetime - i.e. after you've created and deleted the
	object, getInstance() will refuse to create another one. This can be useful to stop
	objects being accidentally re-created during your app's shutdown code.

	If you know that your object will only be created and deleted by a single thread, you
	can use the slightly more efficient juce_DeclareSingleton_SingleThreaded() macro instead
	of this one.

	@see juce_ImplementSingleton, juce_DeclareSingleton_SingleThreaded
*/
#define juce_DeclareSingleton(classname, doNotRecreateAfterDeletion) \
\
	static classname* _singletonInstance;  \
	static juce::CriticalSection _singletonLock; \
\
	static classname* JUCE_CALLTYPE getInstance() \
	{ \
		if (_singletonInstance == nullptr) \
		{\
			const juce::ScopedLock sl (_singletonLock); \
\
			if (_singletonInstance == nullptr) \
			{ \
				static bool alreadyInside = false; \
				static bool createdOnceAlready = false; \
\
				const bool problem = alreadyInside || ((doNotRecreateAfterDeletion) && createdOnceAlready); \
				jassert (! problem); \
				if (! problem) \
				{ \
					createdOnceAlready = true; \
					alreadyInside = true; \
					classname* newObject = new classname();  /* (use a stack variable to avoid setting the newObject value before the class has finished its constructor) */ \
					alreadyInside = false; \
\
					_singletonInstance = newObject; \
				} \
			} \
		} \
\
		return _singletonInstance; \
	} \
\
	static inline classname* JUCE_CALLTYPE getInstanceWithoutCreating() noexcept\
	{ \
		return _singletonInstance; \
	} \
\
	static void JUCE_CALLTYPE deleteInstance() \
	{ \
		const juce::ScopedLock sl (_singletonLock); \
		if (_singletonInstance != nullptr) \
		{ \
			classname* const old = _singletonInstance; \
			_singletonInstance = nullptr; \
			delete old; \
		} \
	} \
\
	void clearSingletonInstance() noexcept\
	{ \
		if (_singletonInstance == this) \
			_singletonInstance = nullptr; \
	}

/** This is a counterpart to the juce_DeclareSingleton macro.

	After adding the juce_DeclareSingleton to the class definition, this macro has
	to be used in the cpp file.
*/
#define juce_ImplementSingleton(classname) \
\
	classname* classname::_singletonInstance = nullptr; \
	juce::CriticalSection classname::_singletonLock;

/**
	Macro to declare member variables and methods for a singleton class.

	This is exactly the same as juce_DeclareSingleton, but doesn't use a critical
	section to make access to it thread-safe. If you know that your object will
	only ever be created or deleted by a single thread, then this is a
	more efficient version to use.

	If doNotRecreateAfterDeletion = true, it won't allow the object to be created more
	than once during the process's lifetime - i.e. after you've created and deleted the
	object, getInstance() will refuse to create another one. This can be useful to stop
	objects being accidentally re-created during your app's shutdown code.

	See the documentation for juce_DeclareSingleton for more information about
	how to use it, the only difference being that you have to use
	juce_ImplementSingleton_SingleThreaded instead of juce_ImplementSingleton.

	@see juce_ImplementSingleton_SingleThreaded, juce_DeclareSingleton, juce_DeclareSingleton_SingleThreaded_Minimal
*/
#define juce_DeclareSingleton_SingleThreaded(classname, doNotRecreateAfterDeletion) \
\
	static classname* _singletonInstance;  \
\
	static classname* getInstance() \
	{ \
		if (_singletonInstance == nullptr) \
		{ \
			static bool alreadyInside = false; \
			static bool createdOnceAlready = false; \
\
			const bool problem = alreadyInside || ((doNotRecreateAfterDeletion) && createdOnceAlready); \
			jassert (! problem); \
			if (! problem) \
			{ \
				createdOnceAlready = true; \
				alreadyInside = true; \
				classname* newObject = new classname();  /* (use a stack variable to avoid setting the newObject value before the class has finished its constructor) */ \
				alreadyInside = false; \
\
				_singletonInstance = newObject; \
			} \
		} \
\
		return _singletonInstance; \
	} \
\
	static inline classname* getInstanceWithoutCreating() noexcept\
	{ \
		return _singletonInstance; \
	} \
\
	static void deleteInstance() \
	{ \
		if (_singletonInstance != nullptr) \
		{ \
			classname* const old = _singletonInstance; \
			_singletonInstance = nullptr; \
			delete old; \
		} \
	} \
\
	void clearSingletonInstance() noexcept\
	{ \
		if (_singletonInstance == this) \
			_singletonInstance = nullptr; \
	}

/**
	Macro to declare member variables and methods for a singleton class.

	This is like juce_DeclareSingleton_SingleThreaded, but doesn't do any checking
	for recursion or repeated instantiation. It's intended for use as a lightweight
	version of a singleton, where you're using it in very straightforward
	circumstances and don't need the extra checking.

	Juce use the normal juce_ImplementSingleton_SingleThreaded as the counterpart
	to this declaration, as you would with juce_DeclareSingleton_SingleThreaded.

	See the documentation for juce_DeclareSingleton for more information about
	how to use it, the only difference being that you have to use
	juce_ImplementSingleton_SingleThreaded instead of juce_ImplementSingleton.

	@see juce_ImplementSingleton_SingleThreaded, juce_DeclareSingleton
*/
#define juce_DeclareSingleton_SingleThreaded_Minimal(classname) \
\
	static classname* _singletonInstance;  \
\
	static classname* getInstance() \
	{ \
		if (_singletonInstance == nullptr) \
			_singletonInstance = new classname(); \
\
		return _singletonInstance; \
	} \
\
	static inline classname* getInstanceWithoutCreating() noexcept\
	{ \
		return _singletonInstance; \
	} \
\
	static void deleteInstance() \
	{ \
		if (_singletonInstance != nullptr) \
		{ \
			classname* const old = _singletonInstance; \
			_singletonInstance = nullptr; \
			delete old; \
		} \
	} \
\
	void clearSingletonInstance() noexcept\
	{ \
		if (_singletonInstance == this) \
			_singletonInstance = nullptr; \
	}

/** This is a counterpart to the juce_DeclareSingleton_SingleThreaded macro.

	After adding juce_DeclareSingleton_SingleThreaded or juce_DeclareSingleton_SingleThreaded_Minimal
	to the class definition, this macro has to be used somewhere in the cpp file.
*/
#define juce_ImplementSingleton_SingleThreaded(classname) \
\
	classname* classname::_singletonInstance = nullptr;

#endif   // __JUCE_SINGLETON_JUCEHEADER__

/*** End of inlined file: juce_Singleton.h ***/


#endif
#ifndef __JUCE_WEAKREFERENCE_JUCEHEADER__

/*** Start of inlined file: juce_WeakReference.h ***/
#ifndef __JUCE_WEAKREFERENCE_JUCEHEADER__
#define __JUCE_WEAKREFERENCE_JUCEHEADER__

/**
	This class acts as a pointer which will automatically become null if the object
	to which it points is deleted.

	To accomplish this, the source object needs to cooperate by performing a couple of simple tasks.
	It must embed a WeakReference::Master object, which stores a shared pointer object, and must clear
	this master pointer in its destructor.

	E.g.
	@code
	class MyObject
	{
	public:
		MyObject()
		{
			// If you're planning on using your WeakReferences in a multi-threaded situation, you may choose
			// to create a WeakReference to the object here in the constructor, which will pre-initialise the
			// embedded object, avoiding an (extremely unlikely) race condition that could occur if multiple
			// threads overlap while creating the first WeakReference to it.
		}

		~MyObject()
		{
			// This will zero all the references - you need to call this in your destructor.
			masterReference.clear();
		}

	private:
		// You need to embed a variable of this type, with the name "masterReference" inside your object. If the
		// variable is not public, you should make your class a friend of WeakReference<MyObject> so that the
		// WeakReference class can access it.
		WeakReference<MyObject>::Master masterReference;
		friend class WeakReference<MyObject>;
	};

	// Here's an example of using a pointer..

	MyObject* n = new MyObject();
	WeakReference<MyObject> myObjectRef = n;

	MyObject* pointer1 = myObjectRef;  // returns a valid pointer to 'n'
	delete n;
	MyObject* pointer2 = myObjectRef;  // returns a null pointer
	@endcode

	@see WeakReference::Master
*/
template <class ObjectType, class ReferenceCountingType = ReferenceCountedObject>
class WeakReference
{
public:
	/** Creates a null SafePointer. */
	inline WeakReference() noexcept {}

	/** Creates a WeakReference that points at the given object. */
	WeakReference (ObjectType* const object)  : holder (getRef (object)) {}

	/** Creates a copy of another WeakReference. */
	WeakReference (const WeakReference& other) noexcept         : holder (other.holder) {}

	/** Copies another pointer to this one. */
	WeakReference& operator= (const WeakReference& other)       { holder = other.holder; return *this; }

	/** Copies another pointer to this one. */
	WeakReference& operator= (ObjectType* const newObject)      { holder = getRef (newObject); return *this; }

   #if JUCE_COMPILER_SUPPORTS_MOVE_SEMANTICS
	WeakReference (WeakReference&& other) noexcept              : holder (static_cast <SharedRef&&> (other.holder)) {}
	WeakReference& operator= (WeakReference&& other) noexcept   { holder = static_cast <SharedRef&&> (other.holder); return *this; }
   #endif

	/** Returns the object that this pointer refers to, or null if the object no longer exists. */
	ObjectType* get() const noexcept                            { return holder != nullptr ? holder->get() : nullptr; }

	/** Returns the object that this pointer refers to, or null if the object no longer exists. */
	operator ObjectType*() const noexcept                       { return get(); }

	/** Returns the object that this pointer refers to, or null if the object no longer exists. */
	ObjectType* operator->() noexcept                           { return get(); }

	/** Returns the object that this pointer refers to, or null if the object no longer exists. */
	const ObjectType* operator->() const noexcept               { return get(); }

	/** This returns true if this reference has been pointing at an object, but that object has
		since been deleted.

		If this reference was only ever pointing at a null pointer, this will return false. Using
		operator=() to make this refer to a different object will reset this flag to match the status
		of the reference from which you're copying.
	*/
	bool wasObjectDeleted() const noexcept                      { return holder != nullptr && holder->get() == nullptr; }

	bool operator== (ObjectType* const object) const noexcept   { return get() == object; }
	bool operator!= (ObjectType* const object) const noexcept   { return get() != object; }

	/** This class is used internally by the WeakReference class - don't use it directly
		in your code!
		@see WeakReference
	*/
	class SharedPointer   : public ReferenceCountingType
	{
	public:
		explicit SharedPointer (ObjectType* const owner_) noexcept : owner (owner_) {}

		inline ObjectType* get() const noexcept     { return owner; }
		void clearPointer() noexcept                { owner = nullptr; }

	private:
		ObjectType* volatile owner;

		JUCE_DECLARE_NON_COPYABLE (SharedPointer);
	};

	typedef ReferenceCountedObjectPtr<SharedPointer> SharedRef;

	/**
		This class is embedded inside an object to which you want to attach WeakReference pointers.
		See the WeakReference class notes for an example of how to use this class.
		@see WeakReference
	*/
	class Master
	{
	public:
		Master() noexcept {}

		~Master()
		{
			// You must remember to call clear() in your source object's destructor! See the notes
			// for the WeakReference class for an example of how to do this.
			jassert (sharedPointer == nullptr || sharedPointer->get() == nullptr);
		}

		/** The first call to this method will create an internal object that is shared by all weak
			references to the object.
		*/
		SharedPointer* getSharedPointer (ObjectType* const object)
		{
			if (sharedPointer == nullptr)
			{
				sharedPointer = new SharedPointer (object);
			}
			else
			{
				// You're trying to create a weak reference to an object that has already been deleted!!
				jassert (sharedPointer->get() != nullptr);
			}

			return sharedPointer;
		}

		/** The object that owns this master pointer should call this before it gets destroyed,
			to zero all the references to this object that may be out there. See the WeakReference
			class notes for an example of how to do this.
		*/
		void clear()
		{
			if (sharedPointer != nullptr)
				sharedPointer->clearPointer();
		}

	private:
		SharedRef sharedPointer;

		JUCE_DECLARE_NON_COPYABLE (Master);
	};

private:
	SharedRef holder;

	static inline SharedPointer* getRef (ObjectType* const o)
	{
		return (o != nullptr) ? o->masterReference.getSharedPointer (o) : nullptr;
	}
};

#endif   // __JUCE_WEAKREFERENCE_JUCEHEADER__

/*** End of inlined file: juce_WeakReference.h ***/


#endif
#ifndef __JUCE_RESULT_JUCEHEADER__

#endif
#ifndef __JUCE_UUID_JUCEHEADER__

/*** Start of inlined file: juce_Uuid.h ***/
#ifndef __JUCE_UUID_JUCEHEADER__
#define __JUCE_UUID_JUCEHEADER__

/**
	A universally unique 128-bit identifier.

	This class generates very random unique numbers based on the system time
	and MAC addresses if any are available. It's extremely unlikely that two identical
	UUIDs would ever be created by chance.

	The class includes methods for saving the ID as a string or as raw binary data.
*/
class JUCE_API  Uuid
{
public:

	/** Creates a new unique ID. */
	Uuid();

	/** Destructor. */
	~Uuid() noexcept;

	/** Creates a copy of another UUID. */
	Uuid (const Uuid& other);

	/** Copies another UUID. */
	Uuid& operator= (const Uuid& other);

	/** Returns true if the ID is zero. */
	bool isNull() const noexcept;

	/** Compares two UUIDs. */
	bool operator== (const Uuid& other) const;

	/** Compares two UUIDs. */
	bool operator!= (const Uuid& other) const;

	/** Returns a stringified version of this UUID.

		A Uuid object can later be reconstructed from this string using operator= or
		the constructor that takes a string parameter.

		@returns a 32 character hex string.
	*/
	String toString() const;

	/** Creates an ID from an encoded string version.

		@see toString
	*/
	Uuid (const String& uuidString);

	/** Copies from a stringified UUID.

		The string passed in should be one that was created with the toString() method.
	*/
	Uuid& operator= (const String& uuidString);

	/** Returns a pointer to the internal binary representation of the ID.

		This is an array of 16 bytes. To reconstruct a Uuid from its data, use
		the constructor or operator= method that takes an array of uint8s.
	*/
	const uint8* getRawData() const noexcept                { return value.asBytes; }

	/** Creates a UUID from a 16-byte array.

		@see getRawData
	*/
	Uuid (const uint8* rawData);

	/** Sets this UUID from 16-bytes of raw data. */
	Uuid& operator= (const uint8* rawData);

private:

   #ifndef DOXYGEN
	union
	{
		uint8 asBytes [16];
		int asInt[4];
		int64 asInt64[2];

	} value;
   #endif

	JUCE_LEAK_DETECTOR (Uuid);
};

#endif   // __JUCE_UUID_JUCEHEADER__

/*** End of inlined file: juce_Uuid.h ***/


#endif
#ifndef __JUCE_WINDOWSREGISTRY_JUCEHEADER__

/*** Start of inlined file: juce_WindowsRegistry.h ***/
#ifndef __JUCE_WINDOWSREGISTRY_JUCEHEADER__
#define __JUCE_WINDOWSREGISTRY_JUCEHEADER__

#if JUCE_WINDOWS || DOXYGEN

/**
	Contains some static helper functions for manipulating the MS Windows registry
	(Only available on Windows, of course!)
*/
class WindowsRegistry
{
public:

	/** Returns a string from the registry.

		The path is a string for the entire path of a value in the registry,
		e.g. "HKEY_CURRENT_USER\Software\foo\bar"
	*/
	static String getValue (const String& regValuePath,
							const String& defaultValue = String::empty);

	/** Sets a registry value as a string.

		This will take care of creating any groups needed to get to the given
		registry value.
	*/
	static void setValue (const String& regValuePath,
						  const String& value);

	/** Returns true if the given value exists in the registry. */
	static bool valueExists (const String& regValuePath);

	/** Deletes a registry value. */
	static void deleteValue (const String& regValuePath);

	/** Deletes a registry key (which is registry-talk for 'folder'). */
	static void deleteKey (const String& regKeyPath);

	/** Creates a file association in the registry.

		This lets you set the executable that should be launched by a given file extension.
		@param fileExtension        the file extension to associate, including the
									initial dot, e.g. ".txt"
		@param symbolicDescription  a space-free short token to identify the file type
		@param fullDescription      a human-readable description of the file type
		@param targetExecutable     the executable that should be launched
		@param iconResourceNumber   the icon that gets displayed for the file type will be
									found by looking up this resource number in the
									executable. Pass 0 here to not use an icon
	*/
	static void registerFileAssociation (const String& fileExtension,
										 const String& symbolicDescription,
										 const String& fullDescription,
										 const File& targetExecutable,
										 int iconResourceNumber);

private:
	WindowsRegistry();
	JUCE_DECLARE_NON_COPYABLE (WindowsRegistry);
};

#endif
#endif   // __JUCE_WINDOWSREGISTRY_JUCEHEADER__

/*** End of inlined file: juce_WindowsRegistry.h ***/


#endif
#ifndef __JUCE_MACADDRESS_JUCEHEADER__

/*** Start of inlined file: juce_MACAddress.h ***/
#ifndef __JUCE_MACADDRESS_JUCEHEADER__
#define __JUCE_MACADDRESS_JUCEHEADER__

/**
	A wrapper for a streaming (TCP) socket.

	This allows low-level use of sockets; for an easier-to-use messaging layer on top of
	sockets, you could also try the InterprocessConnection class.

	@see DatagramSocket, InterprocessConnection, InterprocessConnectionServer
*/
class JUCE_API  MACAddress
{
public:

	/** Populates a list of the MAC addresses of all the available network cards. */
	static void findAllAddresses (Array<MACAddress>& results);

	/** Creates a null address (00-00-00-00-00-00). */
	MACAddress();

	/** Creates a copy of another address. */
	MACAddress (const MACAddress& other);

	/** Creates a copy of another address. */
	MACAddress& operator= (const MACAddress& other);

	/** Creates an address from 6 bytes. */
	explicit MACAddress (const uint8 bytes[6]);

	/** Returns a pointer to the 6 bytes that make up this address. */
	const uint8* getBytes() const noexcept        { return asBytes; }

	/** Returns a dash-separated string in the form "11-22-33-44-55-66" */
	String toString() const;

	/** Returns the address in the lower 6 bytes of an int64.

		This uses a little-endian arrangement, with the first byte of the address being
		stored in the least-significant byte of the result value.
	*/
	int64 toInt64() const noexcept;

	/** Returns true if this address is null (00-00-00-00-00-00). */
	bool isNull() const noexcept;

	bool operator== (const MACAddress& other) const noexcept;
	bool operator!= (const MACAddress& other) const noexcept;

private:
   #ifndef DOXYGEN
	union
	{
		uint64 asInt64;
		uint8 asBytes[6];
	};
   #endif
};

#endif   // __JUCE_MACADDRESS_JUCEHEADER__

/*** End of inlined file: juce_MACAddress.h ***/


#endif
#ifndef __JUCE_NAMEDPIPE_JUCEHEADER__

/*** Start of inlined file: juce_NamedPipe.h ***/
#ifndef __JUCE_NAMEDPIPE_JUCEHEADER__
#define __JUCE_NAMEDPIPE_JUCEHEADER__

/**
	A cross-process pipe that can have data written to and read from it.

	Two or more processes can use these for inter-process communication.

	@see InterprocessConnection
*/
class JUCE_API  NamedPipe
{
public:

	/** Creates a NamedPipe. */
	NamedPipe();

	/** Destructor. */
	~NamedPipe();

	/** Tries to open a pipe that already exists.

		Returns true if it succeeds.
	*/
	bool openExisting (const String& pipeName);

	/** Tries to create a new pipe.

		Returns true if it succeeds.
	*/
	bool createNewPipe (const String& pipeName);

	/** Closes the pipe, if it's open. */
	void close();

	/** True if the pipe is currently open. */
	bool isOpen() const;

	/** Returns the last name that was used to try to open this pipe. */
	String getName() const;

	/** Reads data from the pipe.

		This will block until another thread has written enough data into the pipe to fill
		the number of bytes specified, or until another thread calls the cancelPendingReads()
		method.

		If the operation fails, it returns -1, otherwise, it will return the number of
		bytes read.

		If timeOutMilliseconds is less than zero, it will wait indefinitely, otherwise
		this is a maximum timeout for reading from the pipe.
	*/
	int read (void* destBuffer, int maxBytesToRead, int timeOutMilliseconds = 5000);

	/** Writes some data to the pipe.

		If the operation fails, it returns -1, otherwise, it will return the number of
		bytes written.
	*/
	int write (const void* sourceBuffer, int numBytesToWrite,
			   int timeOutMilliseconds = 2000);

	/** If any threads are currently blocked on a read operation, this tells them to abort.
	*/
	void cancelPendingReads();

private:

	class Pimpl;
	ScopedPointer<Pimpl> pimpl;
	String currentPipeName;
	CriticalSection lock;

	bool openInternal (const String& pipeName, const bool createPipe);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NamedPipe);
};

#endif   // __JUCE_NAMEDPIPE_JUCEHEADER__

/*** End of inlined file: juce_NamedPipe.h ***/


#endif
#ifndef __JUCE_SOCKET_JUCEHEADER__

/*** Start of inlined file: juce_Socket.h ***/
#ifndef __JUCE_SOCKET_JUCEHEADER__
#define __JUCE_SOCKET_JUCEHEADER__

/**
	A wrapper for a streaming (TCP) socket.

	This allows low-level use of sockets; for an easier-to-use messaging layer on top of
	sockets, you could also try the InterprocessConnection class.

	@see DatagramSocket, InterprocessConnection, InterprocessConnectionServer
*/
class JUCE_API  StreamingSocket
{
public:

	/** Creates an uninitialised socket.

		To connect it, use the connect() method, after which you can read() or write()
		to it.

		To wait for other sockets to connect to this one, the createListener() method
		enters "listener" mode, and can be used to spawn new sockets for each connection
		that comes along.
	*/
	StreamingSocket();

	/** Destructor. */
	~StreamingSocket();

	/** Binds the socket to the specified local port.

		@returns    true on success; false may indicate that another socket is already bound
					on the same port
	*/
	bool bindToPort (int localPortNumber);

	/** Tries to connect the socket to hostname:port.

		If timeOutMillisecs is 0, then this method will block until the operating system
		rejects the connection (which could take a long time).

		@returns true if it succeeds.
		@see isConnected
	*/
	bool connect (const String& remoteHostname,
				  int remotePortNumber,
				  int timeOutMillisecs = 3000);

	/** True if the socket is currently connected. */
	bool isConnected() const noexcept                           { return connected; }

	/** Closes the connection. */
	void close();

	/** Returns the name of the currently connected host. */
	const String& getHostName() const noexcept                  { return hostName; }

	/** Returns the port number that's currently open. */
	int getPort() const noexcept                                { return portNumber; }

	/** True if the socket is connected to this machine rather than over the network. */
	bool isLocal() const noexcept;

	/** Waits until the socket is ready for reading or writing.

		If readyForReading is true, it will wait until the socket is ready for
		reading; if false, it will wait until it's ready for writing.

		If the timeout is < 0, it will wait forever, or else will give up after
		the specified time.

		If the socket is ready on return, this returns 1. If it times-out before
		the socket becomes ready, it returns 0. If an error occurs, it returns -1.
	*/
	int waitUntilReady (bool readyForReading,
						int timeoutMsecs) const;

	/** Reads bytes from the socket.

		If blockUntilSpecifiedAmountHasArrived is true, the method will block until
		maxBytesToRead bytes have been read, (or until an error occurs). If this
		flag is false, the method will return as much data as is currently available
		without blocking.

		@returns the number of bytes read, or -1 if there was an error.
		@see waitUntilReady
	*/
	int read (void* destBuffer, int maxBytesToRead,
			  bool blockUntilSpecifiedAmountHasArrived);

	/** Writes bytes to the socket from a buffer.

		Note that this method will block unless you have checked the socket is ready
		for writing before calling it (see the waitUntilReady() method).

		@returns the number of bytes written, or -1 if there was an error.
	*/
	int write (const void* sourceBuffer, int numBytesToWrite);

	/** Puts this socket into "listener" mode.

		When in this mode, your thread can call waitForNextConnection() repeatedly,
		which will spawn new sockets for each new connection, so that these can
		be handled in parallel by other threads.

		@param portNumber       the port number to listen on
		@param localHostName    the interface address to listen on - pass an empty
								string to listen on all addresses
		@returns    true if it manages to open the socket successfully.

		@see waitForNextConnection
	*/
	bool createListener (int portNumber, const String& localHostName = String::empty);

	/** When in "listener" mode, this waits for a connection and spawns it as a new
		socket.

		The object that gets returned will be owned by the caller.

		This method can only be called after using createListener().

		@see createListener
	*/
	StreamingSocket* waitForNextConnection() const;

private:

	String hostName;
	int volatile portNumber, handle;
	bool connected, isListener;

	StreamingSocket (const String& hostname, int portNumber, int handle);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StreamingSocket);
};

/**
	A wrapper for a datagram (UDP) socket.

	This allows low-level use of sockets; for an easier-to-use messaging layer on top of
	sockets, you could also try the InterprocessConnection class.

	@see StreamingSocket, InterprocessConnection, InterprocessConnectionServer
*/
class JUCE_API  DatagramSocket
{
public:

	/**
		Creates an (uninitialised) datagram socket.

		The localPortNumber is the port on which to bind this socket. If this value is 0,
		the port number is assigned by the operating system.

		To use the socket for sending, call the connect() method. This will not immediately
		make a connection, but will save the destination you've provided. After this, you can
		call read() or write().

		If enableBroadcasting is true, the socket will be allowed to send broadcast messages
		(may require extra privileges on linux)

		To wait for other sockets to connect to this one, call waitForNextConnection().
	*/
	DatagramSocket (int localPortNumber,
					bool enableBroadcasting = false);

	/** Destructor. */
	~DatagramSocket();

	/** Binds the socket to the specified local port.

		@returns    true on success; false may indicate that another socket is already bound
					on the same port
	*/
	bool bindToPort (int localPortNumber);

	/** Tries to connect the socket to hostname:port.

		If timeOutMillisecs is 0, then this method will block until the operating system
		rejects the connection (which could take a long time).

		@returns true if it succeeds.
		@see isConnected
	*/
	bool connect (const String& remoteHostname,
				  int remotePortNumber,
				  int timeOutMillisecs = 3000);

	/** True if the socket is currently connected. */
	bool isConnected() const noexcept                           { return connected; }

	/** Closes the connection. */
	void close();

	/** Returns the name of the currently connected host. */
	const String& getHostName() const noexcept                  { return hostName; }

	/** Returns the port number that's currently open. */
	int getPort() const noexcept                                { return portNumber; }

	/** True if the socket is connected to this machine rather than over the network. */
	bool isLocal() const noexcept;

	/** Waits until the socket is ready for reading or writing.

		If readyForReading is true, it will wait until the socket is ready for
		reading; if false, it will wait until it's ready for writing.

		If the timeout is < 0, it will wait forever, or else will give up after
		the specified time.

		If the socket is ready on return, this returns 1. If it times-out before
		the socket becomes ready, it returns 0. If an error occurs, it returns -1.
	*/
	int waitUntilReady (bool readyForReading,
						int timeoutMsecs) const;

	/** Reads bytes from the socket.

		If blockUntilSpecifiedAmountHasArrived is true, the method will block until
		maxBytesToRead bytes have been read, (or until an error occurs). If this
		flag is false, the method will return as much data as is currently available
		without blocking.

		@returns the number of bytes read, or -1 if there was an error.
		@see waitUntilReady
	*/
	int read (void* destBuffer, int maxBytesToRead,
			  bool blockUntilSpecifiedAmountHasArrived);

	/** Writes bytes to the socket from a buffer.

		Note that this method will block unless you have checked the socket is ready
		for writing before calling it (see the waitUntilReady() method).

		@returns the number of bytes written, or -1 if there was an error.
	*/
	int write (const void* sourceBuffer, int numBytesToWrite);

	/** This waits for incoming data to be sent, and returns a socket that can be used
		to read it.

		The object that gets returned is owned by the caller, and can't be used for
		sending, but can be used to read the data.
	*/
	DatagramSocket* waitForNextConnection() const;

private:

	String hostName;
	int volatile portNumber, handle;
	bool connected, allowBroadcast;
	void* serverAddress;

	DatagramSocket (const String& hostname, int portNumber, int handle, int localPortNumber);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DatagramSocket);
};

#endif   // __JUCE_SOCKET_JUCEHEADER__

/*** End of inlined file: juce_Socket.h ***/


#endif
#ifndef __JUCE_URL_JUCEHEADER__

/*** Start of inlined file: juce_URL.h ***/
#ifndef __JUCE_URL_JUCEHEADER__
#define __JUCE_URL_JUCEHEADER__

class InputStream;
class XmlElement;

/**
	Represents a URL and has a bunch of useful functions to manipulate it.

	This class can be used to launch URLs in browsers, and also to create
	InputStreams that can read from remote http or ftp sources.
*/
class JUCE_API  URL
{
public:

	/** Creates an empty URL. */
	URL();

	/** Creates a URL from a string. */
	URL (const String& url);

	/** Creates a copy of another URL. */
	URL (const URL& other);

	/** Destructor. */
	~URL();

	/** Copies this URL from another one. */
	URL& operator= (const URL& other);

	/** Compares two URLs.
		All aspects of the URLs must be identical for them to match, including any parameters,
		upload files, etc.
	*/
	bool operator== (const URL&) const;
	bool operator!= (const URL&) const;

	/** Returns a string version of the URL.

		If includeGetParameters is true and any parameters have been set with the
		withParameter() method, then the string will have these appended on the
		end and url-encoded.
	*/
	String toString (bool includeGetParameters) const;

	/** True if it seems to be valid. */
	bool isWellFormed() const;

	/** Returns just the domain part of the URL.

		E.g. for "http://www.xyz.com/foobar", this will return "www.xyz.com".
	*/
	String getDomain() const;

	/** Returns the path part of the URL.

		E.g. for "http://www.xyz.com/foo/bar?x=1", this will return "foo/bar".
	*/
	String getSubPath() const;

	/** Returns the scheme of the URL.

		E.g. for "http://www.xyz.com/foobar", this will return "http". (It won't
		include the colon).
	*/
	String getScheme() const;

	/** Attempts to read a port number from the URL.
		@returns the port number, or 0 if none is explicitly specified.
	*/
	int getPort() const;

	/** Returns a new version of this URL that uses a different sub-path.

		E.g. if the URL is "http://www.xyz.com/foo?x=1" and you call this with
		"bar", it'll return "http://www.xyz.com/bar?x=1".
	*/
	URL withNewSubPath (const String& newPath) const;

	/** Returns a new URL that refers to a sub-path relative to this one.

		E.g. if the URL is "http://www.xyz.com/foo" and you call this with
		"bar", it'll return "http://www.xyz.com/foo/bar". Note that there's no way for
		this method to know whether the original URL is a file or directory, so it's
		up to you to make sure it's a directory. It also won't attempt to be smart about
		the content of the childPath string, so if this string is an absolute URL, it'll
		still just get bolted onto the end of the path.

		@see File::getChildFile
	*/
	URL getChildURL (const String& subPath) const;

	/** Returns a copy of this URL, with a GET or POST parameter added to the end.

		Any control characters in the value will be encoded.

		e.g. calling "withParameter ("amount", "some fish") for the url "www.fish.com"
		would produce a new url whose toString(true) method would return
		"www.fish.com?amount=some+fish".

		@see getParameterNames, getParameterValues
	*/
	URL withParameter (const String& parameterName,
					   const String& parameterValue) const;

	/** Returns a copy of this URl, with a file-upload type parameter added to it.

		When performing a POST where one of your parameters is a binary file, this
		lets you specify the file.

		Note that the filename is stored, but the file itself won't actually be read
		until this URL is later used to create a network input stream.
	*/
	URL withFileToUpload (const String& parameterName,
						  const File& fileToUpload,
						  const String& mimeType) const;

	/** Returns an array of the names of all the URL's parameters.

		E.g. for the url "www.fish.com?type=haddock&amount=some+fish", this array would
		contain two items: "type" and "haddock".

		You can call getParameterValues() to get the corresponding value of each
		parameter. Note that the list can contain multiple parameters with the same name.

		@see getParameterValues, withParameter
	*/
	const StringArray& getParameterNames() const noexcept       { return parameterNames; }

	/** Returns an array of the values of all the URL's parameters.

		E.g. for the url "www.fish.com?type=haddock&amount=some+fish", this array would
		contain two items: "haddock" and "some fish".

		The values returned will have been cleaned up to remove any escape characters.

		You can call getParameterNames() to get the corresponding name of each
		parameter. Note that the list can contain multiple parameters with the same name.

		@see getParameterNames, withParameter
	*/
	const StringArray& getParameterValues() const noexcept      { return parameterValues; }

	/** Returns the set of files that should be uploaded as part of a POST operation.

		This is the set of files that were added to the URL with the withFileToUpload()
		method.
	*/
	const StringPairArray& getFilesToUpload() const;

	/** Returns the set of mime types associated with each of the upload files.
	*/
	const StringPairArray& getMimeTypesOfUploadFiles() const;

	/** Returns a copy of this URL, with a block of data to send as the POST data.

		If you're setting the POST data, be careful not to have any parameters set
		as well, otherwise it'll all get thrown in together, and might not have the
		desired effect.

		If the URL already contains some POST data, this will replace it, rather
		than being appended to it.

		This data will only be used if you specify a post operation when you call
		createInputStream().
	*/
	URL withPOSTData (const String& postData) const;

	/** Returns the data that was set using withPOSTData(). */
	const String& getPostData() const noexcept                  { return postData; }

	/** Tries to launch the system's default browser to open the URL.

		Returns true if this seems to have worked.
	*/
	bool launchInDefaultBrowser() const;

	/** Takes a guess as to whether a string might be a valid website address.

		This isn't foolproof!
	*/
	static bool isProbablyAWebsiteURL (const String& possibleURL);

	/** Takes a guess as to whether a string might be a valid email address.

		This isn't foolproof!
	*/
	static bool isProbablyAnEmailAddress (const String& possibleEmailAddress);

	/** This callback function can be used by the createInputStream() method.

		It allows your app to receive progress updates during a lengthy POST operation. If you
		want to continue the operation, this should return true, or false to abort.
	*/
	typedef bool (OpenStreamProgressCallback) (void* context, int bytesSent, int totalBytes);

	/** Attempts to open a stream that can read from this URL.

		@param usePostCommand   if true, it will try to do use a http 'POST' to pass
								the paramters, otherwise it'll encode them into the
								URL and do a 'GET'.
		@param progressCallback if this is non-zero, it lets you supply a callback function
								to keep track of the operation's progress. This can be useful
								for lengthy POST operations, so that you can provide user feedback.
		@param progressCallbackContext  if a callback is specified, this value will be passed to
								the function
		@param extraHeaders     if not empty, this string is appended onto the headers that
								are used for the request. It must therefore be a valid set of HTML
								header directives, separated by newlines.
		@param connectionTimeOutMs  if 0, this will use whatever default setting the OS chooses. If
								a negative number, it will be infinite. Otherwise it specifies a
								time in milliseconds.
		@param responseHeaders  if this is non-zero, all the (key, value) pairs received as headers
								in the response will be stored in this array
		@returns    an input stream that the caller must delete, or a null pointer if there was an
					error trying to open it.
	 */
	InputStream* createInputStream (bool usePostCommand,
									OpenStreamProgressCallback* progressCallback = nullptr,
									void* progressCallbackContext = nullptr,
									const String& extraHeaders = String::empty,
									int connectionTimeOutMs = 0,
									StringPairArray* responseHeaders = nullptr) const;

	/** Tries to download the entire contents of this URL into a binary data block.

		If it succeeds, this will return true and append the data it read onto the end
		of the memory block.

		@param destData         the memory block to append the new data to
		@param usePostCommand   whether to use a POST command to get the data (uses
								a GET command if this is false)
		@see readEntireTextStream, readEntireXmlStream
	*/
	bool readEntireBinaryStream (MemoryBlock& destData,
								 bool usePostCommand = false) const;

	/** Tries to download the entire contents of this URL as a string.

		If it fails, this will return an empty string, otherwise it will return the
		contents of the downloaded file. If you need to distinguish between a read
		operation that fails and one that returns an empty string, you'll need to use
		a different method, such as readEntireBinaryStream().

		@param usePostCommand   whether to use a POST command to get the data (uses
								a GET command if this is false)
		@see readEntireBinaryStream, readEntireXmlStream
	*/
	String readEntireTextStream (bool usePostCommand = false) const;

	/** Tries to download the entire contents of this URL and parse it as XML.

		If it fails, or if the text that it reads can't be parsed as XML, this will
		return 0.

		When it returns a valid XmlElement object, the caller is responsibile for deleting
		this object when no longer needed.

		@param usePostCommand   whether to use a POST command to get the data (uses
								a GET command if this is false)

		@see readEntireBinaryStream, readEntireTextStream
	*/
	XmlElement* readEntireXmlStream (bool usePostCommand = false) const;

	/** Adds escape sequences to a string to encode any characters that aren't
		legal in a URL.

		E.g. any spaces will be replaced with "%20".

		This is the opposite of removeEscapeChars().

		If isParameter is true, it means that the string is going to be used
		as a parameter, so it also encodes '$' and ',' (which would otherwise
		be legal in a URL.

		@see removeEscapeChars
	*/
	static String addEscapeChars (const String& stringToAddEscapeCharsTo,
								  bool isParameter);

	/** Replaces any escape character sequences in a string with their original
		character codes.

		E.g. any instances of "%20" will be replaced by a space.

		This is the opposite of addEscapeChars().

		@see addEscapeChars
	*/
	static String removeEscapeChars (const String& stringToRemoveEscapeCharsFrom);

private:

	String url, postData;
	StringArray parameterNames, parameterValues;
	StringPairArray filesToUpload, mimeTypes;

	void addParameter (const String&, const String&);

	static InputStream* createNativeStream (const String& address, bool isPost, const MemoryBlock& postData,
											OpenStreamProgressCallback* progressCallback,
											void* progressCallbackContext, const String& headers,
											const int timeOutMs, StringPairArray* responseHeaders);
	JUCE_LEAK_DETECTOR (URL);
};

#endif   // __JUCE_URL_JUCEHEADER__

/*** End of inlined file: juce_URL.h ***/


#endif
#ifndef __JUCE_BUFFEREDINPUTSTREAM_JUCEHEADER__

/*** Start of inlined file: juce_BufferedInputStream.h ***/
#ifndef __JUCE_BUFFEREDINPUTSTREAM_JUCEHEADER__
#define __JUCE_BUFFEREDINPUTSTREAM_JUCEHEADER__

/** Wraps another input stream, and reads from it using an intermediate buffer

	If you're using an input stream such as a file input stream, and making lots of
	small read accesses to it, it's probably sensible to wrap it in one of these,
	so that the source stream gets accessed in larger chunk sizes, meaning less
	work for the underlying stream.
*/
class JUCE_API  BufferedInputStream  : public InputStream
{
public:

	/** Creates a BufferedInputStream from an input source.

		@param sourceStream                 the source stream to read from
		@param bufferSize                   the size of reservoir to use to buffer the source
		@param deleteSourceWhenDestroyed    whether the sourceStream that is passed in should be
											deleted by this object when it is itself deleted.
	*/
	BufferedInputStream (InputStream* sourceStream,
						 int bufferSize,
						 bool deleteSourceWhenDestroyed);

	/** Creates a BufferedInputStream from an input source.

		@param sourceStream     the source stream to read from - the source stream  must not
								be deleted until this object has been destroyed.
		@param bufferSize       the size of reservoir to use to buffer the source
	*/
	BufferedInputStream (InputStream& sourceStream, int bufferSize);

	/** Destructor.

		This may also delete the source stream, if that option was chosen when the
		buffered stream was created.
	*/
	~BufferedInputStream();

	int64 getTotalLength();
	int64 getPosition();
	bool setPosition (int64 newPosition);
	int read (void* destBuffer, int maxBytesToRead);
	String readString();
	bool isExhausted();

private:

	OptionalScopedPointer<InputStream> source;
	int bufferSize;
	int64 position, lastReadPos, bufferStart, bufferOverlap;
	HeapBlock <char> buffer;
	void ensureBuffered();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BufferedInputStream);
};

#endif   // __JUCE_BUFFEREDINPUTSTREAM_JUCEHEADER__

/*** End of inlined file: juce_BufferedInputStream.h ***/


#endif
#ifndef __JUCE_FILEINPUTSOURCE_JUCEHEADER__

/*** Start of inlined file: juce_FileInputSource.h ***/
#ifndef __JUCE_FILEINPUTSOURCE_JUCEHEADER__
#define __JUCE_FILEINPUTSOURCE_JUCEHEADER__


/*** Start of inlined file: juce_InputSource.h ***/
#ifndef __JUCE_INPUTSOURCE_JUCEHEADER__
#define __JUCE_INPUTSOURCE_JUCEHEADER__

/**
	A lightweight object that can create a stream to read some kind of resource.

	This may be used to refer to a file, or some other kind of source, allowing a
	caller to create an input stream that can read from it when required.

	@see FileInputSource
*/
class JUCE_API  InputSource
{
public:

	InputSource() noexcept      {}

	/** Destructor. */
	virtual ~InputSource()      {}

	/** Returns a new InputStream to read this item.

		@returns            an inputstream that the caller will delete, or 0 if
							the filename isn't found.
	*/
	virtual InputStream* createInputStream() = 0;

	/** Returns a new InputStream to read an item, relative.

		@param relatedItemPath  the relative pathname of the resource that is required
		@returns            an inputstream that the caller will delete, or 0 if
							the item isn't found.
	*/
	virtual InputStream* createInputStreamFor (const String& relatedItemPath) = 0;

	/** Returns a hash code that uniquely represents this item.
	*/
	virtual int64 hashCode() const = 0;

private:

	JUCE_LEAK_DETECTOR (InputSource);
};

#endif   // __JUCE_INPUTSOURCE_JUCEHEADER__

/*** End of inlined file: juce_InputSource.h ***/

/**
	A type of InputSource that represents a normal file.

	@see InputSource
*/
class JUCE_API  FileInputSource     : public InputSource
{
public:

	FileInputSource (const File& file, bool useFileTimeInHashGeneration = false);
	~FileInputSource();

	InputStream* createInputStream();
	InputStream* createInputStreamFor (const String& relatedItemPath);
	int64 hashCode() const;

private:

	const File file;
	bool useFileTimeInHashGeneration;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FileInputSource);
};

#endif   // __JUCE_FILEINPUTSOURCE_JUCEHEADER__

/*** End of inlined file: juce_FileInputSource.h ***/


#endif
#ifndef __JUCE_INPUTSOURCE_JUCEHEADER__

#endif
#ifndef __JUCE_INPUTSTREAM_JUCEHEADER__

#endif
#ifndef __JUCE_MEMORYINPUTSTREAM_JUCEHEADER__

/*** Start of inlined file: juce_MemoryInputStream.h ***/
#ifndef __JUCE_MEMORYINPUTSTREAM_JUCEHEADER__
#define __JUCE_MEMORYINPUTSTREAM_JUCEHEADER__

/**
	Allows a block of data and to be accessed as a stream.

	This can either be used to refer to a shared block of memory, or can make its
	own internal copy of the data when the MemoryInputStream is created.
*/
class JUCE_API  MemoryInputStream  : public InputStream
{
public:

	/** Creates a MemoryInputStream.

		@param sourceData               the block of data to use as the stream's source
		@param sourceDataSize           the number of bytes in the source data block
		@param keepInternalCopyOfData   if false, the stream will just keep a pointer to
										the source data, so this data shouldn't be changed
										for the lifetime of the stream; if this parameter is
										true, the stream will make its own copy of the
										data and use that.
	*/
	MemoryInputStream (const void* sourceData,
					   size_t sourceDataSize,
					   bool keepInternalCopyOfData);

	/** Creates a MemoryInputStream.

		@param data                     a block of data to use as the stream's source
		@param keepInternalCopyOfData   if false, the stream will just keep a reference to
										the source data, so this data shouldn't be changed
										for the lifetime of the stream; if this parameter is
										true, the stream will make its own copy of the
										data and use that.
	*/
	MemoryInputStream (const MemoryBlock& data,
					   bool keepInternalCopyOfData);

	/** Destructor. */
	~MemoryInputStream();

	int64 getPosition();
	bool setPosition (int64 pos);
	int64 getTotalLength();
	bool isExhausted();
	int read (void* destBuffer, int maxBytesToRead);

private:

	const char* data;
	size_t dataSize, position;
	HeapBlock<char> internalCopy;

	void createInternalCopy();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MemoryInputStream);
};

#endif   // __JUCE_MEMORYINPUTSTREAM_JUCEHEADER__

/*** End of inlined file: juce_MemoryInputStream.h ***/


#endif
#ifndef __JUCE_MEMORYOUTPUTSTREAM_JUCEHEADER__

/*** Start of inlined file: juce_MemoryOutputStream.h ***/
#ifndef __JUCE_MEMORYOUTPUTSTREAM_JUCEHEADER__
#define __JUCE_MEMORYOUTPUTSTREAM_JUCEHEADER__

/**
	Writes data to an internal memory buffer, which grows as required.

	The data that was written into the stream can then be accessed later as
	a contiguous block of memory.
*/
class JUCE_API  MemoryOutputStream  : public OutputStream
{
public:

	/** Creates an empty memory stream ready for writing into.

		@param initialSize  the intial amount of capacity to allocate for writing into
	*/
	MemoryOutputStream (size_t initialSize = 256);

	/** Creates a memory stream for writing into into a pre-existing MemoryBlock object.

		Note that the destination block will always be larger than the amount of data
		that has been written to the stream, because the MemoryOutputStream keeps some
		spare capactity at its end. To trim the block's size down to fit the actual
		data, call flush(), or delete the MemoryOutputStream.

		@param memoryBlockToWriteTo             the block into which new data will be written.
		@param appendToExistingBlockContent     if this is true, the contents of the block will be
												kept, and new data will be appended to it. If false,
												the block will be cleared before use
	*/
	MemoryOutputStream (MemoryBlock& memoryBlockToWriteTo,
						bool appendToExistingBlockContent);

	/** Destructor.
		This will free any data that was written to it.
	*/
	~MemoryOutputStream();

	/** Returns a pointer to the data that has been written to the stream.

		@see getDataSize
	*/
	const void* getData() const noexcept;

	/** Returns the number of bytes of data that have been written to the stream.

		@see getData
	*/
	size_t getDataSize() const noexcept                 { return size; }

	/** Resets the stream, clearing any data that has been written to it so far. */
	void reset() noexcept;

	/** Increases the internal storage capacity to be able to contain at least the specified
		amount of data without needing to be resized.
	*/
	void preallocate (size_t bytesToPreallocate);

	/** Returns a String created from the (UTF8) data that has been written to the stream. */
	String toUTF8() const;

	/** Attempts to detect the encoding of the data and convert it to a string.
		@see String::createStringFromData
	*/
	String toString() const;

	/** Returns a copy of the stream's data as a memory block. */
	MemoryBlock getMemoryBlock() const;

	/** If the stream is writing to a user-supplied MemoryBlock, this will trim any excess
		capacity off the block, so that its length matches the amount of actual data that
		has been written so far.
	*/
	void flush();

	bool write (const void* buffer, int howMany);
	int64 getPosition()                                 { return position; }
	bool setPosition (int64 newPosition);
	int writeFromInputStream (InputStream& source, int64 maxNumBytesToWrite);
	void writeRepeatedByte (uint8 byte, int numTimesToRepeat);

private:

	MemoryBlock& data;
	MemoryBlock internalBlock;
	size_t position, size;

	void trimExternalBlockSize();
	void prepareToWrite (int numBytes);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MemoryOutputStream);
};

/** Copies all the data that has been written to a MemoryOutputStream into another stream. */
OutputStream& JUCE_CALLTYPE operator<< (OutputStream& stream, const MemoryOutputStream& streamToRead);

#endif   // __JUCE_MEMORYOUTPUTSTREAM_JUCEHEADER__

/*** End of inlined file: juce_MemoryOutputStream.h ***/


#endif
#ifndef __JUCE_OUTPUTSTREAM_JUCEHEADER__

#endif
#ifndef __JUCE_SUBREGIONSTREAM_JUCEHEADER__

/*** Start of inlined file: juce_SubregionStream.h ***/
#ifndef __JUCE_SUBREGIONSTREAM_JUCEHEADER__
#define __JUCE_SUBREGIONSTREAM_JUCEHEADER__

/** Wraps another input stream, and reads from a specific part of it.

	This lets you take a subsection of a stream and present it as an entire
	stream in its own right.
*/
class JUCE_API  SubregionStream  : public InputStream
{
public:

	/** Creates a SubregionStream from an input source.

		@param sourceStream                 the source stream to read from
		@param startPositionInSourceStream  this is the position in the source stream that
											corresponds to position 0 in this stream
		@param lengthOfSourceStream         this specifies the maximum number of bytes
											from the source stream that will be passed through
											by this stream. When the position of this stream
											exceeds lengthOfSourceStream, it will cause an end-of-stream.
											If the length passed in here is greater than the length
											of the source stream (as returned by getTotalLength()),
											then the smaller value will be used.
											Passing a negative value for this parameter means it
											will keep reading until the source's end-of-stream.
		@param deleteSourceWhenDestroyed    whether the sourceStream that is passed in should be
											deleted by this object when it is itself deleted.
	*/
	SubregionStream (InputStream* sourceStream,
					 int64 startPositionInSourceStream,
					 int64 lengthOfSourceStream,
					 bool deleteSourceWhenDestroyed);

	/** Destructor.

		This may also delete the source stream, if that option was chosen when the
		buffered stream was created.
	*/
	~SubregionStream();

	int64 getTotalLength();
	int64 getPosition();
	bool setPosition (int64 newPosition);
	int read (void* destBuffer, int maxBytesToRead);
	bool isExhausted();

private:
	OptionalScopedPointer<InputStream> source;
	const int64 startPositionInSourceStream, lengthOfSourceStream;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SubregionStream);
};

#endif   // __JUCE_SUBREGIONSTREAM_JUCEHEADER__

/*** End of inlined file: juce_SubregionStream.h ***/


#endif
#ifndef __JUCE_PLATFORMDEFS_JUCEHEADER__

#endif
#ifndef __JUCE_STANDARDHEADER_JUCEHEADER__

#endif
#ifndef __JUCE_SYSTEMSTATS_JUCEHEADER__

/*** Start of inlined file: juce_SystemStats.h ***/
#ifndef __JUCE_SYSTEMSTATS_JUCEHEADER__
#define __JUCE_SYSTEMSTATS_JUCEHEADER__

/**
	Contains methods for finding out about the current hardware and OS configuration.
*/
class JUCE_API  SystemStats
{
public:

	/** Returns the current version of JUCE,

		See also the JUCE_VERSION, JUCE_MAJOR_VERSION and JUCE_MINOR_VERSION macros.
	*/
	static String getJUCEVersion();

	/** The set of possible results of the getOperatingSystemType() method.
	*/
	enum OperatingSystemType
	{
		UnknownOS   = 0,

		MacOSX      = 0x1000,
		Linux       = 0x2000,
		Android     = 0x3000,

		Win95       = 0x4001,
		Win98       = 0x4002,
		WinNT351    = 0x4103,
		WinNT40     = 0x4104,
		Win2000     = 0x4105,
		WinXP       = 0x4106,
		WinVista    = 0x4107,
		Windows7    = 0x4108,

		Windows     = 0x4000,   /**< To test whether any version of Windows is running,
									 you can use the expression ((getOperatingSystemType() & Windows) != 0). */
		WindowsNT   = 0x0100,   /**< To test whether the platform is Windows NT or later (i.e. not Win95 or 98),
									 you can use the expression ((getOperatingSystemType() & WindowsNT) != 0). */
	};

	/** Returns the type of operating system we're running on.

		@returns one of the values from the OperatingSystemType enum.
		@see getOperatingSystemName
	*/
	static OperatingSystemType getOperatingSystemType();

	/** Returns the name of the type of operating system we're running on.

		@returns a string describing the OS type.
		@see getOperatingSystemType
	*/
	static String getOperatingSystemName();

	/** Returns true if the OS is 64-bit, or false for a 32-bit OS.
	*/
	static bool isOperatingSystem64Bit();

   #if JUCE_MAC || DOXYGEN
	/** OSX ONLY - Returns the current OS version number.
		E.g. if it's running on 10.4, this will be 4, 10.5 will return 5, etc.
	*/
	static int getOSXMinorVersionNumber();
   #endif

	/** Returns the current user's name, if available.
		@see getFullUserName()
	*/
	static String getLogonName();

	/** Returns the current user's full name, if available.
		On some OSes, this may just return the same value as getLogonName().
		@see getLogonName()
	*/
	static String getFullUserName();

	/** Returns the host-name of the computer. */
	static String getComputerName();

	// CPU and memory information..

	/** Returns the approximate CPU speed.

		@returns    the speed in megahertz, e.g. 1500, 2500, 32000 (depending on
					what year you're reading this...)
	*/
	static int getCpuSpeedInMegaherz();

	/** Returns a string to indicate the CPU vendor.

		Might not be known on some systems.
	*/
	static String getCpuVendor();

	/** Checks whether Intel MMX instructions are available. */
	static bool hasMMX() noexcept               { return getCPUFlags().hasMMX; }

	/** Checks whether Intel SSE instructions are available. */
	static bool hasSSE() noexcept               { return getCPUFlags().hasSSE; }

	/** Checks whether Intel SSE2 instructions are available. */
	static bool hasSSE2() noexcept              { return getCPUFlags().hasSSE2; }

	/** Checks whether AMD 3DNOW instructions are available. */
	static bool has3DNow() noexcept             { return getCPUFlags().has3DNow; }

	/** Returns the number of CPUs. */
	static int getNumCpus() noexcept            { return getCPUFlags().numCpus; }

	/** Finds out how much RAM is in the machine.

		@returns    the approximate number of megabytes of memory, or zero if
					something goes wrong when finding out.
	*/
	static int getMemorySizeInMegabytes();

	/** Returns the system page-size.

		This is only used by programmers with beards.
	*/
	static int getPageSize();

private:

	struct CPUFlags
	{
		CPUFlags();

		int numCpus;
		bool hasMMX : 1;
		bool hasSSE : 1;
		bool hasSSE2 : 1;
		bool has3DNow : 1;
	};

	SystemStats();
	static const CPUFlags& getCPUFlags();

	JUCE_DECLARE_NON_COPYABLE (SystemStats);
};

#endif   // __JUCE_SYSTEMSTATS_JUCEHEADER__

/*** End of inlined file: juce_SystemStats.h ***/


#endif
#ifndef __JUCE_TARGETPLATFORM_JUCEHEADER__

#endif
#ifndef __JUCE_CHARACTERFUNCTIONS_JUCEHEADER__

#endif
#ifndef __JUCE_CHARPOINTER_ASCII_JUCEHEADER__

#endif
#ifndef __JUCE_CHARPOINTER_UTF16_JUCEHEADER__

#endif
#ifndef __JUCE_CHARPOINTER_UTF32_JUCEHEADER__

#endif
#ifndef __JUCE_CHARPOINTER_UTF8_JUCEHEADER__

#endif
#ifndef __JUCE_IDENTIFIER_JUCEHEADER__

#endif
#ifndef __JUCE_LOCALISEDSTRINGS_JUCEHEADER__

/*** Start of inlined file: juce_LocalisedStrings.h ***/
#ifndef __JUCE_LOCALISEDSTRINGS_JUCEHEADER__
#define __JUCE_LOCALISEDSTRINGS_JUCEHEADER__

/**
	Used to convert strings to localised foreign-language versions.

	This is basically a look-up table of strings and their translated equivalents.
	It can be loaded from a text file, so that you can supply a set of localised
	versions of strings that you use in your app.

	To use it in your code, simply call the translate() method on each string that
	might have foreign versions, and if none is found, the method will just return
	the original string.

	The translation file should start with some lines specifying a description of
	the language it contains, and also a list of ISO country codes where it might
	be appropriate to use the file. After that, each line of the file should contain
	a pair of quoted strings with an '=' sign.

	E.g. for a french translation, the file might be:

	@code
	language: French
	countries: fr be mc ch lu

	"hello" = "bonjour"
	"goodbye" = "au revoir"
	@endcode

	If the strings need to contain a quote character, they can use '\"' instead, and
	if the first non-whitespace character on a line isn't a quote, then it's ignored,
	(you can use this to add comments).

	Note that this is a singleton class, so don't create or destroy the object directly.
	There's also a TRANS(text) macro defined to make it easy to use the this.

	E.g. @code
	printSomething (TRANS("hello"));
	@endcode

	This macro is used in the Juce classes themselves, so your application has a chance to
	intercept and translate any internal Juce text strings that might be shown. (You can easily
	get a list of all the messages by searching for the TRANS() macro in the Juce source
	code).
*/
class JUCE_API  LocalisedStrings
{
public:

	/** Creates a set of translations from the text of a translation file.

		When you create one of these, you can call setCurrentMappings() to make it
		the set of mappings that the system's using.
	*/
	LocalisedStrings (const String& fileContents);

	/** Creates a set of translations from a file.

		When you create one of these, you can call setCurrentMappings() to make it
		the set of mappings that the system's using.
	*/
	LocalisedStrings (const File& fileToLoad);

	/** Destructor. */
	~LocalisedStrings();

	/** Selects the current set of mappings to be used by the system.

		The object you pass in will be automatically deleted when no longer needed, so
		don't keep a pointer to it. You can also pass in zero to remove the current
		mappings.

		See also the TRANS() macro, which uses the current set to do its translation.

		@see translateWithCurrentMappings
	*/
	static void setCurrentMappings (LocalisedStrings* newTranslations);

	/** Returns the currently selected set of mappings.

		This is the object that was last passed to setCurrentMappings(). It may
		be 0 if none has been created.
	*/
	static LocalisedStrings* getCurrentMappings();

	/** Tries to translate a string using the currently selected set of mappings.

		If no mapping has been set, or if the mapping doesn't contain a translation
		for the string, this will just return the original string.

		See also the TRANS() macro, which uses this method to do its translation.

		@see setCurrentMappings, getCurrentMappings
	*/
	static String translateWithCurrentMappings (const String& text);

	/** Tries to translate a string using the currently selected set of mappings.

		If no mapping has been set, or if the mapping doesn't contain a translation
		for the string, this will just return the original string.

		See also the TRANS() macro, which uses this method to do its translation.

		@see setCurrentMappings, getCurrentMappings
	*/
	static String translateWithCurrentMappings (const char* text);

	/** Attempts to look up a string and return its localised version.
		If the string isn't found in the list, the original string will be returned.
	*/
	String translate (const String& text) const;

	/** Attempts to look up a string and return its localised version.
		If the string isn't found in the list, the resultIfNotFound string will be returned.
	*/
	String translate (const String& text, const String& resultIfNotFound) const;

	/** Returns the name of the language specified in the translation file.

		This is specified in the file using a line starting with "language:", e.g.
		@code
		language: german
		@endcode
	*/
	String getLanguageName() const                        { return languageName; }

	/** Returns the list of suitable country codes listed in the translation file.

		These is specified in the file using a line starting with "countries:", e.g.
		@code
		countries: fr be mc ch lu
		@endcode

		The country codes are supposed to be 2-character ISO complient codes.
	*/
	const StringArray& getCountryCodes() const            { return countryCodes; }

	/** Indicates whether to use a case-insensitive search when looking up a string.
		This defaults to true.
	*/
	void setIgnoresCase (bool shouldIgnoreCase);

private:

	String languageName;
	StringArray countryCodes;
	StringPairArray translations;

	void loadFromText (const String& fileContents);

	JUCE_LEAK_DETECTOR (LocalisedStrings);
};

#ifndef TRANS
 /** Uses the LocalisedStrings class to translate the given string literal.
	 This macro is provided for backwards-compatibility, and just calls the translate()
	 function. In new code, it's recommended that you just call translate() directly
	 instead, and avoid using macros.
	 @see translate(), LocalisedStrings
 */
 #define TRANS(stringLiteral) juce::translate (stringLiteral)
#endif

/** Uses the LocalisedStrings class to translate the given string literal.
	@see LocalisedStrings
*/
String translate (const String& stringLiteral);

/** Uses the LocalisedStrings class to translate the given string literal.
	@see LocalisedStrings
*/
String translate (const char* stringLiteral);

/** Uses the LocalisedStrings class to translate the given string literal.
	@see LocalisedStrings
*/
String translate (const String& stringLiteral, const String& resultIfNotFound);

#endif   // __JUCE_LOCALISEDSTRINGS_JUCEHEADER__

/*** End of inlined file: juce_LocalisedStrings.h ***/


#endif
#ifndef __JUCE_NEWLINE_JUCEHEADER__

#endif
#ifndef __JUCE_STRING_JUCEHEADER__

#endif
#ifndef __JUCE_STRINGARRAY_JUCEHEADER__

#endif
#ifndef __JUCE_STRINGPAIRARRAY_JUCEHEADER__

#endif
#ifndef __JUCE_STRINGPOOL_JUCEHEADER__

/*** Start of inlined file: juce_StringPool.h ***/
#ifndef __JUCE_STRINGPOOL_JUCEHEADER__
#define __JUCE_STRINGPOOL_JUCEHEADER__

/**
	A StringPool holds a set of shared strings, which reduces storage overheads and improves
	comparison speed when dealing with many duplicate strings.

	When you add a string to a pool using getPooledString, it'll return a character
	array containing the same string. This array is owned by the pool, and the same array
	is returned every time a matching string is asked for. This means that it's trivial to
	compare two pooled strings for equality, as you can simply compare their pointers. It
	also cuts down on storage if you're using many copies of the same string.
*/
class JUCE_API  StringPool
{
public:

	/** Creates an empty pool. */
	StringPool() noexcept;

	/** Destructor */
	~StringPool();

	/** Returns a pointer to a copy of the string that is passed in.

		The pool will always return the same pointer when asked for a string that matches it.
		The pool will own all the pointers that it returns, deleting them when the pool itself
		is deleted.
	*/
	String::CharPointerType getPooledString (const String& original);

	/** Returns a pointer to a copy of the string that is passed in.

		The pool will always return the same pointer when asked for a string that matches it.
		The pool will own all the pointers that it returns, deleting them when the pool itself
		is deleted.
	*/
	String::CharPointerType getPooledString (const char* original);

	/** Returns a pointer to a copy of the string that is passed in.

		The pool will always return the same pointer when asked for a string that matches it.
		The pool will own all the pointers that it returns, deleting them when the pool itself
		is deleted.
	*/
	String::CharPointerType getPooledString (const wchar_t* original);

	/** Returns the number of strings in the pool. */
	int size() const noexcept;

	/** Returns one of the strings in the pool, by index. */
	String::CharPointerType operator[] (int index) const noexcept;

private:
	Array <String> strings;
	CriticalSection lock;
};

#endif   // __JUCE_STRINGPOOL_JUCEHEADER__

/*** End of inlined file: juce_StringPool.h ***/


#endif
#ifndef __JUCE_CHILDPROCESS_JUCEHEADER__

/*** Start of inlined file: juce_ChildProcess.h ***/
#ifndef __JUCE_CHILDPROCESS_JUCEHEADER__
#define __JUCE_CHILDPROCESS_JUCEHEADER__

/**
	Launches and monitors a child process.

	This class lets you launch an executable, and read its output. You can also
	use it to check whether the child process has finished.
*/
class JUCE_API  ChildProcess
{
public:

	/** Creates a process object.
		To actually launch the process, use start().
	*/
	ChildProcess();

	/** Destructor.
		Note that deleting this object won't terminate the child process.
	*/
	~ChildProcess();

	/** Attempts to launch a child process command.

		The command should be the name of the executable file, followed by any arguments
		that are required.
		If the process has already been launched, this will launch it again. If a problem
		occurs, the method will return false.
	*/
	bool start (const String& command);

	/** Returns true if the child process is alive. */
	bool isRunning() const;

	/** Attempts to read some output from the child process.
		This will attempt to read up to the given number of bytes of data from the
		process. It returns the number of bytes that were actually read.
	*/
	int readProcessOutput (void* destBuffer, int numBytesToRead);

	/** Blocks until the process has finished, and then returns its complete output
		as a string.
	*/
	String readAllProcessOutput();

	/** Blocks until the process is no longer running. */
	bool waitForProcessToFinish (int timeoutMs) const;

	/** Attempts to kill the child process.
		Returns true if it succeeded. Trying to read from the process after calling this may
		result in undefined behaviour.
	*/
	bool kill();

private:

	class ActiveProcess;
	friend class ScopedPointer<ActiveProcess>;
	ScopedPointer<ActiveProcess> activeProcess;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChildProcess);
};

#endif   // __JUCE_CHILDPROCESS_JUCEHEADER__

/*** End of inlined file: juce_ChildProcess.h ***/


#endif
#ifndef __JUCE_CRITICALSECTION_JUCEHEADER__

#endif
#ifndef __JUCE_DYNAMICLIBRARY_JUCEHEADER__

/*** Start of inlined file: juce_DynamicLibrary.h ***/
#ifndef __JUCE_DYNAMICLIBRARY_JUCEHEADER__
#define __JUCE_DYNAMICLIBRARY_JUCEHEADER__

/**
	Handles the opening and closing of DLLs.

	This class can be used to open a DLL and get some function pointers from it.
	Since the DLL is freed when this object is deleted, it's handy for managing
	library lifetimes using RAII.
*/
class JUCE_API  DynamicLibrary
{
public:
	/** Creates an unopened DynamicLibrary object.
		Call open() to actually open one.
	*/
	DynamicLibrary() noexcept : handle (nullptr) {}

	/**
	*/
	DynamicLibrary (const String& name) : handle (nullptr) { open (name); }

	/** Destructor.
		If a library is currently open, it will be closed when this object is destroyed.
	*/
	~DynamicLibrary()   { close(); }

	/** Opens a DLL.
		The name and the method by which it gets found is of course platform-specific, and
		may or may not include a path, depending on the OS.
		If a library is already open when this method is called, it will first close the library
		before attempting to load the new one.
		@returns true if the library was successfully found and opened.
	*/
	bool open (const String& name);

	/** Releases the currently-open DLL, or has no effect if none was open. */
	void close();

	/** Tries to find a named function in the currently-open DLL, and returns a pointer to it.
		If no library is open, or if the function isn't found, this will return a null pointer.
	*/
	void* getFunction (const String& functionName) noexcept;

	/** Returns the platform-specific native library handle.
		You'll need to cast this to whatever is appropriate for the OS that's in use.
	*/
	void* getNativeHandle() const noexcept     { return handle; }

private:
	void* handle;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DynamicLibrary);
};

#endif   // __JUCE_DYNAMICLIBRARY_JUCEHEADER__

/*** End of inlined file: juce_DynamicLibrary.h ***/


#endif
#ifndef __JUCE_INTERPROCESSLOCK_JUCEHEADER__

/*** Start of inlined file: juce_InterProcessLock.h ***/
#ifndef __JUCE_INTERPROCESSLOCK_JUCEHEADER__
#define __JUCE_INTERPROCESSLOCK_JUCEHEADER__

/**
	Acts as a critical section which processes can use to block each other.

	@see CriticalSection
*/
class JUCE_API  InterProcessLock
{
public:

	/** Creates a lock object.

		@param name     a name that processes will use to identify this lock object
	*/
	explicit InterProcessLock (const String& name);

	/** Destructor.

		This will also release the lock if it's currently held by this process.
	*/
	~InterProcessLock();

	/** Attempts to lock the critical section.

		@param timeOutMillisecs     how many milliseconds to wait if the lock
									is already held by another process - a value of
									0 will return immediately, negative values will wait
									forever
		@returns    true if the lock could be gained within the timeout period, or
					false if the timeout expired.
	*/
	bool enter (int timeOutMillisecs = -1);

	/** Releases the lock if it's currently held by this process.
	*/
	void exit();

	/**
		Automatically locks and unlocks an InterProcessLock object.

		This works like a ScopedLock, but using an InterprocessLock rather than
		a CriticalSection.

		@see ScopedLock
	*/
	class ScopedLockType
	{
	public:

		/** Creates a scoped lock.

			As soon as it is created, this will lock the InterProcessLock, and
			when the ScopedLockType object is deleted, the InterProcessLock will
			be unlocked.

			Note that since an InterprocessLock can fail due to errors, you should check
			isLocked() to make sure that the lock was successful before using it.

			Make sure this object is created and deleted by the same thread,
			otherwise there are no guarantees what will happen! Best just to use it
			as a local stack object, rather than creating one with the new() operator.
		*/
		explicit ScopedLockType (InterProcessLock& lock)                    : lock_ (lock) { lockWasSuccessful = lock.enter(); }

		/** Destructor.

			The InterProcessLock will be unlocked when the destructor is called.

			Make sure this object is created and deleted by the same thread,
			otherwise there are no guarantees what will happen!
		*/
		inline ~ScopedLockType()                                            { lock_.exit(); }

		/** Returns true if the InterProcessLock was successfully locked. */
		bool isLocked() const noexcept                                      { return lockWasSuccessful; }

	private:

		InterProcessLock& lock_;
		bool lockWasSuccessful;

		JUCE_DECLARE_NON_COPYABLE (ScopedLockType);
	};

private:

	class Pimpl;
	friend class ScopedPointer <Pimpl>;
	ScopedPointer <Pimpl> pimpl;

	CriticalSection lock;
	String name;

	JUCE_DECLARE_NON_COPYABLE (InterProcessLock);
};

#endif   // __JUCE_INTERPROCESSLOCK_JUCEHEADER__

/*** End of inlined file: juce_InterProcessLock.h ***/


#endif
#ifndef __JUCE_PROCESS_JUCEHEADER__

/*** Start of inlined file: juce_Process.h ***/
#ifndef __JUCE_PROCESS_JUCEHEADER__
#define __JUCE_PROCESS_JUCEHEADER__

/** Represents the current executable's process.

	This contains methods for controlling the current application at the
	process-level.

	@see Thread, JUCEApplication
*/
class JUCE_API  Process
{
public:

	enum ProcessPriority
	{
		LowPriority         = 0,
		NormalPriority      = 1,
		HighPriority        = 2,
		RealtimePriority    = 3
	};

	/** Changes the current process's priority.

		@param priority     the process priority, where
							0=low, 1=normal, 2=high, 3=realtime
	*/
	static void setPriority (const ProcessPriority priority);

	/** Kills the current process immediately.

		This is an emergency process terminator that kills the application
		immediately - it's intended only for use only when something goes
		horribly wrong.

		@see JUCEApplication::quit
	*/
	static void terminate();

	/** Returns true if this application process is the one that the user is
		currently using.
	*/
	static bool isForegroundProcess();

	/** Raises the current process's privilege level.

		Does nothing if this isn't supported by the current OS, or if process
		privilege level is fixed.
	*/
	static void raisePrivilege();

	/** Lowers the current process's privilege level.

		Does nothing if this isn't supported by the current OS, or if process
		privilege level is fixed.
	*/
	static void lowerPrivilege();

	/** Returns true if this process is being hosted by a debugger.
	*/
	static bool JUCE_CALLTYPE isRunningUnderDebugger();

	/** Tries to launch the OS's default reader application for a given file or URL. */
	static bool openDocument (const String& documentURL, const String& parameters);

	/** Tries to launch the OS's default email application to let the user create a message. */
	static bool openEmailWithAttachments (const String& targetEmailAddress,
										  const String& emailSubject,
										  const String& bodyText,
										  const StringArray& filesToAttach);

   #if JUCE_WINDOWS || DOXYGEN

	/** WINDOWS ONLY - This returns the HINSTANCE of the current module.

		The return type is a void* to avoid being dependent on windows.h - just cast
		it to a HINSTANCE to use it.

		In a normal JUCE application, this will be automatically set to the module
		handle of the executable.

		If you've built a DLL and plan to use any JUCE messaging or windowing classes,
		you'll need to make sure you call the setCurrentModuleInstanceHandle()
		to provide the correct module handle in your DllMain() function, because
		the system relies on the correct instance handle when opening windows.
	*/
	static void* JUCE_CALLTYPE getCurrentModuleInstanceHandle() noexcept;

	/** WINDOWS ONLY - Sets a new module handle to be used by the library.

		The parameter type is a void* to avoid being dependent on windows.h, but it actually
		expects a HINSTANCE value.

		@see getCurrentModuleInstanceHandle()
	*/
	static void JUCE_CALLTYPE setCurrentModuleInstanceHandle (void* newHandle) noexcept;

	/** WINDOWS ONLY - Gets the command-line params as a string.
		This is needed to avoid unicode problems with the argc type params.
	*/
	static String JUCE_CALLTYPE getCurrentCommandLineParams();
   #endif

private:
	Process();
	JUCE_DECLARE_NON_COPYABLE (Process);
};

#endif   // __JUCE_PROCESS_JUCEHEADER__

/*** End of inlined file: juce_Process.h ***/


#endif
#ifndef __JUCE_READWRITELOCK_JUCEHEADER__

/*** Start of inlined file: juce_ReadWriteLock.h ***/
#ifndef __JUCE_READWRITELOCK_JUCEHEADER__
#define __JUCE_READWRITELOCK_JUCEHEADER__


/*** Start of inlined file: juce_SpinLock.h ***/
#ifndef __JUCE_SPINLOCK_JUCEHEADER__
#define __JUCE_SPINLOCK_JUCEHEADER__

/**
	A simple spin-lock class that can be used as a simple, low-overhead mutex for
	uncontended situations.

	Note that unlike a CriticalSection, this type of lock is not re-entrant, and may
	be less efficient when used it a highly contended situation, but it's very small and
	requires almost no initialisation.
	It's most appropriate for simple situations where you're only going to hold the
	lock for a very brief time.

	@see CriticalSection
*/
class JUCE_API  SpinLock
{
public:
	inline SpinLock() noexcept {}
	inline ~SpinLock() noexcept {}

	/** Acquires the lock.
		This will block until the lock has been successfully acquired by this thread.
		Note that a SpinLock is NOT re-entrant, and is not smart enough to know whether the
		caller thread already has the lock - so if a thread tries to acquire a lock that it
		already holds, this method will never return!

		It's strongly recommended that you never call this method directly - instead use the
		ScopedLockType class to manage the locking using an RAII pattern instead.
	*/
	void enter() const noexcept;

	/** Attempts to acquire the lock, returning true if this was successful. */
	inline bool tryEnter() const noexcept
	{
		return lock.compareAndSetBool (1, 0);
	}

	/** Releases the lock. */
	inline void exit() const noexcept
	{
		jassert (lock.value == 1); // Agh! Releasing a lock that isn't currently held!
		lock = 0;
	}

	/** Provides the type of scoped lock to use for locking a SpinLock. */
	typedef GenericScopedLock <SpinLock>       ScopedLockType;

	/** Provides the type of scoped unlocker to use with a SpinLock. */
	typedef GenericScopedUnlock <SpinLock>     ScopedUnlockType;

private:

	mutable Atomic<int> lock;

	JUCE_DECLARE_NON_COPYABLE (SpinLock);
};

#endif   // __JUCE_SPINLOCK_JUCEHEADER__

/*** End of inlined file: juce_SpinLock.h ***/


/*** Start of inlined file: juce_WaitableEvent.h ***/
#ifndef __JUCE_WAITABLEEVENT_JUCEHEADER__
#define __JUCE_WAITABLEEVENT_JUCEHEADER__

/**
	Allows threads to wait for events triggered by other threads.

	A thread can call wait() on a WaitableObject, and this will suspend the
	calling thread until another thread wakes it up by calling the signal()
	method.
*/
class JUCE_API  WaitableEvent
{
public:

	/** Creates a WaitableEvent object.

		@param manualReset  If this is false, the event will be reset automatically when the wait()
							method is called. If manualReset is true, then once the event is signalled,
							the only way to reset it will be by calling the reset() method.
	*/
	WaitableEvent (bool manualReset = false) noexcept;

	/** Destructor.

		If other threads are waiting on this object when it gets deleted, this
		can cause nasty errors, so be careful!
	*/
	~WaitableEvent() noexcept;

	/** Suspends the calling thread until the event has been signalled.

		This will wait until the object's signal() method is called by another thread,
		or until the timeout expires.

		After the event has been signalled, this method will return true and if manualReset
		was set to false in the WaitableEvent's constructor, then the event will be reset.

		@param timeOutMilliseconds  the maximum time to wait, in milliseconds. A negative
									value will cause it to wait forever.

		@returns    true if the object has been signalled, false if the timeout expires first.
		@see signal, reset
	*/
	bool wait (int timeOutMilliseconds = -1) const noexcept;

	/** Wakes up any threads that are currently waiting on this object.

		If signal() is called when nothing is waiting, the next thread to call wait()
		will return immediately and reset the signal.

		If the WaitableEvent is manual reset, all current and future threads that wait upon this
		object will be woken, until reset() is explicitly called.

		If the WaitableEvent is automatic reset, and one or more threads is waiting upon the object,
		then one of them will be woken up. If no threads are currently waiting, then the next thread
		to call wait() will be woken up. As soon as a thread is woken, the signal is automatically
		reset.

		@see wait, reset
	*/
	void signal() const noexcept;

	/** Resets the event to an unsignalled state.

		If it's not already signalled, this does nothing.
	*/
	void reset() const noexcept;

private:

	void* internal;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaitableEvent);
};

#endif   // __JUCE_WAITABLEEVENT_JUCEHEADER__

/*** End of inlined file: juce_WaitableEvent.h ***/


/*** Start of inlined file: juce_Thread.h ***/
#ifndef __JUCE_THREAD_JUCEHEADER__
#define __JUCE_THREAD_JUCEHEADER__

/**
	Encapsulates a thread.

	Subclasses derive from Thread and implement the run() method, in which they
	do their business. The thread can then be started with the startThread() method
	and controlled with various other methods.

	This class also contains some thread-related static methods, such
	as sleep(), yield(), getCurrentThreadId() etc.

	@see CriticalSection, WaitableEvent, Process, ThreadWithProgressWindow,
		 MessageManagerLock
*/
class JUCE_API  Thread
{
public:

	/**
		Creates a thread.

		When first created, the thread is not running. Use the startThread()
		method to start it.
	*/
	explicit Thread (const String& threadName);

	/** Destructor.

		Deleting a Thread object that is running will only give the thread a
		brief opportunity to stop itself cleanly, so it's recommended that you
		should always call stopThread() with a decent timeout before deleting,
		to avoid the thread being forcibly killed (which is a Bad Thing).
	*/
	virtual ~Thread();

	/** Must be implemented to perform the thread's actual code.

		Remember that the thread must regularly check the threadShouldExit()
		method whilst running, and if this returns true it should return from
		the run() method as soon as possible to avoid being forcibly killed.

		@see threadShouldExit, startThread
	*/
	virtual void run() = 0;

	// Thread control functions..

	/** Starts the thread running.

		This will start the thread's run() method.
		(if it's already started, startThread() won't do anything).

		@see stopThread
	*/
	void startThread();

	/** Starts the thread with a given priority.

		Launches the thread with a given priority, where 0 = lowest, 10 = highest.
		If the thread is already running, its priority will be changed.

		@see startThread, setPriority
	*/
	void startThread (int priority);

	/** Attempts to stop the thread running.

		This method will cause the threadShouldExit() method to return true
		and call notify() in case the thread is currently waiting.

		Hopefully the thread will then respond to this by exiting cleanly, and
		the stopThread method will wait for a given time-period for this to
		happen.

		If the thread is stuck and fails to respond after the time-out, it gets
		forcibly killed, which is a very bad thing to happen, as it could still
		be holding locks, etc. which are needed by other parts of your program.

		@param timeOutMilliseconds  The number of milliseconds to wait for the
									thread to finish before killing it by force. A negative
									value in here will wait forever.
		@see signalThreadShouldExit, threadShouldExit, waitForThreadToExit, isThreadRunning
	*/
	void stopThread (int timeOutMilliseconds);

	/** Returns true if the thread is currently active */
	bool isThreadRunning() const;

	/** Sets a flag to tell the thread it should stop.

		Calling this means that the threadShouldExit() method will then return true.
		The thread should be regularly checking this to see whether it should exit.

		If your thread makes use of wait(), you might want to call notify() after calling
		this method, to interrupt any waits that might be in progress, and allow it
		to reach a point where it can exit.

		@see threadShouldExit
		@see waitForThreadToExit
	*/
	void signalThreadShouldExit();

	/** Checks whether the thread has been told to stop running.

		Threads need to check this regularly, and if it returns true, they should
		return from their run() method at the first possible opportunity.

		@see signalThreadShouldExit
	*/
	inline bool threadShouldExit() const                { return threadShouldExit_; }

	/** Waits for the thread to stop.

		This will waits until isThreadRunning() is false or until a timeout expires.

		@param timeOutMilliseconds  the time to wait, in milliseconds. If this value
									is less than zero, it will wait forever.
		@returns    true if the thread exits, or false if the timeout expires first.
	*/
	bool waitForThreadToExit (int timeOutMilliseconds) const;

	/** Changes the thread's priority.
		May return false if for some reason the priority can't be changed.

		@param priority     the new priority, in the range 0 (lowest) to 10 (highest). A priority
							of 5 is normal.
	*/
	bool setPriority (int priority);

	/** Changes the priority of the caller thread.

		Similar to setPriority(), but this static method acts on the caller thread.
		May return false if for some reason the priority can't be changed.

		@see setPriority
	*/
	static bool setCurrentThreadPriority (int priority);

	/** Sets the affinity mask for the thread.

		This will only have an effect next time the thread is started - i.e. if the
		thread is already running when called, it'll have no effect.

		@see setCurrentThreadAffinityMask
	*/
	void setAffinityMask (uint32 affinityMask);

	/** Changes the affinity mask for the caller thread.

		This will change the affinity mask for the thread that calls this static method.

		@see setAffinityMask
	*/
	static void setCurrentThreadAffinityMask (uint32 affinityMask);

	// this can be called from any thread that needs to pause..
	static void JUCE_CALLTYPE sleep (int milliseconds);

	/** Yields the calling thread's current time-slot. */
	static void JUCE_CALLTYPE yield();

	/** Makes the thread wait for a notification.

		This puts the thread to sleep until either the timeout period expires, or
		another thread calls the notify() method to wake it up.

		A negative time-out value means that the method will wait indefinitely.

		@returns    true if the event has been signalled, false if the timeout expires.
	*/
	bool wait (int timeOutMilliseconds) const;

	/** Wakes up the thread.

		If the thread has called the wait() method, this will wake it up.

		@see wait
	*/
	void notify() const;

	/** A value type used for thread IDs.
		@see getCurrentThreadId(), getThreadId()
	*/
	typedef void* ThreadID;

	/** Returns an id that identifies the caller thread.

		To find the ID of a particular thread object, use getThreadId().

		@returns    a unique identifier that identifies the calling thread.
		@see getThreadId
	*/
	static ThreadID getCurrentThreadId();

	/** Finds the thread object that is currently running.

		Note that the main UI thread (or other non-Juce threads) don't have a Thread
		object associated with them, so this will return 0.
	*/
	static Thread* getCurrentThread();

	/** Returns the ID of this thread.

		That means the ID of this thread object - not of the thread that's calling the method.

		This can change when the thread is started and stopped, and will be invalid if the
		thread's not actually running.

		@see getCurrentThreadId
	*/
	ThreadID getThreadId() const noexcept                           { return threadId_; }

	/** Returns the name of the thread.

		This is the name that gets set in the constructor.
	*/
	const String& getThreadName() const                             { return threadName_; }

	/** Changes the name of the caller thread.
		Different OSes may place different length or content limits on this name.
	*/
	static void setCurrentThreadName (const String& newThreadName);

	/** Returns the number of currently-running threads.

		@returns  the number of Thread objects known to be currently running.
		@see stopAllThreads
	*/
	static int getNumRunningThreads();

	/** Tries to stop all currently-running threads.

		This will attempt to stop all the threads known to be running at the moment.
	*/
	static void stopAllThreads (int timeoutInMillisecs);

private:

	const String threadName_;
	void* volatile threadHandle_;
	ThreadID threadId_;
	CriticalSection startStopLock;
	WaitableEvent startSuspensionEvent_, defaultEvent_;
	int threadPriority_;
	uint32 affinityMask_;
	bool volatile threadShouldExit_;

   #ifndef DOXYGEN
	friend void JUCE_API juce_threadEntryPoint (void*);
   #endif

	void launchThread();
	void closeThreadHandle();
	void killThread();
	void threadEntryPoint();
	static bool setThreadPriority (void*, int priority);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Thread);
};

#endif   // __JUCE_THREAD_JUCEHEADER__

/*** End of inlined file: juce_Thread.h ***/

/**
	A critical section that allows multiple simultaneous readers.

	Features of this type of lock are:

	- Multiple readers can hold the lock at the same time, but only one writer
	  can hold it at once.
	- Writers trying to gain the lock will be blocked until all readers and writers
	  have released it
	- Readers trying to gain the lock while a writer is waiting to acquire it will be
	  blocked until the writer has obtained and released it
	- If a thread already has a read lock and tries to obtain a write lock, it will succeed if
	  there are no other readers
	- If a thread already has the write lock and tries to obtain a read lock, this will succeed.
	- Recursive locking is supported.

	@see ScopedReadLock, ScopedWriteLock, CriticalSection
*/
class JUCE_API  ReadWriteLock
{
public:

	/**
		Creates a ReadWriteLock object.
	*/
	ReadWriteLock() noexcept;

	/** Destructor.

		If the object is deleted whilst locked, any subsequent behaviour
		is unpredictable.
	*/
	~ReadWriteLock() noexcept;

	/** Locks this object for reading.

		Multiple threads can simulaneously lock the object for reading, but if another
		thread has it locked for writing, then this will block until it releases the
		lock.

		@see exitRead, ScopedReadLock
	*/
	void enterRead() const noexcept;

	/** Releases the read-lock.

		If the caller thread hasn't got the lock, this can have unpredictable results.

		If the enterRead() method has been called multiple times by the thread, each
		call must be matched by a call to exitRead() before other threads will be allowed
		to take over the lock.

		@see enterRead, ScopedReadLock
	*/
	void exitRead() const noexcept;

	/** Locks this object for writing.

		This will block until any other threads that have it locked for reading or
		writing have released their lock.

		@see exitWrite, ScopedWriteLock
	*/
	void enterWrite() const noexcept;

	/** Tries to lock this object for writing.

		This is like enterWrite(), but doesn't block - it returns true if it manages
		to obtain the lock.

		@see enterWrite
	*/
	bool tryEnterWrite() const noexcept;

	/** Releases the write-lock.

		If the caller thread hasn't got the lock, this can have unpredictable results.

		If the enterWrite() method has been called multiple times by the thread, each
		call must be matched by a call to exit() before other threads will be allowed
		to take over the lock.

		@see enterWrite, ScopedWriteLock
	*/
	void exitWrite() const noexcept;

private:

	SpinLock accessLock;
	WaitableEvent waitEvent;
	mutable int numWaitingWriters, numWriters;
	mutable Thread::ThreadID writerThreadId;
	mutable Array <Thread::ThreadID> readerThreads;

	JUCE_DECLARE_NON_COPYABLE (ReadWriteLock);
};

#endif   // __JUCE_READWRITELOCK_JUCEHEADER__

/*** End of inlined file: juce_ReadWriteLock.h ***/


#endif
#ifndef __JUCE_SCOPEDLOCK_JUCEHEADER__

#endif
#ifndef __JUCE_SCOPEDREADLOCK_JUCEHEADER__

/*** Start of inlined file: juce_ScopedReadLock.h ***/
#ifndef __JUCE_SCOPEDREADLOCK_JUCEHEADER__
#define __JUCE_SCOPEDREADLOCK_JUCEHEADER__

/**
	Automatically locks and unlocks a ReadWriteLock object.

	Use one of these as a local variable to control access to a ReadWriteLock.

	e.g. @code

	ReadWriteLock myLock;

	for (;;)
	{
		const ScopedReadLock myScopedLock (myLock);
		// myLock is now locked

		...do some stuff...

		// myLock gets unlocked here.
	}
	@endcode

	@see ReadWriteLock, ScopedWriteLock
*/
class JUCE_API  ScopedReadLock
{
public:

	/** Creates a ScopedReadLock.

		As soon as it is created, this will call ReadWriteLock::enterRead(), and
		when the ScopedReadLock object is deleted, the ReadWriteLock will
		be unlocked.

		Make sure this object is created and deleted by the same thread,
		otherwise there are no guarantees what will happen! Best just to use it
		as a local stack object, rather than creating one with the new() operator.
	*/
	inline explicit ScopedReadLock (const ReadWriteLock& lock) noexcept   : lock_ (lock) { lock.enterRead(); }

	/** Destructor.

		The ReadWriteLock's exitRead() method will be called when the destructor is called.

		Make sure this object is created and deleted by the same thread,
		otherwise there are no guarantees what will happen!
	*/
	inline ~ScopedReadLock() noexcept                                     { lock_.exitRead(); }

private:

	const ReadWriteLock& lock_;

	JUCE_DECLARE_NON_COPYABLE (ScopedReadLock);
};

#endif   // __JUCE_SCOPEDREADLOCK_JUCEHEADER__

/*** End of inlined file: juce_ScopedReadLock.h ***/


#endif
#ifndef __JUCE_SCOPEDWRITELOCK_JUCEHEADER__

/*** Start of inlined file: juce_ScopedWriteLock.h ***/
#ifndef __JUCE_SCOPEDWRITELOCK_JUCEHEADER__
#define __JUCE_SCOPEDWRITELOCK_JUCEHEADER__

/**
	Automatically locks and unlocks a ReadWriteLock object.

	Use one of these as a local variable to control access to a ReadWriteLock.

	e.g. @code

	ReadWriteLock myLock;

	for (;;)
	{
		const ScopedWriteLock myScopedLock (myLock);
		// myLock is now locked

		...do some stuff...

		// myLock gets unlocked here.
	}
	@endcode

	@see ReadWriteLock, ScopedReadLock
*/
class JUCE_API  ScopedWriteLock
{
public:

	/** Creates a ScopedWriteLock.

		As soon as it is created, this will call ReadWriteLock::enterWrite(), and
		when the ScopedWriteLock object is deleted, the ReadWriteLock will
		be unlocked.

		Make sure this object is created and deleted by the same thread,
		otherwise there are no guarantees what will happen! Best just to use it
		as a local stack object, rather than creating one with the new() operator.
	*/
	inline explicit ScopedWriteLock (const ReadWriteLock& lock) noexcept : lock_ (lock) { lock.enterWrite(); }

	/** Destructor.

		The ReadWriteLock's exitWrite() method will be called when the destructor is called.

		Make sure this object is created and deleted by the same thread,
		otherwise there are no guarantees what will happen!
	*/
	inline ~ScopedWriteLock() noexcept                                   { lock_.exitWrite(); }

private:

	const ReadWriteLock& lock_;

	JUCE_DECLARE_NON_COPYABLE (ScopedWriteLock);
};

#endif   // __JUCE_SCOPEDWRITELOCK_JUCEHEADER__

/*** End of inlined file: juce_ScopedWriteLock.h ***/


#endif
#ifndef __JUCE_SPINLOCK_JUCEHEADER__

#endif
#ifndef __JUCE_THREAD_JUCEHEADER__

#endif
#ifndef __JUCE_THREADLOCALVALUE_JUCEHEADER__

/*** Start of inlined file: juce_ThreadLocalValue.h ***/
#ifndef __JUCE_THREADLOCALVALUE_JUCEHEADER__
#define __JUCE_THREADLOCALVALUE_JUCEHEADER__

/**
	Provides cross-platform support for thread-local objects.

	This class holds an internal list of objects of the templated type, keeping
	an instance for each thread that requests one. The first time a thread attempts
	to access its value, an object is created and added to the list for that thread.

	The templated class for your value could be a primitive type, or any class that
	has a default constructor.

	Once a thread has accessed its object, that object will not be deleted until the
	ThreadLocalValue object itself is deleted, even if its thread exits before that.
	But, because thread ID numbers are used to identify threads, and OSes often re-use
	these ID numbers, value objects will often be implicitly re-used by new threads whose
	ID number is the same as one that was used by an earlier thread.
*/
template <typename Type>
class ThreadLocalValue
{
public:
	/** */
	ThreadLocalValue() noexcept
	{
	}

	/** Destructor.
		When this object is deleted, all the value objects for all threads will be deleted.
	*/
	~ThreadLocalValue()
	{
		for (ObjectHolder* o = first.value; o != nullptr;)
		{
			ObjectHolder* const next = o->next;
			delete o;
			o = next;
		}
	}

	/** Returns a reference to this thread's instance of the value.
		Note that the first time a thread tries to access the value, an instance of the
		value object will be created - so if your value's class has a non-trivial
		constructor, be aware that this method could invoke it.
	*/
	Type& operator*() const noexcept    { return get(); }

	/** Returns a pointer to this thread's instance of the value.
		Note that the first time a thread tries to access the value, an instance of the
		value object will be created - so if your value's class has a non-trivial
		constructor, be aware that this method could invoke it.
	*/
	operator Type*() const noexcept     { return &get(); }

	/** Accesses a method or field of the value object.
		Note that the first time a thread tries to access the value, an instance of the
		value object will be created - so if your value's class has a non-trivial
		constructor, be aware that this method could invoke it.
	*/
	Type* operator->() const noexcept   { return &get(); }

	/** Returns a reference to this thread's instance of the value.
		Note that the first time a thread tries to access the value, an instance of the
		value object will be created - so if your value's class has a non-trivial
		constructor, be aware that this method could invoke it.
	*/
	Type& get() const noexcept
	{
		const Thread::ThreadID threadId = Thread::getCurrentThreadId();

		for (ObjectHolder* o = first.get(); o != nullptr; o = o->next)
			if (o->threadId == threadId)
				return o->object;

		ObjectHolder* const newObject = new ObjectHolder (threadId);

		do
		{
			newObject->next = first.get();
		}
		while (! first.compareAndSetBool (newObject, newObject->next));

		return newObject->object;
	}

private:

	struct ObjectHolder
	{
		ObjectHolder (const Thread::ThreadID& threadId_)
			: threadId (threadId_), object()
		{}

		const Thread::ThreadID threadId;
		ObjectHolder* next;
		Type object;

		JUCE_DECLARE_NON_COPYABLE (ObjectHolder);
	};

	mutable Atomic<ObjectHolder*> first;

	JUCE_DECLARE_NON_COPYABLE (ThreadLocalValue);
};

#endif   // __JUCE_THREADLOCALVALUE_JUCEHEADER__

/*** End of inlined file: juce_ThreadLocalValue.h ***/


#endif
#ifndef __JUCE_THREADPOOL_JUCEHEADER__

/*** Start of inlined file: juce_ThreadPool.h ***/
#ifndef __JUCE_THREADPOOL_JUCEHEADER__
#define __JUCE_THREADPOOL_JUCEHEADER__

class ThreadPool;
class ThreadPoolThread;

/**
	A task that is executed by a ThreadPool object.

	A ThreadPool keeps a list of ThreadPoolJob objects which are executed by
	its threads.

	The runJob() method needs to be implemented to do the task, and if the code that
	does the work takes a significant time to run, it must keep checking the shouldExit()
	method to see if something is trying to interrupt the job. If shouldExit() returns
	true, the runJob() method must return immediately.

	@see ThreadPool, Thread
*/
class JUCE_API  ThreadPoolJob
{
public:

	/** Creates a thread pool job object.

		After creating your job, add it to a thread pool with ThreadPool::addJob().
	*/
	explicit ThreadPoolJob (const String& name);

	/** Destructor. */
	virtual ~ThreadPoolJob();

	/** Returns the name of this job.
		@see setJobName
	*/
	String getJobName() const;

	/** Changes the job's name.
		@see getJobName
	*/
	void setJobName (const String& newName);

	/** These are the values that can be returned by the runJob() method.
	*/
	enum JobStatus
	{
		jobHasFinished = 0,     /**< indicates that the job has finished and can be
									 removed from the pool. */

		jobHasFinishedAndShouldBeDeleted,  /**< indicates that the job has finished and that it
												should be automatically deleted by the pool. */

		jobNeedsRunningAgain    /**< indicates that the job would like to be called
									 again when a thread is free. */
	};

	/** Peforms the actual work that this job needs to do.

		Your subclass must implement this method, in which is does its work.

		If the code in this method takes a significant time to run, it must repeatedly check
		the shouldExit() method to see if something is trying to interrupt the job.
		If shouldExit() ever returns true, the runJob() method must return immediately.

		If this method returns jobHasFinished, then the job will be removed from the pool
		immediately. If it returns jobNeedsRunningAgain, then the job will be left in the
		pool and will get a chance to run again as soon as a thread is free.

		@see shouldExit()
	*/
	virtual JobStatus runJob() = 0;

	/** Returns true if this job is currently running its runJob() method. */
	bool isRunning() const                  { return isActive; }

	/** Returns true if something is trying to interrupt this job and make it stop.

		Your runJob() method must call this whenever it gets a chance, and if it ever
		returns true, the runJob() method must return immediately.

		@see signalJobShouldExit()
	*/
	bool shouldExit() const                 { return shouldStop; }

	/** Calling this will cause the shouldExit() method to return true, and the job
		should (if it's been implemented correctly) stop as soon as possible.

		@see shouldExit()
	*/
	void signalJobShouldExit();

private:
	friend class ThreadPool;
	friend class ThreadPoolThread;
	String jobName;
	ThreadPool* pool;
	bool shouldStop, isActive, shouldBeDeleted;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThreadPoolJob);
};

/**
	A set of threads that will run a list of jobs.

	When a ThreadPoolJob object is added to the ThreadPool's list, its run() method
	will be called by the next pooled thread that becomes free.

	@see ThreadPoolJob, Thread
*/
class JUCE_API  ThreadPool
{
public:

	/** Creates a thread pool.

		Once you've created a pool, you can give it some things to do with the addJob()
		method.

		@param numberOfThreads              the maximum number of actual threads to run.
		@param startThreadsOnlyWhenNeeded   if this is true, then no threads will be started
											until there are some jobs to run. If false, then
											all the threads will be fired-up immediately so that
											they're ready for action
		@param stopThreadsWhenNotUsedTimeoutMs  if this timeout is > 0, then if any threads have been
											inactive for this length of time, they will automatically
											be stopped until more jobs come along and they're needed
	*/
	ThreadPool (int numberOfThreads,
				bool startThreadsOnlyWhenNeeded = true,
				int stopThreadsWhenNotUsedTimeoutMs = 5000);

	/** Destructor.

		This will attempt to remove all the jobs before deleting, but if you want to
		specify a timeout, you should call removeAllJobs() explicitly before deleting
		the pool.
	*/
	~ThreadPool();

	/** A callback class used when you need to select which ThreadPoolJob objects are suitable
		for some kind of operation.
		@see ThreadPool::removeAllJobs
	*/
	class JUCE_API  JobSelector
	{
	public:
		virtual ~JobSelector() {}

		/** Should return true if the specified thread matches your criteria for whatever
			operation that this object is being used for.

			Any implementation of this method must be extremely fast and thread-safe!
		*/
		virtual bool isJobSuitable (ThreadPoolJob* job) = 0;
	};

	/** Adds a job to the queue.

		Once a job has been added, then the next time a thread is free, it will run
		the job's ThreadPoolJob::runJob() method. Depending on the return value of the
		runJob() method, the pool will either remove the job from the pool or add it to
		the back of the queue to be run again.
	*/
	void addJob (ThreadPoolJob* job);

	/** Tries to remove a job from the pool.

		If the job isn't yet running, this will simply remove it. If it is running, it
		will wait for it to finish.

		If the timeout period expires before the job finishes running, then the job will be
		left in the pool and this will return false. It returns true if the job is sucessfully
		stopped and removed.

		@param job                  the job to remove
		@param interruptIfRunning   if true, then if the job is currently busy, its
									ThreadPoolJob::signalJobShouldExit() method will be called to try
									to interrupt it. If false, then if the job will be allowed to run
									until it stops normally (or the timeout expires)
		@param timeOutMilliseconds  the length of time this method should wait for the job to finish
									before giving up and returning false
	*/
	bool removeJob (ThreadPoolJob* job,
					bool interruptIfRunning,
					int timeOutMilliseconds);

	/** Tries to remove all jobs from the pool.

		@param interruptRunningJobs if true, then all running jobs will have their ThreadPoolJob::signalJobShouldExit()
									methods called to try to interrupt them
		@param timeOutMilliseconds  the length of time this method should wait for all the jobs to finish
									before giving up and returning false
		@param deleteInactiveJobs   if true, any jobs that aren't currently running will be deleted. If false,
									they will simply be removed from the pool. Jobs that are already running when
									this method is called can choose whether they should be deleted by
									returning jobHasFinishedAndShouldBeDeleted from their runJob() method.
		@param selectedJobsToRemove if this is non-zero, the JobSelector object is asked to decide which
									jobs should be removed. If it is zero, all jobs are removed
		@returns    true if all jobs are successfully stopped and removed; false if the timeout period
					expires while waiting for one or more jobs to stop
	*/
	bool removeAllJobs (bool interruptRunningJobs,
						int timeOutMilliseconds,
						bool deleteInactiveJobs = false,
						JobSelector* selectedJobsToRemove = nullptr);

	/** Returns the number of jobs currently running or queued.
	*/
	int getNumJobs() const;

	/** Returns one of the jobs in the queue.

		Note that this can be a very volatile list as jobs might be continuously getting shifted
		around in the list, and this method may return 0 if the index is currently out-of-range.
	*/
	ThreadPoolJob* getJob (int index) const;

	/** Returns true if the given job is currently queued or running.

		@see isJobRunning()
	*/
	bool contains (const ThreadPoolJob* job) const;

	/** Returns true if the given job is currently being run by a thread.
	*/
	bool isJobRunning (const ThreadPoolJob* job) const;

	/** Waits until a job has finished running and has been removed from the pool.

		This will wait until the job is no longer in the pool - i.e. until its
		runJob() method returns ThreadPoolJob::jobHasFinished.

		If the timeout period expires before the job finishes, this will return false;
		it returns true if the job has finished successfully.
	*/
	bool waitForJobToFinish (const ThreadPoolJob* job,
							 int timeOutMilliseconds) const;

	/** Returns a list of the names of all the jobs currently running or queued.

		If onlyReturnActiveJobs is true, only the ones currently running are returned.
	*/
	StringArray getNamesOfAllJobs (bool onlyReturnActiveJobs) const;

	/** Changes the priority of all the threads.

		This will call Thread::setPriority() for each thread in the pool.
		May return false if for some reason the priority can't be changed.
	*/
	bool setThreadPriorities (int newPriority);

private:

	const int threadStopTimeout;
	int priority;
	class ThreadPoolThread;
	friend class OwnedArray <ThreadPoolThread>;
	OwnedArray <ThreadPoolThread> threads;
	Array <ThreadPoolJob*> jobs;

	CriticalSection lock;
	uint32 lastJobEndTime;
	WaitableEvent jobFinishedSignal;

	friend class ThreadPoolThread;
	bool runNextJob();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThreadPool);
};

#endif   // __JUCE_THREADPOOL_JUCEHEADER__

/*** End of inlined file: juce_ThreadPool.h ***/


#endif
#ifndef __JUCE_TIMESLICETHREAD_JUCEHEADER__

/*** Start of inlined file: juce_TimeSliceThread.h ***/
#ifndef __JUCE_TIMESLICETHREAD_JUCEHEADER__
#define __JUCE_TIMESLICETHREAD_JUCEHEADER__

class TimeSliceThread;

/**
	Used by the TimeSliceThread class.

	To register your class with a TimeSliceThread, derive from this class and
	use the TimeSliceThread::addTimeSliceClient() method to add it to the list.

	Make sure you always call TimeSliceThread::removeTimeSliceClient() before
	deleting your client!

	@see TimeSliceThread
*/
class JUCE_API  TimeSliceClient
{
public:
	/** Destructor. */
	virtual ~TimeSliceClient()   {}

	/** Called back by a TimeSliceThread.

		When you register this class with it, a TimeSliceThread will repeatedly call
		this method.

		The implementation of this method should use its time-slice to do something that's
		quick - never block for longer than absolutely necessary.

		@returns    Your method should return the number of milliseconds which it would like to wait before being called
					again. Returning 0 will make the thread call again as soon as possible (after possibly servicing
					other busy clients). If you return a value below zero, your client will be removed from the list of clients,
					and won't be called again. The value you specify isn't a guaranteee, and is only used as a hint by the
					thread - the actual time before the next callback may be more or less than specified.
					You can force the TimeSliceThread to wake up and poll again immediately by calling its notify() method.
	*/
	virtual int useTimeSlice() = 0;

private:
	friend class TimeSliceThread;
	Time nextCallTime;
};

/**
	A thread that keeps a list of clients, and calls each one in turn, giving them
	all a chance to run some sort of short task.

	@see TimeSliceClient, Thread
*/
class JUCE_API  TimeSliceThread   : public Thread
{
public:

	/**
		Creates a TimeSliceThread.

		When first created, the thread is not running. Use the startThread()
		method to start it.
	*/
	explicit TimeSliceThread (const String& threadName);

	/** Destructor.

		Deleting a Thread object that is running will only give the thread a
		brief opportunity to stop itself cleanly, so it's recommended that you
		should always call stopThread() with a decent timeout before deleting,
		to avoid the thread being forcibly killed (which is a Bad Thing).
	*/
	~TimeSliceThread();

	/** Adds a client to the list.

		The client's callbacks will start after the number of milliseconds specified
		by millisecondsBeforeStarting (and this may happen before this method has returned).
	*/
	void addTimeSliceClient (TimeSliceClient* client, int millisecondsBeforeStarting = 0);

	/** Removes a client from the list.

		This method will make sure that all callbacks to the client have completely
		finished before the method returns.
	*/
	void removeTimeSliceClient (TimeSliceClient* client);

	/** If the given client is waiting in the queue, it will be moved to the front
		and given a time-slice as soon as possible.
		If the specified client has not been added, nothing will happen.
	*/
	void moveToFrontOfQueue (TimeSliceClient* client);

	/** Returns the number of registered clients. */
	int getNumClients() const;

	/** Returns one of the registered clients. */
	TimeSliceClient* getClient (int index) const;

   #ifndef DOXYGEN
	void run();
   #endif

private:
	CriticalSection callbackLock, listLock;
	Array <TimeSliceClient*> clients;
	TimeSliceClient* clientBeingCalled;

	TimeSliceClient* getNextClient (int index) const;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeSliceThread);
};

#endif   // __JUCE_TIMESLICETHREAD_JUCEHEADER__

/*** End of inlined file: juce_TimeSliceThread.h ***/


#endif
#ifndef __JUCE_WAITABLEEVENT_JUCEHEADER__

#endif
#ifndef __JUCE_PERFORMANCECOUNTER_JUCEHEADER__

/*** Start of inlined file: juce_PerformanceCounter.h ***/
#ifndef __JUCE_PERFORMANCECOUNTER_JUCEHEADER__
#define __JUCE_PERFORMANCECOUNTER_JUCEHEADER__

/** A timer for measuring performance of code and dumping the results to a file.

	e.g. @code

		PerformanceCounter pc ("fish", 50, "/temp/myfishlog.txt");

		for (;;)
		{
			pc.start();

			doSomethingFishy();

			pc.stop();
		}
	@endcode

	In this example, the time of each period between calling start/stop will be
	measured and averaged over 50 runs, and the results printed to a file
	every 50 times round the loop.
*/
class JUCE_API  PerformanceCounter
{
public:

	/** Creates a PerformanceCounter object.

		@param counterName      the name used when printing out the statistics
		@param runsPerPrintout  the number of start/stop iterations before calling
								printStatistics()
		@param loggingFile      a file to dump the results to - if this is File::nonexistent,
								the results are just written to the debugger output
	*/
	PerformanceCounter (const String& counterName,
						int runsPerPrintout = 100,
						const File& loggingFile = File::nonexistent);

	/** Destructor. */
	~PerformanceCounter();

	/** Starts timing.

		@see stop
	*/
	void start();

	/** Stops timing and prints out the results.

		The number of iterations before doing a printout of the
		results is set in the constructor.

		@see start
	*/
	void stop();

	/** Dumps the current metrics to the debugger output and to a file.

		As well as using Logger::outputDebugString to print the results,
		this will write then to the file specified in the constructor (if
		this was valid).
	*/
	void printStatistics();

private:

	String name;
	int numRuns, runsPerPrint;
	double totalTime;
	int64 started;
	File outputFile;
};

#endif   // __JUCE_PERFORMANCECOUNTER_JUCEHEADER__

/*** End of inlined file: juce_PerformanceCounter.h ***/


#endif
#ifndef __JUCE_RELATIVETIME_JUCEHEADER__

#endif
#ifndef __JUCE_TIME_JUCEHEADER__

#endif
#ifndef __JUCE_UNITTEST_JUCEHEADER__

/*** Start of inlined file: juce_UnitTest.h ***/
#ifndef __JUCE_UNITTEST_JUCEHEADER__
#define __JUCE_UNITTEST_JUCEHEADER__

class UnitTestRunner;

/**
	This is a base class for classes that perform a unit test.

	To write a test using this class, your code should look something like this:

	@code
	class MyTest  : public UnitTest
	{
	public:
		MyTest()  : UnitTest ("Foobar testing") {}

		void runTest()
		{
			beginTest ("Part 1");

			expect (myFoobar.doesSomething());
			expect (myFoobar.doesSomethingElse());

			beginTest ("Part 2");

			expect (myOtherFoobar.doesSomething());
			expect (myOtherFoobar.doesSomethingElse());

			...etc..
		}
	};

	// Creating a static instance will automatically add the instance to the array
	// returned by UnitTest::getAllTests(), so the test will be included when you call
	// UnitTestRunner::runAllTests()
	static MyTest test;
	@endcode

	To run a test, use the UnitTestRunner class.

	@see UnitTestRunner
*/
class JUCE_API  UnitTest
{
public:

	/** Creates a test with the given name. */
	explicit UnitTest (const String& name);

	/** Destructor. */
	virtual ~UnitTest();

	/** Returns the name of the test. */
	const String& getName() const noexcept       { return name; }

	/** Runs the test, using the specified UnitTestRunner.
		You shouldn't need to call this method directly - use
		UnitTestRunner::runTests() instead.
	*/
	void performTest (UnitTestRunner* runner);

	/** Returns the set of all UnitTest objects that currently exist. */
	static Array<UnitTest*>& getAllTests();

	/** You can optionally implement this method to set up your test.
		This method will be called before runTest().
	*/
	virtual void initialise();

	/** You can optionally implement this method to clear up after your test has been run.
		This method will be called after runTest() has returned.
	*/
	virtual void shutdown();

	/** Implement this method in your subclass to actually run your tests.

		The content of your implementation should call beginTest() and expect()
		to perform the tests.
	*/
	virtual void runTest() = 0;

	/** Tells the system that a new subsection of tests is beginning.
		This should be called from your runTest() method, and may be called
		as many times as you like, to demarcate different sets of tests.
	*/
	void beginTest (const String& testName);

	/** Checks that the result of a test is true, and logs this result.

		In your runTest() method, you should call this method for each condition that
		you want to check, e.g.

		@code
		void runTest()
		{
			beginTest ("basic tests");
			expect (x + y == 2);
			expect (getThing() == someThing);
			...etc...
		}
		@endcode

		If testResult is true, a pass is logged; if it's false, a failure is logged.
		If the failure message is specified, it will be written to the log if the test fails.
	*/
	void expect (bool testResult, const String& failureMessage = String::empty);

	/** Compares two values, and if they don't match, prints out a message containing the
		expected and actual result values.
	*/
	template <class ValueType>
	void expectEquals (ValueType actual, ValueType expected, String failureMessage = String::empty)
	{
		const bool result = (actual == expected);

		if (! result)
		{
			if (failureMessage.isNotEmpty())
				failureMessage << " -- ";

			failureMessage << "Expected value: " << expected << ", Actual value: " << actual;
		}

		expect (result, failureMessage);
	}

	/** Writes a message to the test log.
		This can only be called from within your runTest() method.
	*/
	void logMessage (const String& message);

private:

	const String name;
	UnitTestRunner* runner;

	JUCE_DECLARE_NON_COPYABLE (UnitTest);
};

/**
	Runs a set of unit tests.

	You can instantiate one of these objects and use it to invoke tests on a set of
	UnitTest objects.

	By using a subclass of UnitTestRunner, you can intercept logging messages and
	perform custom behaviour when each test completes.

	@see UnitTest
*/
class JUCE_API  UnitTestRunner
{
public:

	/** */
	UnitTestRunner();

	/** Destructor. */
	virtual ~UnitTestRunner();

	/** Runs a set of tests.

		The tests are performed in order, and the results are logged. To run all the
		registered UnitTest objects that exist, use runAllTests().
	*/
	void runTests (const Array<UnitTest*>& tests);

	/** Runs all the UnitTest objects that currently exist.
		This calls runTests() for all the objects listed in UnitTest::getAllTests().
	*/
	void runAllTests();

	/** Sets a flag to indicate whether an assertion should be triggered if a test fails.
		This is true by default.
	*/
	void setAssertOnFailure (bool shouldAssert) noexcept;

	/** Sets a flag to indicate whether successful tests should be logged.
		By default, this is set to false, so that only failures will be displayed in the log.
	*/
	void setPassesAreLogged (bool shouldDisplayPasses) noexcept;

	/** Contains the results of a test.

		One of these objects is instantiated each time UnitTest::beginTest() is called, and
		it contains details of the number of subsequent UnitTest::expect() calls that are
		made.
	*/
	struct TestResult
	{
		/** The main name of this test (i.e. the name of the UnitTest object being run). */
		String unitTestName;
		/** The name of the current subcategory (i.e. the name that was set when UnitTest::beginTest() was called). */
		String subcategoryName;

		/** The number of UnitTest::expect() calls that succeeded. */
		int passes;
		/** The number of UnitTest::expect() calls that failed. */
		int failures;

		/** A list of messages describing the failed tests. */
		StringArray messages;
	};

	/** Returns the number of TestResult objects that have been performed.
		@see getResult
	*/
	int getNumResults() const noexcept;

	/** Returns one of the TestResult objects that describes a test that has been run.
		@see getNumResults
	*/
	const TestResult* getResult (int index) const noexcept;

protected:
	/** Called when the list of results changes.
		You can override this to perform some sort of behaviour when results are added.
	*/
	virtual void resultsUpdated();

	/** Logs a message about the current test progress.
		By default this just writes the message to the Logger class, but you could override
		this to do something else with the data.
	*/
	virtual void logMessage (const String& message);

	/** This can be overridden to let the runner know that it should abort the tests
		as soon as possible, e.g. because the thread needs to stop.
	*/
	virtual bool shouldAbortTests();

private:

	friend class UnitTest;

	UnitTest* currentTest;
	String currentSubCategory;
	OwnedArray <TestResult, CriticalSection> results;
	bool assertOnFailure, logPasses;

	void beginNewTest (UnitTest* test, const String& subCategory);
	void endTest();

	void addPass();
	void addFail (const String& failureMessage);

	JUCE_DECLARE_NON_COPYABLE (UnitTestRunner);
};

#endif   // __JUCE_UNITTEST_JUCEHEADER__

/*** End of inlined file: juce_UnitTest.h ***/


#endif
#ifndef __JUCE_XMLDOCUMENT_JUCEHEADER__

/*** Start of inlined file: juce_XmlDocument.h ***/
#ifndef __JUCE_XMLDOCUMENT_JUCEHEADER__
#define __JUCE_XMLDOCUMENT_JUCEHEADER__

class InputSource;

/**
	Parses a text-based XML document and creates an XmlElement object from it.

	The parser will parse DTDs to load external entities but won't
	check the document for validity against the DTD.

	e.g.
	@code

	XmlDocument myDocument (File ("myfile.xml"));
	XmlElement* mainElement = myDocument.getDocumentElement();

	if (mainElement == nullptr)
	{
		String error = myDocument.getLastParseError();
	}
	else
	{
		..use the element
	}

	@endcode

	Or you can use the static helper methods for quick parsing..

	@code
	XmlElement* xml = XmlDocument::parse (myXmlFile);

	if (xml != nullptr && xml->hasTagName ("foobar"))
	{
		...etc
	@endcode

	@see XmlElement
*/
class JUCE_API  XmlDocument
{
public:

	/** Creates an XmlDocument from the xml text.
		The text doesn't actually get parsed until the getDocumentElement() method is called.
	*/
	XmlDocument (const String& documentText);

	/** Creates an XmlDocument from a file.
		The text doesn't actually get parsed until the getDocumentElement() method is called.
	*/
	XmlDocument (const File& file);

	/** Destructor. */
	~XmlDocument();

	/** Creates an XmlElement object to represent the main document node.

		This method will do the actual parsing of the text, and if there's a
		parse error, it may returns 0 (and you can find out the error using
		the getLastParseError() method).

		See also the parse() methods, which provide a shorthand way to quickly
		parse a file or string.

		@param onlyReadOuterDocumentElement     if true, the parser will only read the
												first section of the file, and will only
												return the outer document element - this
												allows quick checking of large files to
												see if they contain the correct type of
												tag, without having to parse the entire file
		@returns    a new XmlElement which the caller will need to delete, or null if
					there was an error.
		@see getLastParseError
	*/
	XmlElement* getDocumentElement (bool onlyReadOuterDocumentElement = false);

	/** Returns the parsing error that occurred the last time getDocumentElement was called.

		@returns the error, or an empty string if there was no error.
	*/
	const String& getLastParseError() const noexcept;

	/** Sets an input source object to use for parsing documents that reference external entities.

		If the document has been created from a file, this probably won't be needed, but
		if you're parsing some text and there might be a DTD that references external
		files, you may need to create a custom input source that can retrieve the
		other files it needs.

		The object that is passed-in will be deleted automatically when no longer needed.

		@see InputSource
	*/
	void setInputSource (InputSource* newSource) noexcept;

	/** Sets a flag to change the treatment of empty text elements.

		If this is true (the default state), then any text elements that contain only
		whitespace characters will be ingored during parsing. If you need to catch
		whitespace-only text, then you should set this to false before calling the
		getDocumentElement() method.
	*/
	void setEmptyTextElementsIgnored (bool shouldBeIgnored) noexcept;

	/** A handy static method that parses a file.
		This is a shortcut for creating an XmlDocument object and calling getDocumentElement() on it.
		@returns    a new XmlElement which the caller will need to delete, or null if there was an error.
	*/
	static XmlElement* parse (const File& file);

	/** A handy static method that parses some XML data.
		This is a shortcut for creating an XmlDocument object and calling getDocumentElement() on it.
		@returns    a new XmlElement which the caller will need to delete, or null if there was an error.
	*/
	static XmlElement* parse (const String& xmlData);

private:
	String originalText;
	String::CharPointerType input;
	bool outOfData, errorOccurred;

	String lastError, dtdText;
	StringArray tokenisedDTD;
	bool needToLoadDTD, ignoreEmptyTextElements;
	ScopedPointer <InputSource> inputSource;

	void setLastError (const String& desc, bool carryOn);
	void skipHeader();
	void skipNextWhiteSpace();
	juce_wchar readNextChar() noexcept;
	XmlElement* readNextElement (bool alsoParseSubElements);
	void readChildElements (XmlElement* parent);
	int findNextTokenLength() noexcept;
	void readQuotedString (String& result);
	void readEntity (String& result);

	String getFileContents (const String& filename) const;
	String expandEntity (const String& entity);
	String expandExternalEntity (const String& entity);
	String getParameterEntity (const String& entity);

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (XmlDocument);
};

#endif   // __JUCE_XMLDOCUMENT_JUCEHEADER__

/*** End of inlined file: juce_XmlDocument.h ***/


#endif
#ifndef __JUCE_XMLELEMENT_JUCEHEADER__

#endif
#ifndef __JUCE_GZIPCOMPRESSOROUTPUTSTREAM_JUCEHEADER__

/*** Start of inlined file: juce_GZIPCompressorOutputStream.h ***/
#ifndef __JUCE_GZIPCOMPRESSOROUTPUTSTREAM_JUCEHEADER__
#define __JUCE_GZIPCOMPRESSOROUTPUTSTREAM_JUCEHEADER__

/**
	A stream which uses zlib to compress the data written into it.

	Important note: When you call flush() on a GZIPCompressorOutputStream,
	the gzip data is closed - this means that no more data can be written to
	it, and any subsequent attempts to call write() will cause an assertion.

	@see GZIPDecompressorInputStream
*/
class JUCE_API  GZIPCompressorOutputStream  : public OutputStream
{
public:

	/** Creates a compression stream.

		@param destStream                       the stream into which the compressed data should
												be written
		@param compressionLevel                 how much to compress the data, between 1 and 9, where
												1 is the fastest/lowest compression, and 9 is the
												slowest/highest compression. Any value outside this range
												indicates that a default compression level should be used.
		@param deleteDestStreamWhenDestroyed    whether or not to delete the destStream object when
												this stream is destroyed
		@param windowBits                       this is used internally to change the window size used
												by zlib - leave it as 0 unless you specifically need to set
												its value for some reason
	*/
	GZIPCompressorOutputStream (OutputStream* destStream,
								int compressionLevel = 0,
								bool deleteDestStreamWhenDestroyed = false,
								int windowBits = 0);

	/** Destructor. */
	~GZIPCompressorOutputStream();

	/** Flushes and closes the stream.
		Note that unlike most streams, when you call flush() on a GZIPCompressorOutputStream,
		the stream is closed - this means that no more data can be written to it, and any
		subsequent attempts to call write() will cause an assertion.
	*/
	void flush();

	int64 getPosition();
	bool setPosition (int64 newPosition);
	bool write (const void* destBuffer, int howMany);

	/** These are preset values that can be used for the constructor's windowBits paramter.
		For more info about this, see the zlib documentation for its windowBits parameter.
	*/
	enum WindowBitsValues
	{
		windowBitsRaw = -15,
		windowBitsGZIP = 15 + 16
	};

private:

	OptionalScopedPointer<OutputStream> destStream;

	class GZIPCompressorHelper;
	friend class ScopedPointer <GZIPCompressorHelper>;
	ScopedPointer <GZIPCompressorHelper> helper;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GZIPCompressorOutputStream);
};

#endif   // __JUCE_GZIPCOMPRESSOROUTPUTSTREAM_JUCEHEADER__

/*** End of inlined file: juce_GZIPCompressorOutputStream.h ***/


#endif
#ifndef __JUCE_GZIPDECOMPRESSORINPUTSTREAM_JUCEHEADER__

/*** Start of inlined file: juce_GZIPDecompressorInputStream.h ***/
#ifndef __JUCE_GZIPDECOMPRESSORINPUTSTREAM_JUCEHEADER__
#define __JUCE_GZIPDECOMPRESSORINPUTSTREAM_JUCEHEADER__

/**
	This stream will decompress a source-stream using zlib.

	Tip: if you're reading lots of small items from one of these streams, you
		 can increase the performance enormously by passing it through a
		 BufferedInputStream, so that it has to read larger blocks less often.

	@see GZIPCompressorOutputStream
*/
class JUCE_API  GZIPDecompressorInputStream  : public InputStream
{
public:

	/** Creates a decompressor stream.

		@param sourceStream                 the stream to read from
		@param deleteSourceWhenDestroyed    whether or not to delete the source stream
											when this object is destroyed
		@param noWrap                       this is used internally by the ZipFile class
											and should be ignored by user applications
		@param uncompressedStreamLength     if the creator knows the length that the
											uncompressed stream will be, then it can supply this
											value, which will be returned by getTotalLength()
	*/
	GZIPDecompressorInputStream (InputStream* sourceStream,
								 bool deleteSourceWhenDestroyed,
								 bool noWrap = false,
								 int64 uncompressedStreamLength = -1);

	/** Creates a decompressor stream.

		@param sourceStream     the stream to read from - the source stream must not be
								deleted until this object has been destroyed
	*/
	GZIPDecompressorInputStream (InputStream& sourceStream);

	/** Destructor. */
	~GZIPDecompressorInputStream();

	int64 getPosition();
	bool setPosition (int64 pos);
	int64 getTotalLength();
	bool isExhausted();
	int read (void* destBuffer, int maxBytesToRead);

private:
	OptionalScopedPointer<InputStream> sourceStream;
	const int64 uncompressedStreamLength;
	const bool noWrap;
	bool isEof;
	int activeBufferSize;
	int64 originalSourcePos, currentPos;
	HeapBlock <uint8> buffer;

	class GZIPDecompressHelper;
	friend class ScopedPointer <GZIPDecompressHelper>;
	ScopedPointer <GZIPDecompressHelper> helper;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GZIPDecompressorInputStream);
};

#endif   // __JUCE_GZIPDECOMPRESSORINPUTSTREAM_JUCEHEADER__

/*** End of inlined file: juce_GZIPDecompressorInputStream.h ***/


#endif
#ifndef __JUCE_ZIPFILE_JUCEHEADER__

/*** Start of inlined file: juce_ZipFile.h ***/
#ifndef __JUCE_ZIPFILE_JUCEHEADER__
#define __JUCE_ZIPFILE_JUCEHEADER__

/**
	Decodes a ZIP file from a stream.

	This can enumerate the items in a ZIP file and can create suitable stream objects
	to read each one.
*/
class JUCE_API  ZipFile
{
public:
	/** Creates a ZipFile based for a file. */
	ZipFile (const File& file);

	/** Creates a ZipFile for a given stream.

		@param inputStream                  the stream to read from
		@param deleteStreamWhenDestroyed    if set to true, the object passed-in
											will be deleted when this ZipFile object is deleted
	*/
	ZipFile (InputStream* inputStream, bool deleteStreamWhenDestroyed);

	/** Creates a ZipFile for a given stream.
		The stream will not be owned or deleted by this class - if you want the ZipFile to
		manage the stream's lifetime, use the other constructor.
	*/
	ZipFile (InputStream& inputStream);

	/** Creates a ZipFile for an input source.

		The inputSource object will be owned by the zip file, which will delete
		it later when not needed.
	*/
	ZipFile (InputSource* inputSource);

	/** Destructor. */
	~ZipFile();

	/**
		Contains information about one of the entries in a ZipFile.

		@see ZipFile::getEntry
	*/
	struct ZipEntry
	{
		/** The name of the file, which may also include a partial pathname. */
		String filename;

		/** The file's original size. */
		unsigned int uncompressedSize;

		/** The last time the file was modified. */
		Time fileTime;
	};

	/** Returns the number of items in the zip file. */
	int getNumEntries() const noexcept;

	/** Returns a structure that describes one of the entries in the zip file.

		This may return zero if the index is out of range.

		@see ZipFile::ZipEntry
	*/
	const ZipEntry* getEntry (int index) const noexcept;

	/** Returns the index of the first entry with a given filename.

		This uses a case-sensitive comparison to look for a filename in the
		list of entries. It might return -1 if no match is found.

		@see ZipFile::ZipEntry
	*/
	int getIndexOfFileName (const String& fileName) const noexcept;

	/** Returns a structure that describes one of the entries in the zip file.

		This uses a case-sensitive comparison to look for a filename in the
		list of entries. It might return 0 if no match is found.

		@see ZipFile::ZipEntry
	*/
	const ZipEntry* getEntry (const String& fileName) const noexcept;

	/** Sorts the list of entries, based on the filename.
	*/
	void sortEntriesByFilename();

	/** Creates a stream that can read from one of the zip file's entries.

		The stream that is returned must be deleted by the caller (and
		zero might be returned if a stream can't be opened for some reason).

		The stream must not be used after the ZipFile object that created
		has been deleted.
	*/
	InputStream* createStreamForEntry (int index);

	/** Creates a stream that can read from one of the zip file's entries.

		The stream that is returned must be deleted by the caller (and
		zero might be returned if a stream can't be opened for some reason).

		The stream must not be used after the ZipFile object that created
		has been deleted.
	*/
	InputStream* createStreamForEntry (ZipEntry& entry);

	/** Uncompresses all of the files in the zip file.

		This will expand all the entries into a target directory. The relative
		paths of the entries are used.

		@param targetDirectory      the root folder to uncompress to
		@param shouldOverwriteFiles whether to overwrite existing files with similarly-named ones
		@returns success if the file is successfully unzipped
	*/
	Result uncompressTo (const File& targetDirectory,
						 bool shouldOverwriteFiles = true);

	/** Uncompresses one of the entries from the zip file.

		This will expand the entry and write it in a target directory. The entry's path is used to
		determine which subfolder of the target should contain the new file.

		@param index                the index of the entry to uncompress - this must be a valid index
									between 0 and (getNumEntries() - 1).
		@param targetDirectory      the root folder to uncompress into
		@param shouldOverwriteFiles whether to overwrite existing files with similarly-named ones
		@returns success if all the files are successfully unzipped
	*/
	Result uncompressEntry (int index,
							const File& targetDirectory,
							bool shouldOverwriteFiles = true);

	/** Used to create a new zip file.

		Create a ZipFile::Builder object, and call its addFile() method to add some files,
		then you can write it to a stream with write().

		Currently this just stores the files with no compression.. That will be added
		soon!
	*/
	class Builder
	{
	public:
		Builder();
		~Builder();

		/** Adds a file while should be added to the archive.
			The file isn't read immediately, all the files will be read later when the writeToStream()
			method is called.

			The compressionLevel can be between 0 (no compression), and 9 (maximum compression).
			If the storedPathName parameter is specified, you can customise the partial pathname that
			will be stored for this file.
		*/
		void addFile (const File& fileToAdd, int compressionLevel,
					  const String& storedPathName = String::empty);

		/** Generates the zip file, writing it to the specified stream. */
		bool writeToStream (OutputStream& target) const;

	private:
		class Item;
		friend class OwnedArray<Item>;
		OwnedArray<Item> items;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Builder);
	};

private:

	class ZipInputStream;
	class ZipEntryHolder;
	friend class ZipInputStream;
	friend class ZipEntryHolder;

	OwnedArray <ZipEntryHolder> entries;
	CriticalSection lock;
	InputStream* inputStream;
	ScopedPointer <InputStream> streamToDelete;
	ScopedPointer <InputSource> inputSource;

   #if JUCE_DEBUG
	struct OpenStreamCounter
	{
		OpenStreamCounter() : numOpenStreams (0) {}
		~OpenStreamCounter();

		int numOpenStreams;
	};

	OpenStreamCounter streamCounter;
   #endif

	void init();

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZipFile);
};

#endif   // __JUCE_ZIPFILE_JUCEHEADER__

/*** End of inlined file: juce_ZipFile.h ***/


#endif
// END_AUTOINCLUDE

}

#if JUCE_MSVC
 #pragma warning (pop)
 #pragma pack (pop)
#endif

#endif   // __JUCE_CORE_JUCEHEADER__

/*** End of inlined file: juce_core.h ***/

namespace juce
{

// START_AUTOINCLUDE encryption, hashing
#ifndef __JUCE_BLOWFISH_JUCEHEADER__

/*** Start of inlined file: juce_BlowFish.h ***/
#ifndef __JUCE_BLOWFISH_JUCEHEADER__
#define __JUCE_BLOWFISH_JUCEHEADER__

/**
	BlowFish encryption class.

*/
class JUCE_API  BlowFish
{
public:

	/** Creates an object that can encode/decode based on the specified key.

		The key data can be up to 72 bytes long.
	*/
	BlowFish (const void* keyData, int keyBytes);

	/** Creates a copy of another blowfish object. */
	BlowFish (const BlowFish& other);

	/** Copies another blowfish object. */
	BlowFish& operator= (const BlowFish& other) noexcept;

	/** Destructor. */
	~BlowFish() noexcept;

	/** Encrypts a pair of 32-bit integers. */
	void encrypt (uint32& data1, uint32& data2) const noexcept;

	/** Decrypts a pair of 32-bit integers. */
	void decrypt (uint32& data1, uint32& data2) const noexcept;

private:

	uint32 p[18];
	HeapBlock <uint32> s[4];

	uint32 F (uint32) const noexcept;

	JUCE_LEAK_DETECTOR (BlowFish);
};

#endif   // __JUCE_BLOWFISH_JUCEHEADER__

/*** End of inlined file: juce_BlowFish.h ***/


#endif
#ifndef __JUCE_PRIMES_JUCEHEADER__

/*** Start of inlined file: juce_Primes.h ***/
#ifndef __JUCE_PRIMES_JUCEHEADER__
#define __JUCE_PRIMES_JUCEHEADER__

/**
	Prime number creation class.

	This class contains static methods for generating and testing prime numbers.

	@see BigInteger
*/
class JUCE_API  Primes
{
public:

	/** Creates a random prime number with a given bit-length.

		The certainty parameter specifies how many iterations to use when testing
		for primality. A safe value might be anything over about 20-30.

		The randomSeeds parameter lets you optionally pass it a set of values with
		which to seed the random number generation, improving the security of the
		keys generated.
	*/
	static BigInteger createProbablePrime (int bitLength,
										   int certainty,
										   const int* randomSeeds = 0,
										   int numRandomSeeds = 0);

	/** Tests a number to see if it's prime.

		This isn't a bulletproof test, it uses a Miller-Rabin test to determine
		whether the number is prime.

		The certainty parameter specifies how many iterations to use when testing - a
		safe value might be anything over about 20-30.
	*/
	static bool isProbablyPrime (const BigInteger& number, int certainty);

private:
	Primes();

	JUCE_DECLARE_NON_COPYABLE (Primes);
};

#endif   // __JUCE_PRIMES_JUCEHEADER__

/*** End of inlined file: juce_Primes.h ***/


#endif
#ifndef __JUCE_RSAKEY_JUCEHEADER__

/*** Start of inlined file: juce_RSAKey.h ***/
#ifndef __JUCE_RSAKEY_JUCEHEADER__
#define __JUCE_RSAKEY_JUCEHEADER__

/**
	RSA public/private key-pair encryption class.

	An object of this type makes up one half of a public/private RSA key pair. Use the
	createKeyPair() method to create a matching pair for encoding/decoding.
*/
class JUCE_API  RSAKey
{
public:

	/** Creates a null key object.

		Initialise a pair of objects for use with the createKeyPair() method.
	*/
	RSAKey();

	/** Loads a key from an encoded string representation.

		This reloads a key from a string created by the toString() method.
	*/
	explicit RSAKey (const String& stringRepresentation);

	/** Destructor. */
	~RSAKey();

	bool operator== (const RSAKey& other) const noexcept;
	bool operator!= (const RSAKey& other) const noexcept;

	/** Turns the key into a string representation.

		This can be reloaded using the constructor that takes a string.
	*/
	String toString() const;

	/** Encodes or decodes a value.

		Call this on the public key object to encode some data, then use the matching
		private key object to decode it.

		Returns false if the operation couldn't be completed, e.g. if this key hasn't been
		initialised correctly.

		NOTE: This method dumbly applies this key to this data. If you encode some data
		and then try to decode it with a key that doesn't match, this method will still
		happily do its job and return true, but the result won't be what you were expecting.
		It's your responsibility to check that the result is what you wanted.
	*/
	bool applyToValue (BigInteger& value) const;

	/** Creates a public/private key-pair.

		Each key will perform one-way encryption that can only be reversed by
		using the other key.

		The numBits parameter specifies the size of key, e.g. 128, 256, 512 bit. Bigger
		sizes are more secure, but this method will take longer to execute.

		The randomSeeds parameter lets you optionally pass it a set of values with
		which to seed the random number generation, improving the security of the
		keys generated. If you supply these, make sure you provide more than 2 values,
		and the more your provide, the better the security.
	*/
	static void createKeyPair (RSAKey& publicKey,
							   RSAKey& privateKey,
							   int numBits,
							   const int* randomSeeds = nullptr,
							   int numRandomSeeds = 0);

protected:

	BigInteger part1, part2;

private:

	static BigInteger findBestCommonDivisor (const BigInteger& p, const BigInteger& q);

	JUCE_LEAK_DETECTOR (RSAKey);
};

#endif   // __JUCE_RSAKEY_JUCEHEADER__

/*** End of inlined file: juce_RSAKey.h ***/


#endif
#ifndef __JUCE_MD5_JUCEHEADER__

/*** Start of inlined file: juce_MD5.h ***/
#ifndef __JUCE_MD5_JUCEHEADER__
#define __JUCE_MD5_JUCEHEADER__

/**
	MD5 checksum class.

	Create one of these with a block of source data or a stream, and it calculates
	the MD5 checksum of that data.

	You can then retrieve this checksum as a 16-byte block, or as a hex string.
	@see SHA256
*/
class JUCE_API  MD5
{
public:

	/** Creates a null MD5 object. */
	MD5() noexcept;

	/** Creates a copy of another MD5. */
	MD5 (const MD5& other) noexcept;

	/** Copies another MD5. */
	MD5& operator= (const MD5& other) noexcept;

	/** Creates a checksum for a block of binary data. */
	explicit MD5 (const MemoryBlock& data) noexcept;

	/** Creates a checksum for a block of binary data. */
	MD5 (const void* data, size_t numBytes) noexcept;

	/** Creates a checksum for the input from a stream.

		This will read up to the given number of bytes from the stream, and produce the
		checksum of that. If the number of bytes to read is negative, it'll read
		until the stream is exhausted.
	*/
	MD5 (InputStream& input, int64 numBytesToRead = -1);

	/** Creates a checksum for a file. */
	explicit MD5 (const File& file);

	/** Creates a checksum from a UTF-8 buffer.
		E.g.
		@code MD5 checksum (myString.toUTF8());
		@endcode
	*/
	explicit MD5 (const CharPointer_UTF8& utf8Text) noexcept;

	/** Destructor. */
	~MD5() noexcept;

	/** Returns the checksum as a 16-byte block of data. */
	MemoryBlock getRawChecksumData() const;

	/** Returns a pointer to the 16-byte array of result data. */
	const uint8* getChecksumDataArray() const noexcept          { return result; }

	/** Returns the checksum as a 32-digit hex string. */
	String toHexString() const;

	/** Creates an MD5 from a little-endian UTF-32 encoded string.

		Note that this method is provided for backwards-compatibility with the old
		version of this class, which had a constructor that took a string and performed
		this operation on it. In new code, you shouldn't use this, and are recommended to
		use the constructor that takes a CharPointer_UTF8 instead.
	*/
	static MD5 fromUTF32 (const String&);

	bool operator== (const MD5&) const noexcept;
	bool operator!= (const MD5&) const noexcept;

private:

	uint8 result [16];

	void processData (const void*, size_t) noexcept;
	void processStream (InputStream&, int64);

	JUCE_LEAK_DETECTOR (MD5);
};

#endif   // __JUCE_MD5_JUCEHEADER__

/*** End of inlined file: juce_MD5.h ***/


#endif
#ifndef __JUCE_SHA256_JUCEHEADER__

/*** Start of inlined file: juce_SHA256.h ***/
#ifndef __JUCE_SHA256_JUCEHEADER__
#define __JUCE_SHA256_JUCEHEADER__

/**
	SHA-256 secure hash generator.

	Create one of these objects from a block of source data or a stream, and it
	calculates the SHA-256 hash of that data.

	You can retrieve the hash as a raw 32-byte block, or as a 64-digit hex string.
	@see MD5
*/
class JUCE_API  SHA256
{
public:

	/** Creates an empty SHA256 object.
		The default constructor just creates a hash filled with zeros. (This is not
		equal to the hash of an empty block of data).
	*/
	SHA256() noexcept;

	/** Destructor. */
	~SHA256() noexcept;

	/** Creates a copy of another SHA256. */
	SHA256 (const SHA256& other) noexcept;

	/** Copies another SHA256. */
	SHA256& operator= (const SHA256& other) noexcept;

	/** Creates a hash from a block of raw data. */
	explicit SHA256 (const MemoryBlock& data);

	/** Creates a hash from a block of raw data. */
	SHA256 (const void* data, size_t numBytes);

	/** Creates a hash from the contents of a stream.

		This will read from the stream until the stream is exhausted, or until
		maxBytesToRead bytes have been read. If maxBytesToRead is negative, the entire
		stream will be read.
	*/
	SHA256 (InputStream& input, int64 maxBytesToRead = -1);

	/** Reads a file and generates the hash of its contents.
		If the file can't be opened, the hash will be left uninitialised (i.e. full
		of zeros).
	*/
	explicit SHA256 (const File& file);

	/** Creates a checksum from a UTF-8 buffer.
		E.g.
		@code SHA256 checksum (myString.toUTF8());
		@endcode
	*/
	explicit SHA256 (const CharPointer_UTF8& utf8Text) noexcept;

	/** Returns the hash as a 32-byte block of data. */
	MemoryBlock getRawData() const;

	/** Returns the checksum as a 64-digit hex string. */
	String toHexString() const;

	bool operator== (const SHA256&) const noexcept;
	bool operator!= (const SHA256&) const noexcept;

private:

	uint8 result [32];
	void process (const void*, size_t);

	JUCE_LEAK_DETECTOR (SHA256);
};

#endif   // __JUCE_SHA256_JUCEHEADER__

/*** End of inlined file: juce_SHA256.h ***/


#endif
// END_AUTOINCLUDE

}

#endif   // __JUCE_CRYPTOGRAPHY_JUCEHEADER__

/*** End of inlined file: juce_cryptography.h ***/

namespace juce
{

// START_AUTOINCLUDE encryption/*.cpp, hashing/*.cpp

/*** Start of inlined file: juce_BlowFish.cpp ***/
BlowFish::BlowFish (const void* const keyData, const int keyBytes)
{
	jassert (keyData != nullptr);
	jassert (keyBytes > 0);

	static const uint32 initialPValues [18] =
	{
		0x243f6a88, 0x85a308d3, 0x13198a2e, 0x03707344, 0xa4093822, 0x299f31d0, 0x082efa98, 0xec4e6c89,
		0x452821e6, 0x38d01377, 0xbe5466cf, 0x34e90c6c, 0xc0ac29b7, 0xc97c50dd, 0x3f84d5b5, 0xb5470917,
		0x9216d5d9, 0x8979fb1b
	};

	static const uint32 initialSValues [4 * 256] =
	{
		0xd1310ba6, 0x98dfb5ac, 0x2ffd72db, 0xd01adfb7, 0xb8e1afed, 0x6a267e96, 0xba7c9045, 0xf12c7f99,
		0x24a19947, 0xb3916cf7, 0x0801f2e2, 0x858efc16, 0x636920d8, 0x71574e69, 0xa458fea3, 0xf4933d7e,
		0x0d95748f, 0x728eb658, 0x718bcd58, 0x82154aee, 0x7b54a41d, 0xc25a59b5, 0x9c30d539, 0x2af26013,
		0xc5d1b023, 0x286085f0, 0xca417918, 0xb8db38ef, 0x8e79dcb0, 0x603a180e, 0x6c9e0e8b, 0xb01e8a3e,
		0xd71577c1, 0xbd314b27, 0x78af2fda, 0x55605c60, 0xe65525f3, 0xaa55ab94, 0x57489862, 0x63e81440,
		0x55ca396a, 0x2aab10b6, 0xb4cc5c34, 0x1141e8ce, 0xa15486af, 0x7c72e993, 0xb3ee1411, 0x636fbc2a,
		0x2ba9c55d, 0x741831f6, 0xce5c3e16, 0x9b87931e, 0xafd6ba33, 0x6c24cf5c, 0x7a325381, 0x28958677,
		0x3b8f4898, 0x6b4bb9af, 0xc4bfe81b, 0x66282193, 0x61d809cc, 0xfb21a991, 0x487cac60, 0x5dec8032,
		0xef845d5d, 0xe98575b1, 0xdc262302, 0xeb651b88, 0x23893e81, 0xd396acc5, 0x0f6d6ff3, 0x83f44239,
		0x2e0b4482, 0xa4842004, 0x69c8f04a, 0x9e1f9b5e, 0x21c66842, 0xf6e96c9a, 0x670c9c61, 0xabd388f0,
		0x6a51a0d2, 0xd8542f68, 0x960fa728, 0xab5133a3, 0x6eef0b6c, 0x137a3be4, 0xba3bf050, 0x7efb2a98,
		0xa1f1651d, 0x39af0176, 0x66ca593e, 0x82430e88, 0x8cee8619, 0x456f9fb4, 0x7d84a5c3, 0x3b8b5ebe,
		0xe06f75d8, 0x85c12073, 0x401a449f, 0x56c16aa6, 0x4ed3aa62, 0x363f7706, 0x1bfedf72, 0x429b023d,
		0x37d0d724, 0xd00a1248, 0xdb0fead3, 0x49f1c09b, 0x075372c9, 0x80991b7b, 0x25d479d8, 0xf6e8def7,
		0xe3fe501a, 0xb6794c3b, 0x976ce0bd, 0x04c006ba, 0xc1a94fb6, 0x409f60c4, 0x5e5c9ec2, 0x196a2463,
		0x68fb6faf, 0x3e6c53b5, 0x1339b2eb, 0x3b52ec6f, 0x6dfc511f, 0x9b30952c, 0xcc814544, 0xaf5ebd09,
		0xbee3d004, 0xde334afd, 0x660f2807, 0x192e4bb3, 0xc0cba857, 0x45c8740f, 0xd20b5f39, 0xb9d3fbdb,
		0x5579c0bd, 0x1a60320a, 0xd6a100c6, 0x402c7279, 0x679f25fe, 0xfb1fa3cc, 0x8ea5e9f8, 0xdb3222f8,
		0x3c7516df, 0xfd616b15, 0x2f501ec8, 0xad0552ab, 0x323db5fa, 0xfd238760, 0x53317b48, 0x3e00df82,
		0x9e5c57bb, 0xca6f8ca0, 0x1a87562e, 0xdf1769db, 0xd542a8f6, 0x287effc3, 0xac6732c6, 0x8c4f5573,
		0x695b27b0, 0xbbca58c8, 0xe1ffa35d, 0xb8f011a0, 0x10fa3d98, 0xfd2183b8, 0x4afcb56c, 0x2dd1d35b,
		0x9a53e479, 0xb6f84565, 0xd28e49bc, 0x4bfb9790, 0xe1ddf2da, 0xa4cb7e33, 0x62fb1341, 0xcee4c6e8,
		0xef20cada, 0x36774c01, 0xd07e9efe, 0x2bf11fb4, 0x95dbda4d, 0xae909198, 0xeaad8e71, 0x6b93d5a0,
		0xd08ed1d0, 0xafc725e0, 0x8e3c5b2f, 0x8e7594b7, 0x8ff6e2fb, 0xf2122b64, 0x8888b812, 0x900df01c,
		0x4fad5ea0, 0x688fc31c, 0xd1cff191, 0xb3a8c1ad, 0x2f2f2218, 0xbe0e1777, 0xea752dfe, 0x8b021fa1,
		0xe5a0cc0f, 0xb56f74e8, 0x18acf3d6, 0xce89e299, 0xb4a84fe0, 0xfd13e0b7, 0x7cc43b81, 0xd2ada8d9,
		0x165fa266, 0x80957705, 0x93cc7314, 0x211a1477, 0xe6ad2065, 0x77b5fa86, 0xc75442f5, 0xfb9d35cf,
		0xebcdaf0c, 0x7b3e89a0, 0xd6411bd3, 0xae1e7e49, 0x00250e2d, 0x2071b35e, 0x226800bb, 0x57b8e0af,
		0x2464369b, 0xf009b91e, 0x5563911d, 0x59dfa6aa, 0x78c14389, 0xd95a537f, 0x207d5ba2, 0x02e5b9c5,
		0x83260376, 0x6295cfa9, 0x11c81968, 0x4e734a41, 0xb3472dca, 0x7b14a94a, 0x1b510052, 0x9a532915,
		0xd60f573f, 0xbc9bc6e4, 0x2b60a476, 0x81e67400, 0x08ba6fb5, 0x571be91f, 0xf296ec6b, 0x2a0dd915,
		0xb6636521, 0xe7b9f9b6, 0xff34052e, 0xc5855664, 0x53b02d5d, 0xa99f8fa1, 0x08ba4799, 0x6e85076a,
		0x4b7a70e9, 0xb5b32944, 0xdb75092e, 0xc4192623, 0xad6ea6b0, 0x49a7df7d, 0x9cee60b8, 0x8fedb266,
		0xecaa8c71, 0x699a17ff, 0x5664526c, 0xc2b19ee1, 0x193602a5, 0x75094c29, 0xa0591340, 0xe4183a3e,
		0x3f54989a, 0x5b429d65, 0x6b8fe4d6, 0x99f73fd6, 0xa1d29c07, 0xefe830f5, 0x4d2d38e6, 0xf0255dc1,
		0x4cdd2086, 0x8470eb26, 0x6382e9c6, 0x021ecc5e, 0x09686b3f, 0x3ebaefc9, 0x3c971814, 0x6b6a70a1,
		0x687f3584, 0x52a0e286, 0xb79c5305, 0xaa500737, 0x3e07841c, 0x7fdeae5c, 0x8e7d44ec, 0x5716f2b8,
		0xb03ada37, 0xf0500c0d, 0xf01c1f04, 0x0200b3ff, 0xae0cf51a, 0x3cb574b2, 0x25837a58, 0xdc0921bd,
		0xd19113f9, 0x7ca92ff6, 0x94324773, 0x22f54701, 0x3ae5e581, 0x37c2dadc, 0xc8b57634, 0x9af3dda7,
		0xa9446146, 0x0fd0030e, 0xecc8c73e, 0xa4751e41, 0xe238cd99, 0x3bea0e2f, 0x3280bba1, 0x183eb331,
		0x4e548b38, 0x4f6db908, 0x6f420d03, 0xf60a04bf, 0x2cb81290, 0x24977c79, 0x5679b072, 0xbcaf89af,
		0xde9a771f, 0xd9930810, 0xb38bae12, 0xdccf3f2e, 0x5512721f, 0x2e6b7124, 0x501adde6, 0x9f84cd87,
		0x7a584718, 0x7408da17, 0xbc9f9abc, 0xe94b7d8c, 0xec7aec3a, 0xdb851dfa, 0x63094366, 0xc464c3d2,
		0xef1c1847, 0x3215d908, 0xdd433b37, 0x24c2ba16, 0x12a14d43, 0x2a65c451, 0x50940002, 0x133ae4dd,
		0x71dff89e, 0x10314e55, 0x81ac77d6, 0x5f11199b, 0x043556f1, 0xd7a3c76b, 0x3c11183b, 0x5924a509,
		0xf28fe6ed, 0x97f1fbfa, 0x9ebabf2c, 0x1e153c6e, 0x86e34570, 0xeae96fb1, 0x860e5e0a, 0x5a3e2ab3,
		0x771fe71c, 0x4e3d06fa, 0x2965dcb9, 0x99e71d0f, 0x803e89d6, 0x5266c825, 0x2e4cc978, 0x9c10b36a,
		0xc6150eba, 0x94e2ea78, 0xa5fc3c53, 0x1e0a2df4, 0xf2f74ea7, 0x361d2b3d, 0x1939260f, 0x19c27960,
		0x5223a708, 0xf71312b6, 0xebadfe6e, 0xeac31f66, 0xe3bc4595, 0xa67bc883, 0xb17f37d1, 0x018cff28,
		0xc332ddef, 0xbe6c5aa5, 0x65582185, 0x68ab9802, 0xeecea50f, 0xdb2f953b, 0x2aef7dad, 0x5b6e2f84,
		0x1521b628, 0x29076170, 0xecdd4775, 0x619f1510, 0x13cca830, 0xeb61bd96, 0x0334fe1e, 0xaa0363cf,
		0xb5735c90, 0x4c70a239, 0xd59e9e0b, 0xcbaade14, 0xeecc86bc, 0x60622ca7, 0x9cab5cab, 0xb2f3846e,
		0x648b1eaf, 0x19bdf0ca, 0xa02369b9, 0x655abb50, 0x40685a32, 0x3c2ab4b3, 0x319ee9d5, 0xc021b8f7,
		0x9b540b19, 0x875fa099, 0x95f7997e, 0x623d7da8, 0xf837889a, 0x97e32d77, 0x11ed935f, 0x16681281,
		0x0e358829, 0xc7e61fd6, 0x96dedfa1, 0x7858ba99, 0x57f584a5, 0x1b227263, 0x9b83c3ff, 0x1ac24696,
		0xcdb30aeb, 0x532e3054, 0x8fd948e4, 0x6dbc3128, 0x58ebf2ef, 0x34c6ffea, 0xfe28ed61, 0xee7c3c73,
		0x5d4a14d9, 0xe864b7e3, 0x42105d14, 0x203e13e0, 0x45eee2b6, 0xa3aaabea, 0xdb6c4f15, 0xfacb4fd0,
		0xc742f442, 0xef6abbb5, 0x654f3b1d, 0x41cd2105, 0xd81e799e, 0x86854dc7, 0xe44b476a, 0x3d816250,
		0xcf62a1f2, 0x5b8d2646, 0xfc8883a0, 0xc1c7b6a3, 0x7f1524c3, 0x69cb7492, 0x47848a0b, 0x5692b285,
		0x095bbf00, 0xad19489d, 0x1462b174, 0x23820e00, 0x58428d2a, 0x0c55f5ea, 0x1dadf43e, 0x233f7061,
		0x3372f092, 0x8d937e41, 0xd65fecf1, 0x6c223bdb, 0x7cde3759, 0xcbee7460, 0x4085f2a7, 0xce77326e,
		0xa6078084, 0x19f8509e, 0xe8efd855, 0x61d99735, 0xa969a7aa, 0xc50c06c2, 0x5a04abfc, 0x800bcadc,
		0x9e447a2e, 0xc3453484, 0xfdd56705, 0x0e1e9ec9, 0xdb73dbd3, 0x105588cd, 0x675fda79, 0xe3674340,
		0xc5c43465, 0x713e38d8, 0x3d28f89e, 0xf16dff20, 0x153e21e7, 0x8fb03d4a, 0xe6e39f2b, 0xdb83adf7,
		0xe93d5a68, 0x948140f7, 0xf64c261c, 0x94692934, 0x411520f7, 0x7602d4f7, 0xbcf46b2e, 0xd4a20068,
		0xd4082471, 0x3320f46a, 0x43b7d4b7, 0x500061af, 0x1e39f62e, 0x97244546, 0x14214f74, 0xbf8b8840,
		0x4d95fc1d, 0x96b591af, 0x70f4ddd3, 0x66a02f45, 0xbfbc09ec, 0x03bd9785, 0x7fac6dd0, 0x31cb8504,
		0x96eb27b3, 0x55fd3941, 0xda2547e6, 0xabca0a9a, 0x28507825, 0x530429f4, 0x0a2c86da, 0xe9b66dfb,
		0x68dc1462, 0xd7486900, 0x680ec0a4, 0x27a18dee, 0x4f3ffea2, 0xe887ad8c, 0xb58ce006, 0x7af4d6b6,
		0xaace1e7c, 0xd3375fec, 0xce78a399, 0x406b2a42, 0x20fe9e35, 0xd9f385b9, 0xee39d7ab, 0x3b124e8b,
		0x1dc9faf7, 0x4b6d1856, 0x26a36631, 0xeae397b2, 0x3a6efa74, 0xdd5b4332, 0x6841e7f7, 0xca7820fb,
		0xfb0af54e, 0xd8feb397, 0x454056ac, 0xba489527, 0x55533a3a, 0x20838d87, 0xfe6ba9b7, 0xd096954b,
		0x55a867bc, 0xa1159a58, 0xcca92963, 0x99e1db33, 0xa62a4a56, 0x3f3125f9, 0x5ef47e1c, 0x9029317c,
		0xfdf8e802, 0x04272f70, 0x80bb155c, 0x05282ce3, 0x95c11548, 0xe4c66d22, 0x48c1133f, 0xc70f86dc,
		0x07f9c9ee, 0x41041f0f, 0x404779a4, 0x5d886e17, 0x325f51eb, 0xd59bc0d1, 0xf2bcc18f, 0x41113564,
		0x257b7834, 0x602a9c60, 0xdff8e8a3, 0x1f636c1b, 0x0e12b4c2, 0x02e1329e, 0xaf664fd1, 0xcad18115,
		0x6b2395e0, 0x333e92e1, 0x3b240b62, 0xeebeb922, 0x85b2a20e, 0xe6ba0d99, 0xde720c8c, 0x2da2f728,
		0xd0127845, 0x95b794fd, 0x647d0862, 0xe7ccf5f0, 0x5449a36f, 0x877d48fa, 0xc39dfd27, 0xf33e8d1e,
		0x0a476341, 0x992eff74, 0x3a6f6eab, 0xf4f8fd37, 0xa812dc60, 0xa1ebddf8, 0x991be14c, 0xdb6e6b0d,
		0xc67b5510, 0x6d672c37, 0x2765d43b, 0xdcd0e804, 0xf1290dc7, 0xcc00ffa3, 0xb5390f92, 0x690fed0b,
		0x667b9ffb, 0xcedb7d9c, 0xa091cf0b, 0xd9155ea3, 0xbb132f88, 0x515bad24, 0x7b9479bf, 0x763bd6eb,
		0x37392eb3, 0xcc115979, 0x8026e297, 0xf42e312d, 0x6842ada7, 0xc66a2b3b, 0x12754ccc, 0x782ef11c,
		0x6a124237, 0xb79251e7, 0x06a1bbe6, 0x4bfb6350, 0x1a6b1018, 0x11caedfa, 0x3d25bdd8, 0xe2e1c3c9,
		0x44421659, 0x0a121386, 0xd90cec6e, 0xd5abea2a, 0x64af674e, 0xda86a85f, 0xbebfe988, 0x64e4c3fe,
		0x9dbc8057, 0xf0f7c086, 0x60787bf8, 0x6003604d, 0xd1fd8346, 0xf6381fb0, 0x7745ae04, 0xd736fccc,
		0x83426b33, 0xf01eab71, 0xb0804187, 0x3c005e5f, 0x77a057be, 0xbde8ae24, 0x55464299, 0xbf582e61,
		0x4e58f48f, 0xf2ddfda2, 0xf474ef38, 0x8789bdc2, 0x5366f9c3, 0xc8b38e74, 0xb475f255, 0x46fcd9b9,
		0x7aeb2661, 0x8b1ddf84, 0x846a0e79, 0x915f95e2, 0x466e598e, 0x20b45770, 0x8cd55591, 0xc902de4c,
		0xb90bace1, 0xbb8205d0, 0x11a86248, 0x7574a99e, 0xb77f19b6, 0xe0a9dc09, 0x662d09a1, 0xc4324633,
		0xe85a1f02, 0x09f0be8c, 0x4a99a025, 0x1d6efe10, 0x1ab93d1d, 0x0ba5a4df, 0xa186f20f, 0x2868f169,
		0xdcb7da83, 0x573906fe, 0xa1e2ce9b, 0x4fcd7f52, 0x50115e01, 0xa70683fa, 0xa002b5c4, 0x0de6d027,
		0x9af88c27, 0x773f8641, 0xc3604c06, 0x61a806b5, 0xf0177a28, 0xc0f586e0, 0x006058aa, 0x30dc7d62,
		0x11e69ed7, 0x2338ea63, 0x53c2dd94, 0xc2c21634, 0xbbcbee56, 0x90bcb6de, 0xebfc7da1, 0xce591d76,
		0x6f05e409, 0x4b7c0188, 0x39720a3d, 0x7c927c24, 0x86e3725f, 0x724d9db9, 0x1ac15bb4, 0xd39eb8fc,
		0xed545578, 0x08fca5b5, 0xd83d7cd3, 0x4dad0fc4, 0x1e50ef5e, 0xb161e6f8, 0xa28514d9, 0x6c51133c,
		0x6fd5c7e7, 0x56e14ec4, 0x362abfce, 0xddc6c837, 0xd79a3234, 0x92638212, 0x670efa8e, 0x406000e0,
		0x3a39ce37, 0xd3faf5cf, 0xabc27737, 0x5ac52d1b, 0x5cb0679e, 0x4fa33742, 0xd3822740, 0x99bc9bbe,
		0xd5118e9d, 0xbf0f7315, 0xd62d1c7e, 0xc700c47b, 0xb78c1b6b, 0x21a19045, 0xb26eb1be, 0x6a366eb4,
		0x5748ab2f, 0xbc946e79, 0xc6a376d2, 0x6549c2c8, 0x530ff8ee, 0x468dde7d, 0xd5730a1d, 0x4cd04dc6,
		0x2939bbdb, 0xa9ba4650, 0xac9526e8, 0xbe5ee304, 0xa1fad5f0, 0x6a2d519a, 0x63ef8ce2, 0x9a86ee22,
		0xc089c2b8, 0x43242ef6, 0xa51e03aa, 0x9cf2d0a4, 0x83c061ba, 0x9be96a4d, 0x8fe51550, 0xba645bd6,
		0x2826a2f9, 0xa73a3ae1, 0x4ba99586, 0xef5562e9, 0xc72fefd3, 0xf752f7da, 0x3f046f69, 0x77fa0a59,
		0x80e4a915, 0x87b08601, 0x9b09e6ad, 0x3b3ee593, 0xe990fd5a, 0x9e34d797, 0x2cf0b7d9, 0x022b8b51,
		0x96d5ac3a, 0x017da67d, 0xd1cf3ed6, 0x7c7d2d28, 0x1f9f25cf, 0xadf2b89b, 0x5ad6b472, 0x5a88f54c,
		0xe029ac71, 0xe019a5e6, 0x47b0acfd, 0xed93fa9b, 0xe8d3c48d, 0x283b57cc, 0xf8d56629, 0x79132e28,
		0x785f0191, 0xed756055, 0xf7960e44, 0xe3d35e8c, 0x15056dd4, 0x88f46dba, 0x03a16125, 0x0564f0bd,
		0xc3eb9e15, 0x3c9057a2, 0x97271aec, 0xa93a072a, 0x1b3f6d9b, 0x1e6321f5, 0xf59c66fb, 0x26dcf319,
		0x7533d928, 0xb155fdf5, 0x03563482, 0x8aba3cbb, 0x28517711, 0xc20ad9f8, 0xabcc5167, 0xccad925f,
		0x4de81751, 0x3830dc8e, 0x379d5862, 0x9320f991, 0xea7a90c2, 0xfb3e7bce, 0x5121ce64, 0x774fbe32,
		0xa8b6e37e, 0xc3293d46, 0x48de5369, 0x6413e680, 0xa2ae0810, 0xdd6db224, 0x69852dfd, 0x09072166,
		0xb39a460a, 0x6445c0dd, 0x586cdecf, 0x1c20c8ae, 0x5bbef7dd, 0x1b588d40, 0xccd2017f, 0x6bb4e3bb,
		0xdda26a7e, 0x3a59ff45, 0x3e350a44, 0xbcb4cdd5, 0x72eacea8, 0xfa6484bb, 0x8d6612ae, 0xbf3c6f47,
		0xd29be463, 0x542f5d9e, 0xaec2771b, 0xf64e6370, 0x740e0d8d, 0xe75b1357, 0xf8721671, 0xaf537d5d,
		0x4040cb08, 0x4eb4e2cc, 0x34d2466a, 0x0115af84, 0xe1b00428, 0x95983a1d, 0x06b89fb4, 0xce6ea048,
		0x6f3f3b82, 0x3520ab82, 0x011a1d4b, 0x277227f8, 0x611560b1, 0xe7933fdc, 0xbb3a792b, 0x344525bd,
		0xa08839e1, 0x51ce794b, 0x2f32c9b7, 0xa01fbac9, 0xe01cc87e, 0xbcc7d1f6, 0xcf0111c3, 0xa1e8aac7,
		0x1a908749, 0xd44fbd9a, 0xd0dadecb, 0xd50ada38, 0x0339c32a, 0xc6913667, 0x8df9317c, 0xe0b12b4f,
		0xf79e59b7, 0x43f5bb3a, 0xf2d519ff, 0x27d9459c, 0xbf97222c, 0x15e6fc2a, 0x0f91fc71, 0x9b941525,
		0xfae59361, 0xceb69ceb, 0xc2a86459, 0x12baa8d1, 0xb6c1075e, 0xe3056a0c, 0x10d25065, 0xcb03a442,
		0xe0ec6e0e, 0x1698db3b, 0x4c98a0be, 0x3278e964, 0x9f1f9532, 0xe0d392df, 0xd3a0342b, 0x8971f21e,
		0x1b0a7441, 0x4ba3348c, 0xc5be7120, 0xc37632d8, 0xdf359f8d, 0x9b992f2e, 0xe60b6f47, 0x0fe3f11d,
		0xe54cda54, 0x1edad891, 0xce6279cf, 0xcd3e7e6f, 0x1618b166, 0xfd2c1d05, 0x848fd2c5, 0xf6fb2299,
		0xf523f357, 0xa6327623, 0x93a83531, 0x56cccd02, 0xacf08162, 0x5a75ebb5, 0x6e163697, 0x88d273cc,
		0xde966292, 0x81b949d0, 0x4c50901b, 0x71c65614, 0xe6c6c7bd, 0x327a140a, 0x45e1d006, 0xc3f27b9a,
		0xc9aa53fd, 0x62a80f00, 0xbb25bfe2, 0x35bdd2f6, 0x71126905, 0xb2040222, 0xb6cbcf7c, 0xcd769c2b,
		0x53113ec0, 0x1640e3d3, 0x38abbd60, 0x2547adf0, 0xba38209c, 0xf746ce76, 0x77afa1c5, 0x20756060,
		0x85cbfe4e, 0x8ae88dd8, 0x7aaaf9b0, 0x4cf9aa7e, 0x1948c25c, 0x02fb8a8c, 0x01c36ae4, 0xd6ebe1f9,
		0x90d4f869, 0xa65cdea0, 0x3f09252d, 0xc208e69f, 0xb74e6132, 0xce77e25b, 0x578fdfe3, 0x3ac372e6
	};

	memcpy (p, initialPValues, sizeof (p));

	int i, j = 0;
	for (i = 4; --i >= 0;)
	{
		s[i].malloc (256);
		memcpy (s[i], initialSValues + i * 256, 256 * sizeof (uint32));
	}

	for (i = 0; i < 18; ++i)
	{
		uint32 d = 0;

		for (int k = 0; k < 4; ++k)
		{
			d = (d << 8) | static_cast <const uint8*> (keyData)[j];

			if (++j >= keyBytes)
				j = 0;
		}

		p[i] = initialPValues[i] ^ d;
	}

	uint32 l = 0, r = 0;

	for (i = 0; i < 18; i += 2)
	{
		encrypt (l, r);

		p[i] = l;
		p[i + 1] = r;
	}

	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 256; j += 2)
		{
			encrypt (l, r);

			s[i][j] = l;
			s[i][j + 1] = r;
		}
	}
}

BlowFish::BlowFish (const BlowFish& other)
{
	for (int i = 4; --i >= 0;)
		s[i].malloc (256);

	operator= (other);
}

BlowFish& BlowFish::operator= (const BlowFish& other) noexcept
{
	memcpy (p, other.p, sizeof (p));

	for (int i = 4; --i >= 0;)
		memcpy (s[i], other.s[i], 256 * sizeof (uint32));

	return *this;
}

BlowFish::~BlowFish() noexcept {}

uint32 BlowFish::F (const uint32 x) const noexcept
{
	return ((s[0][(x >> 24) & 0xff] + s[1][(x >> 16) & 0xff])
				^ s[2][(x >> 8) & 0xff]) + s[3][x & 0xff];
}

void BlowFish::encrypt (uint32& data1, uint32& data2) const noexcept
{
	uint32 l = data1;
	uint32 r = data2;

	for (int i = 0; i < 16; ++i)
	{
		l ^= p[i];
		r ^= F(l);
		std::swap (l, r);
	}

	data1 = r ^ p[17];
	data2 = l ^ p[16];
}

void BlowFish::decrypt (uint32& data1, uint32& data2) const noexcept
{
	uint32 l = data1;
	uint32 r = data2;

	for (int i = 17; i > 1; --i)
	{
		l ^= p[i];
		r ^= F(l);
		std::swap (l, r);
	}

	data1 = r ^ p[0];
	data2 = l ^ p[1];
}

/*** End of inlined file: juce_BlowFish.cpp ***/



/*** Start of inlined file: juce_Primes.cpp ***/
namespace PrimesHelpers
{
	void createSmallSieve (const int numBits, BigInteger& result)
	{
		result.setBit (numBits);
		result.clearBit (numBits); // to enlarge the array

		result.setBit (0);
		int n = 2;

		do
		{
			for (int i = n + n; i < numBits; i += n)
				result.setBit (i);

			n = result.findNextClearBit (n + 1);
		}
		while (n <= (numBits >> 1));
	}

	void bigSieve (const BigInteger& base, const int numBits, BigInteger& result,
				   const BigInteger& smallSieve, const int smallSieveSize)
	{
		jassert (! base[0]); // must be even!

		result.setBit (numBits);
		result.clearBit (numBits);  // to enlarge the array

		int index = smallSieve.findNextClearBit (0);

		do
		{
			const int prime = (index << 1) + 1;

			BigInteger r (base), remainder;
			r.divideBy (prime, remainder);

			int i = prime - remainder.getBitRangeAsInt (0, 32);

			if (r.isZero())
				i += prime;

			if ((i & 1) == 0)
				i += prime;

			i = (i - 1) >> 1;

			while (i < numBits)
			{
				result.setBit (i);
				i += prime;
			}

			index = smallSieve.findNextClearBit (index + 1);
		}
		while (index < smallSieveSize);
	}

	bool findCandidate (const BigInteger& base, const BigInteger& sieve,
						const int numBits, BigInteger& result, const int certainty)
	{
		for (int i = 0; i < numBits; ++i)
		{
			if (! sieve[i])
			{
				result = base + (unsigned int) ((i << 1) + 1);

				if (Primes::isProbablyPrime (result, certainty))
					return true;
			}
		}

		return false;
	}

	bool passesMillerRabin (const BigInteger& n, int iterations)
	{
		const BigInteger one (1), two (2);
		const BigInteger nMinusOne (n - one);

		BigInteger d (nMinusOne);
		const int s = d.findNextSetBit (0);
		d >>= s;

		BigInteger smallPrimes;
		int numBitsInSmallPrimes = 0;

		for (;;)
		{
			numBitsInSmallPrimes += 256;
			createSmallSieve (numBitsInSmallPrimes, smallPrimes);

			const int numPrimesFound = numBitsInSmallPrimes - smallPrimes.countNumberOfSetBits();

			if (numPrimesFound > iterations + 1)
				break;
		}

		int smallPrime = 2;

		while (--iterations >= 0)
		{
			smallPrime = smallPrimes.findNextClearBit (smallPrime + 1);

			BigInteger r (smallPrime);
			r.exponentModulo (d, n);

			if (r != one && r != nMinusOne)
			{
				for (int j = 0; j < s; ++j)
				{
					r.exponentModulo (two, n);

					if (r == nMinusOne)
						break;
				}

				if (r != nMinusOne)
					return false;
			}
		}

		return true;
	}
}

BigInteger Primes::createProbablePrime (const int bitLength,
										const int certainty,
										const int* randomSeeds,
										int numRandomSeeds)
{
	using namespace PrimesHelpers;
	int defaultSeeds [16];

	if (numRandomSeeds <= 0)
	{
		randomSeeds = defaultSeeds;
		numRandomSeeds = numElementsInArray (defaultSeeds);
		Random r1, r2;

		for (int j = 10; --j >= 0;)
		{
			r1.setSeedRandomly();

			for (int i = numRandomSeeds; --i >= 0;)
				defaultSeeds[i] ^= r1.nextInt() ^ r2.nextInt();
		}
	}

	BigInteger smallSieve;
	const int smallSieveSize = 15000;
	createSmallSieve (smallSieveSize, smallSieve);

	BigInteger p;

	for (int i = numRandomSeeds; --i >= 0;)
	{
		BigInteger p2;

		Random r (randomSeeds[i]);
		r.fillBitsRandomly (p2, 0, bitLength);

		p ^= p2;
	}

	p.setBit (bitLength - 1);
	p.clearBit (0);

	const int searchLen = jmax (1024, (bitLength / 20) * 64);

	while (p.getHighestBit() < bitLength)
	{
		p += 2 * searchLen;

		BigInteger sieve;
		bigSieve (p, searchLen, sieve,
				  smallSieve, smallSieveSize);

		BigInteger candidate;

		if (findCandidate (p, sieve, searchLen, candidate, certainty))
			return candidate;
	}

	jassertfalse;
	return BigInteger();
}

bool Primes::isProbablyPrime (const BigInteger& number, const int certainty)
{
	using namespace PrimesHelpers;

	if (! number[0])
		return false;

	if (number.getHighestBit() <= 10)
	{
		const int num = number.getBitRangeAsInt (0, 10);

		for (int i = num / 2; --i > 1;)
			if (num % i == 0)
				return false;

		return true;
	}
	else
	{
		if (number.findGreatestCommonDivisor (2 * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23) != 1)
			return false;

		return passesMillerRabin (number, certainty);
	}
}

/*** End of inlined file: juce_Primes.cpp ***/


/*** Start of inlined file: juce_RSAKey.cpp ***/
RSAKey::RSAKey()
{
}

RSAKey::RSAKey (const String& s)
{
	if (s.containsChar (','))
	{
		part1.parseString (s.upToFirstOccurrenceOf (",", false, false), 16);
		part2.parseString (s.fromFirstOccurrenceOf (",", false, false), 16);
	}
	else
	{
		// the string needs to be two hex numbers, comma-separated..
		jassertfalse;
	}
}

RSAKey::~RSAKey()
{
}

bool RSAKey::operator== (const RSAKey& other) const noexcept
{
	return part1 == other.part1 && part2 == other.part2;
}

bool RSAKey::operator!= (const RSAKey& other) const noexcept
{
	return ! operator== (other);
}

String RSAKey::toString() const
{
	return part1.toString (16) + "," + part2.toString (16);
}

bool RSAKey::applyToValue (BigInteger& value) const
{
	if (part1.isZero() || part2.isZero() || value <= 0)
	{
		jassertfalse;   // using an uninitialised key
		value.clear();
		return false;
	}

	BigInteger result;

	while (! value.isZero())
	{
		result *= part2;

		BigInteger remainder;
		value.divideBy (part2, remainder);

		remainder.exponentModulo (part1, part2);

		result += remainder;
	}

	value.swapWith (result);
	return true;
}

BigInteger RSAKey::findBestCommonDivisor (const BigInteger& p, const BigInteger& q)
{
	// try 3, 5, 9, 17, etc first because these only contain 2 bits and so
	// are fast to divide + multiply
	for (int i = 2; i <= 65536; i *= 2)
	{
		const BigInteger e (1 + i);

		if (e.findGreatestCommonDivisor (p).isOne() && e.findGreatestCommonDivisor (q).isOne())
			return e;
	}

	BigInteger e (4);

	while (! (e.findGreatestCommonDivisor (p).isOne() && e.findGreatestCommonDivisor (q).isOne()))
		++e;

	return e;
}

void RSAKey::createKeyPair (RSAKey& publicKey, RSAKey& privateKey,
							const int numBits, const int* randomSeeds, const int numRandomSeeds)
{
	jassert (numBits > 16); // not much point using less than this..
	jassert (numRandomSeeds == 0 || numRandomSeeds >= 2); // you need to provide plenty of seeds here!

	BigInteger p (Primes::createProbablePrime (numBits / 2, 30, randomSeeds, numRandomSeeds / 2));
	BigInteger q (Primes::createProbablePrime (numBits - numBits / 2, 30, randomSeeds == nullptr ? 0 : (randomSeeds + numRandomSeeds / 2), numRandomSeeds - numRandomSeeds / 2));

	const BigInteger n (p * q);
	const BigInteger m (--p * --q);
	const BigInteger e (findBestCommonDivisor (p, q));

	BigInteger d (e);
	d.inverseModulo (m);

	publicKey.part1 = e;
	publicKey.part2 = n;

	privateKey.part1 = d;
	privateKey.part2 = n;
}

/*** End of inlined file: juce_RSAKey.cpp ***/


/*** Start of inlined file: juce_MD5.cpp ***/
class MD5Generator
{
public:
	MD5Generator() noexcept
	{
		state[0] = 0x67452301;
		state[1] = 0xefcdab89;
		state[2] = 0x98badcfe;
		state[3] = 0x10325476;

		count[0] = 0;
		count[1] = 0;
	}

	void processBlock (const void* data, size_t dataSize) noexcept
	{
		int bufferPos = ((count[0] >> 3) & 0x3F);

		count[0] += (uint32) (dataSize << 3);

		if (count[0] < ((uint32) dataSize << 3))
			count[1]++;

		count[1] += (uint32) (dataSize >> 29);

		const size_t spaceLeft = 64 - bufferPos;
		size_t i = 0;

		if (dataSize >= spaceLeft)
		{
			memcpy (buffer + bufferPos, data, spaceLeft);
			transform (buffer);

			for (i = spaceLeft; i + 64 <= dataSize; i += 64)
				transform (static_cast <const char*> (data) + i);

			bufferPos = 0;
		}

		memcpy (buffer + bufferPos, static_cast <const char*> (data) + i, dataSize - i);
	}

	void transform (const void* bufferToTransform) noexcept
	{
		uint32 a = state[0];
		uint32 b = state[1];
		uint32 c = state[2];
		uint32 d = state[3];
		uint32 x[16];

		encode (x, bufferToTransform, 64);

		enum Constants
		{
			S11 = 7, S12 = 12, S13 = 17, S14 = 22, S21 = 5, S22 = 9,  S23 = 14, S24 = 20,
			S31 = 4, S32 = 11, S33 = 16, S34 = 23, S41 = 6, S42 = 10, S43 = 15, S44 = 21
		};

		FF (a, b, c, d, x[ 0], S11, 0xd76aa478);     FF (d, a, b, c, x[ 1], S12, 0xe8c7b756);
		FF (c, d, a, b, x[ 2], S13, 0x242070db);     FF (b, c, d, a, x[ 3], S14, 0xc1bdceee);
		FF (a, b, c, d, x[ 4], S11, 0xf57c0faf);     FF (d, a, b, c, x[ 5], S12, 0x4787c62a);
		FF (c, d, a, b, x[ 6], S13, 0xa8304613);     FF (b, c, d, a, x[ 7], S14, 0xfd469501);
		FF (a, b, c, d, x[ 8], S11, 0x698098d8);     FF (d, a, b, c, x[ 9], S12, 0x8b44f7af);
		FF (c, d, a, b, x[10], S13, 0xffff5bb1);     FF (b, c, d, a, x[11], S14, 0x895cd7be);
		FF (a, b, c, d, x[12], S11, 0x6b901122);     FF (d, a, b, c, x[13], S12, 0xfd987193);
		FF (c, d, a, b, x[14], S13, 0xa679438e);     FF (b, c, d, a, x[15], S14, 0x49b40821);

		GG (a, b, c, d, x[ 1], S21, 0xf61e2562);     GG (d, a, b, c, x[ 6], S22, 0xc040b340);
		GG (c, d, a, b, x[11], S23, 0x265e5a51);     GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa);
		GG (a, b, c, d, x[ 5], S21, 0xd62f105d);     GG (d, a, b, c, x[10], S22, 0x02441453);
		GG (c, d, a, b, x[15], S23, 0xd8a1e681);     GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8);
		GG (a, b, c, d, x[ 9], S21, 0x21e1cde6);     GG (d, a, b, c, x[14], S22, 0xc33707d6);
		GG (c, d, a, b, x[ 3], S23, 0xf4d50d87);     GG (b, c, d, a, x[ 8], S24, 0x455a14ed);
		GG (a, b, c, d, x[13], S21, 0xa9e3e905);     GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8);
		GG (c, d, a, b, x[ 7], S23, 0x676f02d9);     GG (b, c, d, a, x[12], S24, 0x8d2a4c8a);

		HH (a, b, c, d, x[ 5], S31, 0xfffa3942);     HH (d, a, b, c, x[ 8], S32, 0x8771f681);
		HH (c, d, a, b, x[11], S33, 0x6d9d6122);     HH (b, c, d, a, x[14], S34, 0xfde5380c);
		HH (a, b, c, d, x[ 1], S31, 0xa4beea44);     HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9);
		HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60);     HH (b, c, d, a, x[10], S34, 0xbebfbc70);
		HH (a, b, c, d, x[13], S31, 0x289b7ec6);     HH (d, a, b, c, x[ 0], S32, 0xeaa127fa);
		HH (c, d, a, b, x[ 3], S33, 0xd4ef3085);     HH (b, c, d, a, x[ 6], S34, 0x04881d05);
		HH (a, b, c, d, x[ 9], S31, 0xd9d4d039);     HH (d, a, b, c, x[12], S32, 0xe6db99e5);
		HH (c, d, a, b, x[15], S33, 0x1fa27cf8);     HH (b, c, d, a, x[ 2], S34, 0xc4ac5665);

		II (a, b, c, d, x[ 0], S41, 0xf4292244);     II (d, a, b, c, x[ 7], S42, 0x432aff97);
		II (c, d, a, b, x[14], S43, 0xab9423a7);     II (b, c, d, a, x[ 5], S44, 0xfc93a039);
		II (a, b, c, d, x[12], S41, 0x655b59c3);     II (d, a, b, c, x[ 3], S42, 0x8f0ccc92);
		II (c, d, a, b, x[10], S43, 0xffeff47d);     II (b, c, d, a, x[ 1], S44, 0x85845dd1);
		II (a, b, c, d, x[ 8], S41, 0x6fa87e4f);     II (d, a, b, c, x[15], S42, 0xfe2ce6e0);
		II (c, d, a, b, x[ 6], S43, 0xa3014314);     II (b, c, d, a, x[13], S44, 0x4e0811a1);
		II (a, b, c, d, x[ 4], S41, 0xf7537e82);     II (d, a, b, c, x[11], S42, 0xbd3af235);
		II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb);     II (b, c, d, a, x[ 9], S44, 0xeb86d391);

		state[0] += a;
		state[1] += b;
		state[2] += c;
		state[3] += d;

		zerostruct (x);
	}

	void finish (void* result) noexcept
	{
		unsigned char encodedLength[8];
		encode (encodedLength, count, 8);

		// Pad out to 56 mod 64.
		const int index = (uint32) ((count[0] >> 3) & 0x3f);

		const int paddingLength = (index < 56) ? (56 - index)
											   : (120 - index);

		uint8 paddingBuffer[64] = { 0x80 }; // first byte is 0x80, remaining bytes are zero.
		processBlock (paddingBuffer, paddingLength);

		processBlock (encodedLength, 8);

		encode (result, state, 16);
		zerostruct (buffer);
	}

private:
	uint8 buffer [64];
	uint32 state [4];
	uint32 count [2];

	static void encode (void* const output, const void* const input, const int numBytes) noexcept
	{
		for (int i = 0; i < (numBytes >> 2); ++i)
			static_cast<uint32*> (output)[i] = ByteOrder::swapIfBigEndian (static_cast<const uint32*> (input) [i]);
	}

	static inline uint32 rotateLeft (const uint32 x, const uint32 n) noexcept          { return (x << n) | (x >> (32 - n)); }

	static inline uint32 F (const uint32 x, const uint32 y, const uint32 z) noexcept   { return (x & y) | (~x & z); }
	static inline uint32 G (const uint32 x, const uint32 y, const uint32 z) noexcept   { return (x & z) | (y & ~z); }
	static inline uint32 H (const uint32 x, const uint32 y, const uint32 z) noexcept   { return x ^ y ^ z; }
	static inline uint32 I (const uint32 x, const uint32 y, const uint32 z) noexcept   { return y ^ (x | ~z); }

	static void FF (uint32& a, const uint32 b, const uint32 c, const uint32 d, const uint32 x, const uint32 s, const uint32 ac) noexcept
	{
		a += F (b, c, d) + x + ac;
		a = rotateLeft (a, s) + b;
	}

	static void GG (uint32& a, const uint32 b, const uint32 c, const uint32 d, const uint32 x, const uint32 s, const uint32 ac) noexcept
	{
		a += G (b, c, d) + x + ac;
		a = rotateLeft (a, s) + b;
	}

	static void HH (uint32& a, const uint32 b, const uint32 c, const uint32 d, const uint32 x, const uint32 s, const uint32 ac) noexcept
	{
		a += H (b, c, d) + x + ac;
		a = rotateLeft (a, s) + b;
	}

	static void II (uint32& a, const uint32 b, const uint32 c, const uint32 d, const uint32 x, const uint32 s, const uint32 ac) noexcept
	{
		a += I (b, c, d) + x + ac;
		a = rotateLeft (a, s) + b;
	}
};

MD5::MD5() noexcept
{
	zerostruct (result);
}

MD5::MD5 (const MD5& other) noexcept
{
	memcpy (result, other.result, sizeof (result));
}

MD5& MD5::operator= (const MD5& other) noexcept
{
	memcpy (result, other.result, sizeof (result));
	return *this;
}

MD5::MD5 (const MemoryBlock& data) noexcept
{
	processData (data.getData(), data.getSize());
}

MD5::MD5 (const void* data, const size_t numBytes) noexcept
{
	processData (data, numBytes);
}

MD5::MD5 (const CharPointer_UTF8& utf8) noexcept
{
	jassert (utf8.getAddress() != nullptr);
	processData (utf8.getAddress(), utf8.sizeInBytes() - 1);
}

MD5 MD5::fromUTF32 (const String& text)
{
	MD5Generator generator;
	String::CharPointerType t (text.getCharPointer());

	while (! t.isEmpty())
	{
		uint32 unicodeChar = ByteOrder::swapIfBigEndian ((uint32) t.getAndAdvance());
		generator.processBlock (&unicodeChar, sizeof (unicodeChar));
	}

	MD5 m;
	generator.finish (m.result);
	return m;
}

MD5::MD5 (InputStream& input, int64 numBytesToRead)
{
	processStream (input, numBytesToRead);
}

MD5::MD5 (const File& file)
{
	FileInputStream fin (file);

	if (fin.getStatus().wasOk())
		processStream (fin, -1);
	else
		zerostruct (result);
}

MD5::~MD5() noexcept {}

void MD5::processData (const void* data, size_t numBytes) noexcept
{
	MD5Generator generator;
	generator.processBlock (data, numBytes);
	generator.finish (result);
}

void MD5::processStream (InputStream& input, int64 numBytesToRead)
{
	MD5Generator generator;

	if (numBytesToRead < 0)
		numBytesToRead = std::numeric_limits<int64>::max();

	while (numBytesToRead > 0)
	{
		uint8 tempBuffer [512];
		const int bytesRead = input.read (tempBuffer, (int) jmin (numBytesToRead, (int64) sizeof (tempBuffer)));

		if (bytesRead <= 0)
			break;

		numBytesToRead -= bytesRead;
		generator.processBlock (tempBuffer, bytesRead);
	}

	generator.finish (result);
}

MemoryBlock MD5::getRawChecksumData() const
{
	return MemoryBlock (result, sizeof (result));
}

String MD5::toHexString() const
{
	return String::toHexString (result, sizeof (result), 0);
}

bool MD5::operator== (const MD5& other) const noexcept   { return memcmp (result, other.result, sizeof (result)) == 0; }
bool MD5::operator!= (const MD5& other) const noexcept   { return ! operator== (other); }

/*** End of inlined file: juce_MD5.cpp ***/


/*** Start of inlined file: juce_SHA256.cpp ***/
class SHA256Processor
{
public:
	SHA256Processor() noexcept
		: length (0)
	{
		state[0] = 0x6a09e667;
		state[1] = 0xbb67ae85;
		state[2] = 0x3c6ef372;
		state[3] = 0xa54ff53a;
		state[4] = 0x510e527f;
		state[5] = 0x9b05688c;
		state[6] = 0x1f83d9ab;
		state[7] = 0x5be0cd19;
	}

	// expects 64 bytes of data
	void processFullBlock (const void* const data) noexcept
	{
		const uint32 constants[] =
		{
			0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
			0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
			0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
			0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
			0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
			0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
			0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
			0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
		};

		uint32 block[16], s[8];
		memcpy (s, state, sizeof (s));

		for (uint32 j = 0; j < 64; j += 16)
		{
			#define JUCE_SHA256(i) s[(7 - i) & 7] += S1 (s[(4 - i) & 7]) + ch (s[(4 - i) & 7], s[(5 - i) & 7], s[(6 - i) & 7]) + constants[i + j] \
														+ (j != 0 ? (block[i & 15] += s1 (block[(i - 2) & 15]) + block[(i - 7) & 15] + s0 (block[(i - 15) & 15])) \
																  : (block[i] = ByteOrder::bigEndianInt (addBytesToPointer (data, i * 4)))); \
								   s[(3 - i) & 7] += s[(7 - i) & 7]; \
								   s[(7 - i) & 7] += S0 (s[(0 - i) & 7]) + maj (s[(0 - i) & 7], s[(1 - i) & 7], s[(2 - i) & 7])

			JUCE_SHA256(0);  JUCE_SHA256(1);  JUCE_SHA256(2);  JUCE_SHA256(3);  JUCE_SHA256(4);  JUCE_SHA256(5);  JUCE_SHA256(6);  JUCE_SHA256(7);
			JUCE_SHA256(8);  JUCE_SHA256(9);  JUCE_SHA256(10); JUCE_SHA256(11); JUCE_SHA256(12); JUCE_SHA256(13); JUCE_SHA256(14); JUCE_SHA256(15);
			#undef JUCE_SHA256
		}

		for (int i = 0; i < 8; ++i)
			state[i] += s[i];

		length += 64;
	}

	void processFinalBlock (const void* const data, int numBytes) noexcept
	{
		jassert (numBytes < 64);

		length += numBytes;
		length *= 8; // (the length is stored as a count of bits, not bytes)

		uint8 finalBlocks[128];

		memcpy (finalBlocks, data, numBytes);
		finalBlocks [numBytes++] = 128; // append a '1' bit

		while (numBytes != 56 && numBytes < 64 + 56)
			finalBlocks [numBytes++] = 0; // pad with zeros..

		for (int i = 8; --i >= 0;)
			finalBlocks [numBytes++] = (uint8) (length >> (i * 8)); // append the length.

		jassert (numBytes == 64 || numBytes == 128);

		processFullBlock (finalBlocks);

		if (numBytes > 64)
			processFullBlock (finalBlocks + 64);
	}

	void copyResult (uint8* result) const noexcept
	{
		for (int i = 0; i < 8; ++i)
		{
			*result++ = (uint8) (state[i] >> 24);
			*result++ = (uint8) (state[i] >> 16);
			*result++ = (uint8) (state[i] >> 8);
			*result++ = (uint8) state[i];
		}
	}

	void processStream (InputStream& input, int64 numBytesToRead, uint8* const result)
	{
		if (numBytesToRead < 0)
			numBytesToRead = std::numeric_limits<int64>::max();

		for (;;)
		{
			uint8 buffer [64];
			const int bytesRead = input.read (buffer, (int) jmin (numBytesToRead, (int64) sizeof (buffer)));

			if (bytesRead < sizeof (buffer))
			{
				processFinalBlock (buffer, bytesRead);
				break;
			}

			numBytesToRead -= sizeof (buffer);
			processFullBlock (buffer);
		}

		copyResult (result);
	}

private:
	uint32 state[8];
	uint64 length;

	static inline uint32 rotate (const uint32 x, const uint32 y) noexcept                { return (x >> y) | (x << (32 - y)); }
	static inline uint32 ch  (const uint32 x, const uint32 y, const uint32 z) noexcept   { return z ^ ((y ^ z) & x); }
	static inline uint32 maj (const uint32 x, const uint32 y, const uint32 z) noexcept   { return y ^ ((y ^ z) & (x ^ y)); }

	static inline uint32 s0 (const uint32 x) noexcept     { return rotate (x, 7)  ^ rotate (x, 18) ^ (x >> 3); }
	static inline uint32 s1 (const uint32 x) noexcept     { return rotate (x, 17) ^ rotate (x, 19) ^ (x >> 10); }
	static inline uint32 S0 (const uint32 x) noexcept     { return rotate (x, 2)  ^ rotate (x, 13) ^ rotate (x, 22); }
	static inline uint32 S1 (const uint32 x) noexcept     { return rotate (x, 6)  ^ rotate (x, 11) ^ rotate (x, 25); }

	JUCE_DECLARE_NON_COPYABLE (SHA256Processor);
};

SHA256::SHA256() noexcept
{
	zerostruct (result);
}

SHA256::~SHA256() noexcept {}

SHA256::SHA256 (const SHA256& other) noexcept
{
	memcpy (result, other.result, sizeof (result));
}

SHA256& SHA256::operator= (const SHA256& other) noexcept
{
	memcpy (result, other.result, sizeof (result));
	return *this;
}

SHA256::SHA256 (const MemoryBlock& data)
{
	process (data.getData(), data.getSize());
}

SHA256::SHA256 (const void* const data, const size_t numBytes)
{
	process (data, numBytes);
}

SHA256::SHA256 (InputStream& input, const int64 numBytesToRead)
{
	SHA256Processor processor;
	processor.processStream (input, numBytesToRead, result);
}

SHA256::SHA256 (const File& file)
{
	FileInputStream fin (file);

	if (fin.getStatus().wasOk())
	{
		SHA256Processor processor;
		processor.processStream (fin, -1, result);
	}
	else
	{
		zerostruct (result);
	}
}

SHA256::SHA256 (const CharPointer_UTF8& utf8) noexcept
{
	jassert (utf8.getAddress() != nullptr);
	process (utf8.getAddress(), utf8.sizeInBytes() - 1);
}

void SHA256::process (const void* const data, size_t numBytes)
{
	MemoryInputStream m (data, numBytes, false);
	SHA256Processor processor;
	processor.processStream (m, -1, result);
}

MemoryBlock SHA256::getRawData() const
{
	return MemoryBlock (result, sizeof (result));
}

String SHA256::toHexString() const
{
	return String::toHexString (result, sizeof (result), 0);
}

bool SHA256::operator== (const SHA256& other) const noexcept  { return memcmp (result, other.result, sizeof (result)) == 0; }
bool SHA256::operator!= (const SHA256& other) const noexcept  { return ! operator== (other); }

#if JUCE_UNIT_TESTS

class SHA256Tests  : public UnitTest
{
public:
	SHA256Tests() : UnitTest ("SHA-256") {}

	void runTest()
	{
		beginTest ("SHA-256");

		{
			char n[] = "";
			SHA256 sha (n, 0);
			expectEquals (sha.toHexString(), String ("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"));
		}

		{
			const char n[] = "The quick brown fox jumps over the lazy dog";
			SHA256 sha (n, sizeof (n) - 1);
			expectEquals (sha.toHexString(), String ("d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592"));
		}

		{
			const char n[] = "The quick brown fox jumps over the lazy dog.";
			SHA256 sha (n, sizeof (n) - 1);
			expectEquals (sha.toHexString(), String ("ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c"));
		}
	}
};

static SHA256Tests sha256UnitTests;

#endif

/*** End of inlined file: juce_SHA256.cpp ***/

// END_AUTOINCLUDE

}
/*** End of inlined file: juce_cryptography.cpp ***/

