//
//  Stepping.h
//  Application
//
//  Created by Hoon H. on 2/23/14.
//
//

#ifndef __Application__Stepping__
#define __Application__Stepping__

#include <Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>
#include <Eonil/Improvisations/MediaEngine/Graphics/Graphics.h>

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	
	
	
	
	using namespace	Eonil::Improvisations::MediaEngine::Foundation;
	using namespace	Eonil::Improvisations::MediaEngine::Graphics;
	using namespace	Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2;
	
	
	
	
	struct
	Platform;
	
	
	/*!
	 You can access all the contextual informations via this object.
	 */
	class
	Stepping
	{
		DisplayScreenFrame const*	_frame	{nullptr};
		
	public:
		Stepping() = delete;
		Stepping(DisplayScreenFrame const& frame);
		
		auto	frame() const -> DisplayScreenFrame const&;
	};
	
	
	
	
	
	
	
}}}}


#endif /* defined(__Application__Stepping__) */
