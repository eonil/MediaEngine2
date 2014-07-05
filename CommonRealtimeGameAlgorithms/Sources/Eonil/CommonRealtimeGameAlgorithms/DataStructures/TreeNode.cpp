//
//  TreeNode.cpp
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 5/3/14.
//
//

#include "TreeNode.h"
EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DATA_STRUCTURES_TOOLS_BEGIN



















//template <bool const CONSTNESS>
//TreeNodeIterator<CONSTNESS>::TreeNodeIterator(std::nullptr_t) : _ptr(nullptr)
//{
//}
template <bool const CONSTNESS>
TreeNodeIterator<CONSTNESS>::TreeNodeIterator(TYPE* ptr) : _ptr(ptr)
{
//	/*
//	 Halt because state is already corrupted by bad parameter.
//	 */
//	
//	halt_if(ptr == nullptr);
}
template <bool const CONSTNESS>
auto
TreeNodeIterator<CONSTNESS>::operator!=(const TreeNodeIterator<CONSTNESS> &o) const -> bool
{
	return	_ptr != o._ptr;
}
template <bool const CONSTNESS>
auto
TreeNodeIterator<CONSTNESS>::operator*() const -> TYPE&
{
	return	*_ptr;
}
template <bool const CONSTNESS>
auto
TreeNodeIterator<CONSTNESS>::operator++() -> void
{
	_ptr	=	_ptr->next();
}



















template <bool const CONSTNESS>
TreeNodeRange<CONSTNESS>::TreeNodeRange(NODE* first, NODE* last) : _first(first), _last(last)
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		if (USE_HEAVY_EXCEPTION_CHECKINGS)
		{
			/*
			 Halted because state is already corrupted.
			 */
			
			_halt_if_state_is_inconsistent();
		}
	}
}
template <bool const CONSTNESS>
TreeNodeRange<CONSTNESS>::operator TreeNodeRange<true>() const
{
	return	{_first, _last};
}
template <bool const CONSTNESS>
auto
TreeNodeRange<CONSTNESS>::empty() const -> bool
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		if (USE_HEAVY_EXCEPTION_CHECKINGS)
		{
			_halt_if_state_is_inconsistent();
		}
	}
	
	////
	
	return	_first == nullptr and _last == nullptr;
}
template <bool const CONSTNESS>
auto
TreeNodeRange<CONSTNESS>::front() const -> NODE&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		halt_if(empty());
	}
	
	////
	
	return	*_first;
}
template <bool const CONSTNESS>
auto
TreeNodeRange<CONSTNESS>::back() const -> NODE&
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		halt_if(empty());
	}
	
	////
	
	return	*_last;
}
template <bool const CONSTNESS>
auto
TreeNodeRange<CONSTNESS>::begin() const -> TreeNodeIterator<CONSTNESS>
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		if (USE_HEAVY_EXCEPTION_CHECKINGS)
		{
			_halt_if_state_is_inconsistent();
		}
	}
	
	////
	
	return	TreeNodeIterator<CONSTNESS>{_first};
}
template <bool const CONSTNESS>
auto
TreeNodeRange<CONSTNESS>::end() const -> TreeNodeIterator<CONSTNESS>
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		if (USE_HEAVY_EXCEPTION_CHECKINGS)
		{
			_halt_if_state_is_inconsistent();
		}
	}
	
	////
	
	return	nullptr;
}

template <bool const CONSTNESS>
auto
TreeNodeRange<CONSTNESS>::_halt_if_state_is_inconsistent() const -> void
{
	halt_if((_first == nullptr and _last != nullptr) or (_first != nullptr and _last == nullptr), "Inconsistent node range state. One of first or last pointer is null. (not both)");
	halt_if(_first != nullptr and _first->_last() != _last, "Inconsistent node range state. Cannot navigate to last from first.");
	halt_if(_last != nullptr and _last->_first() != _first, "Inconsistent node range state. Cannot navigate to first from last.");
}

















