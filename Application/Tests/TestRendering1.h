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
#include <Eonil/Improvisations/MediaEngine/Graphics/Stub/GL-Context.h>
#include <Eonil/Improvisations/MediaEngine/Graphics/Server/Utility/Functions.h>

#include "run.h"
#include "Bundle.h"

using namespace Eonil::Improvisations::MediaEngine::Mathematics;
using namespace Eonil::Improvisations::MediaEngine::Mathematics::Value;
using namespace Eonil::Improvisations::MediaEngine::Graphics;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Stub;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Server;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Rendering;
using namespace Eonil::Improvisations::MediaEngine::Application;

class
TestRendering1
{
	
public:
	auto
	render(Stepping const& s) const -> void
	{
		Server::Utility::clear({1, 0, 1, 1});
		
		str		tex_path	=	Bundle::main().pathForResource("", "TEX_TEST", "png");
		
		D2014R2::DebuggingInformationOverlayDrawer	_dbgd	{};
		D2014R2::SpriteDrawer						_sprd	{};
		PlanarTexture								_tex1	{PlanarTexture::Utility::textureWithContentOfFileAtPath(tex_path)};
		
		_dbgd.drawNull(s.frame(), Matrix4::Utility::identity());

		
		SpriteDrawer::UniformScalingInstance	inst1{};
		inst1.scale	=	1;
		_sprd.drawInstances(_tex1, {inst1}, Matrix4::Utility::identity(), s.frame());
	}
};














#endif /* defined(__Application__TestRendering1__) */
