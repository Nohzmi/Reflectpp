// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "details/registry.h"

#include "details/sequence_function.h"
#include "details/sequence_type.h"
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

		type* registry::add_base_impl(type* base_type, type* _type) REFLECTPP_NOEXCEPT
		{
			for (auto& it : _type->get_base_classes().m_vector)
				if (it->get_id() == base_type->get_id())
					return nullptr;

			if (_type->get_base_classes().empty())
				_type->m_hierarchy_id = base_type->m_hierarchy_id;

			if (!_type->get_base_classes().empty())
			{
				auto updateHierarchy = [](size_t hierarchyID, auto& lambda, type* type)
				{
					if (type->m_hierarchy_id == hierarchyID)
						return;

					type->m_hierarchy_id = hierarchyID;

					for (auto& it : type->get_base_classes().m_vector)
						lambda(hierarchyID, lambda, it);

					for (auto& it : type->get_derived_classes().m_vector)
						lambda(hierarchyID, lambda, it);
				};

				updateHierarchy(_type->m_hierarchy_id, updateHierarchy, base_type);
			}

			base_type->m_derived_types.m_vector.emplace_back(_type);
			_type->m_base_types.m_vector.emplace_back(base_type);
			_type->m_properties.m_vector.insert(_type->m_properties.m_vector.cbegin(),
				base_type->m_properties.m_vector.cbegin(), base_type->m_properties.m_vector.cbegin());

			return base_type;
		}

		factory* registry::add_factory_impl(ConstructorT constructor, CopyT copy, DestructorT destructor, size_t id) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_factories)
				if (it.first == id)
					return nullptr;

			factory* _factory{ new factory(constructor, copy, destructor) };
			m_factories.emplace(id, _factory);

			return _factory;
		}

		property* registry::add_property_impl(GetterT getter, const char* name, type* property_type, SetterT setter, size_t specifiers, type* _type) REFLECTPP_NOEXCEPT
		{
			size_t id{ details::hash(name) };

			for (auto& prop : _type->get_properties().m_vector)
				if (prop->get_id() == id)
					return nullptr;

			property* prop{ new property(getter, id, name, property_type, setter, specifiers, _type) };
			m_properties.emplace_back(prop);

			_type->m_properties.m_vector.emplace_back(prop);

			return prop;
		}

		sequence_function* registry::add_sequence_function_impl(ClearT clear, EraseT erase, GetT get, size_t id, InsertT insert, ResizeT resize, SetT set, SizeT size) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_sequence_functions)
				if (it.first == id)
					return nullptr;

			sequence_function* _sequence_function{ new sequence_function(clear, erase, get, insert, resize, set, size) };
			m_sequence_functions.emplace(id, _sequence_function);

			return _sequence_function;
		}

		type* registry::add_sequence_type_impl(type* data_type, factory* _factory, sequence_function* _sequence_function, size_t size, type_info* _type_info) REFLECTPP_NOEXCEPT
		{
			for (auto& type : m_types)
				if (type->get_id() == _type_info->get_id())
					return nullptr;

			type* _type{ new sequence_type(data_type, _factory, _sequence_function, size, _type_info) };
			m_types.emplace_back(_type);

			return _type;
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

		bool registry::cast_impl(type* object_type, type* _type) const REFLECTPP_NOEXCEPT
		{
			if (_type->m_hierarchy_id != object_type->m_hierarchy_id)
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

			return isBaseOf(object_type, _type->get_id(), isBaseOf);
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

		sequence_function* registry::get_sequence_function_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_sequence_functions)
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
