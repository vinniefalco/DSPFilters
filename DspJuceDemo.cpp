/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See DspFilter.cpp for notes and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vincent Falco

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

********************************************************************************

This is a simple JUCE based demo application to show the usage and
functionality of Dsp Filters. In order to build the application you will
need to add all the source files in the DspFilters distribution to your
project/makefile, and additionally add the JUCE amalgamation header and
source file. The JUCE files are located at the official site:

http://www.rawmaterialsoftware.com/juce/

*******************************************************************************/

#include "DspJuceConfig.h"
#include "juce_amalgamated.h"

#include "DspFilter.h"

// juce uses floats as function parameters unfortunately, causing a ton of warnings.

#ifdef _MSC_VER
#pragma warning(disable:4250) // dominance
#pragma warning(disable:4244) // conversion from numeric type
#pragma warning(disable:4355) // 'this' used in ctor initializer
#endif

//******************************************************************************

//------------------------------------------------------------------------------

const int kSampleRate=44100;
const int kMaxOrder=50;

//******************************************************************************

// How the JUCE Rectangle and Point should have been
// Seriously why are the data members in there private?
// Except for that, JUCE kicks ass!

struct Rect
{
	Rect()
		{}
	Rect( int top0, int left0, int bottom0, int right0 )
		{ top=top0; left=left0; bottom=bottom0; right=right0; }
	Rect( const juce::Rectangle &r )
		{ top=int(r.getY()); left=int(r.getX()); bottom=int(r.getBottom()); right=int(r.getRight()); }
	operator juce::Rectangle( void ) const
		{ return juce::Rectangle( left, top, Width(), Height() ); }
	int Height( void ) const
		{ return bottom-top; }
	int Width( void ) const
		{ return right-left; }
	void Inset( int dx, int dy )
		{ top+=dy; left+=dx; bottom-=dy; right-=dx; }

	int top;
	int left;
	int bottom;
	int right;
};

//------------------------------------------------------------------------------

template<typename Ty>
struct TPoint
{
	TPoint()
		{ }
	TPoint( Ty x0, Ty y0 )
		{ x=x0; y=y0; }

	bool operator==( const TPoint<Ty> &rhs ) const
		{ return x==rhs.x && y==rhs.y; }
	bool operator!=( const TPoint<Ty> &rhs ) const
		{ return !this->operator==(rhs); }

	Ty x;
	Ty y;
};

typedef TPoint<long> Point;
typedef TPoint<double> Pointf;

//******************************************************************************

// Yes I know this class is awesome, feel free to use it.
class Layout
{
public:
	enum
	{
		anchorUnit=100
	};

	enum Style
	{
		styleStretch,
		styleFixedAspect
	};

	static const Point anchorNone;
	static const Point anchorTopLeft;
	static const Point anchorTopCenter;
	static const Point anchorTopRight;
	static const Point anchorMidLeft;
	static const Point anchorMidCenter;
	static const Point anchorMidRight;
	static const Point anchorBottomLeft;
	static const Point anchorBottomCenter;
	static const Point anchorBottomRight;

public:
	Layout( juce::Component *parent );
	~Layout();

	// Add a Component to the Layout.
	// topLeft and bottomRight are the percentages that the top left and bottom right of
	// the juce::Component should move by, when the layout is resized.
	// So if you wanted to have the control take on the full width of the parent, and
	// half the height, you would use bottomRight.x=50, bottomRight.y=100.
	void Add(
		juce::Component *ctrl,
		const Point &topLeft,
		const Point &bottomRight=anchorNone,
		Style style=styleStretch );

	// Remove a Component from the Layout.
	void Remove( juce::Component *ctrl );

	// Activate (or deactivate) the Layout. The Layout is initially inactive,
	// to prevent spurious recalculation while a Component and its children are being
	// constructed (causing resized() messages). Activating the Layout for the
	// first time will cause an Update().
	void Activate( bool bActive=true );

	// Update the anchor information for all items. This is used on the first Activate(),
	// and can also be used if multiple controls are moved or resized from elsewhere.
	void Update( void );

	// Call this to manually update the anchor information for a single control
	// after it has been moved or resized from elsewhere.
	void Update( juce::Component *ctrl );

