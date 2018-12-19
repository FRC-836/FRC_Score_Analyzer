#include "ConfigParser.h"

extern OutputManager cout;

//print functions
void printGameConfig(const GameConfig_t& toPrint)
{
  cout << "Game Config: name: " << std::get<(int)GameConfigTuple::NAME>(toPrint)
       << ", year: " << std::get<(int)GameConfigTuple::YEAR>(toPrint)
       << ", match length: " << std::get<(int)GameConfigTuple::MATCH_LENGTH>(toPrint)
       << ", auto length: " << std::get<(int)GameConfigTuple::AUTO_LENGTH>(toPrint)
       << ", end game length: " << std::get<(int)GameConfigTuple::END_GAME_LENGTH>(toPrint)
       << ", file version: " << std::get<(int)GameConfigTuple::FILE_VERSION>(toPrint)
       << ", program: " << std::get<(int)GameConfigTuple::PROGRAM>(toPrint) << endl;
  cout << "# Score Types: " << std::get<(int)GameConfigTuple::SCORE_TYPE_LIST>(toPrint).size() << endl;
  for (auto scoreType : std::get<(int)GameConfigTuple::SCORE_TYPE_LIST>(toPrint))
  {
    printScoreType(scoreType);
  } //end  for (auto scoreType : std::get<(int)GameConfigTuple::SCORE_TYPE_LIST>(toPrint))
  cout << "# Score Methods: " << std::get<(int)GameConfigTuple::SCORE_METHOD_LIST>(toPrint).size() << endl;
  for (auto scoreMethod : std::get<(int)GameConfigTuple::SCORE_METHOD_LIST>(toPrint))
  {
    printScoreMethod(scoreMethod);
  }//end for(auto scoreMethod : std::get<(int)GameConfigTuple::SCORE_METHOD_LIST>(toPrint))
  cout << "# Score Mods: " << std::get<(int)GameConfigTuple::SCORE_MODIFIER_LIST>(toPrint).size() << endl;
  for (auto scoreMod : std::get<(int)GameConfigTuple::SCORE_MODIFIER_LIST>(toPrint))
  {
    printScoreModifier(scoreMod);
  }//end for(auto ScoreMod : std::get<(int)GameConfigTuple::SCORE_MODIFIER_LIST>(toPrint))
}
void printScoreType(const ScoreType_t& toPrint, bool useTabs)
{
  auto tabs = (useTabs ? "\t" : "");

  cout << tabs << "Score Type: Name: " << std::get<(int)ScoreTypeTuple::NAME>(toPrint)
       << ", max: " << std::get<(int)ScoreTypeTuple::MAX>(toPrint)
       << ", max per alliance: " <<std::get<(int)ScoreTypeTuple::MAX_PER_ALLIANCE>(toPrint)
       << ", max per team: " << std::get<(int)ScoreTypeTuple::MAX_PER_TEAM>(toPrint)
       << ", type: " << std::get<(int)ScoreTypeTuple::TYPE>(toPrint)
       << ", unit: " << std::get<(int)ScoreTypeTuple::UNIT>(toPrint)
       << ", subset: " << std::get<(int)ScoreTypeTuple::SUBSET>(toPrint) << endl;
}
void printScoreMethod(const ScoreMethod_t& toPrint, bool useTabs)
{
  auto tabs = (useTabs ? "\t" : "");

  cout << tabs << "Score Method: Name: " << std::get<(int)ScoreMethodTuple::NAME>(toPrint)
       << ", type: " << std::get<(int)ScoreMethodTuple::TYPE>(toPrint)
       << ", auto score: " << std::get<(int)ScoreMethodTuple::AUTO_SCORE>(toPrint)
       << ", tele score: " << std::get<(int)ScoreMethodTuple::TELE_SCORE>(toPrint)
       << ", end score: " << std::get<(int)ScoreMethodTuple::END_SCORE>(toPrint) << endl;
}
void printScoreModifier(const ScoreModifier_t& toPrint, bool useTabs)
{
  auto tabs = (useTabs ? "\t" : "");

  cout << tabs << "Score Mod: name: " << std::get<(int)ScoreModifierTuple::NAME>(toPrint)
       << ", type: " << std::get<(int)ScoreModifierTuple::TYPE>(toPrint)
       << ", resource: " << std::get<(int)ScoreModifierTuple::RESOURCE>(toPrint) << endl;

  auto caseList = std::get<(int)ScoreModifierTuple::CASE_LIST>(toPrint);
  cout << tabs << "# cases: " << caseList.size() << endl;
  for (auto caseVal : caseList)
  {
    printCase(caseVal);
  } //end  for (auto caseVal : std::get<(int)ScoreModifierTuple::CASE_LIST>(toPrint))
}
void printCase(const Case_t& toPrint, bool useTabs)
{
  auto tabs = (useTabs ? "\t\t" : "");

  auto modType = std::get<(int)CaseTuple::MODIFIER_TYPE>(toPrint);

  cout << tabs << "Case: value: " << std::get<(int)CaseTuple::VALUE>(toPrint)
       << ", modifier type: " << GameConfig::Case::ModTypesStr[(int)modType]
       << ", amount: " << std::get<(int)CaseTuple::AMOUNT>(toPrint)
       << ", max units: " << std::get<(int)CaseTuple::MAX_UNITS>(toPrint) << endl;

  auto scoreMethods = std::get<(int)CaseTuple::SCORE_METOHD_LIST>(toPrint);
  cout << tabs << "# score methods affected: " << scoreMethods.size() << endl;
  for (auto scoreMethod : scoreMethods)
  {
    cout << tabs << "\t" << scoreMethod << endl;
  } //end  for (auto scoreMethod : std::get<(int)CaseTuple::SCORE_METOHD_LIST>(toPrint))
}

