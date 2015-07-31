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

#ifndef RESIZABLELAYOUT_H
#define RESIZABLELAYOUT_H

#include "Common.h"

//==============================================================================
/**
  Smoothly repositions and resizes child Components without rounding errors,
  according to caller provided stretching parameters.

  Usage:

  1) Derive your Component from ResizableLayout

  2) Give your Component a well defined default size

  3) Add child Components and position them according to how
     they should appear at the default.

  4) For each child Component, also call addToLayout() and specify what
     portion of the owner's growth or reduction should apply to each corner.

  5) At the end of your constructor, call activateLayout() to turn it on

  6) If you later manually reposition a control (for example, using a
     ComponentDragger) call updateLayoutFor() on the control that moved,
     or if you moved all the controls call updateLayout().

  7) You do not need to override resized() to make this work, all you
     have to do is lay things out when you create your child Components
     and add anchors as appropriate.

  Example

  struct ContentComponent : Component, ResizableLayout
  {
    ContentComponent() : ResizableLayout (this)
    {
      // for layouts to work you must start at some size
      // place controls in a location that is initially correct.
      setSize(512, 384);

      TextButton* b;

      b = new TextButton ("Juce");
      b->setBounds (32, 32, 512-64, 32);
      // stretch to fit the width of the window
      addToLayout (b, anchorTopLeft, anchorTopRight);
      addAndMakeVisible (b);

      b = new TextButton ("One");
      b->setBounds (32, 96, 128, 32);
      // take up 1/3 of the width of the window
      addToLayout (b, Point<int>(0,0), Point<int>(33,0));
      addAndMakeVisible (b);

      // turn it on
      activateLayout();
    }
  }
*/

//------------------------------------------------------------------------------

// Derive your child Component from this class if
// you want to be able to set size limits per-item.
class ResizableChild
{
public:
  ResizableChild() : m_minW(0), m_maxW(0x3fffffff), m_minH(0), m_maxH(0x3fffffff) { }

  void setMinimumWidth (int minimumWidth) { m_minW = minimumWidth; }
  void setMaximumWidth (int maximumWidth) { m_maxW = maximumWidth; }
  void setMinimumHeight (int minimumHeight) { m_minH = minimumHeight; }
  void setMaximumHeight (int maximumHeight) { m_maxH = maximumHeight; }

  int getMinimumWidth() const { return m_minW; }
  int getMaximumWidth() const { return m_maxW; }
  int getMinimumHeight() const { return m_minH; }
  int getMaximumHeight() const { return m_maxH; }

  void setMinimumSize (int minimumWidth,
                       int minimumHeight)
  {
    setMinimumWidth (minimumWidth);
    setMinimumHeight (minimumHeight);
  }

  void setMaximumSize (int maximumWidth,
                       int maximumHeight)
  {
    setMaximumWidth (maximumWidth);
    setMaximumHeight (maximumHeight);
  }

  void setSizeLimits (int minimumWidth,
                      int minimumHeight,
                      int maximumWidth,
                      int maximumHeight)
  {
    setMinimumWidth (minimumWidth);
    setMaximumWidth (maximumWidth);
    setMinimumHeight (minimumHeight);
    setMaximumHeight (maximumHeight);
  }

  virtual void resizeStart() {}

private:
  int m_minW;
  int m_maxW;
  int m_minH;
  int m_maxH;
};

//------------------------------------------------------------------------------

