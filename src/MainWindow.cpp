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
void MainWindow::loadGame(const QString& gameConfigPath)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: loadGame()" << endl;
    cout << "\tloading game file: " << gameConfigPath << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //parse the provided game config file
  ConfigParser parser;
  if (!parser.parse(gameConfigPath))
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    {
      cout << "ERROR: MainWindow: Couldn't process game file, ignoring request" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    return;
  } //end  if (!parser.parse(gameConfigPath))

  //update GUI with the new game config
  updateGui(parser.getConfig());
}
void MainWindow::newGame()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: newGame()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}
void MainWindow::saveScenario(const QString& scenarioPath)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: saveScenario()" << endl;
    cout << "\tsaving scenario to " << scenarioPath << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}
bool MainWindow::loadScenario(const QString& scenarioPath)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: loadScenario()" << endl;
    cout << "\tloading scenario file: " << scenarioPath << endl;
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
void MainWindow::updateGui(const GameConfig_t& config)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: updateGui()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
}
bool MainWindow::getGamePath(QString& gameFilePath, bool save)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: getGamePath()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //store the most recently opened directory for use as the start directory next time
  static QString previousDir = QDir::homePath();

  //create a QFileDialog to grab the file the user wants to open
  QFileDialog fileDiag(this);
  fileDiag.setWindowTitle("Open Game File");
  if (save)
  {
    fileDiag.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
  } //end  if (save)
  else
  {
    fileDiag.setFileMode(QFileDialog::FileMode::ExistingFile);
  } //end  else
  fileDiag.setNameFilter("Game Config File (*.xml)"); //may change
  fileDiag.setDirectory(previousDir);
  fileDiag.exec();

  if (!fileDiag.selectedFiles().isEmpty())
  {
    gameFilePath = fileDiag.selectedFiles().at(0);
    previousDir = fileDiag.directory().absolutePath();
    return true;
  } //end  if (!fileDiag.selectedFiles().isEmpty())

  return false;
}
bool MainWindow::getScenarioPath(QString& scenarioFilePath, bool save)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: getScenarioPath()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //store the most recently opened directory for use as the start directory next time
  static QString previousDir = QDir::homePath();

  //create a QFileDialog to grab the file the user wants to open
  QFileDialog fileDiag(this);
  fileDiag.setWindowTitle("Open Scenario File");
  if (save)
  {
    fileDiag.setAcceptMode(QFileDialog::AcceptMode::AcceptSave);
  } //end  if (save)
  else
  {
    fileDiag.setFileMode(QFileDialog::FileMode::ExistingFile);
  } //end  else
  fileDiag.setNameFilter("Scenario File (*.json)"); //may change
  fileDiag.setDirectory(previousDir);
  fileDiag.exec();

  if (!fileDiag.selectedFiles().isEmpty())
  {
    scenarioFilePath = fileDiag.selectedFiles().at(0);
    previousDir = fileDiag.directory().absolutePath();
    return true;
  } //end  if (!fileDiag.selectedFiles().isEmpty())

  return false;
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

  //load the game provided by config path if there was one
  if (!CmdOptions::configFilePath.trimmed().isEmpty())
  {
    loadGame(CmdOptions::configFilePath);
  } //end  if (!CmdOptions::configFilePath.trimmed().isEmpty())
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

  QString filePath;
  if (!getGamePath(filePath))
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
    {
      cout << "DEBUG: MainWindow: loading game file canceled" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
    return;
  } //end  if (!getGamePath(filePath))

  loadGame(filePath);
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

  QString filePath;
  if (!getScenarioPath(filePath))
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
    {
      cout << "DEBUG: MainWindow: loading scenario file canceled" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
    return;
  } //end  if (!getScenarioPath(filePath))

  loadScenario(filePath);
}
void MainWindow::actAboutHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: actAboutHandler()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  displayAbout();
}
void MainWindow::tabChangeHandler(int index)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: tabChangeHandler()" << endl;
    cout << "\ttab changed to " << m_ui->tabWidget->tabText(index) << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //TODO add check to only recalculate summary page when switched to
}