//private functions
Case_t ConfigParser::caseHandler(QXmlStreamReader& reader) const
{
  //TODO implement
  return Case_t();
}
ScoreModifier_t ConfigParser::scoreModHandler(QXmlStreamReader& reader) const
{
  //TODO implement
  return ScoreModifier_t();
}
ScoreMethod_t ConfigParser::scoreMethodHandler(QXmlStreamReader& reader) const
{
  //TODO implement
  return ScoreMethod_t();
}
ScoreType_t ConfigParser::scoreTypeHandler(QXmlStreamReader& reader) const
{
  //TODO implement
  return ScoreType_t();
}
GameConfig_t ConfigParser::gameConfigHandler(QXmlStreamReader& reader) const
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: ConfigParser: gameConfigHandler()" << endl;
    cout << "\tname: " << reader.name() << " (" << QString::number(reader.lineNumber()) << ")" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //ensure reader hasn't already encountered an error
  if (reader.hasError())
  {
    return GameConfig_t();
  } //end  if (reader.hasError())

  //ensure reder is on the correct tag
  if (reader.name() != GameConfig::TagsStr[GameConfig::Tags::GAME])
  {
    reader.raiseError("Unknown tag " + reader.name() + " on line "+QString::number(reader.lineNumber()));
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
    reader.raiseError("Required attribute " + attrStr + " not found line " + QString::number(reader.lineNumber()));
    return GameConfig_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto matchLength = attribs.value(attrStr).toInt(&conversionOk);
  if (!conversionOk)
  {
    reader.raiseError("Attrib " + attrStr + " must be an int (" + QString::number(reader.lineNumber()));
    return GameConfig_t();
  } //end  if (!conversionOk)
  std::get<(int)GameConfigTuple::MATCH_LENGTH>(toReturn) = matchLength;

  //auto length (required)
  attrStr = GameConfig::Game::AttrStr[GameConfig::Game::Attributes::AUTO_LENGTH];
  conversionOk = false;
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + QString::number(reader.lineNumber()));
    return GameConfig_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto autoLength = attribs.value(attrStr).toInt(&conversionOk);
  if (!conversionOk)
  {
    reader.raiseError("Attrib " + attrStr + " must be an int (" + QString::number(reader.lineNumber()));
    return GameConfig_t();
  } //end  if (!conversionOk)
  std::get<(int)GameConfigTuple::AUTO_LENGTH>(toReturn) = autoLength;

  //end game length (required)
  attrStr = GameConfig::Game::AttrStr[GameConfig::Game::Attributes::END_GAME_LENGTH];
  conversionOk = false;
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + QString::number(reader.lineNumber()));
    return GameConfig_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto endGameLength = attribs.value(attrStr).toInt(&conversionOk);
  if (!conversionOk)
  {
    reader.raiseError("Attrib " + attrStr + " must be an int (" + QString::number(reader.lineNumber()));
    return GameConfig_t();
  } //end  if (!conversionOk)
  std::get<(int)GameConfigTuple::END_GAME_LENGTH>(toReturn) = endGameLength;

  //file version (required)
  attrStr = GameConfig::Game::AttrStr[GameConfig::Game::Attributes::FILE_VERSION];
  conversionOk = false;
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + QString::number(reader.lineNumber()));
    return GameConfig_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto fileVersion = attribs.value(attrStr).toString();
  std::get<(int)GameConfigTuple::FILE_VERSION>(toReturn) = fileVersion;

  //game name
  attrStr = GameConfig::Game::AttrStr[GameConfig::Game::Attributes::NAME];
  auto gameName = (attribs.hasAttribute(attrStr) ? attribs.value(attrStr).toString() : "");
  std::get<(int)GameConfigTuple::NAME>(toReturn) = gameName;

  //game year
  attrStr = GameConfig::Game::AttrStr[GameConfig::Game::Attributes::YEAR];
  conversionOk = false;
  auto gameYear = attribs.value(attrStr).toInt(&conversionOk);
  if (!conversionOk)
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_AND_WARNINGS)
    {
      cout << "WARNING: ConfigParser: attrib " << attrStr << " must be an int on line" 
           << reader.lineNumber() << endl;
      cout << "\tSetting value to 0" << endl;
    } //end  if (CmdOptions::configFilePath >= CmdOptions::VERBOSITY::ERRORS_AND_WARNINGS)
    gameYear = 0;
  } //end  if (!conversionOk)
  std::get<(int)GameConfigTuple::YEAR>(toReturn) = gameYear;

  //program
  attrStr = GameConfig::Game::AttrStr[GameConfig::Game::Attributes::PROGRAM];
  auto program = (attribs.hasAttribute(attrStr) ? attribs.value(attrStr).toString() : "");
  std::get<(int)GameConfigTuple::PROGRAM>(toReturn) = program;

  //parse sub tags
  /*
  while (reader.readNext() != QXmlStreamReader::TokenType::EndElement)
  {
    if (reader.tokenType() == QXmlStreamReader::TokenType::StartElement)
    {
      if (reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_TYPE])
      {
        auto scoreType = scoreTypeHandler(reader);
        if (!reader.hasError())
        {
          return GameConfig_t();
        } //end  if (!reader.hasError())
        std::get<(int)GameConfigTuple::SCORE_TYPE_LIST>(toReturn).push_back(scoreType);
      } //end if (reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_TYPE])
      else if (reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_METHOD])
      {
        auto scoreMethod = scoreMethodHandler(reader);
        if (!reader.hasError())
        {
          return GameConfig_t();
        } //end  if (!reader.hasError())
        std::get<(int)GameConfigTuple::SCORE_METHOD_LIST>(toReturn).push_back(scoreMethod);
      }//end else if(reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_METHOD])
      else if (reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_MODIFIER])
      {
        auto scoreMod = scoreModHandler(reader);
        if (!reader.hasError())
        {
          return GameConfig_t();
        } //end  if (!reader.hasError())
        std::get<(int)GameConfigTuple::SCORE_MODIFIER_LIST>(toReturn).push_back(scoreMod);
      }//end else if(reader.name()==GameConfig::TagsStr[GameConfig::Tags::SCORE_MODIFIER])
      else
      {
        reader.raiseError("Unexpected tag: " + reader.name() + " line " + QString::number(reader.lineNumber()));
        return GameConfig_t();
      } //end else
    } //end  if (reader.tokenType() == QXmlStreamReader::TokenType::StartElement)
  } //end  while (reader.readNext() != QXmlStreamReader::TokenType::EndElement)
  */

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
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: ConfigParser: parse()" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::USER_INFO)
  {
    cout << "INFO: ConfigParser: parsing config file: " << configFilePath << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::USER_INFO)

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
  while (reader.readNext() != QXmlStreamReader::TokenType::StartElement)
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
    {
      cout << "DEBUG: ConfigParser: name: " << reader.name() << endl;
      cout << "DEBUG: ConfigParser: text: " << reader.text() << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

    //check for end of document or error
    if (reader.tokenType() == QXmlStreamReader::TokenType::EndDocument || 
        reader.isEndDocument())
    {
      if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
      {
        cout << "ERROR: ConfigParser: Unexpected end of document" << endl;
      } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    } //end  if (TokenType == END_DOCUMENT || reader.isEndDocument())
  } //end  while (reader.readNext() != QXmlStreamReader::TokenType::StartElement)

  m_config = gameConfigHandler(reader);

  //ensure there was no error while reading the file
  if (reader.hasError())
  {
    if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    {
      cout << "ERROR: ConfigParser: couldn't processing the config file" << endl;
      cout << '\t' << reader.errorString() << endl;
    } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::ERRORS_ONLY)
    return false;
  } //end  if (reader.hasError)

  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: ConfigParser: read the following configuration from " 
         << configFilePath << endl;
    printGameConfig(m_config);
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  return true;
}

//getters
GameConfig_t ConfigParser::getConfig() const
{
  return m_config;
}
