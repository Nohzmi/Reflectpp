// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_info.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/registry.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	/**
	* Equivalent to std::type_info \n
	* Independent of the reflection
	*/
	class REFLECTPP_API type_info final
	{
	public:

		type_info() = default;
		~type_info() = default;
		type_info(const type_info&) = default;
		type_info(type_info&&) REFLECTPP_NOEXCEPT = default;
		type_info& operator=(const type_info&) = default;
		type_info& operator=(type_info&&) REFLECTPP_NOEXCEPT = default;
		explicit type_info(details::type_info_data* data) REFLECTPP_NOEXCEPT;

		/**
		* Get type info of the requested type
		*/
		template<typename T>
		REFLECTPP_INLINE static type_info get() REFLECTPP_NOEXCEPT;

		/**
		* Returns id of this type info
		*/
		size_t get_id() const REFLECTPP_NOEXCEPT;

		/**
		* Returns name of this type info
		*/
		const char* get_name() const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type info is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type info is valid
		*/
		explicit operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		bool operator!=(const type_info& rhs) const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		bool operator==(const type_info& rhs) const REFLECTPP_NOEXCEPT;

	private:

		details::type_info_data* m_data{ nullptr };
	};
}

#include "details/impl/type_info.inl"

/**
* @}
*/
