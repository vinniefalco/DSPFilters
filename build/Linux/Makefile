# Automatically generated makefile, created by the Jucer
# Don't edit this file! Your changes will be overwritten when you re-save the Jucer project!

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(TARGET_ARCH),)
  TARGET_ARCH := -march=native
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) -I /home/patrick/dspfilterscpp-demo/include
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L"/usr/X11R6/lib/" -L"../../../juce/bin" -lfreetype -lpthread -lrt -lX11 -lXinerama -lasound 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2"
  TARGET := DspDemo
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) -I /home/patrick/dspfilterscpp-demo/include
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L"/usr/X11R6/lib/" -L"../../../juce/bin" -lfreetype -lpthread -lrt -lX11 -lXinerama -lasound 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2"
  TARGET := DspDemo
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/Bessel_61bd2073.o \
  $(OBJDIR)/Biquad_4594dab7.o \
  $(OBJDIR)/Butterworth_f5ffadcf.o \
  $(OBJDIR)/Cascade_3d4220f5.o \
  $(OBJDIR)/ChebyshevI_819c0c55.o \
  $(OBJDIR)/ChebyshevII_b349b0de.o \
  $(OBJDIR)/Custom_e0524a9a.o \
  $(OBJDIR)/Design_3cd79267.o \
  $(OBJDIR)/Documentation_1c3a30fb.o \
  $(OBJDIR)/Elliptic_1a0cc62b.o \
  $(OBJDIR)/Filter_e2072f21.o \
  $(OBJDIR)/Legendre_187835a9.o \
  $(OBJDIR)/Param_44de914e.o \
  $(OBJDIR)/PoleFilter_9cf1c2f9.o \
  $(OBJDIR)/RBJ_543e417b.o \
  $(OBJDIR)/RootFinder_b2876551.o \
  $(OBJDIR)/State_54139b52.o \
  $(OBJDIR)/JuceSources_b8ea6a94.o \
  $(OBJDIR)/AudioOutput_f821b100.o \
  $(OBJDIR)/binaries_c8d0dea0.o \
  $(OBJDIR)/BrickWallChart_22192c54.o \
  $(OBJDIR)/CpuMeter_49f5422.o \
  $(OBJDIR)/FilterChart_8e53504f.o \
  $(OBJDIR)/FilterControls_e1ef302f.o \
  $(OBJDIR)/FilteringAudioSource_7c453c28.o \
  $(OBJDIR)/GainChart_f9322d28.o \
  $(OBJDIR)/GroupDelayChart_a5792d03.o \
  $(OBJDIR)/MainApp_9bea87b1.o \
  $(OBJDIR)/MainPanel_d9a70354.o \
  $(OBJDIR)/MainWindow_7f83b16a.o \
  $(OBJDIR)/NoiseAudioSource_66e0ee78.o \
  $(OBJDIR)/PhaseChart_a672c884.o \
  $(OBJDIR)/PoleZeroChart_f41b9147.o \
  $(OBJDIR)/ResamplingReader_46b2bde.o \
  $(OBJDIR)/ResizableLayout_fb58d3e.o \
  $(OBJDIR)/SettingsPanel_14e19a2a.o \
  $(OBJDIR)/SettingsWindow_ab9bf554.o \
  $(OBJDIR)/SliderGroup_c6c88f27.o \
  $(OBJDIR)/StepResponseChart_a1adb53a.o \
  $(OBJDIR)/ThreadQueue_449941b0.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking DspDemo
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning DspDemo
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

$(OBJDIR)/Bessel_61bd2073.o: ../../source/Bessel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Bessel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Biquad_4594dab7.o: ../../source/Biquad.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Biquad.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Butterworth_f5ffadcf.o: ../../source/Butterworth.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Butterworth.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Cascade_3d4220f5.o: ../../source/Cascade.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Cascade.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ChebyshevI_819c0c55.o: ../../source/ChebyshevI.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ChebyshevI.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ChebyshevII_b349b0de.o: ../../source/ChebyshevII.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ChebyshevII.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Custom_e0524a9a.o: ../../source/Custom.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Custom.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Design_3cd79267.o: ../../source/Design.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Design.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Documentation_1c3a30fb.o: ../../source/Documentation.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Documentation.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Elliptic_1a0cc62b.o: ../../source/Elliptic.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Elliptic.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Filter_e2072f21.o: ../../source/Filter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Filter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Legendre_187835a9.o: ../../source/Legendre.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Legendre.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Param_44de914e.o: ../../source/Param.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Param.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PoleFilter_9cf1c2f9.o: ../../source/PoleFilter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PoleFilter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/RBJ_543e417b.o: ../../source/RBJ.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling RBJ.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/RootFinder_b2876551.o: ../../source/RootFinder.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling RootFinder.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/State_54139b52.o: ../../source/State.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling State.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/JuceSources_b8ea6a94.o: ../../demo/JuceSources.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling JuceSources.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/AudioOutput_f821b100.o: ../../demo/AudioOutput.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling AudioOutput.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/binaries_c8d0dea0.o: ../../demo/binaries.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling binaries.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BrickWallChart_22192c54.o: ../../demo/BrickWallChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BrickWallChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CpuMeter_49f5422.o: ../../demo/CpuMeter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CpuMeter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FilterChart_8e53504f.o: ../../demo/FilterChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FilterChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FilterControls_e1ef302f.o: ../../demo/FilterControls.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FilterControls.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FilteringAudioSource_7c453c28.o: ../../demo/FilteringAudioSource.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FilteringAudioSource.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GainChart_f9322d28.o: ../../demo/GainChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GainChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GroupDelayChart_a5792d03.o: ../../demo/GroupDelayChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GroupDelayChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainApp_9bea87b1.o: ../../demo/MainApp.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainApp.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainPanel_d9a70354.o: ../../demo/MainPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainWindow_7f83b16a.o: ../../demo/MainWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/NoiseAudioSource_66e0ee78.o: ../../demo/NoiseAudioSource.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling NoiseAudioSource.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PhaseChart_a672c884.o: ../../demo/PhaseChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PhaseChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PoleZeroChart_f41b9147.o: ../../demo/PoleZeroChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PoleZeroChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ResamplingReader_46b2bde.o: ../../demo/ResamplingReader.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ResamplingReader.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ResizableLayout_fb58d3e.o: ../../demo/ResizableLayout.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ResizableLayout.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SettingsPanel_14e19a2a.o: ../../demo/SettingsPanel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SettingsPanel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SettingsWindow_ab9bf554.o: ../../demo/SettingsWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SettingsWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/SliderGroup_c6c88f27.o: ../../demo/SliderGroup.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling SliderGroup.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StepResponseChart_a1adb53a.o: ../../demo/StepResponseChart.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StepResponseChart.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/ThreadQueue_449941b0.o: ../../demo/ThreadQueue.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling ThreadQueue.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
