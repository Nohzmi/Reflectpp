// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file registration.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/registry.h"

/**
* @addtogroup Reflectpp
* @{
*/

#define REGISTRATION									\
static void register_function() REFLECTPP_NOEXCEPT;		\
namespace												\
{														\
	struct register_class final							\
	{													\
		register_class()								\
		{												\
			register_function();						\
		}												\
	};													\
}														\
static const register_class register_obj;				\
void register_function() REFLECTPP_NOEXCEPT

namespace reflectpp
{
	/**
	* Allow to register information in reflection \n
	* Like class, properties, ... etc
	*/
	class REFLECTPP_API registration final
	{
	public:

		registration() = delete;
		~registration() = default;
		registration(const registration&) = default;
		registration(registration&&) REFLECTPP_NOEXCEPT = default;
		registration& operator=(const registration&) = default;
		registration& operator=(registration&&) REFLECTPP_NOEXCEPT = default;
		explicit registration(details::type_data* type) REFLECTPP_NOEXCEPT;

		/**
		* Register the base class of the current type
		*/
		template<typename T>
		REFLECTPP_INLINE registration base() REFLECTPP_NOEXCEPT;

		/**
		* Register a type in reflection
		*/
		template<typename T>
		REFLECTPP_INLINE static registration class_() REFLECTPP_NOEXCEPT;

		/**
		* Register a property of the current type
		* @param name
		* @param addr
		* @param specifiers
		*/
		template<typename T, typename PropertyT>
		REFLECTPP_INLINE registration property(const char* name, PropertyT T::* addr, size_t specifiers = Exposed | Serialized) REFLECTPP_NOEXCEPT;

		/**
		* Register a property of the current type
		* @param name
		* @param getter
		* @param setter
		* @param specifiers
		*/
		template<typename T, typename PropertyT>
		REFLECTPP_INLINE registration property(const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT), size_t specifiers = Exposed | Serialized) REFLECTPP_NOEXCEPT;

	private:

		details::type_data* m_type{ nullptr };
	};
}

#include "details/inline/registration.inl"

/**
* @}
*/
