//
//  TestCommon.h
//  Application
//
//  Created by Hoon H. on 14/5/20.
//
//

#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <Eonil/Aliens.h>
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