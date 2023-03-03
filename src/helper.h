#pragma once

namespace HelperLib
{
	struct Options
	{
		bool EnableLifetimeMessage;
		bool UnlimitedExE;
	};

	void Initialize(void* gameAssemblyBaseAddress, const Options& options);
	void Release();
}
