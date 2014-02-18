//
//  AATestRendering0.h
//  EonilGraphicsRunningTester
//
//  Created by Hoon Hwangbo on 6/17/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphicsRunningTester__AATestRendering0__
#define __EonilGraphicsRunningTester__AATestRendering0__


void	TestClearScreen();

/*
 All these tests will draw one colored at different positions.
 So you should see four squares after running all the tests.
 */

void	TestRenderingWithOnlyVertexesInClientMemory();
void	TestRenderingWithOnlyVertexesInServerMemory();

void	TestRenderingWithVertexesAndIndexesInClientMemory();
void	TestRenderingWithVertexesAndIndexesInServerMemory();

#endif /* defined(__EonilGraphicsRunningTester__AATestRendering0__) */
