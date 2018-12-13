#ifndef SCORE_ANALYZER_CONFIG_PARSER_H
#define SCORE_ANALYZER_CONFIG_PARSER_H

#include <tuple>

#include <qstringlist.h>
#include <qstring.h>
#include <qvector.h>
#include <QXmlStreamReader>
#include <qfile.h>

#include "CmdOptions.h"
#include "OutputManager.h"

//xml tags and attributes helper
namespace GameConfig
{
  namespace Tags
  {
    enum Tags
    {
      GAME,
      SCORE_TYPE,
      SCORE_METHOD,
      SCORE_MODIFIER,
      CASE
    }; //end  enum Tags
  } //end  namespace Tags
  static QStringList TagsStr = {
    "game",
    "scoreType",
    "scoreMethod",
    "scoreModifier",
    "case"
  };

  namespace Game
  {
    namespace Attributes
    {
      enum Attributes
      {
        NAME,
        YEAR,
        MATCH_LENGTH,
        AUTO_LENGTH,
        END_GAME_LENGTH,
        FILE_VERSION,
        PROGRAM
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "name",
      "year",
      "matchLength",
      "autoLength",
      "endGameLength",
      "fileVersion",
      "program"
    };
  } //end  namespace GAME

  namespace ScoreType
  {
    namespace Attributes
    {
      enum Attributes
      {
        NAME,
        MAX,
        MAX_PER_ALLIANCE,
        MAX_PER_TEAM,
        TYPE,
        UNIT,
        SUBSET
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "name",
      "max",
      "maxPerAlliance",
      "maxPerTeam",
      "type",
      "unit",
      "subset"
    };
  } //end  namespace ScoreType

  namespace ScoreMethod
  {
    namespace Attributes
    {
      enum Attributes
      {
        NAME,
        TYPE,
        AUTO_SCORE,
        TELE_SCORE,
        END_SCORE,
      }; //end  enum Attributes
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "name",
      "type",
      "autoScore",
      "teleScore",
      "endScore"
    };
  } //end  namespace ScoreMethod

  namespace ScoreModifier
  {
    namespace Attributes
    {
      enum Attributes
      {
        NAME,
        TYPE,
        RESOURCE
      };
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "name",
      "type",
      "resource"
    };
  } //end  namespace ScoreModifier

  namespace Case
  {
    namespace Attributes
    {
      enum Attributes
      {
        VALUE,
        SCORE_METHOD,
        MODIFIER_TYPE,
        AMOUNT,
        MAX_UNITS
      };
    } //end  namespace Attributes
    static QStringList AttrStr = {
      "value",
      "scoreMethod",
      "modifierType",
      "amount",
      "maxUnits"
    };
    enum class ModifierTypes
    {
      SCALE
    };
  } //end  namespace Case
} //end namespace GameConfig

using Case_t = std::tuple<int,QStringList,GameConfig::Case::ModifierTypes,double,double>;
enum class CaseTuple
{
  VALUE,
  SCORE_METOHD_LIST,
  MODIFIER_TYPE,
  AMOUNT,
  MAX_UNITS
};
using ScoreModifier_t = std::tuple<QString, QString, QString, QVector<Case_t>>;
enum class ScoreModifierTuple
{
  NAME,
  TYPE,
  RESOURCE,
  CASE_LIST
};
using ScoreMethod_t = std::tuple<QString, QString, double, double, double>;
enum class ScoreMethodTuple
{
  NAME,
  TYPE,
  AUTO_SCORE,
  TELE_SCORE,
  END_SCORE
};
using ScoreType_t = std::tuple<QString,double,double,double,QString,QString,QString>;
enum class ScoreTypeTuple
{
  NAME,
  MAX,
  MAX_PER_ALLIANCE,
  MAX_PER_TEAM,
  TYPE,
  UNIT,
  SUBSET
};
using GameConfig_t = std::tuple<QString, int, int, int, int, QString, QString,
                                QVector<ScoreType_t>, QVector<ScoreMethod_t>, 
                                QVector<ScoreModifier_t>>;
enum class GameConfigTuple
{
  NAME,
  YEAR,
  MATCH_LENGTH,
  AUTO_LENGTH,
  END_GAME_LENGTH,
  FILE_VERSION,
  PROGRAM,
  SCORE_TYPE_LIST,
  SCORE_METHOD_LIST,
  SCORE_MODIFIER_LIST
};

class ConfigParser
{
  private:
    //member variables
    QString m_path;
    GameConfig_t m_config;

    //private functions
    Case_t caseHandler(const QXmlStreamAttributes& attribs) const;
    ScoreModifier_t scoreModHandler(const QXmlStreamAttributes attribs) const;
    ScoreMethod_t scoreMethodHandler(const QXmlStreamAttributes attribs) const;
    ScoreType_t scoreTypeHandler(const QXmlStreamAttributes attribs) const;
    GameConfig_t gameConfigHandler(const QXmlStreamAttributes attribs) const;

  public:
    //constructors
    /**
     * Constructor that takes in the file path where the game config file is
     * @param configFilePath: config file to parse on construction if provided
     */
    ConfigParser(const QString& configFilePath = "");

    //public functions
    /**
     * Parse the config file to generate the Game Config information
     * #param configFilePath: path to the game config XML file to parse
     * @return: true if the file was sucessfully parsed, false otherwise
     */
    bool parse(const QString& configFilePath);

    //getters
    /**
     * Get the most recently parsed config data
     * @return: Config data from the most recently parse game config XML file
     */
    GameConfig_t getConfig() const;
};

#endif
