// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file property.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <functional>
#include "details/platform.h"
#include "variant.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp { class registry; }
class type;

#pragma warning(push)
#pragma warning(disable: 4251)

/**
* Show a property of a class in reflection
*/
class REFLECTPP_API property final
{
	friend reflectpp::registry;

	using GetterT = std::function<void* (void*, bool&)>;
	using SetterT = std::function<void(void*, void*)>;

public:

	property() = delete;
	~property() = default;
	property(const property&) = delete;
	property(property&&) noexcept = default;
	property& operator=(const property&) = delete;
	property& operator=(property&&) noexcept = default;

	/**
	* Returns id of this property
	*/
	size_t get_id() const noexcept;

	/**
	* Returns name of this property
	*/
	const char* get_name() const noexcept;

	/**
	* Returns offset of this property
	*/
	size_t get_offset() const noexcept;

	/**
	* Returns type of this property
	*/
	type& get_type() const noexcept;

	/**
	* Returns value of the property from an object of the type that contains it
	* @param object
	*/
	template<typename T>
	variant get_value(T* object) const;

	/**
	* Returns value of the property from an object of the type that contains it
	* @param object
	*/
	variant get_value(const variant& object) const;

private:

	property(GetterT getter, size_t id, const char* name, size_t offset, type* property_type, SetterT setter, type* type) noexcept;

	GetterT m_getter;
	size_t m_id;
	const char* m_name;
	size_t m_offset;
	type* m_property_type;
	SetterT m_setter;
	type* m_type;
};

#pragma warning (pop)

/**
* @}
*/
