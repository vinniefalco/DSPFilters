#include "Common.h"
#include "binaries.h"
#include "BrickWallChart.h"
#include "CpuMeter.h"
#include "CustomSlider.h"
#include "FilterControls.h"
#include "GainChart.h"
#include "GroupDelayChart.h"
#include "MainApp.h"
#include "MainPanel.h"
#include "NoiseAudioSource.h"
#include "PhaseChart.h"
#include "PoleZeroChart.h"
#include "ResamplingReader.h"
#include "StepResponseChart.h"

MainPanel::MainPanel()
	: TopLevelResizableLayout (this)
  , m_lastTypeId (0)
{
  setOpaque (true);

  const int w = 512;
  const int h = 512 + 102;
  const int gap = 4;
  const int x0 = 4;

  m_listeners.add (this);

  int x;
  int y = 4;

  x = x0;

  {
    ComboBox* c = new ComboBox;
    c->setBounds (x, y, 160, 24);
    addToLayout (c, anchorTopLeft);
    addAndMakeVisible (c);
    buildFamilyMenu (c);
    m_menuFamily = c;    
    c->addListener (this);
  }

  x = this->getChildComponent (this->getNumChildComponents() - 1)->getBounds().getRight() + gap;

  {
    ComboBox* c = new ComboBox;
    c->setBounds (x, y, 120, 24);
    addToLayout (c, anchorTopLeft);
    addAndMakeVisible (c);
    buildFamilyMenu (c);
    m_menuType = c;    
    c->addListener (this);
  }

  x = this->getChildComponent (this->getNumChildComponents() - 1)->getBounds().getRight() + gap;

  {
    ComboBox* c = new ComboBox;
    c->setBounds (x, y, 120, 24);
    c->addItem ("Amen Break", 1);
    c->addItem ("White Noise", 2);
    c->addItem ("Sine Wave (440Hz)", 3);
    addToLayout (c, anchorTopLeft);
    addAndMakeVisible (c);
    m_menuAudio = c;    
    c->addListener (this);
  }

  x = this->getChildComponent (this->getNumChildComponents() - 1)->getBounds().getRight() + gap;

  {
    CpuMeter* c = new CpuMeter (MainApp::getInstance().getAudioOutput().getAudioDeviceManager());
    c->setBounds (w - 80 - gap, y, 80, 24);
    addToLayout (c, anchorTopRight);
    addAndMakeVisible (c);
  }

  y = this->getChildComponent (this->getNumChildComponents()-1)->getBounds().getBottom() + gap;
  x = x0;

  x = w - gap;

  const int hfc = 80;

  {
    Slider* c = new Slider;
    c->setBounds (x - 20, y, 20, hfc);
    c->setSliderStyle (Slider::LinearVertical);
    c->setTextBoxStyle (Slider::NoTextBox, true, 0, 0);
    c->setRange (-40, 12);
    c->setValue (0);
    addAndMakeVisible (c);
    addToLayout (c, anchorTopRight);
    c->addListener (this);
    m_volumeSlider = c;
    
  }

  x = this->getChildComponent (this->getNumChildComponents() - 1)->getBounds().getX() - gap;
 
  {
    Slider* c = new Slider;
    c->setBounds (x - 20, y, 20, hfc);
    c->setSliderStyle (Slider::LinearVertical);
    c->setTextBoxStyle (Slider::NoTextBox, true, 0, 0);
    c->setRange (-2, 2);
    c->setValue (0);
    addAndMakeVisible (c);
    addToLayout (c, anchorTopRight);
    c->addListener (this);
    m_tempoSlider = c;
  }

  x = this->getChildComponent (this->getNumChildComponents() - 1)->getBounds().getX() - gap;
 
  {
    FilterControls* c = new FilterControls (m_listeners);
    c->setBounds (x0, y, x - x0, hfc);
    addToLayout (c, anchorTopLeft, anchorTopRight);
    addAndMakeVisible (c);
    m_listeners.add (c);
  }

  y = this->getChildComponent (this->getNumChildComponents()-1)->getBounds().getBottom() + gap;
  x = x0;

  const Rectangle<int> r (x, y, w - (x + gap), h - (y + gap));
  createCharts (r);

	setSize (w, h);

  setMinimumSize (256, 256);

	activateLayout();

  m_menuFamily->setSelectedId (1);
  m_menuAudio->setSelectedId (1);
}

MainPanel::~MainPanel()
{
	deleteAllChildren();
}

