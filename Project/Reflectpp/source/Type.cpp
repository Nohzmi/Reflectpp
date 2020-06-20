// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Type.h"

#include <functional>
#include <string>
#include "Registry.h"

Factory::Factory(void* (*ctor)(), void* (*copy)(void*), void (*dtor)(void*)) noexcept :
	m_Constructor{ ctor },
	m_Copy{ copy },
	m_Destructor{ dtor }
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

Type& Property::GetType() const noexcept
{
	return *m_Type;
}

Registration::Registration(Type* type) noexcept :
	m_Type{ type }
{
}

Type::Type(Factory* factory, size_t size, TypeInfo* typeinfo) noexcept :
	m_Factory{ factory },
	m_HierarchyID{ typeinfo->GetID() },
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

Range<Type>& Type::GetBaseTypes() const noexcept
{
	return *const_cast<Range<Type>*>(&m_BaseTypes);
}

Range<Type>& Type::GetDerivedTypes() const noexcept
{
	return *const_cast<Range<Type>*>(&m_DerivedTypes);
}

Factory& Type::GetFactory() const noexcept
{
	return *m_Factory;
}

size_t Type::GetID() const noexcept
{
	return m_TypeInfo->GetID();
}

const char* Type::GetName() const noexcept
{
	return m_TypeInfo->GetName();
}

Property& Type::GetProperty(const char* name) const noexcept
{
	std::hash<std::string> hasher;
	size_t id{ hasher(name) };

	for (auto& prop : m_Properties)
		if (prop.GetID() == id)
			return prop;

	Reflectpp::Assert(false, "Type::GetProperty(const char* name) : %s isn't registered\n", name);
	return *m_Properties.begin();
}

Range<Property>& Type::GetProperties() const noexcept
{
	return *const_cast<Range<Property>*>(&m_Properties);
}

size_t Type::GetSize() const noexcept
{
	return m_Size;
}

TypeInfo& Type::GetTypeInfo() const noexcept
{
	return *m_TypeInfo;
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
