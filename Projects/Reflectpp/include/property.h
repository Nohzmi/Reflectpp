// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file property.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/registry.h"
#include "variant.h"

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
		* Returns offset of this property
		*/
		size_t get_offset() const REFLECTPP_NOEXCEPT;

		/**
		* Returns type of this property
		*/
		type& get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns value of the property from an object of the type that contains it
		* @param object
		*/
		template<typename T>
		variant get_value(T* object) const REFLECTPP_NOEXCEPT;

		/**
		* Returns value of the property from an object of the type that contains it
		* @param object
		*/
		variant get_value(const variant& object) const REFLECTPP_NOEXCEPT;

	private:

		property(GetterT getter, size_t id, const char* name, size_t offset, type* property_type, SetterT setter, type* type) REFLECTPP_NOEXCEPT;

		GetterT m_getter;
		size_t m_id;
		const char* m_name;
		size_t m_offset;
		type* m_property_type;
		SetterT m_setter;
		type* m_type;
	};

#pragma warning (pop)
}

#include "details/inline/property.inl"

/**
* @}
*/
