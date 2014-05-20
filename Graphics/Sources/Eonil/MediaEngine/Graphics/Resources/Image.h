//
//  Image.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/13/13.
//
//

#pragma once
#include "../Common.h"
#include "../LEGACY/LEGACY_Common.h"
EONIL_MEDIA_ENGINE_GRAPHICS_RESOURCES_NAMESPACE_BEGIN

/*!
 Abstracted binary data.
 Content of image is opaque to external.
 
 Client can determine type of the content with type code,
 and can use proper decoder by type. Anyway there's no direct
 support for decoding of content.
 */
struct
EONIL_MEDIA_ENGINE_DEPRECATE()
Image
{
	struct
	TYPE
	{
		/*!
		 Type name can be one of these format.
		
			Unique symbol.
			List of semantic + subcomponent type.
		 
		 Subcomponent type can be one of these.
		 
			4				4-bit unsigned integer. (impliclty clamped)
			8				8-bit unsigned integer. (impliclty clamped)
			16				16-bit floating-point number.
			32				32-bit floating-point number.
		 
		 TODO:	
		 Clamping of floating-point numbers are not defined yet.
		 
		 */
		enum
		CODE
		{
			UNKNOWN,		//	The content type is unknown, that is invalid state.
			
//						M4F32,			//	Sequence of 4D matrixs built with 32-bit float.
//						V4F32,			//	Sequence of 4D vectors built with 32-bit float.
//						Q4F32,			//	Sequence of quaternions built with 32-bit float.
			
			R4G4B4A4,		//	Red+Green+Blue+Alpha. All subcomponents are 4-bit unsigned integer.
			R8G8B8A8,		//	Red+Green+Blue+Alpha. All subcomponents are 8-bit unsigned integer. Device specific extension is required.
			
			L16A16,			//	Luminance+Alpha. All subcomponents are 16-bit float. Device specific extension is required.
			L32A32,			//	Luminance+Alpha. All subcomponents are 32-bit float. Device specific extension is required.
			
			PVRTC,			//	Compressed. Only for PowerVR GPUs.
			ETC1,			//	Compressed. Support status unknown. http://en.wikipedia.org/wiki/Ericsson_Texture_Compression
		};
	};
	
	TYPE::CODE		type;
	Size			width;
	Size			height;
	Legacy2013SharedMemory			data;
	
//			public:
//				Image();														//	Creates an empty image.
//				Image(TYPE::CODE const type, Memory const data);
//				Image(Image const& origin);
//				
//				bool const				operator==(Image const& other) const = delete;
//				bool const				operator==(Image const& other) const;
	
public:
//				bool const				empty() const;
//				TYPE const				type() const;
//				Memory const&			data() const;
//				
//				//		public:
//				//			Data&					mutableData();
//				
//			private:
//				TYPE::CODE				_type;			//	Pixel data can be accessed directly from data if type is RGBA8888. Otherwise, any accessing to pixel data will cause encoding/decoding.
//				Memory					_data;			//	Source binary.
};

EONIL_MEDIA_ENGINE_GRAPHICS_RESOURCES_NAMESPACE_END
