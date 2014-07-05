////
////  StableDenseStack.h
////  TheFluxGame
////
////  Created by Hoon H. on 3/12/14.
////
////
//
//#pragma once
//
//#include "../CommonRealtimeGameAlgorithmsCommon.h"
//#include "ListAtomSlot.h"
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
///*!
// A queue with no re-allocation, and all the operations are O(1),
// but capacity is fixed at when it is being created.
// 
// @classdesign
// The internal storage starts with uninitialize memory block, and will be 
// initialized when you push, and deinitialized when you pop.
// */
//template <typename T>
//class
//StableDenseStack
//{
//	T*		_data	{nullptr};
//	Size	_cap	{0};
//	Size	_used	{0};
//	
//	inline auto
//	ASSERT_PROPER_INSTANCE() const -> void
//	{
//		EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(_data != nullptr, "This instance of `StableDenseStack` was not initialized properly, so you cannot perform any operation on this instance.");
//	}
//	
//public:
//	StableDenseStack() = default;				//!	Creates an invalid state instance. Accessing any method will cause an exception.
//	StableDenseStack(StableDenseStack&&);
//	StableDenseStack(StableDenseStack const&);
//	~StableDenseStack();
//	
//	StableDenseStack(Size const& capacity);
//	
//	auto	operator=(StableDenseStack const& o) -> StableDenseStack&;
//	auto	operator=(StableDenseStack&& o) -> StableDenseStack&;
//	
//	auto	empty() const -> bool;
//	auto	capacity() const -> Size;
//	auto	size() const -> Size;
//	
//	auto	data() const -> T const*;
//	auto	data() -> T*;
//	
//	auto	at(Size const& index) const -> T const&;
//	auto	at(Size const& index) -> T&;
//	
//	auto	front() const -> T const&;
//	auto	front() -> T&;
//	auto	back() const -> T const&;
//	auto	back() -> T&;
//	
//	auto	begin() const -> T const*;
//	auto	end() const -> T const*;
//	
//	auto	clear() -> void;					//!	Resets all internal state to initial state by popping all elements. Use this instead of re-creating object to avoid reallocation.
//	auto	push(T const& v) -> void;
//	auto	push(T&& v) -> void;
//	auto	pop() -> void;
//	
//	template <typename... ARGS>
//	auto	emplace (ARGS&&... args) -> void;
//};
//
//
//template <typename T>
//StableDenseStack<T>::
//StableDenseStack(StableDenseStack const& o) : _data((T*)(::operator new(sizeof(T) * o._cap))), _cap(o._cap), _used(o._used)
//{
//	for (Size i=0; i<_used; i++)
//	{
//		_data[i]	=	o._data[i];		//	Copy-assignment of T.
//	}
//}
//template <typename T>
//StableDenseStack<T>::
//StableDenseStack(StableDenseStack&& o) : _data(std::move(o._data)), _cap(std::move(o._cap)), _used(std::move(o._used))
//{
//	//	Empty old state for dtor.
//	o._data	=	nullptr;
//	o._cap	=	0;
//	o._used	=	0;
//}
//template <typename T>
//StableDenseStack<T>::
//StableDenseStack(Size const& capacity) : _data((T*)(::operator new(sizeof(T) * capacity))), _cap(capacity), _used(0)
//{
//}
//template <typename T>
//StableDenseStack<T>::
//~StableDenseStack()
//{
//	if (_data != nullptr)
//	{
//		clear();
//		
//		::operator delete ((void*)_data);
//		_data	=	nullptr;
//	}
//}
//
//template <typename T> auto
//StableDenseStack<T>::
//operator=(const StableDenseStack<T> &o) -> StableDenseStack&
//{
//	StableDenseStack	copy{o};
//	std::swap(copy._data, _data);
//	std::swap(copy._cap, _cap);
//	std::swap(copy._used, _used);
//	return	*this;
//}
//template <typename T> auto
//StableDenseStack<T>::
//operator=(StableDenseStack<T> &&o) -> StableDenseStack&
//{
//	_data	=	std::move(o._data);
//	_cap	=	std::move(o._cap);
//	_used	=	std::move(o._used);
//	
//	o._data	=	nullptr;
//	o._cap	=	0;
//	o._used	=	0;
//	
////				std::swap(o._data, _data);
////				std::swap(o._cap, _cap);
////				std::swap(o._used, _used);
//	return	*this;
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
//template <typename T>
//auto StableDenseStack<T>::
//empty() const -> bool
//{
//	ASSERT_PROPER_INSTANCE();
//	return	_used == 0;
//}
//
//template <typename T>
//auto StableDenseStack<T>::
//capacity() const -> Size
//{
//	ASSERT_PROPER_INSTANCE();
//	return	_cap;
//}
//
//template <typename T>
//auto StableDenseStack<T>::
//size() const -> Size
//{
//	ASSERT_PROPER_INSTANCE();
//	return	_used;
//}
//
//
//template <typename T>
//auto StableDenseStack<T>::
//data() const -> T const*
//{
//	ASSERT_PROPER_INSTANCE();
//	return	_data;
//}
//template <typename T>
//auto StableDenseStack<T>::
//data() -> T*
//{
//	ASSERT_PROPER_INSTANCE();
//	return	_data;
//}
//
//template <typename T>
//auto StableDenseStack<T>::
//at(Size const& index) const -> T const&
//{
//	ASSERT_PROPER_INSTANCE();
//	return	_data[index];
//}
//template <typename T>
//auto StableDenseStack<T>::
//at(Size const& index) -> T&
//{
//	ASSERT_PROPER_INSTANCE();
//	return	_data[index];
//}
//
//template <typename T>
//auto StableDenseStack<T>::
//front() const -> T const&
//{
//	ASSERT_PROPER_INSTANCE();
//	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(_used > 0, "This stack is empty, and there's no front element.");
//	return	at(0);
//}
//template <typename T>
//auto StableDenseStack<T>::
//front() -> T&
//{
//	ASSERT_PROPER_INSTANCE();
//	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(_used > 0, "This stack is empty, and there's no front element.");
//	return	at(0);
//}
//template <typename T>
//auto StableDenseStack<T>::
//back() const -> T const&
//{
//	ASSERT_PROPER_INSTANCE();
//	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(_used > 0, "This stack is empty, and there's no back element.");
//	return	at(size()-1);
//}
//template <typename T>
//auto StableDenseStack<T>::
//back() -> T&
//{
//	ASSERT_PROPER_INSTANCE();
//	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(_used > 0, "This stack is empty, and there's no back element.");
//	return	at(size()-1);
//}
//template <typename T>
//auto StableDenseStack<T>::
//begin() const -> T const*
//{
//	return	data();
//}
//template <typename T>
//auto StableDenseStack<T>::
//end() const -> T const*
//{
//	return	data() + size();
//}
//
//
//
//
//
//
//template <typename T>
//auto StableDenseStack<T>::
//clear() -> void
//{
//	ASSERT_PROPER_INSTANCE();
//	
//	if (not std::is_trivially_destructible<T>::value)
//	{
//		//!	Type `T` destructor doesn't need to be called. Just do nothing.
//		//!	@ref http://www.cplusplus.com/reference/type_traits/is_trivially_destructible/
//	}
//	else
//	{
//		//	Deinitialize all existing instances.
//		for (Size i=0; i < _used; i++)
//		{
//			_data[i].~T();
//		}
//		
////					/*
////					 A NOTE FOR FUTURE MAINTAINER
////					 ----------------------------
////					 This goes mostly infinite loop if the `_data` pointer is `nullptr`.
////					 Do not use this.
////					 */
////					for (T* ptr=_data; _data < _data+_used; _data++)
////					{
////						ptr->~T();
////					}
//	}
//	_used	=	0;
//
//}
//template <typename T>
//template <typename ...ARGS>
//auto StableDenseStack<T>::
//emplace(ARGS&&... args) -> void
//{
//	ASSERT_PROPER_INSTANCE();
//	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(_used < _cap, "This stack is full. Cannot insert any.");
//	new (_data+_used) T(std::forward<ARGS>(args)...);
//	_used++;
//}
//template <typename T>
//auto StableDenseStack<T>::
//push(const T &v) -> void
//{
//	ASSERT_PROPER_INSTANCE();
//	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(_used < _cap, "This stack is full. Cannot insert any.");
//	new (_data+_used) T(v);
//	_used++;
//}
//template <typename T>
//auto StableDenseStack<T>::
//push(T &&v) -> void
//{
//	ASSERT_PROPER_INSTANCE();
//	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(_used < _cap, "This stack is full. Cannot insert any.");
//	new (_data+_used) T(std::move(v));
//	_used++;
//}
//template <typename T>
//auto StableDenseStack<T>::
//pop() -> void
//{
//	ASSERT_PROPER_INSTANCE();
//	EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(_used > 0, "This stack is empty. Cannot erase any.");
//	_used--;
//	_data[_used].~T();
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
