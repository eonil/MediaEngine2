//
//  Machine.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__Machine__
#define __EonilGraphics__Machine__

#include "../Common.h"
#include "Declarations.h"

#include "Machinery/CompositionMode.h"

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
			uptr<IndexUnitChannel>				_idxch_ptr;
			std::vector<TextureSampler>			_tus;
			
			CompositionMode						_comp_mode	{};
			
			Machine();
			Machine(Machine const& origin) = delete;					//	Copy prohibited.
			
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
			
			auto								useProgram(Program const& program) -> void;
			auto								unuseProgram() -> void;
			
			auto								executeBlockWithProgram(Program const& program, std::function<void()> block) -> void;
			
			void								setViewport(Bounds2 const bounds);		//!	Bounds in client windows coordinate space.
			void								unsetViewport();
			
			
			
			
			
			auto	compositionMode() const -> CompositionMode const&;
			auto	compositionMode() -> CompositionMode&;
			
			
			

			
			
			
			
			
			
			
			/*
			 Drawings.
			 */
		public:
//			void	drawArrays();																		//	Draws all data as triangle strip.
//			void	drawArrays(Size const index, Size const count);										//	Draws as triangle strip.
//			void	drawArrays(DrawingMode const mode);
			
			/*!
			 @param	index		Index of first vertex to start drawing. Not a byte offset.
			 
			 @param	count		Number of vertexes to be used for drawing.
								Ultimately this decides number of point/line/triangles to be drawn.
			 */
			auto	drawArrays(DrawingMode const mode, Size const index, Size const count) -> void;
			auto	drawElements(DrawingMode const mode, Size const index, Size const count) -> void;
//			void	drawElements(DrawingMode const mode, Size const count, Size const offset);
			

			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		public:
			std::string const					description() const;
//			bool const							validityOfVertexSourcing() const;
//			bool const							validityOfProgramDesignation() const;
			
		private:
			bool	_validity_of_viewport			=	false;
			bool	_dbg_has_scissor				=	false;
//			bool	_validity_vertex_sourcing		=	false;		//	False if vertex source is not configured well.
//			bool	_validity_index_sourcing		=	false;		//	False if index source is not configured well.
			bool	_validity_program_designation	=	false;
			
			
			
			
		public:
			EONIL_MEDIA_ENGINE_DEPRECATE_WITH_MESSAGE("Use `compositionMode` method.")	auto	setScissor(Bounds2 const bounds) -> void ;		//!	Bounds in client windows coordinate space.
			EONIL_MEDIA_ENGINE_DEPRECATE_WITH_MESSAGE("Use `compositionMode` method.")	auto	unsetScissor() -> void;
			
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