// Derive your Component from this class if you
// want to be able to put anchors on children.
class ResizableLayout
  : public ResizableChild
  , private ComponentListener
{
public:
	enum
	{
		anchorUnit=100
	};

	enum Style
	{
		styleStretch,
		styleFixedAspect
	};

	static const Point<int> anchorNone;
	static const Point<int> anchorTopLeft;
	static const Point<int> anchorTopCenter;
	static const Point<int> anchorTopRight;
	static const Point<int> anchorMidLeft;
	static const Point<int> anchorMidCenter;
	static const Point<int> anchorMidRight;
	static const Point<int> anchorBottomLeft;
	static const Point<int> anchorBottomCenter;
	static const Point<int> anchorBottomRight;

public:
	ResizableLayout (Component* owner);
	~ResizableLayout ();

	// Add a Component to the Layout.
	// topLeft and bottomRight are the percentages that the top left and bottom right of
	// the Component should move by, when the layout is resized.
	// So if you wanted to have the control take on the full width of the parent, and
	// half the height, you would use bottomRight.x=100, bottomRight.y=50. or
  // use the constant anchorMidRight
	void addToLayout (
		Component *component,
		const Point<int> &topLeft,
		const Point<int> &bottomRight=anchorNone,
		Style style = styleStretch );

	// Remove a Component from the Layout.
	void removeFromLayout (Component* component);

	// Activate (or deactivate) the Layout. The Layout is initially inactive,
	// to prevent spurious recalculation while a Component and its children are being
	// constructed (causing resized() messages). Activating the Layout for the
	// first time will cause an Update().
	void activateLayout (bool isActive=true);

	// Call this to manually update the state information for a single control
	// after it has been moved or resized from elsewhere.
  // UNFINISHED API
	void updateLayoutFor (Component *component);

  // Convenience function
  static Rectangle<int> calcBoundsOfChildren (Component* parent);

private:
  // Update the state information for all items. This is used on the first Activate(),
	// and can also be used if multiple controls are moved or resized from elsewhere.
  // UNFINISHED API
	void updateLayout ();

  void resizeStart ();

private:
  friend class TopLevelResizableLayout;

  struct Rect
  {
	  Rect() {}
	  Rect (int top0, int left0, int bottom0, int right0) { top=top0; left=left0; bottom=bottom0; right=right0; }
	  Rect (const Rectangle<int> &r) { top=int(r.getY()); left=int(r.getX()); bottom=int(r.getBottom()); right=int(r.getRight()); }
	  operator Rectangle<int>() const { return Rectangle<int>( left, top, getWidth(), getHeight() ); }
	  int getHeight () const { return bottom-top; }
	  int getWidth () const { return right-left; }
	  void reduce (int dx, int dy) { top+=dy; left+=dx; bottom-=dy; right-=dx; }

	  int top;
	  int left;
	  int bottom;
	  int right;
  };

  struct Anchor
	{
		Style	style;
		Component* component;
    ResizableChild* child;
		Point<int> topLeft;
		Point<int> bottomRight;

    Anchor (Component* component=0);
    bool operator== (const Anchor& rhs) const;
    bool operator>= (const Anchor& rhs) const;
    bool operator<  (const Anchor& rhs) const;
	};

  struct State
	{
		Component* component;
		double aspect;
		Rect margin;

    State (Component* component=0);
    State (const State& other);

    bool operator== (const State& rhs) const;
    bool operator>= (const State& rhs) const;
    bool operator<  (const State& rhs) const;
	};

  void addStateFor (const Anchor& anchor);

public:
	void recalculateLayout ();

private:
  void componentMovedOrResized (Component& component,
                                bool wasMoved,
                                bool wasResized);

  void componentBeingDeleted (Component& component);

private:
	Component* m_owner;

  SortedSet<Anchor> m_anchors;
  SortedSet<State> m_states;

	bool m_bFirstTime;
	bool m_isActive;
};

//------------------------------------------------------------------------------

// Derive your content component from this class (i.e. the
// component that you stick in a ResizableWindow) in order to
// allow it to apply size limits automatically.
class TopLevelResizableLayout
  : public ResizableLayout
{
public:
  TopLevelResizableLayout (Component* owner);

  void setAsConstrainerFor (ResizableWindow* window);

private:
  class Constrainer : public ComponentBoundsConstrainer
  {
  public:
    Constrainer (TopLevelResizableLayout* owner);
    void resizeStart();
  private:
    TopLevelResizableLayout& m_owner;
  };

  Constrainer m_constrainer;
};

#endif
