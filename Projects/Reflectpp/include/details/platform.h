// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file platform.h
* @author Nohzmi
* @version 1.0
*/

#pragma once

#ifdef _WIN32
	#ifdef REFLECTPP_DLL
		#define REFLECTPP_API __declspec(dllexport)
	#else
		#define REFLECTPP_API __declspec(dllimport)
	#endif
#else
	#define REFLECTPP_API
#endif
