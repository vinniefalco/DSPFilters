#include "MainApp.h"

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
      /*
      SettingsWindow* w = new SettingsWindow (*getCoreView());
      w->addToDesktop (w->getDesktopWindowStyleFlags());
      w->setVisible (true);
      */
    }
    return true;

  case cmdAbout:
    {
      AlertWindow::showMessageBox (AlertWindow::InfoIcon,
        TRANS("About"),
        TRANS("Dsp Demo written by Vincent Falco\nCopyright(C) 2010\nAll Rights Reserved Worldwide."),
        TRANS("OK"),
        m_mainWindow);
    }
    return true;
  };

  return JUCEApplication::perform (info);
}

START_JUCE_APPLICATION (MainApp)

