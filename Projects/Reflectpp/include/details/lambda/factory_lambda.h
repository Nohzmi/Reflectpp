// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file factory_lambda.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <type_traits>

#include "details/core/macros.h"

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		REFLECTPP_INLINE auto factory_constructor() REFLECTPP_NOEXCEPT;

		template<typename T>
		REFLECTPP_INLINE auto factory_copy_constructor() REFLECTPP_NOEXCEPT;

		template<typename T>
		REFLECTPP_INLINE auto factory_destructor() REFLECTPP_NOEXCEPT;
	}
}

#include "details/lambda/impl/factory_lambda.inl"