	// Recalculate the position and size of all the controls in the layout, based
	// on the parent Component size. This is typically done from resized().
	void Recalculate( void );

private:
	struct Item;

	Item *Find( juce::Component *ctrl );
	void Update( Item *item );

private:
	struct Item
	{
		juce::Component *ctrl;
		Style	style;
		Point	topLeft;
		Point	bottomRight;
		Rect	margin;
		double	aspect;
	};

	juce::Component *m_parent;

	int		m_itemCount;
	int		m_itemMax;
	Item *	m_item;

	bool	m_bFirstTime;
	bool	m_bActive;
};

//------------------------------------------------------------------------------

const Point Layout::anchorNone			( -1, -1 );
const Point Layout::anchorTopLeft		( 0, 0 );
const Point Layout::anchorTopCenter		( anchorUnit/2, 0 );
const Point Layout::anchorTopRight		( anchorUnit, 0 );
const Point Layout::anchorMidLeft		( 0, anchorUnit/2 );
const Point Layout::anchorMidCenter		( anchorUnit/2, anchorUnit/2 );
const Point Layout::anchorMidRight		( anchorUnit, anchorUnit/2 );
const Point Layout::anchorBottomLeft	( 0, anchorUnit );
const Point Layout::anchorBottomCenter	( anchorUnit/2, anchorUnit );
const Point Layout::anchorBottomRight	( anchorUnit, anchorUnit );

//------------------------------------------------------------------------------

Layout::Layout( juce::Component *parent )
{
	m_parent=parent;
	m_itemCount=0;
	m_itemMax=0;
	m_item=0;
	m_bFirstTime=true;
	m_bActive=false;
}

//------------------------------------------------------------------------------

Layout::~Layout()
{
	if( m_item!=0 )
		free( m_item );
}

//------------------------------------------------------------------------------

void Layout::Add( juce::Component *ctrl, const Point &topLeft, const Point &bottomRight, Style style )
{
	if( m_itemCount>=m_itemMax )
	{
		int itemMax=m_itemMax+64;
		m_item=(Item *)realloc( m_item, itemMax*sizeof(m_item[0]) );
		m_itemMax=itemMax;
	}

	int i=m_itemCount++;
	Item *item=&m_item[i];
	item->ctrl=ctrl;
	item->style=style;

	assert( topLeft!=anchorNone );
	if( topLeft!=anchorNone )
		item->topLeft=topLeft;
	else
		item->topLeft=anchorTopLeft;
	item->bottomRight=bottomRight;
}

//------------------------------------------------------------------------------

void Layout::Remove( juce::Component *ctrl )
{
	Item *item=Find( ctrl );

	if( item!=0 )
	{
		int i=item-m_item;
		int last=m_itemCount-1;
		if( i!=last )
			m_item[i]=m_item[last];
		m_itemCount--;
	}
}

//------------------------------------------------------------------------------

void Layout::Activate( bool bActive )
{
	if( m_bActive!=bActive )
	{
		if( bActive && m_bFirstTime )
		{
			Update();
			m_bFirstTime=false;
		}

		m_bActive=bActive;
	}
}

//------------------------------------------------------------------------------

void Layout::Update( void )
{
	for( int i=0;i<m_itemCount;i++ )
		Update( &m_item[i] );
}

//------------------------------------------------------------------------------

void Layout::Update( juce::Component *ctrl )
{
	Item *item=Find( ctrl );
	if( item!=0 )
		Update( item );
}

//------------------------------------------------------------------------------

