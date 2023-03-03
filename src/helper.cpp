#include "helper.h"
#include "game.h"

#include <distormx/distormx.h>

#include <cstddef>
#include <string>

// ==========================================================================================
// Hooks

void MainGameManager_Update(MainGameManager_o* mainGameManager)
{
	GameAssembly.MainGameManager_Update(mainGameManager);

	// Say remaining life time
	if (GameAssembly.Input_GetKeyDown(UnityEngine::KeyCode::F1))
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
				float lifetime = partnerData[i]->fields.m_lifetime;

				int minutes = static_cast<int>(fmodf(lifetime, 60.f));
				int hours = static_cast<int>(fmodf(lifetime / 60.f, 24.f));
				int days = static_cast<int>(floorf(lifetime / 1440.f));
				
				int len;
				if (days > 0)
				{
					len = sprintf_s(buffer, "I'll die in %02d days and %02d:%02d", days, hours, minutes);
				}
				else
				{
					len = sprintf_s(buffer, "I'll die in %02d:%02d", hours, minutes);
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
	auto* playerData = GameAssembly.StorageData_get_PlayerData();
	playerData->fields.m_isUseExe = false;

	return GameAssembly.PartnerCtrl_IsPossibleMiracle(partner, isLose);
}

// ==========================================================================================
void HelperLib::Initialize(void* gModule)
{
	GameAssembly.Initialize((size_t)gModule);

	// Install hooks
	distormx_hook(reinterpret_cast<void**>(&GameAssembly.MainGameManager_Update.ptr), &MainGameManager_Update);
	distormx_hook(reinterpret_cast<void**>(&GameAssembly.PartnerCtrl_IsPossibleMiracle.ptr), &PartnerCtrl_IsPossibleMiracle);
}

void HelperLib::Release()
{
	// Remove hooks
	distormx_unhook(GameAssembly.MainGameManager_Update.ptr);
	distormx_unhook(GameAssembly.PartnerCtrl_IsPossibleMiracle.ptr);

	distormx_destroy();
}
