// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file Type.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <cassert>
#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#include "Register.h"

/**
* @addtogroup Reflectpp
* @{
*/

#define _REFLECTPP_CAT(A, B) A ## B
#define REFLECTPP_CAT(A, B) _REFLECTPP_CAT(A, B)

#define REGISTRATION														\
struct REFLECTPP_CAT(Register, __LINE__) final : public Register			\
{																			\
	REFLECTPP_CAT(Register, __LINE__)();									\
};																			\
REFLECTPP_CAT(Register, __LINE__) REFLECTPP_CAT(Obj, __LINE__);				\
REFLECTPP_CAT(Register, __LINE__)::REFLECTPP_CAT(Register, __LINE__)()

/**
* Contains all utility functions \n
* Mainly to generate type informations
*/
namespace Reflectpp
{
	/**
	* Allow to assert with a message in the console
	* @param expr
	* @param format
	* @param args
	*/
	template <class ...Args>
	void Assert(bool expr, const char* format, Args... args) noexcept
	{
		if (!expr)
		{
			printf(format, args...);
			assert(false);
		}
	}

	/**
	* Returns pointer on created object \n
	* Allow to save a pointer on constructor function
	*/
	template<typename T>
	void* ConstructObject() noexcept
	{
		return new T();
	}

	/**
	* Returns pointer on created object \n
	* Allow to save a pointer on copy constructor function
	*/
	template<typename T>
	void* CopyObject(void* copy) noexcept
	{
		return new T(*static_cast<T*>(copy));
	}

	/**
	* Returns id of the type \n
	* Only use to retrieve type representation
	*/
	template<typename T>
	size_t GetTypeID() noexcept
	{
		static size_t typeID{ typeid(T).hash_code() };
		return typeID;
	}

	/**
	* Returns hashing of an std::string
	* @param str
	*/
	size_t Hash(const char* str) noexcept
	{
		std::hash<std::string> hasher;
		return hasher(std::string(str));
	}

	/**
	* Returns offset of a class member
	* @param member
	*/
	template<typename T, typename FieldT>
	size_t Offset(FieldT T::* addr)
	{
		return reinterpret_cast<size_t>(&(reinterpret_cast<T const volatile*>(nullptr)->*addr));
	}
}

class Type;

/**
* The basic type representation
*/
class Field final
{
public:

	/**
	* Constructor
	*/
	Field() = delete;

	/**
	* Destructor
	*/
	~Field() = default;

	/**
	* Copy constructor
	*/
	Field(const Field&) = delete;

	/**
	* Move constructor
	*/
	Field(Field&&) noexcept = default;

	/**
	* Copy assignement operator
	*/
	Field& operator=(const Field&) = delete;

	/**
	* Move assignement operator
	*/
	Field& operator=(Field&&) noexcept = default;

	/**
	* Construct a field
	* @param id
	* @param name
	* @param offset
	* @param type
	*/
	Field(size_t id, const char* name, size_t offset, Type* type) noexcept :
		m_ID{ id },
		m_Name{ name },
		m_Offset{ offset },
		m_Type{ type }
	{
	}

	/**
	* Returns id of this field
	*/
	size_t GetID() const noexcept
	{
		return m_ID;
	}

	/**
	* Returns name of this field
	*/
	const char* GetName() const noexcept
	{
		return m_Name;
	}

	/**
	* Returns offset of this field
	*/
	size_t GetOffset() const noexcept
	{
		return m_Offset;
	}

	/**
	* Returns type of this field
	*/
	const Type* GetType() const noexcept
	{
		return m_Type;
	}

private:

	const size_t m_ID;
	const char* m_Name;
	const size_t m_Offset;
	const Type* m_Type;
};

struct Register;

/**
* The basic type representation \n
* Also serves as type database
*/
class Type final
{
	friend Register;

	using CopyConstructorT = void* (*)(void*);
	using ConstructorT = void* (*)();
	using FieldDatabase = std::vector<std::unique_ptr<Field>>;
	using TypeDatabase = std::unordered_map<size_t, std::unique_ptr<Type>>;

public:

	/**
	* Constructor
	*/
	Type() = delete;

	/**
	* Destructor
	*/
	~Type() = default;

	/**
	* Copy constructor
	*/
	Type(const Type&) = delete;

	/**
	* Move constructor
	*/
	Type(Type&&) noexcept = default;

	/**
	* Copy assignement operator
	*/
	Type& operator=(const Type&) = delete;

	/**
	* Move assignement operator
	*/
	Type& operator=(Type&&) noexcept = default;

	/**
	* Construct a type representation
	* @param constructor
	* @param copyConstructor
	* @param id
	* @param name
	* @param size
	*/
	Type(ConstructorT constructor, CopyConstructorT copyConstructor, size_t id, const char* name, size_t size) :
		m_Constructor{ constructor },
		m_CopyConstructor{ copyConstructor },
		m_HierarchyID{ id },
		m_ID{ id },
		m_Name{ name },
		m_Size{ size }
	{
	}

	/**
	* Returns whether or not two types are the same
	* @param rhs
	*/
	bool operator==(const Type& rhs) const noexcept
	{
		return m_ID == rhs.m_ID;
	}

