// Copyright (C) 2008-2011 by One Guy Group, Inc., All rights reserved worldwide.

#include "Common.h"
#include "SettingsPanel.h"
#include "SettingsWindow.h"

SettingsWindow::SettingsWindow ()
: DialogWindow (TRANS("Settings"),
                Colour (192,192,192),
                true,
                true)
{
  SettingsPanel* contentComp = new SettingsPanel;

  setOpaque (true);
  setDropShadowEnabled (false);
  setUsingNativeTitleBar (true);

  // must happen AFTER setUsingNativeTitleBar()
  Component::addToDesktop (getDesktopWindowStyleFlags());

  // must happen after addToDesktop()
  setContentComponent (contentComp, true, true);

  centreWithSize (getWidth(), getHeight());
  setVisible (true);

  enterModalState ();
}

SettingsWindow::~SettingsWindow()
{
  deleteAllChildren ();
}

void SettingsWindow::closeButtonPressed()
{
  delete this;
}
