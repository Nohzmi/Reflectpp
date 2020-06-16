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

#ifdef REFLECTPP_DLL
#define REFLECTPP_API __declspec(dllexport)
#else
#define REFLECTPP_API __declspec(dllimport)
#endif

#define REGISTRATION									\
namespace												\
{														\
    struct register_class final : public Register		\
    {													\
        register_class()								\
        {												\
            register_function();						\
        }												\
		static void register_function() noexcept;		\
    };													\
}														\
static const register_class register_obj;				\
void register_class::register_function() noexcept

/**
* Contains all utility functions \n
* Mainly to generate type informations
*/
namespace Reflectpp
{
	template<typename T>
	struct is_valid : std::bool_constant<
		!std::is_array_v<T> &&
		!std::is_const_v<T> &&
		!std::is_null_pointer_v<T> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		!std::is_void_v<T> &&
		!std::is_volatile_v<T>>
	{};

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
		if constexpr (std::is_constructible_v<T>)
			return new T();
		else
			return nullptr;
	}

	/**
	* Returns pointer on created object \n
	* Allow to save a pointer on copy constructor function
	*/
	template<typename T>
	void* CopyObject(void* copy) noexcept
	{
		if constexpr (std::is_copy_constructible_v<T>)
			return new T(*static_cast<T*>(copy));
		else
			return nullptr;
	}

	/**
	* Returns hashing of an std::string
	* @param str
	*/
	REFLECTPP_API size_t Hash(const char* str) noexcept;

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
class REFLECTPP_API Field final
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
	Field(size_t id, const char* name, size_t offset, const Type* type) noexcept;

	/**
	* Returns id of this field
	*/
	size_t GetID() const noexcept;

	/**
	* Returns name of this field
	*/
	const char* GetName() const noexcept;

	/**
	* Returns offset of this field
	*/
	size_t GetOffset() const noexcept;

	/**
	* Returns type of this field
	*/
	const Type* GetType() const noexcept;

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
class REFLECTPP_API Type final
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
	Type(ConstructorT constructor, CopyConstructorT copyConstructor, size_t id, const char* name, size_t size);

	/**
	* Returns whether or not two types are the same
	* @param rhs
	*/
	bool operator==(const Type& rhs) const noexcept;

	/**
	* Returns whether or not two types are the same
	* @param rhs
	*/
	bool operator!=(const Type& rhs) const noexcept;

	/**
	* Register the base class of the current type
	*/
	template<typename T>
	Type& base() noexcept;

	/**
	* Allows to cast between class hierarchies up, down and side
	* @param object
	*/
	template<typename T, typename U, typename V = typename std::remove_pointer_t<T>>
	static std::remove_pointer_t<T>* Cast(U*& object) noexcept;

	/**
	* Returns requested type representation
	*/
	template<typename T>
	static const Type* Get() noexcept;

	/**
	* Returns requested type representation
	* @param object
	*/
	template<typename T>
	static const Type* Get(T*& object) noexcept;

	/**
	* Returns base types of this type
	*/
	const std::vector<const Type*> GetBaseTypes() const noexcept;

	/**
	* Returns constructor of this type
	*/
	ConstructorT GetConstructor() const noexcept;

	/**
	* Returns copy constructor of this type
	*/
	CopyConstructorT GetCopyConstructor() const noexcept;

	/**
	* Returns derived types of this type
	*/
	const std::vector<const Type*> GetDerivedTypes() const noexcept;

	/**
	* Returns field by name of this type
	* @param name
	*/
	const Field* GetField(const char* name) const noexcept;

	/**
	* Returns all field of this type
	*/
	std::vector<const Field*> GetFields() const noexcept;

	/**
	* Returns id of this type
	*/
	size_t GetID() const noexcept;

	/**
	* Returns name of this type
	*/
	const char* GetName() const noexcept;

	/**
	* Returns size of this type
	*/
	size_t GetSize() const noexcept;

	/**
	* Register a field of the current type
	* @param name
	* @param addr
	*/
	template<typename T, typename FieldT, typename U = typename std::remove_cv_t<FieldT>>
	Type& field(const char* name, FieldT T::* addr) noexcept;

private:

	std::vector<const Type*> m_BaseTypes;
	const ConstructorT m_Constructor;
	const CopyConstructorT m_CopyConstructor;
	std::vector<const Type*> m_DerivedTypes;
	static FieldDatabase m_FieldDatabase;
	std::vector<const Field*> m_Fields;
	size_t m_HierarchyID;
	const size_t m_ID;
	const char* m_Name;
	const size_t m_Size;
	static TypeDatabase m_TypeDatabase;
};

/**
* Basic type use in macro for registration
*/
struct REFLECTPP_API Register
{
	/**
	* Register a type in reflection
	* @param name
	*/
	template<typename T>
	static Type& Class(const char* name) noexcept;
};

template<typename T>
inline Type& Type::base() noexcept
{
	if constexpr (std::is_arithmetic_v<T> || !Reflectpp::is_valid<T>::value)
	{
		Reflectpp::Assert(false, "Type::base<%s>() : invalid type\n", typeid(T).name());
		return *const_cast<Type*>(Get<void>());
	}
	else
	{
		Type* base{ const_cast<Type*>(Get<T>()) };

		for (auto it : m_BaseTypes)
			Reflectpp::Assert(it->m_ID != base->m_ID, "Type::base<%s>() : base type already registered\n", base->m_Name);

		if (m_BaseTypes.empty())
			m_HierarchyID = base->m_HierarchyID;

		if (!m_BaseTypes.empty())
		{
			auto updateHierarchy = [](const Type* type, size_t hierarchyID, const auto& lambda)
			{
				if (type->m_HierarchyID == hierarchyID) return;
				const_cast<Type*>(type)->m_HierarchyID = hierarchyID;
				for (auto it : type->m_BaseTypes) lambda(it, hierarchyID, lambda);
				for (auto it : type->m_DerivedTypes) lambda(it, hierarchyID, lambda);
			};

			updateHierarchy(base, m_HierarchyID, updateHierarchy);
		}

		base->m_DerivedTypes.emplace_back(this);
		m_BaseTypes.emplace_back(base);
		m_Fields.insert(m_Fields.cbegin(), base->m_Fields.cbegin(), base->m_Fields.cbegin());

		return *this;
	}
}

