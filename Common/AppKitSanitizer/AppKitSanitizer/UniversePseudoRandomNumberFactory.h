//
//  UniversePseudoRandomNumberFactory.h
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import <FoundationExtras/FoundationExtras.h>

@interface UniversePseudoRandomNumberFactory : BasicObject
//+ (NSUInteger)randomUnsignedInteger;
+ (CGFloat)randomFloat;		//!	@return	0~1 range.
//+ (CGSize)randomSize;
+ (NSColor*)randomColorWithAlpha:(CGFloat)alpha;
+ (NSColor*)randomDarkColorWithAlpha:(CGFloat)alpha;
@end

typedef UniversePseudoRandomNumberFactory	UniversePRNFactory;
