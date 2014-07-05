//
//  UniverseLayoutFactory.m
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import "UniverseLayoutFactory.h"
#import "UniverseViewHierarchyQuery.h"

//@implementation UniverseLayoutArray
//+ (id)alloc
//{
//}
//@end

@implementation UniverseLayoutFactory
+ (NSArray *)layoutSubview:(NSView *)subview toFillSuperview:(NSView *)superview
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(subview, NSView);
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(superview, NSView);
		UNIVERSE_DEBUG_ASSERT([UniverseViewHierarchyQuery isSubview:subview ofSuperview:superview]);
		UNIVERSE_DEBUG_ASSERT_WITH_MESSAGE([subview translatesAutoresizingMaskIntoConstraints] == NO, @"The property `translatesAutoresizingMaskIntoConstraints` MUST be turned OFF to utilize auto-layout correctly without any problem.");	//	Users must turn this off explicitly.
	}
	
	////
	
	NSLayoutConstraint*	c1	=	[NSLayoutConstraint constraintWithItem:superview attribute:(NSLayoutAttributeWidth) relatedBy:(NSLayoutRelationEqual) toItem:subview attribute:(NSLayoutAttributeWidth) multiplier:1 constant:0];
	NSLayoutConstraint*	c2	=	[NSLayoutConstraint constraintWithItem:superview attribute:(NSLayoutAttributeHeight) relatedBy:(NSLayoutRelationEqual) toItem:subview attribute:(NSLayoutAttributeHeight) multiplier:1 constant:0];
	NSLayoutConstraint*	c3	=	[NSLayoutConstraint constraintWithItem:superview attribute:(NSLayoutAttributeCenterX) relatedBy:(NSLayoutRelationEqual) toItem:subview attribute:(NSLayoutAttributeCenterX) multiplier:1 constant:0];
	NSLayoutConstraint*	c4	=	[NSLayoutConstraint constraintWithItem:superview attribute:(NSLayoutAttributeCenterY) relatedBy:(NSLayoutRelationEqual) toItem:subview attribute:(NSLayoutAttributeCenterY) multiplier:1 constant:0];
	NSArray*			cs	=	@[c1, c2, c3, c4];
	
	return	cs;
}
+ (void)makeSubview:(NSView *)subview toFillSuperview:(NSView *)superview
{
	[superview addConstraints:[self layoutSubview:subview toFillSuperview:superview]];
}
+ (NSArray *)layoutSubview:(NSView *)subview toFillSuperview:(NSView *)superview withTopDisplacement:(CGFloat)topDisplacement bottomDisplacement:(CGFloat)bottomDisplacement
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(subview, NSView);
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(superview, NSView);
		UNIVERSE_DEBUG_ASSERT([UniverseViewHierarchyQuery isSubview:subview ofSuperview:superview]);
		UNIVERSE_DEBUG_ASSERT_WITH_MESSAGE([subview translatesAutoresizingMaskIntoConstraints] == NO, @"The property `translatesAutoresizingMaskIntoConstraints` MUST be turned OFF to utilize auto-layout correctly without any problem.");	//	Users must turn this off explicitly.
	}
	
	////
	
	NSLayoutConstraint*	c1	=	[NSLayoutConstraint constraintWithItem:superview attribute:(NSLayoutAttributeTop) relatedBy:(NSLayoutRelationEqual) toItem:subview attribute:(NSLayoutAttributeTop) multiplier:1 constant:topDisplacement];
	NSLayoutConstraint*	c2	=	[NSLayoutConstraint constraintWithItem:superview attribute:(NSLayoutAttributeBottom) relatedBy:(NSLayoutRelationEqual) toItem:subview attribute:(NSLayoutAttributeBottom) multiplier:1 constant:bottomDisplacement];
	NSLayoutConstraint*	c3	=	[NSLayoutConstraint constraintWithItem:superview attribute:(NSLayoutAttributeLeft) relatedBy:(NSLayoutRelationEqual) toItem:subview attribute:(NSLayoutAttributeLeft) multiplier:1 constant:0];
	NSLayoutConstraint*	c4	=	[NSLayoutConstraint constraintWithItem:superview attribute:(NSLayoutAttributeRight) relatedBy:(NSLayoutRelationEqual) toItem:subview attribute:(NSLayoutAttributeRight) multiplier:1 constant:0];
	NSArray*			cs	=	@[c1, c2, c3, c4];
	
	return	cs;
}
+ (void)makeSubview:(NSView *)subview toFillSuperview:(NSView *)superview withTopDisplacement:(CGFloat)topDisplacement bottomDisplacement:(CGFloat)bottomDisplacement
{
	[superview addConstraints:[self layoutSubview:subview toFillSuperview:superview withTopDisplacement:topDisplacement bottomDisplacement:bottomDisplacement]];
}
@end





@implementation UniverseLayoutFactory (Deprecation)
+ (NSArray *)layoutSubview:(NSView *)subview toFillSuperview:(NSView *)superview withTopDisplacement:(CGFloat)topDisplacement
{
	return	[self layoutSubview:subview toFillSuperview:superview withTopDisplacement:topDisplacement bottomDisplacement:0];
}
+ (void)makeSubview:(NSView *)subview toFillSuperview:(NSView *)superview withTopDisplacement:(CGFloat)topDisplacement
{
	[self makeSubview:subview toFillSuperview:superview withTopDisplacement:topDisplacement bottomDisplacement:0];
}
@end










