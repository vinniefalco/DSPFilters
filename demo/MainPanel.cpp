#include "Common.h"
#include "CpuMeter.h"
#include "CustomSlider.h"
#include "GainChart.h"
#include "GroupDelayChart.h"
#include "MainApp.h"
#include "MainPanel.h"
#include "PhaseChart.h"

//------------------------------------------------------------------------------

// A Component which holds a set of knobs created a run time
// based on a filter's design specification and parameters.
class KnobPanel
  : public Component
  , public FilterListener
  , private Slider::Listener
{
private:
  ListenerList<FilterListener>& m_listeners;
public:
  KnobPanel (ListenerList<FilterListener>& listeners)
    : m_listeners (listeners)
  {
  }

  ~KnobPanel ()
  {
    clear ();
  }

  void onFilterChanged (Dsp::Filter* newFilter)
  {
    setFilter (newFilter);
  }

  void clear ()
  {
    for (int i = 0; i < m_items.size(); ++i)
    {
      delete m_items[i].label;
      delete m_items[i].knob;
    }

    m_items.clear ();
  }

  void setFilter (Dsp::Filter* filter)
  {
    clear ();

    const Rectangle<int> bounds = getLocalBounds();

    const int w = 60;
    const int h = 40;
    const int tw = 70;
    const int th = 14;
    const int y0 = bounds.getY();

    int x = bounds.getX();
    for (int i = 0; i < filter->getNumParameters(); ++i)
    {
      const Dsp::ParameterInfo& info =
        filter->getParameterInfo(i);

      const int y = y0 + ((i & 1) ? th : 0);

      Item item;
		  Slider::TextEntryBoxPosition textPos;
		  textPos = (i & 1) ? Slider::TextBoxBelow : Slider::TextBoxAbove;
      item.knob = new CustomSlider (String::empty);
      item.knob->setSliderStyle (Slider::RotaryVerticalDrag);
      item.knob->setRotaryParameters (float_Pi * 1.2f, float_Pi * 2.8f, false);
      item.knob->setBounds (x, y, std::max (w, tw), h + th);
      item.knob->setRange (info.minValue, info.maxValue);
      item.knob->setVelocityBasedMode (false);
      item.knob->setTextBoxStyle (textPos, false, tw, th);
      item.knob->setTextBoxIsEditable (false);
      item.knob->addListener (this);
      item.knob->setValue (filter->getParameters()[i], false);
      addAndMakeVisible (item.knob);
      m_items.add (item);

      x += w + 12;
    }

    m_filter = filter;
  }

  void sliderValueChanged (Slider* ctrl)
  {
    for (int i = 0; i < m_items.size(); ++i)
    {
      if (m_items[i].knob == ctrl)
      {
        Dsp::Parameters parameters = m_filter->getParameters();
        parameters[i] = ctrl->getValue ();
        m_filter->setParameters (parameters);
        /*
        double flo = 10./44100.;
        double fhi = (22050-10)/44100.;
        normalizedFrequency = jlimit (flo, fhi, normalizedFrequency);

        Dsp::Parameters parameters;
        parameters[0] = normalizedFrequency;
        parameters[1] = 3;
        m_filter->setParameters (parameters);
        */
        m_listeners.call (&FilterListener::onFilterParameters);
        break;
      }
    }
  }

private:
  struct Item
  {
    Item ()
    {
      label = 0;
      knob = 0;
    }

    Label* label;
    Slider* knob;
  };

  Array<Item> m_items;
  Dsp::Filter* m_filter;
};

//------------------------------------------------------------------------------

MainPanel::MainPanel()
	: ResizableLayout (this) 	
{
  const int w = 512;
  const int h = 512 + 72;
  int y;

  m_listeners.add (this);

  {
    m_knobPanel = new KnobPanel (m_listeners);
    m_knobPanel->setBounds (4, 4, 496, 68);
    addToLayout (m_knobPanel, anchorTopLeft, anchorTopRight);
    addAndMakeVisible (m_knobPanel);
    m_listeners.add (m_knobPanel);

    y = m_knobPanel->getBottom();
  }

  {
    CpuMeter* c = new CpuMeter (MainApp::getInstance().getAudioOutput().getAudioDeviceManager());
    c->setBounds (424, 8, 80, 14);
    addToLayout (c, anchorTopRight);
    addAndMakeVisible (c);
  }

  {
	  m_menuFilter=new ComboBox( String::empty );
	  m_menuFilter->addItem ("RBJ Low Pass", 1 );
	  m_menuFilter->addItem ("RBJ High Pass", 2 );
	  m_menuFilter->addItem ("RBJ Band Pass 1", 3 );
	  m_menuFilter->addItem ("RBJ Band Pass 2", 4 );
	  m_menuFilter->addItem ("RBJ Band Stop", 5);
	  m_menuFilter->addItem ("RBJ Low Shelf", 6);
	  m_menuFilter->addItem ("RBJ High Shelf", 7);
	  m_menuFilter->addItem ("RBJ Band Shelf", 8);
	  m_menuFilter->addItem ("RBJ All Pass", 9);
	  m_menuFilter->addItem ("Butterworth Low Pass", 10);
	  m_menuFilter->addItem ("Butterworth High Pass", 11);
	  m_menuFilter->addItem ("Butterworth Low Shelf", 12);
	  m_menuFilter->setBounds (342, 26, 512-350, 28);
	  m_menuFilter->addListener(this);
    addToLayout (m_menuFilter, anchorTopRight);
	  addAndMakeVisible (m_menuFilter);
  }

  const Rectangle<int> r (4, y + 4, w - 8, h - (y + 8));
  createCharts (r);

	setSize (w, h);

	activateLayout();

  m_menuFilter->setSelectedId (1);
}

MainPanel::~MainPanel()
{
	deleteAllChildren();
}

/*

Gain Phase Poles

Response   Delay
Response
Response   Step
*/
void MainPanel::createCharts (const Rectangle<int>& r)
{
  const int gap = 4;
  const int w = (r.getWidth()  - (2 * gap)) / 3;
  const int h = (r.getHeight() - (2 * gap)) / 3;
  const int w2 = r.getWidth()  - (w + gap);
  const int h2 = r.getHeight() - (h + gap);

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
}

void MainPanel::paint( Graphics& g )
{
	g.fillAll (Colour (0xffc1d0ff));
}

void MainPanel::setFilter (int id)
{
  Dsp::Filter* f = 0;
  Dsp::Filter* fo = 0;

  switch (id)
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

  case 10:
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
  
  case 11:
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

  case 12:
    f  = new Dsp::FilterType <
      Dsp::PoleZeroDesign <4,
                           Dsp::detail::ButterworthLowShelf,
                           Dsp::detail::LowPassTransformation> >;
    fo  = new Dsp::SmoothedFilter <
      Dsp::PoleZeroDesign <4,
                           Dsp::detail::ButterworthLowShelf,
                           Dsp::detail::LowPassTransformation>,
      Dsp::ChannelsState <2,
                          Dsp::Cascade <2>::State <
                            Dsp::Biquad::DirectFormIState> > > (1024);
    break;

  default:
    break;
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

void MainPanel::onFilterParameters ()
{
  MainApp::getInstance().getAudioOutput().setFilterParameters (
    m_filter->getParameters());
}

void MainPanel::buttonClicked (Button* ctrl)
{
}

void MainPanel::comboBoxChanged (ComboBox* ctrl)
{
  if (ctrl == m_menuFilter)
    setFilter (ctrl->getSelectedId());
}

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
