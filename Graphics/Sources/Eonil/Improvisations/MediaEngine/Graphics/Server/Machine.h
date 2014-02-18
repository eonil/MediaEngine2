//
//  Machine.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__Machine__
#define __EonilGraphics__Machine__

#include "Program.h"
#include "Shader.h"
#include "Texture.h"
#include "Buffer.h"
#include "Framebuffer.h"

#include "Machinery/VertexAttributeChannel.h"
#include "Machinery/IndexUnitChannel.h"
#include "Machinery/TextureSampler.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Server
	{
		using namespace	Machinery;
		using namespace Value;
		
		
		
		
		
		
		
		
		/*!
		 Assumes this is the only way to interact to OpenGL device.
		 You should not access OpenGL directly to ensure this class to work correctly.
		 
		 */
		class
		Machine 
		{
			std::vector<VertexAttributeChannel>	_chs;
			IndexUnitChannel					_idxch;
			std::vector<TextureSampler>			_tus;
			
			Machine();
			Machine(Machine const& origin);					//	Copy prohibited.
			
		public:
			
			enum class
			DrawingMode : GLenum
			{
				POINTS			=	GL_POINTS,
				LINE_STRIP		=	GL_LINE_STRIP,
				LINE_LOOP		=	GL_LINE_LOOP,
				LINES			=	GL_LINES,
				TRIANGLE_STRIP	=	GL_TRIANGLE_STRIP,
				TRIANGLE_FAN	=	GL_TRIANGLE_FAN,
				TRIANGLES		=	GL_TRIANGLES,
			};
			enum class
			BlendingMode : GLenum
			{
				ZERO						=	GL_ZERO,
				ONE							=	GL_ONE,
				SOURCE_COLOR				=	GL_SRC_COLOR,
				DESTINATION_COLOR			=	GL_DST_COLOR,
				SOURCE_ALPHA				=	GL_SRC_ALPHA,
				DESTINATION_ALPHA			=	GL_DST_ALPHA,
				ONE_MINUS_SOURCE_COLOR		=	GL_ONE_MINUS_SRC_COLOR,
				ONE_MINUS_DESTINATION_COLOR	=	GL_ONE_MINUS_DST_COLOR,
				ONE_MINUS_SOURCE_ALPHA		=	GL_ONE_MINUS_SRC_ALPHA,
				ONE_MINUS_DESTINATION_ALPHA	=	GL_ONE_MINUS_DST_ALPHA,
				ONE_MINUS_CONSTANT_COLOR	=	GL_ONE_MINUS_CONSTANT_COLOR,
				ONE_MINUS_CONSTANT_ALPHA	=	GL_ONE_MINUS_CONSTANT_ALPHA,
				CONSTANT_COLOR				=	GL_CONSTANT_COLOR,
				CONSTANT_ALPHA				=	GL_CONSTANT_ALPHA,
				SOURCE_ALPHA_SATURATE		=	GL_SRC_ALPHA_SATURATE,			//	This is the only value which is not supported as destination blending.
			};
			
		public:
			static Machine&						machine();
			
		public:
			auto	setFramebuffer(Framebuffer const& framebuffer) -> void;
			auto	unsetFramebuffer() -> void;
			
			std::vector<VertexAttributeChannel> const&	vertexAttributeChannels() const;
			VertexAttributeChannel const&		vertexAttributeChannelAtIndex(Size const index) const;
			VertexAttributeChannel&				vertexAttributeChannelAtIndex(Size const index);
			
			IndexUnitChannel const&				indexUnitChannel() const;
			IndexUnitChannel&					indexUnitChannel();
			
			std::vector<TextureSampler> const&	textureUnits() const;
			TextureSampler const&				textureUnitAtIndex(Size const index) const;
			TextureSampler&						textureUnitAtIndex(Size const index);
			
//			void								linkAllVertexAttributeChannelsWithClientMemory(void const* memory, VertexAttributeComponentSize const size, VertexAttributeComponentType const type, Size const stride, bool const normalization = false);
//			void								linkAllVertexAttributeChannelsWithServerBuffer(ArrayBuffer const buffer, Size const offset, VertexAttributeComponentSize const size, VertexAttributeComponentType const type, Size const stride, bool const normalization = false);
//			void								unlinkAllVertexAttributeChannel();
			
			auto								useProgram(Program const& program) -> void;
			auto								unuseProgram() -> void;
			
			auto								executeBlockWithProgram(Program const& program, std::function<void()> block) -> void;
			
			void								setViewport(Bounds2 const bounds);		//!	Bounds in client windows coordinate space.
			void								unsetViewport();
			
			void								setScissor(Bounds2 const bounds);		//!	Bounds in client windows coordinate space.
			void								unsetScissor();
			
//			void								drawArrays();																		//	Draws all data as triangle strip.
//			void								drawArrays(Size const index, Size const count);										//	Draws as triangle strip.
//			void								drawArrays(DrawingMode const mode);
			
			/*!
			 @param	count		Number of vertexes to be used for drawing.
								Ultimately this decides number of point/line/triangles to be drawn.
			 */
			void
			drawArrays(DrawingMode const mode, Size const index, Size const count);
			
			void								drawElements(DrawingMode const mode, Size const index, Size const count);
//			void								drawElements(DrawingMode const mode, Size const count, Size const offset);
			

			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		public:
			std::string const					description() const;
//			bool const							validityOfVertexSourcing() const;
//			bool const							validityOfProgramDesignation() const;
			
		private:
			bool	_validity_of_viewport			=	false;
			bool	_has_scissor					=	false;
//			bool	_validity_vertex_sourcing		=	false;		//	False if vertex source is not configured well.
//			bool	_validity_index_sourcing		=	false;		//	False if index source is not configured well.
			bool	_validity_program_designation	=	false;
			
			
			
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
////			struct ProgramRef;
////			struct VertexShaderRef;
////			struct FragmentShaderRef;
////			struct PlanarTextureRef;
////			struct ArrayBufferRef;
////			struct ElementArrayBufferRef;
////			
////			struct VertexShaderRef : public std::shared_ptr<VertexShader>
////			{
////				VertexShaderRef(std::string const sourceCode) : std::shared_ptr<VertexShader>(new VertexShader(sourceCode)) {}
////			};
////			struct FragmentShaderRef : public std::shared_ptr<FragmentShader>
////			{
////				FragmentShaderRef(std::string const sourceCode) : std::shared_ptr<FragmentShader>(new FragmentShader(sourceCode)) {}
////			};
////			struct ProgramRef : private std::shared_ptr<Program>
////			{
////				ProgramRef(VertexShaderRef const vertexShader, FragmentShaderRef const fragmentShader) : std::shared_ptr<Program>(new Program(*vertexShader, *fragmentShader)) {}
////			};
////			typedef		std::shared_ptr<Program>			ProgramRef;
////			typedef		std::shared_ptr<VertexShader>		VertexShaderRef;
////			typedef		std::shared_ptr<FragmentShader>		FragmentShaderRef;
////			typedef		std::shared_ptr<PlanarTexture>		PlanarTextureRef;
////			typedef		std::shared_ptr<ArrayBuffer>		ArrayBufferRef;
////			typedef		std::shared_ptr<ElementArrayBuffer>	ElementArrayBufferRef;
//			
//			/*!
//			 Represents remote server machine.
//			 This manages resources by owning them.
//			 */
//			class
//			Machine
//			{
//			public:
//				void					preloadProgramForKey(Program const program, std::string const key);
//				void					postunloadProgramForKey(std::string const key);
//				
////				VertexShader const		vertexShaderByTransferringSourceCode(std::string const sourceCode);
////				FragmentShader const	fragmentShaderByTransferringSourceCode(std::string const sourceCode);
////				Program const					programByCombiningShaders(Program::VertexShader const vertexShader, Program::FragmentShader const fragmentShader);
//				
////				Texture const					textureByTransferringImage(Eonil::Improvisations::MediaEngine::Graphics::Texture const texture);
//				
////				void							performDrawingUsingProgram(Program const program, );
//
////				static Machine const* const	currentMachine();
////				static void					setCurrentMachine(Machine const* const machine);
//			};
	}
	
	
}}}}

#endif /* defined(__EonilGraphics__Machine__) */
