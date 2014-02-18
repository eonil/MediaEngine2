////
////  UniqueMemoryBlock.h
////  Foundation
////
////  Created by Hoon H. on 2/5/14.
////
////
//
//#ifndef __Foundation__UniqueMemoryBlock__
//#define __Foundation__UniqueMemoryBlock__
//
//#include "../Common.h"
//#include "../Numerics.h"
//
//namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Foundation {
//	
//	namespace
//	D2014R1			//	Distribution 2014, revision 1.
//	{
//		
//		
//		
//		
//		
//		
//		/*!
//		 Immutable view of a memory range.
//		 */
//		template <typename T>
//		struct
//		GenericMemoryRange
//		{
//			T*		begin{nullptr};
//			T*		end{nullptr};
//			
//			GenericMemoryRange() = default;
//			GenericMemoryRange(T* begin, T* end) : begin(begin), end(end) {}
//			
//			/*!
//			 Creates a new view with another type.
//			 */
//			template <typename V> auto
//			reinterpretAs() const -> GenericMemoryRange<V>
//			{
//				static_assert(sizeof(V) > 0, "Size of the type `V` cannot be zero.");
//				static_assert(sizeof(T) % sizeof(V) == 0 or sizeof(V) % sizeof(T) == 0, "One of sizes of types `T` and `V` must be multiplication of the other one.");
//				EONIL_DEBUG_ASSERT_WITH_MESSAGE((uintptr_t(end) - uintptr_t(begin)) % sizeof(V) == 0, "Size of current block must be exaclt multiplication of destination type `V`.");
//
//				V*	b	=	reinterpret_cast<V*>(begin);
//				V*	e	=	reinterpret_cast<V*>(end);
//				
//				return	GenericMemoryRange<V>(b,e);
//			}
//			
//			operator GenericMemoryRange<std::enable_if<not std::is_const<T>::value, T const>>()
//			{
//				return	GenericMemoryRange<T const>(begin, end);
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
//		/*!
//		 @brief				Fixed sized memory block which will be interpreted as a value strip.
//		 
//		 @classdesign		This is just a proxy editor around memory of value strip. This class
//							does not perform any allocation and initialization. Deallocation may
//							be performed by setting a special template parameter `OWNERSHIP`.
//		 
//		 @discussion		User always use this for existing - already initialized - value strip.
//							This class does not allocate any memory.
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
//		template <typename T, bool const OWNERSHIP = false>
//		class
//		GenericMemoryBlock
//		{
//			friend class				GenericMemoryBlock<T, not OWNERSHIP>;
//			GenericMemoryRange<T>		_ran{};
//			
//		public:
//			GenericMemoryBlock() = default;
//			/*!
//			 Creates a new block with opposite ownership.
//			 */
//			GenericMemoryBlock(GenericMemoryBlock<T,not OWNERSHIP> const& block) : GenericMemoryBlock(block._ran)
//			{
//			}
//			GenericMemoryBlock(T* address, Size count) : GenericMemoryBlock(GenericMemoryRange<T>{address, address + count})
//			{
//				EONIL_DEBUG_ASSERT(address != nullptr);
//				EONIL_DEBUG_ASSERT(count > 0);
//			}
//			GenericMemoryBlock(T* begin, T* end) : GenericMemoryBlock(GenericMemoryRange<T>{begin, end})
//			{
//				EONIL_DEBUG_ASSERT(begin != nullptr);
//				EONIL_DEBUG_ASSERT(begin < end);
//			}
//			GenericMemoryBlock(GenericMemoryRange<T> const& range) : _ran(range)
//			{
//				EONIL_DEBUG_ASSERT(range.begin != nullptr);
//				EONIL_DEBUG_ASSERT(range.end != nullptr);
//				EONIL_DEBUG_ASSERT(range.begin < range.end);
//				
//				if (OWNERSHIP)
//				{
//					size_t	num	=	_ran.end - _ran.begin;
//					GenericMemoryRange<T>	r2{};
//					r2.begin	=	new T[num]();
//					r2.end		=	r2.begin + num;
//					
//					std::swap(r2, _ran);
//				}
//			}
//			~GenericMemoryBlock()
//			{
//				if (OWNERSHIP)
//				{
//					delete[]	_ran.begin;
//				}
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
//				return	GenericMemoryBlock<V>(_ran.template reinterpretAs<V>());
//			}
//			
//			operator GenericMemoryBlock<std::enable_if<not std::is_const<T>::value, T const>>()
//			{
//				return	GenericMemoryBlock<T const>(_ran);
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
//		template <typename T, bool const OWNERSHIP> auto GenericMemoryBlock<T,OWNERSHIP>::
//		empty() const -> bool
//		{
//			return	_ran.begin == nullptr;
//		}
//		template <typename T, bool const OWNERSHIP> auto GenericMemoryBlock<T,OWNERSHIP>::
//		size() const -> Size
//		{
//			return	_ran.end - _ran.begin;
//		}
//		
//		template <typename T, bool const OWNERSHIP> auto GenericMemoryBlock<T,OWNERSHIP>::
//		at(Size const& location) const -> T const&
//		{
//			EONIL_DEBUG_ASSERT(location < size());
//			
//			return	*(_ran.begin + location);
//		}
//		template <typename T, bool const OWNERSHIP> auto GenericMemoryBlock<T,OWNERSHIP>::
//		at(Size const& location) -> T&
//		{
//			EONIL_DEBUG_ASSERT(location < size());
//			
//			return	*(_ran.begin + location);
//		}
//		template <typename T, bool const OWNERSHIP> auto GenericMemoryBlock<T,OWNERSHIP>::
//		front() const -> T const&
//		{
//			return	at(0);
//		}
//		template <typename T, bool const OWNERSHIP> auto GenericMemoryBlock<T,OWNERSHIP>::
//		back() const -> T const&
//		{
//			return	at(size() - 1);
//		}
//		
//		template <typename T, bool const OWNERSHIP> auto GenericMemoryBlock<T,OWNERSHIP>::
//		begin() const -> T const*
//		{
//			return	_ran.begin;
//		}
//		template <typename T, bool const OWNERSHIP> auto GenericMemoryBlock<T,OWNERSHIP>::
//		begin() -> T*
//		{
//			return	_ran.begin;
//		}
//		
//		template <typename T, bool const OWNERSHIP> auto GenericMemoryBlock<T,OWNERSHIP>::
//		end() const -> T const*
//		{
//			return	_ran.end;
//		}
//		template <typename T, bool const OWNERSHIP> auto GenericMemoryBlock<T,OWNERSHIP>::
//		end() -> T*
//		{
//			return	_ran.end;
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
//		template <bool const OWNERSHIP>
//		class
//		GenericMemoryBlock<void,OWNERSHIP>
//		{
//			friend class				GenericMemoryBlock<void, not OWNERSHIP>;
//			GenericMemoryRange<void>	_ran{};
//			
//		public:
//			GenericMemoryBlock() = default;
//			/*!
//			 Creates a new block with opposite ownership.
//			 */
//			GenericMemoryBlock(GenericMemoryBlock<void,not OWNERSHIP> const& block) : GenericMemoryBlock(block._ran)
//			{
//			}
//			GenericMemoryBlock(void* begin, void* end) : GenericMemoryBlock(GenericMemoryRange<void>{begin, end})
//			{
//				EONIL_DEBUG_ASSERT(begin != nullptr);
//				EONIL_DEBUG_ASSERT(begin < end);
//			}
//			GenericMemoryBlock(GenericMemoryRange<void> const& range) : _ran(range)
//			{
//				EONIL_DEBUG_ASSERT(range.begin != nullptr);
//				EONIL_DEBUG_ASSERT(range.end != nullptr);
//				EONIL_DEBUG_ASSERT(range.begin < range.end);
//				
//				if (OWNERSHIP)
//				{
//					/*
//					 Just use the smallest unit = byte = char.
//					 */
//					char*	p0	=	static_cast<char*>(_ran.begin);
//					char*	p1	=	static_cast<char*>(_ran.end);
//					size_t	num	=	p1 - p0;
//					GenericMemoryRange<void>	r2{};
//					r2.begin	=	::operator new[](num);
//					r2.end		=	static_cast<void*>(static_cast<char*>(r2.begin) + num);
//					
//					std::swap(r2, _ran);
//				}
//			}
//			~GenericMemoryBlock()
//			{
//				if (OWNERSHIP)
//				{
//					::operator delete[](_ran.begin);
//				}
//			}
//			
//			auto
//			empty() const -> bool
//			{
//				return	_ran.begin == nullptr;
//			}
//			
//			auto
//			begin() const -> void const*
//			{
//				return	_ran.begin;
//			}
//			auto
//			begin() -> void*
//			{
//				return	_ran.begin;
//			}
//			
//			auto
//			end() const -> void const*
//			{
//				return	_ran.end;
//			}
//			auto
//			end() -> void*
//			{
//				return	_ran.end;
//			}
//			
//		public:
//			/*!
//			 Creates a new view with another type.
//			 */
//			template <typename V> auto
//			reinterpretAs() const -> GenericMemoryBlock<V>
//			{
//				return	GenericMemoryBlock<V>(_ran.template reinterpretAs<V>());
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
////		template <typename T>
////		class
////		UniqueGenericMemoryBlock : public GenericMemoryBlock<T>
////		{
////		public:
////			using	GenericMemoryBlock<T>::GenericMemoryBlock;
////			
////			/*!
////			 Creates a new block of value-strip at arbitrary memory location.
////			 */
////			UniqueGenericMemoryBlock(Size const& size) : GenericMemoryBlock<T>(new T[size](), size)
////			{
////			}
////			
////			/*!
////			 Creates a new owned block with existing unowned block.
////			 */
////			UniqueGenericMemoryBlock(GenericMemoryBlock<T> const& block) : GenericMemoryBlock<T>(block)
////			{
////			}
////			~UniqueGenericMemoryBlock()
////			{
////				delete	this->begin();
////			}
////		};
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
////		using	ReadonlyUnknownMemoryRange			=	GenericMemoryRange<void const>;
////		using	ReadonlyUnknownMemoryBlock			=	GenericMemoryBlock<void const>;
////		using	ReadonlyUniqueUnknownMemoryBlock	=	GenericMemoryBlock<void const,true>;
//		using	UnknownMemoryRange					=	GenericMemoryRange<void>;
//		using	UnknownMemoryBlock					=	GenericMemoryBlock<void>;
//		using	UniqueUnknownMemoryBlock			=	GenericMemoryBlock<void,true>;
//		
//		/*!
//		 Use this for binary memory block.
//		 */
////		using	ReadonlyByteMemoryRange				=	GenericMemoryRange<uint8_t const>;
////		using	ReadonlyByteMemoryBlock				=	GenericMemoryBlock<uint8_t const>;
////		using	ReadonlyByteUniqueByteMemoryBlock	=	GenericMemoryBlock<uint8_t const,true>;
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
//#endif /* defined(__Foundation__UniqueMemoryBlock__) */
