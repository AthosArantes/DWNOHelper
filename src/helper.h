#pragma once

#include <cstdint>

namespace HelperLib
{
	struct Options
	{
		// Helpers

		unsigned LifetimeMessageKey {282};

		// Cheats

		bool UnlimitedExE {false};
		bool DisableAgeing {false};
		unsigned ToggleAgeingKey {283};
		bool ManageConstructionMaterials {false};
	};

	void Initialize(const Options& options);
	void Release();
}
