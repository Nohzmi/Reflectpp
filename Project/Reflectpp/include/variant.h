// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/platform.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	class type;
	class property;

	/**
	* Allows to store data of any type
	*/
	class REFLECTPP_API variant final
	{
		friend property;
		friend type;

	public:

		variant();
		~variant();
		variant(const variant&);
		variant(variant&&) noexcept = default;
		variant& operator=(const variant&);
		variant& operator=(variant&&) noexcept = default;

		/**
		* Create a variant from a object \n
		* Don't have the ownership in this case
		* @param object
		*/
		template<typename T>
		variant(T* object) noexcept;

		/**
		* Returns whether or not the stored a value is valid
		*/
		operator bool() const;

		/**
		* Clear the stored value of this variant
		*/
		void clear() noexcept;

		/**
		* Returns the type of the stored value
		*/
		type& get_type() const noexcept;

		/**
		* Returns the value as requested type \n
		* Use IsType() to check if the type is valid
		*/
		template<typename T>
		T& get_value() noexcept;

		/**
		* Returns the value as requested type \n
		* Use IsType() to check if the type is valid
		*/
		template<typename T>
		const T& get_value() const noexcept;

		/**
		* Returns whether or not the stored value is the same type as requested type
		*/
		template<typename T>
		bool is_type() const noexcept;

		/**
		* Returns whether or not the stored a value is valid
		*/
		bool is_valid() const noexcept;

	private:

		variant(void* data, bool is_owner, type* type) noexcept;

		void* m_data;
		bool m_is_owner;
		type* m_type;
	};
}

/**
* @}
*/
