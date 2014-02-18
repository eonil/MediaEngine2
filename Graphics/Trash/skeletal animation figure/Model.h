////
////  Model.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 4/30/13.
////  Copyright (c) 2013 Eonil. All rights reserved.
////
//
//#ifndef __EonilGraphics__Model__
//#define __EonilGraphics__Model__
//
//#include		"Mesh.h"
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		class	Bone;
//		class	Mesh;
//		class	Texture;
//		
//		/*!
//		 Model is a collection of data to draw a graphic.
//		 
//		 Model doesn't share any resources with other models.
//		 
//		 */
//		class
//		Model
//		{
//		public:
//			Model(std::vector<Mesh> const meshes);
//			virtual ~Model();
//			
//		public:
//			std::vector<Bone> const&			bones() const;					//	Map index to bone. Or vice-versa.
//			std::vector<Mesh> const&			meshes() const;
//			std::vector<Texture> const&			textures() const;
//			
//			Size const							boneIndexForName(std::string const) const;
//			
//			void								renderOnMachine(Machine const& m);
//			
//		public:
//			class
//			BoneBinding
//			{
//			public:
//				std::string 					boneName;
//				Scalar							bindingIntensity;
//			};
//			
////			void								addBone();
//			void								addVertex(glm::vec3 const spatialCoordinate, glm::vec2 const textureCoordinate, std::string const boneName);
//		};
//	}
//}
//
//#endif /* defined(__EonilGraphics__Model__) */
