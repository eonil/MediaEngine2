//
//  _ScreenSpaceMeshForm.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/19/13.
//
//

#include "_ScreenSpaceMeshForm.h"

#include "../Debugging/Doctor.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	_DEV_
	{
		using namespace	Server;
		
		
		void
		_ScreenSpaceMeshForm::addFaceTriangle(const Eonil::Improvisations::MediaEngine::Graphics::_DEV_::_ScreenSpaceMeshForm::FaceTriangle face)
		{
			vertexes.push_back(face.points[0]);
			vertexes.push_back(face.points[1]);
			vertexes.push_back(face.points[2]);
		}
		void
		_ScreenSpaceMeshForm::addBox(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector2 minimum, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector2 maximum, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector4 color)
		{
			FaceTriangle	f0	=
			{
				{
					{
						Vector4(minimum.x, minimum.y, 0, 1),
						color,
					},
					{
						Vector4(maximum.x, maximum.y, 0, 1),
						color,
					},
					{
						Vector4(minimum.x, maximum.y, 0, 1),
						color,
					},
				},
			};
			FaceTriangle	f1	=
			{
				{
					{
						Vector4(maximum.x, maximum.y, 0, 1),
						color,
					},
					{
						Vector4(minimum.x, minimum.y, 0, 1),
						color,
					},
					{
						Vector4(maximum.x, minimum.y, 0, 1),
						color,
					},
				},
			};
			
			addFaceTriangle(f0);
			addFaceTriangle(f1);
		}
		
		
		
		
		
		
		Server::_Legacy2013_SharingBox<Server::Program>
		_ScreenSpaceMeshForm::_makeShadingProgramForMachine(Server::Machine const& m)
		{
			using namespace Server;
			
//				static std::string const	vsc	=
//				"										\n"
//				"attribute	vec4	vposition;										\n"
//				"										\n"
//				"										\n"
//				"void	main()										\n"
//				"{										\n"
//				"	gl_Position	=	vposition;									\n"
//				"										\n"
//				"}										\n"
//				;
//				
//				
//				static std::string const	fsc	=
//				"										\n"
//				"void	main()										\n"
//				"{										\n"
//				"	gl_FragColor	=	vec4(0,0,1, 1);										\n"
//				"										\n"
//				"}										\n"
//				"										\n"
//				;
			
			
			
			
			
			static std::string const	vsc	=
			"										\n"
			"										\n"
			"uniform	mat4	taspect;										\n"
			"attribute	vec4	vposition;										\n"
			"attribute	vec4	vcolor;										\n"
			"										\n"
			"varying	vec4	fcolor;											\n"
			"										\n"
			"										\n"
			"void	main()										\n"
			"{										\n"
			"	vec4	p0	=	vposition;										\n"
			"	vec4	p1	=	taspect * p0; 										\n"
			"										\n"
			"	fcolor		=	vcolor;									\n"
			"	gl_Position	=	p1;									\n"
			"										\n"
			"}										\n"
			;
			
			
			static std::string const	fsc	=
			"										\n"
			"										\n"
			"										\n"
			"varying highp vec4	fcolor;				\n"
//				"varying vec4		fcolor;				\n"
			"										\n"
			"void	main()							\n"
			"{										\n"
			"	gl_FragColor	=	fcolor;			\n"
			"										\n"
			"										\n"
			"}										\n"
			"										\n"
			"										\n"
			"										\n"
			;
			
			std::string const	fsc1	=	Debugging::Doctor::doesPlatformSupportShaderPrecision() ? fsc : Program::Utility::shaderCodeForLegacyPlatformsWhichDoNotSupportPrecision(fsc);
			
			std::map<std::string, VertexAttributeChannel const&>	chmap;
			chmap.insert(std::pair<std::string, VertexAttributeChannel const&>("vposition", m.vertexAttributeChannelAtIndex(0)));
			chmap.insert(std::pair<std::string, VertexAttributeChannel const&>("vcolor", m.vertexAttributeChannelAtIndex(1)));
			
			return	new Program(VertexShader(vsc, chmap), FragmentShader(fsc1));
		}
		
		
		
		
		
		void
		_ScreenSpaceMeshForm::_drawOnMachine(Server::Machine &m, Server::_Legacy2013_SharingBox<Server::Program> &p, const std::vector<_ScreenSpaceMeshForm> &fs, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Matrix4 screenAspectRatioMatrix)
		{
			
			//	Draw screen overlays.
			m.useProgram(*p);
			p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("taspect")).setValue(screenAspectRatioMatrix);
			for (_ScreenSpaceMeshForm const& f : fs)
			{
				if (f.vertexes.size() > 0)
				{
					VertexAttributeChannel::Format	f0;
					f0.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
					f0.componentCount		=	VertexAttributeChannel::ComponentSize::FOUR;
					f0.dataOffset			=	0;
					f0.strideSizeInBytes	=	sizeof(_ScreenSpaceMeshForm::Vertex);
					
					VertexAttributeChannel::Format	f1;
					f1.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
					f1.componentCount		=	VertexAttributeChannel::ComponentSize::FOUR;
					f1.dataOffset			=	sizeof(Vector4);
					f1.strideSizeInBytes	=	sizeof(_ScreenSpaceMeshForm::Vertex);
					
					ArrayBuffer	vb			{Legacy2013SharedMemory::Factory::memoryByCopyingRange(&f.vertexes[0], sizeof(_ScreenSpaceMeshForm::Vertex) * f.vertexes.size())};
					m.vertexAttributeChannelAtIndex(0).linkWithServerBuffer(vb, f0);
					m.vertexAttributeChannelAtIndex(1).linkWithServerBuffer(vb, f1);
					{
						m.drawArrays(DrawingMode::TRIANGLES, 0, f.vertexes.size());
					}
					m.vertexAttributeChannelAtIndex(0).unlink();
					m.vertexAttributeChannelAtIndex(1).unlink();
				}
			}
			p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("taspect")).unset();
			m.unuseProgram();
		}
	}
	
	
	
	
	
	
	
	
}}}}