auto
TreeNode::prior() const -> TreeNode const*
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
	}
	
	////
	
	return	_prior;
}
auto
TreeNode::prior() -> TreeNode*
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
	}
	
	////
	
	return	_prior;
}
auto
TreeNode::setPrior(TreeNode *o) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(_prior != nullptr, "Current node already have prior node.");
		_error_if_supplied_node_is_null(o);
		_error_if_supplied_node_would_make_circular_linkage(o);
		error_if(o->_next != nullptr, "Supplied node should have no next node.");
		error_if(o->_parent != nullptr, "Supplied node should have no parent node.");
	}
	
	////
	
	o->_parent	=	_parent;
	o->_next	=	this;
	_prior		=	o;
	
	if (_parent != nullptr and _parent->_fchild == this)
	{
		_parent->_fchild	=	_prior;
	}
}
auto
TreeNode::unsetPrior() -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(_prior == nullptr, "Current node doesn't have prior node.");
		error_if(_prior->_next != this, "Current prior node's next node should be set to this node.");
		error_if(_prior->_parent != _parent, "Current prior node should have same parent node with parent node of this node.");
	}
	
	////
	
	if (_parent != nullptr and _parent->_fchild == _prior)
	{
		_parent->_fchild	=	nullptr;
	}
	
	_prior->_next	=	nullptr;
	_prior			=	nullptr;
}

auto
TreeNode::next() const -> TreeNode const*
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
	}
	
	////
	
	return	_next;
}
auto
TreeNode::next() -> TreeNode*
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
	}
	
	////
	
	return	_next;
}
auto
TreeNode::setNext(TreeNode *o) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(_next != nullptr, "Current node already have next node.");
		_error_if_supplied_node_is_null(o);
		error_if(o->_prior != nullptr, "Supplied node should have no prior node.");
		error_if(o->_parent != nullptr, "Supplied node should have no parent node.");
		_error_if_supplied_node_would_make_circular_linkage(o);
	}
	
	////
	
	_next		=	o;
	o->_prior	=	this;
	o->_parent	=	_parent;
	
	if (_parent != nullptr and _parent->_lchild == this)
	{
		_parent->_lchild	=	_next;
	}
}
auto
TreeNode::unsetNext() -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(_next == nullptr, "Current node doesn't have next node.");
		error_if(_next->_prior != this, "Current next node's should be set to this node.");
		error_if(_next->_parent != _parent, "Current next node's parent node must be same with parent of this node.");
	}
	
	////
	
	if (_parent != nullptr and _parent->_lchild == _next)
	{
		_parent->_lchild	=	this;
	}
	
	_next->_parent	=	nullptr;
	_next->_prior	=	nullptr;
	_next			=	nullptr;
}

auto
TreeNode::parent() const -> TreeNode const*
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
	}
	
	////
	
	return	_parent;
}
auto
TreeNode::parent() -> TreeNode*
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
	}
	
	////
	
	return	_parent;
}
auto
TreeNode::setParent(TreeNode *o) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(_parent != nullptr, "Current node already have parent node.");
		_error_if_supplied_node_is_null(o);
		_error_if_supplied_node_would_make_circular_linkage(o);
		error_if(_prior != nullptr, "Only single child node can set its parent directly. Current node already has a prior node.");
		error_if(_next != nullptr, "Only single child node can set its parent directly. Current node already has a next node.");
		error_if(o->_fchild != nullptr, "`setParent` is allowed only if the parent has no child.");
		error_if(o->_lchild != nullptr, "`setParent` is allowed only if the parent has no child.");
	}
	
	////

	o->_fchild	=	this;
	o->_lchild	=	this;
	_parent		=	o;
}
auto
TreeNode::unsetParent() -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		error_if(_parent == nullptr, "Current node doesn't have parent node.");
		error_if(_prior != nullptr, "Only single child node can set its parent directly. Current node already has a prior node.");
		error_if(_next != nullptr, "Only single child node can set its parent directly. Current node already has a next node.");
	}
	
	////
	
	_parent->_fchild	=	nullptr;
	_parent->_lchild	=	nullptr;
	_parent				=	nullptr;
}

