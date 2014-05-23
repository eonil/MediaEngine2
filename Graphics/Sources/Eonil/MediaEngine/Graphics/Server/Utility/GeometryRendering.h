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


			struct
			GeometryProvisioning
			{
				using	SS	=	GenericMemoryRange<ServerBufferVertexProvisioning const>;
				using	CC	=	GenericMemoryRange<ClientMemoryVertexProvisioning const>;
				
				SS		server	{};
				CC		client	{};
				
				GeometryProvisioning() = delete;
				GeometryProvisioning(ServerBufferVertexProvisioning const* server) : server({server, server+1}) { EONIL_DEBUG_ASSERT(server != nullptr); }
				GeometryProvisioning(ClientMemoryVertexProvisioning const* client) : client({client, client+1}) { EONIL_DEBUG_ASSERT(client != nullptr); }
				GeometryProvisioning(ServerBufferVertexProvisioning const* server, ClientMemoryVertexProvisioning const* client) : server({server, server+1}), client({client, client+1}) { EONIL_DEBUG_ASSERT(server != nullptr); EONIL_DEBUG_ASSERT(client != nullptr); }
				GeometryProvisioning(SS const& server) : server(server) { EONIL_DEBUG_ASSERT(&server != nullptr); }
				GeometryProvisioning(CC const& client) : client(client) { EONIL_DEBUG_ASSERT(&client != nullptr); }
				GeometryProvisioning(SS const& server, CC const& client) : server(server), client(client) { EONIL_DEBUG_ASSERT(&server != nullptr); EONIL_DEBUG_ASSERT(&client != nullptr); }
				
				auto
				empty() const -> bool
				{
					return	server.empty() and client.empty();
				}
			};
			
//			struct
//			GeometryInstancing
//			{	
//			};
			
			using	TextureChannelingRangePointer	=	GenericMemoryRange<PlanarTexture const>;														//!	Texture bindings for each samplers at indexes.
			
						
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
			 
			 @note				If you don't want to use some parameter, use an overload which doesn't have the parameter. 
								Do not pass empty parameter. In other words, always fill all the parameters.
			 */
			auto	draw(GeometryProvisioning const& vertexes, TextureChannelingRangePointer const& textures, DrawingMode const& mode, IndexingRange const& selection) -> void;
			auto	draw(GeometryProvisioning const& vertexes, DrawingMode const& mode, IndexingRange const& selection) -> void;

		
		
		
		
		
		
		
		}
	}
	
}}}}

#endif /* defined(__Graphics__GeometryRendering__) */
