// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Type.h"

size_t Reflectpp::Hash(const char* str) noexcept
{
	std::hash<std::string> hasher;
	return hasher(std::string(str));
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

Type::Type(ConstructorT constructor, CopyConstructorT copyConstructor, size_t id, const char* name, size_t size) :
	m_Constructor{ constructor },
	m_CopyConstructor{ copyConstructor },
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

Type::CopyConstructorT Type::GetCopyConstructor() const noexcept
{
	return m_CopyConstructor;
}

const std::vector<const Type*> Type::GetDerivedTypes() const noexcept
{
	return m_DerivedTypes;
}

const Property* Type::GetProperty(const char* name) const noexcept
{
	size_t id{ Reflectpp::Hash(name) };

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
