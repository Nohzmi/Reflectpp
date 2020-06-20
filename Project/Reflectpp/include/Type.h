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

namespace Reflectpp
{
	class Registry;
}

class Type;
class TypeInfo;

/**
* Generic factory class used in reflection \n
* Independent of the reflection
*/
class REFLECTPP_API Factory final
{
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
	Factory(ConstructorT constructor, CopyT copy, DestructorT destructor) noexcept;

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

	ConstructorT m_Constructor;
	CopyT m_Copy;
	DestructorT m_Destructor;
};

/**
* Show a property of a class in reflection
*/
class REFLECTPP_API Property final
{
	using GetterT = void* (*)(void*);
	using SetterT = void (*)(void*, void*);

public:

	Property() = delete;
	~Property() = default;
	Property(const Property&) = delete;
	Property(Property&&) noexcept = default;
	Property& operator=(const Property&) = delete;
	Property& operator=(Property&&) noexcept = default;
	Property(void* getter, size_t id, const char* name, size_t offset, void* setter, Type* type) noexcept;

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

	void* m_Getter;
	size_t m_ID;
	const char* m_Name;
	size_t m_Offset;
	void* m_Setter;
	Type* m_Type;
};

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
	* Allows to cast between class hierarchies up, down and side
	* @param object
	*/
	template<typename T, typename U>
	static T Cast(U*& object) noexcept;

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

template<typename T> template<typename U>
inline bool Range<T>::Iterator<U>::operator==(const Iterator<U>& rhs) const
{
	return (m_Index == rhs.m_Index) && (m_Range == rhs.m_Range);
}

template<typename T> template<typename U>
inline bool Range<T>::Iterator<U>::operator!=(const Iterator<U>& rhs) const
{
	return (m_Index != rhs.m_Index) || (m_Range != rhs.m_Range);
}

template<typename T> template<typename U>
inline Range<T>::Iterator<U>& Range<T>::Iterator<U>::operator++()
{
	++m_Index;
	return *this;
}

template<typename T> template<typename U>
inline U& Range<T>::Iterator<U>::operator*() const
{
	return (*m_Range)[m_Index];
}

template<typename T>
inline T& Range<T>::operator[](size_t n) const noexcept
{
	return *m_Vector[n];
}

template<typename T>
inline Range<T>::Iterator<T> Range<T>::begin() const noexcept
{
	Iterator<T> it;
	it.m_Index = 0;
	it.m_Range = this;

	return it;
}

template<typename T>
inline bool Range<T>::empty() const noexcept
{
	return m_Vector.empty();
}

template<typename T>
inline Range<T>::Iterator<T> Range<T>::end() const noexcept
{
	Iterator<T> it;
	it.m_Index = size();
	it.m_Range = this;

	return it;
}

template<typename T>
inline size_t Range<T>::size() const noexcept
{
	return m_Vector.size();
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

template<typename T, typename PropertyT>
inline Registration Registration::property(const char* name, PropertyT T::* addr) noexcept
{
	Reflectpp::Registry::Instance().AddProperty(m_Type, name, addr);
	return *this;
}

template<typename T, typename PropertyT>
inline Registration Registration::property(const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT)) noexcept
{
	Reflectpp::Registry::Instance().AddProperty(m_Type, name, getter, setter);
	return *this;
}

template<typename T, typename U>
inline T Type::Cast(U*& object) noexcept
{
	return Reflectpp::Registry::Instance().Cast<T>(object);
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
