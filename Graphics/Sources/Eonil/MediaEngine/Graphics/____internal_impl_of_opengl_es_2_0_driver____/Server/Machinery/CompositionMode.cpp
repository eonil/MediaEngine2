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
#include "../../../Debugging/DebugOnlyValidityFlagSlot.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

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
			using	DEBUG_FLAG_SLOT	=	Debugging::DebugOnlyValidityFlagSlotV1;
			
			
			

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




		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		namespace
		{
			using	PixelBlending	=	CompositionMode::PixelBlending;
			
			static auto
			straightTransparencyAlphaBlending() -> PixelBlending
			{
				PixelBlending	pb1	{};
				pb1.rgb.sourceFactor		=	PixelBlending::FUNCTION::SRC_ALPHA;
				pb1.alpha.sourceFactor		=	PixelBlending::FUNCTION::SRC_ALPHA;
				pb1.rgb.destinationFactor	=	PixelBlending::FUNCTION::ONE_MINUS_SRC_ALPHA;
				pb1.alpha.destinationFactor	=	PixelBlending::FUNCTION::ONE_MINUS_SRC_ALPHA;
				return	pb1;
			}
			
			static auto
			premultipliedTransparencyAlphaBlending() -> PixelBlending
			{
				PixelBlending	pb1	{};
				pb1.rgb.sourceFactor		=	PixelBlending::FUNCTION::ONE;
				pb1.alpha.sourceFactor		=	PixelBlending::FUNCTION::ONE;
				pb1.rgb.destinationFactor	=	PixelBlending::FUNCTION::ONE_MINUS_SRC_ALPHA;
				pb1.alpha.destinationFactor	=	PixelBlending::FUNCTION::ONE_MINUS_SRC_ALPHA;
				return	pb1;
			}
			
			static auto
			straight_screen_transparency_alpha_blending() -> PixelBlending
			{
				PixelBlending	pb1	{};
				pb1.rgb.sourceFactor		=	PixelBlending::FUNCTION::SRC_ALPHA;
				pb1.alpha.sourceFactor		=	PixelBlending::FUNCTION::SRC_ALPHA;
				pb1.rgb.destinationFactor	=	PixelBlending::FUNCTION::ONE;
				pb1.alpha.destinationFactor	=	PixelBlending::FUNCTION::ONE;
				return	pb1;
			}
		}
		
		
		
		auto
		CompositionMode::PixelBlending::transparencyNormalAlphaBlending(bool const premultiplication) -> PixelBlending
		{
			if (premultiplication)
			{
				return	premultipliedTransparencyAlphaBlending();
			}
			else
			{
				return	straightTransparencyAlphaBlending();
			}
		}
		auto
		CompositionMode::PixelBlending::transparencyScreenAlphaBlending() -> PixelBlending
		{
			return	straight_screen_transparency_alpha_blending();
		}
		
		auto
		CompositionMode::PixelBlending::typicalTransparencyAlphaBlending() -> PixelBlending
		{
			return	premultipliedTransparencyAlphaBlending();
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
			
			////
			if (USE_DEBUGGING_ASSERTIONS)
			{
				err9_converted_legacy_assertion(not bounds.isNaN());
				err9_converted_legacy_assertion(bounds != Bounds2::Utility::infinity());
			}
			////
			
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

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END

