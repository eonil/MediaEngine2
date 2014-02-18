//
//  main.m
//  EonilGraphicsTester
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "AATest.h"
#import "AAAppDelegate.h"

#include <Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>

int main(int argc, char *argv[])
{
//	Eonil::Improvisations::MediaEngine::Foundation::Debugging::Doctor::limitMaximumStackSize(1024 * 64);
	
	
	TestVector();
	TestMatrix();
	
	
	@autoreleasepool
	{
		return UIApplicationMain(argc, argv, nil, NSStringFromClass([AAAppDelegate class]));
	}
}
