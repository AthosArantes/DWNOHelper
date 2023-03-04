#pragma once

namespace HelperLib
{
	struct Options
	{
		bool EnableLifetimeMessage {true};
		bool UnlimitedExE {true};
	};

	void Initialize(void* gameAssemblyBaseAddress, const Options& options);
	void Release();
}
