

win32:LIBS += \
  -lwinmm \
  -lgdi32 \
  -lopengl32 \
  -lws2_32 \
  -lwininet \
  -lversion \
  -lole32 \
  -lcomdlg32 \
  -luuid \
  -loleaut32 \
  -lvfw32

QT =

QMAKE_CXXFLAGS += -march=i486
#QMAKE_LFLAGS += -static

VPATH = ../../source ../../demo ../../include

INCLUDEPATH = ../../include

HEADERS = \
  binaries.h \
  BrickWallChart.h \
  FilterChart.h \
  GainChart.h \
  GroupDelayChart.h \
  PhaseChart.h \
  PoleZeroChart.h \
  StepResponseChart.h \
  BrickWallGraph.h \
  DemoPanel.h \
  FilterChartOld.h \
  FilterGraph.h \
  Graph.h \
  bond.h \
  ContentComponentConstrainer.h \
  CpuMeter.h \
  CustomSlider.h \
  NoiseAudioSource.h \
  ResamplingReader.h \
  ResizableLayout.h \
  SliderGroup.h \
  ThreadQueue.h \
  AudioOutput.h \
  Common.h \
  FilterControls.h \
  FilteringAudioSource.h \
  FilterListener.h \
  MainApp.h \
  MainPanel.h \
  MainWindow.h \
  SettingsPanel.h \
  SettingsWindow.h \
  DspFilters/Bessel.h \
  DspFilters/Biquad.h \
  DspFilters/Butterworth.h \
  DspFilters/Cascade.h \
  DspFilters/ChebyshevI.h \
  DspFilters/ChebyshevII.h \
  DspFilters/Common.h \
  DspFilters/Design.h \
  DspFilters/Dsp.h \
  DspFilters/DspFilter.h \
  DspFilters/Elliptic.h \
  DspFilters/Filter.h \
  DspFilters/MathSupplement.h \
  DspFilters/Params.h \
  DspFilters/PoleFilter.h \
  DspFilters/SmoothedFilter.h \
  DspFilters/RBJ.h \
  DspFilters/State.h \
  DspFilters/Types.h \
  DspFilters/Utilities.h \
  juce_amalgamated.h \
  juce_Config.h

SOURCES = \
  binaries.cpp \
  BrickWallChart.cpp \
  FilterChart.cpp \
  GainChart.cpp \
  GroupDelayChart.cpp \
  PhaseChart.cpp \
  PoleZeroChart.cpp \
  StepResponseChart.cpp \
  BrickWallGraph.cpp \
  DemoPanel.cpp \
  FilterChartOld.cpp \
  FilterGraph.cpp \
  Graph.cpp \
  CpuMeter.cpp \
  NoiseAudioSource.cpp \
  ResamplingReader.cpp \
  ResizableLayout.cpp \
  SliderGroup.cpp \
  ThreadQueue.cpp \
  AudioOutput.cpp \
  FilterControls.cpp \
  FilteringAudioSource.cpp \
  MainApp.cpp \
  MainPanel.cpp \
  MainWindow.cpp \
  SettingsPanel.cpp \
  SettingsWindow.cpp \
  Bessel.cpp \
  Biquad.cpp \
  Butterworth.cpp \
  Cascade.cpp \
  ChebyshevI.cpp \
  ChebyshevII.cpp \
  Design.cpp \
  DspFilter.cpp \
  Elliptic.cpp \
  Filter.cpp \
  Param.cpp \
  PoleFilter.cpp \
  RBJ.cpp \
  State.cpp \
  juce_amalgamated.cpp
