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
