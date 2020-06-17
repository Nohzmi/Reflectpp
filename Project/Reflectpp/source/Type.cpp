// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Type.h"
#include <vld.h>//////////////////////////////////////////////

namespace Reflectpp
{
	void* Factory::Construct() const noexcept
	{
		return m_Constructor();
	}

	void* Factory::Copy(void* object) const noexcept
	{
		return m_Copy(object);
	}

	void Factory::Destroy(void* object) const noexcept
	{
		m_Destructor(object);
	}

	Factory::Factory(ConstructorT constructor, CopyT copy, DestructorT destructor) noexcept :
		m_Constructor{ constructor },
		m_Copy{ copy },
		m_Destructor{ destructor }
	{
	}

	bool TypeInfo::operator==(const TypeInfo& rhs) const noexcept
	{
		return m_ID == rhs.m_ID;
	}

	bool TypeInfo::operator!=(const TypeInfo& rhs) const noexcept
	{
		return m_ID != rhs.m_ID;
	}

	size_t TypeInfo::GetID() const noexcept
	{
		return m_ID;
	}

	const char* TypeInfo::GetName() const noexcept
	{
		return m_Name;
	}

	TypeInfo::TypeInfo(size_t id, const char* name) noexcept :
		m_ID{ id },
		m_Name{ name }
	{
	}

	Property::Property(size_t id, const char* name, size_t offset, const Type* type) noexcept :
		m_ID{ id },
		m_Name{ name },
		m_Offset{ offset },
		m_Type{ type }
	{
	}

	size_t Property::GetID() const noexcept
	{
		return m_ID;
	}

	const char* Property::GetName() const noexcept
	{
		return m_Name;
	}

	size_t Property::GetOffset() const noexcept
	{
		return m_Offset;
	}

	const Type* Property::GetType() const noexcept
	{
		return m_Type;
	}

	Type::PropertyDatabase Type::m_PropertyDatabase;
	Type::TypeDatabase Type::m_TypeDatabase;

	bool Type::operator==(const Type& rhs) const noexcept
	{
		return m_TypeInfo == rhs.m_TypeInfo;
	}

	bool Type::operator!=(const Type& rhs) const noexcept
	{
		return m_TypeInfo != rhs.m_TypeInfo;
	}

	const std::vector<const Type*>& Type::GetBaseTypes() const noexcept
	{
		return m_BaseTypes;
	}

	const std::vector<const Type*>& Type::GetDerivedTypes() const noexcept
	{
		return m_DerivedTypes;
	}

	const Factory& Type::GetFactory() const noexcept
	{
		return m_Factory;
	}

	size_t Type::GetID() const noexcept
	{
		return m_TypeInfo.GetID();
	}

	const char* Type::GetName() const noexcept
	{
		return m_TypeInfo.GetName();
	}

	const Property* Type::GetProperty(const char* name) const noexcept
	{
		std::hash<std::string> hasher;
		size_t id{ hasher(name) };

		for (const Property* prop : m_Properties)
			if (prop->GetID() == id)
				return prop;

		Reflectpp::Assert(false, "Type::GetProperty : %s isn't registered\n", name);

		return nullptr;
	}

	const std::vector<const Property*>& Type::GetProperties() const noexcept
	{
		return m_Properties;
	}

	size_t Type::GetSize() const noexcept
	{
		return m_Size;
	}

	const TypeInfo& Type::GetTypeInfo() const noexcept
	{
		return m_TypeInfo;
	}

	Type::Type(const Factory& factory, size_t size, const TypeInfo& typeinfo) noexcept :
		m_Factory{ factory },
		m_HierarchyID{ typeinfo.GetID() },
		m_Size{ size },
		m_TypeInfo{ typeinfo }
	{
	}

	Type* Type::AddBase(Type* base) noexcept
	{
		for (const Type* type : m_BaseTypes)
			if (*type == *base)
				return nullptr;

		if (m_BaseTypes.empty())
			m_HierarchyID = base->m_HierarchyID;

		if (!m_BaseTypes.empty())
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

			updateHierarchy(base, m_HierarchyID, updateHierarchy);
		}

		base->m_DerivedTypes.emplace_back(this);
		m_BaseTypes.emplace_back(base);
		m_Properties.insert(m_Properties.cbegin(), base->m_Properties.cbegin(), base->m_Properties.cbegin());

		return base;
	}

	Property* Type::AddProperty(const char* name, size_t offset, const Type* type) noexcept
	{
		const std::hash<std::string> hasher;
		const size_t id{ hasher(name) };

		for (const Property* prop : GetProperties())
			if (prop->GetID() == id)
				return nullptr;

		Property* prop{ new Property(id, name, offset, type) };
		m_Properties.emplace_back(prop);
		m_PropertyDatabase.emplace_back(prop);

		return prop;
	}

	Type* Type::AddType(const Factory& factory, size_t size, const TypeInfo& typeinfo) noexcept
	{
		const auto it{ m_TypeDatabase.find(typeinfo.GetID()) };

		if (it != m_TypeDatabase.cend())
			return nullptr;

		Type* type{ new Type(factory, size, typeinfo) };
		m_TypeDatabase.emplace(typeinfo.GetID(), type);

		return type;
	}

	Type* Type::FindType(size_t id) noexcept
	{
		const auto it{ m_TypeDatabase.find(id) };
		return (it != m_TypeDatabase.cend()) ? it->second.get() : nullptr;
	}
}
