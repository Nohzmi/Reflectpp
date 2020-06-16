// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Type.h"

namespace Reflectpp
{
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

	Type::Type(ConstructorT constructor, CopyT copyConstructor, DestructorT destructor, size_t id, const char* name, size_t size) :
		m_Constructor{ constructor },
		m_CopyConstructor{ copyConstructor },
		m_Destructor{ destructor },
		m_HierarchyID{ id },
		m_ID{ id },
		m_Name{ name },
		m_Size{ size }
	{
	}

	bool Type::operator==(const Type& rhs) const noexcept
	{
		return m_ID == rhs.m_ID;
	}

	bool Type::operator!=(const Type& rhs) const noexcept
	{
		return m_ID != rhs.m_ID;
	}

	const std::vector<const Type*> Type::GetBaseTypes() const noexcept
	{
		return m_BaseTypes;
	}

	Type::ConstructorT Type::GetConstructor() const noexcept
	{
		return m_Constructor;
	}

	Type::CopyT Type::GetCopyConstructor() const noexcept
	{
		return m_CopyConstructor;
	}

	const std::vector<const Type*> Type::GetDerivedTypes() const noexcept
	{
		return m_DerivedTypes;
	}

	Type::DestructorT Type::GetDestructor() const noexcept
	{
		return m_Destructor;
	}

	const Property* Type::GetProperty(const char* name) const noexcept
	{
		std::hash<std::string> hasher;
		size_t id{ hasher(name) };

		for (auto it : m_Properties)
			if (it->GetID() == id)
				return it;

		Reflectpp::Assert(false, "Type::GetProperty : %s isn't registered\n", name);

		return nullptr;
	}

	std::vector<const Property*> Type::GetProperties() const noexcept
	{
		return m_Properties;
	}

	size_t Type::GetID() const noexcept
	{
		return m_ID;
	}

	const char* Type::GetName() const noexcept
	{
		return m_Name;
	}

	size_t Type::GetSize() const noexcept
	{
		return m_Size;
	}

	Type* Type::AddType(ConstructorT ctor, CopyT cctor, DestructorT dtor,
		size_t id, const char* name, size_t size) noexcept
	{
		auto it{ m_TypeDatabase.find(id) };

		if (it != m_TypeDatabase.cend())
			return nullptr;

		Type* type{ new Type(ctor, cctor, dtor, id, name, size) };
		m_TypeDatabase.emplace(id, type);

		return type;
	}

	Type* Type::FindType(size_t id) noexcept
	{
		auto it{ m_TypeDatabase.find(id) };
		return (it != m_TypeDatabase.cend()) ? it->second.get() : nullptr;
	}
}
