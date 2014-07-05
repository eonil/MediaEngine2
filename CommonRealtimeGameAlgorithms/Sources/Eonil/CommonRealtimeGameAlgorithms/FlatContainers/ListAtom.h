////
////  ListAtom.h
////  CommonRealtimeGameAlgorithms
////
////  Created by Hoon H. on 5/3/14.
////
////
//
//#pragma once
//#include "../CommonRealtimeGameAlgorithmsCommon.h"
//#include "../GenericUtilities/Range.h"
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
//template <typename T>
//class
//ListAtom
//{
//	using	ATOM	=	ListAtom<T>;
//	
//public:
//	auto	value() const -> T const&;
//	auto	value() -> T&;
//	
//	auto	prior() const -> ATOM const*;
//	auto	prior() -> ATOM*;
//	auto	setPrior(ATOM*) -> void;
//	auto	unsetPrior() -> void;
//	
//	auto	next() const -> ATOM const*;
//	auto	next() -> ATOM*;
//	auto	setNext(ATOM*) -> void;
//	auto	unsetNext() -> void;
//	
//private:
//	T		_value	=	{};
//	ATOM*	_prior	=	nullptr;
//	ATOM*	_next	=	nullptr;
//	
//	auto	_halt_if_this_is_null() const -> void;
//	auto	_error_if_supplied_atom_is_null(ATOM*) const -> void;
//};
//
//
//template <typename T>
//class
//ListAtomIterator
//{
//	using	JUST_T	=	typename std::remove_const<T>::type;
//	using	ATOM	=	typename std::conditional<std::is_const<T>::value, ListAtom<JUST_T> const, ListAtom<JUST_T>>::type;
//	
//public:
//	ListAtomIterator() = delete;
//	ListAtomIterator(std::nullptr_t);		//	Makes end iterator.
//	ListAtomIterator(ATOM*);				//	Makes non-end iterator.
//	
//	auto	operator!=(ListAtomIterator const&) const -> bool;
//	auto	operator--() -> void;
//	auto	operator++() -> void;
//	
//private:
//	ATOM*	_atom	=	nullptr;
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
//template <typename T>
//auto
//ListAtom<T>::
//value() const -> T const&
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	_value;
//}
//template <typename T>
//auto
//ListAtom<T>::
//value() -> T&
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	_value;
//}
//template <typename T>
//auto
//ListAtom<T>::
//prior() const -> ATOM const*
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	_prior;
//}
//template <typename T>
//auto
//ListAtom<T>::
//prior() -> ATOM*
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	_prior;
//}
//template <typename T>
//auto
//ListAtom<T>::
//setPrior(ATOM* o) -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		_error_if_supplied_node_is_null(o);
//		error_if(_prior != nullptr, "Current prior atom must be null.");
//		{
//			ATOM*	a1	=	o;
//			while (a1 != nullptr)
//			{
//				error_if(a1 == this, "Current atom is discovered in chained prior elements. Setting prohibited to prevent building of circular list.");
//				a1	=	a1->prior();
//			}
//		}
//	}
//	
//	////
//	
//	_prior	=	o;
//}
//template <typename T>
//auto
//ListAtom<T>::
//unsetPrior() -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		error_if(_prior == nullptr, "Current prior atom must not be null.");
//	}
//	
//	////
//	
//	_prior	=	nullptr;
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
//auto
//ListAtom<T>::
//next() const -> ATOM const*
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	_next;
//}
//template <typename T>
//auto
//ListAtom<T>::
//next() -> ATOM*
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	_next;
//}
//template <typename T>
//auto
//ListAtom<T>::
//setNext(ATOM* o) -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		_error_if_supplied_node_is_null(o);
//		error_if(_prior != nullptr, "Current next atom must be null.");
//		{
//			ATOM*	a1	=	o;
//			while (a1 != nullptr)
//			{
//				error_if(a1 == this, "Current atom is discovered in chained next elements. Setting prohibited to prevent building of circular list.");
//				a1	=	a1->next();
//			}
//		}
//	}
//	
//	////
//	
//	_prior	=	o;
//}
//template <typename T>
//auto
//ListAtom<T>::
//unsetNext() -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		error_if(_prior == nullptr, "Current next atom must not be null.");
//	}
//	
//	////
//	
//	_prior	=	nullptr;
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
//template <typename T>
//auto
//ListAtomIterator<T>::operator!=(const ListAtomIterator<T> &o) const -> bool
//{
//	return	_atom != o._atom;
//}
//template <typename T>
//auto
//ListAtomIterator<T>::operator--() -> void
//{
//	_atom	=	_atom->prior();
//}
//template <typename T>
//auto
//ListAtomIterator<T>::operator++() -> void
//{
//	_atom	=	_atom->next();
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
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
