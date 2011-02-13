/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.h for contact information, notes, and bibliography.

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

*******************************************************************************/

#include "Common.h"
#include "FilterGraph.h"

FilterGraph::FilterGraph()
{
	m_szTitle="";
}

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

void FilterGraph::DrawExtras( Graphics &g )
{
}

void FilterGraph::DrawCutoff( Graphics &g )
{
	Rectangle<int> rc = getLocalBounds();
	double w=m_spec->cutoffFreq;
	float x=FuncToClientX( w );
	Colour cValue(0x6000ff00);
	g.setColour( cValue );
	g.drawLine( x, rc.getY(), x, rc.getBottom() );
}

void FilterGraph::DrawAxisX( Graphics &g, double y )
{
	Rectangle<int> rc = getLocalBounds();
	float yi=FuncToClientY( y );
	g.drawLine( rc.getX(), yi, rc.getRight(), yi );

//	Colour savedColor=g.getCurrentColour();
	char szBuf[64];
	sprintf( szBuf, "%.0f", y );
	g.setColour( m_cText );
	Rectangle<int> rText = tlbr( yi-7, rc.getX()+2, yi, rc.getRight()-2 );
	g.drawFittedText(
		szBuf,
		rText.getX(),
		rText.getY(),
		rText.getWidth(),
		rText.getHeight(),
		Justification::bottomLeft,
		1 );
//	g.setColour( savedColor );
}

void FilterGraph::DrawAxisY( Graphics &g, double x )
{
	Rectangle<int> rc = getLocalBounds();
	float xi=FuncToClientX( x );
	g.drawLine( xi, rc.getY(), xi, rc.getBottom() );
}

void FilterGraph::Recalculate( void )
{
	repaint();
}

void FilterGraph::paint( Graphics &g )
{
	Rectangle<int> rc = getLocalBounds();
	Colour cBack(0xfff8f8f8);

	g.fillAll( cBack );
	g.setColour( m_cFrame );
	g.drawRect( rc.getX(), rc.getY(), rc.getWidth(), rc.getHeight() );

	DrawExtras( g );

	Colour cValue(0xff0000ff);
	g.setColour( cValue );
	DrawGraph( g );

	g.setColour( m_cText );
	Rectangle<int> rText = tlbr( rc.getY()+2, rc.getX()+2, rc.getY()+18, rc.getRight()-2 );
	g.drawFittedText(
		m_szTitle,
		rText.getX(),
		rText.getY(),
		rText.getWidth(),
		rText.getHeight(),
		Justification::topRight,
		1 );
}