	/**
	* Returns whether or not two types are the same
	* @param rhs
	*/
	bool operator!=(const Type& rhs) const noexcept
	{
		return m_ID != rhs.m_ID;
	}

	/**
	* Register the base class of the current type
	*/
	template<typename T>
	Type& base() noexcept
	{
		Type* base{ GetType<T>() };

		for (auto it : m_BaseTypes)
			Reflectpp::Assert(it->m_ID != base->m_ID, "%s is already registered in %s\n", base->m_Name, m_Name);

		if (m_BaseTypes.empty()) m_HierarchyID = base->m_HierarchyID;
		else UpdateHierarchyID(base, m_HierarchyID);

		base->m_DerivedTypes.emplace_back(this);
		m_BaseTypes.emplace_back(base);
		m_Fields.insert(m_Fields.cbegin(), base->m_Fields.cbegin(), base->m_Fields.cbegin());

		return *this;
	}

	/**
	* Allows to cast between class hierarchies up, down and side
	* @param object
	*/
	template<typename T, typename U>
	static typename std::enable_if<std::is_pointer_v<T>, T>::type Cast(U* object) noexcept
	{
		return (GetType<U>()->m_HierarchyID == GetType<std::remove_pointer_t<T>>()->m_HierarchyID) ? reinterpret_cast<T>(object) : nullptr;
	}

	/**
	* Allows to cast between class hierarchies up, down and side
	* @param object
	*/
	template<typename T, typename U>
	static typename std::enable_if<!std::is_pointer_v<T>, T>::type* Cast(U*) noexcept
	{
		Reflectpp::Assert(false, "Invalid cast: not a pointer\n");
		return nullptr;
	}

	/**
	* Returns requested type representation
	*/
	template<typename T>
	static const Type* Get() noexcept
	{
		return GetType<T>();
	}

	/**
	* Returns requested type representation
	* @param object
	*/
	template<typename T>
	static const Type* Get(const T* object) noexcept
	{
		return GetType(object);
	}

	/**
	* Returns base types of this type
	*/
	const std::vector<const Type*> GetBaseTypes() const noexcept
	{
		return m_BaseTypes;
	}

	/**
	* Returns constructor of this type
	*/
	ConstructorT GetConstructor() const noexcept
	{
		return m_Constructor;
	}

	/**
	* Returns copy constructor of this type
	*/
	CopyConstructorT GetCopyConstructor() const noexcept
	{
		return m_CopyConstructor;
	}

	/**
	* Returns derived types of this type
	*/
	const std::vector<const Type*> GetDerivedTypes() const noexcept
	{
		return m_DerivedTypes;
	}

	/**
	* Returns field by name of this type
	* @param name
	*/
	const Field* GetField(const char* name) const noexcept
	{
		size_t id{ Reflectpp::Hash(name) };

		for (auto it : m_Fields)
			if (it->GetID() == id)
				return it;

		Reflectpp::Assert(false, "%s isn't registered in %s\n", name, m_Name);

		return nullptr;
	}

	/**
	* Returns all field of this type
	*/
	std::vector<const Field*> GetFields() const noexcept
	{
		return m_Fields;
	}

	/**
	* Returns id of this type
	*/
	size_t GetID() const noexcept
	{
		return m_ID;
	}

	/**
	* Returns name of this type
	*/
	const char* GetName() const noexcept
	{
		return m_Name;
	}

	/**
	* Returns size of this type
	*/
	size_t GetSize() const noexcept
	{
		return m_Size;
	}

	/**
	* Register a field of the current type
	* @param name
	* @param addr
	*/
	template<typename T, typename FieldT>
	Type& field(const char* name, FieldT T::* addr) noexcept
	{
		size_t id{ Reflectpp::Hash(name) };

		for (auto it : m_Fields)
			Reflectpp::Assert(it->GetID() != id, "%s is already registered in %s\n", name, m_Name);

		Field* field{ new Field(id, name, Reflectpp::Offset(addr), GetType<FieldT>()) };
		GetFieldDatabase().emplace_back(field);
		GetType<T>()->m_Fields.emplace_back(field);

		return *this;
	}

private:

	/**
	* Register a type in reflection
	* @param name
	*/
	template<typename T>
	static Type& AddType(const char* name) noexcept
	{
		size_t id{ Reflectpp::GetTypeID<T>() };
		Reflectpp::Assert(GetTypeDatabase().find(id) == GetTypeDatabase().cend(), "%s is already registered\n", name);

		Type* type{ CreateType<T>(name) };
		GetTypeDatabase().emplace(id, type);

		return *type;
	}

	/**
	* Create a type for reflection
	* @param name
	*/
	template<typename T>
	static Type* CreateType(const char* name) noexcept
	{
		return new Type(Reflectpp::ConstructObject<T>, Reflectpp::CopyObject<T>, Reflectpp::Hash(name), name, sizeof(T));
	}

