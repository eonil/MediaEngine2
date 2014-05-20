//
//  Model.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/13/13.
//
//

#include "Model.h"




namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Resource
	{
		
		Model::Node::Node(Type::CODE const code) : type(code), pointerToSupernodeIndex(nullptr)
		{
		}
		Model::Node::Node(Type::CODE const code, Size const supernodeIndex) : type(code), pointerToSupernodeIndex(new Size(supernodeIndex))
		{
		}
		Model::Node::~Node()
		{
			delete	pointerToSupernodeIndex;
		}
		
		Size const
		Model::Tree::nodeCount() const
		{
			return	_boneNodes.size() + _socketNodes.size();
		}
		Model::Node const&
		Model::Tree::nodeAtIndex(const Size index) const
		{
			return	index < _boneNodes.size() ? _boneNodes.at(index) : _socketNodes.at(index - _boneNodes.size());
		}
		std::vector<Model::Node const> const&
		Model::Tree::boneNodes() const
		{
			return	_boneNodes;
		}
		std::vector<Model::Node const> const&
		Model::Tree::socketNodes() const
		{
			return	_socketNodes;
		}
		
		
		Size const
		Model::Tree::addBoneNode()
		{
			EEGL_ASSERT_WITH_REASON(_socketNodes.size() == 0, "Socket node cannot come before bone node.");
			_boneNodes.push_back(Node(Node::Type::CODE::BONE));
			return	_boneNodes.size() - 1;
		}
		Size const
		Model::Tree::addBoneSubnodeOfNodeAtIndex(const Size nodeIndex)
		{
			EEGL_ASSERT_WITH_REASON(nodeIndex < _boneNodes.size(), "Node index must indicate valid bone-node.");
			EEGL_ASSERT_WITH_REASON(_socketNodes.size() == 0, "Socket node cannot come before bone node.");
			_boneNodes.push_back(Node(Node::Type::CODE::BONE, nodeIndex));
			return	_boneNodes.size() - 1;
		}
		Size const
		Model::Tree::addSocketNode()
		{
			_socketNodes.push_back(Node(Node::Type::CODE::SOCKET));
			return	_boneNodes.size() + _socketNodes.size() - 1;
		}
		Size const
		Model::Tree::addSocketSubnodeOfNodeAtIndex(const Size nodeIndex)
		{
			EEGL_ASSERT_WITH_REASON(nodeIndex < _boneNodes.size(), "Node index must indicate valid bone-node.");
			EEGL_ASSERT_WITH_REASON(nodeAtIndex(nodeIndex).type != Node::Type::SOCKET, "Socket node cannot have subnode.");
			_socketNodes.push_back(Node(Node::Type::CODE::SOCKET, nodeIndex));
			return	_boneNodes.size() + _socketNodes.size() - 1;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
#pragma mark	-	`Model::State` Implementation
		
		Model::State::State(DeformingMesh const mesh, Tree const tree, std::vector<Motion> const motions) : mesh(mesh), tree(tree), motions(motions)
		{
			//	Verify tree state again.
			if (Debugging::Doctor::useStateValidation())
			{
				for (Size i=0; i<tree.nodeCount(); i++)
				{
					Node const&	n	=	tree.nodeAtIndex(i);
					
					if (n.pointerToSupernodeIndex != nullptr)
					{
						Size const	super_nidx	=	*(n.pointerToSupernodeIndex);
						EEGL_ASSERT_WITH_REASON(super_nidx < i, "Super-node must be placed before the current node.");
						EEGL_ASSERT_WITH_REASON(super_nidx < tree.boneNodes().size(), "Only bone-node can become a super-node.");
					}
				}
			}
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
#pragma mark	-	`Model` Implementation
		
		Model::Model(DeformingMesh const mesh, Tree const tree, std::vector<Motion> const motions) : _state(new State(mesh, tree, motions))
		{
		}
		Model::Model(Model const& other) : _state(other._state)
		{
		}
		
		
		
		
		
		
		Model::TreeTransforms const
		Model::treeTransformsWithObjectTransformAtTimeInMotion(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::Matrix4 objectTransform, const Size timeinMotion, const Size motionIndex) const
		{
			Size const		bonec	=	_state->tree.boneNodes().size();
			Motion const&	mo		=	_state->motions.at(motionIndex);
			
			/*!
			 Assume for all the nodes,
			 
			 -	All nodes are sorted in topologic order.
			 -	All bones and sockets are sorted in node index order.
			 -	So all bones and sockets are also topologic order.
			 
			 The constraints are enforced by assertions, and should be
			 satisfied.
			 */
			
			TreeTransforms	tt;
			for (Size i=0; i<_state->tree.nodeCount(); i++)
			{
				Node const		node	=	_state->tree.nodeAtIndex(i);
				Size const*		ptr		=	node.pointerToSupernodeIndex;
				Matrix4 const	pm		=	ptr == nullptr ? objectTransform : tt.boneTransformMatrices.at(*ptr);
				Matrix4 const	cm		=	mo.nodeAnimations.at(i).sampleAtTime(timeinMotion).resolveProjectionMatrix();
				Matrix4 const	m		=	pm * cm;
				
				(i < bonec ? tt.boneTransformMatrices : tt.socketTransformMatrices).push_back(m);
			}
			return	tt;
		}
	}
	
	
	
	
	
	
	
	
}}}}
