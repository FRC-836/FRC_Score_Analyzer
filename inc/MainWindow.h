#ifndef FRC_2018_SCORE_ANALYZER_MAIN_WINDOW_H
#define FRC_2018_SCORE_ANALYZER_MAIN_WINDOW_H

#include <iostream> //for testing only

#include "ui_MainWindow.h"

class MainWindow : public QWidget
{
  Q_OBJECT
private:
  //constants
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
};

#endif
