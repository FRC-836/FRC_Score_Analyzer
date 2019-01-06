#include "MainWindow.h"

extern OutputManager cout;

//private functions
void MainWindow::guiSetup()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: guiSetup()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //setpu the tables for the scoring tabs
  setupTable(m_ui->tblAutoBlue, "Blue");
  setupTable(m_ui->tblTeleBlue, "Blue");
  setupTable(m_ui->tblEndBlue, "Blue");
  setupTable(m_ui->tblAutoRed, "Red");
  setupTable(m_ui->tblTeleRed, "Red");
  setupTable(m_ui->tblEndRed, "Red");
}
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
  connect(m_ui->btnReset, &QPushButton::clicked, this, &MainWindow::btnResetClickHandler);
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

  //TODO implement
}
void MainWindow::saveScenario(const QString& scenarioPath)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: saveScenario()" << endl;
    cout << "\tsaving scenario to " << scenarioPath << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //TODO implement
}
bool MainWindow::loadScenario(const QString& scenarioPath)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: loadScenario()" << endl;
    cout << "\tloading scenario file: " << scenarioPath << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //TODO implement

  return false;
}
void MainWindow::displayAbout()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: displayAbout()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  auto author = QStringLiteral("Author: Matthew \"Cheeto\" Russell");
  auto title = QStringLiteral("FRC Score Analyzer");
  auto description = QStringLiteral("Tool used to analyze FRC game scoring");
  auto version = QStringLiteral("Version: 0.0.1");
  auto contactInfo = QStringLiteral("email: mprussell@robobees.org");

  QMessageBox::about(this, "About FRC Score Analyzer", title + "\n" + version + "\n" +
                     description + "\n" + author + "\n" + contactInfo);
}
void MainWindow::updateGui(const GameConfig_t& config)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: updateGui()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //clear the old tables
  m_ui->tblAutoBlue->setRowCount(0);
  m_ui->tblTeleBlue->setRowCount(0);
  m_ui->tblEndBlue->setRowCount(0);
  m_ui->tblAutoRed->setRowCount(0);
  m_ui->tblTeleRed->setRowCount(0);
  m_ui->tblEndRed->setRowCount(0);

  for (auto scoreMethod : std::get<(int)GameConfigTuple::SCORE_METHOD_LIST>(config))
  {
    auto name = std::get<(int)ScoreMethodTuple::NAME>(scoreMethod);
    if (std::get<(int)ScoreMethodTuple::AUTO_SCORE>(scoreMethod) > 0)
    {
      auto score = std::get<(int)ScoreMethodTuple::AUTO_SCORE>(scoreMethod);
      addRow(m_ui->tblAutoRed, name, score);
      addRow(m_ui->tblAutoBlue, name, score);
    } //end  if (std::get<(int)ScoreMethodTuple::AUTO_SCORE>(scoreMethod) < 0)
    if (std::get<(int)ScoreMethodTuple::TELE_SCORE>(scoreMethod) > 0)
    {
      auto score = std::get<(int)ScoreMethodTuple::TELE_SCORE>(scoreMethod);
      addRow(m_ui->tblTeleRed, name, score);
      addRow(m_ui->tblTeleBlue, name, score);
    } //end  if (std::get<(int)ScoreMethodTuple::TELE_SCORE>(scoreMethod) < 0)
    if (std::get<(int)ScoreMethodTuple::END_SCORE>(scoreMethod) > 0)
    {
      auto score = std::get<(int)ScoreMethodTuple::END_SCORE>(scoreMethod);
      addRow(m_ui->tblEndRed, name, score);
      addRow(m_ui->tblEndBlue, name, score);
    } //end  if (std::get<(int)ScoreMethodTuple::END_SCORE>(scoreMethod) < 0)
  } //end  for (auto scoreMethod : std::get<(int)GameConfigTuple::SCORE_METHOD_LIST>(config))
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
void MainWindow::updateSummaryTab()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: updateSummaryTab()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //calculate auto score
  auto redAutoScore = 0;
  auto blueAutoScore = 0;
  for (int i = 0; i < m_ui->tblAutoRed->rowCount(); i++)
  {
    redAutoScore += calculateRow(m_ui->tblAutoRed, i);
  } //end  for (int i = 0; i < m_ui->tblAutoRed->rowCount(); i++)
  for (int i = 0; i < m_ui->tblAutoBlue->rowCount(); i++)
  {
    blueAutoScore += calculateRow(m_ui->tblAutoBlue, i);
  } //end  for (int i = 0; i < m_ui->tblAutoBlue-<rowCount(); i++)

  //calculate teleop score
  auto redTeleScore = 0;
  auto blueTeleScore = 0;
  for (int i = 0; i < m_ui->tblTeleRed->rowCount(); i++)
  {
    redTeleScore += calculateRow(m_ui->tblTeleRed, i);
  } //end  for (int i = 0; i < m_ui->tblTeleRed->rowCount(); i++)
  for (int i = 0; i < m_ui->tblTeleBlue->rowCount(); i++)
  {
    blueTeleScore += calculateRow(m_ui->tblTeleBlue, i);
  } //end  for (int i = 0; i < m_ui->tblTeleBlue->rowCount(); i++)

  //calculate end game score
  auto redEndScore = 0;
  auto blueEndScore = 0;
  for (int i = 0; i < m_ui->tblEndRed->rowCount(); i++)
  {
    redEndScore += calculateRow(m_ui->tblEndRed, i);
  } //end  for (int i = 0; i < m_ui->tblEndRed->rowCount(); i++)
  for (int i = 0; i < m_ui->tblEndBlue->rowCount(); i++)
  {
    blueEndScore += calculateRow(m_ui->tblEndBlue, i);
  } //end  for (int i = 0; i < m_ui->tblEndBlue->rowCount(); i++)

  //calculate the total scores
  auto redTotalScore = 0;
  auto blueTotalScore = 0;
  redTotalScore = redAutoScore + redTeleScore + redEndScore;
  blueTotalScore = blueAutoScore + blueTeleScore + blueEndScore;

  m_ui->tblSummary->setCellWidget(0, 0, new QLabel(QString::number(redAutoScore)));
  m_ui->tblSummary->setCellWidget(0, 1, new QLabel(QString::number(blueAutoScore)));
  m_ui->tblSummary->setCellWidget(1, 0, new QLabel(QString::number(redTeleScore)));
  m_ui->tblSummary->setCellWidget(1, 1, new QLabel(QString::number(blueTeleScore)));
  m_ui->tblSummary->setCellWidget(2, 0, new QLabel(QString::number(redEndScore)));
  m_ui->tblSummary->setCellWidget(2, 1, new QLabel(QString::number(blueEndScore)));
  m_ui->tblSummary->setCellWidget(3, 0, new QLabel(QString::number(redTotalScore)));
  m_ui->tblSummary->setCellWidget(3, 1, new QLabel(QString::number(blueTotalScore)));
}
void MainWindow::setupTable(QTableWidget* table, QString prefix)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: setupTable()" << endl;

  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  table->setColumnCount(4);
  table->setRowCount(0);
  table->setHorizontalHeaderLabels({"Scoring Method Name", prefix + " 1", prefix + " 2", 
                                    prefix + " 3"});
}
void MainWindow::addRow(QTableWidget* table, const QString& name, int score)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: addRow()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  const auto row = table->rowCount();

  table->setRowCount(table->rowCount() + 1);

  //name column
  table->setCellWidget(row, 0, new QLabel(name));

  auto spnOne = new QSpinBox();
  spnOne->setMinimum(0);
  spnOne->setSingleStep(score);
  connect(m_ui->btnReset, &QPushButton::clicked, 
          std::bind(&QSpinBox::setValue, spnOne, 0));

  //create the tele spinbox
  auto spnTwo = new QSpinBox();
  spnTwo->setMinimum(0);
  spnTwo->setSingleStep(score);
  connect(m_ui->btnReset, &QPushButton::clicked, 
          std::bind(&QSpinBox::setValue, spnTwo, 0));

  //create the end game spinbox
  auto spnThree = new QSpinBox();
  spnThree->setMinimum(0);
  spnThree->setSingleStep(score);
  connect(m_ui->btnReset, &QPushButton::clicked, 
          std::bind(&QSpinBox::setValue, spnThree, 0));

  table->setCellWidget(row, 1, spnOne);
  table->setCellWidget(row, 2, spnTwo);
  table->setCellWidget(row, 3, spnThree);
}
void MainWindow::resizeTable(QTableWidget* table)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: resizeTable()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  table->setColumnWidth(0, table->width() / 4 - 10);
  table->setColumnWidth(1, table->width() / 4 - 10);
  table->setColumnWidth(2, table->width() / 4 - 10);
  table->setColumnWidth(3, table->width() / 4 - 10);
}
void MainWindow::resizeSummaryTable()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: resizeSummaryTable()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  m_ui->tblSummary->setColumnWidth(0, m_ui->tblSummary->width() / 2 - 5);
  m_ui->tblSummary->setColumnWidth(1, m_ui->tblSummary->width() / 2 - 5);
}
int MainWindow::calculateRow(QTableWidget* table, int row) const
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: calculateRow()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //get the three spin boxes that contain the scores for this row
  auto spnScoreOne = qobject_cast<QSpinBox*>(table->cellWidget(row, 1));
  auto spnScoreTwo = qobject_cast<QSpinBox*>(table->cellWidget(row, 2));
  auto spnScoreThree = qobject_cast<QSpinBox*>(table->cellWidget(row, 3));

  //if any of the spinbox grabs failed, error out
  if (spnScoreOne == nullptr) 
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    {
      cout << "ERROR: MainWindow: Couldn't grab score one from row " << row << endl;
      cout << "\tsuggest restarting the app, score's may be wrong" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    return 0;
  } //end  if (spnScoreOne == nullptr) 
  if (spnScoreTwo == nullptr) 
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    {
      cout << "ERROR: MainWindow: Couldn't grab score two from row " << row << endl;
      cout << "\tsuggest restarting the app, score's may be wrong" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    return 0;
  } //end  if (spnScoreTwo == nullptr) 
  if (spnScoreThree == nullptr) 
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    {
      cout << "ERROR: MainWindow: Couldn't grab score three from row " << row << endl;
      cout << "\tsuggest restarting the app, score's may be wrong" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    return 0;
  } //end  if (spnScoreThree == nullptr) 

  return spnScoreOne->value() + spnScoreTwo->value() + spnScoreThree->value();
}

