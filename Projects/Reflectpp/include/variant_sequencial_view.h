// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file variant_sequencial_view.h
* @author Nohzmi
* @version 1.0
*/

#pragma once //TODO peut etre include registry ^^'
#include "details/macros.h"
#include "details/platform.h"
#include "details/factory_data.h"
#include "details/type_data.h"
#include "details/variant_data.h"

/**
* @addtogroup Reflectpp
* @{
*/

namespace reflectpp
{
	class argument;
	class type;
	class variant;

	/**
	* Allows to store sequence containers of any type \n
	* Sequence container: vector, list, ...etc
	*/
	class REFLECTPP_API variant_sequencial_view final
	{
	public:

		class REFLECTPP_API iterator
		{
			friend variant_sequencial_view;

		public:

			iterator() = default;
			~iterator() = default;
			iterator(const iterator&) = default;
			iterator(iterator&&) REFLECTPP_NOEXCEPT = default;
			iterator& operator=(const iterator&) = default;
			iterator& operator=(iterator&&) REFLECTPP_NOEXCEPT = default;
			iterator(size_t index, variant_sequencial_view* variant) REFLECTPP_NOEXCEPT;

			REFLECTPP_INLINE bool operator==(const iterator& rhs) const REFLECTPP_NOEXCEPT;
			REFLECTPP_INLINE bool operator!=(const iterator& rhs) const REFLECTPP_NOEXCEPT;
			REFLECTPP_INLINE iterator& operator++() REFLECTPP_NOEXCEPT;
			REFLECTPP_INLINE iterator operator++(int) REFLECTPP_NOEXCEPT;
			REFLECTPP_INLINE iterator& operator--() REFLECTPP_NOEXCEPT;
			REFLECTPP_INLINE iterator operator--(int) REFLECTPP_NOEXCEPT;
			REFLECTPP_INLINE iterator& operator+=(int i) REFLECTPP_NOEXCEPT;
			REFLECTPP_INLINE iterator operator+(int i) REFLECTPP_NOEXCEPT;
			REFLECTPP_INLINE iterator& operator-=(int i) REFLECTPP_NOEXCEPT;
			REFLECTPP_INLINE iterator operator-(int i) REFLECTPP_NOEXCEPT;
			variant operator*() const REFLECTPP_NOEXCEPT;
			variant get_data() const REFLECTPP_NOEXCEPT;

		private:

			size_t m_index;
			variant_sequencial_view* m_variant_sequencial_view;
		};

		variant_sequencial_view() = default;
		REFLECTPP_INLINE ~variant_sequencial_view();
		REFLECTPP_INLINE variant_sequencial_view(const variant_sequencial_view&);
		variant_sequencial_view(variant_sequencial_view&&) REFLECTPP_NOEXCEPT = default;
		REFLECTPP_INLINE variant_sequencial_view& operator=(const variant_sequencial_view&);
		variant_sequencial_view& operator=(variant_sequencial_view&&) REFLECTPP_NOEXCEPT = default;
		REFLECTPP_INLINE explicit variant_sequencial_view(const details::variant_data& data) REFLECTPP_NOEXCEPT;

		/**
		* Returns whether or not the stored a value is valid
		*/
		REFLECTPP_INLINE operator bool() const;

		/**
		* Returns an iterator to the first element of the container
		*/
		REFLECTPP_INLINE iterator begin() const ;

		/**
		* Remove all elements from the containers
		*/
		REFLECTPP_INLINE void clear() ;

		/**
		* Returns an iterator to the element following the last element of the container
		*/
		REFLECTPP_INLINE iterator end() const ;

		/**
		* Removes the element at the position pos
		* @param pos
		*/
		REFLECTPP_INLINE iterator erase(const iterator& pos) ;

		/**
		* Returns the number of elements
		*/
		REFLECTPP_INLINE size_t get_size() const ;

		/**
		* Returns the type of the stored value
		*/
		type get_type() const ;

		/**
		* Returns the current value at index
		* @param index
		*/
		variant get_value(size_t index) const ;

		/**
		* Returns the data type of the stored value
		*/
		type get_value_type() const ;

		/**
		* Insert a value into the container
		* @param pos
		* @param value
		*/
		iterator insert(const iterator& pos, argument value) const ;

		/**
		* Returns whether or not the container has elements
		*/
		REFLECTPP_INLINE bool is_empty() const ;

		/**
		* Returns whether or not the stored a value is valid
		*/
		REFLECTPP_INLINE bool is_valid() const ;

		/**
		* Sets the size of the sequential container
		* @param size
		*/
		REFLECTPP_INLINE void set_size(size_t size) const ;

		/**
		* Set the content of the the argument at the specified index into the underlying sequential container
		* @param index
		* @param value
		*/
		void set_value(size_t index, argument value) const ;

	private:

		details::variant_data m_data;
	};
}

#include "details/inline/variant_sequencial_view.inl"

/**
* @}
*/
