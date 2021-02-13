// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequential_view_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/forward.h"

namespace reflectpp
{
	namespace details
	{
		struct sequential_view_data final
		{
			void (*m_assign)(void*, size_t, void*) { nullptr };
			void* (*m_at)(void*, size_t) { nullptr };
			void (*m_clear)(void*) { nullptr };
			void (*m_erase)(void*, size_t) { nullptr };
			void (*m_insert)(void*, size_t, void*) { nullptr };
			void (*m_resize)(void*, size_t) { nullptr };
			size_t (*m_size)(void*) { nullptr };
			type_data* m_value_type{ nullptr };
		};
	}
}
