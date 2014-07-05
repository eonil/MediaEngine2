//
//  TestSuite2.h
//  CommonRealtimeGameAlgorithms
//
//  Created by Hoon H. on 14/4/30.
//
//

#pragma once

#include "TestCommon.h"

#include <memory>
#include <cmath>


template <std::size_t LEN>
constexpr inline auto
aligned_size_of() -> std::size_t
{
	return	sizeof(typename std::aligned_storage<LEN>::type);
}
template <typename T>
constexpr inline auto
aligned_size_of() -> std::size_t
{
	return	aligned_size_of<sizeof(T)>();
}


inline auto
experiment_mem_alignment() -> void
{
	{
		struct
		AAA
		{
			char	a	=	'A';
		};
		struct
		BBB
		{
			AAA		a	=	{};
			char	b	=	'B';
		};
		struct
		CCC
		{
			BBB		b	=	{};
			char	c	=	'C';
		};
		
		test_log(sizeof(AAA));
		test_log(sizeof(BBB));
		test_log(sizeof(CCC));
		test_assert(sizeof(AAA) == 1);
		test_assert(sizeof(BBB) == 2);
		test_assert(sizeof(CCC) == 3);
	}
	{
		struct
		AAA
		{
			int32_t	a	=	'A';
		};
		struct
		BBB
		{
			struct
			{
				AAA		a  	=	{};
				char	b	=	'B';
			};
			//			__attribute__((packed));
		};
		struct
		CCC
		{
			BBB		b	=	{};
			char	c	=	'C';
		};
		
		test_log(sizeof(AAA));
		test_log(sizeof(BBB));
		test_log(sizeof(CCC));
		test_assert(sizeof(AAA) == 4);
		test_assert(sizeof(BBB) == 8);
		test_assert(sizeof(CCC) == 12);
	}
	
	{
		struct
		AAA
		{
			int32_t	a	=	'A';
			char	a1	=	'a';
		}
		__attribute__((packed));
		
		struct
		BBB
		{
			struct
			{
				AAA		a  	=	{};
				char	b	=	'B';
			};
		};
		
		struct
		CCC
		{
			BBB		b	=	{};
			char	c	=	'C';
		};
		
		test_log(alignof(std::max_align_t));
		test_log(alignof(AAA));
		test_log(alignof(BBB));
		test_log(alignof(CCC));
		test_log(std::alignment_of<BBB>::value);
		test_log(std::alignment_of<CCC>::value);
		
		test_log(sizeof(AAA));
		test_log(sizeof(BBB));
		test_log(sizeof(CCC));
		test_log(sizeof(CCC::b));
		test_assert(sizeof(AAA) == 5);
		test_assert(sizeof(BBB) == 6);
		test_assert(sizeof(CCC) == 7);
		test_assert(sizeof(CCC::b) == 6);
	}
	{
		struct
		AAA
		{
			int32_t	a	=	'A';
			char	a1	=	'a';
		};
		
		struct
		BBB_PACKED
		{
			struct
			{
				AAA		a  	=	{};
				char	b	=	'B';
			}
			__attribute__((packed));
		};
		
		using	ALIGNED_BBB_PACKED	=	typename std::aligned_storage<sizeof(BBB_PACKED)>::type;
		
		struct
		CCC
		{
			struct
			State
			{
				BBB_PACKED		b	=	{};
				char			c	=	'C';
			}
			__attribute__((packed));
			
			State	state	=	{};
		}
		__attribute__((aligned(alignof(typename std::aligned_storage<sizeof(State)>::type))));
		
		test_log(alignof(AAA));
		test_log(alignof(BBB_PACKED));
		test_log(alignof(CCC));
		
		test_log(sizeof(AAA));
		test_log(sizeof(BBB_PACKED));
		test_log(sizeof(CCC));
//		test_assert(sizeof(AAA) == 5);
//		test_assert(sizeof(BBB) == 6);
//		test_assert(sizeof(CCC) == 7);
	}
	
	{
		struct
		ITEM
		{
			char	a, b, c;
		};
		std::array<ITEM, 3>	a1{};
		test_log(sizeof(ITEM));
		test_log(sizeof(a1));
		test_assert(sizeof(a1) == sizeof(ITEM) * 3);
		a1.at(0).a	=	1;
		a1.at(1).a	=	1;
	}
	
	test_assert(sizeof(uint32_t) == 4);
	test_assert(sizeof(std::float_t) == 4);
	
	{
		struct
		ITEM
		{
			uint32_t		a;
		};
		std::array<ITEM, 3>	a1{};
		test_log(sizeof(ITEM));
		test_log(sizeof(a1));
		test_assert(sizeof(a1) == sizeof(ITEM) * 3);
		a1.at(0).a	=	1;
		a1.at(1).a	=	1;
	}
	
	{
		struct
		ITEM
		{
			std::float_t	a;
		};
		std::array<ITEM, 3>	a1{};
		test_log(sizeof(ITEM));
		test_log(sizeof(a1));
		test_assert(sizeof(a1) == sizeof(ITEM) * 3);
		a1.at(0).a	=	1;
		a1.at(1).a	=	1;
	}
	
	{
		struct
		ITEM
		{
			uint32_t		a;
			bool			f1, f2;
		};
		std::array<ITEM, 3>	a1{};
		test_log(sizeof(ITEM));
		test_log(sizeof(a1));
		test_assert(sizeof(a1) == sizeof(ITEM) * 3);
		a1.at(0).a	=	1;
		a1.at(1).a	=	1;
	}
	
	{
		struct
		ITEM
		{
			std::float_t	a;
			bool			f1, f2;
		};
		std::array<ITEM, 3>	a1{};
		test_log(sizeof(ITEM));
		test_log(sizeof(a1));
		test_assert(sizeof(a1) == sizeof(ITEM) * 3);
		a1.at(0).a	=	1;
		a1.at(1).a	=	1;
	}
}

