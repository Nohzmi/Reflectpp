// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file smart_pointer_data.h
* @author Nohzmi
* @version 1.0
*/

#pragma once

namespace reflectpp
{
	namespace details
	{
		template<typename Container = void, typename Value = void>
		struct smart_pointer_data final
		{
			using class_type = Container;
			using value_type = Value;

			value_type* (*m_get)(class_type* container) { nullptr };
		};

		template<typename Container>
		struct smart_pointer_data<Container, void> final
		{
		};

		template<>
		struct smart_pointer_data<void, void> final
		{
		};
	}
}
