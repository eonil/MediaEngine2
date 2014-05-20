//
//  _Renderer_v2.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/16/13.
//
//

#include "LEGACY_Renderer_v2.h"










#include "../../Server/Machine.h"
#include "../../Stub/GL.h"


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Rendering
	{
		namespace
		D2014R1
		{
			
			
			
			
			
			
			
			
			
				
			namespace
			{
				using namespace Stub;
				
				void
				EnableWithAssertion(bool use, GLenum const cap)
				{
					EEGL_ASSERT(eeglIsEnabled(cap) == GL_FALSE);
					if (use)
					{
						eeglEnable(cap);
						EEGL_ASSERT(eeglIsEnabled(cap) == GL_TRUE);
					}
				}
				void
				DisableWithAssertion(bool use, GLenum const cap)
				{
					if (use)
					{
						EEGL_ASSERT(eeglIsEnabled(cap) == GL_TRUE);
						eeglDisable(cap);
					}
					EEGL_ASSERT(eeglIsEnabled(cap) == GL_FALSE);
				}
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			_Renderer_v2::_Renderer_v2() : machine(Server::Machine::current())
			{
				programs.for_LineMeshForm				=	_LineMeshForm::_makeShadingProgramInMachine(machine);
				_cache.for_TriangleListMeshForm_v2		=	_TriangleListMeshForm_v2::_makeResourceInMachine(machine);
				_cache.for_SkinnedForm_v2				=	_SkinnedForm_v2::_makeShadingProgramInMachine(machine);
			}
			_Renderer_v2::~_Renderer_v2()
			{
				
			}
			
			
			
			
			
			
			
			
			
			
			void
			_Renderer_v2::renderWithWorldToFrameTransform(const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R1::_Renderer_v2::Scene scene, const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Matrix4 worldToFrameTransform)
			{
				Doctor::assertMatrix4Validity(worldToFrameTransform);
				
				using namespace Stub;
				using namespace Server;
				using namespace Server::Machinery;
				
				//	Setup front-end. (= client window related state = viewport & scissor).
				{{
					Machine&	m	=	machine;
					m.setViewport(scene.display.viewport().boundsInWindow());
					
					if (scene.clipping != Bounds2::Utility::infinity())
					{
						Vector2	smin0	=	scene.clipping.minimum;
						Vector2	smax0	=	scene.clipping.maximum;
						
	//						//	Need Y-flipping because client window space is 4/4 plane.
	//						Vector2	smin1	=	Vector2(smin0.x, smax0.y);
	//						Vector2	smax1	=	Vector2(smax0.x, smin0.y);
						
						Vector2	smin2	=	scene.display.projectionMatrix().transform(smin0);
						Vector2	smax2	=	scene.display.projectionMatrix().transform(smax0);

						Bounds2	sci		=	Bounds2(smin2, smax2);
						m.setScissor(sci);
					}
					
					//	Setup feature switches.
					{{
						EnableWithAssertion(scene.switches.depthTesting, GL_DEPTH_TEST);
						EnableWithAssertion(scene.switches.blending.code != Scene::Blending::CODE::NONE, GL_BLEND);
						
						switch (scene.switches.blending.code)
						{
							case
							Scene::Blending::NONE:
							{
								break;
							}
							case
							Scene::Blending::TRANSPARENCY_WITH_PREMULTIPLIED_ALPHA:
							{
								eeglBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
								break;
							}
							case
							Scene::Blending::BURNING_EFFECT_BY_ACCUMULATION:
							{
								eeglBlendFunc(GL_ONE, GL_ONE);		//	Has error on final alpha which it goes more than 1. Anyway it will be clamped, so no problem.
								break;
							}
						}
						
						//	Straight alpha. Needs separated alpha function which is source alpha is ONE.
	//						glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						
						//	Render shapes.
						{{
							Matrix4		t0	=	worldToFrameTransform;
							Matrix4		t1	=	scene.display.regulator().aspectRatioCompensationTransformMatrix();
							Matrix4		t2	=	t1 * t0;
							
							Debugging::Doctor::assertMatrix4Validity(t2);
							
							{
	//								Program		p	=	_LineMeshForm::_makeShadingProgramInMachine(m);
								_Legacy2013_SharingBox<Program>		p	=	programs.for_LineMeshForm;
								_LineMeshForm::_renderOnMachine(m, p, scene.lineMeshes, t2);
							}
	//							{
	//								Program		p	=	_TriangleListMeshForm::_makeShadingProgramInMachine(m);
	//								_TriangleListMeshForm::_renderOnMachine(m, p, scene.triangleMeshForms, t2);
	//							}
	//							{
	//								Program		p	=	_SkinnedForm::_makeShadingProgramInMachine(m);
	//								_SkinnedForm::_renderOnMachine(m, p, scene.skinnedForms, t2);
	//							}
	//							{
	////								auto		r	=	_SkinnedForm::_makeShadingProgramInMachine(m);
	//								auto		r	=	_cache.for_SkinnedForm;
	//								_SkinnedForm::_renderOnMachine(m, r, scene.skinnedForms, t2);
	//							}
							{
	//								auto		r	=	_TriangleListMeshForm_v2::_makeResourceInMachine(m);
								auto		r	=	_cache.for_TriangleListMeshForm_v2;
								_TriangleListMeshForm_v2::_renderOnMachine(m, r, scene.triangleMeshForms2, t2);
							}
							{
								auto		r	=	_cache.for_SkinnedForm_v2;
								_SkinnedForm_v2::_renderOnMachine(m, r, scene.skinnedForms_v2, t2);
							}
						}}
						
						DisableWithAssertion(scene.switches.blending.code != Scene::Blending::CODE::NONE, GL_BLEND);
						DisableWithAssertion(scene.switches.depthTesting, GL_DEPTH_TEST);
					}}
					
					if (scene.clipping != Bounds2::Utility::infinity())
					{
						m.unsetScissor();
					}
					m.unsetViewport();
				}}
			}
			void
			_Renderer_v2::renderWithCamera(const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R1::_Renderer_v2::Scene scene, const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R1::_Camera_v1 camera)
			{
				Doctor::assertCameraValidity(camera);
				
				renderWithWorldToFrameTransform(scene, camera.worldFromFrameMatrix());
			}
			void
			_Renderer_v2::renderWithoutCamera(const Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R1::_Renderer_v2::Scene scene)
			{
				renderWithWorldToFrameTransform(scene, Matrix4::Utility::identity());
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