auto
TreeNode::children() const -> TreeNodeRange<true>
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_children_linking_is_not_consistent();
	}
	
	////
	
	return	{_fchild, _lchild};
}
auto
TreeNode::children() -> TreeNodeRange<false>
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_children_linking_is_not_consistent();
	}
	
	////
	
	return	{_fchild, _lchild};
}
auto
TreeNode::setChildren(TreeNodeRange<false> o) -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_children_linking_is_not_consistent();
		_error_if_supplied_children_linking_is_not_consistent(o);
		error_if(_fchild != nullptr or _lchild != nullptr, "Both of first/last children must be null.");
		if (USE_HEAVY_EXCEPTION_CHECKINGS)
		{
			for (NODE& subnode: o)
			{
				error_if(subnode._parent != nullptr, "One or more child node alredy have parent node.");
			}
		}
	}
	
	////
	
	_fchild	=	o._first;
	_lchild	=	o._last;
	for (NODE& subnode: o)
	{
		subnode._parent	=	this;
	}
}
auto
TreeNode::unsetChildren() -> void
{
	if (USE_EXCEPTION_CHECKINGS)
	{
		_halt_if_this_is_null();
		_halt_if_children_linking_is_not_consistent();
		error_if(_fchild == nullptr or _lchild == nullptr, "Both of first/last children must not be null.");
		if (USE_HEAVY_EXCEPTION_CHECKINGS)
		{
			for (NODE const& subnode: TreeNodeRange<true>{_fchild, _lchild})
			{
				error_if(subnode._parent != this, "All child node's parent node must be this node.");
			}
		}
	}
	
	////
	
	_fchild	=	nullptr;
	_lchild	=	nullptr;
	for (NODE& subnode: TreeNodeRange<false>{_fchild, _lchild})
	{
		subnode._parent	=	nullptr;
	}
}





















auto
TreeNode::_contains(const NODE *o) const -> bool
{
	if (this == o)
	{
		return	true;
	}
	for (NODE const& subnode: children())
	{
		if (subnode._contains(o))
		{
			return	true;
		}
	}
	return	false;
}
auto
TreeNode::_first() const -> TreeNode const*
{
	return	_prior == nullptr ? this : _prior->_first();
}
auto
TreeNode::_last() const -> TreeNode const*
{
	return	_next == nullptr ? this : _next->_last();
}




auto
TreeNode::_halt_if_this_is_null() const -> void
{
	halt_if(this == nullptr, "This object pointer is null.");
}
auto
TreeNode::_halt_if_children_linking_is_not_consistent() const -> void
{
	halt_if((_fchild == nullptr and _lchild != nullptr) or (_fchild != nullptr and _lchild == nullptr), "Inconsistent children linking state. One of first or last child pointer is null. (not both)");
	if (USE_HEAVY_EXCEPTION_CHECKINGS)
	{
		halt_if(_fchild != nullptr and _fchild->_last() != _lchild, "Inconsistent children linking state. First child cannot navigate to last child.");
		halt_if(_lchild != nullptr and _lchild->_first() != _fchild, "Inconsistent children linking state. Last child cannot navigate to first child.");
	}
}

auto
TreeNode::_error_if_supplied_children_linking_is_not_consistent(TreeNodeRange<true> o) const -> void
{
	error_if((o._first == nullptr and o._last != nullptr) or (o._first != nullptr and o._last == nullptr), "Inconsistent children linking state. One of first or last child pointer is null. (not both)");
	if (USE_HEAVY_EXCEPTION_CHECKINGS)
	{
		error_if(o._first->_last() != o._last, "Inconsistent children linking state. First child cannot navigate to last child.");
		error_if(o._last->_first() != o._first, "Inconsistent children linking state. Last child cannot navigate to first child.");
	}
}
auto
TreeNode::_error_if_supplied_node_is_null(const NODE *o) const -> void
{
	error_if(o == nullptr, "Supplied node is null.");
}
auto
TreeNode::_error_if_supplied_node_would_make_circular_linkage(NODE const*o) const -> void
{
	if (USE_CIRCULAR_LINKING_CHECKINGS)
	{
		auto
		checkup	=	[&](std::function<auto(NODE const*)->NODE const*> advance)
		{
			NODE const*	a1	=	o;
			while (a1 != nullptr)
			{
				error_if(a1 == this, "Circular linking is not supported.");
				a1	=	advance(a1);
			}
		};
		
		////
		
		checkup([](NODE const* n1){ return n1->prior(); });
		checkup([](NODE const* n1){ return n1->next(); });
		checkup([](NODE const* n1){ return n1->parent(); });
		for (NODE const& subnode: children())
		{
			error_if(subnode._contains(o), "Circular linking is not supported.");
		}
	}
}













template	class	TreeNodeIterator<true>;
template	class	TreeNodeIterator<false>;

template	class	TreeNodeRange<true>;
template	class	TreeNodeRange<false>;










EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DATA_STRUCTURES_TOOLS_END
