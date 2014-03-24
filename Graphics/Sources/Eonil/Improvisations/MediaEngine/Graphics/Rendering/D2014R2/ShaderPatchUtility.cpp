//
//  ShaderPatchUtility.cpp
//  Graphics
//
//  Created by Hoon H. on 3/24/14.
//
//

#include "ShaderPatchUtility.h"

#include "../../Stub/GL.h"
#include "../../Server/Shader.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			using namespace	Server;
			
			
			
			
	
			
			auto ShaderPatchUtility::
			programWithPatch(const str &vertexShaderCode, const str &fragmentShaderCode) -> Program
			{
#if			EONIL_MEDIA_ENGINE_TARGET_OPENGLDT_3_2
				str	vs_prefix_macros	=
#	include		"Common.shader.glsl-dt-1_10"
#	include		"Common.vertex.shader.glsl-dt-1_10"
				;
				str	fs_prefix_macros	=
#	include		"Common.shader.glsl-dt-1_10"
#	include		"Common.fragment.shader.glsl-dt-1_10"
				;
				
				if (Stub::eeglGetVendorIsATI())
				{
					/*!
					 ATI driver bug. It reports `gl_MaxVertexUniformComponents` as quad multiplied value.
					 It must be divided by 4 to be the correct value.
					 */
					vs_prefix_macros	+=
#	include			"Common.vertex.shader.glsl-dt-1_10-ATI-driver-bug-fix"
					;
				}
				
#elif		EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
				str	vs_prefix_macros	=
#	include		"Common.shader.glsl-es-1_00"
#	include		"Common.vertex.shader.glsl-es-1_00"
				;
				str	fs_prefix_macros	=
#	include		"Common.shader.glsl-es-1_00"
#	include		"Common.fragment.shader.glsl-es-1_00"
				;
#else
#	error		EONIL_MEDIA_ENGINE_MISSING_IMPLEMENTATION_FOR_TARGET_PLATFORM
#endif
				
				str		vs_code_final	=	vs_prefix_macros + "\n" + vertexShaderCode;
				str		fs_code_final	=	fs_prefix_macros + "\n" + fragmentShaderCode;
				
				return	Program{VertexShader{vs_code_final}, FragmentShader{fs_code_final}};
			}








		}
	}

}}}}