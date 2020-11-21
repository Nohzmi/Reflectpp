// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type_info.h
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
	* Equivalent to std::type_info \n
	* Independent of the reflection
	*/
	class REFLECTPP_API type_info final
	{
		friend details::registry;

	public:

		type_info() = delete;
		~type_info() = default;
		type_info(const type_info&) = default;
		type_info(type_info&&) REFLECTPP_NOEXCEPT = default;
		type_info& operator=(const type_info&) = default;
		type_info& operator=(type_info&&) REFLECTPP_NOEXCEPT = default;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		bool operator==(const type_info& rhs) const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		bool operator!=(const type_info& rhs) const REFLECTPP_NOEXCEPT;

		/**
		* Get type info of the requested type
		*/
		template<typename T>
		static type_info& get() REFLECTPP_NOEXCEPT;

		/**
		* Returns id of this type info
		*/
		size_t get_id() const REFLECTPP_NOEXCEPT;

		/**
		* Returns name of this type info
		*/
		const char* get_name() const REFLECTPP_NOEXCEPT;

	private:

		type_info(size_t id, const char* name) REFLECTPP_NOEXCEPT;

		size_t m_id;
		const char* m_name;
	};
}

#include "details/inline/type_info.inl"

/**
* @}
*/