void Layout::Recalculate( void )
{
	if( m_bActive )
	{
		Rect rParent=m_parent->getBounds();
		for( int i=0;i<m_itemCount;i++ )
		{
			Item *item=&m_item[i];
			Rect rBounds;

			// the secret sauce
			rBounds.top=item->margin.top+(rParent.Height()*item->topLeft.y)/anchorUnit;
			rBounds.left=item->margin.left+(rParent.Width()*item->topLeft.x)/anchorUnit;
			if( item->bottomRight!=anchorNone )
			{
				rBounds.bottom=item->margin.bottom+(rParent.Height()*item->bottomRight.y)/anchorUnit;
				rBounds.right=item->margin.right+(rParent.Width()*item->bottomRight.x)/anchorUnit;
			}
			else
			{
				rBounds.bottom=rBounds.top+item->ctrl->getHeight();
				rBounds.right=rBounds.left+item->ctrl->getWidth();
			}

			if( item->style==styleStretch )
			{
				item->ctrl->setBounds( rBounds );
			}
			else if( item->style==styleFixedAspect )
			{
				Rect rItem;
				double aspect=double(rBounds.Width())/rBounds.Height();

				if( aspect>item->aspect )
				{
					rItem.top=rBounds.top;
					rItem.bottom=rBounds.bottom;
					int width=int(item->aspect*rItem.Height());
					rItem.left=rBounds.left+(rBounds.Width()-width)/2;
					rItem.right=rItem.left+width;
				}
				else
				{
					rItem.left=rBounds.left;
					rItem.right=rBounds.right;
					int height=int(1./item->aspect*rItem.Width());
					rItem.top=rBounds.top+(rBounds.Height()-height)/2;
					rItem.bottom=rItem.top+height;
				}

				item->ctrl->setBounds( rItem );
			}
		}
	}
}

//------------------------------------------------------------------------------

Layout::Item *Layout::Find( juce::Component *ctrl )
{
	Item *found;

	for( int i=0;i<m_itemCount;i++ )
	{
		if( m_item[i].ctrl==ctrl )
		{
			found=&m_item[i];
			break;
		}
	}

	return found;
}

//------------------------------------------------------------------------------

void Layout::Update( Item *item )
{
	Rect rBounds=item->ctrl->getBounds();
	// parent size
	Point ptSize( int(m_parent->getWidth()), int(m_parent->getHeight()) );

	// the secret sauce
	item->margin.top=rBounds.top-(ptSize.y*item->topLeft.y)/anchorUnit;
	item->margin.left=rBounds.left-(ptSize.x*item->topLeft.x)/anchorUnit;
	item->margin.bottom=rBounds.bottom-(ptSize.y*item->bottomRight.y)/anchorUnit;
	item->margin.right=rBounds.right-(ptSize.x*item->bottomRight.x)/anchorUnit;
	item->aspect=double(rBounds.Width())/rBounds.Height();
}

//******************************************************************************

class DspLookAndFeel : public juce::LookAndFeel
{
public:
};

//******************************************************************************
//
// FilterChart
//
//******************************************************************************

struct Spec : Dsp::Spec
{
	int proto;
	int kind;
};

//------------------------------------------------------------------------------

class FilterChart : virtual public juce::Component
{
public:
	FilterChart();
	~FilterChart();

	void SetFilter( const Dsp::PoleFilter *filter, const Spec &spec );
	virtual void Recalculate( void )=0;

protected:
	const Dsp::PoleFilter *m_filter;
	const Spec *m_spec;

	juce::Colour m_cFrame;
	juce::Colour m_cAxis;
	juce::Colour m_cAxisMinor;
	juce::Colour m_cText;
};

//------------------------------------------------------------------------------

FilterChart::FilterChart()
{
	m_filter=0;
	m_spec=0;

	m_cFrame=juce::Colour(0xff808080);
	m_cAxis=juce::Colour(0x80000000);
	m_cAxisMinor=juce::Colour(0x20000000);
	m_cText=juce::Colour(0xd0000000);
}

//------------------------------------------------------------------------------

FilterChart::~FilterChart()
{
}

//------------------------------------------------------------------------------

void FilterChart::SetFilter( const Dsp::PoleFilter *filter, const Spec &spec )
{
	m_filter=filter;
	m_spec=&spec;

	Recalculate();
}

//******************************************************************************
//
// Graph
//
//******************************************************************************

class Graph : virtual public juce::Component
{
public:
	Graph();
	~Graph();

	Rect GetClientRect( void )
		{ return Rect( 0, 0, getHeight(), getWidth() ); }

	// Normalized coordinates initially maps the bottom left of the
	// control to (0,0) and the top right to (1,1).

