#include "helper.h"
#include "GameAssembly.h"
#include "Language.h"

#include <distormx/distormx.h>
#include <cstddef>
#include <cstdio>

// ==========================================================================================
static HelperLib::Options CurrentOptions {};

// ==========================================================================================
// Hooks

void MainGameManager_Update(MainGameManager_o* mainGameManager)
{
	GameAssembly.MainGameManager_Update(mainGameManager);

	unsigned langCode = GameAssembly.Language_get_SystemLanguage();

	// Say remaining life time
	if (CurrentOptions.LifetimeMessageKey && GameAssembly.Input_GetKeyDown(CurrentOptions.LifetimeMessageKey))
	{
		PartnerCtrl_o* partnerL = GameAssembly.MainGameManager_GetPartnerCtrl(0);
		PartnerCtrl_o* partnerR = GameAssembly.MainGameManager_GetPartnerCtrl(1);
		if (partnerL && partnerR)
		{
			PlayerData_PartnerData_o* partnerData[] = {
				partnerL->fields.m_data->fields.m_partnerData,
				partnerR->fields.m_data->fields.m_partnerData
			};

			char buffer[64];

			for (int i = 0; i < 2; ++i)
			{
				int lifetime = static_cast<int>(partnerData[i]->fields.m_lifetime);
				int minutes = lifetime % 60;
				int hours = (lifetime / 60) % 24;
				int days = lifetime / 1440;

				int len;
				if (days > 1)
				{
					len = sprintf_s(buffer, GetString(langCode, LanguageStringIndex::DigimonDieDays), days, hours, minutes);
				}
				else
				{
					const char* format = GetString(langCode, (days == 1) ? LanguageStringIndex::DigimonDieDay : LanguageStringIndex::DigimonDieHours);
					len = sprintf_s(buffer, format, hours, minutes);
				}

				auto* msg = GameAssembly.String_CreateStringFromEncoding(buffer, len, GameAssembly.Encoding_get_UTF8());
				GameAssembly.uFieldPanel_StartDigimonMessage(i + 1, msg, 5.0f);
			}
		}
	}
}

// Can ExE always
bool PartnerCtrl_IsPossibleMiracle(PartnerCtrl_o* partner, bool isLose)
{
	if (CurrentOptions.UnlimitedExE)
	{
		auto* playerData = GameAssembly.StorageData_get_PlayerData();
		playerData->fields.m_isUseExe = false;
	}
	return GameAssembly.PartnerCtrl_IsPossibleMiracle(partner, isLose);
}

// ==========================================================================================
void HelperLib::Initialize(const Options& options)
{
	CurrentOptions = options;

	// Install hooks
	distormx_hook(reinterpret_cast<void**>(&GameAssembly.MainGameManager_Update.ptr), &MainGameManager_Update);
	distormx_hook(reinterpret_cast<void**>(&GameAssembly.PartnerCtrl_IsPossibleMiracle.ptr), &PartnerCtrl_IsPossibleMiracle);
}

void HelperLib::Release()
{
	// Remove hooks
	distormx_unhook(&GameAssembly.MainGameManager_Update.ptr);
	distormx_unhook(&GameAssembly.PartnerCtrl_IsPossibleMiracle.ptr);

	distormx_destroy();
}
