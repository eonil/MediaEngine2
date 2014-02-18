////
////  GenericMemoryRange.h
////  Foundation
////
////  Created by Hoon H. on 2/6/14.
////
////
//
//#ifndef __Foundation__GenericMemoryRange__
//#define __Foundation__GenericMemoryRange__
//
//#include <memory>
//#include "../Common.h"
//#include "../Numerics.h"
//
//namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Foundation {
//	
//	namespace
//	D2014R1			//	Distribution 2014, revision 1.
//	{
//		namespace
//		MemoryUtility
//		{
//			static inline auto
//			sizeInBytes(void const* begin, void const* end) -> size_t
//			{
//				char const*	p0	=	static_cast<char const*>(begin);
//				char const*	p1	=	static_cast<char const*>(end);
//				size_t		num	=	p1 - p0;
//				return		num	;
//			}
//		};
//		
//		
//		
//		/*
//		 Memory range is a view of a sequential memory range. It's essentially a proxy view,
//		 and doesn't claim ownership.
//		 
//		 Memory block is uniquely owned memory range.
//		 */
//		
//		template <bool const CONSTNESS>
//		class
//		UnknownMemoryRange;
//		
//		template <bool const CONSTNESS>
//		class
//		UnknownMemoryBlock;
//		
//		
//		
//		
//		
//		template <typename T>
//		class
//		GenericMemoryRange;
//		
//		template <typename T>
//		class
//		GenericMemoryBlock;
//		
//		
//		
//		
//		
//		
//		
//		/*!
//		 The case of `void*`. This is special because we cannot know some details.
//		 We just know the range, and nothing else. You can't know even size because
//		 that require the range to be a byte array. If you really want some byte-
//		 based operation, convert this into `GenericMemoryBlock<uint8_t>` (a.k.a.
//		 `ByteMemoryBlock`).
//		 */
//		template <bool const CONSTNESS>
//		class
//		UnknownMemoryRange
//		{
//			using	T	=	std::conditional<CONSTNESS, void const, void>;
//			
//			friend class	UnknownMemoryRange<CONSTNESS>;
//			T*				_begin{nullptr};
//			T*				_end{nullptr};
//			
//			auto
//			_size_in_bytes() const -> size_t
//			{
//				return	MemoryUtility::sizeInBytes(_begin, _end);
//			}
//			
//		public:
//			UnknownMemoryRange() = default;
//			UnknownMemoryRange(void* begin, void* end) : UnknownMemoryRange(begin, end)
//			{
//				EONIL_DEBUG_ASSERT(_begin != nullptr);
//				EONIL_DEBUG_ASSERT(_end != nullptr);
//				EONIL_DEBUG_ASSERT(_begin < _end);
//			}
//			
//			auto
//			empty() const -> bool
//			{
//				return	_begin == nullptr;
//			}
//			
//			auto
//			begin() const -> void const*
//			{
//				return	_begin;
//			}
//			auto
//			begin() -> void*
//			{
//				return	_begin;
//			}
//			
//			auto
//			end() const -> void const*
//			{
//				return	_end;
//			}
//			auto
//			end() -> void*
//			{
//				return	_end;
//			}
//			
//		public:
//			/*!
//			 Creates a new view with another type.
//			 */
//			template <typename V> auto
//			reinterpretAs() const -> GenericMemoryBlock<V>
//			{
//				static_assert(sizeof(V) > 0, "Size of the type `V` cannot be zero.");
//				EONIL_DEBUG_ASSERT_WITH_MESSAGE(_size_in_bytes() % sizeof(V) == 0, "Size of current block must be exact multiplication of destination type `V`.");
//				
//				V*	b	=	reinterpret_cast<V*>(begin);
//				V*	e	=	reinterpret_cast<V*>(end);
//				
//				return	GenericMemoryRange<V>(b,e);
//			}
//			
//			/*!
//			 Conversion to immutable view is always available implicitly.
//			 */
//			operator UnknownMemoryRange<true>()
//			{
//				return	UnknownMemoryRange<true>(_begin, _end);
//			}
//		};
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
//		
//		
//		
//		
//		
//		
//		/*!
//		 @brief				Fixed sized memory block which will be interpreted as a value strip.
//		 
//		 @classdesign		This is just a proxy editor around memory of value strip. This class
//		 does not perform any allocation and initialization. Deallocation may
//		 be performed by setting a special template parameter `OWNERSHIP`.
//		 
//		 @discussion		User always use this for existing - already initialized - value strip.
//		 This class does not allocate any memory.
//		 
//		 @param	OWNERSHIP	Owns the memory range if this is `true`. As a consequence,
//							the memory block will be deallocated when the block object
//							deallocates.
//							If the type `T` is `void`, the memory will be deallocated using
//							`::operator delete[]`, and destructors will not be called.
//							In any case, this class assumes the memory is an array which has been
//							allocated by `new[]` operator,
//
//							If this is true, this class will exclusively own the
//							memory block. That means this will copy the data on
//							construction, and delete the copy on destruction.
//		 */
//		template <typename T>
//		class
//		GenericMemoryRange : public UnknownMemoryRange<std::is_const<T>::value>
//		{
//		public:
//			GenericMemoryRange() = default;
//			GenericMemoryRange(T* address, Size count) : GenericMemoryRange(address, address + count)
//			{
//			}
//			GenericMemoryRange(T* begin, T* end) : UnknownMemoryRange<std::is_const<T>::value>(begin, end)
//			{
//			}
//			
//			auto	empty() const -> bool;
//			auto	size() const -> Size;
//			
//			auto	at(Size const& location) const -> T const&;
//			auto	at(Size const& location) -> T&;
//			
//			auto	front() const -> T const&;
//			auto	back() const -> T const&;
//			
//			auto	begin() const -> T const*;
//			auto	begin() -> T*;
//			
//			auto	end() const -> T const*;
//			auto	end() -> T*;
//			
//		public:
//			/*!
//			 Creates a new view with another type.
//			 This performs `reinterpret_case<T>`, so you should know the original type.
//			 */
//			template <typename V> auto
//			reinterpretAs() const -> GenericMemoryBlock<V>
//			{
//				static_assert(sizeof(V) > 0, "Size of the type `V` cannot be zero.");
//				static_assert(sizeof(T) % sizeof(V) == 0 or sizeof(V) % sizeof(T) == 0, "One of sizes of types `T` and `V` must be multiplication of the other one.");
//				EONIL_DEBUG_ASSERT_WITH_MESSAGE((uintptr_t(end) - uintptr_t(begin)) % sizeof(V) == 0, "Size of current block must be exaclt multiplication of destination type `V`.");
//				
//				V*	b	=	reinterpret_cast<V*>(begin);
//				V*	e	=	reinterpret_cast<V*>(end);
//				
//				return	GenericMemoryBlock<V>(b,e);
//			}
//			
////			operator GenericMemoryRange<std::enable_if<not std::is_const<T>::value, T const>>()
//			operator GenericMemoryRange<T const>()
//			{
//				return	GenericMemoryRange<T const>(_begin, _end);
//			}
//		};
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
//		template <typename T> auto GenericMemoryRange<T>::
//		empty() const -> bool
//		{
//			EONIL_DEBUG_ASSERT(_begin == nullptr and _end == nullptr or _begin != nullptr and _end != nullptr);
//			return	_begin == nullptr;
//		}
//		template <typename T> auto GenericMemoryRange<T>::
//		size() const -> Size
//		{
//			EONIL_DEBUG_ASSERT(_begin == nullptr and _end == nullptr or _begin != nullptr and _end != nullptr);
//			return	_end - _begin;
//		}
//		
//		template <typename T> auto GenericMemoryRange<T>::
//		at(Size const& location) const -> T const&
//		{
//			EONIL_DEBUG_ASSERT(location < size());
//			
//			return	*(_begin + location);
//		}
//		template <typename T> auto GenericMemoryRange<T>::
//		at(Size const& location) -> T&
//		{
//			EONIL_DEBUG_ASSERT(location < size());
//			
//			return	*(_begin + location);
//		}
//		template <typename T> auto GenericMemoryRange<T>::
//		front() const -> T const&
//		{
//			return	at(0);
//		}
//		template <typename T> auto GenericMemoryRange<T>::
//		back() const -> T const&
//		{
//			return	at(size() - 1);
//		}
//		
//		template <typename T> auto GenericMemoryRange<T>::
//		begin() const -> T const*
//		{
//			return	_begin;
//		}
//		template <typename T> auto GenericMemoryRange<T>::
//		begin() -> T*
//		{
//			return	_begin;
//		}
//		
//		template <typename T> auto GenericMemoryRange<T>::
//		end() const -> T const*
//		{
//			return	_end;
//		}
//		template <typename T> auto GenericMemoryRange<T>::
//		end() -> T*
//		{
//			return	_end;
//		}
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
//		template <typename T>
//		class
//		GenericMemoryBlock
//		{
//			GenericMemoryRange<T>	_range{};
//			
//			static auto
//			_copy_mem_range(GenericMemoryRange<T> const& range) -> GenericMemoryRange<T>
//			{
//				size_t	num	=	range.end() - range.begin();
//				T*	b2		=	new T[num]();
//				T*	e2		=	b2 + num;
//				std::memcpy(b2, range.begin(), MemoryUtility::sizeInBytes(range.begin(), range.end());
//				return	GenericMemoryRange<T>(b2, e2);
//			}
//			
//		public:
//			GenericMemoryBlock(GenericMemoryRange<T> const& range) : _range(_copy_mem_range(range))
//			{
//			}
//			~GenericMemoryBlock()
//			{
//				delete[]	_range.begin();
//			}
//			
//		public:
//			auto	range() const -> GenericMemoryRange<T> const&;
//			auto	range() -> GenericMemoryRange<T>&;
//		};
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
//		using	MutableUnknownMemoryRange	=	UnknownMemoryRange<false>;
//		using	ImmutableUnknownMemoryRange	=	UnknownMemoryRange<true>;
//		
//							
//		
//		
//		template <typename T>
//		using	strip	=	GenericMemoryBlock<T>;
//		
//		
//		
//		
////		
////		
////		
////		
////		/*!
////		 The case of `void*`. This is special because we cannot know some details.
////		 We just know the range, and nothing else. You can't know even size because
////		 that require the range to be a byte array. If you really want some byte-
////		 based operation, convert this into `GenericMemoryBlock<uint8_t>` (a.k.a.
////		 `ByteMemoryBlock`).
////		 */
////		template <bool const OWNERSHIP>
////		class
////		GenericMemoryBlock<void,OWNERSHIP>
////		{
////			friend class				GenericMemoryBlock<void, not OWNERSHIP>;
////			T*							_begin{nullptr};
////			T*							_end{nullptr};
////			
////		public:
////			GenericMemoryBlock() = default;
////			/*!
////			 Creates a new block with opposite ownership.
////			 */
////			GenericMemoryBlock(GenericMemoryBlock<void,not OWNERSHIP> const& block) : GenericMemoryBlock(block._begin, block._end)
////			{
////			}
////			GenericMemoryBlock(void* begin, void* end) : GenericMemoryBlock(begin, end)
////			{
////				EONIL_DEBUG_ASSERT(_begin != nullptr);
////				EONIL_DEBUG_ASSERT(_end != nullptr);
////				EONIL_DEBUG_ASSERT(_begin < _end);
////				
////				if (OWNERSHIP)
////				{
////					/*
////					 Just use the smallest unit = byte = char.
////					 */
////					char*	p0	=	static_cast<char*>(_begin);
////					char*	p1	=	static_cast<char*>(_end);
////					size_t	num	=	p1 - p0;
////
////					void*	b2	=	::operator new[](num);
////					void*	e2	=	static_cast<void*>(static_cast<char*>(b2) + num);
////					
////					std::swap(b2, _begin);
////					std::swap(e2, _end);
////				}
////			}
////			~GenericMemoryBlock()
////			{
////				if (OWNERSHIP)
////				{
////					::operator delete[](_begin);
////				}
////			}
////			
////			auto
////			empty() const -> bool
////			{
////				return	_begin == nullptr;
////			}
////			
////			auto
////			begin() const -> void const*
////			{
////				return	_begin;
////			}
////			auto
////			begin() -> void*
////			{
////				return	_begin;
////			}
////			
////			auto
////			end() const -> void const*
////			{
////				return	_end;
////			}
////			auto
////			end() -> void*
////			{
////				return	_end;
////			}
////			
////		public:
////			/*!
////			 Creates a new view with another type.
////			 */
////			template <typename V> auto
////			reinterpretAs() const -> GenericMemoryBlock<V>
////			{
////				static_assert(sizeof(V) > 0, "Size of the type `V` cannot be zero.");
////				static_assert(sizeof(T) % sizeof(V) == 0 or sizeof(V) % sizeof(T) == 0, "One of sizes of types `T` and `V` must be multiplication of the other one.");
////				EONIL_DEBUG_ASSERT_WITH_MESSAGE((uintptr_t(end) - uintptr_t(begin)) % sizeof(V) == 0, "Size of current block must be exaclt multiplication of destination type `V`.");
////				
////				V*	b	=	reinterpret_cast<V*>(begin);
////				V*	e	=	reinterpret_cast<V*>(end);
////				
////				return	GenericMemoryBlock<V>(b,e);
//////				return	GenericMemoryBlock<V>(_ran.template reinterpretAs<V>());
////			}
////		};
////		
////		
////		
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
//		//		template <typename T>
//		//		class
//		//		UniqueGenericMemoryBlock : public GenericMemoryBlock<T>
//		//		{
//		//		public:
//		//			using	GenericMemoryBlock<T>::GenericMemoryBlock;
//		//
//		//			/*!
//		//			 Creates a new block of value-strip at arbitrary memory location.
//		//			 */
//		//			UniqueGenericMemoryBlock(Size const& size) : GenericMemoryBlock<T>(new T[size](), size)
//		//			{
//		//			}
//		//
//		//			/*!
//		//			 Creates a new owned block with existing unowned block.
//		//			 */
//		//			UniqueGenericMemoryBlock(GenericMemoryBlock<T> const& block) : GenericMemoryBlock<T>(block)
//		//			{
//		//			}
//		//			~UniqueGenericMemoryBlock()
//		//			{
//		//				delete	this->begin();
//		//			}
//		//		};
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
//		template <typename T>	using	MemoryRange			=	GenericMemoryRange<T>;
//		template <typename T>	using	MemoryBlock			=	GenericMemoryBlock<T>;
//		
//		
//		/*
//		 Classes for unknown type memory block. Usually `void*` passed from C functions.
//		 */
//		//		using	ReadonlyUnknownMemoryRange			=	GenericMemoryRange<void const>;
//		//		using	ReadonlyUnknownMemoryBlock			=	GenericMemoryBlock<void const>;
//		//		using	ReadonlyUniqueUnknownMemoryBlock	=	GenericMemoryBlock<void const,true>;
//		using	UnknownMemoryRange					=	GenericMemoryRange<void>;
//		using	UnknownMemoryBlock					=	GenericMemoryBlock<void>;
//		using	UniqueUnknownMemoryBlock			=	GenericMemoryBlock<void,true>;
//		
//		/*!
//		 Use this for binary memory block.
//		 */
//		//		using	ReadonlyByteMemoryRange				=	GenericMemoryRange<uint8_t const>;
//		//		using	ReadonlyByteMemoryBlock				=	GenericMemoryBlock<uint8_t const>;
//		//		using	ReadonlyByteUniqueByteMemoryBlock	=	GenericMemoryBlock<uint8_t const,true>;
//		
//		using	ByteMemoryRange						=	GenericMemoryRange<uint8_t>;
//		using	ByteMemoryBlock						=	GenericMemoryBlock<uint8_t>;
//		using	UniqueByteMemoryBlock				=	GenericMemoryBlock<uint8_t,true>;
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
//		
//		
//		
//	}
//	
//}}}}
//
//#endif /* defined(__Foundation__GenericMemoryRange__) */
