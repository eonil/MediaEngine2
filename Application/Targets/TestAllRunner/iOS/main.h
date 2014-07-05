//
//  main.h
//  Application
//
//  Created by Hoon H. on 2014/05/18.
//
//

#include "run.h"
#include "TestAll.h"

int main(int argc, const char * argv[])
{
	using namespace	Eonil::MediaEngine::Application;
	
	Eonil::MediaEngine::Application::run<TestAll>(argc, argv);
}

