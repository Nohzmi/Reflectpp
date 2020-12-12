// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "details/registry.h"

#include "factory.h"
#include "property.h"
#include "type.h"
#include "type_info.h"

namespace reflectpp
{
	namespace details
	{
		registry registry::m_instance;

		registry::registry()
		{
			auto constructor = []() -> void* { return nullptr; };
			auto copy = [](void*) -> void* { return nullptr; };
			auto destructor = [](void*) {};

			factory* _factory{ new factory(constructor, copy, destructor) };
			type_info* _type_info{ new type_info(0, "") };
			type* _type{ new type(_factory, 0, _type_info) };
			property* prop { new property(nullptr, 0, "", 0, _type, nullptr, _type) };

			m_factories.emplace(0, _factory);
			m_properties.emplace_back(prop);
			m_type_infos.emplace_back(_type_info);
			m_types.emplace_back(_type);
		}

		registry::~registry() = default;

		type* registry::add_base_impl(type* _type, type* base) REFLECTPP_NOEXCEPT
		{
			for (auto& it : _type->get_base_classes().m_vector)
				if (it->get_id() == base->get_id())
					return nullptr;

			if (_type->get_base_classes().empty())
				_type->m_hierarchy_id = base->m_hierarchy_id;

			if (!_type->get_base_classes().empty())
			{
				auto updateHierarchy = [](type* type, size_t hierarchyID, auto& lambda)
				{
					if (type->m_hierarchy_id == hierarchyID)
						return;

					type->m_hierarchy_id = hierarchyID;

					for (auto& it : type->get_base_classes().m_vector)
						lambda(it, hierarchyID, lambda);

					for (auto& it : type->get_derived_classes().m_vector)
						lambda(it, hierarchyID, lambda);
				};

				updateHierarchy(base, _type->m_hierarchy_id, updateHierarchy);
			}

			base->m_derived_types.m_vector.emplace_back(_type);
			_type->m_base_types.m_vector.emplace_back(base);
			_type->m_properties.m_vector.insert(_type->m_properties.m_vector.cbegin(),
				base->m_properties.m_vector.cbegin(), base->m_properties.m_vector.cbegin());

			return base;
		}

		factory* registry::add_factory_impl(size_t id, ConstructorT constructor, CopyT copy, DestructorT destructor) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_factories)
				if (it.first == id)
					return nullptr;

			factory* _factory{ new factory(constructor, copy, destructor) };
			m_factories.emplace(id, _factory);

			return _factory;
		}

		property* registry::add_property_impl(type* _type, const char* name, size_t offset, type* property_type) REFLECTPP_NOEXCEPT
		{
			size_t id{ details::hash(name) };

			for (auto& prop : _type->get_properties().m_vector)
				if (prop->get_id() == id)
					return nullptr;

			property* prop{ new property(nullptr, id, name, offset, property_type, nullptr, _type) };
			m_properties.emplace_back(prop);

			_type->m_properties.m_vector.emplace_back(prop);

			return prop;
		}

		property* registry::add_property_impl(type* _type, const char* name, GetterT getter, SetterT setter, type* property_type) REFLECTPP_NOEXCEPT
		{
			size_t id{ details::hash(name)};

			for (auto& prop : _type->get_properties().m_vector)
				if (prop->get_id() == id)
					return nullptr;

			property* prop{ new property(getter, id, name, 0, property_type, setter, _type) };
			m_properties.emplace_back(prop);

			_type->m_properties.m_vector.emplace_back(prop);

			return prop;
		}

		type* registry::add_type_impl(factory* _factory, size_t size, type_info* _type_info) REFLECTPP_NOEXCEPT
		{
			for (auto& type : m_types)
				if (type->get_id() == _type_info->get_id())
					return nullptr;

			type* _type{ new type(_factory, size, _type_info) };
			m_types.emplace_back(_type);

			return _type;
		}

		type_info* registry::add_type_info(size_t id, const char* name) REFLECTPP_NOEXCEPT
		{
			for (auto& type_info : m_type_infos)
				if (type_info->get_id() == id)
					return nullptr;

			type_info* _type_info{ new type_info(id, name) };
			m_type_infos.emplace_back(_type_info);

			return _type_info;
		}

		bool registry::cast_impl(type* _type, type* otype) const REFLECTPP_NOEXCEPT
		{
			if (_type->m_hierarchy_id != otype->m_hierarchy_id)
				return false;

			auto isBaseOf = [](type* _type, size_t id, auto& lambda) -> bool
			{
				if (_type->get_id() == id)
					return true;

				bool res{ false };

				for (auto& it : _type->get_base_classes().m_vector)
					res |= lambda(it, id, lambda);

				return res;
			};

			return isBaseOf(otype, _type->get_id(), isBaseOf);
		}

		registry& registry::get_instance() REFLECTPP_NOEXCEPT
		{
			return m_instance;
		}

		factory* registry::get_factory_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_factories)
				if (it.first == id)
					return it.second.get();

			return nullptr;
		}

		type* registry::get_type_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			for (auto& type : m_types)
				if (type->get_id() == id)
					return type.get();

			return nullptr;
		}

		type_info* registry::get_type_info_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			for (auto& type_info : m_type_infos)
				if (type_info->get_id() == id)
					return type_info.get();

			return nullptr;
		}

		property* registry::get_property_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			for (auto& prop : m_properties)
				if (prop->get_id() == id)
					return prop.get();

			return nullptr;
		}
	}
}