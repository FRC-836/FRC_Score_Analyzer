#ifndef SCORE_ANALYZER_CMD_OPTIONS_H
#define SCORE_ANALYZER_CMD_OPTIONS_H

#include <string>

#include <qmap.h>

#include "OutputManager.h"

class CmdOptions
{
  public:
    enum class VERBOSITY
    {
      NO_INFO,
      ERRORS_ONLY,
      ERRORS_AND_WARNINGS,
      USER_INFO,
      DEBUG_INFO,
      ALL_INFO
    };
    static const QMap<VERBOSITY, std::string> VERBOSITY_STR_MAP;

    static VERBOSITY verbosity; //verbosity of output
    static std::string configFilePath; //location of the game config/description file
};

OutputManager& operator<<(OutputManager& out, CmdOptions::VERBOSITY toPrint);

#endif