/*

Gain  Phase  Poles

+--------+   Delay
|Response|
+--------+   Step

*/
void MainPanel::createCharts (const Rectangle<int>& r)
{
  const int gap = 4;
  const int w = (r.getWidth()  - (2 * gap)) / 3;
  const int h = (r.getHeight() - (2 * gap)) / 3;
  const int w2 = w * 2 + gap; //r.getWidth()  - (w + gap);
  const int h2 = h * 2 + gap; //r.getHeight() - (h + gap);

  {
    BrickWallChart* c = new BrickWallChart;
    c->setBounds (r.getX(), r.getY(), w, h);
    addToLayout (c, Point<int>(0, 0), Point<int>(33, 33));
    addAndMakeVisible (c);
    m_listeners.add (c);
  }

  {
    PhaseChart* c = new PhaseChart;
    c->setBounds (r.getX() + w + gap, r.getY(), w, h);
    addToLayout (c, Point<int>(33, 0), Point<int>(66, 33));
    addAndMakeVisible (c);
    m_listeners.add (c);
  }

  {
    PoleZeroChart* c = new PoleZeroChart;
    c->setBounds (r.getX() + w + gap + w + gap, r.getY(), w, h);
    addToLayout (c, Point<int>(66, 0), Point<int>(100, 33));
    addAndMakeVisible (c);
    m_listeners.add (c);
  }

  {
    GainChart* c = new GainChart;
    c->setBounds (r.getX(), r.getY() + h + gap, w2, h2);
    addToLayout (c, Point<int>(0, 33), Point<int>(66, 100));
    addAndMakeVisible (c);
    m_listeners.add (c);
  }

  {
    GroupDelayChart* c = new GroupDelayChart;
    c->setBounds (r.getX() + w + gap + w + gap, r.getY() + h + gap, w, h);
    addToLayout (c, Point<int>(66, 33), Point<int>(100, 66));
    addAndMakeVisible (c);
    m_listeners.add (c);
  }

  {
    StepResponseChart* c = new StepResponseChart;
    c->setBounds (r.getX() + w + gap + w + gap, r.getY() + h + gap + h + gap, w, h);
    addToLayout (c, Point<int>(66, 66), Point<int>(100, 100));
    addAndMakeVisible (c);
    m_listeners.add (c);
  }
}

bool MainPanel::isEnabled (int familyId)
{
  bool enabled = true;

  switch (familyId)
  {
  case 3:
  case 4:
  case 5:
  case 6:
    enabled = false;
    break;
  };
  
  return enabled;
}

bool MainPanel::isEnabled (int familyId, int typeId)
{
  bool enabled = isEnabled (familyId);

  if (enabled)
  {
    switch (familyId)
    {
    case 2:
      switch (typeId)
      {
      case 4:
      case 5:
      case 7:
      case 8:
        enabled = false;
        break;
      };
      break;
    };
  }

  return enabled;
}

void MainPanel::buildFamilyMenu (ComboBox* ctrl)
{
  ctrl->clear();

  ctrl->addItem ("RBJ Biquad",   1); ctrl->setItemEnabled (1, isEnabled (1));
  ctrl->addItem ("Butterworth",  2); ctrl->setItemEnabled (2, isEnabled (2));
  ctrl->addItem ("Chebyshev I",  3); ctrl->setItemEnabled (3, isEnabled (3));
  ctrl->addItem ("Chebyshev II", 4); ctrl->setItemEnabled (4, isEnabled (4));
  ctrl->addItem ("Elliptic",     5); ctrl->setItemEnabled (5, isEnabled (5));
  ctrl->addItem ("Bessel",       6); ctrl->setItemEnabled (6, isEnabled (6));
}

void MainPanel::buildTypeMenu (ComboBox* ctrl)
{
  ctrl->clear();

  //
  // NOTE the Type item IDs for equivalent types
  // in different families need to match in order
  // for the interface to work smoothly.
  //
  switch (m_menuFamily->getSelectedId())
  {
  case 1: // RBJ
    ctrl->addItem ("Low Pass",    1); ctrl->setItemEnabled (1, isEnabled (1, 1));
	  ctrl->addItem ("High Pass",   2); ctrl->setItemEnabled (2, isEnabled (1, 2));
	  ctrl->addItem ("Band Pass 1", 3); ctrl->setItemEnabled (3, isEnabled (1, 3));
	  ctrl->addItem ("Band Pass 2", 4); ctrl->setItemEnabled (4, isEnabled (1, 4));
	  ctrl->addItem ("Band Stop",   5); ctrl->setItemEnabled (5, isEnabled (1, 5));
	  ctrl->addItem ("Low Shelf",   6); ctrl->setItemEnabled (6, isEnabled (1, 6));
	  ctrl->addItem ("High Shelf",  7); ctrl->setItemEnabled (7, isEnabled (1, 7));
	  ctrl->addItem ("Band Shelf",  8); ctrl->setItemEnabled (8, isEnabled (1, 8));
	  ctrl->addItem ("All Pass",    9); ctrl->setItemEnabled (8, isEnabled (1, 9));
    break;

  case 2: // Butterworth
    ctrl->addItem ("Low Pass",    1); ctrl->setItemEnabled (1, isEnabled (2, 1));
	  ctrl->addItem ("High Pass",   2); ctrl->setItemEnabled (2, isEnabled (2, 2));
    // 3
	  ctrl->addItem ("Band Pass",   4); ctrl->setItemEnabled (4, isEnabled (2, 4));
	  ctrl->addItem ("Band Stop",   5); ctrl->setItemEnabled (5, isEnabled (2, 5));
	  ctrl->addItem ("Low Shelf",   6); ctrl->setItemEnabled (6, isEnabled (2, 6));
	  ctrl->addItem ("High Shelf",  7); ctrl->setItemEnabled (7, isEnabled (2, 7));
	  ctrl->addItem ("Band Shelf",  8); ctrl->setItemEnabled (8, isEnabled (2, 8));
	  break;
  };
}

