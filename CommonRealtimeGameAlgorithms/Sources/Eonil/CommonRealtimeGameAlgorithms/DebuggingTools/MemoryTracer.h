//
//  MemoryTracer.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/29.
//
//

#pragma once

#include "../CommonRealtimeGameAlgorithmsCommon.h"

EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUGGING_TOOLS_BEGIN



template <typename T>
class
MemoryTracer
{
	std::set<T const*>	_live_ptr_list	{};
	
public:
	auto	is_ptr_live_object(T const* ptr) const -> bool;
	auto	mark_ptr_as_live_object(T const* ptr) -> void;
	auto	unmark_ptr_as_live_object(T const* ptr) -> void;
	
public:
	static auto		theTracer() -> MemoryTracer&;
};



template <typename T> auto
MemoryTracer<T>::
is_ptr_live_object(const T *ptr) const -> bool
{
	return	_live_ptr_list.find(ptr) != _live_ptr_list.end();
}
template <typename T> auto
MemoryTracer<T>::
mark_ptr_as_live_object(const T *ptr) -> void
{
	_live_ptr_list.insert(ptr);
}
template <typename T> auto
MemoryTracer<T>::
unmark_ptr_as_live_object(const T *ptr) -> void
{
	_live_ptr_list.erase(ptr);
}

template <typename T> auto
MemoryTracer<T>::
theTracer() -> MemoryTracer&
{
	static MemoryTracer*	_tt		=	nullptr;
	if (_tt == nullptr)
	{
		_tt	=	new MemoryTracer();
	}
	return	*_tt;
}




EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUGGING_TOOLS_END

