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
		friend details::registry;

		using ConstructorT = void* (*)();
		using CopyT = void* (*)(void*);
		using DestructorT = void (*)(void*);

	public:

		factory() = delete;
		~factory() = default;
		factory(const factory&) = default;
		factory(factory&&) REFLECTPP_NOEXCEPT = default;
		factory& operator=(const factory&) = default;
		factory& operator=(factory&&) REFLECTPP_NOEXCEPT = default;

		/**
		* Returns a pointer on created object
		*/
		void* construct() const REFLECTPP_NOEXCEPT;

		/**
		* Returns a pointer on copied object
		* @param object
		*/
		void* copy(void* object) const REFLECTPP_NOEXCEPT;

		/**
		* Destroys given object
		* @param object
		*/
		void destroy(void* object) const REFLECTPP_NOEXCEPT;

		/**
		* Get factory of the requested type
		*/
		template<typename T>
		static factory& get() REFLECTPP_NOEXCEPT;

	private:

		factory(ConstructorT constructor, CopyT copy, DestructorT destructor) REFLECTPP_NOEXCEPT;

		ConstructorT m_constructor;
		CopyT m_copy;
		DestructorT m_destructor;
	};
}

#include "details/inline/factory.inl"

/**
* @}
*/
