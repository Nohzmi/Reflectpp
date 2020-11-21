// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file assert.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <cassert>
#include <cstdio>

#include "details/macros.h"

#ifdef _DEBUG
	#define REFLECTPP_ASSERT(exp, format, ...) reflectpp::details::_assert(exp, format, __VA_ARGS__)
#else
	#define REFLECTPP_ASSERT(exp, format, ...)
#endif

namespace reflectpp
{
	namespace details
	{
		template <class ...Args>
		void _assert(bool expr, const char* format, Args... args) REFLECTPP_NOEXCEPT;
	}
}

#include "details/inline/assert.inl"
