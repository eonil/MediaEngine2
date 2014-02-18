////
////  CPUTransformParticleDrawer.h
////  Graphics
////
////  Created by Hoon H. on 2/18/14.
////
////
//
//#ifndef __Graphics__CPUTransformParticleDrawer__
//#define __Graphics__CPUTransformParticleDrawer__
//
//#include "../../Common.h"
//#include "../../Server/Texture.h"
//
//namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
//	
//	namespace
//	Rendering
//	{
//		namespace
//		D2014R2
//		{
//			
//			
//			
//			
//			/*!
//			 @discussion
//
//			 */
//			class
//			CPUTransformParticleDrawer
//			{
//				uptr<Server::Program>				_shader		{};
//				ptr<const Server::PlanarTexture>	_ptex		{};
//				
//			public:
//				template <typename T>
//				struct
//				Resolver
//				{
//					using	Solve	=	std::function<T(Size const& index)>;
//					
//					Size		count{0};
//					Solve		solver{nullptr};
//				};
//				
//			public:
//				CPUTransformParticleDrawer(Server::PlanarTexture const& texture);
//				~CPUTransformParticleDrawer();
//				
//				auto	drawInstances(Resolver<Matrix4> const& transforms, Resolver<Vector4> const& colors) const -> void;
//			};
//			
//			
//			
//			
//			
//			
//			
//			
//		}
//	}
//	
//}}}}
//
//#endif /* defined(__Graphics__CPUTransformParticleDrawer__) */
