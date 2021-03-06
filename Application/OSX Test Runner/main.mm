//
//  main.m
//  OSX Test Runner
//
//  Created by Hoon H. on 2/21/14.
//
//

#include "run.h"
#include "TestRendering1.h"

int main(int argc, char const* argv[])
{
	using namespace	Eonil::MediaEngine::Application;

	TestRendering1	r1{};
	
	STEP	step	=	[&r1](Stepping const& s)
	{
		r1.step(s);
		r1.render(s);
	};
	
	Eonil::MediaEngine::Application::run(argc, argv, step);
}
