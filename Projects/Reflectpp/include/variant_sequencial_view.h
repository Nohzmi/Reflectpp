// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant_sequencial_view.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/macros.h"
#include "details/platform.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	namespace details
	{
		class sequence_type;
	}

	class argument;
	class type;
	class variant;

	/**
	* Allows to store sequence containers of any type \n
	* Sequence container: vector, list, ...etc
	*/
	class REFLECTPP_API variant_sequencial_view final
	{
		friend variant;

	public:

		class REFLECTPP_API iterator
		{
			friend variant_sequencial_view;

		public:

			~iterator() = default;
			iterator(const iterator&) = default;
			iterator(iterator&&) REFLECTPP_NOEXCEPT = default;
			iterator& operator=(const iterator&) = default;
			iterator& operator=(iterator&&) REFLECTPP_NOEXCEPT = default;

			bool operator==(const iterator& rhs) const REFLECTPP_NOEXCEPT;
			bool operator!=(const iterator& rhs) const REFLECTPP_NOEXCEPT;
			iterator& operator++() REFLECTPP_NOEXCEPT;
			iterator operator++(int) REFLECTPP_NOEXCEPT;
			iterator& operator--() REFLECTPP_NOEXCEPT;
			iterator operator--(int) REFLECTPP_NOEXCEPT;
			iterator& operator+=(int i) REFLECTPP_NOEXCEPT;
			iterator operator+(int i) REFLECTPP_NOEXCEPT;
			iterator& operator-=(int i) REFLECTPP_NOEXCEPT;
			iterator operator-(int i) REFLECTPP_NOEXCEPT;
			variant operator*() const REFLECTPP_NOEXCEPT;
			variant get_data() const REFLECTPP_NOEXCEPT;

		private:

			iterator() = default;

			size_t m_index;
			const variant_sequencial_view* m_variant_sequencial_view;
		};

		~variant_sequencial_view();
		variant_sequencial_view(const variant_sequencial_view&);
		variant_sequencial_view(variant_sequencial_view&&) REFLECTPP_NOEXCEPT = default;
		variant_sequencial_view& operator=(const variant_sequencial_view&);
		variant_sequencial_view& operator=(variant_sequencial_view&&) REFLECTPP_NOEXCEPT = default;

		/**
		* Returns whether or not the stored a value is valid
		*/
		operator bool() const ;

		/**
		* Returns an iterator to the first element of the container
		*/
		iterator begin() const ;

		/**
		* Remove all elements from the containers
		*/
		void clear() ;

		/**
		* Returns an iterator to the element following the last element of the container
		*/
		iterator end() const ;

		/**
		* Removes the element at the position pos
		* @param pos
		*/
		iterator erase(const iterator& pos) ;

		/**
		* Returns the number of elements
		*/
		size_t get_size() const ;

		/**
		* Returns the type of the stored value
		*/
		type& get_type() const ;

		/**
		* Returns the current value at index
		* @param index
		*/
		variant get_value(size_t index) const ;

		/**
		* Returns the data type of the stored value
		*/
		type& get_value_type() const ;

		/**
		* Insert a value into the container
		* @param pos
		* @param value
		*/
		iterator insert(const iterator& pos, const argument& value) const ;

		/**
		* Returns whether or not the container has elements
		*/
		bool is_empty() const ;

		/**
		* Returns whether or not the stored a value is valid
		*/
		bool is_valid() const ;

		/**
		* Sets the size of the sequential container
		* @param size
		*/
		void set_size(size_t size) const ;

		/**
		* Set the content of the the argument at the specified index into the underlying sequential container
		* @param index
		* @param value
		*/
		void set_value(size_t index, const argument& value) const ;

	private:

		variant_sequencial_view(void* data, bool is_owner, details::sequence_type* _sequence_type);

		void* m_data;
		bool m_is_owner;
		details::sequence_type* m_sequence_type;
	};
}

/**
* @}
*/
