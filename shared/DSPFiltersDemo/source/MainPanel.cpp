/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vinnie Falco

Official project location:
https://github.com/vinniefalco/DSPFilters

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vinnie Falco

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*******************************************************************************/

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
    c->addItem ("Sine Wave (440Hz)", 2);
    c->addItem ("White Noise", 3);
    c->addItem ("Pink Noise", 4);
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
    c->setBounds (x - 20, y, 20, hfc + gap + 24);
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
    c->setBounds (x - 20, y, 20, hfc + gap + 24);
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
 
  int x1 = x - x0 + gap;

  {
    FilterControls* c = new FilterControls (m_listeners);
    c->setBounds (x0, y, x - x0, hfc);
    addToLayout (c, anchorTopLeft, anchorTopRight);
    addAndMakeVisible (c);
    m_listeners.add (c);
  }

  y = this->getChildComponent (this->getNumChildComponents()-1)->getBounds().getBottom() + gap;
  x = x0;

  {
    ComboBox* c = new ComboBox;
    c->setBounds (x, y, 120, 24);
    c->addItem ("Direct Form I", 1);
    c->addItem ("Direct Form II", 2);
    c->addItem ("Transposed Direct Form I", 3);
    c->addItem ("Transposed Direct Form II", 4);
    c->addItem ("Lattice Form", 5); c->setItemEnabled (5, false);
    c->addItem ("State Variable", 6); c->setItemEnabled (6, false);
    c->setSelectedId (1);
    addToLayout (c, anchorTopLeft);
    addAndMakeVisible (c);
    m_menuStateType = c;    
    c->addListener (this);
  }

  x = this->getChildComponent (this->getNumChildComponents() - 1)->getBounds().getRight() + gap;

  {
    ComboBox* c = new ComboBox;
    c->setBounds (x, y, 200, 24);
    c->addItem ("Parameter Smoothing", 1);
    c->addItem ("Pole/Zero Interpolation", 2); c->setItemEnabled (2, false);
    c->addItem ("Coefficient Interpolation", 3); c->setItemEnabled (3, false);
    c->addItem ("No Smoothing", 4);
    c->setSelectedId (1);
    addToLayout (c, anchorTopLeft);
    addAndMakeVisible (c);
    m_menuSmoothing = c;    
    c->addListener (this);
  }

  x = this->getChildComponent (this->getNumChildComponents() - 1)->getBounds().getRight() + gap;

  {
    m_resetButton = new TextButton ("Reset");
    m_resetButton->setBounds (x1 - 60, y, 60, 24);
    m_resetButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    addToLayout (m_resetButton, anchorTopRight);
    addAndMakeVisible (m_resetButton);
    m_resetButton->addListener (this);
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

Resp   Phase  Poles

+---------+   Delay
|  Brick  |
+---------+   Step

*/
void MainPanel::createCharts (const Rectangle<int>& r)
{
  const int gap = 4;
  const int w = (r.getWidth()  - (2 * gap)) / 3;
  const int h = (r.getHeight() - (2 * gap)) / 3;
  const int w2 = w * 2 + gap; //r.getWidth()  - (w + gap);
  const int h2 = h * 2 + gap; //r.getHeight() - (h + gap);

  {
    GainChart* c = new GainChart (m_listeners);
    c->setBounds (r.getX(), r.getY(), w, h);
    addToLayout (c, Point<int>(0, 0), Point<int>(33, 33));
    addAndMakeVisible (c);
  }

  {
    PhaseChart* c = new PhaseChart (m_listeners);
    c->setBounds (r.getX() + w + gap, r.getY(), w, h);
    addToLayout (c, Point<int>(33, 0), Point<int>(66, 33));
    addAndMakeVisible (c);
  }

  {
    PoleZeroChart* c = new PoleZeroChart (m_listeners);
    c->setBounds (r.getX() + w + gap + w + gap, r.getY(), w, h);
    addToLayout (c, Point<int>(66, 0), Point<int>(100, 33));
    addAndMakeVisible (c);
  }

  {
    BrickWallChart* c = new BrickWallChart (m_listeners);
    c->setBounds (r.getX(), r.getY() + h + gap, w2, h2);
    addToLayout (c, Point<int>(0, 33), Point<int>(66, 100));
    addAndMakeVisible (c);
  }

  {
    GroupDelayChart* c = new GroupDelayChart (m_listeners);
    c->setBounds (r.getX() + w + gap + w + gap, r.getY() + h + gap, w, h);
    addToLayout (c, Point<int>(66, 33), Point<int>(100, 66));
    addAndMakeVisible (c);
  }

  {
    StepResponseChart* c = new StepResponseChart (m_listeners);
    c->setBounds (r.getX() + w + gap + w + gap, r.getY() + h + gap + h + gap, w, h);
    addToLayout (c, Point<int>(66, 66), Point<int>(100, 100));
    addAndMakeVisible (c);
  }
}

void MainPanel::buildFamilyMenu (ComboBox* ctrl)
{
  ctrl->clear();

  ctrl->addItem ("RBJ Biquad",   1);
  ctrl->addItem ("Butterworth",  2);
  ctrl->addItem ("Chebyshev I",  3);
  ctrl->addItem ("Chebyshev II", 4);
  ctrl->addItem ("Elliptic",     5);
  ctrl->addItem ("Bessel",       6);
  ctrl->addItem ("Legendre",     7);
  ctrl->addItem ("Custom",       8);
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
    ctrl->addItem ("Low Pass",    1);
	  ctrl->addItem ("High Pass",   2);
	  ctrl->addItem ("Band Pass 1", 3);
	  ctrl->addItem ("Band Pass 2", 4);
	  ctrl->addItem ("Band Stop",   5);
	  ctrl->addItem ("Low Shelf",   6);
	  ctrl->addItem ("High Shelf",  7);
	  ctrl->addItem ("Band Shelf",  8);
	  ctrl->addItem ("All Pass",    9);
    break;

  case 2: // Butterworth
    ctrl->addItem ("Low Pass",    1);
	  ctrl->addItem ("High Pass",   2);
    // 3
	  ctrl->addItem ("Band Pass",   4);
	  ctrl->addItem ("Band Stop",   5);
	  ctrl->addItem ("Low Shelf",   6);
	  ctrl->addItem ("High Shelf",  7);
	  ctrl->addItem ("Band Shelf",  8);
	  break;

  case 3: // Chebyshev I
    ctrl->addItem ("Low Pass",    1);
	  ctrl->addItem ("High Pass",   2);
    // 3
	  ctrl->addItem ("Band Pass",   4);
	  ctrl->addItem ("Band Stop",   5);
	  ctrl->addItem ("Low Shelf",   6);
	  ctrl->addItem ("High Shelf",  7);
	  ctrl->addItem ("Band Shelf",  8);
	  break;

  case 4: // Chebyshev II
    ctrl->addItem ("Low Pass",    1);
	  ctrl->addItem ("High Pass",   2);
    // 3
	  ctrl->addItem ("Band Pass",   4);
	  ctrl->addItem ("Band Stop",   5);
	  ctrl->addItem ("Low Shelf",   6);
	  ctrl->addItem ("High Shelf",  7);
	  ctrl->addItem ("Band Shelf",  8);
	  break;

  case 5: // Elliptic
    ctrl->addItem ("Low Pass",    1);
	  ctrl->addItem ("High Pass",   2);
    // 3
	  ctrl->addItem ("Band Pass",   4);
	  ctrl->addItem ("Band Stop",   5);
	  break;

  case 6: // Bessel
    ctrl->addItem ("Low Pass",    1);
	  ctrl->addItem ("High Pass",   2);
    // 3
	  ctrl->addItem ("Band Pass",   4);
	  ctrl->addItem ("Band Stop",   5);
	  //ctrl->addItem ("Low Shelf",   6);
	  break;

  case 7: // Legendre
    ctrl->addItem ("Low Pass",    1);
	  ctrl->addItem ("High Pass",   2);
    // 3
	  ctrl->addItem ("Band Pass",   4);
	  ctrl->addItem ("Band Stop",   5);
	  break;

  case 8: // Custom
    ctrl->addItem ("Two-Pole", 1);
    ctrl->addItem ("One-Pole", 2);
  };
}

