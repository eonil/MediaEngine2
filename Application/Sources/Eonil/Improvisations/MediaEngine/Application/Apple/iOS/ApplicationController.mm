//
//  ApplicationController.cpp
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#include "ApplicationController.h"

#if	EONIL_MEDIA_ENGINE_TARGET_IOS






#import "____EonilImprovisationsMediaEngineApplicationController_iOS.h"
#import <Eonil/Improvisations/MediaEngine/Mathematics/Mathematics.h>
#import <Eonil/Improvisations/MediaEngine/Graphics/Graphics.h>

using namespace	Eonil::Improvisations::MediaEngine::Mathematics::Value;
using namespace	Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2;

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	
	
	
	
	auto
	run(int argc, char *argv[], std::function<void(Stepping const&)> const& step) -> int
	{
		return
		run(argc, argv, []{}, []{}, step);
	}
	
	
	
	
	
	auto
	run(int argc, char *argv[], PROC const& prepare, PROC const& cleanup, STEP const& step) -> int
	{
		auto	toEE	=	[](CGFloat f) -> Scalar
		{
			return	(Scalar)f;
		};
		
		////
		
		@autoreleasepool
		{
			return
			[____EonilImprovisationsMediaEngineApplicationController_iOS runWithArgc:argc argv:argv
			prepare:^
			{
				prepare();
			}
			cleanup:^
			{
				cleanup();
			}
			step:^(CGRect bounds)
			{
				Scalar	minx	{toEE(CGRectGetMinX(bounds))};
				Scalar	maxx	{toEE(CGRectGetMaxX(bounds))};
				Scalar	miny	{toEE(CGRectGetMinY(bounds))};
				Scalar	maxy	{toEE(CGRectGetMaxY(bounds))};
				
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

