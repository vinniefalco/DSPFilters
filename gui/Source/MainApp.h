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

  ScopedPointer <ApplicationCommandManager> m_commandManager;
  ScopedPointer <AudioOutput> m_audioOutput;
  ScopedPointer <MainWindow> m_mainWindow;
};

#endif
