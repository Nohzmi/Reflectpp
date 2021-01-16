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
	class property;
	class serializer;
	class type;

	/**
	* Class used to forwarding the instance of an object
	*/
	class REFLECTPP_API instance final
	{
		friend property;
		friend serializer;

	public:

		instance() = delete;
		REFLECTPP_INLINE ~instance();
		REFLECTPP_INLINE instance(const instance&);
		instance(instance&&) REFLECTPP_NOEXCEPT = default;
		REFLECTPP_INLINE instance& operator=(const instance&);
		instance& operator=(instance&&) REFLECTPP_NOEXCEPT = default;

		/**
		* Creates an instance from a variant
		* @param var
		*/
		REFLECTPP_INLINE instance(const variant& var) REFLECTPP_NOEXCEPT;

		/**
		* Create an instance from an object
		* @param object
		*/
		template<typename T, typename U = std::enable_if_t<!std::is_same_v<variant, details::decay<T>> && !std::is_same_v<instance, details::decay<T>> && !std::is_pointer_v<std::decay_t<T>>>>
		REFLECTPP_INLINE instance(T& object) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		REFLECTPP_INLINE explicit operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type of the stored value
		*/
		type get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		REFLECTPP_INLINE bool is_valid() const REFLECTPP_NOEXCEPT;

	private:
		
		bool m_is_owner{ false };
		variant* m_variant{ nullptr };
	};
}

#include "details/inline/instance.inl"

/**
* @}
*/
