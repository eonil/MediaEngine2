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
	using namespace	Eonil::Improvisations::MediaEngine::Application;
	
	Eonil::Improvisations::MediaEngine::Application::run<TestAll>(argc, argv);
}

