//
//  _LineMeshForm.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/26/13.
//
//

#ifndef __EonilGraphics___LineMeshForm__
#define __EonilGraphics___LineMeshForm__

#include "../../Common.h"
#include "../../Server/Declarations.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R1
		{
			
			
			
			
			
			
			
			
			
				
			using namespace	Value;
			
			
			
			/*!
			 This class is mainly designed to display development/debugging widgets.
			 
			 @classdesign
			 This will be drawn with `GL_LINES`.
			 Layout vertexes as expected.
			 
			 This is mainly debugging aid. No optimization will be performed.
			 Each instance will have each resources.
			 
			 @deprecated
			 Legacy. Do not use this class for new code.
			 */
			class
			_LineMeshForm
			{
			public:
				struct
				Vertex
				{
					Vector4		location;		//	`w` component must be `1`.
					Vector4		color;
				};
				struct
				Line
				{
					union
					{
						struct
						{
							Vertex		from;
							Vertex		to;
						};
						struct
						{
							Vertex		components[2];
						};
						struct
						{
							Scalar		scalars[(4+4)*2];
						};
					};
				};
				
				std::vector<Line> const&	lines() const;
				Matrix4 const				transform() const;
				
				_LineMeshForm const			lineMeshWithTransform(Matrix4 const m) const;
				
				void						setTransform(Matrix4 const m);
				void						addLine(Line const l);
				void						addLine(Vector4 const from, Vector4 const to, Vector4 const color);
				void						addLines(std::vector<Line> const lines);
				
			public:
				struct
				Utility
				{
	//					static _LineMeshForm const		box(
					
					static _LineMeshForm const		quadraticGrid(Size const halfWidth, Size const halfHeight, Scalar const unitLength, Vector4 const centerColor, Vector4 const borderColor, Vector4 const otherColor);
					static _LineMeshForm const		cubicGrid(Size const halfWidth, Size const halfHeight, Size const halfDepth, Scalar const unitLength, Vector4 const centerColor, Vector4 const borderColor, Vector4 const otherColor);
					static _LineMeshForm const		cubicCross(Vector3 const halfLength, Vector4 const xColor, Vector4 const yColor, Vector4 const zColor);
				};
				
				
				
				
				
				
			private:
				std::vector<Line>			_ls;
				Matrix4						_tm		=	Matrix4::Utility::identity();	//!	Object-to-world transform.
				
			private:
				friend class _DevRenderer;
				friend class _Renderer_v2;
				friend class _DevScreenSpaceRenderer;
				
				static Server::_Legacy2013_SharingBox<Server::Program> _makeShadingProgramInMachine(Server::Machine& m);
				static void					_renderOnMachine(Server::Machine& m, Server::_Legacy2013_SharingBox<Server::Program>& p, std::vector<_LineMeshForm> const& fs, Matrix4 const worldToFrameTransform);
			};
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__EonilGraphics___LineMeshForm__) */














