//
//  Functions.h
//  Graphics
//
//  Created by Hoon H. on 2/26/14.
//
//

#ifndef __Graphics__Functions__
#define __Graphics__Functions__

#include "../../Common.h"
#include "../Declarations.h"

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
			
			class	VertexLayoutDescriptor;
			class	ProgramVertexChannelingDescriptor2;
			
			
			
			
			
			

			/*!
			 Clears all the color, depth and stencil with specified state.
			 This exists mostly only for initial cleanup and quick testing.
			 You will not want to use this on production code for rendering of each frame.
			 
			 @param	depth
			 You can set 0~1 range value. Overflown/underflown value will raise an exception.
			 Default value is 1 which means farthest distance.
			 */
			auto				clear(Vector4 const& color = {0,0,0,0}, Scalar const& depth = 1, Size const& stencil = 0) -> void;
	
			
			
			
			
			
			/*!
			 @brief				Draws with geometry data placed in client-side memory.
								This is good for data which is constantly mutated by CPU, so needs to be transferred to graphics server for each time.
			 
			 @param	textures	A series of textures to be bound to sampler units.
								A texture at an index will be bound to a sampler at the index.
			 
			 @param	range		Specifies index/count of vertexes to draw. Not a number of primitives.
								This range must be correctly match for each drawing mode.
								For example, you must specify 3*N number for TRIANGLES drawing mode.
								And 3 + n for TRIANGLE_STRIP drawing mode.
			 
			 @discussion		These stuffs must be set to proper values before calling this funciton.
				
								-	Viewport.
								-	Program.
								-	All required uniform parameters of the program.
			 
			 @discussion		Program uniform parameters cannot be set before the program as current program, and it may cause some overhead. (possibly huge)
								So you must set program yourself and configure all its uniform parameters properly before calling this function.
			 
			 @note				This isn't a trial to be functional style form. Developers, do not try 
								to make this to be functional. Functional style layer is *renderer-drawer*
								layer.
			 
			 
			 */
			auto				draw(void const* const vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, GenericMemoryRange<PlanarTexture const> const& textures, DrawingMode const& mode, Range const& range) -> void;
			auto				draw(void const* const vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, vec<PlanarTexture> const& textures, DrawingMode const& mode, Range const& range) -> void;
			auto				draw(void const* const vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, PlanarTexture const& texture, DrawingMode const& mode, Range const& range) -> void;
			auto				draw(void const* const vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, DrawingMode const& mode, Range const& range) -> void;
			
			auto				draw(Server::ArrayBuffer const& vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, GenericMemoryRange<PlanarTexture const> const& textures, DrawingMode const& mode, Range const& range) -> void;
//			auto				draw(Server::ArrayBuffer const& vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, vec<PlanarTexture> const& textures, DrawingMode const& mode, Range const& range) -> void;
//			auto				draw(Server::ArrayBuffer const& vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, PlanarTexture const& texture, DrawingMode const& mode, Range const& range) -> void;
			auto				draw(Server::ArrayBuffer const& vertexes, VertexLayoutDescriptor const& layout, ProgramVertexChannelingDescriptor2 const& channeling, DrawingMode const& mode, Range const& range) -> void;
			
			
			
			
			
			
			
			
			
			
			
			
		};
		
		
		
		
		
		
		
		
		
		
		
	}
	
}}}}
	

#endif /* defined(__Graphics__Functions__) */
