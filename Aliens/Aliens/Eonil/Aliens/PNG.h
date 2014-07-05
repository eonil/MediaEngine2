//
//  PNG.h
//  Aliens
//
//  Created by Hoon H. on 14/4/25.
//
//

#pragma once

#include "Common.h"

EONIL_ALIENS_NAMESPACE_BEGIN






/*!
 @note
 This class supports only lossless 32-bit PNG file. (RGBA8888)
 Other subformats may be allowed and loadable, but not guaranteed to work with.
 
 @exception
 Throws `Exception` instances for any exceptions.
 Guarantees strong exception safety.
 */
class
PNG
{
public:
	class
	Exception : public std::logic_error
	{
	public:
		using	logic_error::logic_error;
	};
	
public:
	/*!
	 Represents uncompressed raw image.
	 The pixels must be widely used LDR RGBA format. 
	 (8-bit unsigned integer for four color channels, channels must be ordered in RGBA order)
	 Size of pixels must be matched to its dimensions. (size = width * height * 4)
	 */
	struct
	Image
	{
		size_t						width	{};
		size_t						height	{};
		std::vector<uint8_t>		pixels	{};
	};
	/*!
	 Represents compressed image using PNG algorithm.
	 */
	struct
	Package
	{
		std::vector<uint8_t>		data	{};
	};
	
public:
	/*!
	 @note
	 I intended to make losslessly encoded PNG file.
	 If it doesn't that's bug of this function.
	 */
	static auto		encode(Image const&) -> Package;
	static auto		decode(Package const&) -> Image;
};









EONIL_ALIENS_NAMESPACE_END