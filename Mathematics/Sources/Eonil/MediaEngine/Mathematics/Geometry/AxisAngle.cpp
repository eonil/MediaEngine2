//
//  AxisAngle.cpp
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/11/13.
//
//

#include "AxisAngle.h"
#include "Quaternion.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN












namespace
{
	static inline auto
	refAsVector4(AxisAngle const& o) -> Vector4 const&
	{
		static_assert(sizeof(AxisAngle) == sizeof(Vector4), "Size of two types must be equal.");
		
		return	reinterpret_cast<Vector4 const&>(o);
	}
//	static inline auto
//	refAsAxisAngle(Vector4 const& o) -> AxisAngle const&
//	{
//		static_assert(sizeof(AxisAngle) == sizeof(Vector4), "Size of two types must be equal.");
//		
//		return	reinterpret_cast<AxisAngle const&>(o);
//	}
}


bool const
AxisAngle::operator==(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::AxisAngle &other) const
{
	return	refAsVector4(*this) == refAsVector4(other);
}
bool const
AxisAngle::operator!=(const Eonil::Improvisations::MediaEngine::Mathematics::Geometry::AxisAngle &other) const
{
	return	refAsVector4(*this) != refAsVector4(other);
}
Quaternion const
AxisAngle::asQuaternion() const
{
	return	Quaternion::Utility::quaternionWithAxisAngle(*this);
}









EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END
