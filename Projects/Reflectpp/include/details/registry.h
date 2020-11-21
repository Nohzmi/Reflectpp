// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file registry.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

#include "details/assert.h"
#include "details/hasher.h"
#include "details/platform.h"
#include "details/utilities.h"

namespace reflectpp
{
	class factory;
	class property;
	class registration;
	class type;
	class type_info;
	class variant;

	namespace details
	{
#pragma warning(push)
#pragma warning(disable: 4251)

		class REFLECTPP_API registry final
		{
			friend factory;
			friend property;
			friend registration;
			friend type;
			friend type_info;
			friend variant;

			using ConstructorT = void* (*)();
			using CopyT = void* (*)(void*);
			using DestructorT = void (*)(void*);
			using GetterT = std::function<void* (void*, bool&)>;
			using SetterT = std::function<void(void*, void*)>;

		private:

			registry();
			~registry();
			registry(const registry&) = delete;
			registry(registry&&) REFLECTPP_NOEXCEPT = delete;
			registry& operator=(const registry&) = delete;
			registry& operator=(registry&&) REFLECTPP_NOEXCEPT = delete;

			template<typename T>
			type* add_base(type* type) REFLECTPP_NOEXCEPT;

			type* add_base(type* _type, type* base) REFLECTPP_NOEXCEPT;

			factory* add_factory(size_t id, ConstructorT constructor, CopyT copy, DestructorT destructor) REFLECTPP_NOEXCEPT;

			template<typename T, typename propertyT, typename U = typename std::remove_cv_t<propertyT>>
			property* add_property(type* type, const char* name, propertyT T::* addr) REFLECTPP_NOEXCEPT;

			property* add_property(type* _type, const char* name, size_t offset, type* property_type) REFLECTPP_NOEXCEPT;

			template<typename T, typename propertyT, typename U = typename std::remove_cv_t<std::remove_reference_t<propertyT>>>
			property* add_property(type* type, const char* name, propertyT(T::* getter)() const, void(T::* setter)(propertyT)) REFLECTPP_NOEXCEPT;

			property* add_property(type* _type, const char* name, GetterT getter, SetterT setter, type* property_type) REFLECTPP_NOEXCEPT;

			template<typename T>
			type* add_type() REFLECTPP_NOEXCEPT;

			type* add_type(factory* factory, size_t size, type_info* type_info) REFLECTPP_NOEXCEPT;

			type_info* add_type_info(size_t id, const char* name) REFLECTPP_NOEXCEPT;

			template<typename T, typename U, typename V = typename std::remove_pointer_t<T>>
			std::remove_pointer_t<T>* cast(U* object) REFLECTPP_NOEXCEPT;

			bool cast(type* t, type* otype) const REFLECTPP_NOEXCEPT;

			static registry& get_instance() REFLECTPP_NOEXCEPT;

			template<typename T>
			factory* get_factory() REFLECTPP_NOEXCEPT;

			factory* get_factory(size_t id) const REFLECTPP_NOEXCEPT;

			template<typename T>
			type* get_type() REFLECTPP_NOEXCEPT;

			template<typename T>
			type* get_type(T* object) REFLECTPP_NOEXCEPT;

			type* get_type(size_t id) const REFLECTPP_NOEXCEPT;

			template<typename T>
			type* get_type_with_initialization() REFLECTPP_NOEXCEPT;

			size_t get_type_id(type* _type) const REFLECTPP_NOEXCEPT;

			template<typename T>
			type_info* get_type_info() REFLECTPP_NOEXCEPT;

			type_info* get_type_info(size_t id) const REFLECTPP_NOEXCEPT;

			const char* get_type_name(type* _type) const REFLECTPP_NOEXCEPT;

			property* get_property(size_t id) const REFLECTPP_NOEXCEPT;

			std::unordered_map<size_t, std::unique_ptr<factory>> m_factories;
			std::vector<std::unique_ptr<property>> m_properties;
			std::vector<std::unique_ptr<type_info>> m_type_infos;
			std::vector<std::unique_ptr<type>> m_types;

			static registry m_instance;
		};

#pragma warning (pop)
	}
}

#include "details/inline/registry.inl"
