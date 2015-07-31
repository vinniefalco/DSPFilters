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

#ifndef CONTENTCOMPONENTCONSTRAINER_H
#define CONTENTCOMPONENTCONSTRAINER_H

#include "Common.h"

// "shim" which goes between your constrainer and a ResizableWindow
// or derived class. This will adjust the parameters of the associated
// constrainer so that all constraints are based on the content component
// and do not include the title bar, native window frame, menu bar, or
// window border.
//
// If you set a minimum size with your constrainer, the content component will
// be constrained to EXACTLY your desired dimensions.
//
// This class is SUPER easy to use. First put a constrainer on your window
// or use the function ResizableWindow::setResizeLimits(), and then
// just call ContentComponentConstrainer::attachTo (yourResizableWindow).
// It will take care of deleting itself and handle everything for you.
class ContentComponentConstrainer
  : private ComponentBoundsConstrainer
  , private ComponentListener
{
public:
  // we can attach to anything with ResizableWindow as a base
  static void attachTo (ResizableWindow* resizableWindow)
  {
    ContentComponentConstrainer* contentConstrainer =
      new ContentComponentConstrainer (resizableWindow);
    resizableWindow->addComponentListener (contentConstrainer);
  }

private:
  ContentComponentConstrainer (ResizableWindow* resizableWindow)
   : m_resizableWindow (resizableWindow)
   , m_originalConstrainer (0)
  {
    // if you aren't using a custom constrainer, then at least put a
    // constraint on your ResizableWindow using ResizableWindow::setResizeLimits
    // so that it gets the defaultConstrainer.
    m_originalConstrainer = m_resizableWindow->getConstrainer();
    jassert (m_originalConstrainer); // must exist

    m_resizableWindow->setConstrainer (this);
    m_resizableWindow->addComponentListener (this);
  }

  void resizeStart()
  {
    m_originalConstrainer->resizeStart();
    copyConstraints (*m_originalConstrainer);
    adjustConstraints();
  }

  void resizeEnd()
  {
    m_originalConstrainer->resizeEnd();
  }

  void applyBoundsToComponent (Component* component,
                               const Rectangle<int>& bounds)
  {
    m_originalConstrainer->applyBoundsToComponent (component, bounds);
  }

  void copyConstraints (ComponentBoundsConstrainer& from)
  {
    setMinimumWidth (from.getMinimumWidth());
    setMaximumWidth (from.getMaximumWidth());
    setMinimumHeight (from.getMinimumHeight());
    setMaximumHeight (from.getMaximumHeight());
    setFixedAspectRatio (from.getFixedAspectRatio());

    int minimumWhenOffTheTop;
    int minimumWhenOffTheLeft;
    int minimumWhenOffTheBottom;
    int minimumWhenOffTheRight;

    minimumWhenOffTheTop = from.getMinimumWhenOffTheTop();
    minimumWhenOffTheLeft = from.getMinimumWhenOffTheLeft();
    minimumWhenOffTheBottom = from.getMinimumWhenOffTheBottom();
    minimumWhenOffTheRight = from.getMinimumWhenOffTheRight();

    setMinimumOnscreenAmounts (minimumWhenOffTheTop,
                               minimumWhenOffTheLeft,
                               minimumWhenOffTheBottom,
                               minimumWhenOffTheRight);
  }

  static int addWithoutOverflow (int a, int b)
  {
    if (a < (0x7ffffff-b))
      return a+b;
    else
      return 0x7fffffff;
  }

  // adjusts the current constraints to take into account decorations
  void adjustConstraints()
  {
    BorderSize<int> peerFrameBorder = m_resizableWindow->getPeer()->getFrameSize();
    BorderSize<int> contentCompBorder = m_resizableWindow->getContentComponentBorder();
    
    int extraWidth = peerFrameBorder.getLeftAndRight() + contentCompBorder.getLeftAndRight();
    int extraHeight = peerFrameBorder.getTopAndBottom() + contentCompBorder.getTopAndBottom();

    setMinimumHeight (m_originalConstrainer->getMinimumHeight() + extraHeight);
    setMaximumHeight (addWithoutOverflow (m_originalConstrainer->getMaximumHeight(), extraHeight));
    setMinimumWidth (m_originalConstrainer->getMinimumWidth() + extraWidth);
    setMaximumWidth (addWithoutOverflow (m_originalConstrainer->getMaximumWidth(), extraWidth));
  }

  void componentBeingDeleted (Component& component)
  {
    delete this;
  }

private:
  ResizableWindow* m_resizableWindow;
  ComponentBoundsConstrainer* m_originalConstrainer;
};

#endif
