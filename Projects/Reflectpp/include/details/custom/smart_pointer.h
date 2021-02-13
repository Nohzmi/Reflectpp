// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file smart_pointer.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/macros.h"
#include "details/data/smart_pointer_data.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_smart_pointer_data(T) REFLECTPP_NOEXCEPT;

		template<typename>
		struct is_smart_pointer : std::false_type {};
	}
}

#include "details/custom/impl/smart_pointer.inl"
