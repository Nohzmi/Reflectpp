// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/registry.h"
#include "details/variant_data.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	class property;
	class variant_sequencial_view;

	/**
	* Allows to store data of any type
	*/
	class REFLECTPP_API variant final
	{
		friend property;
		friend variant_sequencial_view;

	public:

		variant() = default;
		REFLECTPP_INLINE ~variant();
		REFLECTPP_INLINE variant(const variant&);
		variant(variant&&) REFLECTPP_NOEXCEPT = default;
		REFLECTPP_INLINE variant& operator=(const variant&);
		variant& operator=(variant&&) REFLECTPP_NOEXCEPT = default;
		REFLECTPP_INLINE explicit variant(const details::variant_data& data) REFLECTPP_NOEXCEPT;

		/**
		* Create a variant from an object \n
		* Don't have the ownership in this case
		* @param object
		*/
		template<typename T, typename U = std::enable_if_t<!std::is_same_v<variant, details::decay<T>> && !std::is_pointer_v<std::decay_t<T>>>>
		REFLECTPP_INLINE variant(T&& object) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		REFLECTPP_INLINE operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Clear the stored value of this variant
		*/
		REFLECTPP_INLINE void clear() REFLECTPP_NOEXCEPT;
		
		/**
		* Creates a variant_sequential_view from the containing value
		*/
		variant_sequencial_view create_sequential_view() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type of the stored value
		*/
		type get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the value as requested type \n
		* Use is_type() to check if the type is valid
		*/
		template<typename T>
		REFLECTPP_INLINE T& get_value() REFLECTPP_NOEXCEPT;

		/**
		* Returns the value as requested type \n
		* Use is_type() to check if the type is valid
		*/
		template<typename T>
		REFLECTPP_INLINE const T& get_value() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not this type is a sequencial container
		*/
		REFLECTPP_INLINE bool is_sequential_container() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored value is the same type as requested type
		*/
		template<typename T>
		REFLECTPP_INLINE bool is_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		REFLECTPP_INLINE bool is_valid() const REFLECTPP_NOEXCEPT;

	private:

		details::variant_data m_data;
	};
}

#include "details/inline/variant.inl"

/**
* @}
*/
