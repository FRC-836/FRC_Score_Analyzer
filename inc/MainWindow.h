#ifndef FRC_2018_SCORE_ANALYZER_MAIN_WINDOW_H
#define FRC_2018_SCORE_ANALYZER_MAIN_WINDOW_H

#include "ui_MainWindow.h"

class MainWindow : public QWidget
{
  Q_OBJECT
private:
  //member variables
  Ui_MainWindow* m_ui;

  //private functions
  void makeConnections();

public:
  //constructors
  MainWindow();
  ~MainWindow();

  //public functions

  //getters

  //setters

  //op overloads

signals:
  //signals

public slots:
  //public slots
  void updateScore();
  void handleScaleSliders();
  void handleRedSwitch();
  void handleBlueSwitch();
};

#endif