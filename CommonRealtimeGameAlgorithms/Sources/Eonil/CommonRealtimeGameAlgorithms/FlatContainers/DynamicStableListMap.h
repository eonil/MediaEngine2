//
//  DynamicStableOrderlessSet.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 5/3/14.
//
//

#pragma once
#include "../CommonRealtimeGameAlgorithmsCommon.h"
EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN




/*!
 Provides limit-less dynamic set.

 @discussion
 C++11 standard containers (a.k.a. STL) doesn't provide a container with these
 attributes.

 -	Stability --- Fully stable pointer for all operations.
 -	Ordering-free --- No ordering or sorting requisite.
 -	Hash-free --- No hash stuff requisite.
 -	Density --- Guaranteed to be dense as much as possible for cache affinity.
	(doesn't need to be completely consecutive)
 -	Complexity --- O(1) complexity for single element mutation operations such
	as `insert/erase`.
 -	Simplicity --- Erasable by pointer rather then iterator. This is important
	becausee pointer is the only type which can be derived from the value
	itself directly.

 For example,

 -	`std::vector` lacks stability and complexity.
 -	`std::list/std::foaward_list` lacks density and simplicity. For example, you
	can't erase an item using pointer to it. Well designed list classes may have
	cache locality theoretically, but not forced by a standard.
 -	`std::set/std::map` needs ordering.
 -	`std::unordered_set/std::unordered_map` needs hashing.
 -	`std::deque` lacks stability.

 @classdesign
 Though this grows and reduces automatically, but reduction is not very unlikely
 to happen due to guarantee of stability. You can perform trigger reduction by
 compacting by erasing and inserting items at bad locations.

 This is al incremental-only structure. Growth is very likely to happen, but
 reduction is not due to guarantee of stability. Growth is done

 @param
 LEN
 Maximum total item count.

 @param
 PARTITION
 Dynamic memory allocation unit.
 */
template <typename T, Size const LEN, Size const PARTITION = 16>
class
DynamicStableListMap
{
public:
private:
};





EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
