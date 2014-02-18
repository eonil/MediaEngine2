//
//  AxisAngle.cpp
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/11/13.
//
//

#include "AxisAngle.h"
#include "Quaternion.h"

/*
 Do not include whole GLKit which needs Objective-C context.
 */
//#include <GLKit/GLKit.h>
#include <GLKit/GLKitBase.h>
#include <GLKit/GLKMath.h>

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Mathematics {

	namespace
	Value
	{
		namespace
		{
			union
			CONV4
			{
				Scalar			V[4];
				GLKQuaternion	GLKQ;
				Quaternion		EEQ;
				
				GLKVector4		GLKV;
				Vector4			EEV;
				
				AxisAngle		EEAA;
				
				CONV4(GLKVector4 const v) : GLKV(v) {}
				CONV4(GLKQuaternion const v) : GLKQ(v) {}
				CONV4(Vector4 const v) : EEV(v) {}
				CONV4(Quaternion const v) : EEQ(v) {}
				CONV4(AxisAngle const v) : EEAA(v) {}
			}
			__attribute__((aligned(16)));
			
			static_assert(sizeof(Scalar) == 4, "");
			static_assert(sizeof(CONV4) == sizeof(Scalar) * 4, "");
		}
		
		
		bool const
		AxisAngle::operator==(const Eonil::Improvisations::MediaEngine::Mathematics::Value::AxisAngle &other) const
		{
			return	GLKVector4AllEqualToVector4(CONV4(*this).GLKV, CONV4(other).GLKV);
		}
		bool const
		AxisAngle::operator!=(const Eonil::Improvisations::MediaEngine::Mathematics::Value::AxisAngle &other) const
		{
			return	not GLKVector4AllEqualToVector4(CONV4(*this).GLKV, CONV4(other).GLKV);
		}
		Quaternion const
		AxisAngle::asQuaternion() const
		{
			return	Quaternion::Utility::quaternionWithAxisAngle(*this);
		}
	}



}}}}