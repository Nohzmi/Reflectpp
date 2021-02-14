// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file smart_pointer_unique_ptr.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <memory>

#include "details/custom/smart_pointer.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		struct smart_pointer<std::unique_ptr<T>>
		{
			REFLECTPP_INLINE static auto get_data() REFLECTPP_NOEXCEPT;
		};
		
		template<typename T>
		struct is_smart_pointer<std::unique_ptr<T>> : std::true_type {};
	}
}

#include "details/custom/impl/smart_pointer_unique_ptr.inl"
