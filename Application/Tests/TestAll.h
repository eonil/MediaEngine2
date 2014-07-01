//
//  TestAll.h
//  Application
//
//  Created by Hoon H. on 2014/05/18.
//
//

#pragma once

#include <Eonil/MediaEngine/Graphics.h>
#include <Eonil/MediaEngine/Graphics_DEV.h>
#include <Eonil/MediaEngine/Graphics/Server/Utility/Functions.h>
#include "../Eonil/MediaEngine/Application/Application.h"
#include "../Eonil/MediaEngine/Controlling/Controlling.h"
#include <Eonil/Aliens.h>

#include "run.h"
#include "Bundle.h"

using namespace Eonil::Improvisations::MediaEngine::Mathematics;
using namespace Eonil::Improvisations::MediaEngine::Mathematics::Geometry;
using namespace Eonil::Improvisations::MediaEngine::Graphics;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Rendering;
using namespace Eonil::Improvisations::MediaEngine::Application;
using namespace Eonil::Improvisations::MediaEngine::Controlling;







namespace
{
	static inline auto
	load_texture(str const& filepath) -> PlanarTexture
	{
		NSString*	s1			=	[NSString stringWithUTF8String:filepath.c_str()];
		NSData*		d2			=	[NSData dataWithContentsOfFile:s1];
		
		Eonil::Aliens::PNG::Package	p1		=	{};
		p1.data								=	{((uint8_t const*)d2.bytes), ((uint8_t const*)d2.bytes)+d2.length};
		
		Eonil::Aliens::PNG::Image	img2	=	Eonil::Aliens::PNG::decode(p1);
		
		return	PlanarTexture::Utility::textureWithPixels({img2.pixels.data(), img2.pixels.data() + img2.pixels.size()}, img2.width, img2.height);
	}
	
	static inline auto
	load_texture_resource(str const& name, str const& type) -> PlanarTexture
	{
		str	p5	=	Bundle::main().pathForResource("", name, type);
		return	load_texture(p5);
	}
	
}






