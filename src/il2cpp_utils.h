#pragma once

#include <cstddef>
#include <cassert>
#include <type_traits>

namespace il2cpp
{
	template <typename ReturnTy, typename... Args>
	struct function
	{
		using value_type = ReturnTy (*)(Args...);

		function() :
			ptr(nullptr)
		{
		}
		function(size_t rva) :
			ptr(reinterpret_cast<value_type>(rva))
		{
		}

		ReturnTy operator()(Args... args)
		{
			assert(ptr != nullptr);
			return ptr(std::forward<Args>(args)...);
		}

		value_type ptr;
	};
}
