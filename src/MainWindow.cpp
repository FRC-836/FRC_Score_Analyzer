#include "MainWindow.h"

extern OutputManager cout;

//private functions
void MainWindow::makeConnections()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: makeConnections()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  connect(m_ui->actClose, &QAction::triggered, this, &QMainWindow::close);
  connect(m_ui->actAbout, &QAction::triggered, this, &MainWindow::actAboutHandler);
  connect(m_ui->actNewGame, &QAction::triggered, this, &MainWindow::actNewGameHandler);
  connect(m_ui->actLoadGame, &QAction::triggered, this, &MainWindow::actLoadGameHandler);
  connect(m_ui->actLoadScenario, &QAction::triggered, 
          this, &MainWindow::actLoadScenarioHandler);
  connect(m_ui->actSaveScenario, &QAction::triggered,
          this, &MainWindow::actSaveScenarioHandler);

  connect(m_ui->tabWidget, &QTabWidget::currentChanged, 
          this, &MainWindow::tabChangeHandler);
}
bool MainWindow::loadGame()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: loadGame()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  return false;
}
void MainWindow::newGame()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: newGame()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}
void MainWindow::saveScenario()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: saveScenario()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}
bool MainWindow::loadScenario()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: loadScenario()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  return false;
}
void MainWindow::displayAbout()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: displayAbout()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}

MainWindow::MainWindow()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: constructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  m_ui = std::make_unique<Ui_MainWindow>();
  m_ui->setupUi(this);

  makeConnections();
}
MainWindow::~MainWindow()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: destructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}

//event handlers
void MainWindow::closeEvent(QCloseEvent* e)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: closeEvent()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}

//public slots
void MainWindow::actNewGameHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: actNewGameHandler()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}
void MainWindow::actLoadGameHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: actLoadGameHandler()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}
void MainWindow::actSaveScenarioHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: actSaveScenarioHandler()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}
void MainWindow::actLoadScenarioHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: actLoadScenarioHandler()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}
void MainWindow::actAboutHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: actAboutHandler()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}
void MainWindow::tabChangeHandler(int index)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: tabChangeHandler()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}
