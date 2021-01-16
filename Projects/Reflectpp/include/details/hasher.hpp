// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file hasher.hpp
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <functional>
#include <string>

#include "details/macros.h"

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
