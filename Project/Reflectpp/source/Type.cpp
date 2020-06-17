// Copyright (c) 2020, Nohzmi. All rights reserved.

#include "Type.h"

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

	const std::vector<const Type*> Type::GetDerivedTypes() const noexcept
	{
		return m_DerivedTypes;
	}

	const Factory& Type::GetFactory() const noexcept
	{
		return m_Factory;
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

	Type::Type(Factory factory, size_t id, const char* name, size_t size) noexcept :
		m_Factory{ factory },
		m_HierarchyID{ id },
		m_ID{ id },
		m_Name{ name },
		m_Size{ size }
	{
	}

	Type* Type::AddType(Factory factory, size_t id, const char* name, size_t size) noexcept
	{
		auto it{ m_TypeDatabase.find(id) };

		if (it != m_TypeDatabase.cend())
			return nullptr;

		Type* type{ new Type(factory, id, name, size) };
		m_TypeDatabase.emplace(id, type);

		return type;
	}

	Type* Type::FindType(size_t id) noexcept
	{
		auto it{ m_TypeDatabase.find(id) };
		return (it != m_TypeDatabase.cend()) ? it->second.get() : nullptr;
	}
}
