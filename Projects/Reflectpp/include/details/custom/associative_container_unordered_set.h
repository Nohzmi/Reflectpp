// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file associative_container_unordered_set.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <unordered_set>

#include "details/custom/associative_container.h"

namespace reflectpp
{
	namespace details
	{
		template<typename Key>
		struct associative_container<std::unordered_set<Key>>
		{
			REFLECTPP_INLINE static auto get_data() REFLECTPP_NOEXCEPT;
		};

		template<typename Key>
		struct is_associative_container<std::unordered_set<Key>> : std::true_type {};

		template<typename Key>
		struct has_value_type<std::unordered_set<Key>> : std::false_type {};
	}
}

#include "details/custom/impl/associative_container_unordered_set.inl"
