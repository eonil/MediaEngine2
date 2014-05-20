//
//  AATesterViewController.m
//  EonilGraphicsTester
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#import		"AATesterViewController.h"

#include	"AATestStatus.h"
#include 	"AATestRendering0.h"
#include 	"AATestRendering1.h"
#include	"AATestRendering2.h"

#import		<Eonil/MediaEngine/Graphics/Platform/iOS/EEGraphicsDrawableView.h>

using namespace	Eonil::Improvisations::MediaEngine::Graphics;
using namespace	Eonil::Improvisations::MediaEngine::Graphics::Stub;






@implementation AATesterViewController
{
	CADisplayLink*	_link;
	EAGLContext*	_ctx;
}
- (void)loadView
{
	[super loadView];
	
	self.view	=	[[EEGraphicsDrawableView alloc] init];
}
- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
}
- (void)viewDidAppear:(BOOL)animated
{
	[super viewDidAppear:animated];
	
	[((EEGraphicsDrawableView*)self.view) prepareGraphicsContext];
	
	_link	=	[CADisplayLink displayLinkWithTarget:self selector:@selector(displayTick:)];
	[_link addToRunLoop:[NSRunLoop mainRunLoop] forMode:NSRunLoopCommonModes];
}
- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
	
	[_link removeFromRunLoop:[NSRunLoop mainRunLoop] forMode:NSRunLoopCommonModes];
	[_link invalidate];
	_link	=	nil;
	
	[((EEGraphicsDrawableView*)self.view) cleanupGraphicsContext];
}
- (void)viewDidDisappear:(BOOL)animated
{
	[super viewDidDisappear:animated];
	
}

- (void)displayTick:(CADisplayLink*)sender
{
	{
		glEnable(GL_DEPTH_TEST);
		
		TestStatus();
		
		TestClearScreen();
		TestRenderingWithOnlyVertexesInClientMemory();
		TestRenderingWithOnlyVertexesInServerMemory();
		TestRenderingWithVertexesAndIndexesInClientMemory();
		TestRenderingWithVertexesAndIndexesInServerMemory();
		
		TestRendering1RenderingWithTransform();
		
		NSString*		fp0		=	[[NSBundle mainBundle] pathForResource:@"02" ofType:@"png"];
		PlanarTexture	tex		=	Server::PlanarTexture::Utility::textureWithContentOfFileAtPath(fp0.UTF8String);
		TestRendering2RenderingWithTexture(tex);
		
		glDisable(GL_DEPTH_TEST);
	}
		
	[((EEGraphicsDrawableView*)self.view) presentRenderbuffer];
}
@end














