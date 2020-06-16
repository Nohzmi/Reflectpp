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

/**
* @addtogroup Reflectpp
* @{
*/

#ifdef REFLECTPP_DLL
#define REFLECTPP_API __declspec(dllexport)
#else
#define REFLECTPP_API __declspec(dllimport)
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

/**
* Contains all utility functions \n
* Mainly to generate type informations
*/
namespace Reflectpp
{
	/**
	* Allow to know if a type id valid at compile time
	*/
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
	* Allow to know if REFLECT macro is used \n
	* Works only for public functions
	*/
	template <typename T>
	class use_macro
	{
	private:
		typedef char TrueType[1];
		typedef char FalseType[2];

		template <typename C> static TrueType& test(decltype(&C::TypeID));
		template <typename C> static FalseType& test(...);

	public:
		enum { value = sizeof(test<T>(0)) == sizeof(TrueType) };
	};

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
	* Returns type id of the given object
	* @param object
	*/
	template<typename T>
	size_t GetTypeID(T*& object) noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).hash_code();
		else
			return object->GetTypeID();
	}

	/**
	* Returns type name of the given object
	* @param object
	*/
	template<typename T>
	const char* GetTypeName(T*& object) noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).name();
		else
			return object->GetTypeName();
	}

	/**
	* Returns type id of the given type
	*/
	template<typename T>
	size_t TypeID() noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).hash_code();
		else
			return T::TypeID();
	}

	/**
	* Returns type name of the given type
	*/
	template<typename T>
	const char* TypeName() noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).name();
		else
			return T::TypeName();
	}
}

class Type;

/**
* The basic type representation
*/
class REFLECTPP_API Property final
{
public:

	/**
	* Constructor
	*/
	Property() = delete;

	/**
	* Destructor
	*/
	~Property() = default;

	/**
	* Copy constructor
	*/
	Property(const Property&) = delete;

	/**
	* Move constructor
	*/
	Property(Property&&) noexcept = default;

	/**
	* Copy assignement operator
	*/
	Property& operator=(const Property&) = delete;

	/**
	* Move assignement operator
	*/
	Property& operator=(Property&&) noexcept = default;

	/**
	* Construct a property
	* @param id
	* @param name
	* @param offset
	* @param type
	*/
	Property(size_t id, const char* name, size_t offset, const Type* type) noexcept;

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
	const Type* GetType() const noexcept;

private:

	const size_t m_ID;
	const char* m_Name;
	const size_t m_Offset;
	const Type* m_Type;
};

/**
* The basic type representation \n
* Also serves as type database
*/
class REFLECTPP_API Type final
{
	friend void register_function() noexcept;

	using CopyConstructorT = void* (*)(void*);
	using ConstructorT = void* (*)();
	using PropertyDatabase = std::vector<std::unique_ptr<Property>>;
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
	* Returns property by name of this type
	* @param name
	*/
	const Property* GetProperty(const char* name) const noexcept;

	/**
	* Returns all property of this type
	*/
	std::vector<const Property*> GetProperties() const noexcept;

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
	* Register a property of the current type
	* @param name
	* @param addr
	*/
	template<typename T, typename PropertyT>
	Type& property(const char* name, PropertyT T::* addr) noexcept;

private:

	/**
	* Register a type in reflection
	* @param name
	*/
	template<typename T>
	static Type& class_() noexcept;

private:

	std::vector<const Type*> m_BaseTypes;
	const ConstructorT m_Constructor;
	const CopyConstructorT m_CopyConstructor;
	std::vector<const Type*> m_DerivedTypes;
	static PropertyDatabase m_PropertyDatabase;
	std::vector<const Property*> m_Properties;
	size_t m_HierarchyID;
	const size_t m_ID;
	const char* m_Name;
	const size_t m_Size;
	static TypeDatabase m_TypeDatabase;
};

template<typename T>
inline Type& Type::base() noexcept
{
	if constexpr (std::is_arithmetic_v<T> || !Reflectpp::is_valid<T>::value)
	{
		Reflectpp::Assert(false, "Type::base<%s>() : invalid type\n", Reflectpp::TypeName<T>());
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
				if (type->m_HierarchyID == hierarchyID)
					return;

				const_cast<Type*>(type)->m_HierarchyID = hierarchyID;

				for (auto it : type->m_BaseTypes)
					lambda(it, hierarchyID, lambda);

				for (auto it : type->m_DerivedTypes)
					lambda(it, hierarchyID, lambda);
			};

			updateHierarchy(base, m_HierarchyID, updateHierarchy);
		}

		base->m_DerivedTypes.emplace_back(this);
		m_BaseTypes.emplace_back(base);
		m_Properties.insert(m_Properties.cbegin(), base->m_Properties.cbegin(), base->m_Properties.cbegin());

		return *this;
	}
}

