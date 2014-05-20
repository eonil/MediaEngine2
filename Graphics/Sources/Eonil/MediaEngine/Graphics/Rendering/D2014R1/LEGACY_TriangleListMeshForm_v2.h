//
//  _TriangleListMeshForm_v2.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/15/13.
//
//

#ifndef __EonilGraphics___TriangleListMeshForm_v2__
#define __EonilGraphics___TriangleListMeshForm_v2__




#include "../../Common.h"
#include "../../Value/Color.h"
#include "../../Server/Declarations.h"
#include "../../Server/LEGACY_Legacy2013Compat.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Rendering
	{
		namespace
		D2014R1
		{
			
			using namespace	Value;
			
			/*!
			 Quick & dirty implementation of 3D flat mesh.
			 
			 @discussion
			 Check the transform validity if this doesn't look work.
			 
			 @deprecated
			 Legacy. Do not use this class for new code.
			 */
			struct
			_TriangleListMeshForm_v2
			{
				/*!
				 Final color is:
				 
					finalColor	=	vertexColor * vertexColorIntensity + texture2D(vertexMapping) * vertexMappingIntensity
				 
				 @discussion	All the colors must be premultiplied. (rgba <- r*a, g*a, b*a, a)
					
				 */
				public:
				struct
				Vertex
				{
					Vector4		location;
					
					Vector4		color;		//!	This color must be premultiplied. That's why this is not defined as `Color` class.
					Vector2		mapping;	//!	Texel colors also must be premultiplied.
					
					struct
					{
						Scalar	color;
						Scalar	mapping;
					}
					intensity;				//!	Color scaling for each source.
				};
				struct
				Face
				{
					union
					{
						Vertex		vertexes[3];
						Scalar		scalars[(4+4+2+1+1)*3];
					};
					
					Face() = default;
					Face(Vertex const vs[3])
					{
						vertexes[0]	=	vs[0];
						vertexes[1]	=	vs[1];
						vertexes[2]	=	vs[2];
					}
				};
				
				struct
				CommonResource
				{
					Server::_Legacy2013_SharingBox<Server::Program>	program;
				};
	//				struct
	//				PerInstanceResource
	//				{
	//				};
				
				
				
				
				
				////
				
				Matrix4					transform		=	Matrix4::Utility::identity();
				std::vector<Face>		faces;
				Server::_Legacy2013_SharingBox<Server::PlanarTexture>	colorTexture;
				
				
				
				
				
				
			public:
				struct
				Utility
				{
					/*!
					 @param		color		Must be premultiplied.
					 */
					static _TriangleListMeshForm_v2 const		boxWithColor(Vector2 const min, Vector2 const max, Color const color);
					static _TriangleListMeshForm_v2 const		boxWithTextureMapping(Vector2 const min, Vector2 const max, Vector2 const minMapping = Vector2(0,0), Vector2 const maxMapping = Vector2(1,1));
				};
				
				
				
				
				
				
				private:
				friend class _DevRenderer;
				friend class _Renderer_v2;
				
				static CommonResource const		_makeResourceInMachine(Server::Machine& m);
				static void						_renderOnMachine(Server::Machine& m, CommonResource& r, std::vector<_TriangleListMeshForm_v2> const& fs, Matrix4 const worldToFrameTransform);
				
			};
			
			
			
			
			
	
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__EonilGraphics___TriangleListMeshForm_v2__) */



