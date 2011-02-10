#include "FilterChart.h"

FilterChart::FilterChart()
{
	m_filter=0;
	m_spec=0;

	m_cFrame=Colour(0xff808080);
	m_cAxis=Colour(0x80000000);
	m_cAxisMinor=Colour(0x20000000);
	m_cText=Colour(0xd0000000);
}

FilterChart::~FilterChart()
{
}

void FilterChart::SetFilter( const Dsp::PoleFilterOld *filter, const Spec &spec )
{
	m_filter=filter;
	m_spec=&spec;

	Recalculate();
}
