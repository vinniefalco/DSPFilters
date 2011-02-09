#ifndef DSPDEMO_GRAPH_H
#define DSPDEMO_GRAPH_H

#include "Common.h"

class Graph : virtual public Component
{
public:
	Graph();
	~Graph();

	// Normalized coordinates initially maps the bottom left of the
	// control to (0,0) and the top right to (1,1).

	// Map between client and normalized coordinates
	double NormToClientX( double x, bool bInverse=false );
	double NormToClientY( double y, bool bInverse=false );
	
	void DrawGraph( Graphics &g );

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
	double m_scale;		// scale factor applied to normalized coords
	Point<float>m_ptOrigin;	// bottom left of graph in normalized coords
};

#endif
