// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file Type.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <vector>
#include "Register.h"

/**
* @addtogroup Reflectpp
* @{
*/

#ifndef REFLECTPP_API
#ifdef REFLECTPP_DLL
#define REFLECTPP_API __declspec(dllexport)
#else
#define REFLECTPP_API __declspec(dllimport)
#endif
#endif

#define REGISTRATION							\
static void register_function() noexcept;		\
namespace										\
{												\
    struct register_class final					\
    {											\
        register_class()						\
        {										\
            register_function();				\
        }										\
    };											\
}												\
static const register_class register_obj;		\
void register_function() noexcept

namespace Reflectpp { class Registry; }
class Type;
class TypeInfo;

/**
* Generic factory class used in reflection \n
* Independent of the reflection
*/
class REFLECTPP_API Factory final
{
public:

	Factory() = delete;
	~Factory() = default;
	Factory(const Factory&) = default;
	Factory(Factory&&) noexcept = default;
	Factory& operator=(const Factory&) = default;
	Factory& operator=(Factory&&) noexcept = default;
	Factory(void* (*ctor)(), void* (*copy)(void*), void (*dtor)(void*)) noexcept;

	/**
	* Returns a pointer on created object
	*/
	void* Construct() const noexcept;

	/**
	* Returns a pointer on copied object
	* @param object
	*/
	void* Copy(void* object) const noexcept;

	/**
	* Destroys given object
	* @param object
	*/
	void Destroy(void* object) const noexcept;

	/**
	* Get factory of the requested type
	*/
	template<typename T>
	static Factory& Get() noexcept;

private:

	void* (*m_Constructor)();
	void* (*m_Copy)(void*);
	void (*m_Destructor)(void*);
};

/**
* Show a property of a class in reflection
*/
class REFLECTPP_API Property final
{
public:

	Property() = delete;
	~Property() = default;
	Property(const Property&) = delete;
	Property(Property&&) noexcept = default;
	Property& operator=(const Property&) = delete;
	Property& operator=(Property&&) noexcept = default;
	Property(size_t id, const char* name, size_t offset, Type* type) noexcept;

	/**
	* Returns id of this property
	*/
	size_t GetID() const noexcept;

	/**
	* Returns name of this property
	*/
	const char* GetName() const noexcept;

	/**
	* Returns offset of this property
	*/
	size_t GetOffset() const noexcept;

	/**
	* Returns type of this property
	*/
	Type& GetType() const noexcept;

private:

	size_t m_ID;
	const char* m_Name;
	size_t m_Offset;
	Type* m_Type;
};

/**
* Allow to register a type in reflection \n
* and his base types and properties too
*/
class REFLECTPP_API Registration final
{
public:

	Registration() = delete;
	~Registration() = default;
	Registration(const Registration&) = default;
	Registration(Registration&&) noexcept = default;
	Registration& operator=(const Registration&) = default;
	Registration& operator=(Registration&&) noexcept = default;
	Registration(Type* type) noexcept;

	/**
	* Register the base class of the current type
	*/
	template<typename T>
	Registration base() noexcept;

	/**
	* Register a type in reflection
	*/
	template<typename T>
	static Registration class_() noexcept;

	/**
	* Register a property of the current type
	* @param name
	* @param addr
	*/
	template<typename T, typename PropertyT, typename U = typename std::remove_cv_t<PropertyT>>
	Registration property(const char* name, PropertyT T::* addr) noexcept;

private:

	Type* m_Type;
};

#pragma warning(push)
#pragma warning(disable: 4251)

/**
* The basic type representation
*/
class REFLECTPP_API Type final
{
	friend Reflectpp::Registry;

public:

	Type() = delete;
	~Type() = default;
	Type(const Type&) = delete;
	Type(Type&&) noexcept = default;
	Type& operator=(const Type&) = delete;
	Type& operator=(Type&&) noexcept = default;
	Type(Factory* factory, size_t size, TypeInfo* typeinfo) noexcept;

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
	* Returns requested type representation
	*/
	template<typename T>
	static Type& Get() noexcept;

