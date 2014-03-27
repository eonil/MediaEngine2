//
//  _UIForm.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/19/13.
//
//

#include "_UIForm.h"











#include "../Stub/GL.h"


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	_DEV_
	{
		
		using namespace	Server;
		
		
		
		
		
		
		namespace
		{
			_Legacy2013_SharingBox<Program>
			MakeProgramInMachine(Server::Machine& m)
			{
				static std::string const	vsc	=
				"										\n"
				"										\n"
				"uniform	mat4	tall;				\n"
				"attribute	vec4	vlocation;			\n"
				"attribute	vec4	vcolor;				\n"
				"attribute	vec2	vmapping;			\n"
				"attribute	float	vcolor_scale;		\n"
				"attribute	float	vmapping_scale;		\n"
				"										\n"
				"varying	vec4	fcolor;				\n"
				"varying	vec2	fmapping;			\n"
				"varying	float	fcolor_scale;		\n"
				"varying	float	fmapping_scale;		\n"
				"										\n"
				"										\n"
				"void	main()							\n"
				"{										\n"
				"	vec4	p0	=	vlocation;			\n"
				"	vec4	p1	=	tall * p0; 			\n"
				"	gl_Position	=	p1;					\n"
				"										\n"
				"	fcolor				=	vcolor;						\n"
				"	fmapping			=	vmapping;					\n"
				"	fcolor_scale		=	vcolor_scale;				\n"
				"	fmapping_scale		=	vmapping_scale;				\n"
				"										\n"
				"										\n"
				"}										\n"
				;
				
				static std::string const	fsc	=
				"										\n"
				"										\n"
				"uniform sampler2D		scolor;			\n"
				"uniform sampler2D		sopacity;			\n"
				"varying highp vec4		fcolor;				\n"
				"varying highp vec2		fmapping;			\n"
				"varying highp float	fcolor_scale;		\n"
				"varying highp float	fmapping_scale;		\n"
				"										\n"
				"void	main()							\n"
				"{										\n"
				"	highp vec4	cvert	=	fcolor * fcolor_scale;								\n"
				"	highp vec4	cmap	=	texture2D(scolor, fmapping) * fmapping_scale;		\n"
				"	highp vec4  opacity	=	texture2D(sopacity, fmapping);						\n"
				"	gl_FragColor		=	(cvert + cmap) * opacity;							\n"
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
				nmap.insert(std::pair<std::string, VertexAttributeChannel const&>("vmapping", m.vertexAttributeChannelAtIndex(2)));
				nmap.insert(std::pair<std::string, VertexAttributeChannel const&>("vcolor_scale", m.vertexAttributeChannelAtIndex(3)));
				nmap.insert(std::pair<std::string, VertexAttributeChannel const&>("vmapping_scale", m.vertexAttributeChannelAtIndex(4)));
				
				return	_Legacy2013_SharingBox<Program> (new Program(VertexShader(vsc, nmap), FragmentShader(fsc1)));
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		_UIForm const
		_UIForm::Utility::boxWithColor(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector2 min, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector2 max, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector4 color)
		{
			_UIForm::Mesh	m;
			
			m.faces.push_back(Face((Vertex[3])
								   {
									   {
										   Vector4(min.x, min.y, 0, 1),
										   color,
										   Vector2(),
										   {
											   1,
											   0
										   },
									   },
									   {
										   Vector4(max.x, max.y, 0, 1),
										   color,
										   Vector2(),
										   {
											   
											   1,
											   0,
										   }
									   },
									   {
										   Vector4(min.x, max.y, 0, 1),
										   color,
										   Vector2(),
										   {
											   1,
											   0,
										   }
									   },
								   }));
			
			m.faces.push_back(Face((Vertex[3])
								   {
									   {
										   Vector4(max.x, max.y, 0, 1),
										   color,
										   Vector2(),
										   {
											   1,
											   0,
										   }
									   },
									   {
										   Vector4(min.x, min.y, 0, 1),
										   color,
										   Vector2(),
										   {
											   1,
											   0,
										   }
									   },
									   {
										   Vector4(max.x, min.y, 0, 1),
										   color,
										   Vector2(),
										   {
											   1,
											   0,
										   }
									   },
								   }));
			
			_UIForm	f;
			f.mesh	=	m;
			return	f;
		}
		
		_UIForm const
		_UIForm::Utility::boxWithTextureMapping(const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector2 min, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector2 max, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector2 minST, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Vector2 maxST)
		{
			_UIForm::Mesh	m;
			
			m.faces.push_back(Face((Vertex[3])
								   {
									   {
										   Vector4(min.x, min.y, 0, 1),
										   Vector4(),
										   Vector2(minST.x, minST.y),
										   {
											   0,
											   1
										   },
									   },
									   {
										   Vector4(max.x, max.y, 0, 1),
										   Vector4(),
										   Vector2(maxST.x, maxST.y),
										   {
											   0,
											   1
										   },
									   },
									   {
										   Vector4(min.x, max.y, 0, 1),
										   Vector4(),
										   Vector2(minST.x, maxST.y),
										   {
											   0,
											   1
										   },
									   },
								   }));
			
			m.faces.push_back(Face((Vertex[3])
								   {
									   {
										   Vector4(max.x, max.y, 0, 1),
										   Vector4(),
										   Vector2(maxST.x, maxST.y),
										   {
											   0,
											   1
										   },
									   },
									   {
										   Vector4(min.x, min.y, 0, 1),
										   Vector4(),
										   Vector2(minST.x, minST.y),
										   {
											   0,
											   1
										   },
									   },
									   {
										   Vector4(max.x, min.y, 0, 1),
										   Vector4(),
										   Vector2(maxST.x, minST.y),
										   {
											   0,
											   1
										   },
									   },
								   }));
			
			_UIForm	f;
			f.mesh	=	m;
			return	f;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		auto
		_UIForm::_makeResourceInMachine(Server::Machine& m) -> CommonResource const
		{
			CommonResource	res;
			res.program		=	MakeProgramInMachine(m);
			return	res;
		}
		
		void
		_UIForm::_renderOnMachine(Server::Machine &m, CommonResource &r, const std::vector<_UIForm> &fs, const Eonil::Improvisations::MediaEngine::Mathematics::Value::Matrix4 worldToFrameTransform)
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
			f1.dataOffset			=	sizeof(Scalar) * (4);
			f1.strideSizeInBytes	=	sizeof(Vertex);
			
			VertexAttributeChannel::Format	f2;
			f2.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
			f2.componentCount		=	VertexAttributeChannel::ComponentSize::TWO;
			f2.dataOffset			=	sizeof(Scalar) * (4+4);
			f2.strideSizeInBytes	=	sizeof(Vertex);
			
			VertexAttributeChannel::Format	f3;
			f3.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
			f3.componentCount		=	VertexAttributeChannel::ComponentSize::ONE;
			f3.dataOffset			=	sizeof(Scalar) * (4+4+2);
			f3.strideSizeInBytes	=	sizeof(Vertex);
			
			VertexAttributeChannel::Format	f4;
			f4.componentType		=	VertexAttributeChannel::ComponentType::FLOAT;
			f4.componentCount		=	VertexAttributeChannel::ComponentSize::ONE;
			f4.dataOffset			=	sizeof(Scalar) * (4+4+2+1);
			f4.strideSizeInBytes	=	sizeof(Vertex);
			
			
			////
			
			
			_Legacy2013_SharingBox<Program>	p	=	r.program;
			m.useProgram(*p);
			for (_UIForm const& f : fs)
			{
				Matrix4		tobj	=	f.transform;
				Matrix4		tall	=	worldToFrameTransform * tobj;
				
				if (f.mesh.colorTexture != nullptr)
				{
//					m.textureUnitAtIndex(0).setTexture_Legacy2013(f.mesh.colorTexture);
					m.textureUnitAtIndex(0).setTexture(*(f.mesh.colorTexture));
					p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("scolor")).setSampler(m.textureUnitAtIndex(0));
				}
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("tall")).setValue(tall);
				
				if (f.mesh.faces.size() > 0)
				{
					m.vertexAttributeChannelAtIndex(0).linkWithClientMemory(f.mesh.faces[0].scalars, f0);
					m.vertexAttributeChannelAtIndex(1).linkWithClientMemory(f.mesh.faces[0].scalars, f1);
					m.vertexAttributeChannelAtIndex(2).linkWithClientMemory(f.mesh.faces[0].scalars, f2);
					m.vertexAttributeChannelAtIndex(3).linkWithClientMemory(f.mesh.faces[0].scalars, f3);
					m.vertexAttributeChannelAtIndex(4).linkWithClientMemory(f.mesh.faces[0].scalars, f4);
					{
						m.drawArrays(DrawingMode::TRIANGLES, 0, f.mesh.faces.size() * 3);
					}
					m.vertexAttributeChannelAtIndex(0).unlink();
					m.vertexAttributeChannelAtIndex(1).unlink();
					m.vertexAttributeChannelAtIndex(2).unlink();
					m.vertexAttributeChannelAtIndex(3).unlink();
					m.vertexAttributeChannelAtIndex(4).unlink();
				}
				
				p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("tall")).unset();
				
				if (f.mesh.colorTexture != nullptr)
				{
					p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("scolor")).unset();
//					m.textureUnitAtIndex(0).unsetTexture_Legacy2013();
					m.textureUnitAtIndex(0).unsetTexture();
				}
			}
			m.unuseProgram();
		}
		
	}
	
	
	
	
	
	
	
	
}}}}


