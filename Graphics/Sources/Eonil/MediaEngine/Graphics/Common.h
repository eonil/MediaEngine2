//
//  Common.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#pragma once

#include <Eonil/Common/age2/age2.h>
#include <Eonil/CommonRealtimeGameAlgorithms/CommonRealtimeGameAlgorithmsCommon.h>
#include <Eonil/MediaEngine/Foundation.h>
#include <Eonil/MediaEngine/Mathematics.h>


#define	EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN			namespace Eonil { namespace MediaEngine { namespace Graphics {
#define	EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END			} } }


//#define	EONIL_MEDIA_ENGINE_GRAPHICS_RESOURCES_NAMESPACE_BEGIN				namespace Eonil { namespace MediaEngine { namespace Graphics { namespace Resources {
//#define	EONIL_MEDIA_ENGINE_GRAPHICS_RESOURCES_NAMESPACE_END					} } } }





#pragma mark	-	Platform Specific GL Inclusion

#if	EONIL_MEDIA_ENGINE_TARGET_IOS
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#endif

#if	EONIL_MEDIA_ENGINE_TARGET_OSX
/*
 In OS X 10.8.x or earlier;
 
 The flag `GL_ARB_ES2_compatibility` just provides API compatibility, but actual behavior
 will not be changed. That means unsupported feature will cause a runtime exception, and 
 that means silent error ignore on compilation. A real big shit. I don't want that.
 It's funnay that the compatibility feature will be disabled when this flag is *defined* 
 instead of undefined.
 */
//#define	GL_ARB_ES2_compatibility
//#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

#if	EONIL_MEDIA_ENGINE_TARGET_APPORTABLE		//	Treat using of Apportable.
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#undef	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
#define	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0				1
#endif











#include <unordered_map>

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

using namespace	Eonil::Common::age2;
using namespace	Eonil::MediaEngine::Foundation;
using namespace	Eonil::MediaEngine::Foundation::D2014R1;
using namespace Eonil::MediaEngine::Mathematics;
using namespace Eonil::MediaEngine::Mathematics::Geometry;

template<typename K, typename V>	using	map		=	std::map<K,V>;
template<typename K, typename V>	using	umap	=	std::unordered_map<K,V>;

namespace
Rendering
{
	namespace
	D2014R2
	{
		class	DisplayScreenFrame;
	}
	
	//		class	FrameChannelImage;
	//		class	RenderingFrame;
	//		class	ColorDepthStencilRenderingPass;
	//		class	BloomEffectPass;
}

namespace
Utility
{
	inline namespace
	D2014R1
	{
		class	NativeDrawableSurface;
	}
	
	//		using namespace	D2014R1;
}

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END












