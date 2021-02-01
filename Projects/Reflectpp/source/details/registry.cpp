// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "details/registry.h"

namespace reflectpp
{
	namespace details
	{
		registry registry::m_instance;

		registry::registry() = default;
		registry::~registry() = default;

		registry& registry::get_instance() REFLECTPP_NOEXCEPT
		{
			return m_instance;
		}

		associative_view_data* registry::add_associative_view_impl(size_t id, associative_view_data* associative_view) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_associative_views)
				if (it.first == id)
					return nullptr;

			m_associative_views.emplace(id, new associative_view_data(*associative_view));
			return m_associative_views.at(id).get();
		}

		void registry::add_base_impl(type_data* type, type_data* base) REFLECTPP_NOEXCEPT
		{
			for (auto& it : type->m_base_types)
			{
				if (it == base)
				{
					REFLECTPP_LOG("%s already registered as base", base->m_type_info->m_name);
					return;
				}
			}

			if (type->m_base_types.empty())
			{
				type->m_hierarchy_id = base->m_hierarchy_id;
			}
			else
			{
				auto updateHierarchy = [](type_data* type, size_t hierarchyID, auto& lambda)
				{
					if (type->m_hierarchy_id == hierarchyID)
						return;

					type->m_hierarchy_id = hierarchyID;

					for (auto& it : type->m_base_types)
						lambda(it, hierarchyID, lambda);

					for (auto& it : type->m_derived_types)
						lambda(it, hierarchyID, lambda);
				};

				updateHierarchy(base, type->m_hierarchy_id, updateHierarchy);
			}

			base->m_derived_types.emplace_back(type);
			type->m_base_types.emplace_back(base);
			type->m_properties.insert(type->m_properties.cbegin(), base->m_properties.cbegin(), base->m_properties.cend());
		}

		factory_data* registry::add_factory_impl(size_t id, factory_data* factory) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_factories)
				if (it.first == id)
					return nullptr;

			m_factories.emplace(id, new factory_data(*factory));
			return m_factories.at(id).get();
		}

		void registry::add_property_impl(type_data* type, property_data* property) REFLECTPP_NOEXCEPT
		{
			for (auto& it : type->m_properties)
			{
				if (it->m_id == property->m_id)
				{
					REFLECTPP_LOG("%s already registered", property->m_name);
					return;
				}
			}

			m_properties.emplace_back(new property_data(*property));
			type->m_properties.emplace_back(m_properties.back().get());
		}

		sequential_view_data* registry::add_sequential_view_impl(size_t id, sequential_view_data* sequential_view) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_sequential_views)
				if (it.first == id)
					return nullptr;

			m_sequential_views.emplace(id, new sequential_view_data(*sequential_view));
			return m_sequential_views.at(id).get();
		}

		type_data* registry::add_type_impl(type_data* type) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_types)
				if (it.get()->m_type_info->m_id == type->m_type_info->m_id)
					return nullptr;

			m_types.emplace_back(new type_data(*type));
			return m_types.back().get();
		}

		type_info_data* registry::add_type_info_impl(type_info_data* type_info) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_type_infos)
				if (it.get()->m_id == type_info->m_id)
					return nullptr;

			m_type_infos.emplace_back(new type_info_data(*type_info));
			return m_type_infos.back().get();
		}

		bool registry::cast_impl(type_data* object, type_data* type) const REFLECTPP_NOEXCEPT
		{
			if (type->m_hierarchy_id != object->m_hierarchy_id)
				return false;

			auto isBaseOf = [](type_data* object, type_data* type, auto& lambda) -> bool
			{
				if (object == type)
					return true;

				bool res{ false };

				for (auto& it : object->m_base_types)
					res |= lambda(it, type, lambda);

				return res;
			};

			return isBaseOf(object, type, isBaseOf);
		}

		associative_view_data* registry::get_associative_view_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_associative_views)
				if (it.first == id)
					return it.second.get();

			return nullptr;
		}

		factory_data* registry::get_factory_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_factories)
				if (it.first == id)
					return it.second.get();

			return nullptr;
		}

		sequential_view_data* registry::get_sequential_view_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_sequential_views)
				if (it.first == id)
					return it.second.get();

			return nullptr;
		}

		type_data* registry::get_type_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_types)
				if (it->m_type_info->m_id == id)
					return it.get();

			return nullptr;
		}

		type_info_data* registry::get_type_info_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_type_infos)
				if (it->m_id == id)
					return it.get();

			return nullptr;
		}

		property_data* registry::get_property_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_properties)
				if (it->m_id == id)
					return it.get();

			return nullptr;
		}
	}
}
