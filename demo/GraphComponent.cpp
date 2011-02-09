#include "Common.h"
#include "GraphComponent.h"

GraphComponent::GraphComponent()
{
	m_cBack       = Colour (0xfff8f8f8);
	m_cFrame      = Colour (0xff808080);
	m_cAxis       = Colour (0x80000000);
	m_cAxisMinor  = Colour (0x20000000);
	m_cText       = Colour (0xd0000000);
}

GraphComponent::~GraphComponent()
{
}

void GraphComponent::paint (Graphics& g)
{
  paintBackground (g);
}

void GraphComponent::paintBackground (Graphics& g)
{
  Rectangle<int> bounds = getLocalBounds ();
	Rectangle<int> r = bounds;

	g.fillAll (m_cBack);
	g.setColour (m_cFrame);
	g.drawRect (r, 1);
}