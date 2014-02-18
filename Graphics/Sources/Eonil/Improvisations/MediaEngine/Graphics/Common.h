//
//  Common.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__Common__
#define __EonilGraphics__Common__

#include	<Eonil/Improvisations/CommonUtility/CommonUtility.h>
#include	<Eonil/Improvisations/MediaEngine/Foundation/Foundation.h>
#include	<Eonil/Improvisations/MediaEngine/Mathematics/Mathematics.h>


#define		EEGL_ASSERT(condexpr)							{ if(Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::useStateValidation()) { Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::assertWithReason(condexpr); }}
#define		EEGL_ASSERT_WITH_REASON(condexpr,reason)		{ if(Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::useStateValidation()) { Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::assertWithReason(condexpr,reason); }}

#define		EEGL_ASSERT_NO_GL_ERROR()						{ if(Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::useStateValidation()) { Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::assertNoGLError(); }}
#define		EEGL_RUN_AS_ASSERTION(stmt)						{ if(Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::useStateValidation()) { stmt; } }





#pragma mark	-	Platform Specific GL Inclusion

#if	EONIL_MEDIA_ENGINE_TARGET_IOS
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#endif

#if	EONIL_MEDIA_ENGINE_TARGET_OSX
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>
#endif

#if	EONIL_MEDIA_ENGINE_TARGET_ANDROID		//	Treat using of Apportable.
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#undef	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0
#define	EONIL_MEDIA_ENGINE_TARGET_OPENGLES_2_0				1
#endif










#define 	EEGL_INLINE 		


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
//	struct
//	NoCopyOrMoveObject
//	{
//		NoCopyOrMoveObject() = default;
//		
//		NoCopyOrMoveObject(NoCopyOrMoveObject const&) = delete;
//		NoCopyOrMoveObject(NoCopyOrMoveObject&) = delete;
//		NoCopyOrMoveObject(NoCopyOrMoveObject const&&) = delete;
//		NoCopyOrMoveObject(NoCopyOrMoveObject&&) = delete;
//	};
	
	struct
	NoCopyButMoveObject
	{
		NoCopyButMoveObject() {};
		
		NoCopyButMoveObject(NoCopyButMoveObject const&) = delete;
//		NoCopyButMoveObject(NoCopyButMoveObject&) = delete;
		
//		NoCopyButMoveObject(NoCopyButMoveObject const&&) = delete;
		NoCopyButMoveObject(NoCopyButMoveObject&&) {};
	};
	
}}}}

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	using		Size				=	Eonil::Improvisations::MediaEngine::Foundation::Size;
//	using		Memory				=	Eonil::Improvisations::MediaEngine::Foundation::_Legacy2013::SharedMemory;
	using		Legacy2013SharedMemory				=	Eonil::Improvisations::MediaEngine::Foundation::_Legacy2013::SharedMemory;
	
//	using		UniqueByteMemoryBlock				=	Foundation::D2014R1::UniqueByteMemoryBlock;
	
	
	
	template <typename T>
	using	sptr	=	std::shared_ptr<T>;
	
	template <typename T>
	using	uptr	=	std::unique_ptr<T>;
	
	using namespace Eonil::Improvisations::CommonUtility;
	using namespace	Eonil::Improvisations::MediaEngine::Foundation;
	using namespace	Eonil::Improvisations::MediaEngine::Foundation::D2014R1;
	using namespace Eonil::Improvisations::MediaEngine::Mathematics;
	using namespace Eonil::Improvisations::MediaEngine::Mathematics::Value;
	

//	namespace
//	Server
//	{
//	}
	
	
	namespace
	Server
	{
		class	Machine;
		
		class	Renderbuffer;
		class	Framebuffer;
		
		class	ArrayBuffer;
		class	ElementArrayBuffer;
		
		class	PlanarTexture;
		
		class	Program;
		class	VertexShader;
		class	FragmentShader;
		
	}

	namespace
	Rendering
	{
		class	FrameChannelImage;
		class	RenderingFrame;
		class	ColorDepthStencilRenderingPass;
		class	BloomEffectPass;
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__Common__) */















