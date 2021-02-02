// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file property.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/forward.h"
#include "details/macros.h"
#include "details/platform.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	/**
	* Show a property of a class in reflection
	*/
	class REFLECTPP_API property final
	{
	public:

		property() = default;
		~property() = default;
		property(const property&) = default;
		property(property&&) REFLECTPP_NOEXCEPT = default;
		property& operator=(const property&) = default;
		property& operator=(property&&) REFLECTPP_NOEXCEPT = default;
		explicit property(details::property_data* data) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two property are the same
		* @param rhs
		*/
		bool operator==(const property& rhs) const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two property are the same
		* @param rhs
		*/
		bool operator!=(const property& rhs) const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this property info is valid
		*/
		explicit operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type of the class or struct that declares this property
		*/
		type get_declaring_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns id of this property
		*/
		size_t get_id() const REFLECTPP_NOEXCEPT;

		/**
		* Returns name of this property
		*/
		const char* get_name() const REFLECTPP_NOEXCEPT;

		/**
		* Returns specifiers of this property
		*/
		size_t get_specifiers() const REFLECTPP_NOEXCEPT;

		/**
		* Returns type of this property
		*/
		type get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns a variant that correspond to the property of the given object
		* @param object
		*/
		variant get_value(instance object) const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this property is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

		/**
		* Set the value of the property of the given object
		* Returns whether or not the operation was successful
		* @param object
		* @param arg
		*/
		bool set_value(instance object, argument arg) const REFLECTPP_NOEXCEPT;

	private:

		details::property_data* m_data{ nullptr };
	};
}

/**
* @}
*/
