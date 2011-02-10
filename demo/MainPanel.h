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
  bool isEnabled (int familyId);
  bool isEnabled (int familyId, int typeId);
  void buildFamilyMenu (ComboBox* comboBox);
  void buildTypeMenu (ComboBox* comboBox);

  void paint (Graphics& g);

  void setFilter (int familyId, int typeId);
  void setAudio (int audioId);

  void buttonClicked (Button *ctrl);
  void sliderValueChanged (Slider* ctrl);
  void comboBoxChanged (ComboBox* ctrl);

  void onFilterParameters ();

  const StringArray getMenuBarNames();
  const PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName);
  void menuItemSelected (int menuItemID, int topLevelMenuIndex);

private:
  template <class DesignType>
  void createSmoothedFilter (Dsp::Filter** pFilter, Dsp::Filter** pAudioFilter);

private:
  ListenerList<FilterListener> m_listeners;
  ComboBox* m_menuFamily;
  ComboBox* m_menuType;
  ComboBox* m_menuAudio;
  Slider* m_volumeSlider;
  Slider* m_tempoSlider;

  int m_lastTypeId;

  ScopedPointer<Dsp::Filter> m_filter;
};

#endif

