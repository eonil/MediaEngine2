//
//  AATestRendering2.cpp
//  EonilGraphicsRunningTester
//
//  Created by Hoon Hwangbo on 6/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "AATestRendering2.h"













#include <vector>
#include <Eonil/MediaEngine/Graphics.h>
#include <Eonil/MediaEngine/Graphics_DEV.h>


using namespace Eonil;
using namespace Eonil::Improvisations::MediaEngine::Graphics;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Value;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Stub;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Server;
//using namespace Eonil::Improvisations::MediaEngine::Graphics::Resources;
//using namespace Eonil::Improvisations::MediaEngine::Graphics::Transcoding;



namespace
{
	struct
	TestVertex
	{
		Vector4		position;
		Vector2		texture;
	};
	
	std::string const
	TestVertexShaderProgram	=
	"attribute	vec4	vertexPosition;"
	"attribute	vec2	vertexTexture;"
	"varying	vec2	fragmentTexture;"
	"uniform	mat4	objectTransform;"
	""
	"void main(void)"
	"{"
	"	gl_Position		=	objectTransform * vertexPosition;"
	"	fragmentTexture	=	vertexTexture;"
	"}"
	;
	
	std::string const
	TestFragmentShaderProgram	=
	""
#if	EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
	"#define	lowp	\n"
#endif
	""
	"uniform sampler2D	textureSampler;"
	"varying lowp vec2	fragmentTexture;"
	""
	"void main (void)"
	"{"
	"	lowp vec4	c	=	texture2D(textureSampler, fragmentTexture);"
	"	gl_FragColor	=	c;"
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
			v.texture	=	Vector2(1,1);
			vs.push_back(v);
		}
		{
			TestVertex	v;
			v.position	=	Vector4(-u,+u,0,1);
			v.texture	=	Vector2(0,1);
			vs.push_back(v);
		}
		{
			TestVertex	v;
			v.position	=	Vector4(+u,-u,0,1);
			v.texture	=	Vector2(1,0);
			vs.push_back(v);
		}
		{
			TestVertex	v;
			v.position	=	Vector4(-u,-u,0,1);
			v.texture	=	Vector2(0,0);
			vs.push_back(v);
		}
		return	vs;
	}
	
	std::vector<uint16_t> const
	MakeTestIndexesFoSquare()
	{
		std::vector<uint16_t>	idxs;
		idxs.push_back(0);
		idxs.push_back(1);
		idxs.push_back(2);
		idxs.push_back(3);
		return	idxs;
	}
}































void
TestRendering2RenderingWithTexture(PlanarTexture const& texture)
{
	
	//	Transfer data & program.
	std::vector<TestVertex> const	vs	=	MakeTestVertexesForSquare();
	std::vector<uint16_t> const		is	=	MakeTestIndexesFoSquare();
	
	Program 	p			{VertexShader(TestVertexShaderProgram), FragmentShader(TestFragmentShaderProgram)};
	
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
	f1.componentCount		=	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::ComponentSize::TWO;
	f1.componentType		=	Eonil::Improvisations::MediaEngine::Graphics::Server::Machinery::VertexAttributeChannel::ComponentType::FLOAT;
	f1.normalization		=	false;
	f1.strideSizeInBytes	=	sizeof(TestVertex);
	
	Machine::current().setViewport(Bounds2(0,80,0+80,80+80));
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->linkWithServerBuffer(vb, f0);
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexTexture"))->linkWithServerBuffer(vb, f1);
	Machine::current().indexUnitChannel().linkWithServerBuffer(ib, 0, IndexUnitChannel::UnitType::CODE::UINT16);
	Machine::current().useProgram(p);
	{
		static Scalar	c = 0;
		c+=	0.01;
		Matrix4		tran		=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle(Vector3(0,0,1), c));
		p.uniformValueSlotForName("objectTransform")->setValue(tran);
		
		Machine::current().textureUnitAtIndex(0).setTexture(texture);
		p.uniformValueSlotForName("textureSampler")->setSampler(Machine::current().textureUnitAtIndex(0));
		
		Machine::current().drawElements(DrawingMode::TRIANGLE_STRIP, 0, is.size());
		
		Machine::current().textureUnitAtIndex(0).unsetTexture();
	};
	Machine::current().unuseProgram();
	Machine::current().indexUnitChannel().unlink();
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexTexture"))->unlink();
	Machine::current().vertexAttributeChannels().at(*p.vertexAttributeSlotForName("vertexPosition"))->unlink();
	Machine::current().unsetViewport();
	
	
}





