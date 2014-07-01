//
//  EqualityComparison.cpp
//  Mathematics
//
//  Created by Hoon H. on 14/5/24.
//
//

#include "EqualityComparison.h"
#include "../Debugging/NaNCheck.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN
using namespace	Debugging;
using namespace	Eonil::Common::age2;





auto
default_epsilon() -> Geometry::Scalar
{
	return	std::numeric_limits<Geometry::Scalar>::epsilon();
}
auto
default_tolerance() -> Geometry::Scalar
{
	return	0.001;
}
auto
almost_equals(Geometry::Scalar const& a, Geometry::Scalar const& b, Geometry::Scalar const& tolerance) -> bool
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		err1_recoverable_bad_input_parameter_if(has_nan(a), "Input vectors shouldn't contain any NaN.");
		err1_recoverable_bad_input_parameter_if(has_nan(b), "Input vectors shouldn't contain any NaN.");
		err1_recoverable_bad_input_parameter_if(tolerance < 0, "Parameter `tolerance` should be larger then 0.");
	}
	
	////
	
	return	std::abs(a - b) < tolerance;
}
auto
almost_equals(Geometry::Vector3 const& a, Geometry::Vector3 const& b, Geometry::Scalar const& tolerance) -> bool
{
	if (USE_DEBUGGING_ASSERTIONS)
	{
		err1_recoverable_bad_input_parameter_if(has_nan(a), "Input vectors shouldn't contains any NaN.");
		err1_recoverable_bad_input_parameter_if(has_nan(b), "Input vectors shouldn't contains any NaN.");
		err1_recoverable_bad_input_parameter_if(tolerance < 0, "Parameter `tolerance` should be larger then 0.");
	}
	
	////
	
	return	(a - b).lengthSquare() < (tolerance * tolerance);
//	return	(a - b).length() < tolerance;
}
auto
almost_normalized(Geometry::Vector3 const& a, Geometry::Scalar const& tolerance) -> bool
{
	return	almost_equals(a.length(), 1, tolerance);
}







EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END
