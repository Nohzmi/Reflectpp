// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file wrapper_unique_ptr.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <memory>

#include "details/custom/wrapper.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		struct wrapper<std::unique_ptr<T>> final
		{
			REFLECTPP_INLINE static auto get_data() REFLECTPP_NOEXCEPT;
		};
		
		template<typename T>
		struct is_wrapper<std::unique_ptr<T>> final : std::true_type {};
	}
}

#include "details/custom/impl/wrapper_unique_ptr.inl"