template<typename T, typename U, typename V>
inline std::remove_pointer_t<T>* Type::Cast(U*& object) noexcept
{
	if constexpr (!std::is_pointer_v<T>)
	{
		Reflectpp::Assert(false, "Type::Cast<%s>(%s*& object) : not a pointer\n", Reflectpp::TypeName<T>(), Reflectpp::GetTypeName(object));
		return nullptr;
	}
	else if constexpr (std::is_const_v<V> || std::is_pointer_v<V> || std::is_void_v<V> || std::is_volatile_v<V>)
	{
		Reflectpp::Assert(false, "Type::Cast<%s>(%s*& object) : invalid type\n", Reflectpp::TypeName<T>(), Reflectpp::GetTypeName(object));
		return nullptr;
	}
	else if constexpr (std::is_const_v<U> || std::is_void_v<U> || std::is_volatile_v<U>)
	{
		Reflectpp::Assert(false, "Type::Cast<%s>(%s*& object) : invalid object type\n", Reflectpp::TypeName<T>(), Reflectpp::GetTypeName(object));
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
		Reflectpp::Assert(false, "Type::Get<%s>() : invalid type\n", Reflectpp::TypeName<T>());
		return nullptr;
	}
	else
	{
		const auto it{ m_TypeDatabase.find(Reflectpp::TypeID<T>()) };

		if (it == m_TypeDatabase.cend())
		{
			if constexpr (std::is_arithmetic_v<T>)
			{
				Type* type{ new Type(Reflectpp::ConstructObject<T>, Reflectpp::CopyObject<T>, Reflectpp::TypeID<T>(), Reflectpp::TypeName<T>(), sizeof(T)) };
				m_TypeDatabase.emplace(Reflectpp::TypeID<T>(), type);

				return type;
			}
			else
			{
				Reflectpp::Assert(false, "Type::Get<%s>() : unregistered type\n", Reflectpp::TypeName<T>());
			}
		}

		return it->second.get();
	}
}

template<typename T>
inline const Type* Type::Get(T*& object) noexcept
{
	if constexpr (std::is_null_pointer_v<T> || std::is_void_v<T> || std::is_volatile_v<T>)
	{
		Reflectpp::Assert(false, "Type::Get(%s*& object) : invalid type\n", Reflectpp::TypeName<T>());
		return nullptr;
	}
	else if constexpr (!std::is_arithmetic_v<T> && !Reflectpp::use_macro<T>::value)
	{
		Reflectpp::Assert(false, "Type::Get(%s*& object) : unregistered type\n", Reflectpp::GetTypeName(object));
		return nullptr;
	}
	else
	{
		Reflectpp::Assert(object != nullptr, "Type::Get(%s*& object) : object nullptr\n", Reflectpp::TypeName<T>());

		if constexpr (std::is_arithmetic_v<T>)
		{
			return Get<T>();
		}
		else
		{
			return m_TypeDatabase.find(Reflectpp::GetTypeID(object))->second.get();
		}
	}
}

template<typename T, typename PropertyT>
inline Type& Type::property(const char* name, PropertyT T::* addr) noexcept
{
	std::hash<std::string> hasher;

	for (auto it : m_Properties)
		Reflectpp::Assert(it->GetID() != hasher(name), "Type::property(const char* name, %s %s::* addr) : %s already registered\n", Reflectpp::TypeName<PropertyT>(), Reflectpp::TypeName<T>(), name);

	m_PropertyDatabase.emplace_back(new Property(hasher(name), name, reinterpret_cast<size_t>(&(reinterpret_cast<T const volatile*>(nullptr)->*addr)), Get<std::remove_cv_t<PropertyT>>()));
	const_cast<Type*>(Get<T>())->m_Properties.emplace_back(m_PropertyDatabase.back().get());

	return *this;
}

template<typename T>
inline Type& Type::class_() noexcept
{
	if constexpr (std::is_arithmetic_v<T> || !Reflectpp::is_valid<T>::value)
	{
		Reflectpp::Assert(false, "Type::class_<%s>() : invalid type\n", Reflectpp::TypeName<T>());
		return *const_cast<Type*>(Type::Get<void>());
	}
	else if constexpr (!Reflectpp::use_macro<T>::value)
	{
		Reflectpp::Assert(false, "Type::class_<%s>() : REFLECT(T) macro not used\n", Reflectpp::TypeName<T>());
		return *const_cast<Type*>(Type::Get<void>());
	}
	else
	{
		Reflectpp::Assert(Type::m_TypeDatabase.find(Reflectpp::TypeID<T>()) == Type::m_TypeDatabase.cend(), "Type::class_<%s>() : type already registered\n", Reflectpp::TypeName<T>());

		Type* type{ new Type(Reflectpp::ConstructObject<T>, Reflectpp::CopyObject<T>, Reflectpp::TypeID<T>(), Reflectpp::TypeName<T>(), sizeof(T)) };
		Type::m_TypeDatabase.emplace(Reflectpp::TypeID<T>(), type);

		return *type;
	}
}

/**
* @}
*/
