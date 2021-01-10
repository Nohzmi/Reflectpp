// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/registry.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	class type;
	class property;

	/**
	* Allows to store data of any type
	*/
	class REFLECTPP_API variant final
	{
		friend property;
		friend type;

	public:

		variant();
		~variant();
		variant(const variant&);
		variant(variant&&) REFLECTPP_NOEXCEPT = default;
		variant& operator=(const variant&);
		variant& operator=(variant&&) REFLECTPP_NOEXCEPT = default;

		/**
		* Create a variant from an object \n
		* Don't have the ownership in this case
		* @param object
		*/
		template<typename T, typename U = std::enable_if_t<!std::is_same_v<variant, details::decay<T>> && !std::is_pointer_v<std::decay_t<T>>>>
		variant(T&& object) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Clear the stored value of this variant
		*/
		void clear() REFLECTPP_NOEXCEPT;

		/**
		* Returns the type of the stored value
		*/
		type& get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the value as requested type \n
		* Use is_type() to check if the type is valid
		*/
		template<typename T>
		T& get_value() REFLECTPP_NOEXCEPT;

		/**
		* Returns the value as requested type \n
		* Use is_type() to check if the type is valid
		*/
		template<typename T>
		const T& get_value() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored value is the same type as requested type
		*/
		template<typename T>
		bool is_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

	private:

		variant(void* data, bool is_owner, type* type) REFLECTPP_NOEXCEPT;

		void* m_data;
		bool m_is_owner;
		type* m_type;
	};
}

#include "details/inline/variant.inl"

/**
* @}
*/
