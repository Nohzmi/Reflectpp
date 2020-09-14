// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file Register.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <functional>
#include <string>

#define REFLECT(T)												\
public:															\
friend void register_function() noexcept;						\
virtual size_t GetTypeID() const noexcept						\
{																\
	static const std::hash<std::string> hasher;					\
	static const size_t typeID{ hasher(std::string(#T)) };		\
	return typeID;												\
}																\
virtual const char* GetTypeName() const noexcept				\
{																\
	return #T;													\
}																\
static size_t TypeID() noexcept									\
{																\
	static const std::hash<std::string> hasher;					\
	static const size_t typeID{ hasher(std::string(#T)) };		\
	return typeID;												\
}																\
static const char* TypeName() noexcept							\
{																\
	return #T;													\
}																\
private:														\

static void register_function() noexcept;
