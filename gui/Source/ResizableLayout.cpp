/*******************************************************************************

"A Collection of Useful C++ Classes for Digital Signal Processing"
 By Vinnie Falco

Official project location:
https://github.com/vinniefalco/DSPFilters

See Documentation.cpp for contact information, notes, and bibliography.

--------------------------------------------------------------------------------

License: MIT License (http://www.opensource.org/licenses/mit-license.php)
Copyright (c) 2009 by Vinnie Falco

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
#include "ResizableLayout.h"

const Point<int> ResizableLayout::anchorNone			  ( -1, -1 );
const Point<int> ResizableLayout::anchorTopLeft		  ( 0, 0 );
const Point<int> ResizableLayout::anchorTopCenter		( anchorUnit/2, 0 );
const Point<int> ResizableLayout::anchorTopRight		( anchorUnit, 0 );
const Point<int> ResizableLayout::anchorMidLeft		  ( 0, anchorUnit/2 );
const Point<int> ResizableLayout::anchorMidCenter		( anchorUnit/2, anchorUnit/2 );
const Point<int> ResizableLayout::anchorMidRight		( anchorUnit, anchorUnit/2 );
const Point<int> ResizableLayout::anchorBottomLeft	( 0, anchorUnit );
const Point<int> ResizableLayout::anchorBottomCenter( anchorUnit/2, anchorUnit );
const Point<int> ResizableLayout::anchorBottomRight	( anchorUnit, anchorUnit );

ResizableLayout::Anchor::Anchor (Component* component_)
: component (component_)
, child (dynamic_cast<ResizableChild*>(component_))
{
  jassert (component);
}

bool ResizableLayout::Anchor::operator== (const Anchor& rhs) const
{
  return component == rhs.component;
}

bool ResizableLayout::Anchor::operator>= (const Anchor& rhs) const
{
    return component >= rhs.component;
}

bool ResizableLayout::Anchor::operator< (const Anchor& rhs) const
{
    return component < rhs.component;
}

ResizableLayout::State::State (Component* component_)
: component (component_)
{
  jassert (component);
}

ResizableLayout::State::State (const State& other)
: component (other.component)
, aspect (other.aspect)
, margin (other.margin)
{
}

bool ResizableLayout::State::operator== (const State& rhs) const
{
  return component == rhs.component;
}

bool ResizableLayout::State::operator>= (const State& rhs) const
{
    return component >= rhs.component;
}

bool ResizableLayout::State::operator< (const State& rhs) const
{
    return component < rhs.component;
}

//------------------------------------------------------------------------------

ResizableLayout::ResizableLayout (Component* owner)
: m_owner (owner)
{
  m_bFirstTime = true;
	m_isActive = false;

  m_owner->addComponentListener (this);
}


ResizableLayout::~ResizableLayout()
{
}

void ResizableLayout::addToLayout (Component* component,
                                   const Point<int> &topLeft,
                                   const Point<int> &bottomRight,
                                   Style style )
{
	jassert (topLeft != anchorNone);

  Anchor anchor (component);
	anchor.style = style;
  anchor.topLeft = topLeft;
  if (bottomRight == anchorNone)
	  anchor.bottomRight = topLeft;
  else
	  anchor.bottomRight = bottomRight;

  m_anchors.add (anchor);

  component->addComponentListener (this);
}

void ResizableLayout::removeFromLayout (Component* component)
{
  m_anchors.removeValue (component);
  m_states.removeValue (component);
}

void ResizableLayout::activateLayout (bool isActive)
{
	if (m_isActive != isActive)
	{
		if (isActive && m_bFirstTime)
		{
			updateLayout();
			m_bFirstTime=false;
		}

		m_isActive=isActive;
	}
}

void ResizableLayout::updateLayout ()
{
  m_states.clearQuick();
	for( int i=0; i<m_anchors.size(); i++ )
		addStateFor (m_anchors[i]);
}

void ResizableLayout::updateLayoutFor (Component *component)
{
  m_states.removeValue (component);
  addStateFor (m_anchors[m_anchors.indexOf (component)]);
}

void ResizableLayout::addStateFor (const Anchor& anchor)
{
	Rect rb = anchor.component->getBounds();

  int w = m_owner->getWidth();
  int h = m_owner->getHeight();

  State state (anchor.component);

  // secret sauce
	state.margin.top = rb.top - (h * anchor.topLeft.getY()) / anchorUnit;
	state.margin.left = rb.left - (w * anchor.topLeft.getX()) / anchorUnit;
	state.margin.bottom = rb.bottom - (h * anchor.bottomRight.getY()) / anchorUnit;
	state.margin.right = rb.right - (w * anchor.bottomRight.getX()) / anchorUnit;

  state.aspect = double (rb.getWidth()) / rb.getHeight();

  m_states.add (state);
}

// Recalculate the position and size of all the controls
// in the layout, based on the owner Component size.
void ResizableLayout::recalculateLayout()
{
	if (m_isActive)
	{
		Rect rp = m_owner->getBounds();
		
    for (int i=0; i<m_states.size(); i++)
		{
      Anchor anchor = m_anchors[i];
      State state = m_states[i];
      jassert (anchor.component == state.component);

      Rect rb;

      // secret sauce
			rb.top = state.margin.top + (rp.getHeight() * anchor.topLeft.getY()) / anchorUnit;
			rb.left = state.margin.left + (rp.getWidth() * anchor.topLeft.getX()) / anchorUnit;
			rb.bottom= state.margin.bottom + (rp.getHeight() * anchor.bottomRight.getY()) / anchorUnit;
			rb.right = state.margin.right + (rp.getWidth() * anchor.bottomRight.getX()) / anchorUnit;
      // prove that there are no rounding issues
      jassert ((anchor.bottomRight != anchor.topLeft) ||
               ((rb.getWidth() == anchor.component->getWidth()) && 
                (rb.getHeight() == anchor.component->getHeight())));

			if (anchor.style == styleStretch)
			{
				anchor.component->setBounds (rb);
			}
			else if (anchor.style==styleFixedAspect)
			{
				Rect r;
				double aspect = double (rb.getWidth()) / rb.getHeight();

				if( aspect > state.aspect )
				{
					r.top = rb.top;
					r.bottom = rb.bottom;
					int width = int (state.aspect * r.getHeight());
					r.left = rb.left + (rb.getWidth()-width)/2;
					r.right = r.left + width;
				}
				else
				{
					r.left = rb.left;
					r.right = rb.right;
					int height = int (1. / state.aspect * r.getWidth());
					r.top = rb.top + (rb.getHeight() - height) / 2;
					r.bottom = r.top + height;
				}

				anchor.component->setBounds (r);
			}
		}
	}
}

void ResizableLayout::componentMovedOrResized (Component& component,
                                               bool wasMoved,
                                               bool wasResized)
{
  if (&component == m_owner)
  {
    if (wasResized)
    {
      recalculateLayout ();
    }
  }
  else
  {
    updateLayoutFor (&component);
  }
}

void ResizableLayout::componentBeingDeleted (Component& component)
{
  if (&component != m_owner)
  {
    m_anchors.removeValue (&component);
    m_states.removeValue (&component);
  }
}

Rectangle<int> ResizableLayout::calcBoundsOfChildren (Component* parent)
{
  Rectangle<int> r;

  for (int i=0; i<parent->getNumChildComponents(); i++)
    r = r.getUnion (parent->getChildComponent(i)->getBounds());

  return r;
}

void ResizableLayout::resizeStart()
{
  bool haveChildren = false;

  // first recursively call resizeStart() on all children
  for (int i=0; i<m_anchors.size(); i++)
	{
    ResizableChild* child = m_anchors.getUnchecked(i).child;
    if (child)
    {
      child->resizeStart();
      haveChildren = true;
    }
  }

  // now check our immediate children for constraints
  if (haveChildren)
  {
    // start with our values
    int xmin0 = getMinimumWidth();
    int ymin0 = getMinimumHeight();

    // for each child, use the inverse of the resize function to solve for the min/max
    for (int i=0; i<m_anchors.size(); i++)
    {
      Anchor anchor = m_anchors.getUnchecked(i);
      if (anchor.child)
      {
        State state = m_states.getUnchecked(i);
        jassert (anchor.component == state.component);

        int xmin1 = anchor.child->getMinimumWidth();
        int ymin1 = anchor.child->getMinimumHeight();
        //int xmax1 = anchor.child->getMaximumWidth();
        //int ymax1 = anchor.child->getMaximumHeight();

        // invert the sauce
        int d; // anchor difference
        int m; // solution to f'(x)

        d = anchor.bottomRight.getX() - anchor.topLeft.getX();
        if (d!=0)
        {
          m = ( xmin1 + state.margin.left - state.margin.right ) * anchorUnit / d;
          xmin0 = jmax (xmin0, m);
        }

        d = anchor.bottomRight.getY() - anchor.topLeft.getY();
        if (d!=0)
        {
          m = ( ymin1 + state.margin.top - state.margin.bottom ) * anchorUnit / d;
          ymin0 = jmax (ymin0, m);
        }
      }
    }
   
    // apply adjusted limits
    setMinimumWidth (xmin0);
    setMinimumHeight (ymin0);
  }
}

//------------------------------------------------------------------------------

TopLevelResizableLayout::Constrainer::Constrainer (TopLevelResizableLayout* owner)
: m_owner (*owner)
{
}

void TopLevelResizableLayout::Constrainer::resizeStart ()
{
  m_owner.resizeStart();

  int minW = m_owner.getMinimumWidth();
  int minH = m_owner.getMinimumHeight();

  setMinimumWidth (minW);
  setMinimumHeight (minH);
}

//------------------------------------------------------------------------------

TopLevelResizableLayout::TopLevelResizableLayout (Component* owner)
  : ResizableLayout (owner)
  , m_constrainer (this)
{

}

void TopLevelResizableLayout::setAsConstrainerFor(ResizableWindow *window)
{
  window->setConstrainer (&m_constrainer);
}
