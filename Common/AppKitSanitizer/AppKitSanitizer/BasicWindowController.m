//
//  BasicWindowController.m
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import "BasicWindowController.h"
#import "BasicDocument.h"

@interface BasicWindowController ()
@end

@implementation BasicWindowController
//- (id)init
//{
//	UNIVERSE_DELETED_METHOD();
//}
- (void)windowDidLoad
{
	UNIVERSE_DELETED_METHOD();
}
- (id)initWithWindowNibName:(NSString *)windowNibName
{
	UNIVERSE_DELETED_METHOD();
}
- (id)initWithWindowNibName:(NSString *)windowNibName owner:(id)owner
{
	UNIVERSE_DELETED_METHOD();
}
- (id)initWithWindowNibPath:(NSString *)windowNibPath owner:(id)owner
{
	UNIVERSE_DELETED_METHOD();
}
- (id)initWithWindow:(BasicWindow *)window
{
	UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(window, BasicWindow);
	
	////
	
	return	[super initWithWindow:window];
}
- (BasicWindow *)window
{
	UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE_OR_NIL([super window], BasicWindow);
	
	////
	
	return	(id)[super window];
}
- (void)setWindow:(BasicWindow *)window
{
	UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(window, BasicWindow);
	
	////
	
	[super setWindow:window];
}
- (id)document
{
	UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE_OR_NIL([super document], BasicDocument);
	
	////
	
	return	[super document];
}
- (void)setDocument:(id)document
{
	UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE_OR_NIL([super document], BasicDocument);
	
	////
	
	[super setDocument:document];
}
@end


















