// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "range.h"
#include "variant.h"

/**
* @addtogroup Reflectpp
* @{
*/
namespace reflectpp
{
	class factory;
	class property;
	class type_info;

#pragma warning(push)
#pragma warning(disable: 4251)

	/**
	* The basic type representation
	*/
	class REFLECTPP_API type final
	{
		friend details::registry;

	public:

		type() = delete;
		~type() = default;
		type(const type&) = delete;
		type(type&&) REFLECTPP_NOEXCEPT = default;
		type& operator=(const type&) = delete;
		type& operator=(type&&) REFLECTPP_NOEXCEPT = default;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		bool operator==(const type& rhs) const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		bool operator!=(const type& rhs) const REFLECTPP_NOEXCEPT;

		/**
		* Allows to cast between class hierarchies up, down and side
		* @param object
		*/
		template<typename T, typename U>
		static T cast(U* object) REFLECTPP_NOEXCEPT;

		/**
		* Returns a variant of this type
		*/
		variant create() const;

		/**
		* Returns requested type representation
		*/
		template<typename T>
		static type& get() REFLECTPP_NOEXCEPT;

		/**
		* Returns requested type representation
		* @param object
		*/
		template<typename T>
		static type& get(T* object) REFLECTPP_NOEXCEPT;

		/**
		* Returns base types of this type
		*/
		range<type>& get_base_classes() const REFLECTPP_NOEXCEPT;

		/**
		* Returns derived types of this type
		*/
		range<type>& get_derived_classes() const REFLECTPP_NOEXCEPT;

		/**
		* Returns factory of this type
		*/
		factory& get_factory() const REFLECTPP_NOEXCEPT;

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
		property& get_property(const char* name) const REFLECTPP_NOEXCEPT;

		/**
		* Returns all property of this type
		*/
		range<property>& get_properties() const REFLECTPP_NOEXCEPT;

		/**
		* Returns size of this type
		*/
		size_t get_sizeof() const REFLECTPP_NOEXCEPT;

		/**
		* Returns type info of this type
		*/
		type_info& get_type_info() const REFLECTPP_NOEXCEPT;

	private:

		type(factory* factory, size_t size, type_info* type_info) REFLECTPP_NOEXCEPT;

		range<type> m_base_types;
		range<type> m_derived_types;
		factory* m_factory;
		size_t m_hierarchy_id;
		range<property> m_properties;
		size_t m_size;
		type_info* m_type_info;
	};

#pragma warning (pop)
}

#include "details/inline/type.inl"

/**
* @}
*/
