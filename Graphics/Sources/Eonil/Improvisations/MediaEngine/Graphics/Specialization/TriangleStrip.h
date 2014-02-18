////
////  TriangleStrip.h
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 4/30/13.
////  Copyright (c) 2013 Eonil. All rights reserved.
////
//
//#ifndef __EonilGraphics__TriangleStrip__
//#define __EonilGraphics__TriangleStrip__
//
//#include "../Common.h"
//
//namespace
//Eonil
//{
//	namespace
//	Graphics
//	{
//		namespace
//		Specialization
//		{
//			
//			class
//			TriangleStrip
//			{
//			public:
//				TriangleStrip(std::vector<glm::vec3> const vertexes, std::vector<Size> const indexes);
//				
//				std::vector<Size> const&		indexes() const;
//				std::vector<glm::vec3> const&	vertexes() const;
//				
//				Size const						countOfAllFaces() const;
//				Size const						countOfVisibleFaces() const;
//				Size const						countOfInvisibleFaces() const;
//				
//				TriangleStrip const				triangleStripByInvertingFaceDirection() const;
//				
//			public:
//				std::vector<Size>&				mutableIndexes();
//				std::vector<glm::vec3>&			mutableVertexes();
//				
//				void							addFace(glm::vec3 const v0, glm::vec3 const v1, glm::vec3 const v2);						//	Creates a new detached face. (using zero-area triangle)
//				void							addFaceToPoint(glm::vec3 const& point);														//	Creaets a new attached face. You need existing face to add to.
//				void							removeLastFace();
//				
//			private:
//				std::vector<Size>				_idxs;
//				std::vector<glm::vec3>			_vtxs;
//			};
//		}
//	}
//}
//
//#endif /* defined(__EonilGraphics__TriangleStrip__) */
