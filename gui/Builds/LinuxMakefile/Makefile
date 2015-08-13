# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_6D53C8B4=1" -D "JUCE_APP_VERSION=2.0.0" -D "JUCE_APP_VERSION_HEX=0x20000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules -I ../../../old/ -I ../../../include
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 

  TARGET := NewProject
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_6D53C8B4=1" -D "JUCE_APP_VERSION=2.0.0" -D "JUCE_APP_VERSION_HEX=0x20000" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../JuceLibraryCode/modules -I ../../../old/ -I ../../../include
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -O3
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 

  TARGET := NewProject
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/NoiseAudioSource_83e66720.o \
  $(OBJDIR)/PhaseChart_7089df2c.o \
  $(OBJDIR)/PoleZeroChart_68f1199f.o \
  $(OBJDIR)/Precompile_4b66f7b9.o \
  $(OBJDIR)/ResamplingReader_2170a486.o \
  $(OBJDIR)/ResizableLayout_a54a5f96.o \
  $(OBJDIR)/SettingsPanel_89b72282.o \
  $(OBJDIR)/SettingsWindow_d17777fc.o \
  $(OBJDIR)/SliderGroup_3f944d7f.o \
  $(OBJDIR)/StepResponseChart_25575192.o \
  $(OBJDIR)/ThreadQueue_bd650008.o \
  $(OBJDIR)/AudioOutput_70ed6f58.o \
  $(OBJDIR)/binaries_4f8d7f48.o \
  $(OBJDIR)/BrickWallChart_47f4aefc.o \
  $(OBJDIR)/CpuMeter_8b5bf4ca.o \
  $(OBJDIR)/FilterChart_71f0ea7.o \
  $(OBJDIR)/FilterControls_7cab2d7.o \
  $(OBJDIR)/FilteringAudioSource_330e20d0.o \
  $(OBJDIR)/GainChart_4a09a180.o \
  $(OBJDIR)/GroupDelayChart_3b0dff5b.o \
  $(OBJDIR)/MainApp_a0433209.o \
  $(OBJDIR)/MainPanel_2a7e77ac.o \
  $(OBJDIR)/MainWindow_499ac812.o \
  $(OBJDIR)/Bessel_1754e5dd.o \
  $(OBJDIR)/Biquad_fb2ca021.o \
  $(OBJDIR)/Butterworth_65cbaa5.o \
  $(OBJDIR)/Cascade_3aa308cb.o \
  $(OBJDIR)/ChebyshevI_719f0cbf.o \
  $(OBJDIR)/ChebyshevII_c3a6bdb4.o \
  $(OBJDIR)/Custom_95ea1004.o \
  $(OBJDIR)/Design_f26f57d1.o \
  $(OBJDIR)/Documentation_89876051.o \
  $(OBJDIR)/Elliptic_c8c8d915.o \
  $(OBJDIR)/Filter_979ef48b.o \
  $(OBJDIR)/Legendre_c7344893.o \
  $(OBJDIR)/Param_efe376a4.o \
  $(OBJDIR)/PoleFilter_8cf4c363.o \
  $(OBJDIR)/RBJ_f8c88451.o \
  $(OBJDIR)/RootFinder_a28a65bb.o \
  $(OBJDIR)/State_ff1880a8.o \
  $(OBJDIR)/juce_audio_basics_2442e4ea.o \
  $(OBJDIR)/juce_audio_devices_a4c8a728.o \
  $(OBJDIR)/juce_audio_formats_d349f0c8.o \
  $(OBJDIR)/juce_audio_processors_44a134a2.o \
  $(OBJDIR)/juce_audio_utils_f63b12e8.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \
  $(OBJDIR)/juce_opengl_c7e3506c.o \
  $(OBJDIR)/juce_video_184321c8.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(RESOURCES)
	@echo Linking DSPFilters
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning DSPFilters
	@$(CLEANCMD)

