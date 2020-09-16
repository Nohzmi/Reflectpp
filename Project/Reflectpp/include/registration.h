// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file registration.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/platform.h"

/**
* @addtogroup Reflectpp
* @{
*/

#define REGISTRATION							\
static void register_function() noexcept;		\
namespace										\
{												\
    struct register_class final					\
    {											\
        register_class()						\
        {										\
            register_function();				\
        }										\
    };											\
}												\
static const register_class register_obj;		\
void register_function() noexcept


namespace reflectpp { class registry; }
class type;

/**
* Allow to register a type in reflection \n
* and his base types and properties too
*/
class REFLECTPP_API registration final
{
	friend reflectpp::registry;

public:

	registration() = delete;
	~registration() = default;
	registration(const registration&) = default;
	registration(registration&&) noexcept = default;
	registration& operator=(const registration&) = default;
	registration& operator=(registration&&) noexcept = default;

	/**
	* Register the base class of the current type
	*/
	template<typename T>
	registration base() noexcept;

	/**
	* Register a type in reflection
	*/
	template<typename T>
	static registration class_() noexcept;

	/**
	* Register a property of the current type
	* @param name
	* @param addr
	*/
	template<typename T, typename PropertyT>
	registration property(const char* name, PropertyT T::* addr) noexcept;

	/**
	* Register a property of the current type
	* @param name
	* @param getter
	* @param setter
	*/
	template<typename T, typename PropertyT>
	registration property(const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT)) noexcept;

private:

	registration(type* type) noexcept;

	type* m_type;
};

/**
* @}
*/
