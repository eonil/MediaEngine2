//
//  Declarations.h
//  Graphics
//
//  Created by Hoon H. on 2/27/14.
//
//

#pragma once
#include "../Common.h"

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
		
		class	Query;
		
		class	Renderbuffer;
		class	Framebuffer;
		
		class	ArrayBuffer;
		class	ElementArrayBuffer;
		
		class	PlanarTexture;
		
		class	VertexShader;
		class	FragmentShader;
		
		class	ProgramUniformValueSlotProxyV1;		//	Deprecated.
		class	ProgramVertexAttributeSlotProxyV1;	//	Deprecated.
		class	Program;
		class	ProgramUniformValueSlotProxy;
		class	ProgramVertexAttributeSlotProxy;
		
		namespace
		Machinery
		{
			class	VertexAttributeChannelIndex;
			
			
			
			class	VertexAttributeChannel;
			class	IndexUnitChannel;
			
			
			class	VertexAttributeChannelList;
			class	IndexUnitChannelList;
			
			class	TextureSampler;
		}
		
		
		
		
		
		
		
		
		
		template <typename T>
		class	_Legacy2013_SharingBox;
	}
	
}}}}

