////
////  StableOrderlessSet.h
////  TheFluxGame
////
////  Created by Hoon H. on 3/9/14.
////
////
//
//#pragma once
//
//#include "../CommonRealtimeGameAlgorithmsCommon.h"
//#include "StableDenseStack.h"
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
//template <typename T>
//class
//StableOrderlessSetPerfectHash;
//
//
///*!
// An unordered-set with guaranteed pointer stability, O(1) insert/erase for single element and no hashing.
// 
// @discussion
// This is essentially a singly-linked-list which strictly placed in a sequential array.
// So it has both of O(1) insert/erase of link-list and cache coherence of an array.
// Item layout is very dense. That the algorithm will try to make them dense as much as
// possible, but not force. So it's not perfectly dense, and some items may be laid sparsly, 
// but it doesn't seem to be frequent.
// 
// @classdesign
// Design priority:
// 
// 1.	Pointers must be always stable for any operation.
// 2.	O(1) for insert/erase of single element.
// 3.	No extra operation (such as hashing) for insert/erase.
// 4.	Data locality (dense layout) for cache coherency.
// 
// I tried very much, but this class couldn't be fully dense.
// `std::unordered_set` is quietly similar, but this class has these benefits.
// 
// -	Pointer stability is always guaranteed.
// -	No hashing.
// -	Fixed data density.
// -	You can use bare pointer instead of iterator for insert/erase.
// 
// Currently, this class uses a flag field to makr empty-ness of a slot. This wastes huge memory
// but required to get strict O(1) complexity on insert/erase. To remove this, we need a sorted list 
// of empty slots, and I don't know how to get a sorted list with strict O(1) insert/erase.
// 
// If you can keep your data to be incremental-only, I recommend using `StableDenseStack` which is
// also strictly O(1), fully dense without memory waste.
//
// @warning
// This class uses a non-standard hack. (because I don't know whether this is allowed in standard...)
// This class require a pointer to `Item::value` to be equal to pointer to `Item` itself.
// In other words, the compiler must place the `value` element at first.
// This condition is asserted in debug build.
// 
// @note
// This is designed for referenceable object type `T`. And referenceable object must be stay
// at an address not to invalidate reference pointers. That's why this class does not support
// insertion by move.
// 
// Because this is stable, you can perform perfect-hash on items using thier pointer address by
// getting an offset from first item's address.
// */
////			template <typename T, Size const LIMIT>
//template <typename T>
//class
//StableOrderlessSet
//{
//	friend class	StableOrderlessSetPerfectHash<T>;
//	
//	static constexpr bool const	IS_T_COPYABLE	=	std::is_trivially_copyable<T>::value;
//	
////				using	COPYABLE_T	=	typename std::enable_if<IS_T_COPYABLE, T>::type;
//	
//	struct
//	Flags
//	{
//		union
//		{
//			Size		bits	{0};
//			struct
//			{
//				bool	occupation:1;
//			};
//		};
//	};
//	/*!
//	 Put togather for cache cohesion.
//	 
//	 @classdesign
//	 This class never need to be copied or moved. (it's a bug if it needs to be)
//	 So copy and move constructors are all deleted.
//	 */
//	struct
//	NonDefaultConstructibleItem
//	{
//		T		value;
//		Flags	flags	{};
//		
//		NonDefaultConstructibleItem() = delete;
//		NonDefaultConstructibleItem(T const& v) : value(v) {};
//		NonDefaultConstructibleItem(T&& v) : value(std::move(v)) {};
//
//		template <typename ...ARGS>
//		NonDefaultConstructibleItem(ARGS&&... args) : value(std::forward<ARGS>(args)...)
//		{
//		}
//		
//		NonDefaultConstructibleItem(NonDefaultConstructibleItem const&) = delete;
//		NonDefaultConstructibleItem(NonDefaultConstructibleItem&&) = delete;
//	};
//	struct
//	DefaultConstructibleItem : NonDefaultConstructibleItem
//	{
//		using	NonDefaultConstructibleItem::NonDefaultConstructibleItem;
//		
//		DefaultConstructibleItem() : NonDefaultConstructibleItem(T{}) {}
//	};
//	
//	using	Item	=	typename std::conditional<std::is_default_constructible<T>::value, DefaultConstructibleItem, NonDefaultConstructibleItem>::type;
//	
//	////
//	
//	StableDenseStack<Item>		_items			{};
//	StableDenseStack<Item*>		_empty_slots	{};
//	
//	////
//	
//	static auto
//	ASSERT_POINTER_EQUALITY_REQUIREMENT(Item const& item) -> void
//	{
//		EONIL_COMMON_REALTIME_GAME_ALGORITHMS_DEBUG_ASSERT(((void*)&item == (void*)&item.value), "A pointer to an `Item` object must be equal to a pointer to its `Item::value` field. This is non-standard behavior but required by design for efficiency.");
//	}
//	
//public:
//	template <bool const CONSTNESS>
//	class
//	CovariantIterator
//	{
//		friend class	StableOrderlessSet<T>;
//		using	V	=	typename std::conditional<CONSTNESS, Item const, Item>::type;
//		using	VT	=	typename std::conditional<CONSTNESS, T const, T>::type;
//		
//		V*	_ptr	{nullptr};
//		V*	_eptr	{nullptr};
//		
//		CovariantIterator(V* ptr, V* eptr) : _ptr(ptr), _eptr(eptr) {}
//		
//	public:
//		CovariantIterator() = delete;
//		CovariantIterator(CovariantIterator const& it) : _ptr(it._ptr), _eptr(it._eptr) {}
//		CovariantIterator(CovariantIterator&& it) : _ptr(std::move(it._ptr)), _eptr(std::move(_eptr)) {}
////					~CovariantIterator();
//		
//		auto
//		operator!=(CovariantIterator const& it) const -> bool
//		{
//			return	_ptr != it._ptr;
//		}
//		auto
//		operator++() -> void
//		{
//			_ptr++;
//			while (_ptr != _eptr and not _ptr->flags.occupation)
//			{
//				_ptr++;
//			}
//		}
//		auto
//		operator*() -> VT&
//		{
//			return	_ptr->value;
//		}
//	};
//	
//	using	ConstIterator	=	CovariantIterator<true>;
//	using	Iterator		=	CovariantIterator<false>;
//	
//public:
//	StableOrderlessSet() = delete;
//	StableOrderlessSet(StableOrderlessSet const&) = delete;
//	StableOrderlessSet(StableOrderlessSet&&) = default;
//	
//	StableOrderlessSet(Size const& capacity);
//	
//	auto	operator=(StableOrderlessSet o) -> StableOrderlessSet& = delete;
//	auto	operator=(StableOrderlessSet const& o) -> StableOrderlessSet& = delete;
//	auto	operator=(StableOrderlessSet&& o) -> StableOrderlessSet& = delete;
//	
//	auto	empty() const -> bool;
//	auto	size() const -> Size;
//	
//	auto	begin() const -> ConstIterator;
//	auto	end() const -> ConstIterator;
//	
//	auto	begin() -> Iterator;
//	auto	end() -> Iterator;
//	
//	auto	insert(T&& v) -> T*;				//	Same with `emplace()`.
////				auto	insert(T const& v) -> T*;
////				auto	insert(T&& v) -> T*;
//	auto	erase(T* v) -> void;
//	
//	template <typename... ARGS>
//	auto	emplace (ARGS&&... args) -> T*;
//};
//
//template <typename T>
//StableOrderlessSet<T>::
//StableOrderlessSet(Size const& capacity) : _items(capacity), _empty_slots(capacity)
//{
//	static_assert(std::is_move_constructible<T>::value, "The type `T` must be move-constructible at least. It doesn't need to be copy-constructible.");
//	static_assert(std::is_move_assignable<T>::value, "The type `T` must be move-assignable at least. It doesn't need to be copy-assignable.");
//}
//
//template <typename T>
//auto StableOrderlessSet<T>::
//empty() const -> bool
//{
//	return	size() == 0;
//}
//
//template <typename T>
//auto StableOrderlessSet<T>::
//size() const -> Size
//{
//	return	_items.size() - _empty_slots.size();
//}
//
//template <typename T>
//auto StableOrderlessSet<T>::
//begin() const -> ConstIterator
//{
//	return	{_items.data(), _items.data()+_items.size()};
//}
//template <typename T>
//auto StableOrderlessSet<T>::
//end() const -> ConstIterator
//{
//	return	{&_items.at(size()), _items.data()+_items.size()};
//}
//
//template <typename T>
//auto StableOrderlessSet<T>::
//begin() -> Iterator
//{
//	Item*	ptr	=	_items.data();
//	return	Iterator{ptr, _items.data()+_items.size()};
//}
//template <typename T>
//auto StableOrderlessSet<T>::
//end() -> Iterator
//{
//	Item*	eptr	=	_items.data()+_items.size();
//	return	{eptr, eptr};
//}
//
//
//template <typename T>
//template <typename ...ARGS>
//auto StableOrderlessSet<T>::
//emplace(ARGS&&... args) -> T*
//{
//	_items.emplace(std::forward<ARGS>(args)...);
//	_items.back().flags.occupation	=	true;
//	return	&(_items.at(_items.size() - 1).value);
//}
//template <typename T>
//auto StableOrderlessSet<T>::
//insert(T&& v) -> T*
//{
//	if (_empty_slots.size() > 0)
//	{
//		Item*	ptr		=	_empty_slots.back();
//		new (ptr) Item(std::move(v));
//		_empty_slots.pop();
//		ptr->flags.occupation	=	true;
//		return	&ptr->value;
//	}
//	else
//	{
//		_items.emplace(std::move(v));
//		ASSERT_POINTER_EQUALITY_REQUIREMENT(_items.back());
//		_items.back().flags.occupation	=	true;
//		return	&_items.back().value;
//	}
//}
//
//
//template <typename T>
//auto StableOrderlessSet<T>::
//erase(T* v) -> void
//{
//	v->~T();
//	_empty_slots.emplace((Item*)v);
//	
//	((Item*)v)->flags.occupation	=	false;
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
//EONIL_COMMON_REALTIME_GAME_ALGORITHMS_FLAT_CONTAINERS_END
