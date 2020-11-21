// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file hasher.h
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
		size_t hash(const char* str) REFLECTPP_NOEXCEPT;
	}
}

#include "details/inline/hasher.inl"