	// Map between client and normalized coordinates
	double NormToClientX( double x, bool bInverse=false );
	double NormToClientY( double y, bool bInverse=false );
	
	void DrawGraph( juce::Graphics &g );

	// map from normalized coordinates to function coordinates
	virtual double NormToFuncX( double x, bool bInverse=false )
		{ return x; }
	virtual double NormToFuncY( double y, bool bInverse=false )
		{ return y; }

	// Convenience functions for clarity
	double ClientToNormX( double x )
		{ return NormToClientX( x, true ); }
	double ClientToNormY( double y )
		{ return NormToClientY( y, true ); }
	double FuncToNormX( double x )
		{ return NormToFuncX( x, true ); }
	double FuncToNormY( double y )
		{ return NormToFuncY( y, true ); }
	double FuncToClientX( double x )
		{ return NormToClientX( FuncToNormX( x ) ); }
	double FuncToClientY( double x )
		{ return NormToClientY( FuncToNormY( x ) ); }

	virtual double Func( double x )=0;

private:
	// disallowed
    Graph(const Graph&);
    const Graph& operator=(const Graph&);

private:
    void resized();

private:
	double m_scale;		// scale factor applied to normalized coords
	Pointf m_ptOrigin;	// bottom left of graph in normalized coords
};

//------------------------------------------------------------------------------

Graph::Graph()
{
	m_scale=1;
	m_ptOrigin=Pointf( 0, 0 );
}

//------------------------------------------------------------------------------

Graph::~Graph()
{
}

//------------------------------------------------------------------------------

double Graph::NormToClientX( double x, bool bInverse )
{
	double cx;
	Rect r=GetClientRect();
	r.Inset( 1, 1 );
	if( bInverse )
	{
		cx=m_ptOrigin.x+m_scale*(x-r.left)/(r.Width()-1);
	}
	else
	{
		cx=r.left+((x-m_ptOrigin.x)/m_scale)*(r.Width()-1);

		if( cx<-30000. )
			cx=-30000;
		else if( cx>30000 )
			cx=30000;
	}
	return cx;
}

//------------------------------------------------------------------------------

double Graph::NormToClientY( double y, bool bInverse )
{
	double cy;
	Rect r=GetClientRect();
	r.Inset( 1, 1 );
	if( bInverse )
	{
		cy=m_ptOrigin.y+m_scale*(y-r.top)/(r.Height()-1);
	}
	else
	{
		cy=(r.bottom-1)-((y-m_ptOrigin.y)/m_scale)*(r.Height()-1);

		if( cy<-30000. )
			cy=-30000;
		else if( cy>30000 )
			cy=30000;
	}
	return cy;
}

//------------------------------------------------------------------------------

void Graph::DrawGraph( juce::Graphics &g )
{
	Rect rc=GetClientRect();

	Rect r=rc;
	r.Inset( 1, 1 );
	float yprev=0;
	for( int xi=r.left;xi<r.right;xi++ )
	{
		double x=NormToFuncX( ClientToNormX( xi ) );
		float yi=float( NormToClientY( FuncToNormY( Func(x) ) ) );
		if( _isnan(yi) )
		{
			x=0;
		}
		if( xi!=r.left )
		{
			g.drawLine(float(xi-1),yprev,float(xi),yi,2);
		}
		else
		{
			g.drawLine(float(xi),yi,float(xi),yi,2);
		}
		yprev=yi;
	}
}

//------------------------------------------------------------------------------

void Graph::resized()
{
}

//******************************************************************************
//
// FilterGraph
//
//******************************************************************************

class FilterGraph : public Graph, public FilterChart
{
public:
	FilterGraph();

	double NormToFreq( double x, bool bInverse );

	void DrawCutoff( juce::Graphics &g );
	void DrawAxisX( juce::Graphics &g, double y );
	void DrawAxisY( juce::Graphics &g, double x );

	virtual void DrawExtras( juce::Graphics &g );
	virtual void Recalculate( void );

	virtual void paint( juce::Graphics &g );

	const char *m_szTitle;
};

//------------------------------------------------------------------------------

FilterGraph::FilterGraph()
{
	m_szTitle="";
}

//------------------------------------------------------------------------------

