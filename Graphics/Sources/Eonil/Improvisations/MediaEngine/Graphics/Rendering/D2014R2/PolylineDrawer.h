//
//  PolylineDrawer.h
//  Graphics
//
//  Created by Hoon H. on 2/17/14.
//
//

#ifndef __Graphics__PolylineDrawer__
#define __Graphics__PolylineDrawer__

#include "../../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Rendering
	{
		namespace
		D2014R2
		{
			
			
			
			
			/*!
			 Draws filled poly-lines with color.
			 A polyline can be drawn as solid, dashed, dotted styled.
			 */
			class
			PolylineDrawer
			{
				uptr<Server::Program>				_shader		{};
				
			public:
				template <typename T>
				struct
				Resolver
				{
					using	Solve	=	std::function<T(Size const& index)>;
					
					Size		count{0};
					Solve		solver{nullptr};
				};
				
			public:
				PolylineDrawer();
				~PolylineDrawer();
				
				auto	drawInstances(Resolver<Matrix4> const& transforms, Resolver<Vector4> const& colors) const -> void;
			};
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__PolylineDrawer__) */
