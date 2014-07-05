////
////  StableStableCircularQueue.h
////  TheFluxGame
////
////  Created by Hoon H. on 3/15/14.
////
////
//
//#pragma once
//
//#include "../CommonRealtimeGameAlgorithmsCommon.h"
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
///*!
// Fixed sized very efficient FIFO queue.
// Roughly follows `std::queue` interface, and crashes on any invalid operations.
// 
// @classdesign
// 
//	 +---+---+---+---+
//	 | 0 | 1 | 2 | 3 | 4 | 5 |
//	 +---+---+---+---+
// 
// If there're two elements from 2 to 3, then ordering-end-pointer will become 0.
// If you add one more element, then the element will be placed at 0, and the
// pointer will point 1. No pointer out of the memory block range will be used
// for ordering.
// 
// @discussion
// This is the default queue choice.
// 
// */
//template <typename T>
//class
//StableCircularQueue final
//{
//	T*		_mem_block_begin_addr	{};
//	T*		_mem_block_end_addr		{};		//	*End* means past-the-last.
//	
//	T*		_ordering_begin_ptr		{};
//	T*		_ordering_end_ptr		{};		//	*End* means past-the-last.
//	
//	Size	_sz						{};		//	May be optimized out, but I have no idea and time... Do it yourself if you have enough time.
//	
//	static auto	_alloc_range(Size cap) -> T*
//	{
//		return	new T[cap]();
//	}
//	static auto	_dealloc_range(T* address) -> void
//	{
//		delete[]	address;
//	}
//	
//	auto
//	ASSERT_NON_EMPTY() const -> void
//	{
//		EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(_ordering_begin_ptr != nullptr, "This queue object was not initialized properly, and cannot be used.");
//		EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(_ordering_end_ptr != nullptr, "This queue object was not initialized properly, and cannot be used.");
//	}
//	auto
//	ASSERT_NON_ZERO_SIZE() const -> void
//	{
////					EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(size() == capacity() or ((_ordering_begin_ptr+1) != _ordering_end_ptr), "Integrity check failure. The size and pointer state doesn't match.");
//		EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(size() > 0, "No item to performt the operation.");
//	}
//	auto
//	ASSERT_POINTER_RANGES() const -> void
//	{
//		EONIL_DEBUG_ASSERT(_ordering_begin_ptr >= _mem_block_begin_addr and _ordering_end_ptr < _mem_block_end_addr);
//		EONIL_DEBUG_ASSERT(_ordering_end_ptr >= _mem_block_begin_addr and _ordering_end_ptr <= _mem_block_end_addr);
//		EONIL_DEBUG_ASSERT(_ordering_begin_ptr != _ordering_end_ptr or size() == 0);
//	}
//	
//	
//	
//	
//	
//public:
//	template <bool const CONSTNESS>
//	struct
//	CovariantIterator
//	{
//		using	Q	=	typename std::conditional<CONSTNESS, StableCircularQueue const, StableCircularQueue>::type;
//		using	V	=	typename std::conditional<CONSTNESS, T const, T>::type;
//		
//		Q*		_q			{nullptr};
//		V*		_cur_ptr	{nullptr};
//		
//	public:
//		CovariantIterator() = delete;
//		CovariantIterator(Q* q, V* cptr) : _q(q), _cur_ptr(cptr)
//		{
//		}
//		
//		auto
//		operator!=(CovariantIterator const& it) const -> bool
//		{
//			EONIL_DEBUG_ASSERT(_q == it._q);
//			return	_cur_ptr != it._cur_ptr;
//		}
//		auto
//		operator++() -> void
//		{
//			_cur_ptr++;
//			if (_cur_ptr == _q->_mem_block_end_addr)
//			{
//				_cur_ptr	=	_q->_mem_block_begin_addr;
//			}
//		}
//		
//		auto
//		operator*() const -> V const&
//		{
//			return	*_cur_ptr;
//		}
//		auto
//		operator*() -> V&
//		{
//			return	*_cur_ptr;
//		}
//	};
//	
//	using	Iterator		=	CovariantIterator<false>;
//	using	ConstIterator	=	CovariantIterator<true>;
//	
//	
//public:
//	StableCircularQueue() = delete;
//	StableCircularQueue(Size const& capacity);
//	~StableCircularQueue();
//	
//	StableCircularQueue(StableCircularQueue const&) = delete;
//	StableCircularQueue(StableCircularQueue&&) = delete;
//	
//	auto	capacity() const -> Size;
//	auto	empty() const -> bool;
//	auto	size() const -> Size;
//	
//	auto	at(Size const& index) const -> T const&;
//	auto	at(Size const& index) -> T&;
//	auto	front() const -> T const&;
//	auto	front() -> T&;
//	auto	back() const -> T const&;
//	auto	back() -> T&;
//	
//	auto	begin() const -> ConstIterator;
//	auto	begin() -> Iterator;
//	auto	end() const -> ConstIterator;
//	auto	end() -> Iterator;
//	
//	auto	push(T const& v) -> void;
//	auto	push(T&& v) -> void;
//	auto	pop() -> void;
//};
//
//
//
//
//
//
//
//template <typename T> StableCircularQueue<T>::
//StableCircularQueue(Size const& capacity)
//: _mem_block_begin_addr(_alloc_range(capacity))
//, _mem_block_end_addr(_mem_block_begin_addr + capacity)
//, _ordering_begin_ptr(_mem_block_begin_addr)
//, _ordering_end_ptr(_mem_block_begin_addr)
//, _sz(0)
//{
//}
//template <typename T> StableCircularQueue<T>::
//~StableCircularQueue()
//{
//	ASSERT_NON_EMPTY();
//	_dealloc_range(_mem_block_begin_addr);
//}
//
//template <typename T> auto StableCircularQueue<T>::
//capacity() const -> Size
//{
//	return	_mem_block_end_addr - _mem_block_begin_addr;
//}
//template <typename T> auto StableCircularQueue<T>::
//empty() const -> bool
//{
//	return	size() == 0;
//}
//template <typename T> auto StableCircularQueue<T>::
//size() const -> Size
//{
//	return	_sz;
//	
////				/*
////				 This algorithm is wrong.
////				 */
////				if (_ordering_begin_ptr <= _ordering_end_ptr)
////				{
////					return	_ordering_end_ptr - _ordering_begin_ptr;
////				}
////				else
////				{
////					return	capacity() - ((_ordering_begin_ptr+1) - (_ordering_end_ptr-1));
////				}
//}
//
//
//template <typename T> auto StableCircularQueue<T>::
//at(Size const&index) const -> T const&
//{
//	return	((StableCircularQueue*)this)->at(index);
//}
//template <typename T> auto StableCircularQueue<T>::
//at(Size const&index) -> T&
//{
//	ASSERT_NON_EMPTY();
//	ASSERT_NON_ZERO_SIZE();
//	EONIL_DEBUG_ASSERT(index < _sz);
//	
//	if (_ordering_begin_ptr < _ordering_end_ptr)
//	{
//		return	*(_ordering_begin_ptr + index);
//	}
//	else
//	{
//		size_t	count_of_former_half	=	_mem_block_end_addr - _ordering_begin_ptr;
//		bool	is_in_former_half		=	index < count_of_former_half;
//		T*		ptr1					=	is_in_former_half ? (_ordering_begin_ptr+index) : (_mem_block_begin_addr + (index - count_of_former_half));
//		return	*ptr1;
//	}
//}
//template <typename T> auto StableCircularQueue<T>::
//front() const -> T const&
//{
//	ASSERT_NON_EMPTY();
//	ASSERT_NON_ZERO_SIZE();
//	return	at(0);
//}
//template <typename T> auto StableCircularQueue<T>::
//front() -> T&
//{
//	ASSERT_NON_EMPTY();
//	ASSERT_NON_ZERO_SIZE();
//	return	at(0);
//}
//template <typename T> auto StableCircularQueue<T>::
//back() const -> T const&
//{
//	ASSERT_NON_EMPTY();
//	ASSERT_NON_ZERO_SIZE();
//	return	at(size()-1);
//}
//template <typename T> auto StableCircularQueue<T>::
//back() -> T&
//{
//	ASSERT_NON_EMPTY();
//	ASSERT_NON_ZERO_SIZE();
//	return	at(size()-1);
//}
//
//
//
//
//
//
//
//
//template <typename T> auto StableCircularQueue<T>::
//begin() const -> ConstIterator
//{
//	return	{this, _ordering_begin_ptr};
//}
//template <typename T> auto StableCircularQueue<T>::
//begin() -> Iterator
//{
//	return	{this, _ordering_begin_ptr};
//}
//template <typename T> auto StableCircularQueue<T>::
//end() const -> ConstIterator
//{
//	return	{this, _ordering_end_ptr};
//}
//template <typename T> auto StableCircularQueue<T>::
//end() -> Iterator
//{
//	return	{this, _ordering_end_ptr};
//}
//
//
//
//
//
//
//template <typename T> auto StableCircularQueue<T>::
//push(T &&v) -> void
//{
//	ASSERT_NON_EMPTY();
//	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(size() != capacity(), "No more free slot. Out of capacity.");
//	EONIL_DEBUG_ASSERT(_ordering_end_ptr >= _mem_block_begin_addr and _ordering_end_ptr <= _mem_block_end_addr);
//	
//	new (_ordering_end_ptr) T(std::move(v));
//	
//	T*	candidate_ptr	=	_ordering_end_ptr + 1;
//	_ordering_end_ptr	=	(candidate_ptr == _mem_block_end_addr) ?  _mem_block_begin_addr : candidate_ptr;
//	
//	_sz++;
//	
//	EONIL_DEBUG_ASSERT(_ordering_end_ptr >= _mem_block_begin_addr and _ordering_end_ptr <= _mem_block_end_addr);
//}
//template <typename T> auto StableCircularQueue<T>::
//push(const T &v) -> void
//{
//	ASSERT_NON_EMPTY();
//	T	v2	=	v;
//	push(std::move(v2));
//}
//
//template <typename T> auto StableCircularQueue<T>::
//pop() -> void
//{
//	ASSERT_NON_EMPTY();
//	ASSERT_NON_ZERO_SIZE();
//	EONIL_DEBUG_ASSERT(_ordering_end_ptr >= _mem_block_begin_addr and _ordering_end_ptr <= _mem_block_end_addr);
//
//	_ordering_begin_ptr->~T();
//	
//	T*	candidate_ptr	=	_ordering_begin_ptr + 1;
//	_ordering_begin_ptr	=	(candidate_ptr == _mem_block_end_addr) ?  _mem_block_begin_addr : candidate_ptr;
//
//	_sz--;
//	
//	EONIL_DEBUG_ASSERT(_ordering_end_ptr >= _mem_block_begin_addr and _ordering_end_ptr <= _mem_block_end_addr);
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
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