MainWindow::MainWindow()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: constructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  m_ui = std::make_unique<Ui_MainWindow>();
  m_ui->setupUi(this);

  guiSetup();
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
void MainWindow::resizeEvent(QResizeEvent* e)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: resizeEvennt()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  resizeTable(m_ui->tblAutoBlue);
  resizeTable(m_ui->tblTeleBlue);
  resizeTable(m_ui->tblEndBlue);
  resizeTable(m_ui->tblAutoRed);
  resizeTable(m_ui->tblTeleRed);
  resizeTable(m_ui->tblEndRed);
  resizeSummaryTable();
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

  switch (index)
  {
    case (int)Tabs::AUTO:
      resizeTable(m_ui->tblAutoRed);
      resizeTable(m_ui->tblAutoBlue);
      break;
    case (int)Tabs::END_GAME:
      resizeTable(m_ui->tblEndRed);
      resizeTable(m_ui->tblEndBlue);
      break;
    case (int)Tabs::SUMMARY:
      updateSummaryTab();
      resizeSummaryTable();
      break;
    case (int)Tabs::TELEOP:
      resizeTable(m_ui->tblTeleRed);
      resizeTable(m_ui->tblTeleBlue);
      break;
    default:
      if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
      {
        cout << "ERROR: MainWindow: Somehow switched to an unrecognized tab." << endl;
        cout << "\tApp restart recommended" << endl;
      } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
      break;
  } //end  switch (index)
}
void MainWindow::btnResetClickHandler()
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: MainWindow: btnResetClickHandler()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //TODO figure out how to wait for all spin boxes to reset

  updateSummaryTab();
}
