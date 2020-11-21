// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file type.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/registry.h"
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
		type(type&&) noexcept = default;
		type& operator=(const type&) = delete;
		type& operator=(type&&) noexcept = default;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		bool operator==(const type& rhs) const noexcept;

		/**
		* Returns whether or not two types are the same
		* @param rhs
		*/
		bool operator!=(const type& rhs) const noexcept;

		/**
		* Allows to cast between class hierarchies up, down and side
		* @param object
		*/
		template<typename T, typename U>
		static T cast(U* object) noexcept;

		/**
		* Returns a variant of this type
		*/
		variant create() const;

		/**
		* Returns requested type representation
		*/
		template<typename T>
		static type& get() noexcept;

		/**
		* Returns requested type representation
		* @param object
		*/
		template<typename T>
		static type& get(T* object) noexcept;

		/**
		* Returns base types of this type
		*/
		range<type>& get_base_classes() const noexcept;

		/**
		* Returns derived types of this type
		*/
		range<type>& get_derived_classes() const noexcept;

		/**
		* Returns factory of this type
		*/
		factory& get_factory() const noexcept;

		/**
		* Returns id of this type
		*/
		size_t get_id() const noexcept;

		/**
		* Returns name of this type
		*/
		const char* get_name() const noexcept;

		/**
		* Returns property by name of this type
		* @param name
		*/
		property& get_property(const char* name) const noexcept;

		/**
		* Returns all property of this type
		*/
		range<property>& get_properties() const noexcept;

		/**
		* Returns size of this type
		*/
		size_t get_sizeof() const noexcept;

		/**
		* Returns type info of this type
		*/
		type_info& get_type_info() const noexcept;

	private:

		type(factory* factory, size_t size, type_info* type_info) noexcept;

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
