// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file associative_container_map.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <map>

#include "details/custom/associative_container.h"

namespace reflectpp
{
	namespace details
	{
		template<typename Key, typename T>
		REFLECTPP_INLINE auto get_associative_container_data(std::map<Key, T>) REFLECTPP_NOEXCEPT;

		template<typename Key, typename T>
		struct is_associative_container<std::map<Key, T>> : std::true_type {};

		template<typename Key, typename T>
		struct has_value_type<std::map<Key, T>> : std::true_type {};
	}
}

#include "details/custom/impl/associative_container_map.inl"
