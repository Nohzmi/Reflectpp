// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file utilities.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <typeinfo>

#include "details/assert.h"
#include "details/platform.h"
#include "details/macros.h"
#include "details/type_traits.h"

namespace reflectpp
{
	class type;

	namespace details
	{
		template<typename T>
		size_t type_id() REFLECTPP_NOEXCEPT;

		template<typename T>
		const char* type_name() REFLECTPP_NOEXCEPT;
	}
}

#include "details/inline/utilities.inl"
