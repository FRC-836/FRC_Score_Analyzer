#ifndef FRC_2018_SCORE_ANALYZER_MAIN_WINDOW_H
#define FRC_2018_SCORE_ANALYZER_MAIN_WINDOW_H

#include <iostream> //for testing only

#include "ui_MainWindow.h"

class MainWindow : public QWidget
{
  Q_OBJECT
private:
  //constants
  static const int SCALE_MAX = 135;

  //member variables
  Ui_MainWindow* m_ui;

  //private functions
  void makeConnections();
  int calculateSwitch(bool red);
  int calculateScale(bool red);
  int calculateVault(bool red);
  int calculateBoost(bool red);
  int calculateClimb(bool red);
  int calculateAutoRun(bool Red);

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
  void redScaleChanged();
  void blueScaleChanged();
  void handleRedSwitch();
  void handleBlueSwitch();
};

#endif
