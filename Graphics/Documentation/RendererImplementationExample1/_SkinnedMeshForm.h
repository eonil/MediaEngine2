//
//  _SkinnedMeshForm.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/2/13.
//
//

#ifndef __EonilGraphics___SkinnedMeshForm__
#define __EonilGraphics___SkinnedMeshForm__


#include "../Common.h"
#include "../Server/Machine.h"
#include "../Server/Texture.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	_DEV_
	{
		using namespace	Value;
		
		
		
		
		
		
		/*!
		 Quick & dirty implementation of 3D flat mesh.
		 */
		struct
		_SkinnedForm
		{
			struct
			Mesh
			{
				struct
				Vertex
				{
					Vector4		location;
					
					Vector4		boneIndexes;
					Vector4		boneWeights;
					
					Vector2		mapping;
				}
				__attribute__((__packed__));
				static_assert(sizeof(Vertex) == 4 * (4+4+4+2), "");
				
				struct
				Face
				{
					union
					{
						Vertex		vertexes[3];
						Scalar		scalars[(4+4+4+2)*3];
					};
				}
				__attribute__((__packed__));
				static_assert(sizeof(Face) == 3 * 4 * (4+4+4+2), "");
				
				std::vector<Face>		faces;
				Server::_Legacy2013_SharingBox<Server::PlanarTexture>	colorTexture;
			};
			
			
		public:
			Mesh					mesh;
			std::vector<Matrix4>	bonePalette;
			Matrix4					transform;
			
		private:
			friend class _DevRenderer;
			friend class _Renderer_v2;
			
			static Server::_Legacy2013_SharingBox<Server::Program> _makeShadingProgramInMachine(Server::Machine& m);
			static void					_renderOnMachine(Server::Machine& m, Server::_Legacy2013_SharingBox<Server::Program>& p, std::vector<_SkinnedForm> const& fs, Matrix4 const worldToFrameTransform);
			
		};
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___SkinnedMeshForm__) */











