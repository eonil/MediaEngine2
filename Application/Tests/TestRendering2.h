//
//  TestRendering2.h
//  Application
//
//  Created by Hoon H. on 3/2/14.
//
//

#ifndef __Application__TestRendering2__
#define __Application__TestRendering2__


#include <Eonil/Improvisations/MediaEngine/Graphics/Graphics.h>
#include <Eonil/Improvisations/MediaEngine/Graphics/Graphics_DEV_.h>
#include <Eonil/Improvisations/MediaEngine/Graphics/Server/Utility/Functions.h>

#include <Eonil/Aliens.h>

#include "run.h"
#include "Bundle.h"

using namespace Eonil::Improvisations::MediaEngine::Mathematics;
using namespace Eonil::Improvisations::MediaEngine::Mathematics::Value;
using namespace Eonil::Improvisations::MediaEngine::Graphics;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Rendering;
using namespace Eonil::Improvisations::MediaEngine::Application;








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
}






class
TestRendering2
{
	Scalar				r1	=	0;

	D2014R2::DebuggingInformationOverlayDrawer	_dbgd{};
	D2014R2::SpriteDrawer						_sprd{};
	uptr<PlanarTexture>							_tex1{};

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
		Matrix4		world_to_screen_transform	=	s.frame().regulationTransformMatrix();
		
		////
		
		Server::Utility::clear({0, 0.5, 1, 1});

		SpriteDrawer::UniformScalingInstance	inst1{};
		inst1.scale			=	0.5;

		SpriteDrawer::UniformScalingInstance	inst2{};
		inst2.scale			=	0.25;
		inst2.rotation		=	Quaternion::Utility::quaternionWithAxisAngle(AxisAngle{{0,0,1}, r1});
		inst2.translation	=	{+0.1, +0.1, 0};
		_sprd.drawInstances(*_tex1, {inst1, inst2}, world_to_screen_transform, s.frame());

		_dbgd.drawNull(s.frame(), world_to_screen_transform, {0.25, 0.25, 0.25});

		{
			_reg_poly_drawer.draw(_circle_instances, world_to_screen_transform, s.frame());
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
