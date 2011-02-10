#include "Common.h"
#include "MainApp.h"
#include "SettingsPanel.h"

SettingsPanel::SettingsPanel ()
{
  setSize (800, 600);

  Component* c = new AudioDeviceSelectorComponent(
    MainApp::getInstance().getAudioOutput().getAudioDeviceManager(),
    0, 2,
    2, 6,
    true, true,
    true,
    false );
  c->setBounds (0, 0, 600, 400);
  addAndMakeVisible (c);
}

SettingsPanel::~SettingsPanel()
{
  deleteAllChildren ();
}
