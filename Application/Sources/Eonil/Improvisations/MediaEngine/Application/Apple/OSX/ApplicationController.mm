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
	run(int argc, char *argv[], std::function<void(Stepping const&)> const& step) -> void
	{
		char const* * argv2	=	(char const* *)argv;
		
		[____EonilImprovisationsMediaEngineApplicationController runWithArgc:argc argv:argv2 step:^(CGRect bounds)
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

//			Graphics::Rendering::D2014R2::DisplayScreenFrame	f{};
//			step({});
		}];
	}
	
	
	
	
	
}}}}




















#endif

