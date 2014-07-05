//
//  UniverseViewHierarchyQuery.m
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import "UniverseViewHierarchyQuery.h"

@implementation UniverseViewHierarchyQuery
+ (BOOL)isSubview:(NSView *)subview ofSuperview:(NSView *)superview
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(subview, NSView);
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(superview, NSView);
		UNIVERSE_DEBUG_ASSERT(subview != superview);
	}
	
	////
	
	NSView*	v1	=	subview;
	while (v1 != nil)
	{
		v1	=	v1.superview;
		
		if (v1 == superview)
		{
			return	YES;
		}
	}
	return	NO;
}
+ (BOOL)isSuperview:(NSView *)superview ofSubview:(NSView *)subview
{
	return	[self isSubview:subview ofSuperview:superview];
}
@end
