//
//  CompositionMode.h
//  Graphics
//
//  Created by Hoon H. on 2/27/14.
//
//

#ifndef __Graphics__CompositionMode__
#define __Graphics__CompositionMode__

#include "../../Common.h"
#include "../Symbols.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		class
		Machine;
		
		namespace
		Machinery
		{
			

			
			
			

			
			
			
			
			
			/*!
			 Defines pixel composition mode.
			 
			 @classdesign
			 You can set state freely, but you have to lock the state before drawing.
			 And you can't update state while it locked.
			 
			 -	Blending
			 -	Alpha blending
			 
			 If you want to use this class at anywhere, all of your GL state update must be
			 fully based on this class. If you mix other methods, then you will get undefined 
			 result.

			 @discussion
			 Managing correct graphics state is hard because OpenGL is fully mutable API.
			 We need illusion of immutable state.
			 
			 This object works as a kind of lock. This locks the graphics machine with some
			 specific state set, and prevents any of unexpected state changes. Of course only
			 within abstraction of this class. If you use lower-level GL functions directly, 
			 that's out of abstraction, and result undefined.
			 
			 Again, this is a sort of lock. You should make only one of this object at once.
			 Conceptually, this creates an illusion of multiple simultaneous drawing state,
			 but actually we have only one machine, so making more than one state will cause
			 a runtime assertion failure. The assertion is the only safety net, and you're
			 responsible not to make more than one instance.
			 */
			class
			CompositionMode
			{
				friend class	Server::Machine;
				
				bool			_locked		{false};
				
				
				
				
				
				
				
				
				
				
			public:
				
				/*!
				 Initial states are set to values defined in standard <Version 2.0.25 (November 2, 2010)>.
				 */
				struct
				StencilTest
				{
					FACE			faceSelection		{FACE::BOTH};
					COMPARISON		comparisonFunction	{COMPARISON::ALWAYS};
					GLint			referenceValue		{0x0};
					GLuint			maskingValue		{~(GLuint(0x0))};			//	The standard <Version 2.0.25 (November 2, 2010)> says; "... and the front and back stencil mask are both all ones." It's vague that, it means `0x1` or `0xFFFF...` but I believe the intention was `0xFFFF...`.
					
					struct
					{
						OPERATION		whenStencilTestFails	{OPERATION::KEEP};
						OPERATION		whenDepthTestFails		{OPERATION::KEEP};
						OPERATION		whenDepthTestPasses		{OPERATION::KEEP};
					}
					operations;
				};

				struct
				DepthTest
				{
					COMPARISON		function	{COMPARISON::LESS};
					
					DepthTest() {}
					DepthTest(COMPARISON const& function) : function(function) {}
				};
				struct
				PixelBlending
				{
					enum class
					MODE
					{
						ADD							=	GL_FUNC_ADD,
						SUBTRACT					=	GL_FUNC_SUBTRACT,
						REVERSE_SUBTRACT			=	GL_FUNC_REVERSE_SUBTRACT,
					};
					
					enum class
					FUNCTION
					{
						ZERO						=	GL_ZERO,
						ONE							=	GL_ONE,
						SRC_COLOR					=	GL_SRC_COLOR,
						ONE_MINUS_SRC_COLOR			=	GL_ONE_MINUS_SRC_COLOR,
						DST_COLOR					=	GL_DST_COLOR,
						ONE_MINUS_DST_COLOR			=	GL_ONE_MINUS_DST_COLOR,
						SRC_ALPHA					=	GL_SRC_ALPHA,
						ONE_MINUS_SRC_ALPHA			=	GL_ONE_MINUS_SRC_ALPHA,
						DST_ALPHA					=	GL_DST_ALPHA,
						ONE_MINUS_DST_ALPHA			=	GL_ONE_MINUS_DST_ALPHA,
						CONSTANT_COLOR				=	GL_CONSTANT_COLOR,
						ONE_MINUS_CONSTANT_COLOR	=	GL_ONE_MINUS_CONSTANT_COLOR,
						CONSTANT_ALPHA				=	GL_CONSTANT_ALPHA,
						ONE_MINUS_CONSTANT_ALPHA	=	GL_ONE_MINUS_CONSTANT_ALPHA,
						SRC_ALPHA_SATURATE			=	GL_SRC_ALPHA_SATURATE,
					};
					
					struct
					ChannelConfiguration
					{
						MODE		equation				{MODE::ADD};
						FUNCTION	sourceFactor			{FUNCTION::ONE};
						FUNCTION	destinationFactor		{FUNCTION::ZERO};
					};
					
					ChannelConfiguration	rgb			{};				//!	RGB part.
					ChannelConfiguration	alpha		{};				//!	A part.
					
//					template <typename T>
//					struct
//					ChannelConfiguration
//					{
//						T	rgb			{};
//						T	alpha		{};
//						
//						ChannelConfiguration() = delete;
//						ChannelConfiguration(T rgba) : rgb(rgba), alpha(rgba) {}
//						ChannelConfiguration(T rgb, T alpha) : rgb(rgb), alpha(alpha) {}
//					};
//					
//					ChannelConfiguration<FUNCTION>		source		{FUNCTION::ONE, FUNCTION::ONE};
//					ChannelConfiguration<FUNCTION>		destination	{FUNCTION::ONE, FUNCTION::ONE};
//					ChannelConfiguration<MODE>			equation	{MODE::ADD, MODE::ADD};
					
					Vector4								intensity	{0,0,0,0};		//!	Each color channel components should be all clamped value.
					
					////
					
					/*!
					 Create alpha-blening parameters to render tranparency using alpha channel.
					 
					 @param			premultiplication
									If true, then blending option will be set to render premultiplied alpha correctly.
					 */
					static auto		transparencyNormalAlphaBlending(bool const premultiplication = false) -> PixelBlending;
					static auto		transparencyScreenAlphaBlending() -> PixelBlending;
					
					
					/*!
					 @deprecated	DO NOT USE.
					 */
					EONIL_MARK_FUNCTION_DEPRECATED static auto		typicalTransparencyAlphaBlending() -> PixelBlending;
				};
				
				
				
//				struct
//				ColorChannelWritingMask
//				{
//					bool	red		{true};
//					bool	green	{true};
//					bool	blue	{true};
//					bool	alpha	{true};
//					
//					ColorChannelWritingMask() {}
//					ColorChannelWritingMask(bool const& red, bool const& green, bool const& blue, bool const& alpha) : red(red), green(green), blue(blue), alpha(alpha) {}
//				};
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
				
			public:
				CompositionMode();
				~CompositionMode();
				
			public:
				/*
				 Per-fragment operations.
				 */
				
				/*!		
				 Scissor test is initially off.
				 
				 @param	bounds
				 All parameters must be an integer number. Any non-integer number will be an exception.
				 
				 @ref	"Initially, the scissor test is disabled." - p.93, <OpenGL ES 2.0 Full Specification, Version 2.0.25 (November 2, 2010)>
				 */
				auto	setScissorTesting(Bounds2 const bounds) -> void;
				auto	unsetScissorTesting() -> void;
				
				/*!
				 Stencil-test is initially off.
				 
				 @ref	"In the initial state, stenciling is disabled, ..." - p.95, <OpenGL ES 2.0 Full Specification, Version 2.0.25 (November 2, 2010)>
				 */
				auto	setStencilTest(StencilTest const& definition) -> void;
				auto	unsetStencilTest() -> void;
				
				/*!
				 Depth-test is initially off.
				 
				 @ref	"In the initial state the function is LESS and the test is disabled." - p.96, <OpenGL ES 2.0 Full Specification, Version 2.0.25 (November 2, 2010)>
				 */
				auto	setDepthTest(DepthTest const& definition) -> void;
				auto	unsetDepthTest() -> void;
				
				/*!
				 Blending is initially off.
				 
				 @ref	"Initially, blending is disabled." - p.100, <OpenGL ES 2.0 Full Specification, Version 2.0.25 (November 2, 2010)>
				 */
				auto	setPixelBlending(PixelBlending const& definition) -> void;
				auto	unsetPixelBlending() -> void;
				
				/*!
				 Dithering is initially on.
				 
				 @ref	"Initially, dithering is enabled." - p.100, <OpenGL ES 2.0 Full Specification, Version 2.0.25 (November 2, 2010)>
				 */
				auto	setColorDithering() -> void;
				auto	unsetColorDithering() -> void;
				
				
				
				
				
				/*
				 Whole framebuffer operations.
				 
				 (commented out because currently I am not understanding what these are)
				 
				 */
			public:
//				auto	setColorMask(bool const& red, bool const& green, bool const& blue, bool const& alpha) -> void;
//				auto	unsetColorMask() -> void;
//				
//				auto	setDepthMask() -> void;
//				auto	unsetColorMask() -> void;
//				
//				auto	setStencilMask(FACE const& face, GLuint const& mask) -> void;
//				auto	unsetColorMask() -> void;
				
				
				
				
				
				
			public:
				auto	lock() -> void;			//!	Locks the composition mode to allow drawing. You can draw only while this is locked.
				auto	unlock() -> void;		//!	Unlocks the composition mode to modify state. You cannot draw while this is unlocked.
			};
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__CompositionMode__) */
