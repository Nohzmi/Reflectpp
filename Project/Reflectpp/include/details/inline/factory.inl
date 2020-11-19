// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T>
	inline factory& factory::get() noexcept
	{
		return *details::registry::get_instance().get_factory<T>();
	}
}
