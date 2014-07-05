//
//  GenericTreeNode.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 5/3/14.
//
//

#pragma once
#include "../CommonRealtimeGameAlgorithmsCommon.h"
#include "TreeNode.h"
EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DATA_STRUCTURES_TOOLS_BEGIN








template <typename T>	class	GenericTreeNode;
template <typename T>	class	GenericTreeNodeIterator;
template <typename T>	class	GenericTreeNodeRange;








template <typename T>
class
GenericTreeNodeIterator : private TreeNodeIterator<std::is_const<T>::value>
{
	static bool const CONSTNESS	=	std::is_const<T>::value;

	using	BASE	=	TreeNodeIterator<CONSTNESS>;
	using	NODE	=	T;

public:
	/*!
	 The parameter can be null to mark end iterator.
	 */
	GenericTreeNodeIterator(NODE* o) : BASE(o)
	{
	}
	
	auto
	operator!=(GenericTreeNodeIterator const&o) const -> bool
	{
		return	BASE::operator!=(o);
	}
	auto
	operator*() const -> NODE&
	{
		return	static_cast<NODE&>(BASE::operator*());
	}
	auto
	operator++() -> void
	{
		BASE::operator++();
	}
};



template <typename T>
class
GenericTreeNodeRange : private TreeNodeRange<std::is_const<T>::value>
{
	friend class	GenericTreeNode<T const>;
	friend class	GenericTreeNode<T>;
	
	static bool const CONSTNESS	=	std::is_const<T>::value;
	
	using	BASE	=	TreeNodeRange<CONSTNESS>;
	using	NODE	=	T;
//	using	NODE	=	typename std::conditional<std::is_const<T>::value, T const, T>::type;
	using	ITER	=	typename std::conditional<std::is_const<T>::value, GenericTreeNodeIterator<T const>, GenericTreeNodeIterator<T>>::type;
	
public:
	GenericTreeNodeRange() = default;								//!	Creates empty (zero-node) range (list).
	
	operator GenericTreeNodeRange<T const>() const
	{
		return	{&BASE::front(), &BASE::back()};
	}
	
	////
	
	/*!
	 Creates non-empty (one or more nodes) range. Both parameters cannot be null.
	 */
	GenericTreeNodeRange(NODE* first, NODE* last) : BASE(first, last)
	{
	}
	
	auto
	empty() const -> bool
	{
		return	BASE::empty();
	}
	
	auto
	front() const -> NODE const&
	{
		return	static_cast<NODE&>(BASE::front());
	}
	auto
	front() -> NODE&
	{
		return	static_cast<NODE&>(BASE::front());
	}
	auto
	back() const -> NODE const&
	{
		return	static_cast<NODE&>(BASE::back());
	}
	auto
	back() -> NODE&
	{
		return	static_cast<NODE&>(BASE::back());
	}
	
	auto
	begin() const -> ITER
	{
		return	ITER(&static_cast<NODE&>(*BASE::begin()));
	}
	auto
	end() const -> ITER
	{
		return	ITER(&static_cast<NODE&>(*BASE::end()));
//		return	ITER(&*BASE::end());
//		return	ITER(nullptr);
	}
};
















/*!
 A tree-node which is providing strong typing via CRTP technique.
 
 @discussion
 Designed to be used in CRTP manner. Subclass this class and pass the final type to `T`.
 The reason of using CRTP is providing maximum flexibility. You can add any members
 as much as you want with full type checking support. Unlike flat containers, structural
 containers usually need to handle thier own types very much, and CRTP is the only solution
 for proper type support.
 */
template <typename T>
class
GenericTreeNode : private TreeNode
{
	friend class	GenericTreeNodeIterator<T const>;
	friend class	GenericTreeNodeIterator<T>;
	friend class	GenericTreeNodeRange<T const>;
	friend class	GenericTreeNodeRange<T>;
	
	using			NODE	=	T;
	
public:
	~GenericTreeNode() noexcept
	{
		static_assert(std::is_base_of<GenericTreeNode<T>, T>::value, "The type `T` must be a subclass of `GenericTreeNode<T>`.");
	}
	
	auto
	prior() const -> NODE const*
	{
		return	static_cast<NODE const*>(TreeNode::prior());
	}
	auto
	prior() -> NODE*
	{
		return	static_cast<NODE*>(TreeNode::prior());
	}
	auto
	setPrior(NODE* o) -> void
	{
		TreeNode::setPrior(o);
	}
	auto
	unsetPrior() -> void
	{
		TreeNode::unsetParent();
	}
	
	auto
	next() const -> NODE const*
	{
		return	static_cast<NODE const*>(TreeNode::next());
	}
	auto
	next() -> NODE*
	{
		return	static_cast<NODE*>(TreeNode::next());
	}
	auto
	setNext(NODE* o) -> void
	{
		TreeNode::setNext(o);
	}
	auto
	unsetNext() -> void
	{
		TreeNode::unsetNext();
	}
	
	auto
	parent() const -> NODE const*
	{
		return	static_cast<NODE const*>(TreeNode::parent());
	}
	auto
	parent() -> NODE*
	{
		return	static_cast<NODE*>(TreeNode::parent());
	}
	auto
	setParent(NODE* o) -> void
	{
		TreeNode::setParent(o);
	}
	auto
	unsetParent() -> void
	{
		TreeNode::unsetParent();
	}
	
	auto
	children() const -> GenericTreeNodeRange<T const>
	{
		using	RANGE	=	GenericTreeNodeRange<T const>;
		
		/*
		 Children object may be empty.
		 */
		
		auto	cr	=	TreeNode::children();
		return	cr.empty() ? RANGE{nullptr, nullptr} : RANGE{static_cast<NODE const*>(&cr.front()), static_cast<NODE const*>(&cr.back())};
	}
	auto
	children() -> GenericTreeNodeRange<T>
	{
		using	RANGE	=	GenericTreeNodeRange<T>;
		
		/*
		 Children object may be empty.
		 */
		
		auto	cr	=	TreeNode::children();
		return	cr.empty() ? RANGE{nullptr, nullptr} : RANGE{static_cast<NODE*>(&cr.front()), static_cast<NODE*>(&cr.back())};
	}
	auto
	setChildren(GenericTreeNodeRange<T> o) -> void
	{
		TreeNode::setChildren(o);
	}
	auto
	unsetChildren() -> void
	{
		TreeNode::unsetChildren();
	}
	
	
	
private:
	auto
	_as_base_ptr() const -> TreeNode const*
	{
		return	this;
	}
	auto
	_as_base_ptr() -> TreeNode*
	{
		return	this;
	}
};






































EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DATA_STRUCTURES_TOOLS_END
