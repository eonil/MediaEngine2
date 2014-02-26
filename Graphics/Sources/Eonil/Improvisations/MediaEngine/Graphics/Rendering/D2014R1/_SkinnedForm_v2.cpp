//
//  _SkinnedForm_v2.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/28/13.
//
//

#include "_SkinnedForm_v2.h"

#include "../../Stub/GL.h"






namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Rendering
	{
		namespace
		D2014R1
		{
			
			
			
			
			
			
			
			
			
				
			using namespace	Server;
			
			
			
			
			_Legacy2013_SharingBox<Program>
			_SkinnedForm_v2::_makeShadingProgramInMachine(Machine& m)
			{
				static std::string const	vsc	=
				"										\n"
				"										\n"
				"uniform	mat4	tall;				\n"
				"uniform	mat4	tbones[128];		\n"
				"										\n"
				"attribute	vec4	vlocation;			\n"
				"attribute	vec4	vboneindexes;		\n"
				"attribute	vec4	vboneweights;		\n"
				"attribute	vec2	vmapping;			\n"
				"										\n"
				"varying	vec2	fmapping;			\n"
				"										\n"
				"										\n"
				"void	main()							\n"
				"{										\n"
				"	vec4	p	=	vlocation;			\n"
				"													\n"
				"	p.w			=	1.0;							\n"
				"													\n"
				"	mat4	m0	=	tbones[int(vboneindexes.x)];	\n"
				"	mat4	m1	=	tbones[int(vboneindexes.y)];	\n"
				"	mat4	m2	=	tbones[int(vboneindexes.z)];	\n"
				"	mat4	m3	=	tbones[int(vboneindexes.w)];	\n"
				"													\n"
				"	vec4	p0	=	(m0 * p) * vboneweights.x;		\n"
				"	vec4	p1	=	(m1 * p) * vboneweights.y;		\n"
				"	vec4	p2	=	(m2 * p) * vboneweights.z;		\n"
				"	vec4	p3	=	(m3 * p) * vboneweights.w;		\n"
				"													\n"
				"	vec4	pa	=	p0 + p1 + p2 + p3;				\n"
				"	pa.w		=	1.0;							\n"
				"	vec4	pb	=	tall * pa; 						\n"
				"													\n"
				"	fmapping	=	vmapping;			\n"
				"	gl_Position	=	pb;					\n"
				"										\n"
				"}										\n"
				;
				
				
				static std::string const	fsc	=
				"										\n"
				"										\n"
				"uniform	sampler2D	scolor;			\n"
				"										\n"
				//				"varying	vec2		fmapping;		\n"
				"varying highp vec2		fmapping;		\n"
				"										\n"
				"void	main()							\n"
				"{										\n"
				//				"	vec4	c		=	texture2D(scolor,fmapping);		\n"
				"	highp vec4	c	=	texture2D(scolor,fmapping);		\n"
				"	gl_FragColor	=	c;				\n"
				"										\n"
				"										\n"
				"}										\n"
				"										\n"
				"										\n"
				"										\n"
				;
				
				std::string const	fsc1	=	Debugging::Doctor::doesPlatformSupportShaderPrecision() ? fsc : Program::Utility::shaderCodeForLegacyPlatformsWhichDoNotSupportPrecision(fsc);
				
				
				VertexShader::NameChannelMap	nmap;
				nmap.insert({"vlocation", &m.vertexAttributeChannelAtIndex(0)});
				nmap.insert({"vboneindexes", &m.vertexAttributeChannelAtIndex(1)});
				nmap.insert({"vboneweights", &m.vertexAttributeChannelAtIndex(2)});
				nmap.insert({"vmapping", &m.vertexAttributeChannelAtIndex(3)});
				
				return	_Legacy2013_SharingBox<Program>(new Program(VertexShader(vsc, nmap), FragmentShader(fsc1)));
			}
			
			void
			_SkinnedForm_v2::_renderOnMachine(Server::Machine &m, Server::_Legacy2013_SharingBox<Server::Program> &p, const std::vector<_SkinnedForm_v2> &fs, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 worldToFrameTransform)
			{
				using namespace Stub;
				using namespace Server::Machinery;
				
				VertexAttributeChannel::Format	f0;
				f0.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
				f0.componentCount		=	VertexAttributeChannel::ComponentSize::FOUR;
				f0.dataOffset			=	sizeof(Vector4)*0;
				f0.strideSizeInBytes	=	sizeof(Mesh::Vertex);
				
				VertexAttributeChannel::Format	f1;
				f1.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
				f1.componentCount		=	VertexAttributeChannel::ComponentSize::FOUR;
				f1.dataOffset			=	sizeof(Vector4)*1;
				f1.strideSizeInBytes	=	sizeof(Mesh::Vertex);
				
				VertexAttributeChannel::Format	f2;
				f2.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
				f2.componentCount		=	VertexAttributeChannel::ComponentSize::FOUR;
				f2.dataOffset			=	sizeof(Vector4)*2;
				f2.strideSizeInBytes	=	sizeof(Mesh::Vertex);
				
				VertexAttributeChannel::Format	f3;
				f3.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
				f3.componentCount		=	VertexAttributeChannel::ComponentSize::TWO;
				f3.dataOffset			=	sizeof(Vector4)*3;
				f3.strideSizeInBytes	=	sizeof(Mesh::Vertex);
				
				//	Draw screen overlays.
				m.useProgram(*p);
				for (_SkinnedForm_v2 const& f : fs)
				{
					Matrix4		tobj			=	f.transform;
					Matrix4		tall			=	worldToFrameTransform * tobj;
	//				Matrix4		tall			=	worldToFrameTransform;
					
					m.textureUnitAtIndex(0).setTexture(*(f.mesh->colorTexture));
					p->uniformValueSlotAtIndex(p->indexOfUniformValueSlotForName("scolor")).setSampler(m.textureUnitAtIndex(0));
					p->uniformValueSlotAtIndex(p->indexOfUniformValueSlotForName("tall")).setValue(tall);
					p->uniformValueSlotAtIndex(p->indexOfUniformValueSlotForName("tbones[0]")).setValueArray(&f.bonePalette[0], f.bonePalette.size());
					if (f.mesh->faceCount > 0)
					{
						ArrayBuffer const&	vb		=	*(f.mesh->vertexBuffer);
						m.vertexAttributeChannelAtIndex(0).linkWithServerBuffer(vb, f0);
						m.vertexAttributeChannelAtIndex(1).linkWithServerBuffer(vb, f1);
						m.vertexAttributeChannelAtIndex(2).linkWithServerBuffer(vb, f2);
						m.vertexAttributeChannelAtIndex(3).linkWithServerBuffer(vb, f3);
						{
							m.drawArrays(DrawingMode::TRIANGLES, 0, f.mesh->faceCount * 3);
						}
						m.vertexAttributeChannelAtIndex(0).unlink();
						m.vertexAttributeChannelAtIndex(1).unlink();
						m.vertexAttributeChannelAtIndex(2).unlink();
						m.vertexAttributeChannelAtIndex(3).unlink();
					}
					p->uniformValueSlotAtIndex(p->indexOfUniformValueSlotForName("tbones[0]")).unset();
					p->uniformValueSlotAtIndex(p->indexOfUniformValueSlotForName("tall")).unset();
					p->uniformValueSlotAtIndex(p->indexOfUniformValueSlotForName("scolor")).unset();
	//				m.textureUnitAtIndex(0).unsetTexture_Legacy2013();
					m.textureUnitAtIndex(0).unsetTexture();
				}
				m.unuseProgram();
			}
	
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

