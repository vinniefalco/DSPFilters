/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vincent Falco

Official project location:
http://code.google.com/p/dspfilterscpp/

See Documentation.cpp for contact information, notes, and bibliography.

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
#include "Graph.h"

Graph::Graph()
{
	m_scale=1;
	m_ptOrigin=Point<float> (0, 0);
}

Graph::~Graph()
{
}

double Graph::NormToClientX( double x, bool bInverse )
{
	double cx;
  Rectangle<int> r = getLocalBounds().reduced (1, 1);

  if( bInverse )
	{
		cx=m_ptOrigin.getX()+m_scale*(x-r.getX())/(r.getWidth()-1);
	}
	else
	{
		cx=r.getX()+((x-m_ptOrigin.getX())/m_scale)*(r.getWidth()-1);

		if( cx<-30000. )
			cx=-30000;
		else if( cx>30000 )
			cx=30000;
	}
	return cx;
}

double Graph::NormToClientY( double y, bool bInverse )
{
	double cy;
  Rectangle<int> r = getLocalBounds().reduced (1, 1);
	if( bInverse )
	{
		cy=m_ptOrigin.getY()+m_scale*(y-r.getY())/(r.getHeight()-1);
	}
	else
	{
		cy=(r.getBottom()-1)-((y-m_ptOrigin.getY())/m_scale)*(r.getHeight()-1);

		if( cy<-30000. )
			cy=-30000;
		else if( cy>30000 )
			cy=30000;
	}
	return cy;
}

void Graph::DrawGraph( Graphics &g )
{
	Rectangle<int> rc = getLocalBounds();

	Rectangle<int> r = rc.reduced (1, 1);

  float yprev=0;
	for( int xi=r.getX();xi<r.getRight();xi++ )
	{
		double x=NormToFuncX( ClientToNormX( xi ) );
		float yi=float( NormToClientY( FuncToNormY( Func(x) ) ) );
		if( xi!=r.getX() )
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
