// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file Type.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <functional>
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

namespace Reflectpp
{
	class Registry;
}

class Property;
class Type;

/**
* Allows to store data of any type
*/
class REFLECTPP_API Variant final
{
	friend Property;
	friend Type;

public:

	Variant();
	~Variant();
	Variant(const Variant&);
	Variant(Variant&&) noexcept = default;
	Variant& operator=(const Variant&);
	Variant& operator=(Variant&&) noexcept = default;

	/**
	* Create a variant from a object \n
	* Don't have the ownership in this case
	* @param object
	*/
	template<typename T>
	Variant(T*& object) noexcept;

	/**
	* Returns whether or not the stored a value is valid
	*/
	operator bool() const;

	/**
	* Clear the stored value of this variant
	*/
	void Clear() noexcept;

	/**
	* Returns the type of the stored value
	*/
	Type& GetType() const noexcept;

	/**
	* Returns the value as requested type \n
	* Use IsType() to check if the type is valid
	*/
	template<typename T>
	T& GetValue() noexcept;

	/**
	* Returns the value as requested type \n
	* Use IsType() to check if the type is valid
	*/
	template<typename T>
	const T& GetValue() const noexcept;

	/**
	* Returns whether or not the stored value is the same type as requested type
	*/
	template<typename T>
	bool IsType() const noexcept;

	/**
	* Returns whether or not the stored a value is valid
	*/
	bool IsValid() const noexcept;

private:

	Variant(void* data, bool isOwner, Type* type) noexcept;

	void* m_Data;
	bool m_IsOwner;
	Type* m_Type;
};

/**
* Generic factory class used in reflection \n
* Independent of the reflection
*/
class REFLECTPP_API Factory final
{
	friend Reflectpp::Registry;

	using ConstructorT = void* (*)();
	using CopyT = void* (*)(void*);
	using DestructorT = void (*)(void*);

public:

	Factory() = delete;
	~Factory() = default;
	Factory(const Factory&) = default;
	Factory(Factory&&) noexcept = default;
	Factory& operator=(const Factory&) = default;
	Factory& operator=(Factory&&) noexcept = default;

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

	Factory(ConstructorT constructor, CopyT copy, DestructorT destructor) noexcept;

	ConstructorT m_Constructor;
	CopyT m_Copy;
	DestructorT m_Destructor;
};

#pragma warning(push)
#pragma warning(disable: 4251)

/**
* Show a property of a class in reflection
*/
class REFLECTPP_API Property final
{
	friend Reflectpp::Registry;

	using GetterT = std::function<void* (void*, bool&)>;
	using SetterT = std::function<void(void*, void*)>;

public:

	Property() = delete;
	~Property() = default;
	Property(const Property&) = delete;
	Property(Property&&) noexcept = default;
	Property& operator=(const Property&) = delete;
	Property& operator=(Property&&) noexcept = default;

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

	/**
	* Returns value of the property from an object of the type that contains it
	* @param object
	*/
	template<typename T>
	Variant GetValue(T*& object) const;

	/**
	* Returns value of the property from an object of the type that contains it
	* @param object
	*/
	Variant GetValue(Variant& object) const;

private:

	Property(GetterT getter, size_t id, const char* name, size_t offset, Type* propertyType, SetterT setter, Type* type) noexcept;

	GetterT m_Getter;
	size_t m_ID;
	const char* m_Name;
	size_t m_Offset;
	Type* m_PropertyType;
	SetterT m_Setter;
	Type* m_Type;
};

#pragma warning (pop)

template<typename T>
class Range final
{
	friend Reflectpp::Registry;

public:

	template<typename T>
	class Iterator
	{
		friend Range<T>;

	public:

		~Iterator() = default;
		Iterator(const Iterator&) = default;
		Iterator(Iterator&&) noexcept = default;
		Iterator& operator=(const Iterator&) = default;
		Iterator& operator=(Iterator&&) noexcept = default;

		bool operator==(const Iterator<T>& rhs) const;
		bool operator!=(const Iterator<T>& rhs) const;
		Iterator<T>& operator++();
		T& operator*() const;

	private:

		Iterator() = default;

		size_t m_Index;
		const Range<T>* m_Range;
	};

	Range() = default;
	~Range() = default;
	Range(const Range&) = delete;
	Range(Range&&) noexcept = default;
	Range& operator=(const Range&) = delete;
	Range& operator=(Range&&) noexcept = default;

	T& operator[] (size_t n) const noexcept;
	Iterator<T> begin() const noexcept;
	bool empty() const noexcept;
	Iterator<T> end() const noexcept;
	size_t size() const noexcept;

private:

	std::vector<T*> m_Vector;
};

/**
* Allow to register a type in reflection \n
* and his base types and properties too
*/
class REFLECTPP_API Registration final
{
	friend Reflectpp::Registry;

public:

	Registration() = delete;
	~Registration() = default;
	Registration(const Registration&) = default;
	Registration(Registration&&) noexcept = default;
	Registration& operator=(const Registration&) = default;
	Registration& operator=(Registration&&) noexcept = default;

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
	template<typename T, typename PropertyT>
	Registration property(const char* name, PropertyT T::* addr) noexcept;

	/**
	* Register a property of the current type
	* @param name
	* @param getter
	* @param setter
	*/
	template<typename T, typename PropertyT>
	Registration property(const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT)) noexcept;

private:

	Registration(Type* type) noexcept;

	Type* m_Type;
};

/**
* Equivalent to std::type_info \n
* Independent of the reflection
*/
class REFLECTPP_API TypeInfo final
{
	friend Reflectpp::Registry;

public:

	TypeInfo() = delete;
	~TypeInfo() = default;
	TypeInfo(const TypeInfo&) = default;
	TypeInfo(TypeInfo&&) noexcept = default;
	TypeInfo& operator=(const TypeInfo&) = default;
	TypeInfo& operator=(TypeInfo&&) noexcept = default;

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

	TypeInfo(size_t id, const char* name) noexcept;

	size_t m_ID;
	const char* m_Name;
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
	* Allows to cast between class hierarchies up, down and side
	* @param object
	*/
	template<typename T, typename U>
	static T Cast(U*& object) noexcept;

	/**
	* Returns a variant of this type
	*/
	Variant Create() const;

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
	Range<Type>& GetBaseTypes() const noexcept;

	/**
	* Returns derived types of this type
	*/
	Range<Type>& GetDerivedTypes() const noexcept;

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
	Range<Property>& GetProperties() const noexcept;

	/**
	* Returns size of this type
	*/
	size_t GetSize() const noexcept;

	/**
	* Returns type info of this type
	*/
	TypeInfo& GetTypeInfo() const noexcept;

private:

	Type(Factory* factory, size_t size, TypeInfo* typeinfo) noexcept;

	Range<Type> m_BaseTypes;
	Range<Type> m_DerivedTypes;
	Factory* m_Factory;
	size_t m_HierarchyID;
	Range<Property> m_Properties;
	size_t m_Size;
	TypeInfo* m_TypeInfo;
};

#pragma warning (pop)

/**
* @}
*/

#include "Registry.h"
