// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_info_helper.hpp
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <typeinfo>

#include "details/macros.h"
#include "details/register_traits.h"
#include "details/type_traits.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE size_t type_id() REFLECTPP_NOEXCEPT
		{
			if constexpr (std::is_arithmetic_v<T> || !is_registered<T>::value)
			{
				return typeid(decay<T>).hash_code();
			}
			else
				return decay<T>::type_id();
		}

		template<typename T>
		REFLECTPP_INLINE const char* type_name() REFLECTPP_NOEXCEPT
		{
			if constexpr (std::is_arithmetic_v<T> || !is_registered<T>::value)
			{
				return typeid(decay<T>).name();
			}
			else
			{
				return decay<T>::type_name();
			}
		}
	}
}
