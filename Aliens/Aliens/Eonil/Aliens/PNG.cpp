//
//  PNG.cpp
//  Aliens
//
//  Created by Hoon H. on 14/4/25.
//
//

#include "PNG.h"
#include "../../../LodePNG/Sources/lodepng.h"

EONIL_ALIENS_NAMESPACE_BEGIN






namespace
{
	static inline auto
	_always_assert(bool cond, std::string const& message = "Failed to perform the operation.") -> void
	{
		if (not cond)
		{
			throw	PNG::Exception(message);
		}
	}
}

auto
PNG::encode(const Eonil::Aliens::PNG::Image &image) -> Package
{
	_always_assert(image.width < std::numeric_limits<uint32_t>::max());
	_always_assert(image.height < std::numeric_limits<uint32_t>::max());
	
	uint32_t		w1	=	uint32_t(image.width);
	uint32_t		h1	=	uint32_t(image.height);
	
	lodepng::State	st1		{};
	lodepng_encoder_settings_init(&st1.encoder);
	st1.encoder.auto_convert		=	LAC_NO;		//	This is required to keep RGBA8888 format.
	st1.encoder.filter_palette_zero	=	0;
	st1.encoder.filter_strategy		=	LFS_ZERO;
	
	Package			p1		{};
	unsigned int	err1	{lodepng::encode(p1.data, image.pixels, w1, h1, st1)};
	
	_always_assert(err1 == 0, "Failed encoding image. An error occured.");
	
	return			p1;
}
auto
PNG::decode(const Eonil::Aliens::PNG::Package &package) -> Image
{
	Image			img1	{};
	unsigned int	w1	=	0;
	unsigned int	h1	=	0;
	unsigned int	err1	{lodepng::decode(img1.pixels, w1, h1, package.data)};
	
	_always_assert(err1 == 0, "Failed decoding image. An error occured.");
	
	img1.width	=	w1;
	img1.height	=	h1;
	
	return			img1;
}












EONIL_ALIENS_NAMESPACE_END