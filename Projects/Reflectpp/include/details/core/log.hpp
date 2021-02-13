// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file log.hpp
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <cstdio>

#include "details/core/macros.h"

#ifdef _DEBUG
	#define REFLECTPP_LOG(format, ...) reflectpp::details::_assert(__FILE__, __LINE__, format, __VA_ARGS__)
#else
	#define REFLECTPP_LOG(format, ...)
#endif

namespace reflectpp
{
	namespace details
	{
		template <class ...Args>
		REFLECTPP_INLINE void _assert(const char* file, int line, const char* format, Args... args) REFLECTPP_NOEXCEPT
		{
			printf("");
			printf("\033[33mLog: ");
			printf(format, args...);
			printf(" [%s:%d]\033[0m\n", file, line);
		}
	}
}
