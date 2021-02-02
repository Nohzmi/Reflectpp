// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file enumeration.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/macros.h"
#include "details/platform.h"
#include "details/type_data.h"

/**
* @addtogroup Reflectpp
* @{
*/
namespace reflectpp
{
	/**
	* The enumeration class provides several meta information about an enum
	*/
	class REFLECTPP_API enumeration
	{
	public:

		enumeration() = default;
		~enumeration() = default;
		enumeration(const enumeration&) = default;
		enumeration(enumeration&&) REFLECTPP_NOEXCEPT = default;
		enumeration& operator=(const enumeration&) = default;
		enumeration& operator=(enumeration&&) REFLECTPP_NOEXCEPT = default;
		explicit enumeration(details::type_data* data) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two enumeration are the same
		* @param rhs
		*/
		bool operator==(const enumeration& rhs) const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two enumeration are the same
		* @param rhs
		*/
		bool operator!=(const enumeration& rhs) const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this enumeration is valid
		*/
		explicit operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type of the class or struct that declares this enumeration 
		*/
		type get_declaring_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the declared name of this enumeration
		*/
		const char* get_name() const REFLECTPP_NOEXCEPT;

		/**
		* Returns all enum names registered for this enumeration
		*/
		std::vector<const char*> get_names() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type object of this enumeration
		*/
		type get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the underlying type (int, unsigned int, etc.) of this enumeration
		*/
		type get_underlying_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns all enum values registered for this enumeration
		*/
		std::vector<variant> get_values() const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this enumeration is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the value of the given enumeration name, or an empty variant if the name is not defined
		*/
		variant name_to_value(const char* name) const REFLECTPP_NOEXCEPT;

		/**
		* Returns the name of the given enumeration value, or an empty string if the value is not defined. 
		*/
		const char* value_to_name(argument value) const REFLECTPP_NOEXCEPT;

	private:

		details::type_data* m_data{ nullptr };
	};
}

/**
* @}
*/
