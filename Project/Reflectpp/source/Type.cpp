// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Type.h"

#include <functional>
#include <string>
#include "Registry.h"

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

Property::Property(void* getter, size_t id, const char* name, size_t offset, void* setter, Type* type) noexcept :
	m_Getter{ getter },
	m_ID{ id },
	m_Name{ name },
	m_Offset{ offset },
	m_Setter{ setter },
	m_Type{ type }
{
}

Registration::Registration(Type* type) noexcept :
	m_Type{ type }
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

Variant::Variant() :
	m_Data{ nullptr },
	m_IsOwner{ false },
	m_Type{ nullptr }
{
}

Variant::~Variant()
{
	if (m_IsOwner && m_Data != nullptr)
	{
		m_Type->GetFactory().Destroy(m_Data);
		m_Data = nullptr;
	}
}

Variant::Variant(const Variant& copy) :
	m_Data{ copy.m_Type->GetFactory().Copy(copy.m_Data) },
	m_IsOwner{ true },
	m_Type{ copy.m_Type }
{
}

Variant& Variant::operator=(const Variant& copy)
{
	m_Data = copy.m_Type->GetFactory().Copy(copy.m_Data);
	m_IsOwner = true;
	m_Type = copy.m_Type;

	return *this;
}

Variant::operator bool() const
{
	return IsValid();
}

void Variant::Clear() noexcept
{
	if (m_IsOwner && IsValid())
		m_Type->GetFactory().Destroy(m_Data);

	m_Data = nullptr;
	m_IsOwner = false;
	m_Type = nullptr;
}

Type& Variant::GetType() const noexcept
{
	Reflectpp::Assert(m_Type != nullptr, "Variant::GetType() : invalid variant\n");
	return *m_Type;
}

bool Variant::IsValid() const noexcept
{
	return m_Data != nullptr;
}

Variant::Variant(void* data, bool isOwner, Type* type) noexcept :
	m_Data{ data },
	m_IsOwner{ isOwner },
	m_Type{ type }
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

Variant Type::Create() const
{
	return Variant(GetFactory().Construct(), true, const_cast<Type*>(this));
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

Type::Type(Factory* factory, size_t size, TypeInfo* typeinfo) noexcept :
	m_Factory{ factory },
	m_HierarchyID{ typeinfo->GetID() },
	m_Size{ size },
	m_TypeInfo{ typeinfo }
{
}
