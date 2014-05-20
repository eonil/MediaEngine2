//
//  AATestCommon.h
//  Testers
//
//  Created by Hoon H. on 14/5/21.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <Eonil/Aliens.h>
#include <Eonil/MediaEngine/Graphics.h>
#include <Eonil/MediaEngine/Graphics_DEV.h>

inline auto
load_all_data_from_path(std::string const& path) -> std::vector<uint8_t>
{
	using	iter	=	std::istreambuf_iterator<char>;
	
	std::ifstream			f1		{path};
	std::vector<uint8_t>	v2	=	{iter(f1), iter()};
	
	return	v2;
}
inline auto
decode_pixels_from_png_data(std::vector<uint8_t> const& data) -> Eonil::Aliens::PNG::Image
{
	using namespace Eonil::Aliens;
	
	PNG::Package	p1	=	{};
	p1.data	=	data;
	
	return	PNG::decode(p1);
}
inline auto
load_png_image_from_path(std::string const& path) -> Eonil::Aliens::PNG::Image
{
	return	decode_pixels_from_png_data(load_all_data_from_path(path));
}
inline auto
load_texture_from_png_image_at_path(std::string const& path) -> Eonil::Improvisations::MediaEngine::Graphics::Server::PlanarTexture
{
	using	PT	=	Eonil::Improvisations::MediaEngine::Graphics::Server::PlanarTexture;
	
	auto			img1	=	load_png_image_from_path(path);
	PT	_tex1	=	PT::Utility::textureWithPixels({img1.pixels.data(), img1.pixels.data()+img1.pixels.size()}, img1.width, img1.height);
	return	_tex1;
}