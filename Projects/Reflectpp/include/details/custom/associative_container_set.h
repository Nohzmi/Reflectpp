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
		struct associative_container<std::set<Key>> final
		{
			REFLECTPP_INLINE static auto get_data() REFLECTPP_NOEXCEPT;
		};

		template<typename Key>
		struct is_associative_container<std::set<Key>> final : std::true_type {};

		template<typename Key>
		struct has_value_type<std::set<Key>> final : std::false_type {};
	}
}

#include "details/custom/impl/associative_container_set.inl"
