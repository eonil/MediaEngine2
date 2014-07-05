////
////  ObjectPack.h
////  CommonRealtimeGameAlgorithms
////
////  Created by Hoon H. on 14/4/30.
////
////
//
//#pragma once
//
//#include "../CommonRealtimeGameAlgorithmsCommon.h"
//#include "MemoryStorage.h"
//#include <bitset>
//
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_BEGIN
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
///*!
// More compact/batched version of `ListAtomSlot`.
// 
// Length of a pack is fixed by hardware system.
// 
// @classdesign
// An array of `ListAtomSlot` with compacted occupation marker prefix.
// 
// @param
// LEN
// It's recommended to set this to a multiplication of machine native alignment.
// I recommend to use just default value.
// */
//template <typename T, Size const LEN = alignof(uintptr_t) * std::numeric_limits<uintptr_t>::digits>
//class
//ObjectPack : ExceptionSupportTools
//{
//	using	OCCS	=	std::bitset<LEN>;
//	using	MEM		=	MemoryStorage<T>;
//	using	MEMS	=	std::array<MEM, LEN>;
//	
//	static_assert(sizeof(MEMS) == sizeof(MEM) * LEN, "Unsupported system. Cannot satisfy precise memory layout assumption.");
//	
//	
//	
//public:
//	~ObjectPack();
//	
//	auto	capacity() const noexcept -> Size;
//	auto	size() const noexcept -> Size;
//	auto	empty() const noexcept -> bool;
//	auto	full() const noexcept -> bool;
//	
//	/*!
//	 Resolves index from a pointer to a value.
//	 
//	 @note
//	 This uses pointer address arithmetics to calculate offset.
//	 */
//	auto	index(T const*) const -> Size;
////	auto	index(ConstIterator) const -> Size;
//	
//	auto	at(Size const& index) const -> T const&;
//	auto	at(Size const& index) -> T&;
//	
////	auto	begin() const -> ConstIterator;
////	auto	begin() -> Iterator;
////	auto	end() const -> ConstIterator;
////	auto	end() -> Iterator;
//	
//	template <typename... ARGS>
//	auto	emplace(Size const index, ARGS&&... args) -> void;
//	auto	insert(Size const index, T const& v) -> void;
//	auto	insert(Size const index, T&& v) -> void;
//	auto	erase(Size const index) -> void;
//	auto	clear() -> void;
//	
//private:
//	OCCS	_occupations	{};
//	MEMS	_memories		{};
//	
//	static_assert(sizeof(_occupations) == sizeof(typename std::aligned_storage<sizeof(OCCS)>::type), "The bitset is not aligned properly. That may affect performance, and prohibited");
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
//
//template <typename T, Size const LEN>
//ObjectPack<T,LEN>::
//~ObjectPack()
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	clear();
//}
//
//template <typename T, Size const LEN> auto
//ObjectPack<T,LEN>::
//capacity() const noexcept -> Size
//{
//	return	LEN;
//}
//template <typename T, Size const LEN> auto
//ObjectPack<T,LEN>::
//size() const noexcept -> Size
//{
//	return	_occupations.count();
//}
//template <typename T, Size const LEN> auto
//ObjectPack<T,LEN>::
//empty() const noexcept -> bool
//{
//	return	_occupations.none();
//}
//template <typename T, Size const LEN> auto
//ObjectPack<T,LEN>::
//full() const noexcept -> bool
//{
//	return	_occupations.all();
//}
//
//template <typename T, Size const LEN> auto
//ObjectPack<T,LEN>::
//at(const Size &index) const -> T const&
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		error_if(not _occupations[index], "No value was set to the slot at index.");
//	}
//	
//	////
//	
//	return	_memories.at(index).value();
//}
//
//
//
//template <typename T, Size const LEN>
//template <typename... ARGS>
//auto
//ObjectPack<T,LEN>::
//emplace(Size const index, ARGS&&... args) -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		error_if(_occupations[index], "A value was already set to the slot at index.");
//	}
//	
//	////
//	
//	_memories.at(index).initialize(std::forward<ARGS>(args)...);
//	_occupations[index]	=	true;
//}
//template <typename T, Size const LEN>
//auto
//ObjectPack<T,LEN>::
//insert(Size const index, T const& v) -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		error_if(_occupations[index], "A value was already set to the slot at index.");
//	}
//	
//	////
//	
//	_memories.at(index).initialize(v);
//	_occupations[index]	=	true;
//}
//template <typename T, Size const LEN>
//auto
//ObjectPack<T,LEN>::
//insert(Size const index, T&& v) -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		error_if(_occupations[index], "A value was already set to the slot at index.");
//	}
//	
//	////
//	
//	_memories.at(index).initialize(std::move(v));
//	_occupations[index]	=	true;
//}
//template <typename T, Size const LEN>
//auto
//ObjectPack<T,LEN>::
//erase(Size const index) -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		error_if(not _occupations[index], "No value was set to the slot at index.");
//	}
//	
//	////
//	
//	_occupations[index]	=	false;
//	_memories.at(index).terminate();
//}
//template <typename T, Size const LEN>
//auto
//ObjectPack<T,LEN>::
//clear() -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	if (size() > 0)
//	{
//		for (Size i=0; i<LEN; i++)
//		{
//			if (_occupations[i])
//			{
//				_memories.at(i).terminate();
//			}
//		}
//		_occupations.reset();
//	}
//}
//
//
//
//
//
//
//
//
//
//
//
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
//
