//
//  ApplicationController.cpp
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#include "ApplicationController.h"
#include "Platform_OSX.h"

#if	EONIL_MEDIA_ENGINE_TARGET_OSX

#import "____EonilImprovisationsMediaEngineApplicationController.h"
#import <Eonil/MediaEngine/Mathematics.h>
#import <Eonil/MediaEngine/Graphics.h>

using namespace	Eonil::MediaEngine::Mathematics::Geometry;
using namespace	Eonil::MediaEngine::Graphics::Rendering::D2014R2;

EONIL_MEDIA_ENGINE_APPLICATION_NAMESPACE_BEGIN





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
		prepare:^(____EonilImprovisationsMediaEngineMainWindowController* mwc)
		{
			/*!
			 On desktop, multisampling will be always on.
			 */
			glEnable(GL_MULTISAMPLE);
			Platform::_init(mwc);
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












EONIL_MEDIA_ENGINE_APPLICATION_NAMESPACE_END
#endif

