#pragma once

enum class LanguageStringIndex : unsigned
{
	DigimonDieDays,
	DigimonDieDay,
	DigimonDieHours
};

const char* GetString(unsigned langCode, LanguageStringIndex stringIndex);
