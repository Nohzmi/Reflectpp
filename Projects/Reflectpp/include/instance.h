// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file instance.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "variant.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	/**
	* Class used to forwarding the instance of an object
	*/
	class REFLECTPP_API instance final
	{
	public:

		instance() = default;
		~instance();
		instance(const instance&);
		instance(instance&&) REFLECTPP_NOEXCEPT;
		instance& operator=(const instance&);
		instance& operator=(instance&&) REFLECTPP_NOEXCEPT;
		explicit operator variant*() const REFLECTPP_NOEXCEPT;

		/**
		* Creates an instance from a variant
		* @param var
		*/
		instance(const variant& var) REFLECTPP_NOEXCEPT;

		/**
		* Creates an instance from a variant
		* @param var
		*/
		instance(variant&& var) REFLECTPP_NOEXCEPT;

		/**
		* Create an instance from an object
		* @param object
		*/
		template<typename T, typename = std::enable_if_t<!std::is_same_v<variant, details::decay<T>> && !std::is_same_v<instance, details::decay<T>> && !std::is_pointer_v<std::decay_t<T>>>>
		REFLECTPP_INLINE instance(T& object) REFLECTPP_NOEXCEPT;

		/**
		* Returns the type of the stored value
		*/
		type get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		explicit operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* This function will try to convert the underlying instance to the given type
		* When the conversion succeeds, a valid pointer will be returned., otherwise a nullptr
		*/
		template<typename T>
		REFLECTPP_INLINE T* try_convert() const REFLECTPP_NOEXCEPT;

	private:
		
		bool m_is_owner{ false };
		variant* m_variant{ nullptr };
	};
}

#include "details/impl/instance.inl"

/**
* @}
*/
