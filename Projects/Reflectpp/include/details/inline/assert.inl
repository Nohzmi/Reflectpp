// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<class ...Args>
		REFLECTPP_INLINE void _assert(bool expr, const char* format, Args ...args) REFLECTPP_NOEXCEPT
		{
			if (!expr)
			{
				printf(format, args...);
				assert(false);
			}
		}
	}
}
