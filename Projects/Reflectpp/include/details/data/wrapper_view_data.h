// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file wrapper_view_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <utility>

#include "details/core/forward.h"

namespace reflectpp
{
	namespace details
	{
		struct wrapper_view_data final
		{
			std::pair<type_data*, void*>(*m_get)(void*) { nullptr };
			void (*m_reset)(void*, void*) { nullptr };
			type_data* m_wrapped_type{ nullptr };
		};
	}
}
