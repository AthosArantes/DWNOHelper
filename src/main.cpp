#include "helper.h"

#include <inireader/inireader.hpp>
#include <filesystem>
#include <fstream>

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// Windows Header Files
#include <windows.h>
#include <tchar.h>

static bool Initialized = false;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			TCHAR buffer[MAX_PATH];
			DWORD len = GetModuleFileName(hModule, buffer, MAX_PATH);
			if (len == 0)
			{
				return FALSE;
			}

			std::filesystem::path path {buffer, &buffer[0] + len};
			path.replace_extension("ini");

			// Read configuration file
			HelperLib::Options options {};			
			try
			{
				ini::Parser iniFile {};
				iniFile.Parse(path);

				ini::Parser::IniSection& section = iniFile.GetSection("Main");
				options.EnableLifetimeMessage = section["EnableLifetimeMessage"].as<bool>();
				options.UnlimitedExE = section["UnlimitedExE"].as<bool>();
			}
			catch (std::runtime_error&)
			{
				return FALSE;
			}

			HMODULE gameAssemblyBaseAddress = GetModuleHandle(_T("GameAssembly.dll"));
			if (gameAssemblyBaseAddress == NULL)
			{
				return FALSE;
			}

			HelperLib::Initialize(gameAssemblyBaseAddress, options);
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
