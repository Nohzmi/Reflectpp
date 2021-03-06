// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file wrapper_lambda.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/macros.h"
#include "custom_wrapper.h"

namespace reflectpp
{
	namespace details
	{
		template<typename Class>
		REFLECTPP_INLINE auto wrapper_get() REFLECTPP_NOEXCEPT;

		template<typename Class, typename Value>
		REFLECTPP_INLINE auto wrapper_reset() REFLECTPP_NOEXCEPT;
	}
}

#include "details/lambda/impl/wrapper_lambda.inl"
