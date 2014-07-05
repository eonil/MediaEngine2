////
////  StaticStableSharingList.h
////  CommonRealtimeGameAlgorithms
////
////  Created by Hoon H. on 5/3/14.
////
////
//
//#pragma once
//#include "../CommonRealtimeGameAlgorithmsCommon.h"
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN
//
//
//
//
//
//
//
//
///*!
// A stable orderless map which shares storage.
// 
// @discussion
// Static containers mean fixed capacity.
// This is problematic when you need flexible storage.
// 
// Here's an example. Let's say we have two lists.
// 
// 1.	source items.
// 2.	referencing pointers.
// 
// If source items are 512 sized, and if we need big enough list which
// can contain all of the source items, then pointer list must be also
// 512 sized. If we need to have multiple pointer lists, then memory
// consumption goes `512 * N`. This is unaffordable.
// 
// If we have one big storage of pointers which is shared among all the
// pointer lists, then we just need `512` sized storage for all
// because soure items are limited to `512` at max!
// 
// Finally, we can reduce memory consumption from O(n*m) to O(n) for the
// situation. This is pretty big advantage.
// 
// Anyway in reality, we need extra overhead to manage partitioning of
// subsets, but still far smaller then O(n*m).
// 
// @classdesign
// This is essentially a singly linked list. Follows most of performance 
// attributes of a linked list --- slow iteration. Because items can be located
// very sparsely.
// 
// Anyway, all the items will ultimately be placed in a flat and dense 
// (consecutive) memory, so if you iterate all the items in the complete storage,
// it will be pretty fast.StaticStableSharingList
// 
// @param
// PART
// Number of items in a partition.
// 
// @param
// MULT
// Number of partitions.
// */
//template <typename T, Size const PART, Size const MULT>
//class
//StaticStableSharingList
//{
//private:
//	struct
//	ITEM
//	{
//		ListAtomSlot<T>	slot	=	{};
//		uint16_t		nidx	=	~(0x0);
//	};
//	
//	using	PARTITION	=	StaticStableListMap<T, 16>;
//	using	MAPPING		=	StaticStableListMap<PARTITION*, 8>;
//	
//	class
//	Partition
//	{
//		StaticStableListStack<PARTITION, MULT>;
//	};
//	
//public:
//	class	Partition;
//	class	Storage;
//	
//	class
//	Storage
//	{
//	private:
//		StaticStableOrderlessSet<T, LEN>		_all_items_set		=	{};
//		StaticStableListMap<Partition*, LEN>	_partiion_mappings	=	{};
//	};
//	class
//	Subset
//	{
//	public:
//	private:
//		Storage*	_storage	=	nullptr;
//		Size		_count		=	0;
//	};
//};
//
//
//
//
//
//
//
//
//
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
