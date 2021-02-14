// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file register_type_traits.h
* @author Nohzmi
* @version 1.0
*/

#pragma once

namespace reflectpp
{
	namespace details
	{
		template <typename T>
		class has_registered final
		{
		private:

			typedef char true_type[1];
			typedef char false_type[2];

			template <typename C>
			static true_type& test(decltype(&C::registered));

			template <typename C>
			static false_type& test(...);

		public:

			enum { value = sizeof(test<T>(0)) == sizeof(true_type) };
		};
	}
}
