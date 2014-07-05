////
////  RegularPolygonDrawer.h
////  Graphics
////
////  Created by Hoon H. on 2/17/14.
////
////
//
//#pragma once
//#include "RenderingD2014R2Common.h"
//EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_BEGIN
//
//
//
//
///*!
// Draws filled/empty regular polygons and ellipses.
// 
// @brief
// Some applications needs to draw a lot of regular primitve shapes.
// This class support optimized way to draw them.
// */
//class
//RegularPolygonDrawer
//{
//	uptr<Server::Program>				_shader		{};
//	
//public:
//	struct
//	RegularInstance
//	{
//		Vector3			translation	{};
//		Scalar			scale		{};
//	};
//	
//	struct
//	ColoringInstance : RegularInstance
//	{
//		Vector4			color		{};
//	};
//	
////				struct
////				RotatingInstance : ColoringInstance
////				{
//////					Quaternion		rotation	{};
////				};
//	
//public:
//	RegularPolygonDrawer(sz const& numberOfSegments);
//	
//	/*!
//	 This draws 2x2 (radius = 1) sized circle at the origin with supplied transform.
//	 */
//	auto	drawInstances(vec<RegularInstance> const& instances) const -> void;
//	auto	drawInstances(vec<ColoringInstance> const& instances) const -> void;
////				auto	drawInstances(vec<RotatingInstance> const& instances) const -> void;
//};
//
//
//
//
//
//
//
//
//
//
//EONIL_MEDIA_ENGINE_GRAPHICS_RENDERING_D2014R2_NAMESPACE_END
//
