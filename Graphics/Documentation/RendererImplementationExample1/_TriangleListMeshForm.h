//
//  _TriangleListMeshForm.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/30/13.
//
//

#ifndef __EonilGraphics___TriangleListMeshForm__
#define __EonilGraphics___TriangleListMeshForm__

#include "../Common.h"
#include "../Server/Machine.h"
#include "../Server/Texture.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

	namespace
	_DEV_
	{
		using namespace	Value;
		
		/*!
		 Quick & dirty implementation of 3d flat mesh.
		 */
		struct
		_TriangleListMeshForm
		{
		public:
			struct
			Vertex
			{
				Vector4		location;
				Vector4		color;
				Vector2		mapping;
			};
			struct
			Face
			{
				union
				{
					Vertex		vertexes[3];
					Scalar		scalars[(4+4+2)*3];
				};
				
				Face() = default;
				Face(Vertex const vs[3])
				{
					vertexes[0]	=	vs[0];
					vertexes[1]	=	vs[1];
					vertexes[2]	=	vs[2];
				}
			};
			
			Matrix4					transform		=	Matrix4::Utility::identity();
			std::vector<Face>		faces;
			Server::_Legacy2013_SharingBox<Server::PlanarTexture>	colorTexture;
			
			
			
			
			
		public:
			struct
			Utility
			{
				static _TriangleListMeshForm const		box2D(Vector2 const min, Vector2 const max, Vector4 const color);
			};
			
			
			
			
			
		private:
			friend class _DevRenderer;
			friend class _Renderer_v2;
			
			static Server::_Legacy2013_SharingBox<Server::Program>	_makeShadingProgramInMachine(Server::Machine& m);
			static void						_renderOnMachine(Server::Machine& m, Server::_Legacy2013_SharingBox<Server::Program>& p, std::vector<_TriangleListMeshForm> const& fs, Matrix4 const worldToFrameTransform);

		};
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___TriangleListMeshForm__) */
