//
//  UniverseViewHierarchyQuery.h
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import "BasicView.h"

@interface	UniverseViewHierarchyQuery : BasicObject
+ (BOOL)	isSubview:(NSView*)subview ofSuperview:(NSView*)superview;
+ (BOOL)	isSuperview:(NSView*)superview ofSubview:(NSView*)subview;
@end
