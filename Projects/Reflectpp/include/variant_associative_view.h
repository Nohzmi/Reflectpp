// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant_associative_view.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include <utility>

#include "details/forward.h"
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
	* Allows to store associative containers of any type \n
	* Sequence container: map, unordered_map, ...etc
	*/
	class REFLECTPP_API variant_associative_view final
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
			iterator(size_t index, variant_associative_view* variant) REFLECTPP_NOEXCEPT;

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
			std::pair<variant, variant> operator*() const REFLECTPP_NOEXCEPT;
			size_t get_index() const REFLECTPP_NOEXCEPT;// a voir si inutile
			variant get_key() const REFLECTPP_NOEXCEPT;
			variant get_value() const REFLECTPP_NOEXCEPT;

		private:

			size_t m_index;
			variant_associative_view* m_variant_associative_view;
		};

		variant_associative_view() = default;
		~variant_associative_view() = default;
		variant_associative_view(const variant_associative_view&) = default;
		variant_associative_view(variant_associative_view&&) REFLECTPP_NOEXCEPT = default;
		variant_associative_view& operator=(const variant_associative_view&) = default;
		variant_associative_view& operator=(variant_associative_view&&) REFLECTPP_NOEXCEPT = default;
		explicit variant_associative_view(const details::variant_data& data) REFLECTPP_NOEXCEPT;

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
		* Returns a range containing all elements with the given key in the container
		* @param key
		*/
		std::pair<iterator, iterator> equal_range(argument key) const REFLECTPP_NOEXCEPT;

		/**
		* Removes the element with the key
		* @param key
		*/
		void erase(argument key) REFLECTPP_NOEXCEPT;
		//TODO return size_t in rttr

		/**
		* Finds an element with specific key
		* @param key
		*/
		iterator find(argument key) REFLECTPP_NOEXCEPT;

		/**
		* Returns the key type of the container
		*/
		type get_key_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the number of elements
		*/
		size_t get_size() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the type of the container
		*/
		type get_type() const REFLECTPP_NOEXCEPT;

		/**
		* Returns the value type of the container
		*/
		type get_value_type() const REFLECTPP_NOEXCEPT;

		/**
		* Insert a key into the container
		* @param key
		*/
		//iterator insert(argument key) const REFLECTPP_NOEXCEPT;

		/**
		* Insert a key-value pair into the container
		* @param key
		* @param value
		*/
		void insert(argument key, argument value) const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the container has elements
		*/
		bool is_empty() const REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		bool is_valid() const REFLECTPP_NOEXCEPT;

	private:

		details::variant_data m_data;
	};
}

/**
* @}
*/
