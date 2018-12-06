#include <qapplication.h>
#include <qcommandlineparser.h>

#include "MainWindow.h"

bool parseCmd(QCommandLineParser& parser);

int main(int argc, char** argv)
{
  QApplication app(argc, argv);

  QCommandLineParser parser;
  if (!parseCmd(parser))
  {
    parser.showHelp(1);
  } //end  if (!parseCmd())

  MainWindow mainWindow;
  
  mainWindow.show();

  return app.exec();
}

bool parseCmd(QCommandLineParser& parser)
{
  //TODO implementation
  return false;
}

