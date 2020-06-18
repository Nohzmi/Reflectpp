// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Type.h"

#include <functional>
#include <string>
#include "Registry.h"

Factory::Factory(ConstructorT constructor, CopyT copy, DestructorT destructor) noexcept :
	m_Constructor{ constructor },
	m_Copy{ copy },
	m_Destructor{ destructor }
{
}

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

Property::Property(size_t id, const char* name, size_t offset, Type* type) noexcept :
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

Registration::Registration(Type* type) noexcept :
	m_Type{ type }
{
}

TypeInfo::TypeInfo(size_t id, const char* name) noexcept :
	m_ID{ id },
	m_Name{ name }
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

Type::Type(Factory& factory, size_t size, TypeInfo& typeinfo) noexcept :
	m_Factory{ factory },
	m_HierarchyID{ typeinfo.GetID() },
	m_Size{ size },
	m_TypeInfo{ typeinfo }
{
}

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

Factory& Type::GetFactory() const noexcept
{
	return *const_cast<Factory*>(&m_Factory);
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

	for (auto& prop : m_Properties)
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

TypeInfo& Type::GetTypeInfo() const noexcept
{
	return *const_cast<TypeInfo*>(&m_TypeInfo);
}
