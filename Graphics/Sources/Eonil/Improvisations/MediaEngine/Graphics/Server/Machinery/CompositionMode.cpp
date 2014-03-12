//
//  CompositionMode.cpp
//  Graphics
//
//  Created by Hoon H. on 2/27/14.
//
//

#include "CompositionMode.h"

#include "../../Stub/GL-Common.h"
#include "../../Stub/GL-Context.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		class
		Machine;
		
		namespace
		Machinery
		{
			using namespace	Stub;
			
			
			namespace
			{
				
				class
				DEBUG_FLAG_SLOT
				{
#if	EONIL_MEDIA_ENGINE_DEBUG_MODE
					bool	f	{false};
#endif
					
				public:
					auto
					should_be_on_now() const -> void
					{
						EONIL_DEBUG_ASSERT(f == true);
					}
					auto
					should_be_off_now() const -> void
					{
						EONIL_DEBUG_ASSERT(f == false);
					}
					auto
					set_on() -> void
					{
						EONIL_DEBUG_ASSERT(f == false);
						EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN
						({
							f	=	true;
						});
					}
					auto
					set_off() -> void
					{
						EONIL_DEBUG_ASSERT(f == true);
						EONIL_MEDIA_ENGINE_DEBUG_ONLY_RUN
						({
							f	=	false;
						});
					}
				};
				
				

				static
				struct
				{
				
					DEBUG_FLAG_SLOT		scissor			{};
					DEBUG_FLAG_SLOT		stencil_test	{};
					DEBUG_FLAG_SLOT		depth_test		{};
					DEBUG_FLAG_SLOT		blending		{};
					DEBUG_FLAG_SLOT		dithering		{};
				}
				_dbg_gl_state_palette;
				
				
				static	DEBUG_FLAG_SLOT	_dbg_singleton_instance_exists	{};
				static	DEBUG_FLAG_SLOT	_dbg_the_instance_locked		{};
			}




			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			auto
			CompositionMode::PixelBlending::typicalTransparencyAlphaBlending() -> PixelBlending
			{
				PixelBlending	pb1	{};
				pb1.alpha.sourceFactor		=	PixelBlending::FUNCTION::SRC_ALPHA;
				pb1.alpha.destinationFactor	=	PixelBlending::FUNCTION::ONE_MINUS_SRC_ALPHA;
				pb1.rgb.sourceFactor		=	PixelBlending::FUNCTION::SRC_ALPHA;
				pb1.rgb.destinationFactor	=	PixelBlending::FUNCTION::ONE_MINUS_SRC_ALPHA;
				return	pb1;
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			CompositionMode::CompositionMode()
			{
				_dbg_singleton_instance_exists.should_be_off_now();
				{
					_dbg_gl_state_palette.dithering.set_on();		//	Dithering is initially on.
				}
				_dbg_singleton_instance_exists.set_on();
			}
			CompositionMode::~CompositionMode()
			{
				_dbg_singleton_instance_exists.should_be_on_now();
				{
				}
				_dbg_singleton_instance_exists.set_off();
			}
			
			
			
			
			auto CompositionMode::
			setScissorTesting(Bounds2 const bounds) -> void
			{
				_dbg_gl_state_palette.scissor.should_be_off_now();
				EONIL_DEBUG_ASSERT(not bounds.isNaN());
				EONIL_DEBUG_ASSERT(bounds != Bounds2::Utility::infinity());
				{
					Vector2	sz	=	bounds.size();
					eeglEnable(GL_SCISSOR_TEST);
					eeglScissor(bounds.minimum.x, bounds.minimum.y, sz.x, sz.y);
				}
				_dbg_gl_state_palette.scissor.set_on();
			}
			auto CompositionMode::
			unsetScissorTesting() -> void
			{
				_dbg_gl_state_palette.scissor.should_be_on_now();
				{
					eeglDisable(GL_SCISSOR_TEST);
				}
				_dbg_gl_state_palette.scissor.set_off();
			}
			
			
			
			
			auto CompositionMode::
			setStencilTest(StencilTest const& definition) -> void
			{
				_dbg_gl_state_palette.stencil_test.should_be_off_now();
				{
					eeglEnable(GL_STENCIL_TEST);
					GLenum	face	=	GLenum(definition.faceSelection);
					GLenum	func	=	GLenum(definition.comparisonFunction);
					eeglStencilFuncSeparate(face, func, definition.referenceValue, definition.maskingValue);
					eeglStencilOpSeparate(face, GLenum(definition.operations.whenStencilTestFails), GLenum(definition.operations.whenDepthTestFails), GLenum(definition.operations.whenDepthTestPasses));
				}
				_dbg_gl_state_palette.stencil_test.set_on();
			}
			auto CompositionMode::
			unsetStencilTest() -> void
			{
				_dbg_gl_state_palette.stencil_test.should_be_on_now();
				{
					eeglDisable(GL_STENCIL_TEST);
				}
				_dbg_gl_state_palette.stencil_test.set_off();
			}
			
			
			
			
			auto CompositionMode::
			setDepthTest(DepthTest const& definition) -> void
			{
				_dbg_gl_state_palette.depth_test.should_be_off_now();
				{
					eeglEnable(GL_DEPTH_TEST);
					eeglDepthFunc(GLenum(definition.function));
				}
				_dbg_gl_state_palette.depth_test.set_on();
			}
			auto CompositionMode::
			unsetDepthTest() -> void
			{
				_dbg_gl_state_palette.depth_test.should_be_on_now();
				{
					eeglDisable(GL_DEPTH_TEST);
				}
				_dbg_gl_state_palette.depth_test.set_off();
			}
			
			
			
			
			auto CompositionMode::
			setPixelBlending(PixelBlending const& definition) -> void
			{
				_dbg_gl_state_palette.blending.should_be_off_now();
				{
					eeglEnable(GL_BLEND);
					eeglBlendEquationSeparate(GLenum(definition.rgb.equation), GLenum(definition.alpha.equation));
					eeglBlendFuncSeparate(GLenum(definition.rgb.sourceFactor), GLenum(definition.rgb.destinationFactor), GLenum(definition.alpha.sourceFactor), GLenum(definition.alpha.destinationFactor));
					eeglBlendColor(definition.intensity.x, definition.intensity.y, definition.intensity.z, definition.intensity.w);
				}
				_dbg_gl_state_palette.blending.set_on();
			}
			auto CompositionMode::
			unsetPixelBlending() -> void
			{
				_dbg_gl_state_palette.blending.should_be_on_now();
				{
					eeglDisable(GL_BLEND);
				}
				_dbg_gl_state_palette.blending.set_off();
			}
			
			
			
			
			auto CompositionMode::
			setColorDithering() -> void
			{
				_dbg_gl_state_palette.dithering.should_be_off_now();
				{
					eeglEnable(GL_DITHER);
				}
				_dbg_gl_state_palette.dithering.set_on();
			}
			auto CompositionMode::
			unsetColorDithering() -> void
			{
				_dbg_gl_state_palette.dithering.should_be_on_now();
				{
					eeglDisable(GL_DITHER);
				}
				_dbg_gl_state_palette.dithering.set_off();
			}
			












			auto CompositionMode::
			lock() -> void
			{
				_dbg_the_instance_locked.should_be_off_now();
				_dbg_the_instance_locked.set_on();
			}
			auto CompositionMode::
			unlock() -> void
			{
				_dbg_the_instance_locked.should_be_on_now();
				_dbg_the_instance_locked.set_off();
			}







		}
	}

}}}}