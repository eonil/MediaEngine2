//
//  _ScreenSpaceMeshForm.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/19/13.
//
//

#ifndef __EonilGraphics___ScreenSpaceMeshForm__
#define __EonilGraphics___ScreenSpaceMeshForm__

#include "../Server/Machine.h"
#include "../Server/Program.h"
#include "../Server/Machinery/VertexAttributeChannel.h"

EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

	namespace
	_DEV_
	{
		using namespace	Eonil::MediaEngine::Graphics::Value;
		
		
		
		
		/*!
		 This will be drawn as TRIANGLES.
		 */
		struct
		_ScreenSpaceMeshForm
		{
			struct
			Vertex
			{
				Vector4		location;
				Vector4		color;
			};
			struct
			FaceTriangle
			{
				Vertex		points[3];
			};
			
			std::vector<Vertex>	vertexes;
		
			void	addFaceTriangle(FaceTriangle const face);
			void	addBox(Vector2 const minimum, Vector2 const maximum, Vector4 const color);
			void	addDisc(Vector2 const center, Scalar const radius);
			
			
		private:
			friend class	_DevScreenSpaceRenderer;
							
			static Server::_Legacy2013_SharingBox<Server::Program>		_makeShadingProgramForMachine(Server::Machine const& m);
			static void					_drawOnMachine(Server::Machine& m, Server::_Legacy2013_SharingBox<Server::Program>& p, std::vector<_ScreenSpaceMeshForm> const& fs, Matrix4 const screenAspectRatioMatrix);		//!	The program `p` must be a program created by `_makeShadingProgram()` method.
//				/*!
//				 Adds a face triangle. First two points must be equal with last points in last face triangles.
//				 */
//				void	addFaceTriangle(Vector3 const p0, Vector3 const p1, Vector3 const p2);
//				
//				/*!
//				 Creates invisible triangles and make ready for next triangle.
//				 */
//				void	jumpToPoint(Vector3 const p0);
		};
		
		
		
//			/*!
//			 Will be drawn with LINES.
//			 */
//			struct
//			_ScreenSpaceLineForm
//			{
//				struct
//				Vertex
//				{
//					Vector4		space;
//					Vector4		color;
//				};
//				struct
//				Line
//				{
//					Vertex		points[3];
//				};
//				
//				std::vector<Vertex>	vertexes;
//				
//				void	addLine(Line const line);
//			};
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___ScreenSpaceMeshForm__) */
