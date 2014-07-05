//
//  AppDelegate.m
//  DemonstraionTest
//
//  Created by Hoon H. on 2014/06/28.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import "AppDelegate.h"
#import <FoundationExtras/FoundationExtras.h>
#import <AppKitSanitizer/AppKitSanitizer.h>







@implementation AppDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	// Insert code here to initialize your application
	if (EONIL_DEBUG_MODE)
	{
		[[NSAlert alertWithMessageText:@"debug mode." defaultButton:@"OK" alternateButton:nil otherButton:nil informativeTextWithFormat:@""] runModal];
	}
	else
	{
		[[NSAlert alertWithMessageText:@"release mode." defaultButton:@"OK" alternateButton:nil otherButton:nil informativeTextWithFormat:@""] runModal];
	}
	
}

@end
