// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file instance.h
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
	* Class used to forwarding the instance of an object
	*/
	class REFLECTPP_API instance final
	{
		friend property;

	public:

		instance() = default;
		~instance();
		instance(const instance&) = default;
		instance(instance&&) REFLECTPP_NOEXCEPT = default;
		instance& operator=(const instance&) = default;
		instance& operator=(instance&&) REFLECTPP_NOEXCEPT = default;

		/**
		* Creates an instance from a variant
		* @param var
		*/
		instance(const variant& var) REFLECTPP_NOEXCEPT;

		/**
		* Create an instance from an object
		* @param object
		*/
		template<typename T, typename U = std::enable_if_t<!std::is_same_v<variant, details::decay<T>> && !std::is_same_v<instance, details::decay<T>>>>
		instance(T& object) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		explicit operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type of the stored value
		*/
		type& get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

	private:
		
		bool m_is_owner;
		variant* m_var;
	};
}

#include "details/inline/instance.inl"

/**
* @}
*/
