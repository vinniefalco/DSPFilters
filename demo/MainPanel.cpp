#include "Common.h"
#include "CustomSlider.h"
#include "FilterChart.h"
#include "MainApp.h"
#include "MainPanel.h"

//------------------------------------------------------------------------------

class ResponseGraph2
  : public GraphComponent
  , public FilterListener
{
private:
  Dsp::Filter* m_filter;
  float m_scale_y;

public:
  Path m_path;

  ResponseGraph2 ()
    : m_filter (0)
    , m_scale_y (1)
  {
  }

  void paint (Graphics& g)
  {
    paintBackground (g);

    Rectangle<int> bounds = getLocalBounds ();
    Rectangle<int> r = bounds.reduced (4, 4);

    AffineTransform t = AffineTransform::
      scale (r.getWidth(), -r.getHeight()*m_scale_y).
      translated (r.getX(), r.getBottom());

    g.setColour (Colour::fromRGBA (0, 0, 0, 12));
    g.fillPath (m_path, t);
    g.setColour (Colours::blue);
    g.strokePath (m_path, 1, t);
  }

  void calcPath ()
  {
    m_path.clear();
    if (m_filter)
    {
      Rectangle<int> bounds = getLocalBounds ();
      Rectangle<int> r = bounds.reduced (4, 4);
      m_path.startNewSubPath (0, 0);
      for (int xi = 0; xi <= r.getWidth(); ++xi )
      {
        float x = xi / float(r.getWidth()-1);
        Dsp::complex_t c = m_filter->response (x/2);
        float y = std::abs(c);
        m_path.lineTo (x, y);
      }
      m_path.lineTo (1, 0);
      m_path.closeSubPath();
    }

    float yh = m_path.getBounds().getHeight();
    m_scale_y = (yh > 1) ? (1/yh) : 1;

    repaint();
  }

  void onFilterChanged (Dsp::Filter* newFilter)
  {
    m_filter = newFilter;
    calcPath ();
  }

  void onFilterParameters ()
  {
    calcPath ();
  }
};

//------------------------------------------------------------------------------

