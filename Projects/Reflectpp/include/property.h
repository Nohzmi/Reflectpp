// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file property.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/registry.h"
#include "variant.h"
#include "instance.h"
#include "argument.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	class type;

#pragma warning(push)
#pragma warning(disable: 4251)

	/**
	* Show a property of a class in reflection
	*/
	class REFLECTPP_API property final
	{
		friend details::registry;

		using GetterT = std::function<void* (void*, bool&)>;
		using SetterT = std::function<void(void*, void*)>;

	public:

		property() = delete;
		~property() = default;
		property(const property&) = delete;
		property(property&&) REFLECTPP_NOEXCEPT = default;
		property& operator=(const property&) = delete;
		property& operator=(property&&) REFLECTPP_NOEXCEPT = default;

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
		type& get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns a variant that correspond to the property of the given object
		* @param object
		*/
		variant get_value(const instance& object) const REFLECTPP_NOEXCEPT;

		/**
		* Set the value of the property of the given object
		* @param object
		* @param arg
		*/
		void set_value(const instance& object, const argument& arg) const REFLECTPP_NOEXCEPT;

	private:

		property(GetterT getter, size_t id, const char* name, type* property_type, SetterT setter, size_t specifiers, type* type) REFLECTPP_NOEXCEPT;

		GetterT m_getter;
		size_t m_id;
		const char* m_name;
		type* m_property_type;
		SetterT m_setter;
		size_t m_specifiers;
		type* m_type;
	};

#pragma warning (pop)
}

/**
* @}
*/
