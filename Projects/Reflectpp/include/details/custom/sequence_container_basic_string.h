// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequence_container_basic_string.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <string>

#include "details/custom/sequence_container.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		struct sequence_container<std::basic_string<T>>
		{
			REFLECTPP_INLINE static auto get_data() REFLECTPP_NOEXCEPT;
		};

		template<typename T>
		struct is_sequence_container<std::basic_string<T>> : std::true_type {};
	}
}

#include "details/custom/impl/sequence_container_basic_string.inl"
