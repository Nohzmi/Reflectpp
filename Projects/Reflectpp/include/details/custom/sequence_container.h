// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequence_container.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/macros.h"
#include "details/data/sequence_container_data.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_sequence_container_data(T) REFLECTPP_NOEXCEPT;

		template<typename>
		struct is_sequence_container : std::false_type {};
	}
}

#include "details/custom/impl/sequence_container.inl"
