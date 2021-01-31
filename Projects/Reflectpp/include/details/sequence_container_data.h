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
		template<typename Container = void, typename Iterator = void, typename Value = void>
		struct sequence_container_data final
		{
			using class_type = Container;
			using iterator = Iterator;
			using value_type = Value;

			value_type& (*m_at)(class_type* container, size_t pos) { nullptr };
			iterator (*m_begin)(class_type* container) { nullptr };
			void (*m_clear)(class_type* container) { nullptr };
			iterator (*m_end)(class_type* container) { nullptr };
			iterator (*m_erase)(class_type* container, iterator pos) { nullptr };
			iterator (*m_insert)(class_type* container, iterator pos, const value_type& value) { nullptr };
			void (*m_resize)(class_type* container, size_t count) { nullptr };
			size_t (*m_size)(class_type* container) { nullptr };
		};

		template<typename Container, typename Iterator>
		struct sequence_container_data<Container, Iterator, void> final
		{
		};

		template<typename Container>
		struct sequence_container_data<Container, void, void> final
		{
		};

		template<>
		struct sequence_container_data<void, void, void> final
		{
		};
	}
}
