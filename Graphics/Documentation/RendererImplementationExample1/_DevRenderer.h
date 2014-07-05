//
//  _DevRenderer.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/19/13.
//
//

#ifndef __EonilGraphics___DevRenderer__
#define __EonilGraphics___DevRenderer__


#include "../Common.h"
#include "../Rendering/Scene.h"
#include "../Rendering/Renderer.h"

#include "_Regulator.h"
#include "_DevCamera.h"
#include "_LineMeshForm.h"
#include "_TriangleListMeshForm.h"
#include "_SkinnedMeshForm.h"
#include "_TriangleListMeshForm_v2.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
	
	namespace
	_DEV_
	{
		/*!
		 A very simple wrapper renderer to test rendering features.
		 As the feature stabilizes, it will move into production renderer.
		 */
		struct
		_DevRenderer
		{
			
			/*!
			 A very simple wrapper scene state to test new faetures.
			 As features gets stabiizes, it will be moved into production scenes.
			 
			 @discussion
			 You must specify viewport.
			 */
			struct
			_DevScene
			{					
				Scene			productionScene;
				
				/*
				 Experimentals.
				 */
				_Regulator							viewport;
				_DevCamera							camera;
				
				struct
				{
					bool		depthTesting	=	false;
				}
				switches;
				
				vec<_LineMeshForm>				lineMeshes;
				vec<_TriangleListMeshForm>		triangleMeshForms;
				vec<_SkinnedForm>				skinnedForms;
				vec<_TriangleListMeshForm_v2>	triangleMeshForms2;
			};
			
			
			
			
			
			Renderer	productionRenderer;
			
			void
			render(_DevScene const scene);
		};
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___DevRenderer__) */
