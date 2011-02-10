#include "Common.h"
#include "DemoPanel.h"
#include "BrickWallGraph.h"
#include "MainApp.h"
#include "CustomSlider.h"

class PhaseGraph : public FilterGraph
{
public:
	PhaseGraph()
	{
		m_szTitle="Phase (deg.)";
	}

	double NormToFuncX( double x, bool bInverse )
	{
		return NormToFreq( x, bInverse );
	}

	double NormToFuncY( double y, bool bInverse )
	{
		const int angle=110;
		if( bInverse )
			// [-angle..angle] -> [0..1]
			return 0.5+(y/(angle*2));
		else
			// [0..1] -> [-angle..angle]
			return angle*((y*2)-1);
	}

	double Func( double x )
	{
		Dsp::Complex c=m_filter->Response( 2*Dsp::kPi*x/m_spec->sampleRate );
		double y=std::arg(c);
		return 90*(y/Dsp::kPi);
	}

	void DrawExtras( Graphics &g )
	{
		g.setColour( m_cAxis );
		DrawAxisX( g, 0 );
		g.setColour( m_cAxisMinor );
		DrawAxisX( g, 90 );
		DrawAxisX( g, -90 );

		DrawCutoff( g );
	}
};

//------------------------------------------------------------------------------

class ResponseGraph : public FilterGraph
{
public:
	ResponseGraph()
	{
		m_szTitle="Response (dB)";
	}

	double NormToFuncX( double x, bool bInverse )
	{
		return NormToFreq( x, bInverse );
	}

	double NormToFuncY( double y, bool bInverse )
	{
		const int dbMin=-48;
		const int dbMax=12;
		if( bInverse )
			// [-48..24] dB to [0..1]
			return (y-dbMin)/(dbMax-dbMin);
		else
			// [0..1] to [-48..24]
			return (dbMax-dbMin)*y+dbMin;
	}

	double Func( double x )
	{
		Dsp::Complex c=m_filter->Response( 2*Dsp::kPi*x/m_spec->sampleRate );
		double y=std::abs(c);
		// convert to decibels
		if( y<0.00001 )
			y=-1000;
		else
			y=20*log10(y);
		return y;
	}

	void DrawExtras( Graphics &g )
	{
		g.setColour( m_cAxis );
		DrawAxisX( g, 0 );

		g.setColour( m_cAxisMinor );
		DrawAxisX( g, -3 );
		for( int i=1;i<10;i++ )
		{
			DrawAxisX( g,  6*i );
			DrawAxisX( g, -6*i );
		}

		DrawAxisY( g, 100 );
		DrawAxisY( g, 1000 );
		DrawAxisY( g, 10000 );
		DrawAxisY( g, 20000 );

		DrawCutoff( g );
	}
};

//------------------------------------------------------------------------------

class DelayGraph : public FilterGraph
{
public:
	DelayGraph()
	{
		m_szTitle="Phase Delay (s)";
	}

	double NormToFuncX( double x, bool bInverse )
	{
		return NormToFreq( x, bInverse );
	}

	double NormToFuncY( double y, bool bInverse )
	{
		const int ymin=-3;
		const int ymax=3;
		if( bInverse )
		{
			// [ymin..ymax] -> [0..1]
			return (y-ymin)/(ymax-ymin);
		}
		else
		{
			// [0..1] -> [ymin..ymax]
			return ymin+y*(ymax-ymin);
		}
	}

	double Func( double x )
	{
		double w=2*Dsp::kPi*x/m_spec->sampleRate;
		Dsp::Complex c=m_filter->Response( w );
		double y;
		if( w!=0 )
			y=-std::abs(c)/w;
		else
			y=0;
		return y;
	}

	void DrawExtras( Graphics &g )
	{
		g.setColour( m_cAxis );
		DrawAxisX( g, 0 );

		g.setColour( m_cAxisMinor );
		DrawAxisX( g, -1 );
		DrawAxisX( g,  1 );

		DrawCutoff( g );
	}
};

//------------------------------------------------------------------------------

class StepGraph : public FilterGraph
{
public:
	StepGraph()
	{
		m_szTitle="Step Response";
	}

	double NormToFuncX( double x, bool bInverse )
	{
		return NormToFreq( x, bInverse );
	}

	double Func( double x )
	{
		Dsp::Complex c=m_filter->Response( 2*Dsp::kPi*x/m_spec->sampleRate );
		double y=std::abs(c);
		return y;
	}
};

//------------------------------------------------------------------------------

