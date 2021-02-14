// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file wrapper_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once

namespace reflectpp
{
	namespace details
	{
		template<typename Container = void, typename Value = void>
		struct wrapper_data final
		{
			using class_type = Container;
			using value_type = Value;

			value_type* (*m_get)(class_type* container) { nullptr };
			void (*m_reset)(class_type* container, value_type* ptr) { nullptr };
		};

		template<typename Container>
		struct wrapper_data<Container, void> final
		{
		};

		template<>
		struct wrapper_data<void, void> final
		{
		};
	}
}
