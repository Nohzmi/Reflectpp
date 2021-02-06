// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file reflectpp_cast.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/reflectpp_cast_helper.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	/**
	* Allows to cast between class hierarchies up, down and side
	* @param object
	*/
	template<typename T, typename U>
	REFLECTPP_INLINE T cast(U* object) REFLECTPP_NOEXCEPT;
}

#include "details/inline/reflectpp_cast.inl"

/**
* @}
*/
