QT =
TARGET = DspFilters
TEMPLATE = app
CONFIG += debug_and_release x86 mmx sse rtti exceptions threads
CONFIG -= lex yacc warn_on uic resources qt link_prl no_mocdepend qt_no_framework

ROOTDIR = $$PWD/../..
BINDIR = $$ROOTDIR/bin

DESTDIR = $$PWD
OBJECTS_DIR = $$DESTDIR

DEFINES =
INCLUDEPATH = \
    /usr/include/freetype2 \
    $$ROOTDIR/include \
    $$ROOTDIR/sources \
    $$ROOTDIR/demo

HEADERS = \
  $$ROOTDIR/demo/AudioOutput.h \
  $$ROOTDIR/demo/binaries.h \
  $$ROOTDIR/demo/bond.h \
  $$ROOTDIR/demo/BrickWallChart.h \
  $$ROOTDIR/demo/Common.h \
  $$ROOTDIR/demo/ContentComponentConstrainer.h \
  $$ROOTDIR/demo/CpuMeter.h \
  $$ROOTDIR/demo/CustomSlider.h \
  $$ROOTDIR/demo/FilterChart.h \
  $$ROOTDIR/demo/FilterControls.h \
  $$ROOTDIR/demo/FilteringAudioSource.h \
  $$ROOTDIR/demo/FilterListener.h \
  $$ROOTDIR/demo/GainChart.h \
  $$ROOTDIR/demo/GroupDelayChart.h \
  $$ROOTDIR/demo/MainApp.h \
  $$ROOTDIR/demo/MainPanel.h \
  $$ROOTDIR/demo/MainWindow.h \
  $$ROOTDIR/demo/NoiseAudioSource.h \
  $$ROOTDIR/demo/PhaseChart.h \
  $$ROOTDIR/demo/PoleZeroChart.h \
  $$ROOTDIR/demo/ResamplingReader.h \
  $$ROOTDIR/demo/ResizableLayout.h \
  $$ROOTDIR/demo/SettingsPanel.h \
  $$ROOTDIR/demo/SettingsWindow.h \
  $$ROOTDIR/demo/SliderGroup.h \
  $$ROOTDIR/demo/StepResponseChart.h \
  $$ROOTDIR/demo/ThreadQueue.h \
  $$ROOTDIR/include/DspFilters/Bessel.h \
  $$ROOTDIR/include/DspFilters/Biquad.h \
  $$ROOTDIR/include/DspFilters/Butterworth.h \
  $$ROOTDIR/include/DspFilters/Cascade.h \
  $$ROOTDIR/include/DspFilters/ChebyshevI.h \
  $$ROOTDIR/include/DspFilters/ChebyshevII.h \
  $$ROOTDIR/include/DspFilters/Common.h \
  $$ROOTDIR/include/DspFilters/Custom.h \
  $$ROOTDIR/include/DspFilters/Design.h \
  $$ROOTDIR/include/DspFilters/Dsp.h \
  $$ROOTDIR/include/DspFilters/Elliptic.h \
  $$ROOTDIR/include/DspFilters/Filter.h \
  $$ROOTDIR/include/DspFilters/MathSupplement.h \
  $$ROOTDIR/include/DspFilters/Params.h \
  $$ROOTDIR/include/DspFilters/PoleFilter.h \
  $$ROOTDIR/include/DspFilters/SmoothedFilter.h \
  $$ROOTDIR/include/DspFilters/RBJ.h \
  $$ROOTDIR/include/DspFilters/RootFinder.h \
  $$ROOTDIR/include/DspFilters/State.h \
  $$ROOTDIR/include/DspFilters/Types.h \
  $$ROOTDIR/include/DspFilters/Utilities.h \
  $$ROOTDIR/demo/juce_amalgamated.h \
  $$ROOTDIR/demo/juce_Config.h

SOURCES = \
  $$ROOTDIR/demo/AudioOutput.cpp \
  $$ROOTDIR/demo/binaries.cpp \
  $$ROOTDIR/demo/BrickWallChart.cpp \
  $$ROOTDIR/demo/CpuMeter.cpp \
  $$ROOTDIR/demo/FilterChart.cpp \
  $$ROOTDIR/demo/FilterControls.cpp \
  $$ROOTDIR/demo/FilteringAudioSource.cpp \
  $$ROOTDIR/demo/GainChart.cpp \
  $$ROOTDIR/demo/GroupDelayChart.cpp \
  $$ROOTDIR/demo/MainApp.cpp \
  $$ROOTDIR/demo/MainPanel.cpp \
  $$ROOTDIR/demo/MainWindow.cpp \
  $$ROOTDIR/demo/NoiseAudioSource.cpp \
  $$ROOTDIR/demo/PhaseChart.cpp \
  $$ROOTDIR/demo/PoleZeroChart.cpp \
  $$ROOTDIR/demo/ResamplingReader.cpp \
  $$ROOTDIR/demo/ResizableLayout.cpp \
  $$ROOTDIR/demo/SettingsPanel.cpp \
  $$ROOTDIR/demo/SettingsWindow.cpp \
  $$ROOTDIR/demo/StepResponseChart.cpp \
  $$ROOTDIR/demo/SliderGroup.cpp \
  $$ROOTDIR/demo/ThreadQueue.cpp \
  $$ROOTDIR/source/Bessel.cpp \
  $$ROOTDIR/source/Biquad.cpp \
  $$ROOTDIR/source/Butterworth.cpp \
  $$ROOTDIR/source/Cascade.cpp \
  $$ROOTDIR/source/ChebyshevI.cpp \
  $$ROOTDIR/source/ChebyshevII.cpp \
  $$ROOTDIR/source/Custom.cpp \
  $$ROOTDIR/source/Design.cpp \
  $$ROOTDIR/source/Documentation.cpp \
  $$ROOTDIR/source/Elliptic.cpp \
  $$ROOTDIR/source/Filter.cpp \
  $$ROOTDIR/source/Legendre.cpp \
  $$ROOTDIR/source/Param.cpp \
  $$ROOTDIR/source/PoleFilter.cpp \
  $$ROOTDIR/source/RBJ.cpp \
  $$ROOTDIR/source/RootFinder.cpp \
  $$ROOTDIR/source/State.cpp \
  $$ROOTDIR/demo/juce_amalgamated.cpp

unix {
  CONFIG +=
  DEFINES += LINUX=1

  LIBS =

  QMAKE_CFLAGS = -mmmx -msse -msse2 -pipe
  QMAKE_CFLAGS_DEBUG = --g
  QMAKE_CFLAGS_RELEASE = -O2

  QMAKE_CXXFLAGS = $$QMAKE_CFLAGS
  QMAKE_CXXFLAGS_DEBUG = $$QMAKE_CFLAGS_DEBUG
  QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE

  QMAKE_LFLAGS = \
      -lm \
      -lrt \
      -ldl \
      -lpthread \
      -lfreetype \
      -lX11 \
      -lXext \
      -lasound \
      -lGL

  CONFIG(debug, debug|release) {
      DEFINES += DEBUG _DEBUG
      DESTDIR = $$BINDIR/Debug
      OBJECTS_DIR = $$DESTDIR
  }

  CONFIG(release, debug|release) {
      DEFINES += NDEBUG _NDEBUG
      DESTDIR = $$BINDIR/Release
      OBJECTS_DIR = $$DESTDIR
  }
}

