// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_info_helper.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <typeinfo>

#include "details/core/macros.h"
#include "details/core/register_traits.h"
#include "details/core/type_traits.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE size_t type_id() REFLECTPP_NOEXCEPT;

		template<typename T>
		REFLECTPP_INLINE const char* type_name() REFLECTPP_NOEXCEPT;
	}
}

#include "details/core/impl/type_info_helper.inl"
