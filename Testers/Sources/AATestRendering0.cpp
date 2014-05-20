//
//  AATestRendering0.cpp
//  EonilGraphicsRunningTester
//
//  Created by Hoon Hwangbo on 6/17/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "AATestRendering0.h"


#include <vector>
#include <Eonil/MediaEngine/Graphics.h>
#include <Eonil/MediaEngine/Graphics_DEV.h>

using namespace Eonil;
using namespace Eonil::Improvisations::MediaEngine::Graphics;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Value;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Stub;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Server;
//using namespace Eonil::Improvisations::MediaEngine::Graphics::Resources;
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
	""
	"void main(void)"
	"{"
	"	gl_Position		=	vertexPosition;"
	"	fragmentColor	=	vertexColor;"
	"}"
	;
	
	std::string const
	TestFragmentShaderProgram	=
	""
#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
	"#define	lowp	\n"
#endif
#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
#endif
	""
	""
	"varying lowp vec4 fragmentColor;"
	""
	"void main (void)"
	"{"
//	"	gl_FragColor	=	vec4(1,1,0,1);"
	"	gl_FragColor	=	fragmentColor;"
	"}"
	;

	
	std::vector<TestVertex> const
	MakeTestVertexesForSquare()
	{
		std::vector<TestVertex>	vs;
		{
			TestVertex	v;
			v.position	=	Vector4(1,1,0,1);
			v.color		=	Vector4(1,0,0,1);
			vs.push_back(v);
		}
		{
			TestVertex	v;
			v.position	=	Vector4(-1,1,0,1);
			v.color		=	Vector4(0,1,0,1);
			vs.push_back(v);
		}
		{
			TestVertex	v;
			v.position	=	Vector4(1,-1,0,1);
			v.color		=	Vector4(0,0,1,1);
			vs.push_back(v);
		}
		{
			TestVertex	v;
			v.position	=	Vector4(-1,-1,0,1);
			v.color		=	Vector4(1,1,1,1);
			vs.push_back(v);
		}
		return	vs;
	}
	
	std::vector<uint16_t> const
	MakeTestIndexesFoSquare()
	{
		std::vector<uint16_t>	idxs;
		idxs.push_back(33333);			//	Wrong value at first intentionally for test...
		idxs.push_back(0);
		idxs.push_back(1);
		idxs.push_back(2);
		idxs.push_back(3);
		return	idxs;
	}
}













void
TestClearScreen()
{
	eeglClearColor(0.0f, 0.5f, 0.5f, 1.0f);
	eeglClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}










void
TestRenderingWithOnlyVertexesInClientMemory()
{
	//	Transfer data & program.
	std::vector<TestVertex> const	vs	=	MakeTestVertexesForSquare();
	
	VertexShader			vp	{TestVertexShaderProgram};
	FragmentShader			fp	{TestFragmentShaderProgram};
	Program					p	{vp, fp};
	
	//	Perform rendering.
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
	
	Machine::current().setViewport(Bounds2(0,0,10,10));
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->linkWithClientMemory(&vs[0], f0);
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexColor"))->linkWithClientMemory(&vs[0], f1);
	Machine::current().executeBlockWithProgram(p,[vs]
	{
		Machine::current().drawArrays(DrawingMode::TRIANGLE_STRIP, 0, vs.size());
	});
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexColor"))->unlink();
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->unlink();
	Machine::current().unsetViewport();
}














void
TestRenderingWithOnlyVertexesInServerMemory()
{
	//	Transfer data & program.
	std::vector<TestVertex> const	vs	=	MakeTestVertexesForSquare();
	
	VertexShader const				vp	{TestVertexShaderProgram};
	FragmentShader const			fp	{TestFragmentShaderProgram};
	Program							p	{vp, fp};
	
	//	Perform rendering.
	ArrayBuffer		vb		=	{{vs.data(), vs.data()+vs.size()}};
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
	
	Machine::current().setViewport(Bounds2(20,0,20+10,10));
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->linkWithServerBuffer(vb, f0);
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexColor"))->linkWithServerBuffer(vb, f1);
	Machine::current().executeBlockWithProgram(p,[vs]
	{
		Machine::current().drawArrays(DrawingMode::TRIANGLE_STRIP, 0, vs.size());
	});
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexColor"))->unlink();
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->unlink();
	Machine::current().unsetViewport();
	
}


























void
TestRenderingWithVertexesAndIndexesInClientMemory()
{
	//	Transfer data & program.
	std::vector<TestVertex> const	vs	=	MakeTestVertexesForSquare();
	std::vector<uint16_t> const		is	=	MakeTestIndexesFoSquare();
		
	VertexShader			vp	{TestVertexShaderProgram};
	FragmentShader			fp	{TestFragmentShaderProgram};
	Program					p	{vp, fp};
	
	//	Perform rendering.
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
	
	Machine::current().setViewport(Bounds2(40,0,40+10,10));
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->linkWithClientMemory(&vs[0], f0);
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexColor"))->linkWithClientMemory(&vs[0], f1);
	Machine::current().indexUnitChannel().linkWithClientMemory({is.data(), is.data()+is.size()}, IndexUnitChannel::UnitType::UINT16);
	Machine::current().executeBlockWithProgram(p,[vs, is]
	{
		Machine::current().drawElements(DrawingMode::TRIANGLE_STRIP, 1, is.size()-1);		//	Starts from second index intentionally for test...
	});
	Machine::current().indexUnitChannel().unlink();
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexColor"))->unlink();
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->unlink();
	Machine::current().unsetViewport();
}











void
TestRenderingWithVertexesAndIndexesInServerMemory()
{
	//	Transfer data & program.
	std::vector<TestVertex> const	vs	=	MakeTestVertexesForSquare();
	std::vector<uint16_t> const		is	=	MakeTestIndexesFoSquare();
	
	Program							p	{VertexShader(TestVertexShaderProgram), FragmentShader(TestFragmentShaderProgram)};
	
	//	Perform rendering.
	ArrayBuffer			vb		=	{{vs.data(), vs.data()+vs.size()}};
	ElementArrayBuffer	ib		=	{{is.data(), is.data()+is.size()}};
	
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
	
	Machine::current().setViewport(Bounds2(60,0,60+10,10));
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->linkWithServerBuffer(vb, f0);
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexColor"))->linkWithServerBuffer(vb, f1);
	Machine::current().indexUnitChannel().linkWithServerBuffer(ib, 0, IndexUnitChannel::UnitType::CODE::UINT16);
	Machine::current().executeBlockWithProgram(p,[vs,is]
	{
		Machine::current().drawElements(DrawingMode::TRIANGLE_STRIP, 1, is.size()-1);		//	Starts from second index intentionally for test...
	});
	Machine::current().indexUnitChannel().unlink();
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexColor"))->unlink();
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->unlink();
	Machine::current().unsetViewport();
	
	
}






