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
				fprintf(stderr, "Assertion failed: ");
				fprintf(stderr, format, args...);
				fprintf(stderr, " [%s:%d]\n", file, line);
				assert(false);
			}
		}
	}
}

//Assertion failed: false, file D:\Poste de Travail\Reflectpp\Projects\Reflectpp\include\details\inline\assert.inl, line 14