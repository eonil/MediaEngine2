//
//  Cluster.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/13/13.
//
//

#ifndef __EonilGraphics__Cluster__
#define __EonilGraphics__Cluster__

#include "../Common.h"
#include "../Transform.h"
#include "../Resource/Sprite.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Form
	{
		using namespace Resource;
		
		/*!
		 Cluster is designed to draw 2D sprite in 3D space. Actually shape is not
		 limited to 2D, but treated as 2D because lighting is not supported.
		 Cluster is a set of different static meshes. This is designed to draw
		 multiple small meshes in 3D space. So vertexes in meshes can have 3D 
		 position, and be transformed in 3D space.
		 
		 You can make some instances to toward to camera by setting proper rotation.
		 Anyway you should do this yourself. This class can't offer automatic
		 adjustment due to lack of camera information. To perform the adjustment,
		 see `Transform::Utility` class.

		 @classdesign
		 This class will perform transform in CPU, and will dispatch only resolved
		 vertexes to GPU.
		 
		 Cluster must contain only sprites which shares all graphics state including 
		 textures. In debug build, cluster method will assert for them.
		 
		 Billboards can be created by settings `billboard` parameter. If it's true,
		 renderer will adjust rotations of all instances to face the camera. And 
		 because sprite is primarily defined as a 2D shape, +Z in object space will 
		 be treated as up vector.
		 
		 @performance
		 To be most efficient, all the transforms must be able to be resolved within
		 only GPU. But, without vertex shader texture fetch, that's mostly impossible.
		 (we need universal shader architecture) As this library is targeting 
		 OpenGL ES 2.0, I decided not to try to implement it. Just transform all the
		 vertexes and dispatch to GPU.
		 
		 Because this is an optimzied class for specific purpose, only flat, color
		 textured shading is supported. No support for lighting based on normals.
		 
		 Don't & Why?
		 ------------
		 Just save transforms and source sprites. Because it's more source information, which is 
		 better for debugging. Also it's superier in memory efficiency. Storing fully transformed
		 vertexes needs at least 5 scalars * 4 vertexes = 20 scalars(= 80 bytes). But storing 
		 source transform and linked sprite needs only 10 scalars + 1 pointers (= 48 bytes).
		 
		 @note
		 Primary use of this class is billboard in 3D space. But anyway, works well
		 for particles. But, because this class performs full 3D transform for each
		 vertexes, it can be slow if instance count go huge. If you need even faster 
		 particles, you can consider using of `Cloud` class which drops 3D tranform
		 feature, and only can be tranformed in 2D.
		 
		 */
		struct
		Cluster
		{
			struct
			Instance
			{
				Sprite		sprite;
				Transform	transform;
				Vector4		color;
			};
			
			bool					billboard;
			std::vector<Instance>	instances;
		};
		
		
		
		
		
		
		
		
		
		
//			/*!
//			 Cluster doesn't limit shape to 2D sprite, and also can use any other 3D shapes.
//			 But support for 3D shape will increase complexity, so it won't be supported without
//			 strong needs.
//			 
//			 Trouble on Supporting 3D Shape
//			 ------------------------------
//			 3D shape doesn't mean just appending a scalar for Z axis.
//			 For complete support, any other attributes should also be supported such as normal.
//			 This will require related material, shader support.
//			 */
//			class
//			Cluster
//			{
//			public:
//				struct
//				Instance
//				{
//					Transform					transform;
//					Vector4						color;
//				};
//				
//				Sprite const&					sprite() const;
//				void							setSprite(Sprite const s);
//				
//				std::vector<Instance> const&	instances() const;
//				std::vector<Instance>&			instances();
//				void							setInstances(std::vector<Instance> const instances);
//				
//			private:
//				std::vector<Instance>			_insts;
//			};
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__Cluster__) */
