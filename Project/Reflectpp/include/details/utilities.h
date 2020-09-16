// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file Registry.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <cassert>
#include <functional>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <vector>

#ifndef REFLECTPP_API
#ifdef REFLECTPP_DLL
#define REFLECTPP_API __declspec(dllexport)
#else
#define REFLECTPP_API __declspec(dllimport)
#endif
#endif

class Factory;
class Property;
class Type;
class TypeInfo;

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

	template <class ...Args>
	void Assert(bool expr, const char* format, Args... args) noexcept;

	template<typename T>
	static size_t TypeID() noexcept;

	template<typename T>
	static size_t TypeID(T* object) noexcept;

	template<typename T>
	static const char* TypeName() noexcept;

	template<typename T>
	static const char* TypeName(T* object) noexcept;

#pragma warning(push)
#pragma warning(disable: 4251)

	class REFLECTPP_API Registry final
	{
		using ConstructorT = void* (*)();
		using CopyT = void* (*)(void*);
		using DestructorT = void (*)(void*);
		using GetterT = std::function<void* (void*, bool&)>;
		using SetterT = std::function<void(void*, void*)>;

	public:

		Registry(const Registry&) = delete;
		Registry(Registry&&) noexcept = delete;
		Registry& operator=(const Registry&) = delete;
		Registry& operator=(Registry&&) noexcept = delete;

		template<typename T>
		Type* AddBase(Type* type) noexcept;

		template<typename T, typename PropertyT, typename U = typename std::remove_cv_t<PropertyT>>
		Property* AddProperty(Type* type, const char* name, PropertyT T::* addr) noexcept;

		template<typename T, typename PropertyT, typename U = typename std::remove_cv_t<std::remove_reference_t<PropertyT>>>
		Property* AddProperty(Type* type, const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT)) noexcept;

		template<typename T>
		Type* AddType() noexcept;

		template<typename T, typename U, typename V = typename std::remove_pointer_t<T>>
		std::remove_pointer_t<T>* Cast(U* object) noexcept;

		static Registry& Instance() noexcept;

		template<typename T>
		Factory* GetFactory() noexcept;

		template<typename T>
		Type* GetType() noexcept;

		template<typename T>
		Type* GetType(T* object) noexcept;

		template<typename T>
		TypeInfo* GetTypeInfo() noexcept;

	private:

		Registry();
		~Registry();

		Type* AddBase(Type* type, Type* base) noexcept;
		Factory* AddFactory(size_t id, ConstructorT constructor, CopyT copy, DestructorT destructor) noexcept;
		Property* AddProperty(Type* type, const char* name, size_t offset, Type* propertytype) noexcept;
		Property* AddProperty(Type* type, const char* name, GetterT getter, SetterT setter, Type* propertytype) noexcept;
		Type* AddType(Factory* factory, size_t size, TypeInfo* typeinfo) noexcept;
		TypeInfo* AddTypeInfo(size_t id, const char* name) noexcept;
		bool Cast(Type* type, Type* otype) const noexcept;
		Factory* GetFactory(size_t id) const noexcept;
		Type* GetType(size_t id) const noexcept;
		TypeInfo* GetTypeInfo(size_t id) const noexcept;
		Property* GetProperty(size_t id) const noexcept;

		std::unordered_map<size_t, std::unique_ptr<Factory>> m_Factories;
		std::vector<std::unique_ptr<Property>> m_Properties;
		std::vector<std::unique_ptr<TypeInfo>> m_TypeInfos;
		std::vector<std::unique_ptr<Type>> m_Types;
		static Registry m_Value;
	};

#pragma warning (pop)
}

#include "Type.h"

namespace Reflectpp
{
	template<class ...Args>
	void Assert(bool expr, const char* format, Args ...args) noexcept
	{
		if (!expr)
		{
			printf(format, args...);
			assert(false);
		}
	}