void MainPanel::paint (Graphics& g)
{
	g.fillAll (Colour (0xffc1d0ff));
}

//------------------------------------------------------------------------------

template <class DesignType, class StateType>
void MainPanel::createFilterDesign (Dsp::Filter** pFilter, Dsp::Filter** pAudioFilter)
{
  switch (m_menuSmoothing->getSelectedId())
  {
  case 1:
    *pAudioFilter = new Dsp::SmoothedFilterDesign <DesignType, 2, StateType> (1024);
    break;

  default:
    *pAudioFilter = new Dsp::FilterDesign <DesignType, 2, StateType>;
    break;
  };
}

template <class DesignType>
void MainPanel::createFilterState (Dsp::Filter** pFilter, Dsp::Filter** pAudioFilter)
{
  *pFilter = new Dsp::FilterDesign <DesignType, 1>;

  switch (m_menuStateType->getSelectedId())
  {
  case 1: createFilterDesign <DesignType, Dsp::DirectFormI> (pFilter, pAudioFilter); break;
  case 2: createFilterDesign <DesignType, Dsp::DirectFormII> (pFilter, pAudioFilter); break;
  case 3: createFilterDesign <DesignType, Dsp::TransposedDirectFormI> (pFilter, pAudioFilter); break;
  case 4: createFilterDesign <DesignType, Dsp::TransposedDirectFormII> (pFilter, pAudioFilter); break;
  default:
    createFilterDesign <DesignType, Dsp::DirectFormI> (pFilter, pAudioFilter);
  };
}

