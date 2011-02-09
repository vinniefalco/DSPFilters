#include "MainWindow.h"
#include "DemoPanel.h"
#include "MainPanel.h"

MainWindow::MainWindow () 
  : DocumentWindow (TRANS("Dsp Filters Demo"),
                    Colours::lightgrey, 
                    DocumentWindow::allButtons,
                    true)
{
  setResizable (true, false);
  
  //DemoPanel* contentComponent = new DemoPanel;
  MainPanel* contentComponent = new MainPanel;

  setMenuBar (contentComponent);
  setContentComponent (contentComponent, true, true);

  centreWithSize (getWidth(), getHeight());
  setVisible (true);
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeButtonPressed()
{
  JUCEApplication::quit();
}
