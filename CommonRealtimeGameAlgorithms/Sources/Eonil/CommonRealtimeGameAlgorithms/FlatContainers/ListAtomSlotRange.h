//
//  ListAtomSlotRange.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/29.
//
//

#pragma once

#include "../CommonRealtimeGameAlgorithmsCommon.h"
#include "ListAtomSlotIterator.h"
#include "../GenericUtilities/IterationRange.h"

EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN




template <typename T>		using	ListAtomSlotRange		=	GenericUtilities::IterationRange<ListAtomSlotIterator<T>>;





///*!
// Single pointer sized object which wraps pointer to an list-atom-slot.
// Accessing target value-object in the slot will become effectively zero-cost
// because it will ultimately reduced into a same pointer at machine level.
// 
// It's recommended to store this iterator to point a target value.
// */
//template <typename T>
//class
//ListAtomSlotRange final
//{
//public:
//	ListAtomSlotRange() = default;
//	ListAtomSlotRange(ListAtomSlotIterator<T> begin, ListAtomSlotIterator<T> end);
//	
//	template <typename C>
//	ListAtomSlotRange(C& container) : ListAtomSlotRange(container.begin(), container.end())
//	{
//	}
//
//	
////	auto	begin() const -> ListAtomSlotIterator<T const>;
//	auto	begin() -> ListAtomSlotIterator<T>;
////	auto	end() const -> ListAtomSlotIterator<T const>;
//	auto	end() -> ListAtomSlotIterator<T>;
//	
//private:
//	ListAtomSlotIterator<T>	_begin	{};
//	ListAtomSlotIterator<T>	_end	{};
//};
//
//
//
//
//template <typename T>
//ListAtomSlotRange<T>::
//ListAtomSlotRange(ListAtomSlotIterator<T> begin, ListAtomSlotIterator<T> end) : _begin(begin), _end(end)
//{
//}
//
//template <typename T> auto
//ListAtomSlotRange<T>::
//begin() -> ListAtomSlotIterator<T>
//{
//	return	_begin;
//}
//template <typename T> auto
//ListAtomSlotRange<T>::
//end() -> ListAtomSlotIterator<T>
//{
//	return	_end;
//}
//

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	






EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
