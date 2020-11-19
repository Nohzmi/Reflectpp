// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file hasher.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <functional>
#include <string>

namespace reflectpp
{
	namespace details
	{
		size_t hash(const char* str) noexcept;
	}
}

#include "details/inline/hasher.inl"
