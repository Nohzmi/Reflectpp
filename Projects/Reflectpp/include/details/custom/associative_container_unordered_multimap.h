// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file associative_container_unordered_multimap.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <unordered_map>

#include "details/custom/associative_container.h"

namespace reflectpp
{
	namespace details
	{
		template<typename Key, typename T>
		struct associative_container<std::unordered_multimap<Key, T>> final
		{
			REFLECTPP_INLINE static auto get_data() REFLECTPP_NOEXCEPT;
		};

		template<typename Key, typename T>
		struct is_associative_container<std::unordered_multimap<Key, T>> final : std::true_type {};

		template<typename Key, typename T>
		struct has_value_type<std::unordered_multimap<Key, T>> final : std::true_type {};
	}
}

#include "details/custom/impl/associative_container_unordered_multimap.inl"
