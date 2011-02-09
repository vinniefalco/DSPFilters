#ifndef DSPDEMO_MAINPANEL_H
#define DSPDEMO_MAINPANEL_H

#include "Common.h"
#include "GraphComponent.h"
#include "ResizableLayout.h"

class PoleChart2;
class ResponseGraph2;
class KnobPanel;

class FilterListener
{
public:
  virtual void onFilterChanged (Dsp::Filter* newFilter)
  {
  }

  virtual void onFilterParameters ()
  {
  }
};

class MainPanel :
	public Component,
  public MenuBarModel,
	public ButtonListener,
	public ComboBoxListener,
  public ResizableLayout,
  public FilterListener
{
public:
  MainPanel();
  ~MainPanel();

  const StringArray getMenuBarNames();
  const PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName);
  void menuItemSelected (int menuItemID, int topLevelMenuIndex);

  void paint (Graphics& g);

  void setFilter (int id);

  void onFilterParameters ();

  void buttonClicked (Button *ctrl);
  void comboBoxChanged (ComboBox* ctrl);

private:
  ListenerList<FilterListener> m_listeners;
  ComboBox* m_menuFilter;
  KnobPanel* m_knobPanel;
  ScopedPointer<Dsp::Filter> m_filter;
  PoleChart2* m_poleChart;
  ResponseGraph2* m_responseGraph;
};

#endif

