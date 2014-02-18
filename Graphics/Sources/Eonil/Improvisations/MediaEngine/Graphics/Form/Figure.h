//
//  Figure.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/12/13.
//
//

#ifndef __EonilGraphics__Figure__
#define __EonilGraphics__Figure__

#include "../Transform.h"
#include "../Resource/Model.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Form
	{
		using namespace	Resource;
		
		
		
		
		
		
		/*!
		 A deformable mesh. (a.k.a. skinned mesh)
		 
		 This is a kind of optimized vertex animation. Instead of moving all each vertexes,
		 this uses a few control points (a.k.a. bone) to deform multiple vertexes.
		 
		 A figure can contain only one mesh. If you need to render multiple meshes,
		 render them separately.
		 
		 Or you can merge multiple figures into one. Also you can split one figure
		 into multiple figures. Merging figures will detect and discard all duplicated
		 data. If you split a figure, each pieces can have duplicated data because some
		 duplication is required. Both of merging and splitting are all pretty expensive
		 operation, so do that only as a preprocessing.
		 
		 Merging/splitting is mainly exist to correspond to maximum bone count limit.
		 I recommend to make merged model by default, and split when needed.
		 
		 Animation
		 ---------
		 Skinning figures usually have multiple animations.
		 */
		struct
		Figure
		{
			Model		model;
			Transform	transform;
			
			/*!
			 Deformation control points are stored in source model as a form of continuous
			 motion channel curves. This specifies a point of the motion to sample on.
			 */
			struct
			{
				struct
				{
					Size	index;
					Size	time;
				}
				motion;
			}
			deformation;
			
			/*!
			 This is an instance of the internal shader with prebound parameters.
			 */
			struct
			{
				_Legacy2013_SharingBox<PlanarTexture>	texture;
			}
			material;
		};
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
//			/*!
//			 A deformable mesh. (a.k.a. skinned mesh)
//			 
//			 This is a kind of optimized vertex animation. Instead of moving all each vertexes,
//			 this uses a few control points (a.k.a. bone) to deform multiple vertexes.
//			 
//			 A figure can contain only one mesh. If you need to render multiple meshes,
//			 render them separately.
//			 
//			 Or you can merge multiple figures into one. Also you can split one figure
//			 into multiple figures. Merging figures will detect and discard all duplicated
//			 data. If you split a figure, each pieces can have duplicated data because some
//			 duplication is required. Both of merging and splitting are all pretty expensive
//			 operation, so do that only as a preprocessing.
//			 
//			 Merging/splitting is mainly exist to correspond to maximum bone count limit.
//			 I recommend to make merged model by default, and split when needed.
//			 
//			 Animation
//			 ---------
//			 Skinning figures usually have multiple animations.
//			 */
//			class
//			Figure
//			{
//			public:
//				/*!
//				 Deformation control points are stored in source model as a form of continuous
//				 motion channel curves. This specifies a point of the motion to sample on.
//				 */
//				struct
//				Deformation
//				{
//					struct
//					{
//						Size	index;
//						Size	time;
//					}
//					motion;
//				};
//				/*!
//				 This is an instance of a shader with prebound parameters.
//				 */
//				struct
//				Material
//				{
//					
//				};
//				
//			public:
//				Figure(Model const model);
//				Figure(Model const model, Transform const transform);
//				
//				Model const&			model() const;
//				void					setModel(Model const& model);
//				
//				Transform const&		transform() const;
//				void					setTransform(Transform const transform);
//				
//				Deformation const&		deformation() const;
//				void					setDeformation(Deformation const deformation);
//				
//			private:
//				Model					_m;
//				Transform				_t;
//				Deformation 			_d;
//			};
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__Figure__) */
