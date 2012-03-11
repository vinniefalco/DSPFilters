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

#ifndef DSPDEMO_MAINPANEL_H
#define DSPDEMO_MAINPANEL_H

#include "Common.h"
#include "ResizableLayout.h"
#include "FilterListener.h"

class MainPanel :
	public Component,
  public MenuBarModel,
	public ButtonListener,
  public SliderListener,
	public ComboBoxListener,
  public TopLevelResizableLayout,
  public FilterListener
{
public:
  MainPanel();
  ~MainPanel();

  void createCharts (const Rectangle<int>& r);
  void buildFamilyMenu (ComboBox* comboBox);
  void buildTypeMenu (ComboBox* comboBox);

  void paint (Graphics& g);

  void setAudio (int audioId);

  void buttonClicked (Button *ctrl);
  void sliderValueChanged (Slider* ctrl);
  void comboBoxChanged (ComboBox* ctrl);

  void onFilterParameters ();

  const StringArray getMenuBarNames();
  const PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName);
  void menuItemSelected (int menuItemID, int topLevelMenuIndex);

private:
  template <class DesignType, class StateType>
  void createFilterDesign (Dsp::Filter** pFilter, Dsp::Filter** pAudioFilter);

  template <class DesignType>
  void createFilterState (Dsp::Filter** pFilter, Dsp::Filter** pAudioFilter);

  void createFilter ();

private:
  ListenerList<FilterListener> m_listeners;
  ComboBox* m_menuFamily;
  ComboBox* m_menuType;
  ComboBox* m_menuAudio;
  ComboBox* m_menuStateType;
  ComboBox* m_menuSmoothing;
  Button* m_resetButton;
  Slider* m_volumeSlider;
  Slider* m_tempoSlider;

  int m_lastTypeId;

  ScopedPointer<Dsp::Filter> m_filter;
};

#endif