double FilterGraph::NormToFreq( double x, bool bInverse )
{
#if 0
	// logarithmic scale
	if( bInverse )
		// [0..sampleRate/2] -> [0..1]
		return log(x)/log(m_spec->sampleRate/2);
	else
		// [0..1] -> [0..sampleRate/2]
		return pow(m_spec->sampleRate/2, x );
#else
	// linear scale
	if( bInverse )
		// [0..sampleRate/2] -> [0..1]
		return 2*x/(m_spec->sampleRate);
	else
		// [0..1] -> [0..sampleRate/2]
		return x*m_spec->sampleRate/2;
#endif
}

//------------------------------------------------------------------------------

void FilterGraph::DrawExtras( juce::Graphics &g )
{
}

//------------------------------------------------------------------------------

void FilterGraph::DrawCutoff( juce::Graphics &g )
{
	Rect rc=GetClientRect();
	double w=m_spec->cutoffFreq;
	float x=FuncToClientX( w );
	juce::Colour cValue(0x6000ff00);
	g.setColour( cValue );
	g.drawLine( x, rc.top, x, rc.bottom );
}

//------------------------------------------------------------------------------

void FilterGraph::DrawAxisX( juce::Graphics &g, double y )
{
	Rect rc=GetClientRect();
	float yi=FuncToClientY( y );
	g.drawLine( rc.left, yi, rc.right, yi );

	juce::Colour savedColor=g.getCurrentColour();
	char szBuf[64];
	sprintf( szBuf, "%.0f", y );
	g.setColour( m_cText );
	Rect rText( yi-7, rc.left+2, yi, rc.right-2 );
	g.drawFittedText(
		szBuf,
		rText.left,
		rText.top,
		rText.Width(),
		rText.Height(),
		juce::Justification::bottomLeft,
		1 );
	g.setColour( savedColor );
}

//------------------------------------------------------------------------------

void FilterGraph::DrawAxisY( juce::Graphics &g, double x )
{
	Rect rc=GetClientRect();
	float xi=FuncToClientX( x );
	g.drawLine( xi, rc.top, xi, rc.bottom );
}

//------------------------------------------------------------------------------

void FilterGraph::Recalculate( void )
{
	repaint();
}

//------------------------------------------------------------------------------

void FilterGraph::paint( juce::Graphics &g )
{
	Rect rc=GetClientRect();
	juce::Colour cBack(0xfff8f8f8);

	g.fillAll( cBack );
	g.setColour( m_cFrame );
	g.drawRect( rc.left, rc.top, rc.Width(), rc.Height() );

	DrawExtras( g );

	juce::Colour cValue(0xff0000ff);
	g.setColour( cValue );
	DrawGraph( g );

	g.setColour( m_cText );
	Rect rText( rc.top+2, rc.left+2, rc.top+18, rc.right-2 );
	g.drawFittedText(
		m_szTitle,
		rText.left,
		rText.top,
		rText.Width(),
		rText.Height(),
		juce::Justification::topRight,
		1 );
}

//******************************************************************************
//
// Graphs
//
//******************************************************************************

class BrickWallGraph : public FilterGraph
{
public:
	BrickWallGraph()
	{
		m_szTitle="Gain";
	}

	double NormToFuncX( double x, bool bInverse )
	{
		return NormToFreq( x, bInverse );
	}

	double NormToFuncY( double y, bool bInverse )
	{
		const double ymin=-0.2;
		const double ymax=1.8;

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
		Dsp::Complex c=m_filter->Response( 2*Dsp::kPi*x/m_spec->sampleRate );
		double y=std::abs(c);
		return y;
	}

	void DrawExtras( juce::Graphics &g )
	{
		g.setColour( m_cAxis );
		DrawAxisX( g, 1 );
		DrawAxisX( g, 0 );

		DrawCutoff( g );
	}
};

//------------------------------------------------------------------------------

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

	void DrawExtras( juce::Graphics &g )
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

	void DrawExtras( juce::Graphics &g )
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

	void DrawExtras( juce::Graphics &g )
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

class PoleChart : virtual public juce::Component, public FilterChart
{
public:
	void Recalculate( void )
	{
		repaint();
	}

