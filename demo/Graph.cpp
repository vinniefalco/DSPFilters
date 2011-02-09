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
