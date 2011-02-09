#ifndef DSPDEMO_MAINAPP_H
#define DSPDEMO_MAINAPP_H

#include "Common.h"
#include "AudioOutput.h"
#include "MainWindow.h"

class MainApp : public JUCEApplication
{
public:
  enum CommandIDs
  {
    cmdSettings                  = 0x2001,
    cmdAbout                     = 0x2020
  };

public:
  MainApp();
  ~MainApp();

  void initialise (const String& commandLine);
  void shutdown ();
  const String getApplicationName ();
  const String getApplicationVersion ();
  bool moreThanOneInstanceAllowed ();

  void getAllCommands (Array <CommandID>& commands);
  void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result);
  bool perform (const InvocationInfo& info);

  ApplicationCommandManager* getCommandManager() { return m_commandManager; }
  AudioOutput& getAudioOutput () { return *m_audioOutput; }

  static MainApp& getInstance() { return *s_app; }

private:
  static MainApp* s_app;

  ScopedPointer<ApplicationCommandManager> m_commandManager;
  ScopedPointer<AudioOutput> m_audioOutput;
  ScopedPointer<MainWindow> m_mainWindow;
};

#endif