	void paint( juce::Graphics &g )
	{
		juce::Colour cBack(0xfff8f8f8);
		juce::Colour cValue(0xff000000);
		juce::Colour cPole(0xd0ff0000);
		juce::Colour cZero(0xd02020ff);
		
		juce::Rectangle rc( 0, 0, getWidth(), getHeight() );

		int size=getWidth();
		if( size>getHeight() )
			size=getHeight();

		g.fillAll( cBack );

		g.setColour( m_cFrame );
		g.drawRect( rc.getX(), rc.getY(), rc.getRight(), rc.getBottom() );

		juce::Rectangle r=rc;
		r.expand( -1, -1 );

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
			Rect rc( 0, 0, getHeight(), getWidth() );
			Rect rText( rc.top+2, rc.left+2, rc.top+18, rc.right-2 );
			g.drawFittedText(
				"Pole/Zero",
				rText.left,
				rText.top,
				rText.Width(),
				rText.Height(),
				juce::Justification::topRight,
				1 );
		}
	}
};

//******************************************************************************
//
// FilterPanel
//
//******************************************************************************

class FilterPanel :
	public juce::Component,
	public juce::ButtonListener,
	public juce::ComboBoxListener,
	public juce::SliderListener
{
public:
    FilterPanel();
    ~FilterPanel();

    juce_UseDebuggingNewOperator

private:
	// disallowed
	FilterPanel(const FilterPanel&);
	const FilterPanel& operator=(const FilterPanel&);

	// Proto
	enum
	{
		idButter=1,
		idChebyI=2,
		idChebyII=3,
		idElliptic=4,
		idBessel=5,
		idLegendere=6
	};

	// Kind
	enum
	{
		idLowPass=1,
		idHighPass=2,
		idBandPass=3,
		idBandStop=4,
		idLowShelf=5,
		idHighShelf=6,
		idPeakEq=7
	};

	// Knobs
	enum
	{
		idOrd=0,
		idFreq=1,
		idWid=2,
		idRip=3,
		idAtt=4,
		idGain=5,
		idSlope=6,

		knobCount
	};

	// Graphs
	enum
	{
		idBrick=0,
		idPhase=1,
		idPoles=2,
		idResponse=3,
		idDelay=4,
		idStep=5,

		chartCount
	};

	struct Filters
	{
		Dsp::ButterLowPass<kMaxOrder,1> butterLp;
		Dsp::ButterHighPass<kMaxOrder,1> butterHp;
		Dsp::ButterBandPass<kMaxOrder,1> butterBp;
		Dsp::ButterBandStop<kMaxOrder,1> butterBs;
		Dsp::ButterLowShelf<kMaxOrder,1> butterLs;
		Dsp::ButterHighShelf<kMaxOrder,1> butterHs;
		Dsp::ButterEq<kMaxOrder,1> butterEq;

		Dsp::ChebyILowPass<kMaxOrder,1> chebyILp;
		Dsp::ChebyIHighPass<kMaxOrder,1> chebyIHp;
		Dsp::ChebyIBandPass<kMaxOrder,1> chebyIBp;
		Dsp::ChebyIBandStop<kMaxOrder,1> chebyIBs;
		Dsp::ChebyILowShelf<kMaxOrder,1> chebyILs;
		Dsp::ChebyIHighShelf<kMaxOrder,1> chebyIHs;
		Dsp::ChebyIEq<kMaxOrder,1> chebyIEq;

		Dsp::ChebyIILowPass<kMaxOrder,1> chebyIILp;
		Dsp::ChebyIIHighPass<kMaxOrder,1> chebyIIHp;
		Dsp::ChebyIIBandPass<kMaxOrder,1> chebyIIBp;
		Dsp::ChebyIIBandStop<kMaxOrder,1> chebyIIBs;
		Dsp::ChebyIILowShelf<kMaxOrder,1> chebyIILs;
		Dsp::ChebyIIHighShelf<kMaxOrder,1> chebyIIHs;
		Dsp::ChebyIIEq<kMaxOrder,1> chebyIIEq;

		Dsp::EllipticLowPass<kMaxOrder,1> ellipticLp;
		Dsp::EllipticHighPass<kMaxOrder,1> ellipticHp;
		Dsp::EllipticBandPass<kMaxOrder,1> ellipticBp;
		Dsp::EllipticBandStop<kMaxOrder,1> ellipticBs;

		Dsp::BesselLowPass<kMaxOrder,1> besselLp;
		Dsp::BesselHighPass<kMaxOrder,1> besselHp;
		Dsp::BesselBandPass<kMaxOrder,1> besselBp;
		Dsp::BesselBandStop<kMaxOrder,1> besselBs;

		Dsp::LegendereLowPass<kMaxOrder,1> legendereLp;
	};

private:
	void SpecDefaults( Spec *spec );
	void SpecToCtrls( void );
	Dsp::PoleFilter *SpecToFilter( const Spec &spec, Filters *filters );

private:
	void paint( juce::Graphics &g );
    void resized();
    void buttonClicked( juce::Button *ctrl );
    void comboBoxChanged( juce::ComboBox *ctrl );
    void sliderValueChanged( juce::Slider *ctrl );

private:
	Layout				m_layout;
	juce::ComboBox *	m_menuProto;
	juce::ComboBox *	m_menuKind;
	juce::Slider *		m_knob[knobCount];
	FilterChart *		m_chart[chartCount];

	Spec				m_spec;
	Filters				m_filters;
	Dsp::PoleFilter *	m_filter;
};

