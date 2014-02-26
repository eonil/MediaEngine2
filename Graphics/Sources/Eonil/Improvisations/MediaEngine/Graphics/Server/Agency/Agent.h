////
////  Agent.h
////  Graphics
////
////  Created by Hoon H. on 2/19/14.
////
////
//
//#ifndef __Graphics__Agent__
//#define __Graphics__Agent__
//
//#include "../../Common.h"
//#include "VertexDescriptor.h"
//
//namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
//	
//	namespace
//	Server
//	{
//		/*!
//		 Provides simplified, even more abstracted, data-driven drawing using graphics server.
//		 Sometimes can go less efficient.
//		 */
//		namespace
//		Agency
//		{
//			class	UniformProgramParameter;
//			
//			
//			
//			
//			
//			
//
//			/*!
//			 Clears all the color, depth and stencil with specified state.
//			 This exists mostly only for initial cleanup and quick testing.
//			 You will not want to use this on production code for rendering of each frame.
//			 
//			 @param	depth
//			 You can set 0~1 range value. Overflown/underflown value will raise an exception.
//			 Default value is 1 which means farthest distance.
//			 */
//			auto				clear(Vector4 const& color = {0,0,0,0}, Scalar const& depth = 1, Size const& stencil = 0) -> void;
//	
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			/*!
//			 @brief				Draws with geometry data placed in client-side memory.
//								This is good for data which is constantly mutated by CPU, so needs to be transferred to graphics server for each time.
//			 
//			 @param	frame		A marker parameter to require you to have a defined viewport frame.
//			 
//			 @param	range		Specifies index/count of vertexes to draw. Not a number of primitives.
//								This range must be correctly match for each drawing mode.
//								For example, you must specify 3*N number for TRIANGLES drawing mode.
//								And 3 + n for TRIANGLE_STRIP drawing mode.
//			 
//			 @discussion		This has some overhead, but super simple.
//								You must have a defined viewport to draw something.
//			 */
//			
//			auto				draw(Rendering::D2014R2::DisplayScreenFrame const& frame, Program& program, VertexDescriptor const& format, void const* const vertexes, PlanarTexture const& texture, DrawingMode const& mode, Range const& range) -> void;
//			
//			auto				draw(Rendering::D2014R2::DisplayScreenFrame const& frame, Program& program, VertexDescriptor const& format, void const* const vertexes, DrawingMode const& mode, Range const& range) -> void;
//			
//			
//			
//			
//			
//			
//			
//			
////			/*!
////			 @brief				Draws with geometry data placed in client-side memory.
////								This is good for data which is constantly mutated by CPU, so needs to be transferred to graphics server for each time.
////			 
////			 @param	frame		A marker parameter to require you to have a defined viewport frame.
////			 
////			 @param	range		Specifies index/count of vertexes to draw. Not a number of primitives.
////								This range must be correctly match for each drawing mode.
////								For example, you must specify 3*N number for TRIANGLES drawing mode.
////								And 3 + n for TRIANGLE_STRIP drawing mode.
////			 
////			 @discussion		This has some overhead, but super simple.
////								You must have a defined viewport to draw something.
////			 */
////			
////			auto				draw(Rendering::D2014R2::DisplayScreenFrame const& frame, Program& program, vec<UniformProgramParameter> const& parameters, VertexDescriptor const& format, void const* const vertexes, PlanarTexture const& texture, DrawingMode const& mode, Range const& range) -> void;
////			
////			auto				draw(Rendering::D2014R2::DisplayScreenFrame const& frame, Program& program, vec<UniformProgramParameter> const& parameters, VertexDescriptor const& format, void const* const vertexes, DrawingMode const& mode, Range const& range) -> void;
////			
////			
////			
//			
//
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
////			/*!
////			 Draws with geometry data placed in server-side memory.
////			 */
////			auto	draw(Program const& program, VertexDescriptor const& format, ArrayBuffer const& vertexes, ElementArrayBuffer const& indexes, PlanarTexture const& texture, DrawingMode const& mode, Range const& range) -> void;
//
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//			
//		}
//	}
//	
//}}}}
//
//#endif /* defined(__Graphics__Agent__) */
