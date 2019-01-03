#ifndef FRC_2018_SCORE_ANALYZER_MAIN_WINDOW_H
#define FRC_2018_SCORE_ANALYZER_MAIN_WINDOW_H

#include <iostream>
#include <memory>

#include <QMainWindow>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>

#include "ui_MainWindow.h"
#include "ConfigParser.h"
#include "CmdOptions.h"
#include "OutputManager.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  //enums
  enum class Tabs
  {
    AUTO,
    TELEOP,
    END_GAME,
    SUMMARY
  };

  //private functions
  void guiSetup();
  void makeConnections();
  void loadGame(const QString& gameConfigPath);
  void newGame();
  void saveScenario(const QString& scenarioPath);
  bool loadScenario(const QString& scenarioPath);
  void displayAbout();
  void updateGui(const GameConfig_t& config);
  bool getGamePath(QString& gameFilePath, bool save = false);
  bool getScenarioPath(QString& scenarioFilePath, bool save = false);
  void updateSummaryTab();
  void setupTable(QTableWidget* table, QString prefix);
  void addRow(QTableWidget* table, const ScoreMethod_t& scoreMethod);
  void resizeTable(QTableWidget* table);

  //member variables
  std::unique_ptr<Ui_MainWindow> m_ui;

protected:
  //event handlers
  void closeEvent(QCloseEvent* e) override;
  void resizeEvent(QResizeEvent* e) override;

public:
  //constructors
  MainWindow();
  ~MainWindow();

  //public functions

signals:
  //signals

public slots:
  //public slots
  void actNewGameHandler();
  void actLoadGameHandler();
  void actSaveScenarioHandler();
  void actLoadScenarioHandler();
  void actAboutHandler();
  void tabChangeHandler(int index);
};

#endif
