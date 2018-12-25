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
       << ", modifier type: " << GameConfig::Case::ModTypesStr[modType]
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
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: ConfigParser: caseHandler()" << endl;
    cout << "\tname: " << reader.name() << " (" << QString::number(reader.lineNumber()) << ")" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //ensure reader hasn't already encountered an error
  if (reader.hasError())
  {
    return Case_t();
  } //end  if (reader.hasError())

  //ensure reder is on the correct tag
  if (reader.name() != GameConfig::TagsStr[GameConfig::Tags::CASE])
  {
    reader.raiseError("Unknown tag " + reader.name() + " on line "+QString::number(reader.lineNumber()));
    return Case_t();
  } //end  if (reader.name() != GameConfig::TagsStr[GameConfig::Tags::CASE])

  //handle attributes
  Case_t toReturn;
  auto attribs = reader.attributes();

  //value (required)
  auto attrStr = GameConfig::Case::AttrStr[GameConfig::Case::Attributes::VALUE];
  auto conversionOk = false;
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + QString::number(reader.lineNumber()));
    return Case_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto value = attribs.value(attrStr).toInt(&conversionOk);
  if (!conversionOk)
  {
    reader.raiseError("Attrib " + attrStr + " must be an int (" + QString::number(reader.lineNumber()));
    return Case_t();
  } //end  if (!conversionOk)
  std::get<(int)CaseTuple::VALUE>(toReturn) = value;

  //score method (required)
  attrStr = GameConfig::Case::AttrStr[GameConfig::Case::Attributes::SCORE_METHOD];
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + QString::number(reader.lineNumber()));
    return Case_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto scoreMethodStr = attribs.value(attrStr).toString();
  std::get<(int)CaseTuple::SCORE_METOHD_LIST>(toReturn) = scoreMethodStr.split(", ");

  //modifier type (required)
  attrStr = GameConfig::Case::AttrStr[GameConfig::Case::Attributes::MODIFIER_TYPE];
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + QString::number(reader.lineNumber()));
    return Case_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  //auto type = ModTypesStr.keyattribs.value(attrStr).toString();
  auto type = GameConfig::Case::ModTypesStr.key(attribs.value(attrStr).toString(), 
                                                GameConfig::Case::ModifierTypes::INVALID);
  if (type == GameConfig::Case::ModifierTypes::INVALID)
  {
    reader.raiseError("Invalid case type " + GameConfig::Case::ModTypesStr[type] +
                      " provided on line " + QString::number(reader.lineNumber()));
    return Case_t();
  } //end  if (type == GameConfig::Case::ModifierTypes::INVALID)

  //amount (required)
  attrStr = GameConfig::Case::AttrStr[GameConfig::Case::Attributes::AMOUNT];
  conversionOk = false;
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + QString::number(reader.lineNumber()));
    return Case_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto amount = attribs.value(attrStr).toInt(&conversionOk);
  if (!conversionOk)
  {
    reader.raiseError("Attrib " + attrStr + " must be an int (" + QString::number(reader.lineNumber()));
    return Case_t();
  } //end  if (!conversionOk)
  std::get<(int)CaseTuple::AMOUNT>(toReturn) = amount;

  //max units
  attrStr = GameConfig::Case::AttrStr[GameConfig::Case::Attributes::MAX_UNITS];
  conversionOk = false;
  auto maxUnits = -1;
  if (attribs.hasAttribute(attrStr))
  {
    maxUnits = attribs.value(attrStr).toInt(&conversionOk);
    if (!conversionOk)
    {
      reader.raiseError("Attrib " + attrStr + " must be an int (" + QString::number(reader.lineNumber()));
      return Case_t();
    } //end  if (!conversionOk)
  } //end  if (attribs.hasAttribute(attrStr))
  std::get<(int)CaseTuple::MAX_UNITS>(toReturn) = maxUnits;

  return toReturn;
}
ScoreModifier_t ConfigParser::scoreModHandler(QXmlStreamReader& reader) const
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: ConfigParser: scoreModHandler()" << endl;
    cout << "\tname: " << reader.name() << " (" << QString::number(reader.lineNumber()) << ")" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //ensure reader hasn't already encountered an error
  if (reader.hasError())
  {
    return ScoreModifier_t();
  } //end  if (reader.hasError())

  //ensure reder is on the correct tag
  if (reader.name() != GameConfig::TagsStr[GameConfig::Tags::SCORE_MODIFIER])
  {
    reader.raiseError("Unknown tag " + reader.name() + " on line "+QString::number(reader.lineNumber()));
    return ScoreModifier_t();
  } //end  if (reader.name() != GameConfig::TagsStr[GameConfig::Tags::GAME])

  //handle attributes
  ScoreModifier_t toReturn;
  auto attribs = reader.attributes();

  //name (required)
  auto attrStr = GameConfig::ScoreModifier::AttrStr[GameConfig::ScoreModifier::Attributes::NAME];
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + QString::number(reader.lineNumber()));
    return ScoreModifier_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto name = attribs.value(attrStr).toString();
  std::get<(int)ScoreModifierTuple::NAME>(toReturn) = name;

  //resource (required)
  attrStr = GameConfig::ScoreModifier::AttrStr[GameConfig::ScoreModifier::Attributes::RESOURCE];
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + QString::number(reader.lineNumber()));
    return ScoreModifier_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto resource = attribs.value(attrStr).toString();
  std::get<(int)ScoreModifierTuple::RESOURCE>(toReturn) = resource;

  //type
  attrStr = GameConfig::ScoreModifier::AttrStr[GameConfig::ScoreModifier::Attributes::TYPE];
  auto type = (attribs.hasAttribute(attrStr) ? attribs.value(attrStr).toString() : "");
  std::get<(int)ScoreModifierTuple::TYPE>(toReturn) = type;

  //parse sub tags
  while (!(reader.readNext() == QXmlStreamReader::TokenType::EndElement && 
          reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_MODIFIER]))
  {
    if (reader.tokenType() == QXmlStreamReader::TokenType::StartElement)
    {
      if (reader.name() == GameConfig::TagsStr[GameConfig::Tags::CASE])
      {
        auto caseVal = caseHandler(reader);
        if (reader.hasError())
        {
          return ScoreModifier_t();
        } //end  if (reader.hasError())
        std::get<(int)ScoreModifierTuple::CASE_LIST>(toReturn).push_back(caseVal);
      } //end if (reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_TYPE])
      else
      {
        reader.raiseError("Unexpected tag: " + reader.name() + " line " + QString::number(reader.lineNumber()));
        return ScoreModifier_t();
      } //end else
    } //end  if (reader.tokenType() == QXmlStreamReader::TokenType::StartElement)
  } //end  while ((reader.readNext() == QXmlStreamReader::TokenType::EndElement && 

  return toReturn;
}
ScoreMethod_t ConfigParser::scoreMethodHandler(QXmlStreamReader& reader) const
{
  //TODO implement
  return ScoreMethod_t();
}
ScoreType_t ConfigParser::scoreTypeHandler(QXmlStreamReader& reader) const
{
  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)
  {
    cout << "DEBUG: ConfigParser: typeHandler()" << endl;
    cout << "\tname: " << reader.name() << " (" << QString::number(reader.lineNumber()) << ")" << endl;
  } //end  if (CmdOptions::verbosity >= CmdOptions::VERBOSITY::DEBUG_INFO)

  //ensure reader hasn't already encountered an error
  if (reader.hasError())
  {
    return ScoreType_t();
  } //end  if (reader.hasError())

  //ensure reder is on the correct tag
  if (reader.name() != GameConfig::TagsStr[GameConfig::Tags::SCORE_TYPE])
  {
    reader.raiseError("Unknown tag " + reader.name() + " on line "+QString::number(reader.lineNumber()));
    return ScoreType_t();
  } //end  if (reader.name() != GameConfig::TagsStr[GameConfig::Tags::GAME])

  //handle attributes
  ScoreType_t toReturn;
  auto attribs = reader.attributes();

  //name (required)
  auto attrStr = GameConfig::ScoreType::AttrStr[GameConfig::ScoreType::Attributes::NAME];
  auto conversionOk = false;
  if (!attribs.hasAttribute(attrStr))
  {
    reader.raiseError("Required attribute " + attrStr + " not found line " + QString::number(reader.lineNumber()));
    return ScoreType_t();
  } //end  if (!attribs.hasAttribute(attrStr))
  auto name = attribs.value(attrStr).toString();
  std::get<(int)ScoreTypeTuple::NAME>(toReturn) = name;

  //max (semi-required: only one of the 3 max attributes are required)
  attrStr = GameConfig::ScoreType::AttrStr[GameConfig::ScoreType::Attributes::MAX];
  conversionOk = false;
  auto max = -1;
  if (attribs.hasAttribute(attrStr))
  {
    max = attribs.value(attrStr).toInt(&conversionOk);
    if (!conversionOk)
    {
      reader.raiseError("Attrib " + attrStr + " must be an int (" + QString::number(reader.lineNumber()));
      return ScoreType_t();
    } //end  if (!conversionOk)
  } //end  if (attribs.hasAttribute(attrStr))
  std::get<(int)ScoreTypeTuple::MAX>(toReturn) = max;

  //max per alliance (semi-required: only one of the 3 max attributes are required)
  attrStr = GameConfig::ScoreType::AttrStr[GameConfig::ScoreType::Attributes::MAX_PER_ALLIANCE];
  conversionOk = false;
  auto maxPerAlliance = -1;
  if (attribs.hasAttribute(attrStr))
  {
    maxPerAlliance = attribs.value(attrStr).toInt(&conversionOk);
    if (!conversionOk)
    {
      reader.raiseError("Attrib " + attrStr + " must be an int (" + QString::number(reader.lineNumber()));
      return ScoreType_t();
    } //end  if (!conversionOk)
  } //end  if (attribs.hasAttribute(attrStr))
  std::get<(int)ScoreTypeTuple::MAX_PER_ALLIANCE>(toReturn) = maxPerAlliance;

  //max per team (semi-required: only one of the 3 max attributes are required)
  attrStr = GameConfig::ScoreType::AttrStr[GameConfig::ScoreType::Attributes::MAX_PER_TEAM];
  conversionOk = false;
  auto maxPerTeam = -1;
  if (attribs.hasAttribute(attrStr))
  {
    maxPerTeam = attribs.value(attrStr).toInt(&conversionOk);
    if (!conversionOk)
    {
      reader.raiseError("Attrib " + attrStr + " must be an int (" + QString::number(reader.lineNumber()));
      return ScoreType_t();
    } //end  if (!conversionOk)
  } //end  if (attribs.hasAttribute(attrStr))
  std::get<(int)ScoreTypeTuple::MAX_PER_TEAM>(toReturn) = maxPerTeam;

  //check if at least one max attribute was provided
  if (max == -1 && maxPerAlliance == -1 && maxPerTeam == -1)
  {
    auto attrStrs = GameConfig::ScoreType::AttrStr;
    reader.raiseError("There must be at least one max attribute provided: " + 
                      QString::number(reader.lineNumber()) + "\n" + 
                      "valid max attributes are: " + 
                      attrStrs[GameConfig::ScoreType::Attributes::MAX_PER_ALLIANCE]+", "+ 
                      attrStrs[GameConfig::ScoreType::Attributes::MAX] + ", " +
                      attrStrs[GameConfig::ScoreType::Attributes::MAX_PER_TEAM]);
  } //end  if (max == -1 && maxPerAlliance == -1 && maxPerTeam == -1)

  //type
  attrStr = GameConfig::ScoreType::AttrStr[GameConfig::ScoreType::Attributes::TYPE];
  auto type = (attribs.hasAttribute(attrStr) ? attribs.value(attrStr).toString() : "");
  std::get<(int)ScoreTypeTuple::TYPE>(toReturn) = type;

  //unit
  attrStr = GameConfig::ScoreType::AttrStr[GameConfig::ScoreType::Attributes::UNIT];
  auto unit = (attribs.hasAttribute(attrStr) ? attribs.value(attrStr).toString() : "");
  std::get<(int)ScoreTypeTuple::UNIT>(toReturn) = unit;

  //subset
  attrStr = GameConfig::ScoreType::AttrStr[GameConfig::ScoreType::Attributes::SUBSET];
  auto subset = (attribs.hasAttribute(attrStr) ? attribs.value(attrStr).toString() : "");
  std::get<(int)ScoreTypeTuple::SUBSET>(toReturn) = subset;

  return toReturn;
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
  while (!(reader.readNext() == QXmlStreamReader::TokenType::EndElement &&
         reader.name() == GameConfig::TagsStr[GameConfig::Tags::GAME]))
  {
    if (reader.tokenType() == QXmlStreamReader::TokenType::StartElement)
    {
      if (reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_TYPE])
      {
        auto scoreType = scoreTypeHandler(reader);
        if (reader.hasError())
        {
          return GameConfig_t();
        } //end  if (reader.hasError())
        std::get<(int)GameConfigTuple::SCORE_TYPE_LIST>(toReturn).insert(std::get<(int)ScoreTypeTuple::NAME>(scoreType), scoreType);;
      } //end if (reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_TYPE])
      else if (reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_METHOD])
      {
        auto scoreMethod = scoreMethodHandler(reader);
        if (reader.hasError())
        {
          return GameConfig_t();
        } //end  if (reader.hasError())
        std::get<(int)GameConfigTuple::SCORE_METHOD_LIST>(toReturn).insert(std::get<(int)ScoreMethodTuple::NAME>(scoreMethod), scoreMethod);
      }//end else if(reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_METHOD])
      else if (reader.name() == GameConfig::TagsStr[GameConfig::Tags::SCORE_MODIFIER])
      {
        auto scoreMod = scoreModHandler(reader);
        if (reader.hasError())
        {
          return GameConfig_t();
        } //end  if (reader.hasError())
        std::get<(int)GameConfigTuple::SCORE_MODIFIER_LIST>(toReturn).insert(std::get<(int)ScoreModifierTuple::NAME>(scoreMod), scoreMod);
      }//end else if(reader.name()==GameConfig::TagsStr[GameConfig::Tags::SCORE_MODIFIER])
      else
      {
        reader.raiseError("Unexpected tag: " + reader.name() + " line " + QString::number(reader.lineNumber()));
        return GameConfig_t();
      } //end else
    } //end  if (reader.tokenType() == QXmlStreamReader::TokenType::StartElement)
  } //end  while (reader.readNext() != QXmlStreamReader::TokenType::EndDocument)

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
      cout << "ERROR: ConfigParser: couldn't process the config file" << endl;
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
