// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file associative_container.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/macros.h"
#include "details/data/associative_container_data.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_associative_container_data(T) REFLECTPP_NOEXCEPT;

		template<typename>
		struct has_value_type : std::false_type {};

		template<typename>
		struct is_associative_container : std::false_type {};
	}
}

#include "details/custom/impl/associative_container.inl"
