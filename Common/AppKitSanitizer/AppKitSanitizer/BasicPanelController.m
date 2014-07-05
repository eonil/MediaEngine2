//
//  BaiscPanelController.m
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import "BasicPanelController.h"

@interface BasicPanelController ()

@end

@implementation BasicPanelController
- (id)initWithWindow:(BasicPanel *)window
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(window, BasicPanel);
	}
	
	////
	
	return	[super initWithWindow:window];
}
- (BasicPanel *)window
{
	return	(id)[super window];
}
- (void)setWindow:(BasicPanel *)window
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{		
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(window, BasicPanel);
	}
	
	////
	
	[super setWindow:window];
}

@end













