// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file associative_container_set.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <set>

#include "details/custom/associative_container.h"

namespace reflectpp
{
	namespace details
	{
		template<typename Key>
		REFLECTPP_INLINE auto get_associative_container_data(std::set<Key>) REFLECTPP_NOEXCEPT;

		template<typename Key>
		struct is_associative_container<std::set<Key>> : std::true_type {};

		template<typename Key>
		struct has_value_type<std::set<Key>> : std::false_type {};
	}
}

#include "details/custom/impl/associative_container_set.inl"
