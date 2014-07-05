//
//  UniverseViewFactory.m
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import "UniverseViewFactory.h"
#import "UniversePseudoRandomNumberFactory.h"

@implementation UniverseViewFactory
//+ (BasicView *)emptyView
//{
//	return	[[BasicView alloc] init];
//}
+ (BasicView *)viewWithSolidColor:(NSColor *)color
{
	CALayer*	l1	=	[[CALayer alloc] init];
	[l1 setBackgroundColor:color.CGColor];
	
	BasicView*	v1	=	[[BasicView alloc] init];
	[v1 setWantsLayer:YES];
	[v1 setLayer:l1];
	
	return	v1;
}
+ (NSTableColumn *)tableColumnWithIdentifier:(NSString*)identifier title:(NSString *)title
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(identifier, NSString);
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(title, NSString);
	}
	
	////
	
	NSTableColumn*	c1	=	[NSTableColumn instantiation];
	[c1 setIdentifier:identifier];
	[[c1 headerCell] setStringValue:title];
	return	c1;
}
+ (NSTableColumn *)smallTableColumnWithIdentifier:(NSString *)identifier title:(NSString *)title
{
	NSTableColumn*	c1	=	[self tableColumnWithIdentifier:identifier title:title];
	[[c1 dataCell] setFont:[NSFont systemFontOfSize:[NSFont smallSystemFontSize]]];
	return	c1;
}
+ (NSToolbarItem *)toolbarItemWithIdentifier:(NSString *)identifier label:(NSString *)label target:(id)target action:(SEL)action
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(identifier, NSString);
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(label, NSString);
	}
	
	////
	
	NSToolbarItem*	item1	=	[[NSToolbarItem alloc] initWithItemIdentifier:identifier];
	item1.label		=	label;
	item1.target	=	target;
	item1.action	=	action;
	return	item1;
}
@end

@implementation UniverseViewFactory (Debugging)
+ (BasicView *)viewWithRandomColorForDebugging
{
	NSColor*	c1	=	[UniversePseudoRandomNumberFactory randomColorWithAlpha:1];
	BasicView*	v1	=	[self viewWithSolidColor:c1];
	return		v1;
}
+ (BasicView *)viewWithRandomDarkColorForDebugging
{
	NSColor*	c1	=	[UniversePseudoRandomNumberFactory randomDarkColorWithAlpha:1];
	BasicView*	v1	=	[self viewWithSolidColor:c1];
	return		v1;
}
@end