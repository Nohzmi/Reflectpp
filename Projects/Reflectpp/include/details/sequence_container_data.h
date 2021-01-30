// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file sequence_container_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once

namespace reflectpp
{
	namespace details
	{
		template<typename T>
		struct sequence_container_data final
		{
			using iterator = typename T::iterator;
			using value_type = typename T::value_type;

			value_type& (*m_at)(T* container, size_t pos) { nullptr };
			iterator (*m_begin)(T* container) { nullptr };
			void (*m_clear)(T* container) { nullptr };
			iterator (*m_end)(T* container) { nullptr };
			iterator (*m_erase)(T* container, iterator pos) { nullptr };
			iterator (*m_insert)(T* container, iterator pos, const value_type& value) { nullptr };
			void (*m_resize)(T* container, size_t count) { nullptr };
			size_t (*m_size)(T* container) { nullptr };
		};

		template<>
		struct sequence_container_data<void> final
		{
		};
	}
}
