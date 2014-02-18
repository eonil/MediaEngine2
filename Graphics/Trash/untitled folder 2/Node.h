////
////  Node.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 4/30/13.
////  Copyright (c) 2013 Eonil. All rights reserved.
////
//
//#ifndef __EonilGraphics__Node__
//#define __EonilGraphics__Node__
//
//#include	"Transform.h"
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		class
//		Node
//		{
//		public:			
//			class
//			Transform : public Eonil::Improvisations::MediaEngine::Graphics::Transform
//			{
//			public:
//				Transform(Node const& owner);
//				Node const&		owner() const;
//			private:
//				Node const& 			_owner;
//			};
//			
//		public:
//			Node();
//			Node(Size const subnodeCapacity);
//			Node(std::vector<Node> const sourceNodes);							//	Semantically copies source nodes. C++ compiler may optimize it by case.
//			~Node();
//			
//			Node::Transform const&		transform() const;
//			std::vector<Node> const&	subnodes() const;
////			Size const			subnodeCount() const;
////			Node const&			subnodeAtIndex(Size const index) const;
//			
//		public:
//			Node::Transform&			mutableTransform();
//			std::vector<Node>&			mutableSubnodes();
//			
////			Node&				mutableSubnodeAtIndex(Size const index);
////			Node&				addSubnode();
////			Node&				addSubnode(Node const& node);					//	Semantically copies content of the node. C++ compiler may optimize it by case.
////			void				removeSubnodeAtIndex(Size const index);
////			void				removeSubnode(Node const& node);				//	A node should be a reference obtained from this object.
//			
//		private:
//			Node::Transform				_tran;
//			std::vector<Node>			_nodes;
//		};
//		
//		
//		class
//		NodeList : public std::vector<Node>
//		{
//		public:
//			
//			Size const	subnodeCount() const;
//			Node const&	subnodeAtIndex(Size const index) const;
//			
//		public:
//			Node&		mutableSubnodeAtIndex(Size const index);
//			Node&		addSubnode();
//			Node&		addSubnode(Node const& node);					//	Copies content of the node.
//			void		removeSubnodeAtIndex(Size const index);
//			void		removeSubnode(Node const& node);				//	A node should be a reference obtained from this object.
//			
//		};
//	}
//}
//
//#endif /* defined(__EonilGraphics__Node__) */
