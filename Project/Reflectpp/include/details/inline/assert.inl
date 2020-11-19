// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<class ...Args>
		inline void _assert(bool expr, const char* format, Args ...args) noexcept
		{
			if (!expr)
			{
				printf(format, args...);
				assert(false);
			}
		}
	}
}
