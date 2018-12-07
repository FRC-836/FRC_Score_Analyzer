#ifndef SCORE_ANALYZER_CONFIG_PARSER_H
#define SCORE_ANALYZER_CONFIG_PARSER_H

#include <qstringlist.h>

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
      } //end  enum Attributes
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
  } //end  namespace Case
} //end namespace GameConfig

class ConfigParser
{
  private:
  public:
};

#endif
