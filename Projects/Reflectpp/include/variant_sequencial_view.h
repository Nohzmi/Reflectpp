// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant_sequencial_view.h
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
	class REFLECTPP_API variant_sequencial_view final
	{
	public:

		class REFLECTPP_API iterator
		{
		public:

			iterator() = default;
			~iterator() = default;
			iterator(const iterator&) = default;
			iterator(iterator&&) REFLECTPP_NOEXCEPT = default;
			iterator& operator=(const iterator&) = default;
			iterator& operator=(iterator&&) REFLECTPP_NOEXCEPT = default;
			iterator(size_t index, variant_sequencial_view* variant) REFLECTPP_NOEXCEPT;

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
			size_t get_index() const REFLECTPP_NOEXCEPT;

		private:

			size_t m_index;
			variant_sequencial_view* m_variant_sequencial_view;
		};

		variant_sequencial_view() = default;
		~variant_sequencial_view() = default;
		variant_sequencial_view(const variant_sequencial_view&) = default;
		variant_sequencial_view(variant_sequencial_view&&) REFLECTPP_NOEXCEPT = default;
		variant_sequencial_view& operator=(const variant_sequencial_view&) = default;
		variant_sequencial_view& operator=(variant_sequencial_view&&) REFLECTPP_NOEXCEPT = default;
		explicit variant_sequencial_view(const details::variant_data& data) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
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
		* @param pos
		*/
		iterator erase(const iterator& pos) REFLECTPP_NOEXCEPT;

		/**
		* Returns the number of elements
		*/
		size_t get_size() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type of the stored value
		*/
		type get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the current value at index
		* @param index
		*/
		variant get_value(size_t index) const REFLECTPP_NOEXCEPT;

		/**
		* Returns the data type of the stored value
		*/
		type get_value_type() const REFLECTPP_NOEXCEPT;

		/**
		* Insert a value into the container
		* @param pos
		* @param value
		*/
		iterator insert(const iterator& pos, argument value) const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the container has elements
		*/
		bool is_empty() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

		/**
		* Sets the size of the sequential container
		* @param size
		*/
		void set_size(size_t size) const REFLECTPP_NOEXCEPT;

		/**
		* Set the content of the the argument at the specified index into the underlying sequential container
		* @param index
		* @param value
		*/
		void set_value(size_t index, argument value) const REFLECTPP_NOEXCEPT;

	private:

		details::variant_data m_data;
	};
}

/**
* @}
*/
