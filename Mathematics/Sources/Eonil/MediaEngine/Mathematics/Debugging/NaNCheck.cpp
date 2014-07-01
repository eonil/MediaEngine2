//
//  NaNCheck.cpp
//  Mathematics
//
//  Created by Hoon H. on 14/7/2.
//
//

#include "NaNCheck.h"
#include "../Geometry/Vector.h"
#include "../Geometry/Matrix.h"
#include <iostream>
EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_BEGIN











auto
has_nan(Geometry::Scalar const& o) -> bool
{
	return	std::isnan(o);
}
auto
has_nan(Geometry::Vector2 const& o) -> bool
{
	for (auto const& v: o.components)
	{
		if (std::isnan(v))
		{
			return	true;
		}
	}
	return	false;
}
auto
has_nan(Geometry::Vector3 const& o) -> bool
{
	for (auto const& v: o.components)
	{
		if (std::isnan(v))
		{
			return	true;
		}
	}
	return	false;
}
auto
has_nan(Geometry::Vector4 const& o) -> bool
{
	for (auto const& v: o.components)
	{
		if (std::isnan(v))
		{
			return	true;
		}
	}
	return	false;
}
auto
has_nan(Geometry::Matrix4 const& o) -> bool
{
	for (auto const& v: o.components)
	{
		if (std::isnan(v))
		{
			return	true;
		}
	}
	return	false;
}






EONIL_MEDIA_ENGINE_MATHEMATICS_DEBUGGING_NAMESPACE_END