	template<typename T>
	size_t TypeID() noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).hash_code();
		else
			return T::TypeID();
	}

	template<typename T>
	size_t TypeID(T* object) noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).hash_code();
		else
			return object->GetTypeID();
	}

	template<typename T>
	const char* TypeName() noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).name();
		else
			return T::TypeName();
	}

	template<typename T>
	const char* TypeName(T* object) noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !use_macro<T>::value)
			return typeid(T).name();
		else
			return object->GetTypeName();
	}

	template<typename T>
	inline Type* Registry::AddBase(Type* type) noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !is_valid<T>::value)
		{
			Assert(false, "Registration::base<%s>() : invalid type\n", TypeName<T>());
			return nullptr;
		}
		else
		{
			Type* base{ AddBase(type, GetType<T>()) };
			Assert(base != nullptr, "Registration::base<%s>() : base type already registered\n", base->GetName());

			return base;
		}
	}

	template<typename T, typename PropertyT, typename U>
	inline Property* Registry::AddProperty(Type* type, const char* name, PropertyT T::* addr) noexcept
	{
		Assert(*GetType<T>() == *type, "Registration::property(const char* name, %s %s::* addr) : %s isn't in %s\n", TypeName<U>(), TypeName<T>(), name, type->GetName());
		Property* prop{ AddProperty(type, name, (size_t)(char*)&((T*)nullptr->*addr), GetType<U>()) };
		Assert(prop != nullptr, "Registration::property(const char* name, %s %s::* addr) : %s already registered\n", TypeName<U>(), TypeName<T>(), name);

		return prop;
	}

	template<typename T, typename PropertyT, typename U>
	inline Property* Registry::AddProperty(Type* type, const char* name, PropertyT(T::* getter)() const, void(T::* setter)(PropertyT)) noexcept
	{
		Assert(*GetType<T>() == *type, "Registration::property(const char* name, %s %s::* addr) : %s isn't in %s\n", TypeName<U>(), TypeName<T>(), name, type->GetName());

		auto get = [getter](void* object, bool& isOwner) -> void*
		{
			if constexpr (std::is_reference_v<PropertyT>)
			{
				isOwner = false;
				const U& tmp{ (static_cast<T*>(object)->*getter)() };

				return const_cast<U*>(&tmp);
			}
			else
			{
				isOwner = true;
				U* val{ new U() };
				*val = (static_cast<T*>(object)->*getter)();

				return  val;
			}
		};

		auto set = [setter](void* object, void* value)
		{
			(static_cast<T*>(object)->*setter)(*static_cast<U*>(value));
		};

		Property* prop{ AddProperty(type, name, get, set, GetType<U>()) };
		Assert(prop != nullptr, "Registration::property(const char* name, %s %s::* addr) : %s already registered\n", TypeName<U>(), TypeName<T>(), name);

		return prop;
	}

	template<typename T>
	inline Type* Registry::AddType() noexcept
	{
		if constexpr (std::is_arithmetic_v<T> || !is_valid<T>::value)
		{
			Assert(false, "Registration::class_<%s>() : invalid type\n", TypeName<T>());
			return nullptr;
		}
		else if constexpr (!use_macro<T>::value)
		{
			Assert(false, "Registration::class_<%s>() : REFLECT(T) macro isn't used\n", TypeName<T>());
			return nullptr;
		}
		else
		{
			Type* type{ AddType(GetFactory<T>(), sizeof(T), GetTypeInfo<T>()) };
			Assert(type != nullptr, "Registration::class_<%s>() : type already registered\n", TypeName<T>());

			return type;
		}
	}

	template<typename T, typename U, typename V>
	inline std::remove_pointer_t<T>* Registry::Cast(U* object) noexcept
	{
		if constexpr (!std::is_pointer_v<T>)
		{
			Assert(false, "Type::Cast<%s>(%s*& object) : not a pointer\n", TypeName<T>(), TypeName(object));
			return nullptr;
		}
		else if constexpr (std::is_const_v<V> || std::is_pointer_v<V> || std::is_void_v<V> || std::is_volatile_v<V>)
		{
			Assert(false, "Type::Cast<%s>(%s*& object) : invalid type\n", TypeName<T>(), TypeName(object));
			return nullptr;
		}
		else if constexpr (std::is_const_v<U> || std::is_void_v<U> || std::is_volatile_v<U>)
		{
			Assert(false, "Type::Cast<%s>(%s*& object) : invalid object type\n", TypeName<T>(), TypeName(object));
			return nullptr;
		}
		else
			return Cast(GetType<V>(), GetType(object)) ? reinterpret_cast<T>(object) : nullptr;
	}

	template<typename T>
	inline Factory* Registry::GetFactory() noexcept
	{
		Factory* factory{ GetFactory(TypeID<T>()) };

		if (factory != nullptr)
			return factory;

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

		return AddFactory(TypeID<T>(), constructor, copy, destructor);
	}

	template<typename T>
	inline Type* Registry::GetType() noexcept
	{
		if constexpr (!is_valid<T>::value)
		{
			Assert(false, "Type::Get<%s>() : invalid type\n", TypeName<T>());
			return nullptr;
		}
		else if constexpr (std::is_arithmetic_v<T>)
		{
			Type* type{ GetType(TypeID<T>()) };

			if (type == nullptr)
				return AddType(GetFactory<T>(), sizeof(T), GetTypeInfo<T>());

			return type;
		}
		else
		{
			Type* type{ GetType(TypeID<T>()) };
			Assert(type != nullptr, "Type::Get<%s>() : unregistered type\n", TypeName<T>());

			return type;
		}
	}

	template<typename T>
	inline Type* Registry::GetType(T* object) noexcept
	{
		if constexpr (std::is_null_pointer_v<T> || std::is_void_v<T> || std::is_volatile_v<T>)
		{
			Assert(false, "Type::Get(%s*& object) : invalid type\n", TypeName<T>());
			return nullptr;
		}
		else if constexpr (!std::is_arithmetic_v<T> && !use_macro<T>::value)
		{
			Assert(false, "Type::Get(%s*& object) : unregistered type\n", TypeName(object));
			return nullptr;
		}
		else if constexpr (std::is_arithmetic_v<T>)
		{
			Assert(object != nullptr, "Type::Get(%s*& object) : object nullptr\n", TypeName<T>());

			Type* type{ GetType(TypeID<T>()) };

			if (type == nullptr)
				return AddType(GetFactory<T>(), sizeof(T), GetTypeInfo<T>());

			return type;
		}
		else
		{
			Assert(object != nullptr, "Type::Get(%s*& object) : object nullptr\n", TypeName<T>());
			return GetType(TypeID(object));
		}
	}

	template<typename T>
	inline TypeInfo* Registry::GetTypeInfo() noexcept
	{
		TypeInfo* typeInfo{ GetTypeInfo(TypeID<T>()) };

		if (typeInfo != nullptr)
			return typeInfo;

		return AddTypeInfo(TypeID<T>(), TypeName<T>());
	}
}

