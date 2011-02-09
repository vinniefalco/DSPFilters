#ifndef DSPDEMO_FILTERGRAPH_H
#define DSPDEMO_FILTERGRAPH_H

#include "Common.h"
#include "Graph.h"
#include "FilterChart.h"

class FilterGraph : public Graph, public FilterChart
{
public:
	FilterGraph();

	double NormToFreq( double x, bool bInverse );

	void DrawCutoff( Graphics &g );
	void DrawAxisX( Graphics &g, double y );
	void DrawAxisY( Graphics &g, double x );

	virtual void DrawExtras( Graphics &g );
	virtual void Recalculate( void );

	virtual void paint( Graphics &g );

	const char *m_szTitle;
};

#endif
