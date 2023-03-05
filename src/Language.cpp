#include "Language.h"
#include "GameConstants.h"

#include <utility>

// ==========================================================================================
static const char* LangStrings_en[] = {
	"I'll die in %d days and %02d:%02d",
	"I'll die in 1 day and %02d:%02d",
	"I'll die in %02d:%02d"
};
static const char* LangStrings_pt[] = {
	"Vou morrer em %d dias e %02d:%02d",
	"Vou morrer em 1 dia e %02d:%02d",
	"Vou morrer em %02d:%02d"
};

static std::pair<DWNO::SystemLanguage::Enum, const char**> LangStringArray[] {
	{DWNO::SystemLanguage::English, LangStrings_en},
	{DWNO::SystemLanguage::Portuguese, LangStrings_pt}
};

// ==========================================================================================
const char* GetString(unsigned langCode, LanguageStringIndex stringIndex)
{
	for (const auto& pair : LangStringArray)
	{
		if (pair.first == langCode)
		{
			return pair.second[(unsigned)stringIndex];
		}
	}
	return LangStrings_en[(unsigned)stringIndex];
}
