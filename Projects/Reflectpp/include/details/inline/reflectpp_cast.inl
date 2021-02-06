// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	template<typename T, typename U>
	REFLECTPP_INLINE T cast(U* object) REFLECTPP_NOEXCEPT
	{
		return details::cast<T>(object);
	}
}
