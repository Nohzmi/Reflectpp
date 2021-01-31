// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file custom_associative_container.hpp
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/associative_container.hpp"

/*********************************************************************************************************/
/*                                                                                                       */
/*  Function requirements:                                                                               */
/*    begin: iterator (*)(T* container)                                                                  */
/*    end: iterator (*)(T* container)                                                                    */
/*                                                                                                       */
/*  Function optional:                                                                                   */
/*    clear: void (*)(T* container)                                                                      */
/*    equal_range: std::pair<iterator, iterator> (*)(T* container, const key_type& key)                  */
/*    erase: size_t (*)(T* container, const key_type& key)                                               */
/*    find: iterator (*)(T* container, const key_type& key)                                              */
/*    insert: std::pair<iterator, bool> (*)(T* container, const key_type& key)                           */
/*    insert: std::pair<iterator, bool> (*)(T* container, const key_type& key, const value_type& value)  */
/*    size: size_t (*)(T* container)                                                                     */
/*                                                                                                       */
/*  Member type requirements:                                                                            */
/*    iterator                                                                                           */
/*    key_type                                                                                           */
/*    mapped_type                                                                                        */
/*                                                                                                       */
/*********************************************************************************************************/

namespace reflectpp
{
	namespace details
	{
		// See example in "details/associative_container.hpp"
	}
}
