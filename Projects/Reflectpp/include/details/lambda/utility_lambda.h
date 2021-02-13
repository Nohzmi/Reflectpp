// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file utility_lambda.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/macros.h"
#include "details/core/utility_type_traits.h"

namespace reflectpp
{
	namespace details
	{
		template<typename From, typename To>
		REFLECTPP_INLINE auto get_can_convert() REFLECTPP_NOEXCEPT;

		template<typename T>
		REFLECTPP_INLINE auto get_compare() REFLECTPP_NOEXCEPT;

		template<typename From, typename To>
		REFLECTPP_INLINE auto get_convert() REFLECTPP_NOEXCEPT;
	}
}

#include "details/lambda/impl/utility_lambda.inl"
