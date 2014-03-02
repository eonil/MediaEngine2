//
//  Declarations.h
//  Graphics
//
//  Created by Hoon H. on 2/27/14.
//
//

#ifndef __Graphics__Declarations__
#define __Graphics__Declarations__

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		
		
		
		
		
		enum class	FACE : GLenum;
		enum class	COMPARISON : GLenum;
		enum class	OPERATION : GLenum;
		enum class	DrawingMode : GLenum;
		enum class	BlendingMode : GLenum;
		
		
		
		class	Machine;
		
		class	Renderbuffer;
		class	Framebuffer;
		
		class	ArrayBuffer;
		class	ElementArrayBuffer;
		
		class	PlanarTexture;
		
		class	VertexShader;
		class	FragmentShader;
		
		class	UniformValueSlot;
		class	VertexAttributeSlot;
		class	Program;
		
		namespace
		Machinery
		{
			class	VertexAttributeChannel;
			class	IndexUnitChannel;
			
			class	TextureSampler;
		}
		
		
		
		
		
		
		
		
		
		template <typename T>
		class	_Legacy2013_SharingBox;
	}
	
}}}}

#endif /* defined(__Graphics__Declarations__) */
