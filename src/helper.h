#pragma once

#include <cstdint>

namespace HelperLib
{
	struct Options
	{
		unsigned LifetimeMessageKey {282};
		bool UnlimitedExE {false};
	};

	void Initialize(const Options& options);
	void Release();
}
