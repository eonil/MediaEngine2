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

#include "run.h"
#include "Bundle.h"

using namespace Eonil::Improvisations::MediaEngine::Mathematics;
using namespace Eonil::Improvisations::MediaEngine::Mathematics::Value;
using namespace Eonil::Improvisations::MediaEngine::Graphics;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Rendering;
using namespace Eonil::Improvisations::MediaEngine::Application;










class
TestRendering2
{
	Scalar				r1	=	0;
	
	D2014R2::DebuggingInformationOverlayDrawer	_dbgd{};
	D2014R2::SpriteDrawer						_sprd{};
	uptr<PlanarTexture>							_tex1{};
	
public:
	TestRendering2()
	{
		str		tex_path	=	Bundle::main().pathForResource("", "PIA14415_clip_1024", "png");
		_tex1				=	uptr<PlanarTexture>(new PlanarTexture(PlanarTexture::Utility::textureWithContentOfFileAtPath(tex_path)));
	}
	
	auto
	mutate() -> void
	{
		r1	+=	0.01;
	}
	
	auto
	render(Stepping const& s) const -> void
	{
		Matrix4		world_to_screen_transform	=	s.frame().regulationTransformMatrix();
		
		////
		
		Server::Utility::clear({1, 0, 1, 1});
		
		SpriteDrawer::UniformScalingInstance	inst1{};
		inst1.scale			=	0.5;
		
		SpriteDrawer::UniformScalingInstance	inst2{};
		inst2.scale			=	0.25;
		inst2.rotation		=	Quaternion::Utility::quaternionWithAxisAngle(AxisAngle{{0,0,1}, r1});
		inst2.translation	=	{+0.1, +0.1, 0};
		_sprd.drawInstances(*_tex1, {inst1, inst2}, world_to_screen_transform, s.frame());
		
		_dbgd.drawNull(s.frame(), world_to_screen_transform, {0.25, 0.25, 0.25});
	}
	
	
	
	auto
	step(Stepping const& s) -> void
	{
		mutate();
		render(s);
	}
	
};













#endif /* defined(__Application__TestRendering2__) */