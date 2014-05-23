//
//  Common.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#pragma once

#include	<Eonil/Improvisations/CommonUtility/CommonUtility.h>
#include	<Eonil/MediaEngine/Foundation.h>
#include	<Eonil/MediaEngine/Mathematics.h>


#define		EEGL_ASSERT(condexpr)							{ if(Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::useStateValidation()) { Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::assertWithReason(condexpr); }}
#define		EEGL_ASSERT_WITH_REASON(condexpr,reason)		{ if(Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::useStateValidation()) { Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::assertWithReason(condexpr,reason); }}

#define		EEGL_ASSERT_NO_GL_ERROR()						{ if(Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::useStateValidation()) { Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::assertNoGLError(); }}
#define		EEGL_RUN_AS_ASSERTION(stmt)						{ if(Eonil::Improvisations::MediaEngine::Graphics::Debugging::Doctor::useStateValidation()) { stmt; } }

#define	EONIL_MEDIA_ENGINE_GRAPHICS_STUB2_NAMESPACE_BEGIN					namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics { namespace Stub2 {
#define	EONIL_MEDIA_ENGINE_GRAPHICS_STUB2_NAMESPACE_END						} } } } }

#define	EONIL_MEDIA_ENGINE_GRAPHICS_RESOURCES_NAMESPACE_BEGIN				namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics { namespace Resources {
#define	EONIL_MEDIA_ENGINE_GRAPHICS_RESOURCES_NAMESPACE_END					} } } } }

#define	EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN		namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics { namespace Rendering { namespace D2014R2 {
#define	EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END			} } } } } }





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












namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
//	struct
//	NoCopyNoMoveObject
//	{
//		NoCopyNoMoveObject() = default;
//		
//		NoCopyNoMoveObject(NoCopyNoMoveObject const&) = delete;
//		NoCopyNoMoveObject(NoCopyNoMoveObject&) = delete;
//		NoCopyNoMoveObject(NoCopyNoMoveObject const&&) = delete;
//		NoCopyNoMoveObject(NoCopyNoMoveObject&&) = delete;
//	};
	
	struct
	NoCopyButMoveObject
	{
		NoCopyButMoveObject() {};
		
		NoCopyButMoveObject(NoCopyButMoveObject const&) = delete;
//		NoCopyButMoveObject(NoCopyButMoveObject&) = delete;
		
//		NoCopyButMoveObject(NoCopyButMoveObject const&&) = delete;
		NoCopyButMoveObject(NoCopyButMoveObject&&) = default;
		
		auto	operator=(NoCopyButMoveObject const&) -> NoCopyButMoveObject& = delete;
		auto	operator=(NoCopyButMoveObject&&) -> NoCopyButMoveObject& = default;
	};

	
	
	
	
//	/*!
//	 Dense, sequential, contiguous array of element T.
//	 All the elements will be default-constructed at first. So T must 
//	 be default constructible.
//	 
//	 No copy or move operations are used.
//	 */
//	template <typename T>
//	class
//	DynamicArray final
//	{
//		T*		_elements	{nullptr};
//		Size	_count		{0};
//		
//	public:
//		DynamicArray() = default;
//		DynamicArray(Size const count) : _elements(new T[count])
//		{
//		}
//		~DynamicArray()
//		{
//			delete[]	_elements;
//		}
//		
//		auto
//		size() const -> Size
//		{
//			return	_count;
//		}
//		auto
//		at(Size index) const -> T const&
//		{
//			EONIL_DEBUG_ASSERTION(index < _count);
//			return	_elements[index];
//		}
//		auto
//		at(Size index) -> T&
//		{
//			EONIL_DEBUG_ASSERTION(index < _count);
//			return	_elements[index];
//		}
//	};
	
}}}}

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	using		Size				=	Eonil::Improvisations::MediaEngine::Foundation::Size;
//	using		Memory				=	Eonil::Improvisations::MediaEngine::Foundation::_Legacy2013::SharedMemory;
//	using		UniqueByteMemoryBlock				=	Foundation::D2014R1::UniqueByteMemoryBlock;
	
	
	using namespace Eonil::Improvisations::CommonUtility;
	using namespace	Eonil::Improvisations::MediaEngine::Foundation;
	using namespace	Eonil::Improvisations::MediaEngine::Foundation::D2014R1;
	using namespace Eonil::Improvisations::MediaEngine::Mathematics;
	using namespace Eonil::Improvisations::MediaEngine::Mathematics::Geometry;
	

	
	
	
	
	
	
	
	
	

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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}}}}

















