// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "details/registry.h"

namespace reflectpp
{
	template<typename T>
	inline type_info& type_info::get() noexcept
	{
		return *details::registry::get_instance().get_type_info<T>();
	}
}
