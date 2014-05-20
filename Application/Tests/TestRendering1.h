//
//  TestRendering1.h
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#ifndef __Application__TestRendering1__
#define __Application__TestRendering1__

#include <Eonil/MediaEngine/Graphics.h>
#include <Eonil/MediaEngine/Graphics_DEV.h>
#include <Eonil/MediaEngine/Graphics/Server/Utility/Functions.h>
#include "run.h"
#include "Bundle.h"
#include "TestCommon.h"

using namespace Eonil::Improvisations::MediaEngine::Mathematics;
using namespace Eonil::Improvisations::MediaEngine::Mathematics::Geometry;
using namespace Eonil::Improvisations::MediaEngine::Graphics;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Rendering;
using namespace Eonil::Improvisations::MediaEngine::Application;










/*!
 This tests extreme simple logic.
 All the drawing resources are intentionally loaded/unloaded for each frame.
 
 A picture will be drawin in quarter area of the screen. (client area)
 */
class
TestRendering1
{
	Scalar	r1	=	0;
	
public:
	auto
	mutate() -> void
	{
		r1	+=	0.01;
	}
	
	auto
	render(Stepping const& s) const -> void
	{
		Matrix4		world_to_screen_transform	=	s.frame().regulationTransformMatrix();
//		Matrix4		world_to_screen_transform	=	Matrix4::Utility::identity();
		str			tex_path					=	Bundle::main().pathForResource("", "TEX_TEST", "png");
		
		D2014R2::DebuggingInformationOverlayDrawer	_dbgd	{};
		D2014R2::SpriteDrawer						_sprd	{};
		
		PlanarTexture	_tex1	=	load_texture_from_png_image_at_path(tex_path);
		
		////
		
		Server::Utility::clear({1, 0, 1, 1});
		
		
		
		
		
		SpriteDrawer::FreeTransformInstance		inst1	=	{};
		inst1.transform		=	Matrix4::Utility::scaleWithUniformScalar(0.5);

		Matrix4	stm	=	Matrix4::Utility::scaleWithUniformScalar(0.25);
		Matrix4	rtm	=	Matrix4::Utility::rotationWithAxisAngle(AxisAngle{{0,0,1}, r1});
		Matrix4	ttm	=	Matrix4::Utility::translationWithVector({+0.1, +0.1, 0});
		SpriteDrawer::FreeTransformInstance		inst2	=	{};
		inst2.transform		=	ttm * rtm * stm;
		_sprd.drawInstances(_tex1, {inst1, inst2}, world_to_screen_transform, s.frame());
		
		_dbgd.drawNull(s.frame(), world_to_screen_transform, {0.25, 0.25, 0.25});
	}
	
	
	
	auto
	step(Stepping const& s) -> void
	{
		mutate();
		render(s);
	}
	
};














#endif /* defined(__Application__TestRendering1__) */
