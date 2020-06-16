// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file Register.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <typeinfo>

/**
* @addtogroup Reflectpp
* @{
*/

#define REFLECT()															\
public:																		\
friend void register_function() noexcept;									\
virtual size_t GetTypeID() const noexcept									\
{																			\
	static const size_t typeID{ typeid(decltype(*this)).hash_code() };		\
	return typeID;															\
}																			\
private:																	\

/**
* Contains all utility functions \n
* Mainly to generate type informations
*/
namespace Reflectpp
{
	/**
	* Allow to know if REFLECT macro is used \n
	* Works only if GetTypeID() is public
	*/
	template <typename T>
	class HasGetTypeID
	{
	private:
		typedef char TrueType[1];
		typedef char FalseType[2];

		template <typename C> static TrueType& test(decltype(&C::GetTypeID));
		template <typename C> static FalseType& test(...);

	public:
		enum { value = sizeof(test<T>(0)) == sizeof(TrueType) };
	};
}

/**
* @}
*/
