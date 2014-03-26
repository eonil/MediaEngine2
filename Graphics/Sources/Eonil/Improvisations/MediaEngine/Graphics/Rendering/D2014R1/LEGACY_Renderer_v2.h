//
//  _Renderer_v2.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/16/13.
//
//

#ifndef __EonilGraphics___Renderer_v2__
#define __EonilGraphics___Renderer_v2__


#include "../../Common.h"
#include "../../Server/_Legacy2013Compat.h"

#include "_Display_v1.h"
#include "_Camera_v1.h"
#include "LEGACY_LineMeshForm.h"

#include "LEGACY_TriangleListMeshForm_v2.h"
#include "LEGACY_SkinnedForm_v2.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Rendering
	{
		namespace
		D2014R1
		{
			
			using namespace	Server;
			
			/*!
			 A very simple wrapper renderer to test rendering features.
			 As the feature stabilizes, it will move into production renderer.
			 
			 @note		Unified screen-space renderer and camera-space renderer.
			 */
			struct
			_Renderer_v2
			{
				
				/*!
				 A very simple wrapper scene state to test new faetures.
				 As features gets stabiizes, it will be moved into production scenes.
				 
				 @discussion		You must specify viewport.
									If you set clipping to other than `infinity`, renderer
									set clip rendering by it.
				 */
				struct
				Scene
				{
					struct
					Blending
					{
						enum
						CODE
						{
							NONE	=	0,
							TRANSPARENCY_WITH_PREMULTIPLIED_ALPHA,
							BURNING_EFFECT_BY_ACCUMULATION,
						};
						CODE	code	=	NONE;
					};
					
					////
					
					_Display_v1							display;
					
					Bounds2								clipping	=	Bounds2::Utility::infinity();		//!	Bounds in RSS.
					
					struct
					{
						bool		depthTesting	=	false;
						Blending	blending		=	{};
					}
					switches;
					
					std::vector<_LineMeshForm>				lineMeshes;
					std::vector<_TriangleListMeshForm_v2>	triangleMeshForms2;
					std::vector<_SkinnedForm_v2>			skinnedForms_v2;
				};
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				Server::Machine&	machine;
				
				struct
				{
					_Legacy2013_SharingBox<Program>		for_LineMeshForm;
				}
				programs;
				
				
				
				
				
				_Renderer_v2();
				~_Renderer_v2();
				
				
				/*!
				 @note
				 See `Camera` class for information about *Frame Space*.
				 */
				void		renderWithWorldToFrameTransform(Scene const scene, Matrix4 const worldToFrameTransform);
				void		renderWithCamera(Scene const scene, _Camera_v1 const camera);
				void		renderWithoutCamera(Scene const scene);
				
				
				
			private:
				
				struct
				{
					_TriangleListMeshForm_v2::CommonResource		for_TriangleListMeshForm_v2;
					_Legacy2013_SharingBox<Program>					for_SkinnedForm_v2;
				}
				_cache;
				
				
			};
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__EonilGraphics___Renderer_v2__) */
