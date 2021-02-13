// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequence_container_list.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <list>

#include "details/custom/sequence_container.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_sequence_container_data(std::list<T>) REFLECTPP_NOEXCEPT;

		template<typename T>
		struct is_sequence_container<std::list<T>> : std::true_type {};
	}
}

#include "details/custom/impl/sequence_container_list.inl"
