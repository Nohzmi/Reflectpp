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

		registry::registry() = default;
		registry::~registry() = default;

		type* registry::add_base(type* _type, type* base) noexcept
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

		factory* registry::add_factory(size_t id, ConstructorT constructor, CopyT copy, DestructorT destructor) noexcept
		{
			for (auto& it : m_factories)
				if (it.first == id)
					return nullptr;

			factory* _factory{ new factory(constructor, copy, destructor) };
			m_factories.emplace(id, _factory);

			return _factory;
		}

		property* registry::add_property(type* _type, const char* name, size_t offset, type* property_type) noexcept
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

		property* registry::add_property(type* _type, const char* name, GetterT getter, SetterT setter, type* property_type) noexcept
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

		type* registry::add_type(factory* _factory, size_t size, type_info* typeinfo) noexcept
		{
			for (auto& type : m_types)
				if (type->get_id() == typeinfo->get_id())
					return nullptr;

			type* _type{ new type(_factory, size, typeinfo) };
			m_types.emplace_back(_type);

			return _type;
		}

		type_info* registry::add_type_info(size_t id, const char* name) noexcept
		{
			for (auto& typeinfo : m_type_infos)
				if (typeinfo->get_id() == id)
					return nullptr;

			type_info* typeinfo{ new type_info(id, name) };
			m_type_infos.emplace_back(typeinfo);

			return typeinfo;
		}

		bool registry::cast(type* _type, type* otype) const noexcept
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

		registry& registry::get_instance() noexcept
		{
			return m_instance;
		}

		factory* registry::get_factory(size_t id) const noexcept
		{
			for (auto& it : m_factories)
				if (it.first == id)
					return it.second.get();

			return nullptr;
		}

		type* registry::get_type(size_t id) const noexcept
		{
			for (auto& type : m_types)
				if (type->get_id() == id)
					return type.get();

			return nullptr;
		}

		size_t registry::get_type_id(type* _type) const noexcept
		{
			return _type->get_id();
		}

		type_info* registry::get_type_info(size_t id) const noexcept
		{
			for (auto& typeinfo : m_type_infos)
				if (typeinfo->get_id() == id)
					return typeinfo.get();

			return nullptr;
		}

		const char* registry::get_type_name(type* _type) const noexcept
		{
			return _type->get_name();
		}

		property* registry::get_property(size_t id) const noexcept
		{
			for (auto& prop : m_properties)
				if (prop->get_id() == id)
					return prop.get();

			return nullptr;
		}
	}
}
