//
//  TestTrackingPointerSlot.cpp
//  Testers
//
//  Created by Hoon H. on 2/9/14.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#include "TestTrackingPointerSlot.h"
using namespace Eonil::MediaEngine::Foundation;


struct
Foo1 : public TrackableObject
{
	str	field1	=	"FIELD!VALUE!";
};



/*!
 None of these test blocks must crash program.
 */
static inline void
_happy_cases()
{
	{
		ptr<Foo1>	f1{nullptr};
	}
	{
		Foo1*		f1	=	new Foo1();
		{
			ptr<Foo1>	f2(f1);
		}
		delete		f1;
	}
	
}





/*!
 All the test blocks must crash program.
 */
static inline void
_evil_cases()
{
	{
		Foo1*		f1	=	new Foo1();
		ptr<Foo1>	f2	=	ptr<Foo1>(f1);
		delete		f1;
	}
}








void
TestTrackingPointerSlot()
{
	_happy_cases();
	//	_evil_cases();
}
