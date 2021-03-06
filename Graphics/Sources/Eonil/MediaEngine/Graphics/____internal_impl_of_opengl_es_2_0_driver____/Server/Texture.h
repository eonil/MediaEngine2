//
//  Texture.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#pragma once
//#include "../Resources/Image.h"
#include "../Server/ServerObjectProxy.h"
//#include "../Aliens/PlanarRGBAImageProxy.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN
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
	
//		using namespace	Resources;
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
	 You cannot create actual texture instance directly.
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
	Texture2D final : public ServerObjectProxy
	{
//			friend class	Machinery::TextureSampler;
		
		struct
		Core
		{
			GLuint				name	=	NULL_GL_NAME();
			
			Core();							//!	Create a new texture name.
			Core(GLuint const name);		//!	Use existing texture name.
			~Core();						//!	Delete the texture name.
		};
		
		uptr<Core>		_cptr	{nullptr};
		
		Texture2D(Core* const core);
		
		void			_assertNonEmptyState() const;

		
		
	public:
		struct
		Parameters
		{
			enum class
			FILTER : GLint
			{
				NEAREST	=	GL_NEAREST,
				LINEAR	=	GL_LINEAR,
			};
			
			enum class
			WRAP : GLint
			{
				CLAMP	=	GL_CLAMP_TO_EDGE,
				REPEAT	=	GL_REPEAT,
				MIRROR	=	GL_MIRRORED_REPEAT,
			};
			
			FILTER	minificationFilter	=	FILTER::NEAREST;
			FILTER	magnificationFilter	=	FILTER::NEAREST;
//				FILTER	mipmappingFilter	=	FILTER::NEAREST;	//!	Map-mapping is not supported yet.
			WRAP	horizontalWrapping	=	WRAP::REPEAT;		//!	Initial value is REPEAT. @ref https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
			WRAP	verticalWrapping	=	WRAP::REPEAT;		//!	Initial value is REPEAT. @ref https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
		};
		
	public:
		Texture2D();											//!	Creates an empty texture. (null, no server-side object)
		Texture2D(Texture2D const&) = delete;				//!	Copy prohibited.
		Texture2D(Texture2D&& other);						//!	Move allowed.
		~Texture2D();
		
		auto	operator=(Texture2D&&) -> Texture2D& = default;		//!	Move assignment allowed.
		
//			auto	transferData(Image const image) -> void;
		
		auto	empty() const -> bool;
		auto	name() const -> GLuint;
		
		auto	setParameters(Parameters const&) -> void;
		
	public:
		struct
		Utility
		{
			/*!
			 Creates a texture from RGBA8888 pixels. (LDR, 8-bits integer per channel x 4 channels, 32-bits per pixels)
			 
			 @param		flipInY
						Flips the image along the Y axis. Use this if you need to flip the image.
						In most cases (especially if you loaded an image using only this library)
						you don't need to set the value. 
			 
						**CAUTION** 
						This option is supported only with premultiplied-alpha images.
						If your image is straight-alpha, you must set this to `false`.
			 
			 @note
			 This function will use alpha channel as is. If you want premultiplied alpha, then you should premultiply
			 them yourself.
			 */
			static auto	textureWithPixels(GenericMemoryRange<void const> memory, sz const& width, sz const& height, bool const& flipInY = false) -> Texture2D;
			
			
			
			
			
			
			
			
//				EONIL_MEDIA_ENGINE_DEPRECATE()
//				static Texture2D	_DEV_textureWithResourceAtPath(std::string const path);											//!	The path can be absolute or relative path to resource root.
//				
//				/*!
//				 @param		flipInY
//							Flips the image along the Y axis. Use this if you need to flip the image.
//							In most cases (especially if you loaded an image using only this library)
//							you don't need to set the value. 
//				 
//							**CAUTION** 
//							This option is supported only with premultiplied-alpha images.
//							If your image is straight-alpha, you must set this to `false`.
//				 
//				 */
//				
//				EONIL_MEDIA_ENGINE_DEPRECATE()
//				static auto	textureWithAlienImage(Aliens::PlanarRGBAImageProxy const& image, bool const flipInY = false) -> Texture2D;
//				
//				/*!
//				 @param		flipInY
//							This parameter will be routed to `flipInY` parameter in `textureWithAlienImage` 
//							function. See the function's comment.
//				 */
//				EONIL_MEDIA_ENGINE_DEPRECATE()
//				static auto textureWithMemoryRangeContainingPNGData(GenericMemoryRange<UInt8 const> memory, bool const flipInY = false) -> Texture2D;
//				
//				EONIL_MEDIA_ENGINE_DEPRECATE()
//				static auto	textureWithContentOfFileAtPath(str const& filepath) -> Texture2D;
		};
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*!
	 3-D texture.
	 */
//		class
//		Texture3D
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

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END


