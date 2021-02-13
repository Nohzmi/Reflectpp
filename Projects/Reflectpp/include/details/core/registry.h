// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file registry.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <cstdint>
#include <tuple>

#include "details/core/hasher.h"
#include "details/core/log.hpp"
#include "details/core/platform.h"
#include "details/core/specifiers.h"
#include "details/core/type_info_helper.h"
#include "details/data/associative_view_data.h"
#include "details/data/enumeration_data.h"
#include "details/data/factory_data.h"
#include "details/data/property_data.h"
#include "details/data/sequential_view_data.h"
#include "details/data/type_data.h"
#include "details/data/type_info_data.h"
#include "details/data/utility_data.h"
#include "details/data/wrapper_data.h"
#include "details/lambda/associative_view_lambda.h"
#include "details/lambda/factory_lambda.h"
#include "details/lambda/property_lambda.h"
#include "details/lambda/sequential_view_lambda.h"
#include "details/lambda/utility_lambda.h"
#include "details/lambda/wrapper_lambda.h"

namespace reflectpp
{
	namespace details
	{
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

			template<typename T, typename PropertyT>
			REFLECTPP_INLINE void add_property(type_data* type, const char* name, PropertyT T::* addr, size_t specifiers) REFLECTPP_NOEXCEPT;

			template<typename T, typename PropertyT>
			REFLECTPP_INLINE void add_property(type_data* type, const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT), size_t specifiers) REFLECTPP_NOEXCEPT;

			template<typename T>
			REFLECTPP_INLINE type_data* add_type() REFLECTPP_NOEXCEPT;

			template<typename EnumT>
			REFLECTPP_INLINE void add_value(type_data* type, const char* name, EnumT value) REFLECTPP_NOEXCEPT;

			std::vector<type_data*> get_arithmetic_types() REFLECTPP_NOEXCEPT;

			template<typename T>
			REFLECTPP_INLINE factory_data* get_factory() REFLECTPP_NOEXCEPT;

			static registry& get_instance() REFLECTPP_NOEXCEPT;

			template<typename T>
			REFLECTPP_INLINE type_data* get_type() REFLECTPP_NOEXCEPT;

			template<typename T>
			REFLECTPP_INLINE type_data* get_type(T&& object) REFLECTPP_NOEXCEPT;

			type_data* get_type_by_name(const char* name) const REFLECTPP_NOEXCEPT;

			template<typename T>
			REFLECTPP_INLINE type_info_data* get_type_info() REFLECTPP_NOEXCEPT;

			std::vector<type_data*> get_types() const REFLECTPP_NOEXCEPT;

		private:

			void add_base_impl(type_data* type, type_data* base) const REFLECTPP_NOEXCEPT;

			enumeration_data* add_enumeration_impl(size_t id) REFLECTPP_NOEXCEPT;

			property_data* add_property_impl(type_data* type, size_t id, const char* name) REFLECTPP_NOEXCEPT;

			template<typename T>
			REFLECTPP_INLINE type_data* add_type_impl() REFLECTPP_NOEXCEPT;

			type_data* add_type_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT;

			void add_value_impl(enumeration_data* enumeration, const char* name, void* value) const REFLECTPP_NOEXCEPT;

			template<typename T>
			REFLECTPP_INLINE associative_view_data* get_associative_view_impl() REFLECTPP_NOEXCEPT;

			associative_view_data* get_associative_view_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT;

			factory_data* get_factory_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT;

			template<typename T>
			REFLECTPP_INLINE sequential_view_data* get_sequential_view_impl() REFLECTPP_NOEXCEPT;

			sequential_view_data* get_sequential_view_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT;

			type_data* get_type_impl(size_t id) const REFLECTPP_NOEXCEPT;

			type_info_data* get_type_info_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT;

			template<typename T>
			REFLECTPP_INLINE utility_data* get_utility_impl() REFLECTPP_NOEXCEPT;

			utility_data* get_utility_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT;

			template<typename T>
			REFLECTPP_INLINE wrapper_data* get_wrapper_impl() REFLECTPP_NOEXCEPT;

			wrapper_data* get_wrapper_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT;

#pragma warning(push)
#pragma warning(disable: 4251)

			std::tuple<bool, float, double, long double, int8_t, int16_t, int32_t, long, int64_t, uint8_t, uint16_t, uint32_t, unsigned long, uint64_t, char, char16_t, char32_t, wchar_t> m_arithmetic_types;
			std::unordered_map<size_t, std::unique_ptr<associative_view_data>> m_associative_views;
			std::unordered_map<size_t, std::unique_ptr<enumeration_data>> m_enumerations;
			std::unordered_map<size_t, std::unique_ptr<factory_data>> m_factories;
			std::vector<std::unique_ptr<property_data>> m_properties;
			std::unordered_map<size_t, std::unique_ptr<sequential_view_data>> m_sequential_views;
			std::unordered_map<size_t, std::unique_ptr<type_info_data>> m_type_infos;
			std::unordered_map<size_t, std::unique_ptr<type_data>> m_types;
			std::unordered_map<size_t, std::unique_ptr<utility_data>> m_utilities;
			std::unordered_map<size_t, std::unique_ptr<wrapper_data>> m_wrappers;

#pragma warning (pop)

			static registry m_instance;
		};
	}
}

#include "details/core/impl/registry.inl"
