// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant_wrapper_view.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/macros.h"
#include "details/core/platform.h"
#include "details/data/variant_data.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	/**
	* Allows to store wrappers of any type \n
	* Wrapper: std::unique_ptr<T>, ...etc
	*/
	class REFLECTPP_API variant_wrapper_view final
	{
	public:

		variant_wrapper_view() = default;
		~variant_wrapper_view() = default;
		variant_wrapper_view(const variant_wrapper_view&) = default;
		variant_wrapper_view(variant_wrapper_view&&) REFLECTPP_NOEXCEPT = default;
		variant_wrapper_view& operator=(const variant_wrapper_view&) = default;
		variant_wrapper_view& operator=(variant_wrapper_view&&) REFLECTPP_NOEXCEPT = default;
		explicit variant_wrapper_view(const details::variant_data& data) REFLECTPP_NOEXCEPT;

		/**
		* Returns the type object of this wrapper
		*/
		type get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type object of the wrapped value of this wrapper \n
		* Can be different from the wrapped value type
		*/
		type get_wrapped_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the wrapped value of this wrapper
		*/
		variant get_wrapped_value() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the wrapper managed an object
		*/
		bool is_empty() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored value is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored value is valid
		*/
		explicit operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Replaces the managed object and destroys the object currently managed
		* @param value
		*/
		void reset(argument value) REFLECTPP_NOEXCEPT;

	private:

		details::variant_data m_data;
	};
}

/**
* @}
*/
