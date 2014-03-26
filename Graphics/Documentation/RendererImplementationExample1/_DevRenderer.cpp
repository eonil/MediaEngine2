//
//  _DevRenderer.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/19/13.
//
//

#include "_DevRenderer.h"

#include "../Server/Machine.h"
#include "../Stub/GL.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	_DEV_
	{
		void
		_DevRenderer::render(const Eonil::Improvisations::MediaEngine::Graphics::_DEV_::_DevRenderer::_DevScene scene)
		{
			Doctor::assertCameraValidity(scene.camera);
			
			using namespace Stub;
			using namespace Server;
			using namespace Server::Machinery;
			
			Machine&	m	=	Server::Machine::current();
			m.setViewport(scene.viewport.boundsOfViewport());
			
			if (scene.switches.depthTesting)
			{
				eeglEnable(GL_DEPTH_TEST);
			}
			else
			{
				EEGL_ASSERT(eeglIsEnabled(GL_DEPTH_TEST) == GL_FALSE);
			}
			
			//	In-space display.
			{
				
				Matrix4		t0	=	scene.camera.worldToFrameMatrix();
				Matrix4		t1	=	scene.viewport.aspectRatioCompensationTransformMatrix();
				Matrix4		t2	=	t1 * t0;
				
				Debugging::Doctor::assertMatrix4Validity(t2);
				
				{
					_Legacy2013_SharingBox<Program>		p	=	_LineMeshForm::_makeShadingProgramInMachine(m);
					_LineMeshForm::_renderOnMachine(m, p, scene.lineMeshes, t2);
				}
				{
					_Legacy2013_SharingBox<Program>		p	=	_TriangleListMeshForm::_makeShadingProgramInMachine(m);
					_TriangleListMeshForm::_renderOnMachine(m, p, scene.triangleMeshForms, t2);
				}
				{
					_Legacy2013_SharingBox<Program>		p	=	_SkinnedForm::_makeShadingProgramInMachine(m);
					_SkinnedForm::_renderOnMachine(m, p, scene.skinnedForms, t2);
				}
				{
					auto		r	=	_TriangleListMeshForm_v2::_makeResourceInMachine(m);
					_TriangleListMeshForm_v2::_renderOnMachine(m, r, scene.triangleMeshForms2, t2);
				}
			}
			
			if (scene.switches.depthTesting)
			{
				eeglDisable(GL_DEPTH_TEST);
			}
			else
			{
				EEGL_ASSERT(eeglIsEnabled(GL_DEPTH_TEST) == GL_FALSE);
			}
			
			m.unsetViewport();
		}
	}
	
	
	
	
	
	
	
	
}}}}






