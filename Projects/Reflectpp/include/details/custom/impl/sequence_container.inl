// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_sequence_container_data(T) REFLECTPP_NOEXCEPT
		{
			return sequence_container_data<void>();
		}
	}
}