//******************************************************************************

FilterPanel::FilterPanel()
	:m_layout( this )	
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
		juce::Slider::TextEntryBoxPosition textPos;
		textPos=(i&1)?juce::Slider::TextBoxBelow:juce::Slider::TextBoxAbove;
		m_knob[i]=new juce::Slider(juce::String::empty);
		m_knob[i]->setSliderStyle (juce::Slider::RotaryVerticalDrag);
		m_knob[i]->setRotaryParameters (juce::float_Pi * 1.2f, juce::float_Pi * 2.8f, false);
		m_knob[i]->setTextBoxStyle( textPos, false, tw, th);
		m_knob[i]->setBounds( x, y, std::max(sw,tw), sh+th );
		m_knob[i]->setTextValueSuffix( szUnits );
		m_knob[i]->setRange( v0, v1, vinc );
		m_knob[i]->setVelocityBasedMode( true );
		addAndMakeVisible( m_knob[i] );
		m_knob[i]->addListener( this );

		y=y0+((i&1)?0:sh+th);
		juce::Label *label=new juce::Label(juce::String::empty, szLabel );
		label->setFont( juce::Font(12, juce::Font::plain) );
	    label->setJustificationType( juce::Justification::centred );
	    label->setEditable( false, false, false );
	    label->setJustificationType( juce::Justification::centred );
	    label->setJustificationType( juce::Justification::centred );
		label->setColour( juce::Label::textColourId, juce::Colours::black );
		label->setColour( juce::TextEditor::textColourId, juce::Colours::black );
		label->setColour( juce::TextEditor::backgroundColourId, juce::Colour(0x0) );
	    label->setBounds( x, y, tw, th );
		addAndMakeVisible( label );

		x=x+sw+12;
	}

	y=y0;
	x+=32;

	tw=160; // menu size
	th=20;

	m_menuProto=new juce::ComboBox( juce::String::empty );
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

	m_menuKind=new juce::ComboBox( juce::String::empty );
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
	m_layout.Add( chart, Point( 0, 0 ), Point( 33, 33 ) );
	x=x+200+8;

	chart=new PhaseGraph();
	chart->setBounds( x, y, 200, 200 );
	addAndMakeVisible( chart );
	m_chart[idPhase]=chart;
	m_layout.Add( chart, Point( 33, 0 ), Point( 66, 33 ) );
	x=x+200+8;

	chart=new PoleChart();
	chart->setBounds( x, y, 200, 200 );
	addAndMakeVisible( chart );
	m_chart[idPoles]=chart;
	m_layout.Add( chart, Point( 66, 0 ), Point( 100, 33 ) );
	x=x+200+8;

	y=y+200+8;

	x=x0;

	chart=new ResponseGraph();
	chart->setBounds( x, y, 400+8, 400+8 );
	addAndMakeVisible( chart );
	m_chart[idResponse]=chart;
	m_layout.Add( chart, Point( 0, 33 ), Point( 66, 100 ) );
	x=x+400+8+8;

	chart=new DelayGraph();
	chart->setBounds( x, y, 200, 200 );
	addAndMakeVisible( chart );
	m_chart[idDelay]=chart;
	m_layout.Add( chart, Point( 66, 33 ), Point( 100, 66 ) );
	y=y+200+8;

	chart=new StepGraph();
	chart->setBounds( x, y, 200, 200 );
	addAndMakeVisible( chart );
	m_chart[idStep]=chart;
	m_layout.Add( chart, Point( 66, 66 ), Point( 100, 100 ) );
	y=y+200+8;
	x=x+200+8;

	//

	setSize( x, y );

	m_layout.Activate();

	SpecDefaults( &m_spec );
	SpecToCtrls();
}