strip:
	@echo Stripping DSPFilters
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/NoiseAudioSource_83e66720.o: ../../Source/NoiseAudioSource.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling NoiseAudioSource.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PhaseChart_7089df2c.o: ../../Source/PhaseChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PhaseChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PoleZeroChart_68f1199f.o: ../../Source/PoleZeroChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PoleZeroChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Precompile_4b66f7b9.o: ../../Source/Precompile.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Precompile.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ResamplingReader_2170a486.o: ../../Source/ResamplingReader.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ResamplingReader.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ResizableLayout_a54a5f96.o: ../../Source/ResizableLayout.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ResizableLayout.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SettingsPanel_89b72282.o: ../../Source/SettingsPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SettingsPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SettingsWindow_d17777fc.o: ../../Source/SettingsWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SettingsWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SliderGroup_3f944d7f.o: ../../Source/SliderGroup.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SliderGroup.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StepResponseChart_25575192.o: ../../Source/StepResponseChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StepResponseChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ThreadQueue_bd650008.o: ../../Source/ThreadQueue.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ThreadQueue.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AudioOutput_70ed6f58.o: ../../Source/AudioOutput.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AudioOutput.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/binaries_4f8d7f48.o: ../../Source/binaries.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling binaries.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BrickWallChart_47f4aefc.o: ../../Source/BrickWallChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BrickWallChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CpuMeter_8b5bf4ca.o: ../../Source/CpuMeter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CpuMeter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FilterChart_71f0ea7.o: ../../Source/FilterChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FilterChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FilterControls_7cab2d7.o: ../../Source/FilterControls.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FilterControls.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FilteringAudioSource_330e20d0.o: ../../Source/FilteringAudioSource.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FilteringAudioSource.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GainChart_4a09a180.o: ../../Source/GainChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GainChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GroupDelayChart_3b0dff5b.o: ../../Source/GroupDelayChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GroupDelayChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainApp_a0433209.o: ../../Source/MainApp.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainApp.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainPanel_2a7e77ac.o: ../../Source/MainPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainWindow_499ac812.o: ../../Source/MainWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Bessel_1754e5dd.o: ../../../old/DspFilters/Bessel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Bessel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Biquad_fb2ca021.o: ../../../old/DspFilters/Biquad.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Biquad.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Butterworth_65cbaa5.o: ../../../old/DspFilters/Butterworth.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Butterworth.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Cascade_3aa308cb.o: ../../../old/DspFilters/Cascade.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Cascade.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ChebyshevI_719f0cbf.o: ../../../old/DspFilters/ChebyshevI.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ChebyshevI.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ChebyshevII_c3a6bdb4.o: ../../../old/DspFilters/ChebyshevII.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ChebyshevII.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Custom_95ea1004.o: ../../../old/DspFilters/Custom.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Custom.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Design_f26f57d1.o: ../../../old/DspFilters/Design.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Design.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Documentation_89876051.o: ../../../old/DspFilters/Documentation.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Documentation.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Elliptic_c8c8d915.o: ../../../old/DspFilters/Elliptic.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Elliptic.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Filter_979ef48b.o: ../../../old/DspFilters/Filter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Filter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Legendre_c7344893.o: ../../../old/DspFilters/Legendre.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Legendre.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Param_efe376a4.o: ../../../old/DspFilters/Param.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Param.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PoleFilter_8cf4c363.o: ../../../old/DspFilters/PoleFilter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PoleFilter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/RBJ_f8c88451.o: ../../../old/DspFilters/RBJ.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling RBJ.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/RootFinder_a28a65bb.o: ../../../old/DspFilters/RootFinder.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling RootFinder.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/State_ff1880a8.o: ../../../old/DspFilters/State.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling State.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_2442e4ea.o: ../../JuceLibraryCode/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_a4c8a728.o: ../../JuceLibraryCode/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_d349f0c8.o: ../../JuceLibraryCode/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_44a134a2.o: ../../JuceLibraryCode/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_utils_f63b12e8.o: ../../JuceLibraryCode/modules/juce_audio_utils/juce_audio_utils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_utils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_7767d6a8.o: ../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_opengl_c7e3506c.o: ../../JuceLibraryCode/modules/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_video_184321c8.o: ../../JuceLibraryCode/modules/juce_video/juce_video.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_video.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
