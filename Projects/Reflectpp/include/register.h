// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file register.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/core/forward.h"
#include "details/core/hasher.h"
#include "details/core/type_info_helper.h"

#define REFLECT(T)																\
private:																		\
																				\
	friend reflectpp::details::has_registered<T>;								\
	friend reflectpp::details::registry;										\
	friend size_t reflectpp::details::type_id<T>() REFLECTPP_NOEXCEPT;			\
	friend const char* reflectpp::details::type_name<T>() REFLECTPP_NOEXCEPT;	\
	friend void register_function() REFLECTPP_NOEXCEPT;							\
																				\
	void registered() REFLECTPP_NOEXCEPT;										\
																				\
	virtual size_t get_type_id() const REFLECTPP_NOEXCEPT						\
	{																			\
		static const size_t type_id{ reflectpp::details::hash(#T) };			\
		return type_id;															\
	}																			\
																				\
	virtual const char* get_type_name() const REFLECTPP_NOEXCEPT				\
	{																			\
		return #T;																\
	}																			\
																				\
	static size_t type_id() REFLECTPP_NOEXCEPT									\
	{																			\
		static const size_t type_id{ reflectpp::details::hash(#T) };			\
		return type_id;															\
	}																			\
																				\
	static const char* type_name() REFLECTPP_NOEXCEPT							\
	{																			\
		return #T;																\
	}																			\


static void register_function() REFLECTPP_NOEXCEPT;
