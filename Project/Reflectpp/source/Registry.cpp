// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Registry.h"

#include <functional>
#include <string>
#include "Type.h"

namespace Reflectpp
{
	Registry Registry::m_Value;

	Registry::Registry() = default;
	Registry::~Registry() = default;

	Registry& Registry::Instance() noexcept
	{
		return m_Value;
	}

	Type* Registry::AddBase(Type* type, Type* base) noexcept
	{
		for (auto& it : type->GetBaseTypes().m_Vector)
			if (it->GetID() == base->GetID())
				return nullptr;

		if (type->GetBaseTypes().empty())
			type->m_HierarchyID = base->m_HierarchyID;

		if (!type->GetBaseTypes().empty())
		{
			auto updateHierarchy = [](Type* type, size_t hierarchyID, auto& lambda)
			{
				if (type->m_HierarchyID == hierarchyID)
					return;

				type->m_HierarchyID = hierarchyID;

				for (auto& it : type->GetBaseTypes().m_Vector)
					lambda(it, hierarchyID, lambda);

				for (auto& it : type->GetDerivedTypes().m_Vector)
					lambda(it, hierarchyID, lambda);
			};

			updateHierarchy(base, type->m_HierarchyID, updateHierarchy);
		}

		base->m_DerivedTypes.m_Vector.emplace_back(type);
		type->m_BaseTypes.m_Vector.emplace_back(base);
		type->m_Properties.m_Vector.insert(type->m_Properties.m_Vector.cbegin(),
			base->m_Properties.m_Vector.cbegin(), base->m_Properties.m_Vector.cbegin());

		return base;
	}

	Factory* Registry::AddFactory(size_t id, void* (*ctor)(), void* (*copy)(void*), void(*dtor)(void*)) noexcept
	{
		for (auto& it : m_Factories)
			if (it.first == id)
				return nullptr;

		Factory* factory{ new Factory(ctor, copy, dtor) };
		m_Factories.emplace(id, factory);

		return factory;
	}

	Property* Registry::AddProperty(Type* type, const char* name, size_t offset, Type* ptype) noexcept
	{
		std::hash<std::string> hasher;
		size_t id{ hasher(name) };

		for (auto& prop : type->GetProperties().m_Vector)
			if (prop->GetID() == id)
				return nullptr;

		Property* prop{ new Property(id, name, offset, ptype) };
		m_Properties.emplace_back(prop);

		type->m_Properties.m_Vector.emplace_back(prop);

		return prop;
	}

	Type* Registry::AddType(Factory* factory, size_t size, TypeInfo* typeinfo) noexcept
	{
		for (auto& type : m_Types)
			if (type->GetID() == typeinfo->GetID())
				return nullptr;

		Type* type{ new Type(factory, size, typeinfo) };
		m_Types.emplace_back(type);

		return type;
	}

	TypeInfo* Registry::AddTypeInfo(size_t id, const char* name) noexcept
	{
		for (auto& typeinfo : m_TypeInfos)
			if (typeinfo->GetID() == id)
				return nullptr;

		TypeInfo* typeinfo{ new TypeInfo(id, name) };
		m_TypeInfos.emplace_back(typeinfo);

		return typeinfo;
	}

	bool Registry::Cast(Type* type, Type* otype) const noexcept
	{
		if (type->m_HierarchyID != otype->m_HierarchyID)
			return false;

		auto isBaseOf = [](Type* type, size_t id, auto& lambda) -> bool
		{
			if (type->GetID() == id)
				return true;

			bool res{ false };

			for (auto& it : type->GetBaseTypes().m_Vector)
				res |= lambda(it, id, lambda);

			return res;
		};

		return isBaseOf(otype, type->GetID(), isBaseOf);
	}

	Factory* Registry::GetFactory(size_t id) const noexcept
	{
		for (auto& it : m_Factories)
			if (it.first == id)
				return it.second.get();

		return nullptr;
	}

	Type* Registry::GetType(size_t id) const noexcept
	{
		for (auto& type : m_Types)
			if (type->GetID() == id)
				return type.get();

		return nullptr;
	}

	TypeInfo* Registry::GetTypeInfo(size_t id) const noexcept
	{
		for (auto& typeinfo : m_TypeInfos)
			if (typeinfo->GetID() == id)
				return typeinfo.get();

		return nullptr;
	}

	Property* Registry::GetProperty(size_t id) const noexcept
	{
		for (auto& prop : m_Properties)
			if (prop->GetID() == id)
				return prop.get();

		return nullptr;
	}
}
