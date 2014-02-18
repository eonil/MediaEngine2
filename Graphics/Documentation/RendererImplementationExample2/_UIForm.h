//
//  _UIForm.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/19/13.
//
//

#ifndef __EonilGraphics___UIForm__
#define __EonilGraphics___UIForm__



#include "../Common.h"
#include "../Server/Machine.h"
#include "../Server/Texture.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	_DEV_
	{
		using namespace	Value;
		
		/*!
		 Specialized form to draw UI stuffs.
		 Quick & dirty implementation of 3D flat mesh.
		 
		 @discussion
		 Check the transform validity if this doesn't look work.
		 */
		struct
		_UIForm
		{
			/*!
			 Final color is:
			 
			 finalColor	=	vertexColor * vertexColorIntensity + texture2D(vertexMapping) * vertexMappingIntensity
			 
			 */
		public:
			struct
			Vertex
			{
				Vector4		location;
				
				Vector4		color;
				Vector2		mapping;
				
				struct
				{
					Scalar	color;
					Scalar	mapping;
				}
				intensity;
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
			Mesh
			{
				std::vector<Face>		faces;
				Server::_Legacy2013_SharingBox<Server::PlanarTexture>	colorTexture	=	nullptr;
				Server::_Legacy2013_SharingBox<Server::PlanarTexture>	opacityTexture	=	nullptr;
			};
			
			
			
			struct
			CommonResource
			{
				Server::_Legacy2013_SharingBox<Server::Program>			program;
			};
			//				struct
			//				PerInstanceResource
			//				{
			//				};
			
			
			
			
			
			
			
			////
			
			Mesh					mesh;
			Matrix4					transform		=	Matrix4::Utility::identity();
			
			
			
			
			
		public:
			struct
			Utility
			{
				static _UIForm const		boxWithColor(Vector2 const min, Vector2 const max, Vector4 const color);
				static _UIForm const		boxWithTextureMapping(Vector2 const min, Vector2 const max, Vector2 const minMapping = Vector2(0,0), Vector2 const maxMapping = Vector2(1,1));
			};
			
			
			
			
			
			
		private:
			friend class _DevRenderer;
			friend class _Renderer_v2;
			
			static CommonResource const		_makeResourceInMachine(Server::Machine& m);
			static void						_renderOnMachine(Server::Machine& m, CommonResource& r, std::vector<_UIForm> const& fs, Matrix4 const worldToFrameTransform);
			
		};
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___UIForm__) */
