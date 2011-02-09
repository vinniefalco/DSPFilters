#ifndef DSPDEMO_FILTERCHART_H
#define DSPDEMO_FILTERCHART_H

#include "Common.h"

class FilterChart : virtual public Component
{
public:
	FilterChart();
	~FilterChart();

	void SetFilter( const Dsp::PoleFilter *filter, const Spec &spec );
	virtual void Recalculate( void )=0;

protected:
	const Dsp::PoleFilter *m_filter;
	const Spec *m_spec;

	Colour m_cFrame;
	Colour m_cAxis;
	Colour m_cAxisMinor;
	Colour m_cText;
};

#endif
