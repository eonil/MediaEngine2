//
//  ____shader_patch_utility.h
//  Graphics
//
//  Created by Hoon H. on 3/24/14.
//
//

#pragma once
#include "RenderingD2014R2Common.h"
#include "RenderingD2014R2____internal____.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN





/*!
 Very unfortunately, GLSL programming world is total mess due to incompatible
 fragmentation. Also, GPU driver bugs suffers me.
 
 This utility functions provide a set of GLSL macros to provide compatibility 
 between GLSL (DT) and GLSL ES. And also to avoid the driver bugs.
 
 Shader code should be written with consideration of patching macros.
 
 @discussion
 This is mainly written to avoid GPU driver bugs.
 For example, ATI driver reports wrong number for vertex shader uniform limit.
 And that is impossible to avoid without some dynamic GLSL macro programming.
 
 -	ATI vertex shader uniform bug avoidance macro.
 */
namespace
____shader_patch_utility
{
	/*!
	 Each shader code must follow Eonil Media Engine's portability guideline. (not yet formally written)
	 Main consideration is adapting compatible macris. The major language is based on OpenGL ES 2.0 SL 1.00,
	 and use the macros defined in `Common~` files.
	 */
	auto	programWithPatch(str const& compatibleVertexShaderCode, str const& compatibleFragmentShaderCode) -> ____internal_impl_of_opengl_es_2_0_driver____::Server::Program;
};







EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END