class
TestAll
{
	Scalar				r1	=	0;
	
	D2014R2::DebuggingInformationOverlayDrawer	_dbgd{};
	D2014R2::SpriteDrawer						_sprd{};
	uptr<PlanarTexture>							_tex1{};
	
	PlanarTexture			_tex2	=	load_texture_resource("TEX_TEST", "png");
	
	D2014R2::GPUTransformRegularPolygonDrawer	_reg_poly_drawer	=	{8};
	D2014R2::PolylineDrawer						_polyline_drawer	=	{};
	
	vec<GPUTransformRegularPolygonDrawer::VaryingInstance>	_circle_instances{};
	
public:
	TestAll(TestAll const&) = delete;
	TestAll(TestAll&&) = delete;
	
	auto	operator=(TestAll const&) -> TestAll& = delete;
	auto	operator=(TestAll&&) -> TestAll& = delete;
	
	TestAll()
	{
		using namespace	Eonil;
		
		str		tex_path	=	Bundle::main().pathForResource("", "PIA14415_clip_1024", "png");
		_tex1				=	uptr<PlanarTexture>(new PlanarTexture(load_texture(tex_path)));
		
		////
		
		vec<GPUTransformRegularPolygonDrawer::VaryingInstance>	insts	=	{};
		size_t	w	=	20;
		size_t	h	=	20;
		for (size_t xi=0; xi<w; xi++)
		{
			for (size_t yi=0; yi<h; yi++)
			{
				Scalar	x	=	Scalar(xi) / Scalar(w) * 0.5;
				Scalar	y	=	Scalar(yi) / Scalar(h) * 0.5;
				Scalar	l	=	Scalar(rand()) / std::numeric_limits<int>::max();
				
				GPUTransformRegularPolygonDrawer::VaryingInstance	inst1	{};
				inst1.position	=	{x, y};
				inst1.boundary	=	{0,0};
				inst1.color		=	{l, l, l, 1};
				insts.push_back(inst1);
				
				_circle_instances	=	insts;
			}
		}
	}
	
	auto
	mutate() -> void
	{
		r1	+=	0.01;
		
		for (auto& a: _circle_instances)
		{
			a.boundary.inner	=	0.01 + sinf(r1 * 4.0) * 0.01;
			a.boundary.outer	=	a.boundary.inner + 0.0025;
		}
	}
	
	auto
	render(Stepping const& s) const -> void
	{
		Matrix4 const		world_to_screen_transform	=	Matrix4::Utility::scaleWithUniformScalar(2) * s.frame().regulationTransformMatrix();
		
		////
		
		Server::Utility::clear({0, 0.5, 1, 1});
		
		{
			SpriteDrawer::FreeTransformInstance		inst1{};
			inst1.transform		=	Matrix4::Utility::scaleWithUniformScalar(0.5);
			
			SpriteDrawer::FreeTransformInstance		inst2{};
			Matrix4		stm		=	Matrix4::Utility::scaleWithUniformScalar(0.25);
			Matrix4		rtm		=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle{{0,0,1}, r1});
			Matrix4		ttm		=	Matrix4::Utility::translationWithScalars(+0.1, +0.1, 0);
			Matrix4		atm		=	ttm * rtm * stm;
			inst2.transform		=	atm;
			_sprd.drawInstances(*_tex1, {inst1, inst2}, world_to_screen_transform, s.frame());
			
			_dbgd.drawNull(s.frame(), world_to_screen_transform, {0.25, 0.25, 0.25});
			
			{
				_reg_poly_drawer.draw(_circle_instances, world_to_screen_transform, s.frame());
			}
			
		}
		{
			Bounds2	r2	=	{0.4, 0.4, 0.6, 0.6};
			vec<SpriteDrawer::FreeTransformInstance>	insts1	=	{};
			SpriteDrawer::FreeTransformInstance	inst1	{};
			Matrix4		stm		=	Matrix4::Utility::scaleWithUniformScalar(1.0 / 8.0);
			Matrix4		rtm		=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle{{0,0,1}, r1});
			Matrix4		ttm		=	Matrix4::Utility::translationWithScalars(-0.25, +0.25, 0);
			Matrix4		atm		=	ttm * rtm * stm;
			inst1.transform		=	atm;
			inst1.color			=	{0,1,1,1};
			insts1.push_back(inst1);
			_sprd.drawInstances(_tex2, r2, insts1, world_to_screen_transform, s.frame());
		}

		{
			Matrix4	m1	=	Matrix4::Utility::translationWithScalars(+0.5, -0.5, 0);
			Matrix4	m2	=	world_to_screen_transform * m1;
			
			CPUTransformTriangleDrawer				trid	=	{};
			CPUTransformTriangleDrawer::Triangle	t1		=	{};
			CPUTransformTriangleDrawer::Triangle	t2		=	{};
			t1.points		=
			{
				Vector3{0,0,0},
				Vector3{0,+0.1,0},
				Vector3{-0.1,0,0},
			};
			t2.points		=
			{
				Vector3{0,+0.1,0},
				Vector3{0,+0.2,0},
				Vector3{-0.1,+0.1,0},
			};
			for (auto& p: t1.points)
			{
				p	=	m2.transform(p);
			}
			for (auto& p: t2.points)
			{
				p	=	m2.transform(p);
			}
			vec<CPUTransformTriangleDrawer::Triangle>	ts	=	{};
			ts.push_back(t1);
			ts.push_back(t2);
			trid.drawTriangleList({ts.data(), ts.data() + ts.size()}, {1,1,0,1});
		}
		{
			Matrix4 const	rss_to_ndc	=	world_to_screen_transform;
			{
				PolylineDrawer::StrokeInstance	inst0	=	{};
				inst0.points						=
				{
					Vector3{-0.3,-0.3,0},
					Vector3{-0.4,-0.45,0},
				};
				_polyline_drawer.draw(rss_to_ndc, {inst0}, 0.01, {1,1,1,1});
			}
			{
				PolylineDrawer::StrokeInstance	inst0	=	{};
				inst0.points						=
				{
					Vector3{0,0,0},
					Vector3{+0.1,0,0},
					Vector3{+0.2,+0.1,0},
					Vector3{+0.2,+0.3,0},
					Vector3{+0.1,+0.4,0},
					Vector3{+0.0,+0.4,0},
				};
				_polyline_drawer.draw(rss_to_ndc, {inst0}, 0.01, {1,1,1,1});
			}
			{
				PolylineDrawer::StrokeInstance	inst0	=	{};
				inst0.points						=
				{
					Vector3{0,0,0},
					Vector3{+0.1,0,0},
					Vector3{+0.2,0,0},
					Vector3{+0.3,0,0},
				};
				_polyline_drawer.draw(rss_to_ndc, {inst0}, 0.01, {1,1,1,1});
			}
			{
				PolylineDrawer::StrokeInstance	inst0	=	{};
				inst0.points						=
				{
					Vector3{0,0,0},
					Vector3{+0.1,-0.05,0},
					Vector3{+0.2,-0.10,0},
					Vector3{+0.3,-0.15,0},
				};
				_polyline_drawer.draw(rss_to_ndc, {inst0}, 0.01, {1,1,1,1});
			}
			{
				PolylineDrawer::StrokeInstance	inst0	=	{};
				inst0.points						=
				{
					Vector3{-0.2,0,0},
					Vector3{0,0,0},
					Vector3{+0.1,+0.1,0},
					Vector3{+0.1,+0.3,0},
					Vector3{+0.2,+0.4,0},
					Vector3{+0.4,+0.4,0},
				};
				_polyline_drawer.draw(rss_to_ndc, {inst0}, 0.01, {1,1,1,1});
			}
			{
				Matrix4	m1	=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle({0,0,1}, +0.3));
				Vector3	p1	=	{0,0.2,0};
				
				PolylineDrawer::StrokeInstance	inst0	=	{};
				for (size_t i=0; i<16; i++)
				{
					inst0.points.push_back(p1);
					p1	=	m1.transform(p1);
				}
				_polyline_drawer.draw(rss_to_ndc, {inst0}, 0.005, {1,1,1,1});
			}
			{
				Matrix4	m1	=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle({0,0,1}, M_PI * 2 / 128));
				Vector3	p1	=	{0,0.43,0};
				
				PolylineDrawer::StrokeInstance	inst0	=	{};
				for (size_t i=0; i<127; i++)
				{
					inst0.points.push_back(p1);
					p1	=	m1.transform(p1);
				}
				_polyline_drawer.draw(rss_to_ndc, {inst0}, 0.002, {1,1,1,1});
			}
		}
	}
	
	
	
	auto
	step(Stepping const& s) -> void
	{
		mutate();
		render(s);
	}
	
};












