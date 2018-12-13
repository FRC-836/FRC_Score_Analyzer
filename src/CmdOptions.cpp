#include "CmdOptions.h"

const QMap<CmdOptions::VERBOSITY, QString> CmdOptions::VERBOSITY_STR_MAP = {
  {CmdOptions::VERBOSITY::NO_INFO,             "No Information"},
  {CmdOptions::VERBOSITY::ERRORS_ONLY,         "Errors Only"},
  {CmdOptions::VERBOSITY::ERRORS_AND_WARNINGS, "Errors and Warnings"},
  {CmdOptions::VERBOSITY::USER_INFO,           "User Information"},
  {CmdOptions::VERBOSITY::VERBOSE_INFO,        "Verbose Information"},
  {CmdOptions::VERBOSITY::DEBUG_INFO,          "Debug Information"},
  {CmdOptions::VERBOSITY::ALL_INFO,            "All Information"}
};

//defaults
CmdOptions::VERBOSITY CmdOptions::verbosity = CmdOptions::VERBOSITY::USER_INFO;
QString CmdOptions::configFilePath = "";

OutputManager& operator<<(OutputManager& out, CmdOptions::VERBOSITY toPrint)
{
  out << CmdOptions::VERBOSITY_STR_MAP.value(toPrint, "Invalid");
  return out;
}

