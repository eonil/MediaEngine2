//
//  AATestStatus.cpp
//  EonilGraphicsRunningTester
//
//  Created by Hoon Hwangbo on 7/1/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "AATestStatus.h"






#include <vector>
#include <Eonil/Improvisations/MediaEngine/MediaEngine.h>
#include <Eonil/Improvisations/MediaEngine/MediaEngine_DEV_.h>

using namespace Eonil;
using namespace Eonil::Improvisations::MediaEngine::Graphics;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Value;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Stub;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Server;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Resource;
using namespace Eonil::Improvisations::MediaEngine::Graphics::Transcoding;



namespace
{
	void
	print(std::string desc, GLint value)
	{
		std::cout << desc;
		std::cout << ": ";
		std::cout << value;
		std::cout << "\n";
	}
}


void
TestStatus()
{
	using namespace	Eonil::Improvisations::MediaEngine::Graphics;
	using namespace	Eonil::Improvisations::MediaEngine::Graphics::Stub;
	
	GLint	cb_name		=	eeglGetFramebufferAttachmentParameteri(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
	GLint	db_name		=	eeglGetFramebufferAttachmentParameteri(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
	GLint	sb_name		=	eeglGetFramebufferAttachmentParameteri(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME);
	
	print("framebuffer name", eeglGetInteger(GL_FRAMEBUFFER_BINDING));
	print("color buffer name", cb_name);
	print("depth buffer name", db_name);
	print("stencil buffer name", sb_name);
	
	if (cb_name != 0)
	{
		eeglBindRenderbuffer(GL_RENDERBUFFER, cb_name);
		print("color buffer - width", eeglGetRenderbufferParameteri(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH));
		print("color buffer - height", eeglGetRenderbufferParameteri(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT));
		print("color buffer - green size", eeglGetRenderbufferParameteri(GL_RENDERBUFFER, GL_RENDERBUFFER_GREEN_SIZE));
		print("color buffer - blue size", eeglGetRenderbufferParameteri(GL_RENDERBUFFER, GL_RENDERBUFFER_BLUE_SIZE));
		print("color buffer - alpha size", eeglGetRenderbufferParameteri(GL_RENDERBUFFER, GL_RENDERBUFFER_ALPHA_SIZE));
		eeglUnbindRenderbuffer(GL_RENDERBUFFER);
	}
	
	if (db_name != 0)
	{
		eeglBindRenderbuffer(GL_RENDERBUFFER, db_name);
		print("depth buffer - width", eeglGetRenderbufferParameteri(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH));
		print("depth buffer - height", eeglGetRenderbufferParameteri(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT));
		print("depth buffer - depth size", eeglGetRenderbufferParameteri(GL_RENDERBUFFER, GL_RENDERBUFFER_DEPTH_SIZE));
		eeglUnbindRenderbuffer(GL_RENDERBUFFER);
	}

	print("depth test", eeglGetInteger(GL_DEPTH_TEST));
	
}

