class PoleChart2
  : public GraphComponent
  , public FilterListener
{
private:
  double m_max;
  Dsp::Filter* m_filter;
  Dsp::PoleZeros m_pz;

public:
  PoleChart2 ()
    : m_filter (0)
  {
  }

  void onFilterChanged (Dsp::Filter* newFilter)
  {
    setFilter (newFilter);
  }

  void onFilterParameters ()
  {
    update ();
  }

  void clear ()
  {
    m_max = 0;
    m_pz.poles.clear();
    m_pz.zeros.clear();
  }

  void setFilter (Dsp::Filter* filter)
  {
    m_filter = filter;

    update();
  }

  void update ()
  {
    clear ();

    if (m_filter)
      addPoleZeros (m_filter->getPoleZeros());

    repaint ();
  }

	void paint( Graphics &g )
	{
    paintBackground (g);

		Colour cPole (0xd0ff0000);
		Colour cZero (0xd02020ff);
		
		Rectangle<int> bounds = getLocalBounds();

		int size = (jmin (getWidth(), getHeight()) + 2) / 3;

    // scale the graph down if the pole/zeroes lie outside the unit disc
    AffineTransform t = AffineTransform::identity;

    {
      double margin = 0.2;
      if (m_max > 1 + margin)
      {
        t = t.scaled (1/(m_max-margin), 1/(m_max-margin));
      }
    }

    t = t.scaled (size, -size);
    t = t.translated (bounds.getCentreX (), bounds.getCentreY ());

		g.setColour (m_cAxis);
    {
      Point<float> p = Point<float>(100000, 0).transformedBy (t);
      g.drawLine (-p.getX(), p.getY(), p.getX(), p.getY(), 1);
    }
    {
      Point<float> p = Point<float>(0, 100000).transformedBy (t);
      g.drawLine (p.getX(), -p.getY(), p.getX(), p.getY(), 1);
    }
    {
      Point<float> p0 = Point<float>(-1, -1).transformedBy (t);
      Point<float> p1 = Point<float>( 1,  1).transformedBy (t);
      g.drawEllipse (p0.getX(), p0.getY(),
                     p1.getX()-p0.getX(), p1.getY()-p0.getY(), 1);
    }

    const float r = 3.5f;

    g.setColour (cPole);
    for (size_t i = 0; i < m_pz.poles.size(); ++i)
    {
      Point<float> p (m_pz.poles[i].real(), m_pz.poles[i].imag());
      p = p.transformedBy (t);
      g.drawLine (p.getX()-r, p.getY()-r, p.getX()+r, p.getY()+r);
      g.drawLine (p.getX()+r, p.getY()-r, p.getX()-r, p.getY()+r);
    }

		g.setColour (cZero);
    for (size_t i = 0; i < m_pz.zeros.size(); ++i)
    {
      Point<float> p (m_pz.zeros[i].real(), m_pz.zeros[i].imag());
      p = p.transformedBy (t);
  	  g.drawEllipse (p.getX()-r, p.getY()-r, 2*r, 2*r, 1);
    }

		{
			g.setColour( m_cText );
			Rectangle<int> rc( 0, 0, getWidth(), getHeight() );
			Rectangle<int> rText = tlbr( rc.getY()+2, rc.getX()+2, rc.getY()+18, rc.getRight()-2 );
			g.drawFittedText(
				"Pole/Zero",
				rText.getX(),
				rText.getY(),
				rText.getWidth(),
				rText.getHeight(),
				Justification::topRight,
				1 );
		}
	}

private:
  void addPoleZeros (Dsp::PoleZeros pz)
  {
    for (size_t i = 0; i < pz.poles.size(); ++i)
    {
      m_pz.poles.push_back (pz.poles[i]);
      m_max = jmax (m_max, fabs(pz.poles[i].real()));
      m_max = jmax (m_max, fabs(pz.poles[i].imag()));
    }

    for (size_t i = 0; i < pz.zeros.size(); ++i)
    {
      m_pz.zeros.push_back (pz.zeros[i]);
      m_max = jmax (m_max, fabs(pz.zeros[i].real()));
      m_max = jmax (m_max, fabs(pz.zeros[i].imag()));
    }
  }

};

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
  int w = 512;
  int h = 384;

  m_listeners.add (this);

  {
    m_knobPanel = new KnobPanel (m_listeners);
    m_knobPanel->setBounds (4, 4, 496, 68);
    addToLayout (m_knobPanel, anchorTopLeft, anchorTopRight);
    addAndMakeVisible (m_knobPanel);

    m_listeners.add (m_knobPanel);
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
	  m_menuFilter->setBounds (342, 8, 512-350, 28);
	  m_menuFilter->addListener(this);
    addToLayout (m_menuFilter, anchorTopRight);
	  addAndMakeVisible (m_menuFilter);
  }

  {
    m_poleChart = new PoleChart2;
    m_poleChart->setBounds (4, 76, 246, 244);
    addToLayout (m_poleChart, anchorTopLeft, anchorBottomCenter);
    addAndMakeVisible (m_poleChart);

    m_listeners.add (m_poleChart);
  }

  {
    m_responseGraph = new ResponseGraph2;
    m_responseGraph->setBounds (258, 76, 246, 244);
    addToLayout (m_responseGraph, anchorTopCenter, anchorBottomRight);
    addAndMakeVisible (m_responseGraph);

    m_listeners.add (m_responseGraph);
  }

  m_menuFilter->setSelectedId (1);

#if 0
  Slider* s = new CustomSlider (String::empty);
  s->setSliderStyle (Slider::RotaryVerticalDrag);
  s->setRotaryParameters (float_Pi * 1.2f, float_Pi * 2.8f, false);
  s->setBounds (8, 8, 58, 58 );
  s->setRange (0, 0.5);
  s->setVelocityBasedMode (false);
  s->addListener (this);
  addAndMakeVisible (s);

  s->setValue (0.25);
#endif

	setSize (w, h);

	activateLayout();
}

MainPanel::~MainPanel()
{
	deleteAllChildren();
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
      Dsp::PoleZeroDesign <24,
                           Dsp::detail::ButterworthLowPass,
                           Dsp::detail::LowPassTransformation> >;
    fo  = new Dsp::SmoothedFilter <
      Dsp::PoleZeroDesign <24,
                           Dsp::detail::ButterworthLowPass,
                           Dsp::detail::LowPassTransformation>,
      Dsp::ChannelsState <2,
                          Dsp::Cascade <12>::State <
                            Dsp::Biquad::DirectFormIState> > > (1024);
    break;
  
  case 11:
    f  = new Dsp::FilterType <
      Dsp::PoleZeroDesign <15,
                           Dsp::detail::ButterworthLowPass,
                           Dsp::detail::HighPassTransformation> >;
    fo  = new Dsp::FilterType <
      Dsp::PoleZeroDesign <15,
                           Dsp::detail::ButterworthLowPass,
                           Dsp::detail::HighPassTransformation> >;
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
    {
      fo->setParameters (m_filter->getDefaultParameters());
      MainApp::getInstance().getAudioOutput().setFilter (fo);
    }
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