void MainPanel::paint (Graphics& g)
{
	g.fillAll (Colour (0xffc1d0ff));
}

//------------------------------------------------------------------------------

void MainPanel::setFilter (int familyId, int typeId)
{
  Dsp::Filter* f = 0;
  Dsp::Filter* fo = 0;

  //
  // RBJ
  //
  if (familyId == 1)
  {
    switch (typeId)
    {
    case 1:
      f  = new Dsp::FilterType     <Dsp::RBJLowPassDesign>;
      fo = new Dsp::SmoothedFilter <Dsp::RBJLowPassDesign,
        Dsp::ChannelsState <2,      Dsp::RBJLowPassDesign::DirectFormIState> > (1024);
      break;

    case 2:
      f  = new Dsp::FilterType <Dsp::RBJHighPassDesign>;
      fo = new Dsp::SmoothedFilter <Dsp::RBJHighPassDesign,
        Dsp::ChannelsState <2, Dsp::RBJHighPassDesign::DirectFormIState> > (1024);
      break;

    case 3:
      f  = new Dsp::FilterType <Dsp::RBJBandPass1Design>;
      fo = new Dsp::SmoothedFilter <Dsp::RBJBandPass1Design,
        Dsp::ChannelsState <2, Dsp::RBJBandPass1Design::DirectFormIState> > (1024);
      break;

    case 4:
      f  = new Dsp::FilterType <Dsp::RBJBandPass2Design>;
      fo = new Dsp::SmoothedFilter <Dsp::RBJBandPass2Design,
        Dsp::ChannelsState <2, Dsp::RBJBandPass2Design::DirectFormIState> > (1024);
      break;

    case 5:
      f  = new Dsp::FilterType <Dsp::RBJBandStopDesign>;
      fo = new Dsp::SmoothedFilter <Dsp::RBJBandStopDesign,
        Dsp::ChannelsState <2, Dsp::RBJBandStopDesign::DirectFormIState> > (1024);
      break;

    case 6:
      f  = new Dsp::FilterType <Dsp::RBJLowShelfDesign>;
      fo = new Dsp::SmoothedFilter <Dsp::RBJLowShelfDesign,
        Dsp::ChannelsState <2, Dsp::RBJLowShelfDesign::DirectFormIState> > (1024);
      break;

    case 7:
      f  = new Dsp::FilterType <Dsp::RBJHighShelfDesign>;
      fo = new Dsp::SmoothedFilter <Dsp::RBJHighShelfDesign,
        Dsp::ChannelsState <2, Dsp::RBJHighShelfDesign::DirectFormIState> > (1024);
      break;

    case 8:
      f  = new Dsp::FilterType <Dsp::RBJBandShelfDesign>;
      fo = new Dsp::SmoothedFilter <Dsp::RBJBandShelfDesign,
        Dsp::ChannelsState <2, Dsp::RBJBandShelfDesign::DirectFormIState> > (1024);
      break;

    case 9:
      f  = new Dsp::FilterType <Dsp::RBJAllPassDesign>;
      fo = new Dsp::SmoothedFilter <Dsp::RBJAllPassDesign,
        Dsp::ChannelsState <2, Dsp::RBJAllPassDesign::DirectFormIState> > (1024);
      break;
    };
  }
  //
  // Butterworth
  //
  else if (familyId == 2)
  {
    switch (typeId)
    {
    case 1:
      f  = new Dsp::FilterType <
        Dsp::PoleZeroDesign <7,
                             Dsp::detail::ButterworthLowPass,
                             Dsp::detail::LowPassTransformation> >;
      fo  = new Dsp::SmoothedFilter <
        Dsp::PoleZeroDesign <7,
                             Dsp::detail::ButterworthLowPass,
                             Dsp::detail::LowPassTransformation>,
        Dsp::ChannelsState <2,
                            Dsp::Cascade <4>::State <
                              Dsp::Biquad::DirectFormIState> > > (1024);
      break;
    
    case 2:
      f  = new Dsp::FilterType <
        Dsp::PoleZeroDesign <3,
                             Dsp::detail::ButterworthLowPass,
                             Dsp::detail::HighPassTransformation> >;
      fo  = new Dsp::SmoothedFilter <
        Dsp::PoleZeroDesign <3,
                             Dsp::detail::ButterworthLowPass,
                             Dsp::detail::HighPassTransformation>,
        Dsp::ChannelsState <2,
                            Dsp::Cascade <2>::State <
                              Dsp::Biquad::DirectFormIState> > > (1024);
      break;

    case 6:
      f  = new Dsp::FilterType <
        Dsp::PoleZeroDesign <26,
                             Dsp::detail::ButterworthLowShelf,
                             Dsp::detail::LowPassTransformation> >;
      fo  = new Dsp::SmoothedFilter <
        Dsp::PoleZeroDesign <26,
                             Dsp::detail::ButterworthLowShelf,
                             Dsp::detail::LowPassTransformation>,
        Dsp::ChannelsState <2,
                            Dsp::Cascade <13>::State <
                              Dsp::Biquad::DirectFormIState> > > (1024);
      break;
    }
  }

  if (f)
  {
    m_filter = f;

    m_filter->setParameters (m_filter->getDefaultParameters());
   
    m_listeners.call (&FilterListener::onFilterChanged, m_filter);

    if (fo)
      fo->setParameters (m_filter->getDefaultParameters());
    MainApp::getInstance().getAudioOutput().setFilter (fo);
  }
}

