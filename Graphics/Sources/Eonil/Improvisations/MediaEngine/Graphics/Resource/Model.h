//
//  Model.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/13/13.
//
//

#ifndef __EonilGraphics__Model__
#define __EonilGraphics__Model__

#include "../Transform.h"
#include "Animation.h"
#include "Mesh.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Resource
	{
		/*!
		 Model is a fully immutable composition of mesh, bone and animation set.
		 
		 @classdesign
		 
		 Tree Hierarchy
		 --------------
		 Tree is a concept to represent a subspace hierarchy in the object space.
		 This is required only to present nesting state of each subobjects.
		 
		 Nodes in tree represents just how each transforms are nested. All nodes are in a 
		 subspace created by object's transform. So they ultimately need to be multiplied 
		 to object's transform matrix to be placed in global space transform. Bone index 
		 number is the bone ID which will be resolved to transform-animation for the index.
		 
		 A model can have multiple top-level bones. If all the bones are top-level, it means
		 hierarchy is flatten.
		 
		 Currently two subobject graph is using node.
		 
		 -	Bone
		 -	Socket
		 
		 Bones and sockets have these different characteristics.
		 
		 -	Bones are used to deform model-internal vertexes.
		 -	Sockets are used to placement of external object rather than internal vertexes.
		 -	Sockets cannot have subnodes.

		 Because sockets cannot have subnodes, all the sockets will come after all the bones.
		 
		 
		 
		 @note
		 Debug build will remain node name, animation channel name and etc.
		 Debug build will assert for requirements.
		 */
		class
		Model
		{
		public:
			struct
			Node
			{
				struct
				Type
				{
					enum
					CODE
					{
						BONE,
						SOCKET,
					};
				};
				
				Type::CODE const	type;
				Size const* const	pointerToSupernodeIndex;
				
				Node(Type::CODE const type);
				Node(Type::CODE const type, Size const supernodeIndex);
				~Node();
			};
			
			/*!
			 Because this is append only, and appending subnode needs to specify
			 super-node, added nodes will be sorted in topological order automatically.
			 
			 Because it's sorted in topologic order, simply performing matrix accumulation
			 sequentially with consideration of super-node will give you correct result.
			 
			 Also, all the sockets must come after all the bones. You can simply take index
			 of socket node using an offset. 

			 These rules are enforced by assertions on debug build.
			 
			 See the implementation of `Model` for actual usage.
			 */
			class
			Tree
			{
			public:
				Size const					nodeCount() const;
				Node const&					nodeAtIndex(Size const index) const;
				
				std::vector<Node const> const&	boneNodes() const;
				std::vector<Node const> const&	socketNodes() const;
				
				Size const					addBoneNode();
				Size const					addBoneSubnodeOfNodeAtIndex(Size const nodeIndex);
				
				Size const					addSocketNode();
				Size const					addSocketSubnodeOfNodeAtIndex(Size const nodeIndex);

			private:
				std::vector<Node const>		_boneNodes;
				std::vector<Node const>		_socketNodes;
			};
							
			struct
			Motion
			{
				std::vector<TransformAnimation>	nodeAnimations;			//!	Bones are matched by index number.
				
				std::string				originNameForDebugging;
			};

			/*!
			 Fully accumulated matrices which transforms vertexes into global-space.
			 (object transform is also has been applied)
			 */
			struct
			TreeTransforms
			{
				std::vector<Matrix4>	boneTransformMatrices;
				std::vector<Matrix4>	socketTransformMatrices;
			};
			
		public:
			Model() = delete;
			Model(DeformingMesh const mesh, Tree const tree, std::vector<Motion> const motions);
			Model(Model const& other);
			
			DeformingMesh const&		mesh() const;
			Tree const&					tree() const;
			std::vector<Motion> const&	motions() const;
			
			/*!
			 Resolve everything at once.
			 
			 @note
			 If memory is enough, this can cache resolutions very aggressively
			 for each motion and for each time. But it will take too much memory.
			 If a model has 64 bones, total data amount for a frame is 4*16*64 = 4KB. 
			 If we store 60 frames, it will become 4KB*60 = 240KB. In SRT form,
			 */
			TreeTransforms const		treeTransformsWithObjectTransformAtTimeInMotion(Matrix4 const objectTransform, Size const timeinMotion, Size const motionIndex) const;
			
			std::string					originNameForDebugging;
			
		private:
			struct
			State
			{
				DeformingMesh const		mesh;
				Tree const				tree;
				std::vector<Motion>		motions;
									
				State(DeformingMesh const mesh, Tree const tree, std::vector<Motion> const motions);
			};
			
			std::shared_ptr<State>		_state;
		};
	}
	
	
	
	
	
	
	
}}}}


#endif /* defined(__EonilGraphics__Model__) */