inline auto
test_mem_alignment() -> void
{
	
	{
		using	ITEM1	=	MemoryStorage<bool>;
		using	ITEM2	=	MemoryStorage<uint32_t>;
		test_log(sizeof(ITEM1));
		test_log(sizeof(ITEM2));
		test_assert(sizeof(ITEM1) == 1);
		test_assert(sizeof(ITEM2) == 4);
	}
	{
		struct
		AAA
		{
			int32_t	a;
		};
		using	ITEM1	=	ObjectSlot<AAA,false>;
		using	ITEM2	=	ObjectSlot<AAA,true>;
		test_log(sizeof(AAA));
		test_log(sizeof(ITEM1));
		test_log(sizeof(ITEM2));
		test_assert(sizeof(ITEM1) == sizeof(AAA)+1);
		test_assert(sizeof(ITEM2) == aligned_size_of<aligned_size_of<AAA>() + 1>());
	}
	{
		using	ITEM1	=	ObjectSlot<uint32_t>;
		using	ITEM2	=	ListAtomSlot<uint32_t>;
		using	ITEM3	=	ListAtomSlot<uint32_t,false>;
		using	ARR		=	std::array<ListAtomSlot<uint32_t>, 3>;
		ARR	a1{};
		test_log(sizeof(ITEM1));
		test_log(sizeof(ITEM2));
		test_log(sizeof(ITEM3));
		test_log(sizeof(ARR));
		/*
		 Compiler will put extra padding to provide memory alignment.
		 This is possible because the type `T` is known at compiler time
		 on `ListAtomSlot` type.
		 */
		test_assert(sizeof(ITEM1) == aligned_size_of<sizeof(uint32_t) + sizeof(bool)>());
		test_assert(sizeof(ITEM2) == aligned_size_of<sizeof(uint32_t) + sizeof(bool) + sizeof(bool)>());
		test_assert(sizeof(ITEM3) == sizeof(uint32_t) + sizeof(bool) + sizeof(bool));
		test_assert(sizeof(a1) == ((4+2)+2) * 3);
		a1.at(0).initialize(1);
		a1.at(1).initialize(2);
		test_assert(a1.at(0).value() == 1);
		test_assert(a1.at(1).value() == 2);
		a1.at(0).terminate();
		a1.at(1).terminate();
	}
	
	{
		std::array<ListAtomSlot<std::float_t>, 3>	a1{};
		test_assert(sizeof(a1) == ((4+2)+2) * 3);
		a1.at(0).initialize(1);
		a1.at(1).initialize(2);
		test_assert(a1.at(0).value() == 1);
		test_assert(a1.at(1).value() == 2);
		a1.at(0).terminate();
		a1.at(1).terminate();
	}
	
	
	
//	std::array<ListAtomSlot<char>, 366>	a1{};
//	for (int i=0; i<366; i ++)
//	{
//		a1[i].initialize(i);
//	}
//	for (int i=0; i<366; i ++)
//	{
//		std::cout << a1[i].value() << "\n";
//	}
//	for (int i=0; i<366; i ++)
//	{
//		a1[i].terminate();
//	}
	
	
	
	
	
	
	
	
	
//	struct
//	AAA
//	{
//		char aaa[3];
//	};
//	std::array<ListAtomSlot<AAA>, 3> a2{};
//	a2.at(1).initialize();
//	auto v1 = a2.at(1).value();
//	a2.at(1).value().aaa[0] = 1;
//	a2.at(1).terminate();
//	
//	////
//	
//	StaticStableListMap<AAA, 3>	m1{};
//	m1.insert(0, {});
//	m1.insert(1, {});
//	m1.insert(2, {});
//	
//	std::cout << sizeof(m1) << "\n";
//	std::cout << uintptr_t(&m1) << "\n";
//	std::cout << uintptr_t(&m1.at(0).aaa) << "\n";
//	std::cout << uintptr_t(&m1.at(1).aaa) << "\n";
//	std::cout << uintptr_t(&m1.at(2).aaa) << "\n";
//	
//	uintptr_t	map_ptr	=	uintptr_t(&m1);
//	uintptr_t	a0_ptr	=	uintptr_t(&m1.at(0));
//	uintptr_t	a1_ptr	=	uintptr_t(&m1.at(1));
//	uintptr_t	a2_ptr	=	uintptr_t(&m1.at(2));
//	
//	uintptr_t	diff_o		=	a0_ptr - map_ptr;
//	uintptr_t	diff_0_1	=	a1_ptr - a0_ptr;
//	uintptr_t	diff_1_2	=	a2_ptr - a1_ptr;
//	
//	test_assert(diff_o % sizeof(uintptr_t) == 0);
//	test_assert(diff_0_1 % sizeof(uintptr_t) == 0);
//	test_assert(diff_1_2 % sizeof(uintptr_t) == 0);
//	
}

inline auto
raise_EXC_ARM_DA_ALIGN() -> void
{
	char mem[16];
	char* p1 = mem;
	double* p2 = (double*)(p1 + 1);
	*p2 =  10;
	
}









inline auto
test_all2() -> void
{
//	experiment_mem_alignment();
	test_mem_alignment();
}

