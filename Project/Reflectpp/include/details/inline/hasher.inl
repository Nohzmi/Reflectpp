// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		inline size_t hash(const char* str) noexcept
		{
			std::hash<std::string> hasher;
			return hasher(std::string(str));
		}
	}
}
