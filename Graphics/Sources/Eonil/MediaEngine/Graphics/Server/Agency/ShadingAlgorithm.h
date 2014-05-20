////
////  ShadingAlgorithm.h
////  Graphics
////
////  Created by Hoon H. on 2/23/14.
////
////
//
//#ifndef __Graphics__ShadingAlgorithm__
//#define __Graphics__ShadingAlgorithm__
//
//#include "../../Common.h"
//#include "UniformProgramParameter.h"
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
//			
//			class	VertexLayoutDescriptor;
//			
//			
//			
//			
//			
//			
//			
//			
//			/*!
//			 Represents a program with bound uniform state.
//			 
//			 @classdesign
//			 A program usually have uniform variables - the global mutable state.
//			 This is the biggest huddle which preventing functional style coding with
//			 program object. But because OpenGL is single threaded architecture, it
//			 presumes single threaded execution, and we can construct functional style
//			 hallucination on top of it. This is simply a bundle of a program and its
//			 uniform values. The uniforms will be bound when requested, but not until
//			 actually needed. This will look like a immutable object to users, and 
//			 users can code a lot more easily.
//			 
//			 @discussion
//			 This is a combination of a program and its uniform state.
//			 That is not complete state without vertex channeling.
//			 */
//			class
//			ShadingAlgorithm
//			{
//				friend	auto					draw(Rendering::D2014R2::DisplayScreenFrame const& frame, ShadingAlgorithm const& shading, VertexLayoutDescriptor const& format, void const* const vertexes, DrawingMode const& mode, Range const& range) -> void;
//				
//				Program*						_program_ptr	{nullptr};
//				vec<UniformProgramParameter>	_parameters		{};
//				
//			public:
//				ShadingAlgorithm(Program* program, vec<UniformProgramParameter>&& parameters);
//			};
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
//#endif /* defined(__Graphics__ShadingAlgorithm__) */
