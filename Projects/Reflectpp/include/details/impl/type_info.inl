// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T>
	REFLECTPP_INLINE type_info type_info::get() REFLECTPP_NOEXCEPT
	{
		return type_info(details::registry::get_instance().get_type_info<T>());
	}
}
