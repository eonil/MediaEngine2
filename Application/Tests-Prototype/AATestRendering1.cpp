//
//  AATestRendering1.cpp
//  EonilGraphicsRunningTester
//
//  Created by Hoon Hwangbo on 6/18/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "AATestRendering1.h"

#include <vector>
#include <Eonil/MediaEngine/Graphics.h>
#include <Eonil/MediaEngine/Graphics_DEV.h>

using namespace Eonil;
using namespace Eonil::MediaEngine::Graphics;
using namespace Eonil::MediaEngine::Graphics::Value;
using namespace Eonil::MediaEngine::Graphics::Stub;
using namespace Eonil::MediaEngine::Graphics::Server;
//using namespace Eonil::MediaEngine::Graphics::Resources;
//using namespace Eonil::MediaEngine::Graphics::Transcoding;



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

	Program					p		{VertexShader(TestVertexShaderProgram), FragmentShader(TestFragmentShaderProgram)};
	printf("program = %s\n", Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::describe(p).c_str());
	
	//	Perform rendering.
	ArrayBuffer			vb	=	{{vs.data(), vs.data()+vs.size()}};
	ElementArrayBuffer	ib	=	{{is.data(), is.data()+is.size()}};
	
	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::Format	f0, f1;
	
	f0.dataOffset			=	0;
	f0.componentCount		=	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::ComponentSize::FOUR;
	f0.componentType		=	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::ComponentType::FLOAT;
	f0.normalization		=	false;
	f0.strideSizeInBytes	=	sizeof(TestVertex);
	
	f1.dataOffset			=	sizeof(Vector4);
	f1.componentCount		=	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::ComponentSize::FOUR;
	f1.componentType		=	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::ComponentType::FLOAT;
	f1.normalization		=	false;
	f1.strideSizeInBytes	=	sizeof(TestVertex);
	
	Machine::current().setViewport(Bounds2(0,40,0+20,40+20));
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->linkWithServerBuffer(vb, f0);
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexColor"))->linkWithServerBuffer(vb, f1);
	Machine::current().indexUnitChannel().linkWithServerBuffer(ib, 0, IndexUnitChannel::UnitType::CODE::UINT16);
	Machine::current().useProgram(p);
	{
		static Scalar	c = 0;
		c+=	0.01;
		Matrix4		tran		=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle(Vector3(0,0,1), c));
		p.uniformValueSlotForName("objectTransform")->setValue(tran);
		
		Machine::current().drawElements(DrawingMode::TRIANGLE_STRIP, 1, is.size()-1);
	};
	Machine::current().unuseProgram();
	Machine::current().indexUnitChannel().unlink();
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexColor"))->unlink();
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->unlink();
	Machine::current().unsetViewport();
	
}