template<typename T, typename U, typename V>
inline std::remove_pointer_t<T>* Type::Cast(U*& object) noexcept
{
	if constexpr (!std::is_pointer_v<T>)
	{
		Reflectpp::Assert(false, "Type::Cast<%s>() : not a pointer\n", typeid(T).name());
		return nullptr;
	}
	else if constexpr (std::is_const_v<V> || std::is_pointer_v<V> || std::is_void_v<V> || std::is_volatile_v<V>)
	{
		Reflectpp::Assert(false, "Type::Cast<%s>() : invalid type\n", typeid(T).name());
		return nullptr;
	}
	else if constexpr (std::is_const_v<U> || std::is_void_v<U> || std::is_volatile_v<U>)
	{
		Reflectpp::Assert(false, "Type::Cast<%s, %s>() : invalid object type\n", typeid(T).name(), typeid(U).name());
		return nullptr;
	}
	else
	{
		return (Get(object)->m_HierarchyID == Get<V>()->m_HierarchyID) ? reinterpret_cast<T>(object) : nullptr;
	}
}

template<typename T>
inline const Type* Type::Get() noexcept
{
	if constexpr (!Reflectpp::is_valid<T>::value)
	{
		Reflectpp::Assert(false, "Type::Get<%s>() : invalid type\n", typeid(T).name());
		return nullptr;
	}
	else if constexpr (std::is_arithmetic_v<T>)
	{
		const auto it{ m_TypeDatabase.find(typeid(T).hash_code()) };

		if (it != m_TypeDatabase.cend())
			return it->second.get();

		Type* type{ new Type(Reflectpp::ConstructObject<T>, Reflectpp::CopyObject<T>, Reflectpp::Hash(typeid(T).name()), typeid(T).name(), sizeof(T)) };
		m_TypeDatabase.emplace(typeid(T).hash_code(), type);

		return type;
	}
	else
	{
		const auto it{ m_TypeDatabase.find(typeid(T).hash_code()) };
		Reflectpp::Assert(it != m_TypeDatabase.cend(), "Type::Get<%s>() : unregistered type\n", typeid(T).name());

		return it->second.get();
	}
}

template<typename T>
inline const Type* Type::Get(T*& object) noexcept
{
	if constexpr (std::is_null_pointer_v<T> || std::is_void_v<T> || std::is_volatile_v<T>)
	{
		Reflectpp::Assert(false, "Type::Get<%s>(T*& object) : invalid type\n", typeid(T).name());
		return nullptr;
	}
	else if constexpr (std::is_arithmetic_v<T>)
	{
		Reflectpp::Assert(object != nullptr, "Type::Get<%s>(T*& object) : object nullptr\n", typeid(*object).name());
		return Get<T>();
	}
	else if constexpr (!Reflectpp::HasGetTypeID<T>::value)
	{
		Reflectpp::Assert(false, "Type::Get<%s>(T*& object) : unregistered type\n", typeid(*object).name());
		return nullptr;
	}
	else
	{
		Reflectpp::Assert(object != nullptr, "Type::Get<%s>(T*& object) : object nullptr\n", typeid(T).name());
		return m_TypeDatabase.find(object->GetTypeID())->second.get();
	}
}

template<typename T, typename FieldT, typename U>
inline Type& Type::field(const char* name, FieldT T::* addr) noexcept
{
	for (auto it : m_Fields)
		Reflectpp::Assert(it->GetID() != Reflectpp::Hash(name), "Type::field : %s already registered\n", name);

	m_FieldDatabase.emplace_back(new Field(Reflectpp::Hash(name), name, Reflectpp::Offset(addr), Get<U>()));
	const_cast<Type*>(Get<T>())->m_Fields.emplace_back(m_FieldDatabase.back().get());

	return *this;
}

template<typename T>
inline Type& Register::Class(const char* name) noexcept
{
	if constexpr (std::is_arithmetic_v<T> || !Reflectpp::is_valid<T>::value)
	{
		Reflectpp::Assert(false, "Register::Class<%s>() : invalid type\n", typeid(T).name());
		return *const_cast<Type*>(Type::Get<void>());
	}
	else if constexpr (!Reflectpp::HasGetTypeID<T>::value)
	{
		Reflectpp::Assert(false, "Register::Class<%s>() : REFLECT macro not used\n", typeid(T).name());
		return *const_cast<Type*>(Type::Get<void>());
	}
	else
	{
		const size_t id{ typeid(T).hash_code() };
		Reflectpp::Assert(Type::m_TypeDatabase.find(id) == Type::m_TypeDatabase.cend(), "Register::Class<%s>() : type already registered\n", typeid(T).name());

		Type* type{ new Type(Reflectpp::ConstructObject<T>, Reflectpp::CopyObject<T>, Reflectpp::Hash(name), name, sizeof(T)) };
		Type::m_TypeDatabase.emplace(id, type);

		return *type;
	}
}

/**
* @}
*/