void MainPanel::createFilter ()
{
  Dsp::Filter* f = 0;
  Dsp::Filter* fo = 0;

  const int familyId = m_menuFamily->getSelectedId();
  const int typeId = m_menuType->getSelectedId();

  //
  // RBJ
  //
  if (familyId == 1)
  {
    switch (typeId)
    {
    case 1: createFilterState <Dsp::RBJ::Design::LowPass> (&f, &fo); break;
    case 2: createFilterState <Dsp::RBJ::Design::HighPass> (&f, &fo); break;
    case 3: createFilterState <Dsp::RBJ::Design::BandPass1> (&f, &fo); break;
    case 4: createFilterState <Dsp::RBJ::Design::BandPass2> (&f, &fo); break;
    case 5: createFilterState <Dsp::RBJ::Design::BandStop> (&f, &fo); break;
    case 6: createFilterState <Dsp::RBJ::Design::LowShelf> (&f, &fo); break;
    case 7: createFilterState <Dsp::RBJ::Design::HighShelf> (&f, &fo); break;
    case 8: createFilterState <Dsp::RBJ::Design::BandShelf> (&f, &fo); break;
    case 9: createFilterState <Dsp::RBJ::Design::AllPass> (&f, &fo); break;
    };
  }
  //
  // Butterworth
  //
  else if (familyId == 2)
  {
    switch (typeId)
    {
    case 1: createFilterState <Dsp::Butterworth::Design::LowPass   <50> > (&f, &fo); break;
    case 2: createFilterState <Dsp::Butterworth::Design::HighPass  <50> > (&f, &fo); break;
    case 4: createFilterState <Dsp::Butterworth::Design::BandPass  <50> > (&f, &fo); break;
    case 5: createFilterState <Dsp::Butterworth::Design::BandStop  <50> > (&f, &fo); break;
    case 6: createFilterState <Dsp::Butterworth::Design::LowShelf  <50> > (&f, &fo); break;
    case 7: createFilterState <Dsp::Butterworth::Design::HighShelf <50> > (&f, &fo); break;
    case 8: createFilterState <Dsp::Butterworth::Design::BandShelf <50> > (&f, &fo); break;
    };
  }
  //
  // Chebyshev I
  //
  else if (familyId == 3)
  {
    switch (typeId)
    {
    case 1: createFilterState <Dsp::ChebyshevI::Design::LowPass   <50> > (&f, &fo); break;
    case 2: createFilterState <Dsp::ChebyshevI::Design::HighPass  <50> > (&f, &fo); break;
    case 4: createFilterState <Dsp::ChebyshevI::Design::BandPass  <50> > (&f, &fo); break;
    case 5: createFilterState <Dsp::ChebyshevI::Design::BandStop  <50> > (&f, &fo); break;
    case 6: createFilterState <Dsp::ChebyshevI::Design::LowShelf  <50> > (&f, &fo); break;
    case 7: createFilterState <Dsp::ChebyshevI::Design::HighShelf <50> > (&f, &fo); break;
    case 8: createFilterState <Dsp::ChebyshevI::Design::BandShelf <50> > (&f, &fo); break;
    };
  }
  //
  // Chebyshev II
  //
  else if (familyId == 4)
  {
    switch (typeId)
    {
    case 1: createFilterState <Dsp::ChebyshevII::Design::LowPass   <50> > (&f, &fo); break;
    case 2: createFilterState <Dsp::ChebyshevII::Design::HighPass  <50> > (&f, &fo); break;
    case 4: createFilterState <Dsp::ChebyshevII::Design::BandPass  <50> > (&f, &fo); break;
    case 5: createFilterState <Dsp::ChebyshevII::Design::BandStop  <50> > (&f, &fo); break;
    case 6: createFilterState <Dsp::ChebyshevII::Design::LowShelf  <50> > (&f, &fo); break;
    case 7: createFilterState <Dsp::ChebyshevII::Design::HighShelf <50> > (&f, &fo); break;
    case 8: createFilterState <Dsp::ChebyshevII::Design::BandShelf <50> > (&f, &fo); break;
    };
  }
  //
  // Elliptic
  //
  else if (familyId == 5)
  {
    switch (typeId)
    {
    case 1: createFilterState <Dsp::Elliptic::Design::LowPass  <50> > (&f, &fo); break;
    case 2: createFilterState <Dsp::Elliptic::Design::HighPass <50> > (&f, &fo); break;
    case 4: createFilterState <Dsp::Elliptic::Design::BandPass <50> > (&f, &fo); break;
    case 5: createFilterState <Dsp::Elliptic::Design::BandStop <50> > (&f, &fo); break;
    };
  }
  //
  // Bessel
  //
  else if (familyId == 6)
  {
    switch (typeId)
    {
    case 1: createFilterState <Dsp::Bessel::Design::LowPass  <25> > (&f, &fo); break;
    case 2: createFilterState <Dsp::Bessel::Design::HighPass <25> > (&f, &fo); break;
    case 4: createFilterState <Dsp::Bessel::Design::BandPass <25> > (&f, &fo); break;
    case 5: createFilterState <Dsp::Bessel::Design::BandStop <25> > (&f, &fo); break;
    case 6: createFilterState <Dsp::Bessel::Design::LowShelf <25> > (&f, &fo); break;
    };
  }
  //
  // Legendre
  //
  else if (familyId == 7)
  {
    switch (typeId)
    {
    case 1: createFilterState <Dsp::Legendre::Design::LowPass  <25> > (&f, &fo); break;
    case 2: createFilterState <Dsp::Legendre::Design::HighPass <25> > (&f, &fo); break;
    case 4: createFilterState <Dsp::Legendre::Design::BandPass <25> > (&f, &fo); break;
    case 5: createFilterState <Dsp::Legendre::Design::BandStop <25> > (&f, &fo); break;
    };
  }
  //
  // Custom
  //
  else if (familyId == 8)
  {
    switch (typeId)
    {
    case 1: createFilterState <Dsp::Custom::Design::TwoPole> (&f, &fo); break;
    case 2: createFilterState <Dsp::Custom::Design::OnePole> (&f, &fo); break;
    };
  }

  if (f)
  {
    // TODO: Copy the parameters over in an intelligent way
    f->copyParamsFrom (m_filter);
    m_filter = f;
    //m_filter->setParams (m_filter->getDefaultParams());
   
    m_listeners.call (&FilterListener::onFilterChanged, m_filter);

    if (fo)
      fo->setParams (m_filter->getParams ());
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

  case 2: // sine wave
    {
      ToneGeneratorAudioSource* tgas = new ToneGeneratorAudioSource ();
      tgas->setFrequency (440);
      tgas->setAmplitude (1.f);
      source = tgas;
    }
    break;

  case 3: // White Noise
    source = new NoiseAudioSource;
    break;

  case 4: // Pink Noise
    source = new NoiseAudioSource (true);
    break;
  };

  MainApp::getInstance().getAudioOutput().setSource (source);
}

void MainPanel::buttonClicked (Button* ctrl)
{
  if (ctrl == m_resetButton)
  {
    MainApp::getInstance().getAudioOutput().resetFilter();
  }
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
      if (m_menuType->indexOfItemId (m_lastTypeId) != -1 )
      {
        id = m_lastTypeId;
      }
    }
    m_menuType->setSelectedId (id);
  }
  else if (ctrl == m_menuType)
  {
    m_lastTypeId = m_menuType->getSelectedId();

    createFilter ();
  }
  else if (ctrl == m_menuStateType )
  {
    createFilter ();
  }
  else if (ctrl == m_menuSmoothing)
  {
    createFilter ();
  }
  else if (ctrl == m_menuAudio)
  {
    setAudio (ctrl->getSelectedId());
  }
}

void MainPanel::onFilterParameters ()
{
  MainApp::getInstance().getAudioOutput().setFilterParameters (
    m_filter->getParams());
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
