//
//  Texture.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__Texture__
#define __EonilGraphics__Texture__

#include "../Resource/Image.h"
#include "_Legacy2013Compat.h"
#include "../Aliens/PlanarRGBAImageProxy.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Platform
	{
		namespace
		D2014R1
		{
			class
			NativeImage;
		}
	}
	
	namespace
	Server
	{
//			namespace
//			Machinery
//			{
//				struct
//				TextureSampler;
//			}
		
		using namespace	Resource;
		using namespace Platform::D2014R1;
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		/*!
		 1-D texture.
		 */
//			class
//			LinearTexture
//			{
//				
//			};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		/*!
		 2-D texture.
		 
		 
		 
		 @classdesign
		 You cannot create actualy texture instance directly.
		 Instead, use one of static utility methods.
		 
		 The destructor is not virtual by default. Subclassing this class might be dangerous,
		 and that's why this class is finalized.
		 
		 A texture interface is fully immutable, so you have no way to modify its content.
		 Anyway, media engine can update its content internally. (e.g. render to texture)
		 
		 
		 
		 @note
		 Texture is GL level object. So there's no support for auto-flipping on Y axis.
		 Always follows GL's default coordination system. (+Y is up)
		 
		 
		 
		 @discussion
		 Currently, MediaEngine require OpenGL ES 2.0 hardware, and future features may not be
		 supported.
		 
		 
		 
		 @ref
		 OpenGL ES 3.0 has full NPOT support in core; ES 2.0 has limited NPOT support (no
		 mipmaps, no Repeat wrap mode) in core; and ES 1.1 has no NPOT support.
		 http://aras-p.info/blog/2012/10/17/non-power-of-two-textures/
		 */
		class
		PlanarTexture final : public ServerObjectProxy
		{
			
//			friend class	Machinery::TextureSampler;
			
			struct	Core;
			
			uptr<Core>		_cptr	{nullptr};					//!	`std::uniqur_ptr` doesn't work due to size requirement for incomplete type.
			
			PlanarTexture(Core* const core);
			
			void			_assertNonEmptyState() const;
	
			
			
		public:
			PlanarTexture();									//!	Creates an empty texture.
			PlanarTexture(PlanarTexture const&) = delete;		//!	Copy prohibited.
			PlanarTexture(PlanarTexture&& other);				//!	Move allowed.
			~PlanarTexture();
			
//			auto	transferData(Image const image) -> void;
			
			auto	empty() const -> bool;
			auto	name() const -> GLuint;
			
		public:
			struct
			Utility
			{
				static PlanarTexture	_DEV_textureWithResourceAtPath(std::string const path);											//!	The path can be absolute or relative path to resource root.
				
				static auto	textureWithAlienImage(Aliens::PlanarRGBAImageProxy const& image, bool const flipInY = false) -> PlanarTexture;
				static auto textureWtihMemoryRangeContainingPNGData(GenericMemoryRange<UInt8> const& memory, bool const flipInY = false) -> PlanarTexture;
				static auto	textureWithContentOfFileAtPath(str const& filepath) -> PlanarTexture;
			};
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		/*!
		 3-D texture.
		 */
//		class
//		SpatialTexture
//		{
//			
//		};
		
		
		/*!
		 Environment mapping texture.
		 */
		class
		CubeMapTexture 
		{
		public:
			enum class
			SIDE
			{
				POSITIVE_X	=	GL_TEXTURE_CUBE_MAP_POSITIVE_X,
				POSITIVE_Y	=	GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
				POSITIVE_Z	=	GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
				NAGATIVE_X	=	GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
				NAGATIVE_Y	=	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
				NAGATIVE_Z	=	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			};
			
		public:
			
			
			CubeMapTexture(CubeMapTexture const&) = delete;
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
}}}}

#endif /* defined(__EonilGraphics__Texture__) */
