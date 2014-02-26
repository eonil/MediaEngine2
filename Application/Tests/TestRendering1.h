//
//  TestRendering1.h
//  Application
//
//  Created by Hoon H. on 2/21/14.
//
//

#ifndef __Application__TestRendering1__
#define __Application__TestRendering1__

#include <Eonil/Improvisations/MediaEngine/Graphics/Graphics.h>
#include <Eonil/Improvisations/MediaEngine/Graphics/Server/Utility/Functions.h>

#include "run.h"
#include "Bundle.h"

using namespace Eonil::Improvisations::MediaEngine::Mathematics;
using namespace Eonil::Improvisations::MediaEngine::Mathematics::Value;
using namespace Eonil::Improvisations::MediaEngine::Graphics;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Rendering;
using namespace Eonil::Improvisations::MediaEngine::Application;

class
TestRendering1
{
	Scalar	r1	=	0;
	
public:
	auto
	step() -> void
	{
		r1	+=	0.01;
	}
	
	auto
	render(Stepping const& s) const -> void
	{
		Server::Utility::clear({1, 0, 1, 1});
		
		str		tex_path	=	Bundle::main().pathForResource("", "TEX_TEST", "png");
		
		D2014R2::DebuggingInformationOverlayDrawer	_dbgd	{};
		D2014R2::SpriteDrawer						_sprd	{};
		PlanarTexture								_tex1	{PlanarTexture::Utility::textureWithContentOfFileAtPath(tex_path)};
		
		
		
		
		
		SpriteDrawer::UniformScalingInstance	inst1{};
		SpriteDrawer::UniformScalingInstance	inst2{};
		inst2.scale			=	0.5;
		inst2.rotation		=	Quaternion::Utility::quaternionWithAxisAngle(AxisAngle{{0,0,1}, r1});
		inst2.translation	=	{+0.1, +0.1, 0};
		_sprd.drawInstances(_tex1, {inst1, inst2}, Matrix4::Utility::identity(), s.frame());
		
		_dbgd.drawNull(s.frame(), Matrix4::Utility::identity());
	}
};














#endif /* defined(__Application__TestRendering1__) */
