// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file argument.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "variant.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	class property;
	class type;

	/**
	* Class used to forwarding the argument of an object
	*/
	class REFLECTPP_API argument final
	{
		friend property;
		friend variant_sequencial_view;

	public:

		argument() = default;
		~argument();
		argument(const argument&) = default;
		argument(argument&&) REFLECTPP_NOEXCEPT = default;
		argument& operator=(const argument&) = default;
		argument& operator=(argument&&) REFLECTPP_NOEXCEPT = default;

		/**
		* Creates an argument from a variant
		* @param var
		*/
		argument(const variant& var) REFLECTPP_NOEXCEPT;

		/**
		* Create an argument from an object
		* @param object
		*/
		template<typename T, typename U = std::enable_if_t<!std::is_same_v<variant, details::decay<T>> && !std::is_same_v<argument, details::decay<T>> && !std::is_pointer_v<std::decay_t<T>>>>
		argument(T&& object) REFLECTPP_NOEXCEPT;

		/**
		* Returns the type of the stored value
		*/
		type& get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the value as requested type \n
		* Use is_type() to check if the type is valid
		*/
		template<typename T>
		T& get_value() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored value is the same type as requested type
		*/
		template<typename T>
		bool is_type() const REFLECTPP_NOEXCEPT;

	private:
		
		bool m_is_owner;
		variant* m_var;
	};
}

#include "details/inline/argument.inl"

/**
* @}
*/
