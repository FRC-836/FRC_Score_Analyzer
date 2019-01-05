#include <qapplication.h>
#include <qcommandlineparser.h>

#include "MainWindow.h"
#include "CmdOptions.h"
#include "OutputManager.h"

OutputManager cout(stdout);

bool parseCmd(QCommandLineParser& parser);

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  QCommandLineParser parser;
  if (!parseCmd(parser))
  {
    parser.showHelp(1);
  } //end  if (!parseCmd())

  //print out the cmd args
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "Verbosity:        " << CmdOptions::verbosity << endl;
    cout << "Game Config File: " << CmdOptions::configFilePath << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  MainWindow mainWindow;
  
  mainWindow.show();

  return app.exec();
}

bool parseCmd(QCommandLineParser& parser)
{
  parser.addHelpOption();
  parser.setApplicationDescription("Analyze the scoring in robotics games");

  parser.addOptions({{{"v", "verbosity"}, "Verbosity of the info displayed", "verbosityLevel", "3"},
                     {{"c", "config"}, "Location of the game config file", "configPath", ""}});

  parser.process(QCoreApplication::arguments());

  bool conversionSuccess = false;

  int verbosity = parser.value("verbosity").toInt(&conversionSuccess);
  if (!conversionSuccess)
  {
    return false;
  } //end  if (!conversionSuccess)
  verbosity = (verbosity < static_cast<int>(CmdOptions::VERBOSITY::NO_INFO)) ? 
               static_cast<int>(CmdOptions::VERBOSITY::NO_INFO) : verbosity;
  verbosity = (verbosity > static_cast<int>(CmdOptions::VERBOSITY::ALL_INFO)) ? 
               static_cast<int>(CmdOptions::VERBOSITY::ALL_INFO) : verbosity;
  CmdOptions::verbosity = static_cast<CmdOptions::VERBOSITY>(verbosity);

  CmdOptions::configFilePath = parser.value("config");

  return true;
}

