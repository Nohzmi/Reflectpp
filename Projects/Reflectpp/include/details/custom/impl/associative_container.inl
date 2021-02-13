// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_associative_container_data(T) REFLECTPP_NOEXCEPT
		{
			return associative_container_data();
		}
	}
}
