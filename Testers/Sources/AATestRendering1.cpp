//
//  AATestRendering1.cpp
//  EonilGraphicsRunningTester
//
//  Created by Hoon Hwangbo on 6/18/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "AATestRendering1.h"

#include <vector>
#include <Eonil/Improvisations/MediaEngine/MediaEngine.h>
#include <Eonil/Improvisations/MediaEngine/MediaEngine_DEV_.h>

using namespace Eonil;
using namespace Eonil::Improvisations::MediaEngine::Graphics;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Value;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Stub;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Server;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Resource;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Transcoding;



namespace
{
	struct
	TestVertex
	{
		Vector4		position;
		Vector4		color;
	};
	
	std::string const
	TestVertexShaderProgram	=
	"attribute	vec4	vertexPosition;"
	"attribute	vec4	vertexColor;"
	"varying	vec4	fragmentColor;"
	"uniform	mat4	objectTransform;"
	""
	"void main(void)"
	"{"
	"	gl_Position		=	objectTransform * vertexPosition;"
	"	fragmentColor	=	vertexColor;"
	"}"
	;
	
	std::string const
	TestFragmentShaderProgram	=
	""
#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
	"#define	lowp	\n"
#endif
	""
	"varying lowp vec4 fragmentColor;"
	""
	"void main (void)"
	"{"
	"	gl_FragColor	=	fragmentColor;"
	"}"
	;
	
	
	std::vector<TestVertex> const
	MakeTestVertexesForSquare()
	{
		Scalar const u	=	0.5f;
		std::vector<TestVertex>	vs;
		{
			TestVertex	v;
			v.position	=	Vector4(+u,+u,0,1);
			v.color		=	Vector4(1,0,0,1);
			vs.push_back(v);
		}
		{
			TestVertex	v;
			v.position	=	Vector4(-u,+u,0,1);
			v.color		=	Vector4(0,1,0,1);
			vs.push_back(v);
		}
		{
			TestVertex	v;
			v.position	=	Vector4(+u,-u,0,1);
			v.color		=	Vector4(0,0,1,1);
			vs.push_back(v);
		}
		{
			TestVertex	v;
			v.position	=	Vector4(-u,-u,0,1);
			v.color		=	Vector4(1,1,1,1);
			vs.push_back(v);
		}
		return	vs;
	}
	
	std::vector<uint16_t> const
	MakeTestIndexesFoSquare()
	{
		std::vector<uint16_t>	idxs;
		idxs.push_back(33333);
		idxs.push_back(0);
		idxs.push_back(1);
		idxs.push_back(2);
		idxs.push_back(3);
		return	idxs;
	}
}









void
TestRendering1RenderingWithTransform()
{	
	//	Transfer data & program.
	std::vector<TestVertex> const	vs	=	MakeTestVertexesForSquare();
	std::vector<uint16_t> const		is	=	MakeTestIndexesFoSquare();
	
	VertexShader::NameChannelMap chmap;
	chmap.insert(std::pair<std::string, VertexAttributeChannel>("vertexPosition", Machine::machine().vertexAttributeChannelAtIndex(0)));
	chmap.insert(std::pair<std::string, VertexAttributeChannel>("vertexColor", Machine::machine().vertexAttributeChannelAtIndex(1)));

	Program					p		{VertexShader(TestVertexShaderProgram, chmap), FragmentShader(TestFragmentShaderProgram)};
	printf("program = %s\n", Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::describe(p).c_str());
	
	//	Perform rendering.
	ArrayBuffer			vb	{Legacy2013SharedMemory::Factory::memoryByCopyingRange(&vs[0], sizeof(TestVertex) * vs.size())};
	ElementArrayBuffer	ib	{Legacy2013SharedMemory::Factory::memoryByCopyingRange(&is[0], sizeof(uint16_t) * is.size())};
	
	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::Format	f0, f1;
	
	f0.dataOffset			=	0;
	f0.componentCount		=	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::ComponentSize::CODE::FOUR;
	f0.componentType		=	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::ComponentType::CODE::FLOAT;
	f0.normalization		=	false;
	f0.strideSizeInBytes	=	sizeof(TestVertex);
	
	f1.dataOffset			=	sizeof(Vector4);
	f1.componentCount		=	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::ComponentSize::CODE::FOUR;
	f1.componentType		=	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::ComponentType::CODE::FLOAT;
	f1.normalization		=	false;
	f1.strideSizeInBytes	=	sizeof(TestVertex);
	
	Machine::machine().setViewport(Bounds2(0,40,0+20,40+20));
	Machine::machine().vertexAttributeChannelAtIndex(0).linkWithServerBuffer(vb, f0);
	Machine::machine().vertexAttributeChannelAtIndex(1).linkWithServerBuffer(vb, f1);
	Machine::machine().indexUnitChannel().linkWithServerBuffer(ib, 0, IndexUnitChannel::UnitType::CODE::UINT16);
	Machine::machine().useProgram(p);
	{
		static Scalar	c = 0;
		c+=	0.01;
		Matrix4		tran		=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle(Vector3(0,0,1), c));
		p.uniformValueSlotAtIndex(p.indexOfUniformValueSlotForName("objectTransform")).setValue(tran);
		
		Machine::machine().drawElements(Machine::DrawingMode::TRIANGLE_STRIP, 1, is.size()-1);
	};
	Machine::machine().unuseProgram();
	Machine::machine().indexUnitChannel().unlink();
	Machine::machine().vertexAttributeChannelAtIndex(1).unlink();
	Machine::machine().vertexAttributeChannelAtIndex(0).unlink();
	Machine::machine().unsetViewport();
	
}


