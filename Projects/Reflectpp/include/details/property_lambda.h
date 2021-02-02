// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file property_lambda.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/macros.h"
#include "details/type_traits.h"

namespace reflectpp
{
	namespace details
	{
		REFLECTPP_INLINE auto get_getter_addr(size_t offset) REFLECTPP_NOEXCEPT;

		template<typename T, typename PropertyT>
		REFLECTPP_INLINE auto get_getter_func(PropertyT(T::* getter)() const) REFLECTPP_NOEXCEPT;

		template<typename PropertyT>
		REFLECTPP_INLINE auto get_setter_addr(size_t offset) REFLECTPP_NOEXCEPT;

		template<typename T, typename PropertyT>
		REFLECTPP_INLINE auto get_setter_func(void(T::* setter)(PropertyT)) REFLECTPP_NOEXCEPT;
	}
}

#include "details/inline/property_lambda.inl"
