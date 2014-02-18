//
//  Color.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/19/13.
//
//

#ifndef __EonilGraphics__Color__
#define __EonilGraphics__Color__

#include "../Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Value
	{

		/*!
		 4 x 32b-bit float component (RGBA) color.
		 
		 @discussion			Color can be described in many ways. OpenGL is using RGBA
		 method, so this class (main color descriptor) is defined
		 using RGBA method.
		 
		 @discussion			This represents a color with straight alpha. You cannot
		 construct a straight-alpha color value from premultiplied
		 one because premultiplication is destructive transform,
		 so some informations are loss when transform.
		 */
		class
		Color
		{
		public:
			/*!
			 Creates empty color (0,0,0,0) which is semantically fully transparent black.
			 */
			Color();
			Color(Vector4 const components);
			Color(Scalar const red, Scalar const green, Scalar const blue, Scalar const opacity);
			
			Vector4 const		components() const;
			Vector4 const		componentsWithPremultiplication() const;		//!	Take care premultiplication is destructive transform. No way back.
			
		private:
			Vector4				_comps;
		};
	}
	
	
}}}}

#endif /* defined(__EonilGraphics__Color__) */
