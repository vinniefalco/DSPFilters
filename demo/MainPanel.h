#ifndef DSPDEMO_MAINPANEL_H
#define DSPDEMO_MAINPANEL_H

#include "Common.h"
#include "ResizableLayout.h"
#include "FilterListener.h"

class MainPanel :
	public Component,
  public MenuBarModel,
	public ButtonListener,
	public ComboBoxListener,
  public TopLevelResizableLayout,
  public FilterListener
{
public:
  MainPanel();
  ~MainPanel();

  void createCharts (const Rectangle<int>& r);
  bool isEnabled (int familyId);
  bool isEnabled (int familyId, int typeId);
  void buildFamilyMenu (ComboBox* comboBox);
  void buildTypeMenu (ComboBox* comboBox);

  void paint (Graphics& g);

  void setFilter (int familyId, int typeId);
  void buttonClicked (Button *ctrl);
  void comboBoxChanged (ComboBox* ctrl);

  void onFilterParameters ();

  const StringArray getMenuBarNames();
  const PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName);
  void menuItemSelected (int menuItemID, int topLevelMenuIndex);

private:
  ListenerList<FilterListener> m_listeners;
  ComboBox* m_menuFamily;
  ComboBox* m_menuType;
  int m_lastTypeId;

  ScopedPointer<Dsp::Filter> m_filter;
};

#endif

