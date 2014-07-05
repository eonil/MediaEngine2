//
//  main.m
//  OSX Test Runner 2
//
//  Created by Hoon H. on 3/22/14.
//
//

#include "run.h"
#include "TestRendering1.h"
#include "TestRendering2.h"

int main(int argc, const char * argv[])
{
	using namespace	Eonil::MediaEngine::Application;
	
	Eonil::MediaEngine::Application::run<TestRendering2>(argc, argv);
}

