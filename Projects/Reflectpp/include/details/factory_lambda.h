// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file factory_lambda.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/macros.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto get_constructor() REFLECTPP_NOEXCEPT;

		template<typename T>
		REFLECTPP_INLINE auto get_copy_constructor() REFLECTPP_NOEXCEPT;

		template<typename T>
		REFLECTPP_INLINE auto get_destructor() REFLECTPP_NOEXCEPT;
	}
}

#include "details/inline/factory_lambda.inl"
