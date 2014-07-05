//
//  BasicView.m
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import "BasicView.h"

@implementation BasicView
- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
	{
        // Initialization code here.
    }
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}
- (void)addConstraint:(NSLayoutConstraint *)constraint
{
	UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(constraint, NSLayoutConstraint);
	
	////
	
	[super addConstraint:constraint];
}
- (void)addConstraints:(NSArray *)constraints
{
	UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(constraints, NSArray);
	UNIVERSE_DEBUG_ASSERT_FOR_EACH_ELEMENTS_TYPE_IN_ARRAY(constraints, NSLayoutConstraint);
	
	////
	
	[super addConstraints:constraints];
}
@end
