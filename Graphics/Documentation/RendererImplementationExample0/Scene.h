//
//  Scene.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/3/13.
//
//

#ifndef __EonilGraphics__Scene__
#define __EonilGraphics__Scene__

#include "../Common.h"
#include "../Form/Figure.h"
#include "../Form/Cluster.h"
#include "../Form/Cloud.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	using namespace	Form;
	
	/*!
	 Represents a space captured by a camera.
	 
	 Scene is limited only to single space with a single camera.
	 If you want to present objects in multiple spaces, you have to project them into a single
	 space first by transforming them.
	 
	 -	SkinFigure
	 -	SkeletalFigure
	 
	 */
	class
	Scene
	{
	public:
		std::vector<Figure>		figures;
		std::vector<Cluster>	clusters;
		std::vector<Cloud>		clouds;
	};
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__Scene__) */