class PoleChart : virtual public Component, public FilterChart
{
public:
	void Recalculate( void )
	{
		repaint();
	}

	void paint( Graphics &g )
	{
		Colour cBack(0xfff8f8f8);
		Colour cValue(0xff000000);
		Colour cPole(0xd0ff0000);
		Colour cZero(0xd02020ff);
		
		Rectangle<int> rc = getLocalBounds();

		int size=getWidth();
		if( size>getHeight() )
			size=getHeight();

		g.fillAll( cBack );

		g.setColour( m_cFrame );
		g.drawRect( rc.getX(), rc.getY(), rc.getRight(), rc.getBottom() );

		Rectangle<int> r = rc.expanded (1, 1);

		float xi0=float(r.getCentreX());
		float yi0=float(r.getCentreY());

		g.setColour( m_cAxis );
		g.drawLine( xi0, float(r.getY()), xi0, float(r.getBottom()) );
		g.drawLine( float(r.getX()), yi0, float(r.getRight()), yi0 );
		g.drawEllipse( float(xi0-size/3), float(yi0-size/3), float(size/1.5), float(size/1.5), 1 );

		g.setColour( cPole );
		for( int i=0;i<m_filter->CountPoles();i++ )
		{
			const Dsp::Complex &c=m_filter->Poles().GetNth( i );
			float xi=xi0+int(c.real()*size/3);
			float yi=yi0+int(c.imag()*size/3);
			g.drawLine( xi-3, yi-3, xi+4, yi+4 );
			g.drawLine( xi-3, yi+3, xi+4, yi-4 );
		}

		g.setColour( cZero );
		for( int i=0;i<m_filter->CountZeros();i++ )
		{
			const Dsp::Complex &c=m_filter->Zeros().GetNth( i );
			float xi=xi0+int(c.real()*size/3);
			float yi=yi0+int(c.imag()*size/3);
			g.drawEllipse( float(xi-3.5), float(yi-3.5), 7, 7, 1 );
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
};

//------------------------------------------------------------------------------

DemoPanel::DemoPanel()
	:ResizableLayout (this) 	
{
	int x0=8;
	int y0=8;
	int x=x0;
	int y;
	int tw;
	int th;

	for( int i=0;i<knobCount;i++ )
	{
		tw=70; // text box width
		th=14; // text box height
		int sw=40; // knob width
		int sh=40; // knob height

		double v0, v1, vinc=0;
		const char *szLabel;
		const char *szUnits;
		switch( i )
		{
		case idOrd:	szLabel="Ord."; szUnits=""; v0=1; v1=kMaxOrder; vinc=1; break;
		case idFreq: szLabel="Freq."; szUnits="Hz"; v0=10; v1=kSampleRate/2-20; vinc=1; break;
		case idWid:	szLabel="Wid."; szUnits="Hz"; v0=1; v1=kSampleRate/2-20; vinc=1; break;
		case idRip:	szLabel="Rip."; szUnits="dB"; v0=0; v1=6; vinc=0.001; break;
		case idAtt:	szLabel="Att."; szUnits="dB"; v0=0; v1=48; vinc=0.001; break;
		case idGain: szLabel="Gain"; szUnits="dB"; v0=-12; v1=12; vinc=0.01; break;
		case idSlope: szLabel="Slope"; szUnits=""; v0=0.0000001; v1=.0001; vinc=v0; break;
		default:
			szLabel="?";
			szUnits="?";
			break;
		}

		y=y0+((i&1)?th:0);
		Slider::TextEntryBoxPosition textPos;
		textPos=(i&1)?Slider::TextBoxBelow:Slider::TextBoxAbove;
		m_knob[i]=new CustomSlider(String::empty);
		m_knob[i]->setSliderStyle (Slider::RotaryVerticalDrag);
		m_knob[i]->setRotaryParameters (float_Pi * 1.2f, float_Pi * 2.8f, false);
		m_knob[i]->setTextBoxStyle( textPos, false, tw, th);
		m_knob[i]->setBounds( x, y, std::max(sw,tw), sh+th );
		m_knob[i]->setTextValueSuffix( szUnits );
		m_knob[i]->setRange( v0, v1, vinc );
		m_knob[i]->setVelocityBasedMode( false );
		addAndMakeVisible( m_knob[i] );
		m_knob[i]->addListener( this );

		y=y0+((i&1)?0:sh+th);
		Label *label=new Label(String::empty, szLabel );
		label->setFont( Font(12, Font::plain) );
	    label->setJustificationType( Justification::centred );
	    label->setEditable( false, false, false );
	    label->setJustificationType( Justification::centred );
	    label->setJustificationType( Justification::centred );
		label->setColour( Label::textColourId, Colours::black );
		label->setColour( TextEditor::textColourId, Colours::black );
		label->setColour( TextEditor::backgroundColourId, Colour(0x0) );
	    label->setBounds( x, y, tw, th );
		addAndMakeVisible( label );

		x=x+sw+12;
	}

	y=y0;
	x+=32;

	tw=160; // menu size
	th=20;

	m_menuProto=new ComboBox( String::empty );
	m_menuProto->addItem( "Butterworth", idButter );
	m_menuProto->addItem( "Chebyshev", idChebyI );
	m_menuProto->addItem( "Inverse Chebyshev", idChebyII );
	m_menuProto->addItem( "Elliptic", idElliptic );
	m_menuProto->addItem( "Bessel", idBessel );
	m_menuProto->addItem( "Legendere", idLegendere );
	m_menuProto->setSelectedId( idButter );
	m_menuProto->setBounds( x, y, tw, th );
	addAndMakeVisible( m_menuProto );
	m_menuProto->addListener( this );

	m_menuKind=new ComboBox( String::empty );
	m_menuKind->addItem( "Low Pass", idLowPass );
	m_menuKind->addItem( "High Pass", idHighPass );
	m_menuKind->addItem( "Band Pass", idBandPass );
	m_menuKind->addItem( "Band Stop", idBandStop );
	m_menuKind->addItem( "Low Shelf", idLowShelf );
	m_menuKind->addItem( "High Shelf", idHighShelf );
	m_menuKind->addItem( "Peak/Notch Eq", idPeakEq );
	m_menuKind->setSelectedId( idLowPass );
	m_menuKind->setBounds( x, y+th+8, tw, th );
	addAndMakeVisible( m_menuKind );
	m_menuKind->addListener( this );

	x=x0;
	y=y+80;

	// Graphs

	FilterChart *chart;

	chart=new BrickWallGraph();
	chart->setBounds( x, y, 200, 200 );
	addAndMakeVisible( chart );
	m_chart[idBrick]=chart;
	addToLayout( chart, anchorTopLeft, Point<int>(33, 33));
	x=x+200+8;

	chart=new PhaseGraph();
	chart->setBounds( x, y, 200, 200 );
	addAndMakeVisible( chart );
	m_chart[idPhase]=chart;
	addToLayout( chart, Point<int>( 33, 0 ), Point<int>( 66, 33 ) );
	x=x+200+8;

	chart=new PoleChart();
	chart->setBounds( x, y, 200, 200 );
	addAndMakeVisible( chart );
	m_chart[idPoles]=chart;
	addToLayout( chart, Point<int>( 66, 0 ), Point<int>( 100, 33 ) );
	x=x+200+8;

	y=y+200+8;

	x=x0;

	chart=new ResponseGraph();
	chart->setBounds( x, y, 400+8, 400+8 );
	addAndMakeVisible( chart );
	m_chart[idResponse]=chart;
	addToLayout( chart, Point<int>( 0, 33 ), Point<int>( 66, 100 ) );
	x=x+400+8+8;

	chart=new DelayGraph();
	chart->setBounds( x, y, 200, 200 );
	addAndMakeVisible( chart );
	m_chart[idDelay]=chart;
	addToLayout( chart, Point<int>( 66, 33 ), Point<int>( 100, 66 ) );
	y=y+200+8;

	chart=new StepGraph();
	chart->setBounds( x, y, 200, 200 );
	addAndMakeVisible( chart );
	m_chart[idStep]=chart;
	addToLayout( chart, Point<int>( 66, 66 ), Point<int>( 100, 100 ) );
	y=y+200+8;
	x=x+200+8;

	//

	setSize( x, y );

	activateLayout();

	SpecDefaults( &m_spec );
	SpecToCtrls();
}

//------------------------------------------------------------------------------

DemoPanel::~DemoPanel()
{
	deleteAllChildren();
}

//------------------------------------------------------------------------------

void DemoPanel::SpecDefaults( Spec *spec )
{
	spec->order=2;
	spec->sampleRate=44100;
	spec->cutoffFreq=spec->sampleRate/4;
//	spec->cutoffFreq=1;
	spec->passRippleDb=0.1;
	spec->stopBandDb=12;
	spec->centerFreq=spec->cutoffFreq;
	spec->normWidth=0.125;
	spec->gainDb=3;
	spec->rollOff=0.5;
	spec->proto=idButter;
	spec->kind=idLowPass;
//	spec->kind=idBandPass;
}

//------------------------------------------------------------------------------

void DemoPanel::SpecToCtrls( void )
{
	m_menuProto->setSelectedId( m_spec.proto, true );
	m_menuKind->setSelectedId( m_spec.kind, true );

	m_knob[idOrd]->setValue( m_spec.order, false );
	m_knob[idFreq]->setValue( m_spec.cutoffFreq, false );
	m_knob[idWid]->setValue( m_spec.normWidth*m_spec.sampleRate, false );
	m_knob[idRip]->setValue( m_spec.passRippleDb, false );
	m_knob[idAtt]->setValue( m_spec.stopBandDb, false );
	m_knob[idGain]->setValue( m_spec.gainDb, false );
	m_knob[idSlope]->setValue( m_spec.rollOff, false );

	m_filter=SpecToFilter( m_spec, &m_filters );
	m_filter->Setup( m_spec );

	for( int i=0;i<chartCount;i++ )
		m_chart[i]->SetFilter( m_filter, m_spec );
}

//------------------------------------------------------------------------------

Dsp::PoleFilterOld *DemoPanel::SpecToFilter( const Spec &spec, Filters *filters )
{
	Dsp::PoleFilterOld *filter=0;

	switch( spec.proto )
	{
	default:
	case idButter:
		switch( spec.kind )
		{
		default:
		case idLowPass: filter=&filters->butterLp; break;
		case idHighPass: filter=&filters->butterHp; break;
		case idBandPass: filter=&filters->butterBp; break;
		case idBandStop: filter=&filters->butterBs; break;
		case idLowShelf: filter=&filters->butterLs; break;
		case idHighShelf: filter=&filters->butterHs; break;
		case idPeakEq: filter=&filters->butterEq; break;
		};
		break;
	case idChebyI:
		switch( spec.kind )
		{
		default:
		case idLowPass: filter=&filters->chebyILp; break;
		case idHighPass: filter=&filters->chebyIHp; break;
		case idBandPass: filter=&filters->chebyIBp; break;
		case idBandStop: filter=&filters->chebyIBs; break;
		case idLowShelf: filter=&filters->chebyILs; break;
		case idHighShelf: filter=&filters->chebyIHs; break;
		case idPeakEq: filter=&filters->chebyIEq; break;
		};
		break;
	case idChebyII:
		switch( spec.kind )
		{
		default:
		case idLowPass: filter=&filters->chebyIILp; break;
		case idHighPass: filter=&filters->chebyIIHp; break;
		case idBandPass: filter=&filters->chebyIIBp; break;
		case idBandStop: filter=&filters->chebyIIBs; break;
		case idLowShelf: filter=&filters->chebyIILs; break;
		case idHighShelf: filter=&filters->chebyIIHs; break;
		case idPeakEq: filter=&filters->chebyIIEq; break;
		};
		break;
	case idElliptic:
		switch( spec.kind )
		{
		default:
		case idLowPass: filter=&filters->ellipticLp; break;
		case idHighPass: filter=&filters->ellipticHp; break;
		case idBandPass: filter=&filters->ellipticBp; break;
		case idBandStop: filter=&filters->ellipticBs; break;
		};
		break;
	case idBessel:
		switch( spec.kind )
		{
		default:
		case idLowPass: filter=&filters->besselLp; break;
		case idHighPass: filter=&filters->besselHp; break;
		case idBandPass: filter=&filters->besselBp; break;
		case idBandStop: filter=&filters->besselBs; break;
		};
		break;
	case idLegendere:
		switch( spec.kind )
		{
		default:
		case idLowPass: filter=&filters->legendereLp; break;
		};
		break;
	};

	return filter;
}

//------------------------------------------------------------------------------

void DemoPanel::paint( Graphics& g )
{
	g.fillAll( Colour(0xffc1d0ff) );
//    g.setColour (Colours::white);
  //  g.setColour (Colour (0xff6f6f6f));
//    g.strokePath (internalPath1, PathStrokeType (5.2000f));
}

//------------------------------------------------------------------------------

void DemoPanel::buttonClicked( Button *ctrl )
{
}

//------------------------------------------------------------------------------

void DemoPanel::comboBoxChanged( ComboBox *ctrl )
{
	if( ctrl==m_menuProto )
	{
		bool bChanged=false;

		int proto=ctrl->getSelectedId();
		switch( proto )
		{
		case idButter:
		case idChebyI:
		case idChebyII:
			m_menuKind->setItemEnabled( idLowPass, true );
			m_menuKind->setItemEnabled( idHighPass, true );
			m_menuKind->setItemEnabled( idBandPass, true );
			m_menuKind->setItemEnabled( idBandStop, true );
			m_menuKind->setItemEnabled( idLowShelf, true );
			m_menuKind->setItemEnabled( idHighShelf, true );
			m_menuKind->setItemEnabled( idPeakEq, true );
			break;
		case idElliptic:
		case idBessel:
			m_menuKind->setItemEnabled( idLowPass, true );
			m_menuKind->setItemEnabled( idHighPass, true );
			m_menuKind->setItemEnabled( idBandPass, true );
			m_menuKind->setItemEnabled( idBandStop, true );
			m_menuKind->setItemEnabled( idLowShelf, false );
			m_menuKind->setItemEnabled( idHighShelf, false );
			m_menuKind->setItemEnabled( idPeakEq, false );

			if( m_spec.kind==idLowShelf ||
				m_spec.kind==idHighShelf ||
				m_spec.kind==idPeakEq )
			{
				bChanged=true;
				m_spec.kind=idLowPass;
				m_menuKind->setSelectedId( m_spec.kind, true );
			}

			break;
		case idLegendere:
			m_menuKind->setItemEnabled( idLowPass, true );
			m_menuKind->setItemEnabled( idHighPass, false );
			m_menuKind->setItemEnabled( idBandPass, false );
			m_menuKind->setItemEnabled( idBandStop, false );
			m_menuKind->setItemEnabled( idLowShelf, false );
			m_menuKind->setItemEnabled( idHighShelf, false );
			m_menuKind->setItemEnabled( idPeakEq, false );

			if( m_spec.kind==idHighPass ||
				m_spec.kind==idBandPass ||
				m_spec.kind==idBandStop ||
				m_spec.kind==idLowShelf ||
				m_spec.kind==idHighShelf ||
				m_spec.kind==idPeakEq )
			{
				bChanged=true;
				m_spec.kind=idLowPass;
				m_menuKind->setSelectedId( m_spec.kind, true );
			}
			break;

		default:
			break;
		}

		if( m_spec.proto!=proto )
		{
			bChanged=true;
			m_spec.proto=proto;
		}

		if( bChanged )
		{
			m_filter=SpecToFilter( m_spec, &m_filters );
			m_filter->Setup( m_spec );

			for( int i=0;i<chartCount;i++ )
				m_chart[i]->SetFilter( m_filter, m_spec );
		}
	}
	else if( ctrl==m_menuKind )
	{
		int kind=m_menuKind->getSelectedId();

		if( m_spec.kind!=kind )
		{
			m_spec.kind=kind;

			m_filter=SpecToFilter( m_spec, &m_filters );
			m_filter->Setup( m_spec );

			for( int i=0;i<chartCount;i++ )
				m_chart[i]->SetFilter( m_filter, m_spec );
		}
	}
}

//------------------------------------------------------------------------------

void DemoPanel::sliderValueChanged( Slider *ctrl )
{
	int id=-1;
	for( int i=0;i<knobCount;i++ )
	{
		if( m_knob[i]==ctrl )
		{
			id=i;
			break;
		}
	}

	bool bChanged=true;

	switch( id )
	{
	case idOrd:
		m_spec.order=int(ctrl->getValue());
		break;
	case idFreq:
		m_spec.cutoffFreq=ctrl->getValue();
		m_spec.centerFreq=m_spec.cutoffFreq;
		break;
	case idWid:
		m_spec.normWidth=ctrl->getValue()/m_spec.sampleRate;
		break;
	case idRip:
		m_spec.passRippleDb=ctrl->getValue();
		break;
	case idAtt:
		m_spec.stopBandDb=ctrl->getValue();
		break;
	case idGain:
		m_spec.gainDb=ctrl->getValue();
		break;
	case idSlope:
		m_spec.rollOff=ctrl->getValue();
		break;
	default:
		bChanged=false;
		break;
	}

	if( bChanged )
	{
		m_filter->Setup( m_spec );

		for( int i=0;i<chartCount;i++ )
			m_chart[i]->Recalculate();
	}
}

const StringArray DemoPanel::getMenuBarNames()
{
  StringArray names;
  names.add (TRANS("File"));
  names.add (TRANS("Help"));
  return names;
}

const PopupMenu DemoPanel::getMenuForIndex (int topLevelMenuIndex, const String& menuName)
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

void DemoPanel::menuItemSelected (int menuItemID, int topLevelMenuIndex)
{
}
