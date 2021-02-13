// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file wrapper_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/forward.h"

namespace reflectpp
{
	namespace details
	{
		struct wrapper_data final
		{
			void* (*m_get)(void*) { nullptr };
			type_data* m_value_type{ nullptr };
		};
	}
}