	/**
	* Initialize the type database
	*/
	static TypeDatabase CreateTypeDatabase() noexcept
	{
		TypeDatabase typeDatabase;
		typeDatabase.emplace(Reflectpp::GetTypeID<bool>(), CreateType<bool>("bool"));
		typeDatabase.emplace(Reflectpp::GetTypeID<char>(), CreateType<char>("char"));
		typeDatabase.emplace(Reflectpp::GetTypeID<char16_t>(), CreateType<char16_t>("char16_t"));
		typeDatabase.emplace(Reflectpp::GetTypeID<char32_t>(), CreateType<char32_t>("char32_t"));
		typeDatabase.emplace(Reflectpp::GetTypeID<double>(), CreateType<double>("double"));
		typeDatabase.emplace(Reflectpp::GetTypeID<float>(), CreateType<float>("float"));
		typeDatabase.emplace(Reflectpp::GetTypeID<int>(), CreateType<int>("int"));
		typeDatabase.emplace(Reflectpp::GetTypeID<long>(), CreateType<long>("long"));
		typeDatabase.emplace(Reflectpp::GetTypeID<long double>(), CreateType<long double>("long double"));
		typeDatabase.emplace(Reflectpp::GetTypeID<long long>(), CreateType<long long>("long long"));
		typeDatabase.emplace(Reflectpp::GetTypeID<short>(), CreateType<short>("short"));
		typeDatabase.emplace(Reflectpp::GetTypeID<signed char>(), CreateType<signed char>("signed char"));
		typeDatabase.emplace(Reflectpp::GetTypeID<unsigned char>(), CreateType<unsigned char>("unsigned char"));
		typeDatabase.emplace(Reflectpp::GetTypeID<unsigned int>(), CreateType<unsigned int>("unsigned int"));
		typeDatabase.emplace(Reflectpp::GetTypeID<unsigned long>(), CreateType<unsigned long>("unsigned long"));
		typeDatabase.emplace(Reflectpp::GetTypeID<unsigned long long>(), CreateType<unsigned long long>("unsigned long long"));
		typeDatabase.emplace(Reflectpp::GetTypeID<unsigned short>(), CreateType<unsigned short>("unsigned short"));
		typeDatabase.emplace(Reflectpp::GetTypeID<wchar_t>(), CreateType<wchar_t>("wchar_t"));

		return typeDatabase;
	}

	/**
	* Returns requested type representation
	*/
	template<typename T>
	static Type* GetType() noexcept
	{
		auto it{ GetTypeDatabase().find(Reflectpp::GetTypeID<T>()) };
		Reflectpp::Assert(it != GetTypeDatabase().cend(), "%s isn't registered\n", typeid(T).name());

		return it->second.get();
	}

	/**
	* Returns requested type representation
	* @param object
	*/
	template<typename T>
	static typename std::enable_if <!std::is_class_v<T> || Reflectpp::HasGetTypeID<T>::value, Type>::type* GetType(const T* object) noexcept
	{
		auto it{ GetTypeDatabase().find(std::is_class_v<T> ? object->GetTypeID() : Reflectpp::GetTypeID<T>()) };
		Reflectpp::Assert(it != GetTypeDatabase().cend(), "%s isn't registered\n", typeid(T).name());

		return it->second.get();
	}

	/**
	* Returns requested type representation
	* @param object
	*/
	template<typename T>
	static typename std::enable_if<std::is_class_v<T> && !Reflectpp::HasGetTypeID<T>::value, Type>::type* GetType(const T* object) noexcept
	{
		Reflectpp::Assert(false, "%s don't use REFLECT macro\n", typeid(*object).name());
		return nullptr;
	}

	/**
	* Returns database of types representation
	*/
	static TypeDatabase& GetTypeDatabase() noexcept
	{
		static TypeDatabase m_TypeDatabase{ CreateTypeDatabase() };
		return m_TypeDatabase;
	}

	/**
	* Returns database of types representation
	*/
	static FieldDatabase& GetFieldDatabase() noexcept
	{
		static FieldDatabase m_FieldDatabase;
		return m_FieldDatabase;
	}

	/**
	* Update hierarchy id recursively
	* @param type
	* @param hierarchyID
	*/
	static void UpdateHierarchyID(const Type* type, size_t hierarchyID) noexcept
	{
		if (type->m_HierarchyID == hierarchyID)
			return;

		const_cast<Type*>(type)->m_HierarchyID = hierarchyID;

		for (auto it : type->m_BaseTypes)
			UpdateHierarchyID(it, hierarchyID);

		for (auto it : type->m_DerivedTypes)
			UpdateHierarchyID(it, hierarchyID);
	}

private:

	std::vector<const Type*> m_BaseTypes;
	const ConstructorT m_Constructor;
	const CopyConstructorT m_CopyConstructor;
	std::vector<const Type*> m_DerivedTypes;
	std::vector<const Field*> m_Fields;
	size_t m_HierarchyID;
	const size_t m_ID;
	const char* m_Name;
	const size_t m_Size;
};

/**
* Basic type use in macro for registration
*/
struct Register
{
	/**
	* Register a type in reflection
	* @param name
	*/
	template<typename T>
	static Type& Class(const char* name) noexcept
	{
		return Type::AddType<T>(name);
	}
};

/**
* @}
*/
