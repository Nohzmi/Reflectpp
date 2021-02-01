// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file associative_view_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/forward.h"

namespace reflectpp
{
	namespace details
	{
		struct associative_view_data final
		{
			std::pair<void*, void*> (*m_associative_at)(void*, size_t) { nullptr };
			void (*m_associative_clear)(void*) { nullptr };
			std::pair<size_t, size_t> (*m_associative_equal_range)(void*, void*) { nullptr };
			size_t (*m_associative_erase)(void*, void*) { nullptr };
			size_t (*m_associative_find)(void*, void*) { nullptr };
			std::pair<size_t, bool> (*m_associative_insert)(void*, void*, void*) { nullptr };
			size_t (*m_associative_size)(void*) { nullptr };
			type_data* m_key_type{ nullptr };
			type_data* m_value_type{ nullptr };
		};
	}
}