//------------------------------------------------------------------------------

FilterPanel::~FilterPanel()
{
	deleteAllChildren();
}

//------------------------------------------------------------------------------

void FilterPanel::SpecDefaults( Spec *spec )
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

void FilterPanel::SpecToCtrls( void )
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

Dsp::PoleFilter *FilterPanel::SpecToFilter( const Spec &spec, Filters *filters )
{
	Dsp::PoleFilter *filter=0;

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

void FilterPanel::paint( juce::Graphics& g )
{
	g.fillAll( juce::Colour(0xffc1d0ff) );
//    g.setColour (Colours::white);
  //  g.setColour (Colour (0xff6f6f6f));
//    g.strokePath (internalPath1, PathStrokeType (5.2000f));
}

//------------------------------------------------------------------------------

void FilterPanel::resized()
{
	m_layout.Recalculate();
}

//------------------------------------------------------------------------------

void FilterPanel::buttonClicked( juce::Button *ctrl )
{
}

//------------------------------------------------------------------------------

void FilterPanel::comboBoxChanged( juce::ComboBox *ctrl )
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

void FilterPanel::sliderValueChanged( juce::Slider *ctrl )
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

//******************************************************************************
//
// DspWindow
//
//******************************************************************************

class DspWindow  : public juce::DocumentWindow
{
public:
    DspWindow() 
		: juce::DocumentWindow (T("Dsp Filters Demo"),
                          juce::Colours::lightgrey, 
                          juce::DocumentWindow::allButtons,
                          true )
	{
		setResizable( true, false );
        FilterPanel *const ctrl = new FilterPanel();
        setContentComponent (ctrl, true, true);
        centreWithSize (getWidth(), getHeight());
        setVisible (true);
    }

    ~DspWindow()
    {
    }

    void closeButtonPressed()
    {
        juce::JUCEApplication::quit();
    }
};

//******************************************************************************
//
// DspApp
//
//******************************************************************************

class DspApp : public juce::JUCEApplication
{
    // Important! NEVER embed objects directly inside your JUCEApplication class!
    DspWindow *m_dspWindow;
	DspLookAndFeel m_lookAndFeel; // except for this one

public:
    DspApp()
    {
		m_dspWindow=0;
    }

    ~DspApp()
    {
        // Your shutdown() method should already have done all the things necessary to
        // clean up this app object, so you should never need to put anything in
        // the destructor.

        // Making any Juce calls in here could be very dangerous...
    }

    void initialise( const juce::String& commandLine )
    {
		juce::LookAndFeel::setDefaultLookAndFeel( &m_lookAndFeel );

        m_dspWindow = new DspWindow();
    }

    void shutdown()
    {
		delete m_dspWindow;
    }

    const juce::String getApplicationName()
    {
        return T("Dsp Filters Demo");
    }

    const juce::String getApplicationVersion()
    {
        return T("1.0");
    }

    bool moreThanOneInstanceAllowed()
    {
        return true;
    }

    void anotherInstanceStarted( const juce::String& commandLine )
    {
    }
};

//******************************************************************************

// JUCE magic
START_JUCE_APPLICATION( DspApp )

//******************************************************************************

