// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file reflectpp_cast_helper.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/registry.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T, typename U>
		REFLECTPP_INLINE std::remove_pointer_t<T>* cast(U* object) REFLECTPP_NOEXCEPT;

		REFLECTPP_API bool can_cast(type_data* object, type_data* type) REFLECTPP_NOEXCEPT;
	}
}

#include "details/core/impl/reflectpp_cast_helper.inl"
