// Copyright (c) 2020, Nohzmi. All rights reserved.

namespace reflectpp
{
	namespace details
	{
		template<class ...Args>
		REFLECTPP_INLINE void _assert(bool expr, const char* file, int line, const char* format, Args ...args) REFLECTPP_NOEXCEPT
		{
			if (!expr)
			{
				fprintf(stderr, "\033[31m");
				fprintf(stderr, "Assertion failed: ");
				fprintf(stderr, format, args...);
				fprintf(stderr, " [%s:%d]", file, line);
				fprintf(stderr, "\033[0m\n");
				abort();
			}
		}
	}
}
