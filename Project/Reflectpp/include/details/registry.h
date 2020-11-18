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

#include "details/platform.h"

namespace reflectpp
{
	class factory;
	class property;
	class type;
	class type_info;

	namespace details
	{
#pragma warning(push)
#pragma warning(disable: 4251)

		class REFLECTPP_API registry final
		{
			using ConstructorT = void* (*)();
			using CopyT = void* (*)(void*);
			using DestructorT = void (*)(void*);
			using GetterT = std::function<void* (void*, bool&)>;
			using SetterT = std::function<void(void*, void*)>;

		public:

			registry(const registry&) = delete;
			registry(registry&&) noexcept = delete;
			registry& operator=(const registry&) = delete;
			registry& operator=(registry&&) noexcept = delete;

			template<typename T>
			type* add_base(type* type) noexcept;

			template<typename T, typename propertyT, typename U = typename std::remove_cv_t<propertyT>>
			property* add_property(type* type, const char* name, propertyT T::* addr) noexcept;

			template<typename T, typename propertyT, typename U = typename std::remove_cv_t<std::remove_reference_t<propertyT>>>
			property* add_property(type* type, const char* name, propertyT(T::* getter)() const, void(T::* setter)(propertyT)) noexcept;

			template<typename T>
			type* add_type() noexcept;

			template<typename T, typename U, typename V = typename std::remove_pointer_t<T>>
			std::remove_pointer_t<T>* cast(U* object) noexcept;

			template<typename T>
			factory* get_factory() noexcept;

			template<typename T>
			type* get_type() noexcept;

			template<typename T>
			type* get_type(T* object) noexcept;

			template<typename T>
			type_info* get_type_info() noexcept;

			static registry& get_instance() noexcept;

		private:

			registry();
			~registry();

			type* add_base(type* _type, type* base) noexcept;
			factory* add_factory(size_t id, ConstructorT constructor, CopyT copy, DestructorT destructor) noexcept;
			property* add_property(type* _type, const char* name, size_t offset, type* propertytype) noexcept;
			property* add_property(type* _type, const char* name, GetterT getter, SetterT setter, type* propertytype) noexcept;
			type* add_type(factory* factory, size_t size, type_info* type_info) noexcept;
			type_info* add_type_info(size_t id, const char* name) noexcept;
			bool cast(type* t, type* otype) const noexcept;
			factory* get_factory(size_t id) const noexcept;
			type* get_type(size_t id) const noexcept;
			type_info* get_type_info(size_t id) const noexcept;
			property* get_property(size_t id) const noexcept;

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
