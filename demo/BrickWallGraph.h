#ifndef DSPDEMO_FILTERS_H
#define DSPDEMO_FILTERS_H

#include "Common.h"
#include "FilterGraph.h"

class BrickWallGraph : public FilterGraph
{
public:
	BrickWallGraph();
	double NormToFuncX( double x, bool bInverse );
	double NormToFuncY( double y, bool bInverse );
	double Func( double x );
	void DrawExtras( Graphics &g );
};

#endif
