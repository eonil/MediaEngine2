//
//  BasicColor.h
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import <FoundationExtras/FoundationExtras.h>

@interface BasicColor : NSColor
+ (id)allocWithZone:(struct _NSZone *)zone UNIVERSE_UNAVAILABLE_METHOD;
+ (id)copyWithZone:(struct _NSZone *)zone UNIVERSE_UNAVAILABLE_METHOD;
+ (NSColor *)colorWithRed:(CGFloat)red green:(CGFloat)green blue:(CGFloat)blue alpha:(CGFloat)alpha UNIVERSE_UNAVAILABLE_METHOD;
- (id)initWithCoder:(NSCoder *)aDecoder UNIVERSE_UNAVAILABLE_METHOD;
@end
