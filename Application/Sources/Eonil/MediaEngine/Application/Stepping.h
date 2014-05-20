//
//  Stepping.h
//  Application
//
//  Created by Hoon H. on 2/23/14.
//
//

#pragma once

#include <Eonil/MediaEngine/Foundation.h>
#include <Eonil/MediaEngine/Graphics.h>

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Application {
	
	
	
	
	
	using namespace	Eonil::Improvisations::MediaEngine::Foundation;
	using namespace	Eonil::Improvisations::MediaEngine::Graphics;
	using namespace	Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R2;
	
	
	
	
	
	
	/*!
	 Temporal environment context information.
	 You can access all the contextual informations via this object.
	 
	 @discussion
	 This is temporal object. You shouldn't store or cache this object
	 or any informations retrieved from this object.
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