template<typename T>
inline Variant::Variant(T* object) noexcept :
	m_Data{ object },
	m_IsOwner{ false },
	m_Type{ &Type::Get(object) }
{
}

template<typename T>
inline T& Variant::GetValue() noexcept
{
	Reflectpp::Assert(IsValid(), "Variant::GetValue<%s>() : invalid variant\n", Reflectpp::TypeName<T>());
	Reflectpp::Assert(Type::Get<T>() == *m_Type, "Variant::GetValue<%s>() : wrong type, stored value is a %s\n", Reflectpp::TypeName<T>(), m_Type->GetName());

	return *static_cast<T*>(m_Data);
}

template<typename T>
inline const T& Variant::GetValue() const noexcept
{
	Reflectpp::Assert(IsValid(), "Variant::GetValue<%s>() : invalid variant\n", Reflectpp::TypeName<T>());
	Reflectpp::Assert(Type::Get<T>() == *m_Type, "Variant::GetValue<%s>() : wrong type, stored value is a %s\n", Reflectpp::TypeName<T>(), m_Type->GetName());

	return *static_cast<T*>(m_Data);
}

template<typename T>
inline bool Variant::IsType() const noexcept
{
	return IsValid() ? Type::Get<T>() == *m_Type : false;
}

template<typename T>
inline Factory& Factory::Get() noexcept
{
	return *Reflectpp::Registry::Instance().GetFactory<T>();
}

template<typename T>
inline Variant Property::GetValue(T* object) const
{
	Reflectpp::Assert(Type::Get(object) == *m_Type, "Property::GetValue(%s*& object) : wrong object type, %s is in %s\n", Reflectpp::TypeName(object), m_Name, m_Type->GetName());

	if (m_Getter != nullptr)
	{
		bool isOwner{ false };
		void* data{ m_Getter(object, isOwner) };

		return Variant(data, isOwner, m_PropertyType);
	}
	else
		return Variant(reinterpret_cast<char*>(object) + m_Offset, false, m_PropertyType);
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

template<typename T>
inline TypeInfo& TypeInfo::Get() noexcept
{
	return *Reflectpp::Registry::Instance().GetTypeInfo<T>();
}

template<typename T, typename U>
inline T Type::Cast(U* object) noexcept
{
	return Reflectpp::Registry::Instance().Cast<T>(object);
}

template<typename T>
inline Type& Type::Get() noexcept
{
	return *Reflectpp::Registry::Instance().GetType<T>();
}

template<typename T>
inline Type& Type::Get(T* object) noexcept
{
	return *Reflectpp::Registry::Instance().GetType(object);
}
