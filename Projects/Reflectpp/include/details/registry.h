// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file registry.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <memory>

#include "details/associative_view_data.h"
#include "details/enumeration_data.h"
#include "details/factory_data.h"
#include "details/hasher.hpp"
#include "details/log.hpp"
#include "details/platform.h"
#include "details/property_data.h"
#include "details/sequential_view_data.h"
#include "details/specifiers.h"
#include "details/type_data.h"
#include "details/type_info_data.h"
#include "details/utilities.hpp"
#include "custom_associative_container.hpp"
#include "custom_sequence_container.hpp"

namespace reflectpp
{
	namespace details
	{
#pragma warning(push)
#pragma warning(disable: 4251)

		class REFLECTPP_API registry final
		{
		public:

			registry();
			~registry();
			registry(const registry&) = delete;
			registry(registry&&) REFLECTPP_NOEXCEPT = delete;
			registry& operator=(const registry&) = delete;
			registry& operator=(registry&&) REFLECTPP_NOEXCEPT = delete;

			template<typename T>
			REFLECTPP_INLINE void add_base(type_data* type) REFLECTPP_NOEXCEPT;
			template<typename T>
			REFLECTPP_INLINE type_data* add_enumeration(const char* name) REFLECTPP_NOEXCEPT;
			template<typename T, typename propertyT>
			REFLECTPP_INLINE void add_property(type_data* type, const char* name, propertyT T::* addr, size_t specifiers) REFLECTPP_NOEXCEPT;
			template<typename T, typename propertyT>
			REFLECTPP_INLINE void add_property(type_data* type, const char* name, propertyT(T::* getter)() const,  void(T::* setter)(propertyT), size_t specifiers) REFLECTPP_NOEXCEPT;
			template<typename T>
			REFLECTPP_INLINE type_data* add_type() REFLECTPP_NOEXCEPT;
			template<typename EnumT>
			REFLECTPP_INLINE void add_value(type_data* type, const char* name, EnumT value) REFLECTPP_NOEXCEPT;
			template<typename T, typename U>
			REFLECTPP_INLINE std::remove_pointer_t<T>* cast(U* object) REFLECTPP_NOEXCEPT;
			template<typename T>
			REFLECTPP_INLINE factory_data* get_factory() REFLECTPP_NOEXCEPT;
			template<typename T>
			REFLECTPP_INLINE type_data* get_type() REFLECTPP_NOEXCEPT;
			template<typename T>
			REFLECTPP_INLINE type_data* get_type(T&& object) REFLECTPP_NOEXCEPT;
			template<typename T>
			REFLECTPP_INLINE type_info_data* get_type_info() REFLECTPP_NOEXCEPT;

			static registry& get_instance() REFLECTPP_NOEXCEPT;

		private:

			template<typename T>
			REFLECTPP_INLINE associative_view_data* get_associative_view_impl() REFLECTPP_NOEXCEPT;
			template<typename T>
			REFLECTPP_INLINE sequential_view_data* get_sequential_view_impl() REFLECTPP_NOEXCEPT;
			template<typename T>
			REFLECTPP_INLINE type_data* get_type_impl() REFLECTPP_NOEXCEPT;

			associative_view_data* add_associative_view_impl(size_t id) REFLECTPP_NOEXCEPT;
			void add_base_impl(type_data* type, type_data* base) REFLECTPP_NOEXCEPT; //
			enumeration_data* add_enumeration_impl(size_t id) REFLECTPP_NOEXCEPT;
			factory_data* add_factory_impl(size_t id) REFLECTPP_NOEXCEPT;
			void add_property_impl(type_data* type, property_data* property) REFLECTPP_NOEXCEPT; //
			sequential_view_data* add_sequential_view_impl(size_t id) REFLECTPP_NOEXCEPT;
			type_data* add_type_impl(type_data* type) REFLECTPP_NOEXCEPT; //
			type_info_data* add_type_info_impl(size_t id) REFLECTPP_NOEXCEPT;
			bool cast_impl(type_data* object, type_data* type) const REFLECTPP_NOEXCEPT;
			associative_view_data* get_associative_view_impl(size_t id) const REFLECTPP_NOEXCEPT;
			enumeration_data* get_enumeration_impl(size_t id) const REFLECTPP_NOEXCEPT;
			factory_data* get_factory_impl(size_t id) const REFLECTPP_NOEXCEPT;
			sequential_view_data* get_sequential_view_impl(size_t id) const REFLECTPP_NOEXCEPT;
			type_data* get_type_impl(size_t id) const REFLECTPP_NOEXCEPT;
			type_info_data* get_type_info_impl(size_t id) const REFLECTPP_NOEXCEPT;
			property_data* get_property_impl(size_t id) const REFLECTPP_NOEXCEPT;

			std::unordered_map<size_t, std::unique_ptr<associative_view_data>> m_associative_views;
			std::unordered_map<size_t, std::unique_ptr<enumeration_data>> m_enumerations;
			std::unordered_map<size_t, std::unique_ptr<factory_data>> m_factories;
			std::vector<std::unique_ptr<property_data>> m_properties;
			std::unordered_map<size_t, std::unique_ptr<sequential_view_data>> m_sequential_views;
			std::unordered_map<size_t, std::unique_ptr<type_info_data>> m_type_infos;
			std::vector<std::unique_ptr<type_data>> m_types;

			static registry m_instance;
		};

#pragma warning (pop)
	}
}

#include "details/inline/registry.inl"
