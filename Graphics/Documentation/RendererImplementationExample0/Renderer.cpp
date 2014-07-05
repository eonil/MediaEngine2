//
//  Renderer.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include	"../Common.h"
#include 	"../Stub/GL.h"
#include	"../Server/Machine.h"
#include	"../Server/Program.h"
#include	"../Server/Shader.h"
#include	"../Server/Buffer.h"
#include	"../Server/Texture.h"

#include 	"Renderer.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
	
	using namespace Debugging;
	using namespace	Server;
	using namespace Stub;
	using namespace Value;
	using namespace Resource;
	
	
	namespace
	{
		
		void
		renderFigureUsingCamera(Figure const f, Camera const c)
		{
			
		}
		
		void
		renderCluster()
		{
			
		}
		
		
		void
		renderCloud()
		{
			
		}
		
		
	}
	
	
	
	
	
	
	
	
	
	
	
	Renderer::Renderer()
	{
	}
	Renderer::~Renderer()
	{
		
	}
	
	
	
	void
	Renderer::clearFrame(const Vector4 color)
	{
		eeglClearColor(color.x, color.y, color.z, color.w);
		eeglClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	
	void
	Renderer::render(const Scene scene)
	{
//			for (Figure const& f : scene.figures)
//			{		
////				renderFigure(f);
//			}
		
		
		//	Prepare data.
//			std::vector<UInt16>		idxs;			
//			DeformingMesh::Section	ms();
		
		std::vector<DeformingMesh::Vertex>	vs;
		{
			DeformingMesh::Vertex	v;
			v.geom.spaceCoordinate		=	Vector3(1,1,0);
			v.geom.normalDirection		=	Vector3(0,0,0);
			v.texture.mappingCoordinate	=	Vector2(1,1);
			vs.push_back(v);
		}
		{
			DeformingMesh::Vertex	v;
			v.geom.spaceCoordinate		=	Vector3(-1,1,0);
			v.geom.normalDirection		=	Vector3(0,0,0);
			v.texture.mappingCoordinate	=	Vector2(0,1);
			vs.push_back(v);
		}
		{
			DeformingMesh::Vertex	v;
			v.geom.spaceCoordinate		=	Vector3(1,-1,0);
			v.geom.normalDirection		=	Vector3(0,0,0);
			v.texture.mappingCoordinate	=	Vector2(1,0);
			vs.push_back(v);
		}
		{
			DeformingMesh::Vertex	v;
			v.geom.spaceCoordinate		=	Vector3(-1,-1,0);
			v.geom.normalDirection		=	Vector3(0,0,0);
			v.texture.mappingCoordinate	=	Vector2(0,0);
			vs.push_back(v);
		}
		
		_Legacy2013_SharingBox<ArrayBuffer>				vb	=	new ArrayBuffer(Legacy2013SharedMemory::Factory::memoryByProxyingRange(&vs[0], sizeof(DeformingMesh::Vertex) * vs.size()));
		_Legacy2013_SharingBox<ElementArrayBuffer>		ib	=	new ElementArrayBuffer(Legacy2013SharedMemory::Factory::memoryByProxyingRange(&vs[0], sizeof(DeformingMesh::Vertex) * vs.size()));
		std::vector<DeformingMesh::Section const>	ss;
		
		DeformingMesh			m(vb, ib, ss);
		

		
		
		
//			
//			//	Prepare program.
//			std::string		vps	=
//			"attribute	vec3	vertexPosition;"
//			""
//			"void main(void)"
//			"{"
//			"	vec3		v	=	vertexPosition;"
//			"	vec4		p	=	vec4(v.x,v.y,v.z,1);"
//			"	gl_Position		=	p;"
//			"}"
//			;
//			
//			std::string		fps	=
//			""
//			"void main (void)"
//			"{"
//			"	gl_FragColor	=	vec4(1,1,0,1);"
//			"}"
//			;
//
//			//	Transfer data & program.
//			
//			VertexShader	vp	=	VertexShader(vps);
//			FragmentShader	fp	=	FragmentShader(fps);
//			Program			p	=	Program(vp, fp);
//			
//			
		
		
		
		
		
		
//			//	Perform rendering.
////			VertexSourcingWithServerBuffer	srcparam	=	m.vertexSourcingParametersWithArrayBuffer(vb);
//			VertexSourcingWithServerBuffer	srcparam(vb);
//			srcparam.channelingFormats.resize(1);
//			srcparam.channelingFormats[0].componentCount	=	VertexChannelingFormat::FOUR;
//			srcparam.channelingFormats[0].componentType		=	VertexChannelingFormat::FLOAT;
//			srcparam.channelingFormats[0].normalization		=	GL_FALSE;
//			srcparam.channelingFormats[0].strideSizeInBytes	=	sizeof(DeformingMesh::Vertex);
//			srcparam.channelingFormats[0].setBufferOffsetInBytes(0);
		
//			Machine::current().setViewport(Rect(100,100,200,200));
//			Machine::current().executeBlockWithProgram(p,[srcparam, vs]
//			{
//				Machine::current().setVertexSourcingParameters(srcparam);
//				{
//					printf("machine = %s", Machine::current().description().c_str());
////					p.mutableProgramVertexAttributeSlotProxyV1AtIndex(0).setVertexAttributeChannel(Machine::current().vertexAttributeChannelAtIndex(0));
////					Machine::current().drawArrays(DrawingMode::TRIANGLE_STRIP, 0, m.vertexes().size());
//					Machine::current().drawArrays(DrawingMode::TRIANGLE_STRIP, 0, vs.size());
//				}
//				Machine::current().unsetVertexSourcingParameters();
//			});
	}
	
	
	
	
	
	
	
	
}}}}









