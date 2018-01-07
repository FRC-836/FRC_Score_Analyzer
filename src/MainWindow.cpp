#include "MainWindow.h"

//private functions
void MainWindow::makeConnections()
{
  //scale sliders
  connect(m_ui->m_hslBlueScale, &QSlider::valueChanged, this, &MainWindow::blueScaleChanged);
  connect(m_ui->m_hslRedScale, &QSlider::valueChanged, this, &MainWindow::redScaleChanged);

  //switchs slider
  connect(m_ui->m_hslBlueSwitch, &QSlider::valueChanged, this, &MainWindow::handleBlueSwitch);
  connect(m_ui->m_hslRedSwitch, &QSlider::valueChanged, this, &MainWindow::handleRedSwitch);

  //cubes in vault
  connect(m_ui->m_spnBlueVault, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &MainWindow::updateScore);
  connect(m_ui->m_spnRedVault, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &MainWindow::updateScore);

  //boost
  connect(m_ui->m_chkBlueBoost, &QCheckBox::stateChanged, this, &MainWindow::updateScore);
  connect(m_ui->m_chkRedBoost, &QCheckBox::stateChanged, this, &MainWindow::updateScore);

  //climbs
  connect(m_ui->m_spnBlueClimb, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &MainWindow::updateScore);
  connect(m_ui->m_spnRedClimb, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &MainWindow::updateScore);

  //auto runs
  connect(m_ui->m_spnBlueAutoRun, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &MainWindow::updateScore);
  connect(m_ui->m_spnRedAutoRun, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
          this, &MainWindow::updateScore);
}
int MainWindow::calculateSwitch(bool red)
{
  return red ? m_ui->m_hslRedSwitch->value() : m_ui->m_hslBlueSwitch->value();
}
int MainWindow::calculateScale(bool red)
{
  return red ? m_ui->m_hslRedScale->value() : m_ui->m_hslBlueScale->value();
}
int MainWindow::calculateVault(bool red)
{
  int numVaults = red ? m_ui->m_spnRedVault->value() : m_ui->m_spnBlueVault->value();
  return numVaults * 5; //cubes scored in vault are worth 5 points each
}
int MainWindow::calculateBoost(bool red)
{
  int total = 0;

  //calculate switch boost points
  int switchPoints = red ? m_ui->m_hslRedSwitch->value() : m_ui->m_hslBlueSwitch->value();
  total += (switchPoints >= 10) ? 10 : switchPoints;

  //calculate scale boost points
  int scalePoints = red ? m_ui->m_hslRedScale->value() : m_ui->m_hslBlueScale->value();
  total += (scalePoints >= 10) ? 10 : scalePoints;

  bool boostUsed = red ? m_ui->m_chkRedBoost->isChecked() : m_ui->m_chkBlueBoost->isChecked();
  return boostUsed ? total : 0;
}
int MainWindow::calculateClimb(bool red)
{
  int numClimbs = red ? m_ui->m_spnRedClimb->value() : m_ui->m_spnBlueClimb->value();
  return numClimbs * 30; //each climb is worth 30 points
}
int MainWindow::calculateAutoRun(bool red)
{
  int numRuns = red ? m_ui->m_spnRedAutoRun->value() : m_ui->m_spnBlueAutoRun->value();
  return numRuns * 5; //each auto run is worth 5 points
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
  int redTotal = 0;
  int blueTotal = 0;

  //switch points
  redTotal += calculateSwitch(true);
  blueTotal += calculateSwitch(false);

  //scale points
  redTotal += calculateScale(true);
  blueTotal += calculateScale(false);

  //vault points
  redTotal += calculateVault(true);
  blueTotal += calculateVault(false);

  //boost points
  redTotal += calculateBoost(true);
  blueTotal += calculateBoost(false);

  //climb points
  redTotal += calculateClimb(true);
  blueTotal += calculateClimb(false);

  //auto run points
  redTotal += calculateAutoRun(true);
  blueTotal += calculateAutoRun(false);

  //display totals
  m_ui->m_lblRedFinalScore->setText(QString::number(redTotal));
  m_ui->m_lblBlueFinalScore->setText(QString::number(blueTotal));
}
void MainWindow::redScaleChanged()
{
  QSlider* slider = qobject_cast<QSlider*>(QObject::sender());
  m_ui->m_lblRedScaleScore->setText(QString::number(slider->value()));

  //adjust blue scale
  if ((slider->value() + m_ui->m_hslBlueScale->value()) > SCALE_MAX)
  {
    int blueScaleScore = SCALE_MAX - slider->value();
    m_ui->m_hslBlueScale->blockSignals(true); //necessary to prevent recurssion of this calling bluescalechanged()
    m_ui->m_hslBlueScale->setValue(blueScaleScore);
    m_ui->m_lblBlueScaleScore->setText(QString::number(blueScaleScore));
    m_ui->m_hslBlueScale->blockSignals(false);
  }
  updateScore();
}
void MainWindow::blueScaleChanged()
{
  QSlider* slider = qobject_cast<QSlider*>(QObject::sender());
  m_ui->m_lblBlueScaleScore->setText(QString::number(slider->value()));

  //adjust blue scale if total of scores excedes max
  if ((slider->value() + m_ui->m_hslRedScale->value()) > SCALE_MAX)
  {
    int redScaleScore = SCALE_MAX - slider->value();
    m_ui->m_hslRedScale->blockSignals(true); //necessary to prevent recurssion of this calling bluescalechanged()
    m_ui->m_hslRedScale->setValue(redScaleScore);
    m_ui->m_lblRedScaleScore->setText(QString::number(redScaleScore));
    m_ui->m_hslRedScale->blockSignals(false);
  }
  updateScore();
}
void MainWindow::handleRedSwitch()
{
  QSlider* slider = qobject_cast<QSlider*>(QObject::sender());
  m_ui->m_lblRedSwitchScore->setText(QString::number(slider->value()));
  updateScore();
}
void MainWindow::handleBlueSwitch()
{
  //TODO: make safe
  QSlider* slider = qobject_cast<QSlider*>(QObject::sender());
  m_ui->m_lblBlueSwitchScore->setText(QString::number(slider->value()));
  updateScore();
}