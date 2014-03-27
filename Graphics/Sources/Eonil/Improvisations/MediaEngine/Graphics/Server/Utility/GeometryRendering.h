//
//  GeometryRendering.h
//  Graphics
//
//  Created by Hoon H. on 3/27/14.
//
//

#ifndef __Graphics__GeometryRendering__
#define __Graphics__GeometryRendering__


#include "../../Common.h"
#include "../Declarations.h"

#include "VertexComponentChannelingDescriptor.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		/*!
		 A collection of convenient functions.
		 
		 @classdesign
		 This is provided to perform many operations in a few calls.
		 This is not designed for conceptual completeness.
		 
		 @note
		 DO NOT TRY TO MAKE THIS TO BE CONCEPTUALLY COMPLETE.
		 */
		namespace
		Utility
		{
			/*
			 Vertex data can be sourced from multiple sources. In many cases, only one (interleaved) source is used.
			 */

			using	ServerBufferChannelingRangePointer	=	GenericMemoryRange<VertexComponentChannelingDescriptorForStreamInServerBuffer const>;
			using	ClientMemoryChannelingRangePointer	=	GenericMemoryRange<VertexComponentChannelingDescriptorForStreamInClientMemory const>;
			using	TextureChannelingRangePointer		=	GenericMemoryRange<PlanarTexture const>;														//!	Texture bindings for each samplers at indexes.
			

			struct
			GeometryChanneling
			{
				ServerBufferChannelingRangePointer		server	{};
				ClientMemoryChannelingRangePointer		client	{};
				
				GeometryChanneling() = delete;
				GeometryChanneling(VertexComponentChannelingDescriptorForStreamInServerBuffer const* server) : server({server, server+1}) {}
				GeometryChanneling(VertexComponentChannelingDescriptorForStreamInClientMemory const* client) : client({client, client+1}) {}
				GeometryChanneling(VertexComponentChannelingDescriptorForStreamInServerBuffer const* server, VertexComponentChannelingDescriptorForStreamInClientMemory const* client) : server({server, server+1}), client({client, client+1}) {}
				GeometryChanneling(ClientMemoryChannelingRangePointer const& client) : client(client) {}
				GeometryChanneling(ServerBufferChannelingRangePointer const& server) : server(server) {}
				GeometryChanneling(ServerBufferChannelingRangePointer const& server, ClientMemoryChannelingRangePointer const& client) : server(server), client(client) {}
			};
			
			struct
			GeometryInstancing
			{
				
			};
			
			
						
			/*!
			 @brief				Draws with geometry data placed in client-side memory.
								This is good for data which is constantly mutated by CPU, so needs to be transferred to graphics server for each time.
			 
			 @param	textures	A series of textures to be bound to sampler units.
								A texture at an index will be bound to a sampler at the index.
			 
			 @param	selection	Specifies index/count of vertexes to draw. Not a number of primitives.
								This range must be correctly match for each drawing mode.
								For example, you must specify 3*N number for TRIANGLES drawing mode.
								And 3 + n for TRIANGLE_STRIP drawing mode.
			 
			 @discussion		These stuffs must be set to proper values before calling this funciton.
				
								-	Viewport.
								-	Program.
								-	All required uniform parameters of the program.
			 
			 @discussion		Program uniform parameters cannot be set before the program as current program, and it may cause some overhead. (possibly huge)
								So you must set program yourself and configure all its uniform parameters properly before calling this function.
			 
			 @note				This isn't a trial to be functional-style form. Developers, do not try
								to make this to be functional. Functional style layer is *renderer-drawer*
								layer.
			 
			 @note				This is the most generic form. Others are just simplified versions, and semantically will use this version.
								This passes very many stuffs, but not everything. For example, program unifroams are not being passed.
			 
			 */
			auto	draw(GeometryChanneling const& vertexes, TextureChannelingRangePointer const& textures, DrawingMode const& mode, IndexingRange const& selection) -> void;
			auto	draw(GeometryChanneling const& vertexes, DrawingMode const& mode, IndexingRange const& selection) -> void;

		
		
		
		
		
		
		
		}
	}
	
}}}}

#endif /* defined(__Graphics__GeometryRendering__) */
