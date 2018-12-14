#include "ConfigParser.h"

extern OutputManager cout;

//private functions
Case_t ConfigParser::caseHandler(QXmlStreamReader& reader) const
{
  //TODO implement
}
ScoreModifier_t ConfigParser::scoreModHandler(QXmlStreamReader& reader) const
{
  //TODO implement
}
ScoreMethod_t ConfigParser::scoreMethodHandler(QXmlStreamReader& reader) const
{
  //TODO implement
}
ScoreType_t ConfigParser::scoreTypeHandler(QXmlStreamReader& reader) const
{
  //TODO implement
}
GameConfig_t ConfigParser::gameConfigHandler(QXmlStreamReader& reader) const
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: ConfigParser: gameConfigHandler()" << endl;
    cout << "\tname: " << reader.name() << " (" << reader.lineNumber() << ")" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //ensure reader hasn't already encountered an error
  if (reader.hasError())
  {
    return GameConfig_t();
  } //end  if (reader.hasError())

  //ensure reder is on the correct tag
  if (reader.name() != GameConfig::TagsStr[GameConfig::Tags::GAME])
  {
    reader.raiseError("Unknown tag " + reader.name() + " on line "+reader.lineNumber());
    return GameConfig_t();
  } //end  if (reader.name() != GameConfig::TagsStr[GameConfig::Tags::GAME])

  //handle attributes
  GameConfig_t toReturn;
  auto attribs = reader.attributes();

  //match length (required)
  auto attrStr = GameConfig::Game::AttrStr[GameConfig::Game::Attributes::MATCH_LENGTH];
  auto conversionOk = false;
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + reader.lineNumber());
    return GameConfig_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto matchLength = attribs.value(attrStr).toInt(&conversionOk);
  if (!conversionOk)
  {
    reader.raiseError("Attrib " + attrStr + " must be an int (" + reader.lineNumber());
    return GameConfig_t();
  } //end  if (!conversionOk)
  std::get<(int)GameConfigTuple::MATCH_LENGTH>(toReturn) = matchLength;

  //auto length (required)
  attrStr = GameConfig::Game::AttrStr[GameConfig::Game::Attributes::AUTO_LENGTH];
  conversionOk = false;
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + reader.lineNumber());
    return GameConfig_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto autoLength = attribs.value(attrStr).toInt(&conversionOk);
  if (!conversionOk)
  {
    reader.raiseError("Attrib " + attrStr + " must be an int (" + reader.lineNumber());
    return GameConfig_t();
  } //end  if (!conversionOk)
  std::get<(int)GameConfigTuple::AUTO_LENGTH>(toReturn) = autoLength;

  //end game length (required)
  attrStr = GameConfig::Game::AttrStr[GameConfig::Game::Attributes::END_GAME_LENGTH];
  conversionOk = false;
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + reader.lineNumber());
    return GameConfig_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto endGameLength = attribs.value(attrStr).toInt(&conversionOk);
  if (!conversionOk)
  {
    reader.raiseError("Attrib " + attrStr + " must be an int (" + reader.lineNumber());
    return GameConfig_t();
  } //end  if (!conversionOk)
  std::get<(int)GameConfigTuple::END_GAME_LENGTH>(toReturn) = endGameLength;

  //file version (required)
  attrStr = GameConfig::Game::AttrStr[GameConfig::Game::Attributes::FILE_VERSION];
  conversionOk = false;
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + reader.lineNumber());
    return GameConfig_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto fileVersion = attribs.value(attrStr).toString();
  std::get<(int)GameConfigTuple::FILE_VERSION>(toReturn) = fileVersion;

  return toReturn;
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
    default:
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
  if (reader.readNextStartElement() || reader.atEnd())
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    {
      cout << "ERROR: ConfigParser: unexpected end of document reached" << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    return false;
  } //end  if (reader.readNextStartElement() || reader.atEnd())

  m_config = gameConfigHandler(reader);

  if (reader.hasError())
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    {
      cout << "ERROR: ConfigParser: couldn't processing the config file" << endl;
      cout << '\t' << reader.errorString() << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    return false;
  } //end  if (reader.hasError)
  return true;
}

//getters
GameConfig_t ConfigParser::getConfig() const
{
  return m_config;
}
