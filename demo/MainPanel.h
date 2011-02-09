#ifndef DSPDEMO_MAINPANEL_H
#define DSPDEMO_MAINPANEL_H

#include "Common.h"
#include "BrickWallChart.h"
#include "PoleZeroChart.h"
#include "ResizableLayout.h"
#include "FilterListener.h"

class KnobPanel;

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

  BrickWallChart* m_brickWallChart;
  PoleZeroChart* m_poleChart;
};

#endif

