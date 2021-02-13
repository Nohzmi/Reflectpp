// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_smart_pointer_data(T) REFLECTPP_NOEXCEPT
		{
			return smart_pointer_data<void>();
		}
	}
}
