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
using namespace Eonil::Improvisations::MediaEngine::Graphics::Transcoding;



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
		idxs.push_back(33333);
		idxs.push_back(0);
		idxs.push_back(1);
		idxs.push_back(2);
		idxs.push_back(3);
		return	idxs;
	}
}































void
TestRendering2RenderingWithTexture(PlanarTexture const& texture)
//void
//TestRendering2RenderingWithTexture(char const* filepath)
{
//	PlanarTexture	texture	=	Server::PlanarTexture::Utility::_DEV_textureWithFileAtPath(filepath);
	
	
	//	Transfer data & program.
	std::vector<TestVertex> const	vs	=	MakeTestVertexesForSquare();
	std::vector<uint16_t> const		is	=	MakeTestIndexesFoSquare();
	
	VertexShader::NameChannelMap chmap;
	chmap.insert(std::pair<str, Machinery::VertexAttributeChannel const*>{"vertexPosition", &Machine::current().vertexAttributeChannelAtIndex(0)});
	chmap.insert(std::pair<str, Machinery::VertexAttributeChannel const*>{"vertexTexture", &Machine::current().vertexAttributeChannelAtIndex(1)});
	
//	_Legacy2013_SharingBox<VertexShader> const				vp	=	;
//	_Legacy2013_SharingBox<FragmentShader> const			fp	=	_Legacy2013_SharingBox<FragmentShader>(new FragmentShader(TestFragmentShaderProgram));
	
	Program 	p			{VertexShader(TestVertexShaderProgram, chmap), FragmentShader(TestFragmentShaderProgram)};
	
	printf("program = %s\n", Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::describe(p).c_str());
	
	//	Perform rendering.
	ArrayBuffer			vb	{Legacy2013SharedMemory::Factory::memoryByCopyingRange(&vs[0], sizeof(TestVertex) * vs.size())};
	ElementArrayBuffer	ib	{Legacy2013SharedMemory::Factory::memoryByCopyingRange(&is[0], sizeof(uint16_t) * is.size())};
	
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
	
	Machine::machine().setViewport(Bounds2(0,80,0+80,80+80));
	Machine::machine().vertexAttributeChannelAtIndex(0).linkWithServerBuffer(vb, f0);
	Machine::machine().vertexAttributeChannelAtIndex(1).linkWithServerBuffer(vb, f1);
	Machine::machine().indexUnitChannel().linkWithServerBuffer(ib, 0, IndexUnitChannel::UnitType::CODE::UINT16);
	Machine::machine().useProgram(p);
	{
		static Scalar	c = 0;
		c+=	0.01;
		Matrix4		tran		=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle(Vector3(0,0,1), c));
//		p.uniformValueSlotAtIndex(p.indexOfUniformValueSlotV1ForName("objectTransform")).setValue(tran);
		p.uniformValueSlotForName("objectTransform")->setValue(tran);
		
		Machine::machine().textureUnitAtIndex(0).setTexture(texture);
//		p.uniformValueSlotAtIndex(p.indexOfUniformValueSlotV1ForName("textureSampler")).setSampler(Machine::machine().textureUnitAtIndex(0));
		p.uniformValueSlotForName("textureSampler")->setSampler(Machine::machine().textureUnitAtIndex(0));
		
		Machine::machine().drawElements(DrawingMode::TRIANGLE_STRIP, 1, is.size()-1);
		
		Machine::machine().textureUnitAtIndex(0).unsetTexture();
	};
	Machine::machine().unuseProgram();
	Machine::machine().indexUnitChannel().unlink();
	Machine::machine().vertexAttributeChannelAtIndex(1).unlink();
	Machine::machine().vertexAttributeChannelAtIndex(0).unlink();
	Machine::machine().unsetViewport();
	
	
}





