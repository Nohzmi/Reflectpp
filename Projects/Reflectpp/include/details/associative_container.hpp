// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file associative_container.hpp
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <map>

#include "details/macros.h"
#include "details/associative_container_data.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE associative_container_data get_associative_container_data(T) REFLECTPP_NOEXCEPT
		{
			return associative_container_data();
		}

		template<typename>
		struct is_associative_container : std::false_type {};

		template<typename Key, typename T>
		REFLECTPP_INLINE associative_container_data get_associative_container_data(std::map<Key, T>) REFLECTPP_NOEXCEPT
		{
			associative_container_data data;

			return data;
		}

		template<typename Key, typename T>
		struct is_associative_container<std::map<Key, T>> : std::true_type {};
	}
}
