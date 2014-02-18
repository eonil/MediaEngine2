//
//  Color.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/19/13.
//
//

#include "Color.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Value
	{
		
		
		
		
		Color::Color() : _comps(Vector4(0,0,0,0))
		{
		}
		Color::Color(Vector4 const comps) : _comps(comps)
		{
		}
		Color::Color(Scalar const red, Scalar const green, Scalar const blue, Scalar const opacity) : Color(Vector4(red, green, blue, opacity))
		{
		}
		
		auto
		Color::components() const -> Vector4 const
		{
			return	_comps;
		}
		auto
		Color::componentsWithPremultiplication() const -> Vector4 const
		{
			Vector4	c1	=	_comps;
			c1.x		*=	c1.w;
			c1.y		*=	c1.w;
			c1.z		*=	c1.w;
			return	c1;
		}
		
		
		
		
	}
	
}}}}