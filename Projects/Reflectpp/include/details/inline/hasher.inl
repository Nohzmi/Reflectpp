// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		REFLECTPP_INLINE size_t hash(const char* str) REFLECTPP_NOEXCEPT
		{
			std::hash<std::string> hasher;
			return hasher(std::string(str));
		}
	}
}
