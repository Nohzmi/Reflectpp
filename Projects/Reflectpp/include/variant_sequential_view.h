// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant_sequential_view.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/macros.h"
#include "details/platform.h"
#include "details/variant_data.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	/**
	* Allows to store sequence containers of any type \n
	* Sequence container: vector, list, ...etc
	*/
	class REFLECTPP_API variant_sequential_view final
	{
	public:

		class REFLECTPP_API iterator
		{
			friend variant_sequential_view;

		public:

			iterator() = default;
			~iterator() = default;
			iterator(const iterator&) = default;
			iterator(iterator&&) REFLECTPP_NOEXCEPT = default;
			iterator& operator=(const iterator&) = default;
			iterator& operator=(iterator&&) REFLECTPP_NOEXCEPT = default;
			explicit iterator(size_t index, variant_sequential_view* variant) REFLECTPP_NOEXCEPT;

			bool operator==(const iterator& rhs) const REFLECTPP_NOEXCEPT;
			bool operator!=(const iterator& rhs) const REFLECTPP_NOEXCEPT;
			iterator& operator++() REFLECTPP_NOEXCEPT;
			iterator operator++(int) REFLECTPP_NOEXCEPT;
			iterator& operator--() REFLECTPP_NOEXCEPT;
			iterator operator--(int) REFLECTPP_NOEXCEPT;
			iterator& operator+=(size_t i) REFLECTPP_NOEXCEPT;
			iterator operator+(size_t i) REFLECTPP_NOEXCEPT;
			iterator& operator-=(size_t i) REFLECTPP_NOEXCEPT;
			iterator operator-(size_t i) REFLECTPP_NOEXCEPT;
			variant operator*() const REFLECTPP_NOEXCEPT;
			variant get_data() const REFLECTPP_NOEXCEPT;

		private:

			size_t m_index{ 0 };
			variant_sequential_view* m_variant{ nullptr };
		};

		variant_sequential_view() = default;
		~variant_sequential_view() = default;
		variant_sequential_view(const variant_sequential_view&) = default;
		variant_sequential_view(variant_sequential_view&&) REFLECTPP_NOEXCEPT = default;
		variant_sequential_view& operator=(const variant_sequential_view&) = default;
		variant_sequential_view& operator=(variant_sequential_view&&) REFLECTPP_NOEXCEPT = default;
		explicit variant_sequential_view(const details::variant_data& data) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored value is valid
		*/
		explicit operator bool() const REFLECTPP_NOEXCEPT;

		/**
		* Returns an iterator to the first element of the container
		*/
		iterator begin() const REFLECTPP_NOEXCEPT;

		/**
		* Remove all elements from the containers
		*/
		void clear() REFLECTPP_NOEXCEPT;

		/**
		* Returns an iterator to the element following the last element of the container
		*/
		iterator end() const REFLECTPP_NOEXCEPT;

		/**
		* Removes the element at the position pos
		* Return iterator following the removed element
		* @param pos
		*/
		iterator erase(const iterator& pos) REFLECTPP_NOEXCEPT;

		/**
		* Returns the number of elements in the sequential container
		*/
		size_t get_size() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type object of this sequential container
		*/
		type get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the current value at index
		* @param index
		*/
		variant get_value(size_t index) const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type object from the value of this sequential container
		*/
		type get_value_type() const REFLECTPP_NOEXCEPT;

		/**
		* Insert a value into the container
		* Return an iterator to the inserted element, otherwise an invalid iterator, when the insertion was not possible
		* @param pos
		* @param value
		*/
		iterator insert(const iterator& pos, argument value) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the container is dynamic \n
		* When a sequential view is dynamic, it is possible to change its size, clear its content or insert and erase values from it
		*/
		bool is_dynamic() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the container has elements
		*/
		bool is_empty() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored value is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

		/**
		* Sets the size of the sequential container \n
		* Returns whether or not the size could be changed
		* @param size
		*/
		bool set_size(size_t size) REFLECTPP_NOEXCEPT;

		/**
		* Set the content of the the argument at the specified index into the underlying sequential container
		* Returns whether or not the value could be set
		* @param index
		* @param value
		*/
		bool set_value(size_t index, argument value) REFLECTPP_NOEXCEPT;

	private:

		details::variant_data m_data;
	};
}

/**
* @}
*/
