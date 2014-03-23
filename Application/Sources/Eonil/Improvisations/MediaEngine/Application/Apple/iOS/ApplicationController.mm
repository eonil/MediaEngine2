//
//  ApplicationController.cpp
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#include "ApplicationController.h"

#if	EONIL_MEDIA_ENGINE_TARGET_IOS

#include "Stepping.h"
#include "Platform_iOS.h"





#import "____EonilImprovisationsMediaEngineApplicationController_iOS.h"
#import <Eonil/Improvisations/MediaEngine/Mathematics/Mathematics.h>
#import <Eonil/Improvisations/MediaEngine/Graphics/Graphics.h>

using namespace	Eonil::Improvisations::MediaEngine::Mathematics::Value;
using namespace	Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2;

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	
		
	
	
	
	
	auto
	run(int argc, char const *argv[], STEP const& step) -> int
	{
		return
		run(argc, argv, []{}, []{}, step);
	}
	
	
	
	
	
	auto
	run(int argc, char const *argv[], PROC const& prepare, PROC const& cleanup, STEP const& step) -> int
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
			prepare:^(UIViewController* mvc)
			{
				Platform::_init(mvc);
				prepare();
			}
			cleanup:^()
			{
				cleanup();
				Platform::_term();
			}
			step:^(CGRect boundsInPixels)
			{
				Scalar	minx	{toEE(CGRectGetMinX(boundsInPixels))};
				Scalar	maxx	{toEE(CGRectGetMaxX(boundsInPixels))};
				Scalar	miny	{toEE(CGRectGetMinY(boundsInPixels))};
				Scalar	maxy	{toEE(CGRectGetMaxY(boundsInPixels))};
				
				Bounds2				b	{minx, miny, maxx, maxy};
				DisplayScreenFrame	f	{b};
				{
					Stepping		s	{f};
					step(s);
				}
			}];
		}
	}
	
	
	
}}}}














#endif