	/**
	* Returns requested type representation
	* @param object
	*/
	template<typename T>
	static Type& Get(T*& object) noexcept;

	/**
	* Returns base types of this type
	*/
	const std::vector<Type*>& GetBaseTypes() const noexcept;

	/**
	* Returns derived types of this type
	*/
	const std::vector<Type*>& GetDerivedTypes() const noexcept;

	/**
	* Returns factory of this type
	*/
	Factory& GetFactory() const noexcept;

	/**
	* Returns id of this type
	*/
	size_t GetID() const noexcept;

	/**
	* Returns name of this type
	*/
	const char* GetName() const noexcept;

	/**
	* Returns property by name of this type
	* @param name
	*/
	Property& GetProperty(const char* name) const noexcept;

	/**
	* Returns all property of this type
	*/
	const std::vector<Property*>& GetProperties() const noexcept;

	/**
	* Returns size of this type
	*/
	size_t GetSize() const noexcept;

	/**
	* Returns type info of this type
	*/
	TypeInfo& GetTypeInfo() const noexcept;

private:

	std::vector<Type*> m_BaseTypes;
	std::vector<Type*> m_DerivedTypes;
	Factory* m_Factory;
	size_t m_HierarchyID;
	std::vector<Property*> m_Properties;
	size_t m_Size;
	TypeInfo* m_TypeInfo;
};

#pragma warning (pop)

/**
* Equivalent to std::type_info \n
* Independent of the reflection
*/
class REFLECTPP_API TypeInfo final
{
public:

	TypeInfo() = delete;
	~TypeInfo() = default;
	TypeInfo(const TypeInfo&) = default;
	TypeInfo(TypeInfo&&) noexcept = default;
	TypeInfo& operator=(const TypeInfo&) = default;
	TypeInfo& operator=(TypeInfo&&) noexcept = default;
	TypeInfo(size_t id, const char* name) noexcept;

	/**
	* Returns whether or not two types are the same
	* @param rhs
	*/
	bool operator==(const TypeInfo& rhs) const noexcept;

	/**
	* Returns whether or not two types are the same
	* @param rhs
	*/
	bool operator!=(const TypeInfo& rhs) const noexcept;

	/**
	* Get type info of the requested type
	*/
	template<typename T>
	static TypeInfo& Get() noexcept;

	/**
	* Returns id of this type info
	*/
	size_t GetID() const noexcept;

	/**
	* Returns name of this type info
	*/
	const char* GetName() const noexcept;

private:

	size_t m_ID;
	const char* m_Name;
};

/**
* @}
*/

#include "Registry.h"

template<typename T>
inline Factory& Factory::Get() noexcept
{
	return *Reflectpp::Registry::Instance().GetFactory<T>();
}

template<typename T>
inline Registration Registration::base() noexcept
{
	Reflectpp::Registry::Instance().AddBase<T>(m_Type);
	return *this;
}

template<typename T>
inline Registration Registration::class_() noexcept
{
	return Registration(Reflectpp::Registry::Instance().AddType<T>());
}

template<typename T, typename PropertyT, typename U>
inline Registration Registration::property(const char* name, PropertyT T::* addr) noexcept
{
	Reflectpp::Registry::Instance().AddProperty(m_Type, name, addr);
	return *this;
}

template<typename T>
inline Type& Type::Get() noexcept
{
	return *Reflectpp::Registry::Instance().GetType<T>();
}

template<typename T>
inline Type& Type::Get(T*& object) noexcept
{
	return *Reflectpp::Registry::Instance().GetType(object);
}

template<typename T>
inline TypeInfo& TypeInfo::Get() noexcept
{
	return *Reflectpp::Registry::Instance().GetTypeInfo<T>();
}