void MainPanel::setAudio (int audioId)
{
  AudioSource* source = 0;

  switch (audioId)
  {
  case 1: // Amen Break
    {
      WavAudioFormat waf;
      AudioFormatReader* afr = waf.createReaderFor (
        new MemoryInputStream (binaries::amenbreakloop_wav,
          binaries::amenbreakloop_wavSize,
          false),
        true);

      source = new ResamplingReader (afr);
    }
    break;

  case 2: // White Noise
    source = new NoiseAudioSource;
    break;

  case 3: // sine wave
    {
      ToneGeneratorAudioSource* tgas = new ToneGeneratorAudioSource ();
      tgas->setFrequency (440);
      tgas->setAmplitude (1.f);
      source = tgas;
    }
    break;
  };

  MainApp::getInstance().getAudioOutput().setSource (source);
}

void MainPanel::buttonClicked (Button* ctrl)
{
}

void MainPanel::sliderValueChanged (Slider* ctrl)
{
  if (ctrl == m_volumeSlider)
  {
    MainApp::getInstance().getAudioOutput().setGain (float(ctrl->getValue()));
  }
  else if (ctrl == m_tempoSlider)
  {
    const float tempo = pow (1.2f, float(ctrl->getValue()));
    MainApp::getInstance().getAudioOutput().setTempo (tempo);
  }
}

void MainPanel::comboBoxChanged (ComboBox* ctrl)
{
  if (ctrl == m_menuFamily)
  {
    buildTypeMenu (m_menuType);

    // try to map the previous type to this one via menu item id
    int id = 1;
    if (m_lastTypeId != 0)
    {
      // does a corresponding type exist enabled in the new menu?
      if (m_menuType->indexOfItemId (m_lastTypeId) != -1 &&
          isEnabled (m_menuFamily->getSelectedId(), m_lastTypeId))
      {
        id = m_lastTypeId;
      }
    }
    m_menuType->setSelectedId (id);
  }
  else if (ctrl == m_menuType)
  {
    m_lastTypeId = m_menuType->getSelectedId();

    setFilter (m_menuFamily->getSelectedId(), m_lastTypeId);
  }
  else if (ctrl == m_menuAudio)
  {
    setAudio (ctrl->getSelectedId());
  }
}

void MainPanel::onFilterParameters ()
{
  MainApp::getInstance().getAudioOutput().setFilterParameters (
    m_filter->getParameters());
}

//------------------------------------------------------------------------------

const StringArray MainPanel::getMenuBarNames()
{
  StringArray names;
  names.add (TRANS("File"));
  names.add (TRANS("Help"));
  return names;
}

const PopupMenu MainPanel::getMenuForIndex (int topLevelMenuIndex, const String& menuName)
{
  PopupMenu menu;
  ApplicationCommandManager* commandManager = MainApp::getInstance().getCommandManager();

  switch (topLevelMenuIndex)
  {
  case 0:
    menu.addCommandItem (commandManager, MainApp::cmdSettings);
    menu.addSeparator ();
    menu.addCommandItem (commandManager, StandardApplicationCommandIDs::quit);
    break;

  case 1:
    menu.addCommandItem (commandManager, MainApp::cmdAbout);
    break;
  };

  return menu;
}

void MainPanel::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{
}

