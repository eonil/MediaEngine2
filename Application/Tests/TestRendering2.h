//
//  TestRendering2.h
//  Application
//
//  Created by Hoon H. on 3/2/14.
//
//

#ifndef __Application__TestRendering2__
#define __Application__TestRendering2__


#include <Eonil/MediaEngine/Graphics.h>
#include <Eonil/MediaEngine/Graphics_DEV.h>
#include <Eonil/MediaEngine/Graphics/____internal_impl_of_opengl_es_2_0_driver____/driver_all.h>
#include <Eonil/Aliens.h>

#include "run.h"
#include "Bundle.h"

using namespace Eonil::MediaEngine::Mathematics;
using namespace Eonil::MediaEngine::Mathematics::Geometry;
using namespace Eonil::MediaEngine::Graphics;
using namespace Eonil::MediaEngine::Graphics::Rendering;
using namespace Eonil::MediaEngine::Graphics::____internal_impl_of_opengl_es_2_0_driver____;
using namespace Eonil::MediaEngine::Application;








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
TestRendering2
{
	Scalar				r1	=	0;

	D2014R2::DebuggingInformationOverlayDrawer	_dbgd{};
	D2014R2::SpriteDrawer						_sprd{};
	uptr<PlanarTexture>							_tex1{};

	PlanarTexture			_tex2	=	load_texture_resource("TEX_TEST", "png");

	D2014R2::GPUTransformRegularPolygonDrawer				_reg_poly_drawer	{8};
	
	vec<GPUTransformRegularPolygonDrawer::VaryingInstance>	_circle_instances{};
	
public:
	TestRendering2(TestRendering2 const&) = delete;
	TestRendering2(TestRendering2&&) = delete;
	auto	operator=(TestRendering2) -> TestRendering2& = delete;
	auto	operator=(TestRendering2&&) -> TestRendering2& = delete;
	
	TestRendering2()
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
	}
	
	
	
	auto
	step(Stepping const& s) -> void
	{
		mutate();
		render(s);
	}
	
};













#endif /* defined(__Application__TestRendering2__) */
