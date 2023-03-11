#include "GameAssembly.h"

GameAssemblyModule GameAssembly {};

void GameAssemblyModule::Initialize(void* baseAddress)
{
#define ADD_MODULE_ADDRESS(v) \
	v.ptr = reinterpret_cast<typename decltype(v)::value_type>((size_t)v.ptr + (size_t)baseAddress)

	ADD_MODULE_ADDRESS(Encoding_get_UTF8);
	ADD_MODULE_ADDRESS(String_CreateStringFromEncoding);

	ADD_MODULE_ADDRESS(Input_GetKey);
	ADD_MODULE_ADDRESS(Input_GetKeyDown);
	ADD_MODULE_ADDRESS(Input_GetKeyUp);

	ADD_MODULE_ADDRESS(Language_get_SystemLanguage);

	ADD_MODULE_ADDRESS(MainGameManager_get);
	ADD_MODULE_ADDRESS(MainGameManager_GetPlayerCtrl);
	ADD_MODULE_ADDRESS(MainGameManager_GetPartnerCtrl);
	ADD_MODULE_ADDRESS(MainGameManager_Update);
	ADD_MODULE_ADDRESS(MainGameManager_get_MainMessageManager);

	ADD_MODULE_ADDRESS(StorageData);

	ADD_MODULE_ADDRESS(CommonMessageWindowManager_Get00);
	ADD_MODULE_ADDRESS(CommonMessageWindowManager_Get01);
	ADD_MODULE_ADDRESS(uCommonMessageWindow_SetMessage);
	ADD_MODULE_ADDRESS(uConstructionPanelMaterial_Update);
	ADD_MODULE_ADDRESS(uConstructionPanelMaterial_MaterialNum_SetNum);
	ADD_MODULE_ADDRESS(uItemBase_GetSelectItemData);
	ADD_MODULE_ADDRESS(uItemBase_UpdateItemListObjectAll);
	ADD_MODULE_ADDRESS(uStoragePanel_Update);

	ADD_MODULE_ADDRESS(uFieldPanel_StartDigimonMessage);

	ADD_MODULE_ADDRESS(PartnerCtrl_IsPossibleMiracle);

#undef ADD_MODULE_ADDRESS
}
