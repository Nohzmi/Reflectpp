// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file wrapper.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/macros.h"
#include "details/data/wrapper_data.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		struct wrapper final
		{
			REFLECTPP_INLINE static auto get_data() REFLECTPP_NOEXCEPT;
		};

		template<typename>
		struct is_wrapper final : std::false_type {};
	}
}

#include "details/custom/impl/wrapper.inl"
