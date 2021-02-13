// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequence_container_vector.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <vector>

#include "details/custom/sequence_container.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_sequence_container_data(std::vector<T>) REFLECTPP_NOEXCEPT;

		template<typename T>
		struct is_sequence_container<std::vector<T>> : std::true_type {};
	}
}

#include "details/custom/impl/sequence_container_vector.inl"
