// Copyright (c) 2020, Nohzmi. All rights reserved.

/**
* @file custom_sequence_container.h
* @author Nohzmi
* @version 1.0
*/

#pragma once
#include "details/custom/sequence_container_array.h"
#include "details/custom/sequence_container_basic_string.h"
#include "details/custom/sequence_container_deque.h"
#include "details/custom/sequence_container_forward_list.h"
#include "details/custom/sequence_container_list.h"
#include "details/custom/sequence_container_vector.h"

/*********************************************************************************/
/*                                                                               */
/*  Function requirements:                                                       */
/*    begin: iterator (*)(T* container)                                          */
/*    end: iterator (*)(T* container)                                            */
/*                                                                               */
/*  Function optional:                                                           */
/*    at: value_type& (*)(T* container, size_t pos);                             */
/*    clear: void (*)(T* container)                                              */
/*    erase: iterator (*)(T* container, iterator pos)                            */
/*    insert: iterator (*)(T* container, iterator pos, const value_type& value)  */
/*    resize: void (*)(T* container, size_t count)                               */
/*    size: size_t (*)(T* container)                                             */
/*                                                                               */
/*  Member type requirements:                                                    */
/*    iterator                                                                   */
/*    value_type                                                                 */
/*                                                                               */
/*********************************************************************************/

namespace reflectpp
{
	namespace details
	{
		// See examples in "details/custom/sequence_container_*.h"
	}
}
