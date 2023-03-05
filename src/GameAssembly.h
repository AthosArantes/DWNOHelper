#pragma once

#include <il2cppdump/il2cpp.h>
#include "il2cpp_utils.h"
#include "GameConstants.h"

struct GameAssemblyModule
{
	void Initialize(void* baseAddress);

	il2cpp::function<System_Text_Encoding_o*> Encoding_get_UTF8 {0xA7C2B0};
	il2cpp::function<System_String_o*, const char* /*bytes*/, uint32_t /*size*/, System_Text_Encoding_o*> String_CreateStringFromEncoding {0xA7FED0};

	il2cpp::function<bool, unsigned /*keyCode*/> Input_GetKey {0x10C4260};
	il2cpp::function<bool, unsigned /*keyCode*/> Input_GetKeyDown {0x10C4220};
	il2cpp::function<bool, unsigned /*keyCode*/> Input_GetKeyUp {0x10C42A0};

	il2cpp::function<unsigned> Language_get_SystemLanguage {0x3CA830};

	il2cpp::function<MainGameManager_o*> MainGameManager_get {0x26CD30};
	il2cpp::function<PlayerCtrl_o*> MainGameManager_GetPlayerCtrl {0x25F0E0};
	il2cpp::function<PartnerCtrl_o*, int32_t /*idx*/> MainGameManager_GetPartnerCtrl {0x25ECE0};
	il2cpp::function<void, MainGameManager_o* /*this*/> MainGameManager_Update {0x267E40};
	il2cpp::function<CommonMessageWindowManager_o*, MainGameManager_o* /*this*/> MainGameManager_get_MainMessageManager {0x26CC80};

	il2cpp::function<PlayerData_o*> StorageData_get_PlayerData {0x2B3CA0};

	il2cpp::function<uCommonMessageWindow_o*, CommonMessageWindowManager_o* /*this*/> CommonMessageWindowManager_Get00 {0x4E34C0};
	il2cpp::function<uCommonMessageWindow_o*, CommonMessageWindowManager_o* /*this*/> CommonMessageWindowManager_Get01 {0x4E34D0};
	il2cpp::function<void, uCommonMessageWindow_o* /*this*/> uCommonMessageWindow_SetMessage {0x540AE0};

	il2cpp::function<void, int32_t /*unitID*/, System_String_o* /*text*/, float /*timeSeconds*/> uFieldPanel_StartDigimonMessage {0x5D4C50};

	il2cpp::function<bool, PartnerCtrl_o* /*this*/, bool /*isLose*/> PartnerCtrl_IsPossibleMiracle {0x2273E0};
};

extern GameAssemblyModule GameAssembly;
