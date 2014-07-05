//
//  UniverseLayoutFactory.h
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import <FoundationExtras/FoundationExtras.h>

//@interface UniverseLayoutArray : NSArray
//+ (id)allocWithZone:(struct _NSZone *)zone UNIVERSE_UNAVAILABLE_METHOD;
//+ (id)copyWithZone:(struct _NSZone *)zone UNIVERSE_UNAVAILABLE_METHOD;
//- (id)initWithCoder:(NSCoder *)aDecoder UNIVERSE_UNAVAILABLE_METHOD;
//@end

@interface	UniverseLayoutFactory : BasicObject
/*!
 Add returned constraints to some container view.
 */
+ (NSArray*)layoutSubview:(NSView*)subview toFillSuperview:(NSView*)superview;
+ (void)	makeSubview:(NSView*)subview toFillSuperview:(NSView*)superview;

+ (NSArray*)layoutSubview:(NSView *)subview toFillSuperview:(NSView *)superview withTopDisplacement:(CGFloat)topDisplacement bottomDisplacement:(CGFloat)bottomDisplacement;
+ (void)	makeSubview:(NSView *)subview toFillSuperview:(NSView *)superview withTopDisplacement:(CGFloat)topDisplacement bottomDisplacement:(CGFloat)bottomDisplacement;
@end

@interface	UniverseLayoutFactory (Deprecation)
+ (NSArray*)layoutSubview:(NSView *)subview toFillSuperview:(NSView *)superview withTopDisplacement:(CGFloat)topDisplacement UNIVERSE_DEPRECATED_METHOD;
+ (void)	makeSubview:(NSView *)subview toFillSuperview:(NSView *)superview withTopDisplacement:(CGFloat)topDisplacement UNIVERSE_DEPRECATED_METHOD;
@end