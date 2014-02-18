////
////  Mesh.cpp
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 4/30/13.
////  Copyright (c) 2013 Eonil. All rights reserved.
////
//
//#include "Mesh.h"
//#include "Server/Buffer.h"
//#include "Server/VertexChanneling.h"
//
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		std::vector<Mesh::Vertex> const&
//		Mesh::vertexes() const
//		{
//			return	_vtxs;
//		}
//		std::vector<Mesh::Section> const&
//		Mesh::sections() const
//		{
//			return	_secs;
//		}
//
//		
//		
//		
//		
//		Size const
//		Mesh::vertexesSizeInBytes() const
//		{
//			return	sizeof(Vertex) * _vtxs.size();
//		}
//		Memory const
//		Mesh::vertexesSnapshotData() const
//		{
//			Size const	len		=	vertexesSizeInBytes();
//			Vertex*		vsptr	=	(Vertex*)malloc(len);
//			Size const	c		=	_vtxs.size();
//			
//			for (size_t i=0; i<c; i++)
//			{
//				vsptr[i]		=	_vtxs.at(i);		//	Copies.
//			}
//		 	
//			return 	Memory::Factory::memoryByOwningRange(vsptr, len);
//		}
//		
//		VertexSourcingWithServerBuffer const
//		Mesh::vertexSourcingParametersWithArrayBuffer(Eonil::Improvisations::MediaEngine::Graphics::Server::ArrayBuffer dataBuffer) const
//		{
//			VertexSourcingWithServerBuffer	src(dataBuffer);
//			src.channelingFormats.resize(4);
//			
//			src.channelingFormats[0].componentCount		=	VertexChannelingFormat::THREE;
//			src.channelingFormats[0].componentType		=	VertexChannelingFormat::FLOAT;
//			src.channelingFormats[0].strideSizeInBytes	=	sizeof(Vertex);
//			src.channelingFormats[0].normalization		=	GL_FALSE;
//			src.channelingFormats[0].setBufferOffsetInBytes(0);
//			
//			src.channelingFormats[1].componentCount		=	VertexChannelingFormat::TWO;
//			src.channelingFormats[1].componentType		=	VertexChannelingFormat::FLOAT;
//			src.channelingFormats[1].strideSizeInBytes	=	sizeof(Vertex);
//			src.channelingFormats[1].normalization		=	GL_FALSE;
//			src.channelingFormats[1].setBufferOffsetInBytes(4*3);
//			
//			src.channelingFormats[2].componentCount		=	VertexChannelingFormat::FOUR;
//			src.channelingFormats[2].componentType		=	VertexChannelingFormat::UBYTE;
//			src.channelingFormats[2].strideSizeInBytes	=	sizeof(Vertex);
//			src.channelingFormats[2].normalization		=	GL_FALSE;
//			src.channelingFormats[2].setBufferOffsetInBytes(4*3+4*3);
//			
//			src.channelingFormats[3].componentCount		=	VertexChannelingFormat::FOUR;
//			src.channelingFormats[3].componentType		=	VertexChannelingFormat::FLOAT;
//			src.channelingFormats[3].strideSizeInBytes	=	sizeof(Vertex);
//			src.channelingFormats[3].normalization		=	GL_FALSE;
//			src.channelingFormats[3].setBufferOffsetInBytes(4*3+4*3+1*4);
//			
//			return	src;			
//		}
//		
//		
//		
//		
//		
//		std::vector<Mesh::Vertex>&
//		Mesh::mutableVertexes()
//		{
//			return	_vtxs;
//		}
//		std::vector<Mesh::Section>&
//		Mesh::mutableSections()
//		{
//			return	_secs;
//		}
//	}
//}
//
//
//
//
//
//
//
//
