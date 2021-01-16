// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type.h
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
	class factory;
	class property;
	class type_info;
	class variant;

#pragma warning(push)
#pragma warning(disable: 4251)

	/**
	* The basic type representation
	*/
	class REFLECTPP_API type
	{
	public:

		type() = default;
		~type() = default;
		type(const type&) = default;
		type(type&&) REFLECTPP_NOEXCEPT = default;
		type& operator=(const type&) = default;
		type& operator=(type&&) REFLECTPP_NOEXCEPT = default;
		REFLECTPP_INLINE explicit type(details::type_data* data) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		REFLECTPP_INLINE bool operator==(const type& rhs) const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		REFLECTPP_INLINE bool operator!=(const type& rhs) const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type is valid
		*/
		REFLECTPP_INLINE operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Allows to cast between class hierarchies up, down and side
		* @param object
		*/
		template<typename T, typename U>
		REFLECTPP_INLINE static T cast(U* object) REFLECTPP_NOEXCEPT;

		/**
		* Returns a variant of this type
		*/
		variant create() const REFLECTPP_NOEXCEPT;

		/**
		* Returns requested type representation
		*/
		template<typename T>
		REFLECTPP_INLINE static type get() REFLECTPP_NOEXCEPT;

		/**
		* Returns requested type representation
		* @param object
		*/
		template<typename T>
		REFLECTPP_INLINE static type get(T&& object) REFLECTPP_NOEXCEPT;

		/**
		* Returns base types of this type
		*/
		std::vector<type> get_base_classes() const REFLECTPP_NOEXCEPT;

		/**
		* Returns derived types of this type
		*/
		std::vector<type> get_derived_classes() const REFLECTPP_NOEXCEPT;

		/**
		* Returns factory of this type
		*/
		factory get_factory() const REFLECTPP_NOEXCEPT;

		/**
		* Returns id of this type
		*/
		REFLECTPP_INLINE size_t get_id() const REFLECTPP_NOEXCEPT;

		/**
		* Returns name of this type
		*/
		REFLECTPP_INLINE const char* get_name() const REFLECTPP_NOEXCEPT;

		/**
		* Returns property by name of this type
		* @param name
		*/
		property get_property(const char* name) const REFLECTPP_NOEXCEPT;

		/**
		* Returns all property of this type
		*/
		std::vector<property> get_properties() const REFLECTPP_NOEXCEPT;

		/**
		* Returns size of this type
		*/
		REFLECTPP_INLINE size_t get_sizeof() const REFLECTPP_NOEXCEPT;

		/**
		* Returns type info of this type
		*/
		type_info get_type_info() const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type is a sequencial container
		*/
		REFLECTPP_INLINE bool is_sequential_container() const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type is valid
		*/
		REFLECTPP_INLINE bool is_valid() const REFLECTPP_NOEXCEPT;

	private:

		details::type_data* m_data{ nullptr };
	};

#pragma warning (pop)
}

#include "details/inline/type.inl"

/**
* @}
*/
