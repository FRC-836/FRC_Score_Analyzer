#include "ConfigParser.h"

extern OutputManager cout;

//private functions
Case_t ConfigParser::caseHandler(const QXmlStreamAttributes& attribs) const
{
  //TODO implement
}
ScoreModifier_t ConfigParser::scoreModHandler(const QXmlStreamAttributes attribs) const
{
  //TODO implement
}
ScoreMethod_t ConfigParser::scoreMethodHandler(const QXmlStreamAttributes attribs) const
{
  //TODO implement
}
ScoreType_t ConfigParser::scoreTypeHandler(const QXmlStreamAttributes attribs) const
{
  //TODO implement
}
GameConfig_t ConfigParser::gameConfigHandler(const QXmlStreamAttributes attribs) const
{
  //TODO implement
}

//constructors
ConfigParser::ConfigParser(const QString& configFilePath)
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: ConfigParser: constructing..." << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  if (configFilePath != "")
  {
    parse(configFilePath);
  } //end  if (configFilePath != "")
}

//public functions
bool ConfigParser::parse(const QString& configFilePath)
{
  switch (CmdOptions::verbosity)
  {
    case CmdOptions::VERBOSITY::DEBUG_INFO:
      cout << "DEBUG: ConfigParser: parse()" << endl;
    case CmdOptions::VERBOSITY::USER_INFO:
      cout << "INFO: ConfigParser: parsing config file: " << configFilePath << endl;
      break;
  } //end  switch (CmdOptions::verbosity)

  //check file validity
  QFile* xmlFile = new QFile(configFilePath);
  if (!xmlFile->exists())
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    {
      cout << "ERROR: ConfigParser: file " << configFilePath << " doesn't exist" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    return false;
  } //end  if (!xmlFile->exists())
  if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    {
      cout << "ERROR: ConfigParser: file couldn't be opened" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
  } //end  if (!xmlFile->open(QIODevice::ReadOnly | QIODevice::Text))

  //read the xml file
  QXmlStreamReader reader(xmlFile);
  while (!reader.atEnd())
  {
    reader.readNext();

    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
    {
      cout << "DEBUG: ConfigParser: token type: " << reader.tokenString() << endl;
      switch (reader.tokenType())
      {
        case QXmlStreamReader::TokenType::StartElement:
        case QXmlStreamReader::TokenType::EndElement:
          cout << "DEBUG: ConfigParser: name: " << reader.name().toString() << endl;
          break;
        case QXmlStreamReader::TokenType::Comment:
          cout << "DEBUG: ConfigParser: text: " << reader.text().toString() << endl;
          break;
      } //end  switch (reader.tokenType())
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
    {
      cout << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  } //end  while (!reader.atEnd())

  return false;
}

//getters
GameConfig_t ConfigParser::getConfig() const
{
  return m_config;
}
