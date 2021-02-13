// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type.h
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

		explicit type(details::type_data* data) REFLECTPP_NOEXCEPT;
		explicit operator details::type_data*() const REFLECTPP_NOEXCEPT;

		/**
		* Creates an instance of the current type
		*/
		variant create() const REFLECTPP_NOEXCEPT;

		/**
		* Destroys the contained object in the variant
		* Return whether of not the destructor of the object could be invoked
		* @param var
		*/
		bool destroy(variant& var) const REFLECTPP_NOEXCEPT;

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
		* Returns the type object with the given name
		*/ 
		static type get_by_name(const char* name) REFLECTPP_NOEXCEPT;

		/**
		* Returns derived types of this type
		*/
		std::vector<type> get_derived_classes() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the enumerator if this type is an enum type
		*/
		enumeration get_enumeration() const REFLECTPP_NOEXCEPT;

		/**
		* Returns factory of this type
		*/
		factory get_factory() const REFLECTPP_NOEXCEPT;

		/**
		* Returns id of this type
		*/
		size_t get_id() const REFLECTPP_NOEXCEPT;

		/**
		* Returns name of this type
		*/
		const char* get_name() const REFLECTPP_NOEXCEPT;

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
		size_t get_sizeof() const REFLECTPP_NOEXCEPT;

		/**
		* Returns type info of this type
		*/
		type_info get_type_info() const REFLECTPP_NOEXCEPT;

		/**
		* Returns a list of all registered type objects
		*/
		static std::vector<type> get_types() REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type represents an arithmetic type
		*/
		bool is_arithmetic() const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type is an associative container
		*/
		bool is_associative_container() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not this type is the base class from the given type
		*/
		template<typename T>
		REFLECTPP_INLINE bool is_base_of() REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type is the base class from the given type
		* @param other
		*/
		bool is_base_of(const type& other) const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type represents a class
		*/
		bool is_class() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not this type is derived from the given type
		*/
		template<typename T>
		REFLECTPP_INLINE bool is_derived_of() REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type is derived from the given type
		* @param other
		*/
		bool is_derived_of(const type& other) const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not the given type represents an enumeration
		*/
		bool is_enumeration() const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type is a sequential container
		*/
		bool is_sequential_container() const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

		/*
		* Returns whether or not this type is valid
		*/
		explicit operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		bool operator!=(const type& rhs) const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		bool operator==(const type& rhs) const REFLECTPP_NOEXCEPT;

	private:

		details::type_data* m_data{ nullptr };
	};
}

#include "details/impl/type.inl"

/**
* @}
*/
