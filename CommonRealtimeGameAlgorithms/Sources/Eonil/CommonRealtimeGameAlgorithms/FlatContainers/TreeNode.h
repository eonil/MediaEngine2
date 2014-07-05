////
////  TreeNode.h
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
//
//
//
//template <typename T>
//class
//TreeNode
//{
//	using	NODE	=	TreeNode<T>;
//	
//public:
//	auto	value() const -> T const&;
//	auto	value() -> T&;
//	
//	auto	prior() const -> NODE const*;
//	auto	prior() -> NODE*;
//	auto	setPrior(NODE*) -> void;
//	auto	unsetPrior() -> void;
//	
//	auto	next() const -> NODE const*;
//	auto	next() -> NODE*;
//	auto	setNext(NODE*) -> void;
//	auto	unsetNext() -> void;
//	
//	auto	parent() const -> NODE const*;
//	auto	parent() -> NODE*;
//	auto	setParent(NODE*) -> void;
//	auto	unsetParent() -> void;
//	
//	auto	child() const -> NODE const*;
//	auto	child() -> NODE*;
//	auto	setChild(NODE*) -> void;
//	auto	unsetChild() -> void;
//	
//private:
//	T		_value	=	{};
//	NODE*	_prior	=	nullptr;
//	NODE*	_next	=	nullptr;
//	
//	NODE*	_parent	=	nullptr;
//	NODE*	_child	=	nullptr;
//	
//	auto	_halt_if_this_is_null() const -> void;
//	auto	_error_if_supplied_node_is_null(NODE*) const -> void;
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
//template <typename T>
//auto
//TreeNode<T>::
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
//TreeNode<T>::
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
//
//
//
//
//
//template <typename T>
//auto
//TreeNode<T>::
//prior() const -> NODE const*
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
//TreeNode<T>::
//prior() -> NODE*
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
//TreeNode<T>::
//setPrior(NODE* o) -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		_error_if_supplied_node_is_null(o);
//		error_if(_prior != nullptr, "Current prior atom must be null.");
//		if (_prior->_parent != nullptr)
//		{
//			error_if(_parent != nullptr, "If the prior has parent, this node must have no parent.");
//		}
//		{
//			NODE*	a1	=	o;
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
//	_parent	=	_prior->_parent;
//}
//template <typename T>
//auto
//TreeNode<T>::
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
//TreeNode<T>::
//next() const -> NODE const*
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
//TreeNode<T>::
//next() -> NODE*
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
//TreeNode<T>::
//setNext(NODE* o) -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		_error_if_supplied_node_is_null(o);
//		error_if(_prior != nullptr, "Current next node must be null.");
//		{
//			NODE*	a1	=	o;
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
//TreeNode<T>::
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
//template <typename T>
//auto
//TreeNode<T>::
//parent() const -> NODE const*
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	_parent;
//}
//template <typename T>
//auto
//TreeNode<T>::
//parent() -> NODE*
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	_parent;
//}
//template <typename T>
//auto
//TreeNode<T>::
//setParent(NODE* o) -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		_error_if_supplied_node_is_null(o);
//		error_if(_prior == nullptr and o->_child != nullptr, "If this is the first node, supplied node should have no first child.");
//	}
//	
//	////
//	
//	_parent	=	o;
//	if (_prior == nullptr)
//	{
//		_parent->_child	=	this;
//	}
//}
//template <typename T>
//auto
//TreeNode<T>::
//unsetParent() -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		error_if(_prior == nullptr and _parent->_child != this, "If this is the first node, supplied node's first child must be this node.");
//	}
//	
//	////
//	
//	if (_parent->_prior == nullptr)
//	{
//		_parent->_child	=	nullptr;
//	}
//	_parent	=	nullptr;
//}
//
//
//
//
//
//template <typename T>
//auto
//TreeNode<T>::
//child() const -> NODE const*
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	_parent;
//}
//template <typename T>
//auto
//TreeNode<T>::
//parent() -> NODE*
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//	}
//	
//	////
//	
//	return	_parent;
//}
//template <typename T>
//auto
//TreeNode<T>::
//setParent(NODE* o) -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		_error_if_supplied_node_is_null(o);
//		error_if(_prior == nullptr and o->_child != nullptr, "If this is the first node, supplied node should have no first child.");
//	}
//	
//	////
//	
//	_parent	=	o;
//	if (_prior == nullptr)
//	{
//		_parent->_child	=	this;
//	}
//}
//template <typename T>
//auto
//TreeNode<T>::
//unsetParent() -> void
//{
//	if (USE_EXCEPTION_CHECKINGS)
//	{
//		_halt_if_this_is_null();
//		error_if(_prior == nullptr and _parent->_child != this, "If this is the first node, supplied node's first child must be this node.");
//	}
//	
//	////
//	
//	if (_parent->_prior == nullptr)
//	{
//		_parent->_child	=	nullptr;
//	}
//	_parent	=	nullptr;
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
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
