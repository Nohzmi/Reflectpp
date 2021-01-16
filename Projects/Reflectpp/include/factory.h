// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file factory.h
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
	/**
	* Generic factory class used in reflection \n
	* Independent of the reflection
	*/
	class REFLECTPP_API factory final
	{
	public:

		factory() = default;
		~factory() = default;
		factory(const factory&) = default;
		factory(factory&&) REFLECTPP_NOEXCEPT = default;
		factory& operator=(const factory&) = default;
		factory& operator=(factory&&) REFLECTPP_NOEXCEPT = default;
		REFLECTPP_INLINE explicit factory(details::factory_data* data) REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this factory is valid
		*/
		REFLECTPP_INLINE operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Returns a pointer on created object
		*/
		REFLECTPP_INLINE void* construct() const REFLECTPP_NOEXCEPT;

		/**
		* Returns a pointer on copied object
		* @param object
		*/
		REFLECTPP_INLINE void* copy(void* object) const REFLECTPP_NOEXCEPT;

		/**
		* Destroys given object
		* @param object
		*/
		REFLECTPP_INLINE void destroy(void* object) const REFLECTPP_NOEXCEPT;

		/**
		* Get factory of the requested type
		*/
		template<typename T>
		REFLECTPP_INLINE static factory get() REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this factory is valid
		*/
		REFLECTPP_INLINE bool is_valid() const REFLECTPP_NOEXCEPT;

	private:

		details::factory_data* m_data{ nullptr };
	};
}

#include "details/inline/factory.inl"

/**
* @}
*/
