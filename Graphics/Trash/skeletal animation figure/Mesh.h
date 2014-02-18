////
////  Mesh.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 4/30/13.
////  Copyright (c) 2013 Eonil. All rights reserved.
////
//
//#ifndef __EonilGraphics__Mesh__
//#define __EonilGraphics__Mesh__
//
//#include 	"Server/Buffer.h"
//#include 	"Server/Machine.h"
//#include	"Material.h"
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		using namespace		Foundation;
//		using namespace		Server;
//		
//		/*!
//		 A mesh is a collection of multiple points(vertices) and its connectivities(indices).
//		 
//		 Mesh is a value. No data will be shared.
//		 This means, you have no way to share meshes between models.
//		 
//		 */
//		class
//		Mesh 
//		{
//		public:
//			typedef		uint16_t			Index;
//			typedef		uint8_t				BoneIndex;
//			
//			struct
//			Section
//			{
//			public:				
//				std::vector<Index>			indexes;
//				Material					material;
//				
//				Size const					indexesSizeInBytes() const;
//				Memory const				indexesSnapshotData() const;
//			};
//			
//			/*!
//			 float x 3 + float x 2 + byte x 4 + float x 1 = 28 byte.
//			 */
//			struct
//			Vertex
//			{
//				glm::vec3					spaceCoordinate			=	glm::vec3(0,0,0);
//				glm::vec2					textureCoordinate		=	glm::vec2(0,0);
//				BoneIndex					boneIndexes[4]			=	{0,0,0,0};
//				Scalar						skinningIntensities[4]	=	{0,0,0,0};
//			
//				void						setSkinningIntensityForBoneAtIndex(Scalar const skinningIntensity, BoneIndex const boneIndex, Size const index);
//			};
//			
//			
//		public:
//			std::vector<Vertex> const&		vertexes() const;
//			std::vector<Section> const&		sections() const;
//			Size const						vertexesSizeInBytes() const;
//			Memory const					vertexesSnapshotData() const;
//			
//			VertexSourcingWithServerBuffer const	vertexSourcingParametersWithArrayBuffer(ArrayBuffer dataBuffer) const;
////			void							renderOnMachine(Machine& machine) const;
//			
//		public:
//			std::vector<Vertex>&			mutableVertexes();
//			std::vector<Section>&			mutableSections();
//			
//			
//			
//		private:
//			std::vector<Vertex>				_vtxs;
//			std::vector<Section>			_secs;
//			
//			
////		public:
////			class	Section;
////			class	Face;
////			class	Edge;
////			class	Vertex;
////			
////			struct
////			Section
////			{
////				
////			};
////			
////			struct
////			Face
////			{
////				std::vector<Edge>	edges;
////				Material			material;
////			};
////			
////			struct
////			Edge
////			{
////				std::vector<Vertex>	vertexes;
////			};
////			
////			class
////			Vertex
////			{
////				glm::vec3			spaceCoordinate;
////				glm::vec2			textureCoordinate;
////			};
////			
////			
////		public:
////			Face const&				faceAtIndex;
////			/*!
////			 Triangle-strip index.
////			 */
////			class
////			Section
////			{
////			public:
////				Section(vector<Size> const indexes);
////				vector<Size> const		indexes() const;
////				Material const			material() const;
////			private:
////				vector<Size>			_idxs;
////				Material				_mat;
////			};
////			struct
////			Vertex
////			{
////				
////			};
////			struct
////			Enveloping
////			{
////				Byte			boneIndex;
////				Scalar			bindingIntensity;
////			};
////			typedef uint16_t	Index;
////			
////		public:
////			Mesh(Vertex const vertices[], Size const count);
////			virtual ~Mesh();
////			
////			Size const			vertexCount() const;
////			Vertex const&		vertexAtIndex(Size const index) const;
////			
////			Server::
////			
////		public:
////			void				addFace(
////			
////		public:
//////			Vertex&				mutableVertexAtIndex(Size const index);
//////			void				setLength
////			
////		private:
////			std::vector<glm::vec3>			_posvec;
////			std::vector<glm::vec2>			_texvec;
////			std::vector<Mesh::Enveloping>	_envvec;
//		};
//	}
//}
//
//#endif /* defined(__EonilGraphics__Mesh__) */
