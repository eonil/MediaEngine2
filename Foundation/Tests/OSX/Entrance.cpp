//
//  Entrance.cpp
//  Foundation
//
//  Created by Hoon H. on 2/5/14.
//
//

#include "Entrance.h"

#include "Foundation.h"

#include <Eonil/Improvisations/Test/TestHelperMacros.h>

using namespace	Eonil::Improvisations::Test;
using namespace	Eonil::Improvisations::MediaEngine::Foundation;
using namespace	Eonil::Improvisations::MediaEngine::Foundation::D2014R1;

struct
AAA
{
	int8_t	aaa{};
	int8_t	bbb{};
	int16_t	ccc{};
};

int main(int argc, const char * argv[])
{
	{
		uint8_t*	bs	=	new uint8_t[8]();
		GenericMemoryRange<uint8_t>	b1{bs, 8};
		
		b1.at(1)	=	11;
		b1.at(2)	=	22;
		b1.at(3)	=	33;
		
		EONIL_TEST_ASSERT(b1.size() == 8);
		EONIL_TEST_ASSERT(bs[0] == 0);
		EONIL_TEST_ASSERT(bs[1] == 11);
		EONIL_TEST_ASSERT(bs[2] == 22);
		EONIL_TEST_ASSERT(bs[3] == 33);
		
		GenericMemoryRange<uint8_t>	b2{b1};
		EONIL_TEST_ASSERT(b2.at(3) == 33);
		
		GenericMemoryRange<void>	u3	=	b2.reinterpretAs<void>();
		EONIL_TEST_ASSERT(not u3.empty());
		
		GenericMemoryRange<int16_t>	i4	=	u3.reinterpretAs<int16_t>();
		EONIL_TEST_ASSERT(i4.at(0) == (11 << 8) or i4.at(0) == (11 << 0));
		EONIL_TEST_ASSERT(i4.at(1) == ((22 << 8) + 33) or i4.at(1) == ((33 << 8) + 22));
		
		for (auto const& a: b1)
		{
			std::cout << std::to_string(a) + "\n";
		}
		for (auto const& a: i4)
		{
			std::cout << std::to_string(a) + "\n";
		}
		
		GenericMemoryRange<AAA>	a5	=	i4.reinterpretAs<AAA>();
		EONIL_TEST_ASSERT(a5.at(0).aaa == 0);
		EONIL_TEST_ASSERT(a5.at(0).bbb == 11);
		EONIL_TEST_ASSERT(a5.at(0).ccc == ((22 << 8) + 33) or i4.at(1) == ((33 << 8) + 22));
		
		delete[]	bs;
	}
	
	
	
	
	{
		struct
		T1 : public TrackableObject
		{
		};
		{
			ptr<T1>	p1		{nullptr};
			ptr<T1>	p2		{nullptr};
			
			EONIL_TEST_ASSERT(p1 == p2);
		}
		{
			T1*		p0	=	new T1();
			{
				ptr<T1>	p1		{p0};
				ptr<T1>	p2		{nullptr};
				
				EONIL_TEST_ASSERT(p1 != p2);
			}
			delete	p0;
		}
		{
			GenericMemoryRange<int>	r1	{nullptr, nullptr};
		}
		{
			vec<int>	v1	=	{1,2,3,4};
			GenericMemoryRange<int>	r1	{v1.data(), v1.size()};
		}
	}
	
	// insert code here...
	std::cout << "Hello, World!\n";
    return 0;
}




