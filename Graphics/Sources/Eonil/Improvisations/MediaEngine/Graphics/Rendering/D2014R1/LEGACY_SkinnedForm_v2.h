//
//  _SkinnedForm_v2.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/28/13.
//
//

#ifndef __EonilGraphics___SkinnedForm_v2__
#define __EonilGraphics___SkinnedForm_v2__




#include "../../Common.h"
#include "../../Server/Declarations.h"
#include "../../Server/_Legacy2013Compat.h"




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
			 
			 @deprecated
			 Legacy. Do not use this class for new code.
			 */
			struct
			_SkinnedForm_v2
			{
				struct
				Mesh
				{
					using	Ref	=	std::shared_ptr<Mesh const>;
					
					struct
					Vertex
					{
						Vector4		location;
						
						Vector4		boneIndexes;
						Vector4		boneWeights;
						
						Vector2		mapping;
	//					Vector2		empty;
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
					
					Server::_Legacy2013_SharingBox<Server::ArrayBuffer>		vertexBuffer;
					Size					faceCount;
					
					Server::_Legacy2013_SharingBox<Server::PlanarTexture>	colorTexture;
				};
				
				
			public:
				Mesh::Ref				mesh;
				std::vector<Matrix4>	bonePalette;
				Matrix4					transform;
				
			private:
				friend class _DevRenderer;
				friend class _Renderer_v2;
				
				static Server::_Legacy2013_SharingBox<Server::Program>	_makeShadingProgramInMachine(Server::Machine& m);
				static void						_renderOnMachine(Server::Machine& m, Server::_Legacy2013_SharingBox<Server::Program>& p, std::vector<_SkinnedForm_v2> const& fs, Matrix4 const worldToFrameTransform);
				
			};
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__EonilGraphics___SkinnedForm_v2__) */
