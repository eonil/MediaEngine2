//
//  FigureDrawer.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/17/13.
//
//

#ifndef __EonilGraphics__FigureDrawer__
#define __EonilGraphics__FigureDrawer__

#include "Camera.h"
#include "../Form/Figure.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
	
	using namespace	Form;
	
	/*!
	 @classdesign
	 `FigureDrawer` instantiates its own shader program for each instances.
	 Unlike resources, this doesn't share underlying shader program implicitly.
	 
	 So do not instantiate multiple drawer instances for same shaders.
	 
	 @note
	 No implicit sharing because I am not sure on optimization of shader programs.
	 Can parameter static compile improve performance? How's memory consumption?
	 If GPU driver perform those optimizations implicitly? There are too many things
	 to consider, so it needs profiling. Currently, it's really unpredictable.
	 */
	class
	FigureDrawer
	{
	public:
		FigureDrawer();
		
		void		drawFigureUsingCamera(Figure const figure, Camera const camera) const;
		
	private:
		_Legacy2013_SharingBox<Program>		_p;			//	Dedicated shader for figure drawing.
	};
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__FigureDrawer__) */
