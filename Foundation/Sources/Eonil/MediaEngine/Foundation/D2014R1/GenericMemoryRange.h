//
//  GenericMemoryRange.h
//  Foundation
//
//  Created by Hoon H. on 2/6/14.
//
//

#pragma once
#include "../Prelude.h"
#include "ConstantEvaluationUtility.h"
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_BEGIN
inline namespace
D2014R1			//	Distribution 2014, revision 1.
{
	template <typename T>
	class
	GenericMemoryRange;
	
	
	
	
	template <typename T>
	class
	_MemoryRangeAbstraionLevel1
	{	
	protected:
		T*		_begin{nullptr};
		T*		_end{nullptr};
		
	protected:
		_MemoryRangeAbstraionLevel1() = default;
		_MemoryRangeAbstraionLevel1(T* begin, T* end) : _begin(begin), _end(end)
		{
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion((_begin != nullptr and _end != nullptr and _begin < _end) or (_begin == nullptr and _end == nullptr));
			}
			
			////
		}

	public:
		auto	empty() const -> bool;
		
		auto	begin() const -> T const*;
		auto	begin() -> T*;
		
		auto	end() const -> T const*;
		auto	end() -> T*;
		
	public:
		/*!
		 Creates a new view with another type.
		 */
		template <typename V> auto
		reinterpretAs() const -> GenericMemoryRange<V>
		{
			using namespace	ConstantEvaluation;
			
			static_assert(std::is_void<V>::value or
						  void_aware_sizeof<V>() > 0,
						  "The type `V` must be `void or non-zero sized.");
			
			static_assert(std::is_void<T>::value or
						  std::is_void<V>::value or
						  void_aware_sizeof<T>() % void_aware_sizeof<V>() == 0 or
						  void_aware_sizeof<V>() % void_aware_sizeof<T>() == 0,
						  "One of sizes of types `T` and `V` must be multiplication of the other unless one of them is `void`.");

			if (void_aware_sizeof<V>() == sz(0))
			{
				//	We cannot check because we don't know the destination type.
			}
			else
			{
				if (USE_DEBUGGING_ASSERTIONS)
				{
					err9_converted_legacy_assertion((uintptr_t(_end) - uintptr_t(_begin)) % void_aware_sizeof<V>() == 0, "Size of current block must be exaclt multiplication of destination type `V` unless `V` is `void`.");
				}
			}
			
			////
			
			V*	b	=	reinterpret_cast<V*>(_begin);
			V*	e	=	reinterpret_cast<V*>(_end);
			
			return	GenericMemoryRange<V>(b,e);
		}
		
		operator GenericMemoryRange<std::enable_if<not std::is_const<T>::value, T const>>()
		{
			return	GenericMemoryRange<T const>(begin, end);
		}
	};
	
	template <typename T> auto _MemoryRangeAbstraionLevel1<T>::
	empty() const -> bool
	{
		return	_begin == nullptr;
	}
	
	template <typename T> auto _MemoryRangeAbstraionLevel1<T>::
	begin() const -> T const*
	{
		return	_begin;
	}
	template <typename T> auto _MemoryRangeAbstraionLevel1<T>::
	begin() -> T*
	{
		return	_begin;
	}
	
	template <typename T> auto _MemoryRangeAbstraionLevel1<T>::
	end() const -> T const*
	{
		return	_end;
	}
	template <typename T> auto _MemoryRangeAbstraionLevel1<T>::
	end() -> T*
	{
		return	_end;
	}
	

	

	
	
	
	
	
	
	
	
	
	/*!
	 A proxy view of a memory range.
	 
	 @classdesign
	 You should treat this with pointer semantics.
	 
	 @brief
	 This is used to represent a fixed sized collection.
	 
	 @note
	 This is special case (consecutive list of values) of generic range concept.
	 Can be replaced by generic range concept in near future.
	 So be careful when you add a new feature.
	 */
	template <typename T>
	class
	GenericMemoryRange : public _MemoryRangeAbstraionLevel1<T>
	{
		using	BASE	=	_MemoryRangeAbstraionLevel1<T>;
		
	public:
		GenericMemoryRange() = default;															//!	 Creates an empty range. (invalid state)
		GenericMemoryRange(T* address, sz count) : BASE(address, address + count)
		{
		}
		GenericMemoryRange(T* begin, T* end) : BASE(begin, end)
		{
		}
		
		auto	size() const -> sz;
		
		auto	at(sz const& location) const -> T const&;
		auto	at(sz const& location) -> T&;
		
		auto	front() const -> T const&;
		auto	back() const -> T const&;
	};
	
	template <typename T> auto GenericMemoryRange<T>::
	size() const -> sz
	{
		return	BASE::end() - BASE::begin();
	}
	
	template <typename T> auto GenericMemoryRange<T>::
	at(sz const& location) const -> T const&
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(location < size());
		}
		
		////
		
		return	*(BASE::begin() + location);
	}
	template <typename T> auto GenericMemoryRange<T>::
	at(sz const& location) -> T&
	{
		if (USE_DEBUGGING_ASSERTIONS)
		{
			err9_converted_legacy_assertion(location < size());
		}
		
		////
		
		return	*(BASE::begin() + location);
	}
	template <typename T> auto GenericMemoryRange<T>::
	front() const -> T const&
	{
		return	at(0);
	}
	template <typename T> auto GenericMemoryRange<T>::
	back() const -> T const&
	{
		return	at(size() - 1);
	}
	
	
	
	/*!
	 The case of `void*`. This is special because we cannot know the type details.
	 We just know the addressing range, and nothing else. You can't know even size 
	 because that require the range to be a byte array. If you really want some 
	 byte-based operation, convert this into `GenericMemoryBlock<uint8_t>` (a.k.a.
	 `ByteMemoryBlock`).
	 */
	template <>
	class
	GenericMemoryRange<void> : public _MemoryRangeAbstraionLevel1<void>
	{
		using	BASE	=	_MemoryRangeAbstraionLevel1<void>;
		
	public:
		GenericMemoryRange() = default;
		GenericMemoryRange(void* begin, void* end) : BASE(begin, end)
		{
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(_begin != nullptr);
				err9_converted_legacy_assertion(_end != nullptr);
				err9_converted_legacy_assertion(_begin < _end);
			}
		}
		
	};
	
	template <>
	class
	GenericMemoryRange<void const> : public _MemoryRangeAbstraionLevel1<void const>
	{
		using	BASE	=	_MemoryRangeAbstraionLevel1<void const>;
		
	public:
		GenericMemoryRange() = default;
		GenericMemoryRange(void const* begin, void const* end) : BASE(begin, end)
		{
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(_begin != nullptr);
				err9_converted_legacy_assertion(_end != nullptr);
				err9_converted_legacy_assertion(_begin < _end);
			}
		}
		
		/*!
		 Any type range can be converted into `void const` type.
		 */
		template <typename T>
		GenericMemoryRange(GenericMemoryRange<T const> origin) : GenericMemoryRange(origin.begin(), origin.end())
		{
		}
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_END