#include "MainWindow.h"

extern OutputManager cout;

//private functions
void MainWindow::makeConnections()
{
}
bool MainWindow::loadGame(const QString& gameConfigPath)
{
  return false;
}
void MainWindow::newGame()
{
}
void MainWindow::saveScenario(const QString& scenarioPath)
{
}
bool MainWindow::loadScenario(const QString& scenarioPath)
{
  return false;
}
void MainWindow::displayAbout()
{
}

MainWindow::MainWindow()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: constructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  m_ui = std::make_unique<Ui_MainWindow>();
  m_ui->setupUi(this);
}
MainWindow::~MainWindow()
{
}

//event handlers
void MainWindow::closeEvent(QCloseEvent* e)
{
}

//public slots
void MainWindow::actNewGameHandler()
{
}
void MainWindow::actLoadGameHandler()
{
}
void MainWindow::actSaveScenarioHandler()
{
}
void MainWindow::actLoadScenarioHandler()
{
}
void MainWindow::actAboutHandler()
{
}
void MainWindow::tabChangeHandler(int index)
{
}
