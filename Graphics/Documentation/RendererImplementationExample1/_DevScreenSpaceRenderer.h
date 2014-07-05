//
//  _DevScreenSpaceRenderer.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/15/13.
//
//

#ifndef __EonilGraphics___DevScreenSpaceRenderer__
#define __EonilGraphics___DevScreenSpaceRenderer__


#include "../Common.h"

#include "_Regulator.h"
#include "_ScreenSpaceMeshForm.h"
#include "_LineMeshForm.h"


EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

	namespace
	_DEV_
	{
		/*!
		 A very simple wrapper renderer to test rendering features.
		 As the feature stabilizes, it will move into production renderer.
		 */
		struct
		_DevScreenSpaceRenderer
		{
			struct
			Scene
			{
				_Regulator						viewport;
				std::vector<_ScreenSpaceMeshForm>	triangles;
				std::vector<_LineMeshForm>			lines;
			};
			
			void
			render(Scene const scene);
		};
	}
	
	
	
	
	
	
	
	
}}}}


#endif /* defined(__EonilGraphics___DevScreenSpaceRenderer__) */
