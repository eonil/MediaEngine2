//
//  GenericMemoryRange.h
//  Foundation
//
//  Created by Hoon H. on 2/6/14.
//
//

#ifndef __Foundation__GenericMemoryRange__
#define __Foundation__GenericMemoryRange__

#include "../Common.h"
#include "../Numerics.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Foundation {
	
	inline namespace
	D2014R1			//	Distribution 2014, revision 1.
	{
		template <typename T>
		class
		GenericMemoryRange;
		
		
		
		namespace
		{
			
			template <typename X>
			struct
			_void_aware_sizeof
			{
				static const size_t	value	=	sizeof(X);
			};
			template <>
			struct
			_void_aware_sizeof<void>
			{
				static const size_t	value	=	0;
			};
			template <>
			struct
			_void_aware_sizeof<void const>
			{
				static const size_t	value	=	0;
			};
			
			template<typename T>
			constexpr auto
			_VOID_AWARE_SIZEOF() -> Size
			{
				return	_void_aware_sizeof<T>::value;
			}
		}
		
		
		
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
				EONIL_DEBUG_ASSERT((_begin != nullptr and _end != nullptr and _begin < _end) or (_begin == nullptr and _end == nullptr));
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
				static_assert(sizeof(V) > 0, "Size of the type `V` cannot be zero.");
				static_assert((not std::is_same<typename std::remove_const<T>::type, void>::value and not std::is_same<typename std::remove_const<V>::type, void>::value)
							  or (_VOID_AWARE_SIZEOF<T>() % _VOID_AWARE_SIZEOF<V>() == 0 or _VOID_AWARE_SIZEOF<V>() % _VOID_AWARE_SIZEOF<T>() == 0),
							  "One of sizes of types `T` and `V` must be multiplication of the other one or `void`.");
				EONIL_DEBUG_ASSERT_WITH_MESSAGE((uintptr_t(_end) - uintptr_t(_begin)) % sizeof(V) == 0, "Size of current block must be exaclt multiplication of destination type `V`.");
				
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
		 */
		template <typename T>
		class
		GenericMemoryRange : public _MemoryRangeAbstraionLevel1<T>
		{
			using	BASE	=	_MemoryRangeAbstraionLevel1<T>;
			
		public:
			GenericMemoryRange() = default;															//!	 Creates an empty range. (invalid state)
			GenericMemoryRange(T* address, Size count) : BASE(address, address + count)
			{
			}
			GenericMemoryRange(T* begin, T* end) : BASE(begin, end)
			{
			}
			
			auto	size() const -> Size;
			
			auto	at(Size const& location) const -> T const&;
			auto	at(Size const& location) -> T&;
			
			auto	front() const -> T const&;
			auto	back() const -> T const&;
		};
		
		template <typename T> auto GenericMemoryRange<T>::
		size() const -> Size
		{
			return	BASE::end() - BASE::begin();
		}
		
		template <typename T> auto GenericMemoryRange<T>::
		at(Size const& location) const -> T const&
		{
			EONIL_DEBUG_ASSERT(location < size());
			
			return	*(BASE::begin() + location);
		}
		template <typename T> auto GenericMemoryRange<T>::
		at(Size const& location) -> T&
		{
			EONIL_DEBUG_ASSERT(location < size());
			
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
				EONIL_DEBUG_ASSERT(_begin != nullptr);
				EONIL_DEBUG_ASSERT(_end != nullptr);
				EONIL_DEBUG_ASSERT(_begin < _end);
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
				EONIL_DEBUG_ASSERT(_begin != nullptr);
				EONIL_DEBUG_ASSERT(_end != nullptr);
				EONIL_DEBUG_ASSERT(_begin < _end);
			}
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		

		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
}}}}



#endif /* defined(__Foundation__GenericMemoryRange__) */
