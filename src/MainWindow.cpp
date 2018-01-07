#include "MainWindow.h"

//private functions
void MainWindow::makeConnections()
{
}

//constructors
MainWindow::MainWindow()
{
  m_ui = new Ui_MainWindow();
  m_ui->setupUi(this);

  makeConnections();
}
MainWindow::~MainWindow()
{
  delete m_ui;
}

//getters

//setters

//op overloads

//public signals
void MainWindow::updateScore()
{
}
void MainWindow::handleScaleSliders()
{
}
void MainWindow::handleRedSwitch()
{
}
void MainWindow::handleBlueSwitch()
{
  //need to make safe
  QSlider* sender = qobject_cast<QSlider*>(QObject::sender());
}