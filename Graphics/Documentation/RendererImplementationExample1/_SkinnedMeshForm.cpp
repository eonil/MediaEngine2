//
//  _SkinnedMeshForm.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/2/13.
//
//

#include "_SkinnedMeshForm.h"










#include "_LineMeshForm.h"

#include "../Stub/GL.h"


EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

	namespace
	_DEV_
	{
		
		using namespace	Server;
		
		
		
		
		_Legacy2013_SharingBox<Program>
		_SkinnedForm::_makeShadingProgramInMachine(Machine& m)
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
			nmap.insert(std::pair<std::string, VertexAttributeChannel const&>("vlocation", m.vertexAttributeChannelAtIndex(0)));
			nmap.insert(std::pair<std::string, VertexAttributeChannel const&>("vboneindexes", m.vertexAttributeChannelAtIndex(1)));
			nmap.insert(std::pair<std::string, VertexAttributeChannel const&>("vboneweights", m.vertexAttributeChannelAtIndex(2)));
			nmap.insert(std::pair<std::string, VertexAttributeChannel const&>("vmapping", m.vertexAttributeChannelAtIndex(3)));
			return	_Legacy2013_SharingBox<Program>(new Program(VertexShader(vsc, nmap), FragmentShader(fsc1)));
		}
		
		void
		_SkinnedForm::_renderOnMachine(Server::Machine &m, Server::_Legacy2013_SharingBox<Server::Program> &p, const std::vector<_SkinnedForm> &fs, const Matrix4 worldToFrameTransform)
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
			for (_SkinnedForm const& f : fs)
			{
				Matrix4		tobj			=	f.transform;
				Matrix4		tall			=	worldToFrameTransform * tobj;
//					Matrix4		tall			=	worldToFrameTransform;
				
//				m.textureUnitAtIndex(0).setTexture_Legacy2013(f.mesh.colorTexture);
				m.textureUnitAtIndex(0).setTexture(*(f.mesh.colorTexture));
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("scolor")).setSampler(m.textureUnitAtIndex(0));
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("tall")).setValue(tall);
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("tbones[0]")).setValueArray(&f.bonePalette[0], f.bonePalette.size());
				if (f.mesh.faces.size() > 0)
				{
					ArrayBuffer	vb		{Legacy2013SharedMemory::Factory::memoryByCopyingRange(f.mesh.faces[0].scalars, sizeof(Mesh::Face) * f.mesh.faces.size())};
					
					m.vertexAttributeChannelAtIndex(0).linkWithServerBuffer(vb, f0);
					m.vertexAttributeChannelAtIndex(1).linkWithServerBuffer(vb, f1);
					m.vertexAttributeChannelAtIndex(2).linkWithServerBuffer(vb, f2);
					m.vertexAttributeChannelAtIndex(3).linkWithServerBuffer(vb, f3);
					{
						m.drawArrays(DrawingMode::TRIANGLES, 0, f.mesh.faces.size() * 3);
					}
					m.vertexAttributeChannelAtIndex(0).unlink();
					m.vertexAttributeChannelAtIndex(1).unlink();
					m.vertexAttributeChannelAtIndex(2).unlink();
					m.vertexAttributeChannelAtIndex(3).unlink();
				}
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("tbones[0]")).unset();
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("tall")).unset();
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("scolor")).unset();
//				m.textureUnitAtIndex(0).unsetTexture_Legacy2013();
				m.textureUnitAtIndex(0).unsetTexture();
			}
			m.unuseProgram();
		}
		
	}
	
	
	
	
	
	
	
	
}}}}








