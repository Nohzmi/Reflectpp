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
	* Generic Factory \n
	* Allow to call on constructor / destructor
	*/
	class REFLECTPP_API Factory final
	{
		using ConstructorT = void* (*)();
		using CopyT = void* (*)(void*);
		using DestructorT = void (*)(void*);

	public:

		/**
		* Constructor
		*/
		Factory() = delete;

		/**
		* Destructor
		*/
		~Factory() = default;

		/**
		* Copy constructor
		*/
		Factory(const Factory&) = default;

		/**
		* Move constructor
		*/
		Factory(Factory&&) noexcept = default;

		/**
		* Copy assignement operator
		*/
		Factory& operator=(const Factory&) = default;

		/**
		* Move assignement operator
		*/
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
		* Get factory of requested type
		*/
		template<typename T>
		static Factory Get() noexcept;

	private:

		/**
		* Construct a factory
		* @param constructor
		* @param copy
		* @param destructor
		*/
		Factory(ConstructorT constructor, CopyT copy, DestructorT destructor) noexcept;

	private:

		const ConstructorT m_Constructor;
		const CopyT m_Copy;
		const DestructorT m_Destructor;
	};

	/**
	* Equivalent to std::type_info
	*/
	class REFLECTPP_API TypeInfo final
	{
	public:

		/**
		* Constructor
		*/
		TypeInfo() = delete;

		/**
		* Destructor
		*/
		~TypeInfo() = default;

		/**
		* Copy constructor
		*/
		TypeInfo(const TypeInfo&) = default;

		/**
		* Move constructor
		*/
		TypeInfo(TypeInfo&&) noexcept = default;

		/**
		* Copy assignement operator
		*/
		TypeInfo& operator=(const TypeInfo&) = default;

		/**
		* Move assignement operator
		*/
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
		static TypeInfo Get() noexcept;

		/**
		* Returns id of this type
		*/
		size_t GetID() const noexcept;

		/**
		* Returns name of this type
		*/
		const char* GetName() const noexcept;

		/**
		* Returns type id of the given type
		*/
		template<typename T>
		static size_t ID() noexcept;

		/**
		* Returns type id of the given object
		* @param object
		*/
		template<typename T>
		static size_t ID(T*& object) noexcept;

		/**
		* Returns type name of the given type
		*/
		template<typename T>
		static const char* Name() noexcept;

		/**
		* Returns type name of the given object
		* @param object
		*/
		template<typename T>
		static const char* Name(T*& object) noexcept;

	private:

		/**
		* Construct a type info
		* @param id
		* @param name
		*/
		TypeInfo(size_t id, const char* name) noexcept;

	private:

		const size_t m_ID;
		const char* m_Name;
	};

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
		friend void ::register_function() noexcept;

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
		const std::vector<const Type*>& GetBaseTypes() const noexcept;

		/**
		* Returns derived types of this type
		*/
		const std::vector<const Type*>& GetDerivedTypes() const noexcept;

		/**
		* Returns factory of this type
		*/
		const Factory& GetFactory() const noexcept;

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
		const Property* GetProperty(const char* name) const noexcept;

		/**
		* Returns all property of this type
		*/
		const std::vector<const Property*>& GetProperties() const noexcept;

		/**
		* Returns size of this type
		*/
		size_t GetSize() const noexcept;

		/**
		* Returns type info of this type
		*/
		const TypeInfo& GetTypeInfo() const noexcept;

		/**
		* Register a property of the current type
		* @param name
		* @param addr
		*/
		template<typename T, typename PropertyT>
		Type& property(const char* name, PropertyT T::* addr) noexcept;

	private:

		/**
		* Construct a type representation
		* @param factory
		* @param size
		* @param typeinfo
		*/
		Type(const Factory& factory, size_t size, const TypeInfo& typeinfo) noexcept;

		/**
		* Register a type in reflection
		* @param factory
		* @param size
		* @param typeinfo
		*/
		static Type* AddType(const Factory& factory, size_t size, const TypeInfo& typeinfo) noexcept;

		/**
		* Returns requested type representation
		* @param id
		*/
		static Type* FindType(size_t id) noexcept;

		/**
		* Register a type in reflection
		*/
		template<typename T>
		static Type& class_() noexcept;

	private:

		std::vector<const Type*> m_BaseTypes;
		std::vector<const Type*> m_DerivedTypes;
		const Factory m_Factory;
		size_t m_HierarchyID;
		std::vector<const Property*> m_Properties;
		static PropertyDatabase m_PropertyDatabase;
		const size_t m_Size;
		static TypeDatabase m_TypeDatabase;
		const TypeInfo m_TypeInfo;
	};

	/**
	* inline
	*/

	template<typename T>
	inline Factory Factory::Get() noexcept
	{
		auto constructor = []() -> void*
		{
			if constexpr (std::is_constructible_v<T>)
				return new T();
			else
				return nullptr;
		};

		auto copy = [](void* object) -> void*
		{
			if constexpr (std::is_copy_constructible_v<T>)
				return new T(*static_cast<T*>(object));
			else
				return nullptr;
		};

		auto destructor = [](void* object)
		{
			if constexpr (std::is_destructible_v<T>)
				delete static_cast<T*>(object);
		};

		return Factory(constructor, copy, destructor);
	}

	template<typename T>
	inline TypeInfo TypeInfo::Get() noexcept
	{
		return TypeInfo(ID<T>(), Name<T>());
	}

	template<typename T>
	inline size_t TypeInfo::ID() noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).hash_code();
		else
			return T::TypeID();
	}

	template<typename T>
	inline size_t TypeInfo::ID(T*& object) noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).hash_code();
		else
			return object->GetTypeID();
	}

	template<typename T>
	inline const char* TypeInfo::Name() noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).name();
		else
			return T::TypeName();
	}

	template<typename T>
	inline const char* TypeInfo::Name(T*& object) noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).name();
		else
			return object->GetTypeName();
	}

	template<typename T>
	inline Type& Type::base() noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !Reflectpp::is_valid<T>::value)
		{
			Reflectpp::Assert(false, "Type::base<%s>() : invalid type\n", TypeInfo::Name<T>());
			return *const_cast<Type*>(Get<void>());
		}
		else
		{
			Type* base{ const_cast<Type*>(Get<T>()) };

			for (auto it : m_BaseTypes)
				Reflectpp::Assert(it != base, "Type::base<%s>() : base type already registered\n", base->GetName());

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
			Reflectpp::Assert(false, "Type::Cast<%s>(%s*& object) : not a pointer\n", TypeInfo::Name<T>(), TypeInfo::Name(object));
			return nullptr;
		}
		else if constexpr (std::is_const_v<V> || std::is_pointer_v<V> || std::is_void_v<V> || std::is_volatile_v<V>)
		{
			Reflectpp::Assert(false, "Type::Cast<%s>(%s*& object) : invalid type\n", TypeInfo::Name<T>(), TypeInfo::Name(object));
			return nullptr;
		}
		else if constexpr (std::is_const_v<U> || std::is_void_v<U> || std::is_volatile_v<U>)
		{
			Reflectpp::Assert(false, "Type::Cast<%s>(%s*& object) : invalid object type\n", TypeInfo::Name<T>(), TypeInfo::Name(object));
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
			Reflectpp::Assert(false, "Type::Get<%s>() : invalid type\n", TypeInfo::Name<T>());
			return nullptr;
		}
		else
		{
			const auto it{ FindType(TypeInfo::ID<T>()) };

			if (it == nullptr)
			{
				if constexpr (std::is_arithmetic_v<T>)
				{
					return AddType(Factory::Get<T>(), sizeof(T), TypeInfo::Get<T>());
				}
				else
				{
					Reflectpp::Assert(false, "Type::Get<%s>() : unregistered type\n", TypeInfo::Name<T>());
				}
			}

			return it;
		}
	}

	template<typename T>
	inline const Type* Type::Get(T*& object) noexcept
	{
		if constexpr (std::is_null_pointer_v<T> || std::is_void_v<T> || std::is_volatile_v<T>)
		{
			Reflectpp::Assert(false, "Type::Get(%s*& object) : invalid type\n", TypeInfo::Name<T>());
			return nullptr;
		}
		else if constexpr (!std::is_arithmetic_v<T> && !Reflectpp::use_macro<T>::value)
		{
			Reflectpp::Assert(false, "Type::Get(%s*& object) : unregistered type\n", TypeInfo::Name(object));
			return nullptr;
		}
		else
		{
			Reflectpp::Assert(object != nullptr, "Type::Get(%s*& object) : object nullptr\n", TypeInfo::Name<T>());

			if constexpr (!std::is_arithmetic_v<T>)
				return m_TypeDatabase.find(TypeInfo::ID(object))->second.get();
			else
				return Get<T>();
		}
	}

	template<typename T, typename PropertyT>
	inline Type& Type::property(const char* name, PropertyT T::* addr) noexcept
	{
		std::hash<std::string> hasher;

		for (auto it : m_Properties)
			Reflectpp::Assert(it->GetID() != hasher(name), "Type::property(const char* name, %s %s::* addr) : %s already registered\n", TypeInfo::Name<PropertyT>(), TypeInfo::Name<T>(), name);

		m_PropertyDatabase.emplace_back(new Property(hasher(name), name, reinterpret_cast<size_t>(&(reinterpret_cast<T const volatile*>(nullptr)->*addr)), Get<std::remove_cv_t<PropertyT>>()));
		const_cast<Type*>(Get<T>())->m_Properties.emplace_back(m_PropertyDatabase.back().get());

		return *this;
	}

	template<typename T>
	inline Type& Type::class_() noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !is_valid<T>::value)
		{
			Assert(false, "Type::class_<%s>() : invalid type\n", TypeInfo::Name<T>());
			return *const_cast<Type*>(Type::Get<void>());
		}
		else if constexpr (!Reflectpp::use_macro<T>::value)
		{
			Assert(false, "Type::class_<%s>() : REFLECT(T) macro not used\n", TypeInfo::Name<T>());
			return *const_cast<Type*>(Type::Get<void>());
		}
		else
		{
			Type* type{ AddType(Factory::Get<T>(), sizeof(T), TypeInfo::Get<T>()) };
			Assert(type != nullptr, "Type::class_<%s>() : type already registered\n", TypeInfo::Name<T>());
			return *type;
		}
	}
}

/**
* @}
*/
