// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file serializer.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/registry.h"
#include "variant.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
#pragma warning(push)
#pragma warning(disable: 4251)

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
		serializer(serializer&&) noexcept = default;
		serializer& operator=(const serializer&) = default;
		serializer& operator=(serializer&&) noexcept = default;

		/**
		* Create a variant from a object
		* @param path
		*/
		serializer(const char* path);

		/**
		* Serialize an object
		* @param object
		*/
		template<typename T>
		void save(const T& object) noexcept;

		/**
		* Deserialize an object
		* @param object
		*/
		template<typename T>
		void load(T& object) const noexcept;

	private:

		void save(const variant& var) noexcept;
		void load(variant& var) const noexcept;

		std::string m_path;
	};

#pragma warning (pop)
}

#include "details/inline/serializer.inl"

/**
* @}
*/
