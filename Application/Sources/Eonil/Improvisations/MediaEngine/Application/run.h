//
//  run.h
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#ifndef __Application__run__
#define __Application__run__

#include <Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>
#include <Eonil/Improvisations/MediaEngine/Graphics/Graphics.h>
#include "Stepping.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	using namespace	Eonil::Improvisations::MediaEngine::Foundation;
	using namespace	Eonil::Improvisations::MediaEngine::Graphics;
	using namespace	Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2;
	
	using	STEP	=	std::function<void(Stepping const&)>;
	
	
	
	
	/*!
	 Runs application loop.
	 
	 @param	step	
	 A function will be called for each frame.
	 This will be copied, so you must configure all captured variables to be safe for copying.
	 
	 @discussion
	 If you need to prepare/cleanup some stuffs, then do it before/after calling this function.
	 */
	auto
	run(int argc, char *argv[], STEP const& step) -> void;
	
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__Application__run__) */
