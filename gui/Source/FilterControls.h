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

#ifndef DSPDEMO_FILTERCONTROLS_H
#define DSPDEMO_FILTERCONTROLS_H

#include "Common.h"
#include "FilterListener.h"
#include "ResizableLayout.h"
#include "SliderGroup.h"

/*
 * Creates filter Gui controls dynamically, using
 * the introspection features of Dsp::Filter.
 *
 */
class FilterControls
  : public Component
  , public FilterListener
{
public:
  FilterControls (ListenerList<FilterListener>& listeners);
  ~FilterControls ();

  void paint (Graphics& g);

  void onFilterChanged (Dsp::Filter* newFilter);

protected:
  void clear ();

private:
  struct Item
  {
    Item ()
    {
      group = 0;
    }

    SliderGroup* group;
  };

  ListenerList<FilterListener>& m_listeners;
  Array<Item> m_items;
  Dsp::Filter* m_filter;
};

#endif
