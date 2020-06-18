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

	Type* Registry::AddBase(Type* type, Type* base) noexcept
	{
		// TODO clean

		for (const Type* t : type->m_BaseTypes)
			if (*t == *base)
				return nullptr;

		if (type->m_BaseTypes.empty())
			type->m_HierarchyID = base->m_HierarchyID;

		if (!type->m_BaseTypes.empty())
		{
			auto updateHierarchy = [](const Type* type, size_t hierarchyID, const auto& lambda)
			{
				if (type->m_HierarchyID == hierarchyID)
					return;

				const_cast<Type*>(type)->m_HierarchyID = hierarchyID;

				for (const Type* baseType : type->m_BaseTypes)
					lambda(baseType, hierarchyID, lambda);

				for (const Type* derivedType : type->m_DerivedTypes)
					lambda(derivedType, hierarchyID, lambda);
			};

			updateHierarchy(base, type->m_HierarchyID, updateHierarchy);
		}

		base->m_DerivedTypes.emplace_back(type);
		type->m_BaseTypes.emplace_back(base);
		type->m_Properties.insert(type->m_Properties.cbegin(), base->m_Properties.cbegin(), base->m_Properties.cbegin());

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

		for (auto& prop : type->GetProperties())
			if (prop->GetID() == id)
				return nullptr;

		Property* prop{ new Property(id, name, offset, ptype) };
		m_Properties.emplace_back(prop);

		type->m_Properties.emplace_back(prop);

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

	Registry& Registry::Instance() noexcept
	{
		return m_Value;
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
