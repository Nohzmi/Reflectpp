// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/registry.h"
#include "details/data/variant_data.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	/**
	* Allows to store data of any type
	*/
	class REFLECTPP_API variant final
	{
	public:

		variant() = default;
		~variant();
		variant(const variant&);
		variant(variant&&) REFLECTPP_NOEXCEPT;
		variant& operator=(const variant&);
		variant& operator=(variant&&) REFLECTPP_NOEXCEPT;
		explicit variant(const details::variant_data& data) REFLECTPP_NOEXCEPT;
		explicit operator details::variant_data*() const REFLECTPP_NOEXCEPT;

		/**
		* Create a variant from an object \n
		* Don't have the ownership in this case
		* @param object
		*/
		template<typename T, typename = std::enable_if_t<!std::is_same_v<variant, details::decay<T>> && !std::is_pointer_v<std::decay_t<T>>>>
		REFLECTPP_INLINE variant(T&& object) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the contained value can be converted to the given type
		*/
		template<typename T>
		REFLECTPP_INLINE bool can_convert() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the contained value can be converted to the given type
		* @param target_type
		*/
		bool can_convert(const type& target_type) const REFLECTPP_NOEXCEPT;

		/**
		* Clear the stored value of this variant
		*/
		void clear() REFLECTPP_NOEXCEPT;

		/**
		* Converts the containing data to a value of requested type \n
		* Allow conversion between of all arithmetic types \n
		* Allow conversion of enum types to its underlying arithmetic types and vice versa \n
		* Allow conversion if cast authorized \n
		* Returns whether or not the contained value can be converted to the given type
		*/
		template<typename T>
		REFLECTPP_INLINE bool convert() REFLECTPP_NOEXCEPT;

		/**
		* Converts the containing data to a value of requested type \n
		* Allow conversion between of all arithmetic types \n
		* Allow conversion of enum types to its underlying arithmetic types and vice versa \n
		* Allow conversion if cast authorized \n
		* Returns whether or not the contained value can be converted to the given type
		* @param target_type
		*/
		bool convert(const type& target_type) REFLECTPP_NOEXCEPT;

		/**
		* Creates a variant_associative_view from the containing value
		*/
		variant_associative_view create_associative_view() const REFLECTPP_NOEXCEPT;

		/**
		* Creates a variant_sequential_view from the containing value
		*/
		variant_sequential_view create_sequential_view() const REFLECTPP_NOEXCEPT;

		/**
		* Extracts a variant with the wrapped value
		*/
		variant extract_wrapped_value() const REFLECTPP_NOEXCEPT;

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
		* Returns a reference to the contained wrapped value as requested type
		*/
		template<typename T>
		REFLECTPP_INLINE const T& get_wrapped_value() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not this type is an associative container
		*/
		bool is_associative_container() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not this type is a sequential container
		*/
		bool is_sequential_container() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored value is the same type as requested type
		*/
		template<typename T>
		REFLECTPP_INLINE bool is_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		explicit operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two variant are the same value
		* @param rhs
		*/
		bool operator!=(const variant& rhs) const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two variant are the same value
		* @param rhs
		*/
		bool operator==(const variant& rhs) const REFLECTPP_NOEXCEPT;

	private:

		details::variant_data m_data;
	};
}

#include "details/impl/variant.inl"

/**
* @}
*/
