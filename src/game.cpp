#include "game.h"

GameAssemblyModule GameAssembly {};

void GameAssemblyModule::Initialize(size_t moduleAddress)
{
#define ADD_MODULE_ADDRESS(v) \
	v.ptr = reinterpret_cast<typename decltype(v)::value_type>(reinterpret_cast<size_t>(v.ptr) + moduleAddress)

	ADD_MODULE_ADDRESS(Encoding_get_UTF8);
	ADD_MODULE_ADDRESS(String_CreateStringFromEncoding);

	ADD_MODULE_ADDRESS(Input_GetKey);
	ADD_MODULE_ADDRESS(Input_GetKeyDown);
	ADD_MODULE_ADDRESS(Input_GetKeyUp);

	ADD_MODULE_ADDRESS(MainGameManager_get);
	ADD_MODULE_ADDRESS(MainGameManager_GetPlayerCtrl);
	ADD_MODULE_ADDRESS(MainGameManager_GetPartnerCtrl);
	ADD_MODULE_ADDRESS(MainGameManager_Update);
	ADD_MODULE_ADDRESS(MainGameManager_get_MainMessageManager);

	ADD_MODULE_ADDRESS(StorageData_get_PlayerData);

	ADD_MODULE_ADDRESS(CommonMessageWindowManager_Get00);
	ADD_MODULE_ADDRESS(CommonMessageWindowManager_Get01);
	ADD_MODULE_ADDRESS(uCommonMessageWindow_SetMessage);

	ADD_MODULE_ADDRESS(uFieldPanel_StartDigimonMessage);

	ADD_MODULE_ADDRESS(PartnerCtrl_IsPossibleMiracle);

#undef ADD_MODULE_ADDRESS
}
