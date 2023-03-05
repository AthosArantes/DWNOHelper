#include "GameAssembly.h"
#include "helper.h"

#include <inireader/inireader.hpp>
#include <filesystem>
#include <vector>

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// Windows Header Files
#include <windows.h>
#include <tchar.h>

// ==========================================================================================
static std::filesystem::path GetModuleFilePath(HMODULE hModule)
{
	std::vector<TCHAR> buffer;
	DWORD len = 0;
	do
	{
		buffer.resize(buffer.capacity() + MAX_PATH);
		len = GetModuleFileName(hModule, buffer.data(), buffer.capacity());
	} while (len >= buffer.capacity());
	return std::filesystem::path {buffer.data(), buffer.data() + len};
}

// ==========================================================================================
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	static bool Initialized = false;

	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			HMODULE gameAssemblyBaseAddress = GetModuleHandle(_T("GameAssembly.dll"));
			if (gameAssemblyBaseAddress == NULL)
			{
				fprintf(stderr, "[Error] Failed to retrieve GameAssembly handle.");
				return FALSE;
			}
			GameAssembly.Initialize(gameAssemblyBaseAddress);

			// Read configuration file
			HelperLib::Options options {};
			try
			{
				std::filesystem::path path {GetModuleFilePath(hModule)};
				path.replace_extension(_T("ini"));

				ini::Parser iniFile {};
				iniFile.Parse(path);

				ini::Parser::IniSection& section = iniFile.GetSection("Main");
				options.LifetimeMessageKey = section["LifetimeMessageKey"].as<unsigned>();
				options.UnlimitedExE = section["UnlimitedExE"].as<bool>();
			}
			catch (std::runtime_error& e)
			{
				fprintf(stderr, "[ini::Parser][Error] %s. Default settings will be used.", e.what());
			}
			HelperLib::Initialize(options);
			Initialized = true;

			return TRUE;
		}
		case DLL_THREAD_ATTACH:
			return TRUE;
		case DLL_THREAD_DETACH:
			return TRUE;
		case DLL_PROCESS_DETACH:
			if (Initialized)
			{
				HelperLib::Release();
			}
			return TRUE;
		default:
			return FALSE;
	}
}
