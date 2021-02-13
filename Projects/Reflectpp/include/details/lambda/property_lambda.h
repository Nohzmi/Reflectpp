// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file property_lambda.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/macros.h"
#include "details/core/type_traits.h"

namespace reflectpp
{
	namespace details
	{
		REFLECTPP_INLINE auto property_getter_addr(size_t offset) REFLECTPP_NOEXCEPT;

		template<typename T, typename PropertyT>
		REFLECTPP_INLINE auto property_getter_func(PropertyT(T::* getter)() const) REFLECTPP_NOEXCEPT;

		template<typename PropertyT>
		REFLECTPP_INLINE auto property_setter_addr(size_t offset) REFLECTPP_NOEXCEPT;

		template<typename T, typename PropertyT>
		REFLECTPP_INLINE auto property_setter_func(void(T::* setter)(PropertyT)) REFLECTPP_NOEXCEPT;
	}
}

#include "details/lambda/impl/property_lambda.inl"
