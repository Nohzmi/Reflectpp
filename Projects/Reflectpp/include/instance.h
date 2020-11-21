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
	class type;

	/**
	* Generic factory class used in reflection \n
	* Independent of the reflection
	*/
	class REFLECTPP_API instance final
	{
		friend property;

	public:

		instance() = default;
		~instance() = default;
		instance(const instance&) = default;
		instance(instance&&) REFLECTPP_NOEXCEPT = default;
		instance& operator=(const instance&) = default;
		instance& operator=(instance&&) REFLECTPP_NOEXCEPT = default;

		/**
		* Creates an instance from a variant
		* @param var
		*/
		instance(const variant& var) REFLECTPP_NOEXCEPT;

		/**
		* Create an instance from an object
		* @param object
		*/
		template<typename T, typename U = std::enable_if_t<!std::is_same_v<variant, T> && !std::is_pointer_v<T>>>
		instance(T& object) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		explicit operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type of the stored value
		*/
		type& get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

	private:
		
		variant m_var;
	};
}

#include "details/inline/instance.inl"


/*RTTR_INLINE instance() RTTR_NOEXCEPT;
60
64     
76     template < typename T, typename Tp = decay_instance_t<T>>
77     RTTR_INLINE instance(T & data) RTTR_NOEXCEPT;
78
85     template < typename Target_Type>
86     RTTR_INLINE Target_Type * try_convert() const RTTR_NOEXCEPT;
87
93    

/**
* @}
*/
