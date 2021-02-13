// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "details/core/registry.h"

namespace reflectpp
{
	namespace details
	{
		registry registry::m_instance;

		registry::registry() = default;

		registry::~registry()
		{
			for (auto& it : m_enumerations)
				for (auto& ptr : it.second->m_values)
					it.second->m_underlying_type->m_factory->m_destructor(ptr);
		}

		std::vector<type_data*> registry::get_arithmetic_types() REFLECTPP_NOEXCEPT
		{
			std::vector<type_data*> types;
			std::apply([&](auto... args){ (types.emplace_back(get_type<decltype(args)>()), ...); }, m_arithmetic_types);
			return types;
		}

		registry& registry::get_instance() REFLECTPP_NOEXCEPT
		{
			return m_instance;
		}

		type_data* registry::get_type_by_name(const char* name) const REFLECTPP_NOEXCEPT
		{
			auto it{ m_types.find(hash(name)) };
			return it != m_types.end() ? it->second.get() : nullptr;
		}

		std::vector<type_data*> registry::get_types() const REFLECTPP_NOEXCEPT
		{
			std::vector<type_data*> types;

			for (auto& it : m_types)
				types.emplace_back(it.second.get());

			return types;
		}

		void registry::add_base_impl(type_data* type, type_data* base) const REFLECTPP_NOEXCEPT
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

		enumeration_data* registry::add_enumeration_impl(size_t id) REFLECTPP_NOEXCEPT
		{
			auto data{ new enumeration_data() };
			m_enumerations.emplace(id, data);
			return data;
		}

		property_data* registry::add_property_impl(type_data* type, size_t id, const char* name) REFLECTPP_NOEXCEPT
		{
			for (auto& it : type->m_properties)
			{
				if (it->m_id == id)
				{
					REFLECTPP_LOG("%s already registered", name);
					return nullptr;
				}
			}

			auto data{ new property_data() };
			m_properties.emplace_back(data);
			type->m_properties.emplace_back(data);
			return data;
		}

		type_data* registry::add_type_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_types)
			{
				if (it.first == id)
				{
					created = false;
					return it.second.get();
				}
			}

			created = true;
			auto data{ new type_data() };
			m_types.emplace(id, data);
			return data;
		}

		void registry::add_value_impl(enumeration_data* enumeration, const char* name, void* value) const REFLECTPP_NOEXCEPT
		{
			enumeration->m_names.emplace_back(name);
			enumeration->m_values.emplace_back(value);
		}

		associative_view_data* registry::get_associative_view_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_associative_views)
			{
				if (it.first == id)
				{
					created = false;
					return it.second.get();
				}
			}

			created = true;
			auto data{ new associative_view_data() };
			m_associative_views.emplace(id, data);
			return data;
		}

		factory_data* registry::get_factory_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_factories)
			{
				if (it.first == id)
				{
					created = false;
					return it.second.get();
				}
			}

			created = true;
			auto data{ new factory_data() };
			m_factories.emplace(id, data);
			return data;
		}

		sequential_view_data* registry::get_sequential_view_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT
		{

			for (auto& it : m_sequential_views)
			{
				if (it.first == id)
				{
					created = false;
					return it.second.get();
				}
			}

			created = true;
			auto data{ new sequential_view_data() };
			m_sequential_views.emplace(id, data);
			return data;
		}

		type_data* registry::get_type_impl(size_t id) const REFLECTPP_NOEXCEPT
		{
			auto it{ m_types.find(id) };

			if (it != m_types.end())
				return it->second.get();

			return nullptr;
		}

		type_info_data* registry::get_type_info_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_type_infos)
			{
				if (it.first == id)
				{
					created = false;
					return it.second.get();
				}
			}

			created = true;
			auto data{ new type_info_data() };
			m_type_infos.emplace(id, data);
			return data;
		}

		utility_data* registry::get_utility_impl(size_t id, bool& created) REFLECTPP_NOEXCEPT
		{
			for (auto& it : m_utilities)
			{
				if (it.first == id)
				{
					created = false;
					return it.second.get();
				}
			}

			created = true;
			auto data{ new utility_data() };
			m_utilities.emplace(id, data);
			return data;
		}
	}
}
