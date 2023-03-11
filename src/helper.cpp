#include "helper.h"
#include "GameAssembly.h"
#include "Language.h"

#include <distormx/distormx.h>
#include <cstddef>
#include <cstdio>
#include <climits>
#include <algorithm>

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
		auto* playerData = (*GameAssembly.StorageData.ptr)->static_fields->_m_playerData_k__BackingField;
		playerData->fields.m_isUseExe = false;
	}
	return GameAssembly.PartnerCtrl_IsPossibleMiracle(partner, isLose);
}

// Manage town materials
void uConstructionPanelMaterial_Update(uConstructionPanelMaterial_o* instance)
{
	GameAssembly.uConstructionPanelMaterial_Update(instance);

	if (!CurrentOptions.ManageConstructionMaterials)
	{
		return;
	}

	// The material panel is open and is not animating.
	bool isOpen = instance->fields.m_isOpend && (instance->fields.m_state == DWNO::ConstructionPanelState::Main);
	auto* townMaterialAccess = (*GameAssembly.StorageData.ptr)->static_fields->m_materialData;
	if (isOpen && townMaterialAccess)
	{
		// Get how much a material should be incremented/decremented.
		int32_t increment = (int)GameAssembly.Input_GetKeyDown(UnityEngine::KeyCode::KeypadPlus) - (int)GameAssembly.Input_GetKeyDown(UnityEngine::KeyCode::KeypadMinus);
		if (increment != 0)
		{
			// Multiply by 10 if shift is held down
			if (GameAssembly.Input_GetKey(UnityEngine::KeyCode::LeftShift) || GameAssembly.Input_GetKey(UnityEngine::KeyCode::RightShift))
			{
				increment *= 10;
			}

			// The currently selected material index on the panel.
			int32_t selectionIndex = instance->fields.m_materialContentCursor->fields._index_k__BackingField;

			auto* townMaterialDatas = townMaterialAccess->fields.m_materialDatas;
			auto* materialContent = instance->fields.m_materialContents->m_Items[selectionIndex];
			auto* materialNum = instance->fields.m_materialNums->m_Items[selectionIndex];

			if (townMaterialDatas && materialContent && materialNum)
			{
				uint32_t id = materialContent->fields._id_k__BackingField; // Material id

				// Update the material count.
				for (size_t i = 0; i < townMaterialDatas->max_length; ++i)
				{
					auto* m = townMaterialDatas->m_Items[i];
					if (m->fields.m_id == id)
					{
						int32_t& amount = m->fields.m_material_num;
						amount += increment;

						// Update the amount text on the panel.
						GameAssembly.uConstructionPanelMaterial_MaterialNum_SetNum(materialNum, amount);

						break;
					}
				}
			}
		}
	}
}

// Manage town warehouse items
void uStoragePanel_Update(uStoragePanel_o* instance)
{
	GameAssembly.uStoragePanel_Update(instance);

	bool managingBackpack = instance->fields.m_openType == DWNO::StorageType::Player;
	bool managingWarehouse = instance->fields.m_openType == DWNO::StorageType::Shop;
	if (instance->fields.m_enabelPanel && (managingBackpack || managingWarehouse))
	{
		// Get how much an item should be incremented/decremented.
		int32_t increment = (int)GameAssembly.Input_GetKeyDown(UnityEngine::KeyCode::KeypadPlus) - (int)GameAssembly.Input_GetKeyDown(UnityEngine::KeyCode::KeypadMinus);
		if (increment != 0)
		{
			// Multiply by 10 if shift is held down
			if (GameAssembly.Input_GetKey(UnityEngine::KeyCode::LeftShift) || GameAssembly.Input_GetKey(UnityEngine::KeyCode::RightShift))
			{
				increment *= 10;
			}

			auto* panelItem = managingBackpack ? instance->fields.m_itemPanelL : instance->fields.m_itemPanelR;
			if (panelItem)
			{
				auto* itemData = GameAssembly.uItemBase_GetSelectItemData(reinterpret_cast<uItemBase_o*>(panelItem));
				if (itemData)
				{
					int32_t& amount = itemData->fields.m_itemNum;
					amount = std::max(amount + increment, 1);

					// Update text
					GameAssembly.uItemBase_UpdateItemListObjectAll(reinterpret_cast<uItemBase_o*>(panelItem), UINT_MAX);
				}
			}
		}
	}
}

// ==========================================================================================
void HelperLib::Initialize(const Options& options)
{
	CurrentOptions = options;

	// Install hooks
	distormx_hook(reinterpret_cast<void**>(&GameAssembly.MainGameManager_Update.ptr), &MainGameManager_Update);
	distormx_hook(reinterpret_cast<void**>(&GameAssembly.PartnerCtrl_IsPossibleMiracle.ptr), &PartnerCtrl_IsPossibleMiracle);
	distormx_hook(reinterpret_cast<void**>(&GameAssembly.uConstructionPanelMaterial_Update.ptr), &uConstructionPanelMaterial_Update);
	distormx_hook(reinterpret_cast<void**>(&GameAssembly.uStoragePanel_Update.ptr), &uStoragePanel_Update);
}

void HelperLib::Release()
{
	// Remove hooks
	distormx_unhook(&GameAssembly.MainGameManager_Update.ptr);
	distormx_unhook(&GameAssembly.PartnerCtrl_IsPossibleMiracle.ptr);
	distormx_unhook(&GameAssembly.uConstructionPanelMaterial_Update.ptr);
	distormx_unhook(&GameAssembly.uStoragePanel_Update.ptr);

	distormx_destroy();
}
