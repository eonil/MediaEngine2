//
//  _TriangleListMeshForm.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/30/13.
//
//

#include "_TriangleListMeshForm.h"

#include "_LineMeshForm.h"

#include "../Stub/GL.h"


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	_DEV_
	{
		
		using namespace	Server;
		
		
		
		
		
		
		
		
		
		_TriangleListMeshForm const
		_TriangleListMeshForm::Utility::box2D(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector2 min, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector2 max, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Vector4 color)
		{
			_TriangleListMeshForm	m;
			
			m.faces.push_back(Face((Vertex[3])
			{
				{
					Vector4(min.x, min.y, 0, 1),
					color,
					Vector2(0, 0),
				},
				{
					Vector4(max.x, max.y, 0, 1),
					color,
					Vector2(1, 1),
				},
				{
					Vector4(min.x, max.y, 0, 1),
					color,
					Vector2(0, 1),
				},
			}));
			
			m.faces.push_back(Face((Vertex[3])
			{
				{
					Vector4(max.x, max.y, 0, 1),
					color,
					Vector2(1, 1),
				},
				{
					Vector4(min.x, min.y, 0, 1),
					color,
					Vector2(0, 0),
				},
				{
					Vector4(max.x, min.y, 0, 1),
					color,
					Vector2(1, 0),
				},
			}));
			
			return	m;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		_Legacy2013_SharingBox<Program>
		_TriangleListMeshForm::_makeShadingProgramInMachine(Machine& m)
		{
			static std::string const	vsc	=
			"										\n"
			"										\n"
			"uniform	mat4	tall;										\n"
			"attribute	vec4	vlocation;										\n"
			"attribute	vec4	vcolor;										\n"
			"attribute	vec2	vmapping;			\n"
			"										\n"
			"varying	vec4	fcolor;				\n"
			"varying	vec2	fmapping;			\n"
			"										\n"
			"										\n"
			"void	main()							\n"
			"{										\n"
			"	vec4	p0	=	vlocation;			\n"
			"	vec4	p1	=	tall * p0; 			\n"
			"										\n"
			"	fcolor		=	vcolor;				\n"
			"	fmapping	=	vmapping;			\n"
			"	gl_Position	=	p1;					\n"
			"										\n"
			"}										\n"
			;
			
			
			static std::string const	fsc	=
			"										\n"
			"										\n"
			"uniform sampler2D		scolor;			\n"
			"varying highp vec4		fcolor;			\n"
			"varying highp vec2		fmapping;		\n"
			"										\n"
			"void	main()							\n"
			"{										\n"
			"	highp vec4	c	=	texture2D(scolor,fmapping);		\n"
			"	c.x				*=	fcolor.x;						\n"
			"	c.y				*=	fcolor.y;						\n"
			"	c.z				*=	fcolor.z;						\n"
			"	c.w				*=	fcolor.w;						\n"
			"	gl_FragColor	=	c;				\n"
			"	gl_FragColor	=	fcolor;			\n"
			"										\n"
			"										\n"
			"}										\n"
			"										\n"
			"										\n"
			"										\n"
			;
			
			std::string const	fsc1	=	Debugging::Doctor::doesPlatformSupportShaderPrecision() ? fsc : Program::Utility::shaderCodeForLegacyPlatformsWhichDoNotSupportPrecision(fsc);
			
			
			VertexShader::NameChannelMap	nmap;
			nmap.insert(std::pair<std::string, VertexAttributeChannel const&>("vlocation", m.vertexAttributeChannelAtIndex(0)));
			nmap.insert(std::pair<std::string, VertexAttributeChannel const&>("vcolor", m.vertexAttributeChannelAtIndex(1)));
			return	_Legacy2013_SharingBox<Program>(new Program(VertexShader(vsc, nmap), FragmentShader(fsc1)));
		}
		
		void
		_TriangleListMeshForm::_renderOnMachine(Server::Machine &m, Server::_Legacy2013_SharingBox<Server::Program> &p, const std::vector<_TriangleListMeshForm> &fs, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Matrix4 worldToFrameTransform)
		{
			using namespace Stub;
			using namespace Server::Machinery;
			
			VertexAttributeChannel::Format	f0;
			f0.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
			f0.componentCount		=	VertexAttributeChannel::ComponentSize::FOUR;
			f0.dataOffset			=	0;
			f0.strideSizeInBytes	=	sizeof(Vertex);
			
			VertexAttributeChannel::Format	f1;
			f1.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
			f1.componentCount		=	VertexAttributeChannel::ComponentSize::FOUR;
			f1.dataOffset			=	sizeof(Vector4);
			f1.strideSizeInBytes	=	sizeof(Vertex);
			
			VertexAttributeChannel::Format	f2;
			f2.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
			f2.componentCount		=	VertexAttributeChannel::ComponentSize::TWO;
			f2.dataOffset			=	sizeof(Vector4) * 2;
			f2.strideSizeInBytes	=	sizeof(Vertex);

			//	Draw screen overlays.
			m.useProgram(*p);
			for (_TriangleListMeshForm const& f : fs)
			{					
				Matrix4		tobj	=	f.transform;
				Matrix4		tall	=	worldToFrameTransform * tobj;
				
				if (f.colorTexture != nullptr)
				{
					m.textureUnitAtIndex(0).setTexture(*(f.colorTexture));
//					m.textureUnitAtIndex(0).setTexture_Legacy2013(f.colorTexture);
				}
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("scolor")).setSampler(m.textureUnitAtIndex(0));
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("tall")).setValue(tall);
				
				if (f.faces.size() > 0)
				{
//						ArrayBuffer	vb		=	ArrayBuffer(Memory::Factory::memoryByCopyingRange(f.faces[0].scalars, sizeof(Face) * f.faces.size()));
//						m.vertexAttributeChannelAtIndex(0).linkWithServerBuffer(vb, f0);
//						m.vertexAttributeChannelAtIndex(1).linkWithServerBuffer(vb, f1);
//						m.vertexAttributeChannelAtIndex(2).linkWithServerBuffer(vb, f2);

					m.vertexAttributeChannelAtIndex(0).linkWithClientMemory(f.faces[0].scalars, f0);
					m.vertexAttributeChannelAtIndex(1).linkWithClientMemory(f.faces[0].scalars, f1);
					m.vertexAttributeChannelAtIndex(2).linkWithClientMemory(f.faces[0].scalars, f2);
					{
						m.drawArrays(DrawingMode::TRIANGLES, 0, f.faces.size() * 3);
					}
					m.vertexAttributeChannelAtIndex(0).unlink();
					m.vertexAttributeChannelAtIndex(1).unlink();
					m.vertexAttributeChannelAtIndex(2).unlink();
				}
				
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("tall")).unset();
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("scolor")).unset();
				if (f.colorTexture != nullptr)
				{
					m.textureUnitAtIndex(0).unsetTexture();
//					m.textureUnitAtIndex(0).unsetTexture_Legacy2013();
				}
			}
			m.unuseProgram();
		}

	}
	
	
	
	
	
	
	
	
}}}}



