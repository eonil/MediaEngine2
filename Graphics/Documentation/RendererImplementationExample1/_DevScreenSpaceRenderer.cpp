//
//  _DevScreenSpaceRenderer.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/15/13.
//
//

#include "_DevScreenSpaceRenderer.h"




#include "../Server/Machine.h"
#include "../Stub/GL.h"


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	_DEV_
	{
		using namespace Stub;
		using namespace Server;
		using namespace Server::Machinery;
		
		void
		_DevScreenSpaceRenderer::render(const Eonil::Improvisations::MediaEngine::Graphics::_DEV_::_DevScreenSpaceRenderer::Scene scene)
		{
			EEGL_ASSERT(eeglIsEnabled(GL_DEPTH_TEST) == GL_FALSE);
			
			////
			
			Machine&	m	=	Server::Machine::current();
			m.setViewport(scene.viewport.boundsOfViewport());
			
			//	On-screen display.
			{
				Matrix4		taspect	=	scene.viewport.aspectRatioCompensationTransformMatrix();
				{
					_Legacy2013_SharingBox<Program>		p	=	_ScreenSpaceMeshForm::_makeShadingProgramForMachine(m);
					_ScreenSpaceMeshForm::_drawOnMachine(m, p, scene.triangles, taspect);
				}
				{
					_Legacy2013_SharingBox<Program>		p	=	_LineMeshForm::_makeShadingProgramInMachine(m);
					_LineMeshForm::_renderOnMachine(m, p, scene.lines, taspect);
				}
			}
			
			m.unsetViewport();
		}
	}
	
	
	
	
	
	
	
	
}}}}




