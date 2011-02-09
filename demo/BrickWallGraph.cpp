#include "Common.h"
#include "BrickWallGraph.h"

BrickWallGraph::BrickWallGraph()
{
	m_szTitle="Gain";
}

double BrickWallGraph::NormToFuncX( double x, bool bInverse )
{
	return NormToFreq( x, bInverse );
}

double BrickWallGraph::NormToFuncY( double y, bool bInverse )
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

double BrickWallGraph::Func( double x )
{
	Dsp::Complex c=m_filter->Response( 2*Dsp::kPi*x/m_spec->sampleRate );
	double y=std::abs(c);
	return y;
}

void BrickWallGraph::DrawExtras( Graphics &g )
{
	g.setColour( m_cAxis );
	DrawAxisX( g, 1 );
	DrawAxisX( g, 0 );

	DrawCutoff( g );
}
