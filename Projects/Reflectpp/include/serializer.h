// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file serializer.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <nlohmann/json.hpp>

#include "instance.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	/**
	* Generic factory class used in reflection \n
	* Independent of the reflection
	*/
	class REFLECTPP_API serializer final
	{
	public:

		serializer() = delete;
		~serializer() = default;
		serializer(const serializer&) = default;
		serializer(serializer&&) REFLECTPP_NOEXCEPT = default;
		serializer& operator=(const serializer&) = default;
		serializer& operator=(serializer&&) REFLECTPP_NOEXCEPT = default;

		/**
		* Create a variant from a object
		* @param path
		*/
		serializer(const char* path) REFLECTPP_NOEXCEPT;

		/**
		* Serialize an object
		* @param object
		*/
		void save(instance object) const REFLECTPP_NOEXCEPT;

		/**
		* Deserialize an object
		* @param object
		*/
		void load(instance object) const REFLECTPP_NOEXCEPT;

	private:

		void save_type(const variant& var, nlohmann::json& j) const REFLECTPP_NOEXCEPT;
		void load_type(variant& var, const nlohmann::json& j) const REFLECTPP_NOEXCEPT;

		const char* m_path{ "default" };
	};
}

/**
* @}
*/
