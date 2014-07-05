//
//  UniversePseudoRandomNumberFactory.m
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import "UniversePseudoRandomNumberFactory.h"

@implementation UniversePseudoRandomNumberFactory
+ (CGFloat)randomFloat
{
	return	(CGFloat)(uint64_t)arc4random() / (CGFloat)RAND_MAX;
}
+ (NSColor *)randomColorWithAlpha:(CGFloat)alpha
{
	CGFloat		r1	=	[self randomFloat];
	CGFloat		g1	=	[self randomFloat];
	CGFloat		b1	=	[self randomFloat];
	CGFloat		a1	=	alpha;
	NSColor*	c1	=	[NSColor colorWithSRGBRed:r1 green:g1 blue:b1 alpha:a1];
	return		c1;
}
+ (NSColor *)randomDarkColorWithAlpha:(CGFloat)alpha
{
	CGFloat		r1	=	[self randomFloat] / 2;
	CGFloat		g1	=	[self randomFloat] / 2;
	CGFloat		b1	=	[self randomFloat] / 2;
	CGFloat		a1	=	alpha;
	NSColor*	c1	=	[NSColor colorWithSRGBRed:r1 green:g1 blue:b1 alpha:a1];
	return		c1;
}
@end
