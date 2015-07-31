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

#include "Common.h"
#include "MainApp.h"
#include "SettingsWindow.h"

MainApp* MainApp::s_app = 0;

MainApp::MainApp()
{
  jassert (!s_app);
  s_app = this;
}

MainApp::~MainApp()
{
  jassert (s_app == this);
  s_app = 0;
}

void MainApp::initialise (const String& commandLine)
{
  //LookAndFeel::setDefaultLookAndFeel( &m_lookAndFeel );

  m_commandManager = new ApplicationCommandManager;
  m_commandManager->registerAllCommandsForTarget (this);

  m_audioOutput = new AudioOutput;

  m_mainWindow = new MainWindow;
}

void MainApp::shutdown()
{
  m_mainWindow = 0;
  m_commandManager = 0;
  m_audioOutput = 0;
}

const String MainApp::getApplicationName()
{
  return TRANS("Dsp Filters Demo");
}

const String MainApp::getApplicationVersion()
{
  return TRANS("1.1");
}

bool MainApp::moreThanOneInstanceAllowed()
{
  return true;
}

void MainApp::getAllCommands (Array <CommandID>& commands)
{
  JUCEApplication::getAllCommands (commands);

  const CommandID ids[] = {
    cmdSettings,
    cmdAbout
  };

  commands.addArray (ids, numElementsInArray (ids));
}

void MainApp::getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
{
  switch (commandID)
  {
  case cmdAbout:
    result.setInfo (TRANS("About Dsp Demo"),
                    TRANS("Displays the About box"), String::empty, 0);
    break;

  case cmdSettings:
    result.setInfo (TRANS("Settings..."),
                    TRANS("Adjust audio settings"), String::empty, 0);
    break;

  default:
    JUCEApplication::getCommandInfo (commandID, result);
    break;
  }
}

bool MainApp::perform (const InvocationInfo& info)
{
  switch (info.commandID)
  {
  case cmdSettings:
    {
      SettingsWindow* w = new SettingsWindow;
      w->setVisible (true);
    }
    return true;

  case cmdAbout:
    {
      AlertWindow::showMessageBox (AlertWindow::InfoIcon,
        TRANS("About"),
        TRANS(
          "DSP Filters Demo\n"
          "by Vinnie Falco,\n"
          "One Guy Group, Inc.\n"
          "Copyright(C) 2010\nAll Rights Reserved Worldwide."),
        TRANS("OK"),
        m_mainWindow);
    }
    return true;
  };

  return JUCEApplication::perform (info);
}

START_JUCE_APPLICATION (MainApp)

