// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequence_container_array.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <array>

#include "details/custom/sequence_container.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T, size_t Size>
		REFLECTPP_INLINE auto get_sequence_container_data(std::array<T, Size>) REFLECTPP_NOEXCEPT;
		
		template<typename T, size_t Size>
		struct is_sequence_container<std::array<T, Size>> : std::true_type {};
	}
}

#include "details/custom/impl/sequence_container_array.inl"