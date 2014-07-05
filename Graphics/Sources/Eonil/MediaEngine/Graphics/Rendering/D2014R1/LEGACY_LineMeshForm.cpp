//
//  _LineMeshForm.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/26/13.
//
//

#include "LEGACY_LineMeshForm.h"

#include "../../Stub/GL.h"

#include "../../Server/Machine.h"
#include "../../Server/Shader.h"
#include "../../Server/Program.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
	
	namespace
	Rendering
	{
		namespace
		D2014R1
		{
			
			
			
			
			
			
			
			
			
			
			
			
			
				
			using namespace Server;
			
			std::vector<_LineMeshForm::Line> const&
			_LineMeshForm::lines() const
			{
				return	_ls;
			}
			Matrix4 const
			_LineMeshForm::transform() const
			{
				return	_tm;
			}
			
			
			
			
			_LineMeshForm const
			_LineMeshForm::lineMeshWithTransform(const Matrix4 m) const
			{
				_LineMeshForm	f1;
				for (Line l : lines())
				{
					Vertex	v0, v1;
					v0.location	=	m.transform(l.from.location);
					v0.color	=	l.from.color;
					
					v1.location	=	m.transform(l.to.location);
					v1.color	=	l.to.color;
					
					Line	l1;
					l1.from		=	v0;
					l1.to		=	v1;
					
					f1.addLine(l1);
				}
				return	f1;
			}
			
			
			
			void
			_LineMeshForm::setTransform(const Matrix4 m)
			{
				_tm	=	m;
			}
			void
			_LineMeshForm::addLine(const Rendering::D2014R1::_LineMeshForm::Line l)
			{
				_ls.push_back(l);
			}
			void
			_LineMeshForm::addLine(const Vector4 from, const Vector4 to, const Vector4 color)
			{
				Line	l;
				l.from.location	=	from;
				l.from.color	=	color;
				l.to.location	=	to;
				l.to.color		=	color;
				addLine(l);
			}
			void
			_LineMeshForm::addLines(const std::vector<Line> lines)
			{
				for (Line const& l : lines)
				{
					addLine(l);
				}
			}
			
			
			
			
			
			
			
			
			
			
			
			_LineMeshForm const
			_LineMeshForm::Utility::quadraticGrid(const Size halfWidth, const Size halfHeight, const Scalar unitLength, const Vector4 centerColor, const Vector4 borderColor, const Vector4 otherColor)
			{
				return	cubicGrid(halfWidth, halfHeight, 0, unitLength, centerColor, borderColor, otherColor);
			}
			_LineMeshForm const
			_LineMeshForm::Utility::cubicGrid(const Size halfWidth, const Size halfHeight, const Size halfDepth, const Scalar unitLength, const Vector4 centerColor, const Vector4 borderColor, const Vector4 otherColor)
			{
				EEGL_ASSERT(isnormal(unitLength));
				EEGL_ASSERT(unitLength >= 0.0f);
				
				_LineMeshForm	f;
				
				Scalar	hWLen	=	halfWidth * unitLength;
				Scalar	hHLen	=	halfHeight * unitLength;
				Scalar	hDLen	=	halfDepth * unitLength;
				
				//	Filling lines.
				for (Size z=0; z<=halfDepth; z++)
				{
					for (Size x=1; x<halfWidth; x++)
					{
						f.addLine(Vector4(-unitLength*x,-hHLen,0,1), Vector4(-unitLength*x,+hHLen,0,1), otherColor);
						f.addLine(Vector4(+unitLength*x,-hHLen,0,1), Vector4(+unitLength*x,+hHLen,0,1), otherColor);
					}
					for (Size y=1; y<halfHeight; y++)
					{
						f.addLine(Vector4(-hWLen,-unitLength*y,0,1), Vector4(+hWLen,-unitLength*y,0,1), otherColor);
						f.addLine(Vector4(-hWLen,+unitLength*y,0,1), Vector4(+hWLen,+unitLength*y,0,1), otherColor);
					}
				}
				
				//	Border lines.
				for (Size z=0; z<=halfDepth; z++)
				{
					f.addLine(Vector4(-hWLen,-hHLen,0,1), Vector4(+hWLen,-hHLen,0,1), otherColor);
					f.addLine(Vector4(-hWLen,+hHLen,0,1), Vector4(+hWLen,+hHLen,0,1), otherColor);
					
					f.addLine(Vector4(-hWLen,-hHLen,0,1), Vector4(-hWLen,+hHLen,0,1), otherColor);
					f.addLine(Vector4(+hWLen,-hHLen,0,1), Vector4(+hWLen,+hHLen,0,1), otherColor);
				}
				
				//	Center lines.
				f.addLine(Vector4(-hWLen,0,0,1), Vector4(+hWLen,0,0,1), centerColor);
				f.addLine(Vector4(0,-hHLen,0,1), Vector4(0,+hHLen,0,1), centerColor);
				f.addLine(Vector4(0,0,-hDLen,1), Vector4(0,0,+hDLen,1), centerColor);
				
				
				return	f;
			}
			
			_LineMeshForm const
			_LineMeshForm::Utility::cubicCross(const Vector3 halfLength, const Vector4 xColor, const Vector4 yColor, const Vector4 zColor)
			{
				Debugging::Doctor::assertForZeroOrNormal(halfLength.x);
				Debugging::Doctor::assertForZeroOrNormal(halfLength.y);
				Debugging::Doctor::assertForZeroOrNormal(halfLength.z);
				Debugging::Doctor::assertVector4Validity(xColor);
				Debugging::Doctor::assertVector4Validity(yColor);
				Debugging::Doctor::assertVector4Validity(zColor);
				
				////
				
				_LineMeshForm	f;
				f.addLine(Vector4(-halfLength.x,0,0,1), Vector4(+halfLength.x,0,0,1), xColor);
				f.addLine(Vector4(0,-halfLength.y,0,1), Vector4(0,+halfLength.y,0,1), xColor);
				f.addLine(Vector4(0,0,-halfLength.z,1), Vector4(0,0,+halfLength.z,1), xColor);
				return	f;
			}

			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			_Legacy2013_SharingBox<Program>
			_LineMeshForm::_makeShadingProgramInMachine(Machine& m)
			{
				static std::string const	vsc	=
				"										\n"
				"										\n"
				"uniform	mat4	tall;										\n"
				"attribute	vec4	vlocation;										\n"
				"attribute	vec4	vcolor;										\n"
				"										\n"
				"varying	vec4	fcolor;											\n"
				"										\n"
				"										\n"
				"void	main()										\n"
				"{										\n"
				"	vec4	p0	=	vlocation;										\n"
				"	vec4	p1	=	tall * p0; 										\n"
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
				"										\n"
				"varying highp vec4	fcolor;				\n"
	//				"varying vec4		fcolor;				\n"
				"										\n"
				"void	main()										\n"
				"{										\n"
				"	gl_FragColor	=	fcolor;										\n"
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
				nmap.insert({"vcolor", &m.vertexAttributeChannelAtIndex(1)});
				return	_Legacy2013_SharingBox<Program>(new Program(VertexShader(vsc, nmap), FragmentShader(fsc1)));
			}
			
			void
			_LineMeshForm::_renderOnMachine(Server::Machine &m, Server::_Legacy2013_SharingBox<Server::Program> &p, const std::vector<_LineMeshForm> &fs, const Matrix4 worldToFrameTransform)
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
				
	//				Matrix4		pers			=	Matrix4::Utility::perspective(-1, +1, -1, +1, 1, 1000);
	//				Matrix4		tran			=	Matrix4::Utility::translationWithScalars(0, 0, -1);
	//				Matrix4		tall			=	pers * tran;
	////				Matrix4		tall			=	Matrix4::Utility::orthograph(-2, +2, -1, +1, 0, 100) * Matrix4::Utility::translationWithScalars(0, 0, -10);
	////				Matrix4		tall			=	Matrix4::Utility::perspective(-2, +2, -1, +1, 0, 100);
				
				//	Draw screen overlays.
				m.useProgram(*p);
				for (_LineMeshForm const& f : fs)
				{
					Matrix4		tobj			=	f.transform();
					Matrix4		tall			=	worldToFrameTransform * tobj;
					
					p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("tall")).setValue(tall);
					if (f.lines().size() > 0)
					{
	//						ArrayBuffer	vb			=	ArrayBuffer(Memory::Factory::memoryByCopyingRange(f.lines()[0].scalars, sizeof(Line) * f.lines().size()));
	//						m.vertexAttributeChannelAtIndex(0).linkWithServerBuffer(vb, f0);
	//						m.vertexAttributeChannelAtIndex(1).linkWithServerBuffer(vb, f1);
						
						m.vertexAttributeChannelAtIndex(0).linkWithClientMemory(f.lines()[0].scalars, f0);
						m.vertexAttributeChannelAtIndex(1).linkWithClientMemory(f.lines()[0].scalars, f1);
						{
							m.drawArrays(DrawingMode::LINES, 0, f.lines().size() * 2);
						}
						m.vertexAttributeChannelAtIndex(0).unlink();
						m.vertexAttributeChannelAtIndex(1).unlink();
					}
					p->uniformValueSlotAtIndex(p->indexOfProgramUniformValueSlotProxyV1ForName("tall")).unset();
				}
				m.unuseProgram();
			}
	
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
		
}}}}






