// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file hasher.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <functional>
#include <string>

#include "details/core/macros.h"

namespace reflectpp
{
	namespace details
	{
		REFLECTPP_INLINE size_t hash(const char* str) REFLECTPP_NOEXCEPT;
	}
}

#include "details/core/impl/hasher.inl"
