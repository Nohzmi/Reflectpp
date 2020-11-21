// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file register.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/hasher.h"

#define REFLECT(T)													\
public:																\
friend void register_function() noexcept;							\
virtual size_t get_type_id() const noexcept							\
{																	\
	static const size_t type_id{ reflectpp::details::hash(#T) };	\
	return type_id;													\
}																	\
virtual const char* get_type_name() const noexcept					\
{																	\
	return #T;														\
}																	\
static size_t type_id() noexcept									\
{																	\
	static const size_t type_id{ reflectpp::details::hash(#T) };	\
	return type_id;													\
}																	\
static const char* type_name() noexcept								\
{																	\
	return #T;														\
}																	\
private:															\

static void register_function() noexcept;
