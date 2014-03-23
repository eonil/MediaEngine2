//
//  ApplicationController.cpp
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#include "ApplicationController.h"

#if	EONIL_MEDIA_ENGINE_TARGET_OSX










#import "____EonilImprovisationsMediaEngineApplicationController.h"
#import <Eonil/Improvisations/MediaEngine/Mathematics/Mathematics.h>
#import <Eonil/Improvisations/MediaEngine/Graphics/Graphics.h>

using namespace	Eonil::Improvisations::MediaEngine::Mathematics::Value;
using namespace	Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2;

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	
	
	
	
	auto
	run(int argc, char const *argv[], std::function<void(Stepping const&)> const& step) -> int
	{
		return
		run(argc, argv, []{}, []{}, step);
	}
	
	
	
	
	
	auto
	run(int argc, char const *argv[], PROC const& prepare, PROC const& cleanup, STEP const& step) -> int
	{	
		@autoreleasepool
		{
			return
			[____EonilImprovisationsMediaEngineApplicationController runWithArgc:argc argv:argv
			prepare:^
			{
				/*!
				 On desktop, multisampling will be always on.
				 */
				glEnable(GL_MULTISAMPLE);
				prepare();
			}
			cleanup:^
			{
				cleanup();
			}
			step:^(CGRect bounds)
			{
				Scalar	minx	{Scalar(CGRectGetMinX(bounds))};
				Scalar	maxx	{Scalar(CGRectGetMaxX(bounds))};
				Scalar	miny	{Scalar(CGRectGetMinY(bounds))};
				Scalar	maxy	{Scalar(CGRectGetMaxY(bounds))};
				
				Bounds2				b	{minx, miny, maxx, maxy};
				DisplayScreenFrame	f	{b};
				
				{
					step({f});
				}
			}];
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}}}}




















#endif

