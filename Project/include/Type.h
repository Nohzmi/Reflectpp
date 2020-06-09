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
#include <typeinfo>
#include <unordered_map>
#include <vector>

/**
* @addtogroup Reflectpp
* @{
*/

#define _CAT(A, B) A ## B
#define CAT(A, B) _CAT(A, B)

#define REGISTRATION										\
struct CAT(Register, __LINE__) final : public Register		\
{															\
	CAT(Register, __LINE__)();								\
};															\
CAT(Register, __LINE__) CAT(Obj, __LINE__);					\
CAT(Register, __LINE__)::CAT(Register, __LINE__)()

/**
* Contains all utility functions \n
* Mainly to generate type informations
*/
namespace Reflectpp
{
	/**
	* Allow to assert with a message in the console
	* @param expr
	* @param msg
	*/
	void Assert(bool expr, const std::string& msg, const std::string& details) noexcept
	{
		if (!expr)
		{
			printf("Eventpp: %s {%s}\n", msg.c_str(), details.c_str());
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
	* Returns vector of derefenced pointer from vector of pointers
	* @param pointers
	*/
	template<typename T>
	std::vector<T> Dereference(const std::vector<T*>& pointers)
	{
		std::vector<T> reference;
		reference.reserve(pointers.size());

		for (auto it : pointers)
			reference.emplace_back(*it);

		return reference;
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
	size_t Hash(const std::string& str) noexcept
	{
		std::hash<std::string> hasher;
		return hasher(str);
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
	Field(const Field&) = default;

	/**
	* Move constructor
	*/
	Field(Field&&) noexcept = default;

	/**
	* Copy assignement operator
	*/
	Field& operator=(const Field&) = default;

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
	Field(size_t id, const std::string& name, size_t offset, Type* type) noexcept :
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
	std::string GetName() const noexcept
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
	const Type& GetType() const noexcept
	{
		return *m_Type;
	}

private:

	size_t m_ID{ 0u };
	std::string m_Name{ "" };
	size_t m_Offset{ 0u };
	Type* m_Type{ nullptr };
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
	Type() = default;

	/**
	* Destructor
	*/
	~Type() = default;

	/**
	* Copy constructor
	*/
	Type(const Type&) = default;

	/**
	* Move constructor
	*/
	Type(Type&&) noexcept = default;

	/**
	* Copy assignement operator
	*/
	Type& operator=(const Type&) = default;

	/**
	* Move assignement operator
	*/
	Type& operator=(Type&&) noexcept = default;

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

		for (Type* it : m_BaseTypes)
			Reflectpp::Assert(it->GetID() != base->GetID(), "Registered base type", base->GetName());

		base->m_DerivedTypes.emplace_back(this);
		m_BaseTypes.emplace_back(base);
		m_Fields.insert(m_Fields.cbegin(), base->m_Fields.cbegin(), base->m_Fields.cbegin());

		return *this;
	}

	/**
	* Returns requested type representation
	*/
	template<typename T>
	static const Type& Get() noexcept
	{
		return *GetType<T>();
	}

	/**
	* Returns base types of this type
	*/
	const std::vector<Type> GetBaseTypes() const noexcept
	{
		return Reflectpp::Dereference<Type>(m_BaseTypes);
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
	const std::vector<Type> GetDerivedTypes() const noexcept
	{
		return Reflectpp::Dereference<Type>(m_DerivedTypes);
	}

	/**
	* Returns field by name of this type
	*/
	const Field& GetField(const std::string& name) const noexcept
	{
		size_t id{ Reflectpp::Hash(name) };

		for (Field* it : m_Fields)
			if (it->GetID() == id)
				return *it;

		Reflectpp::Assert(false, "Unregistered field", name);
	}

	/**
	* Returns all field of this type
	*/
	std::vector<Field> GetFields() const noexcept
	{
		return Reflectpp::Dereference<Field>(m_Fields);
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
	std::string GetName() const noexcept
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
	Type& field(const std::string& name, FieldT T::* addr) noexcept
	{
		size_t id{ Reflectpp::Hash(name) };

		for (Field* it : m_Fields)
			Reflectpp::Assert(it->GetID() != id, "Registered field", name);

		Field* field{ new Field(id, name, Reflectpp::Offset(addr), GetType<FieldT>()) };
		GetFieldDatabase().emplace_back(field);
		GetType<T>()->m_Fields.emplace_back(field);

		return *this;
	}

private:

	/**
	* Register a type in reflection
	*/
	template<typename T>
	static Type& AddType(const std::string& name) noexcept
	{
		size_t id{ Reflectpp::GetTypeID<T>() };
		Reflectpp::Assert(GetTypeDatabase().find(id) == GetTypeDatabase().cend(), "Registered type", name);

		Type* type{ CreateType<T>(name) };
		GetTypeDatabase().emplace(id, type);

		return *type;
	}

	/**
	* Create a type for reflection
	*/
	template<typename T>
	static Type* CreateType(const std::string& name) noexcept
	{
		auto type{ new Type() };
		type->m_Constructor = Reflectpp::ConstructObject<T>;
		type->m_CopyConstructor = Reflectpp::CopyObject<T>;
		type->m_ID = Reflectpp::Hash(name);
		type->m_Name = name;
		type->m_Size = sizeof(T);

		return type;
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
	* Also register the type if needed
	*/
	template<typename T>
	static Type* GetType() noexcept
	{
		auto it{ GetTypeDatabase().find(Reflectpp::GetTypeID<T>()) };
		Reflectpp::Assert(it != GetTypeDatabase().cend(), "Unregistered type", typeid(T).name());

		return it->second.get();
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

private:

	std::vector<Type*> m_BaseTypes;
	ConstructorT m_Constructor{ nullptr };
	CopyConstructorT m_CopyConstructor{ nullptr };
	std::vector<Type*> m_DerivedTypes;
	std::vector<Field*> m_Fields;
	size_t m_ID{ 0u };
	std::string m_Name{ "" };
	size_t m_Size{ 0u };
};

/**
* Basic type use in macro for registration
*/
struct Register
{
	/**
	* Register a type in reflection
	*/
	template<typename T>
	static Type& Class(const std::string& name) noexcept
	{
		return Type::AddType<T>(name);
	}
};

/**
* @}
*/
