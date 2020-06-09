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
	* Returns pointer on created object \n
	* Allow to save a pointer on constructor function
	*/
	template<typename T>
	inline void* ConstructObject() noexcept
	{
		return new T();
	}

	/**
	* Returns pointer on created object \n
	* Allow to save a pointer on copy constructor function
	*/
	template<typename T>
	inline void* CopyObject(void* copy) noexcept
	{
		return new T(*static_cast<T*>(copy));
	}

	/**
	* Returns id of the type \n
	* Only use to retrieve type representation
	*/
	template<typename T>
	inline size_t GetTypeID() noexcept
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
	using Database = std::unordered_map<size_t, std::unique_ptr<Type>>;

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
		assert(m_BaseType == nullptr && "Base type already registered");

		m_BaseType = GetType<T>();
		m_BaseType->m_DerivedTypes.emplace_back(this);

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
	* Returns base type of this type
	*/
	const Type& GetBaseType() const noexcept
	{
		return *m_BaseType;
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
	* Returns field by name of this type
	*/
	const Field& GetField(const std::string& name) const noexcept
	{
		auto it{ m_Fields.find(Reflectpp::Hash(name)) };

		if (it == m_Fields.cend() && m_BaseType != nullptr)
			return m_BaseType->GetField(name);

		assert(it != m_Fields.cend() && "Unregistered field");

		return it->second;
	}

	/**
	* Returns all field of this type
	*/
	std::vector<Field> GetFields() const noexcept
	{
		std::vector<Field> fields;

		if (m_BaseType != nullptr)
			fields = m_BaseType->GetFields();

		for (auto it : m_Fields)
			fields.emplace_back(it.second);

		return fields;
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
		assert(m_Fields.find(id) == m_Fields.cend() && "Field already registered");

		Field field{ Field(id, name, Reflectpp::Offset(addr), GetType<FieldT>()) };
		GetType<T>()->m_Fields.emplace(id, field);

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
		assert(GetTypes().find(id) == GetTypes().cend() && "Type already registered");

		Type* type{ new Type() };
		GetTypes().emplace(id, type);

		type->m_Constructor = Reflectpp::ConstructObject<T>;
		type->m_CopyConstructor = Reflectpp::CopyObject<T>;
		type->m_ID = Reflectpp::Hash(name);
		type->m_Name = name;
		type->m_Size = sizeof(T);

		return *type;
	}

	/**
	* Returns requested type representation
	* Also register the type if needed
	*/
	template<typename T>
	static Type* GetType() noexcept
	{
		auto it{ GetTypes().find(Reflectpp::GetTypeID<T>()) };
		assert(it != GetTypes().cend() && "Unregistered type");

		return it->second.get();
	}

	/**
	* Returns database of types representation
	*/
	static Database& GetTypes() noexcept
	{
		static Database m_Types;
		return m_Types;
	}

private:

	Type* m_BaseType{ nullptr };
	ConstructorT m_Constructor{ nullptr };
	CopyConstructorT m_CopyConstructor{ nullptr };
	std::vector<Type*> m_DerivedTypes;
	std::unordered_map<size_t, Field> m_Fields;
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
