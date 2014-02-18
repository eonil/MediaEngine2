//
//  Transform.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 4/30/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics__Transform__
#define __EonilGraphics__Transform__

#include "Common.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Debugging
	{
		struct	Doctor;
	}
	
	using namespace	Value;
	
	/*!
	 Initial value is identity.
	 
	 `resolve~` methods caches result until parameters changes.
	 */
	class
	Transform
	{
		friend class	Debugging::Doctor;
//			static_assert(glm::quat(0.0f, 0.0f, 0.0f, 1.0f) == glm::angleAxis(0.0f, 0.0f, 0.0f, 0.0f), "Ensure identity quaternion.");
//			static_assert(glm::quat(0.0f, 0.0f, 0.0f, 1.0f) == glm::angleAxis(0.0f, 1.0f, 0.0f, 0.0f), "Ensure identity quaternion.");
//			static_assert(glm::quat(0.0f, 0.0f, 0.0f, 1.0f) == glm::angleAxis(0.0f, 0.0f, 1.0f, 0.0f), "Ensure identity quaternion.");
//			static_assert(glm::quat(0.0f, 0.0f, 0.0f, 1.0f) == glm::angleAxis(0.0f, 0.0f, 0.0f, 1.0f), "Ensure identity quaternion.");
		
	public:
//			Transform()
//			{
//				/*
//				 Don't know why, but doesn't work with `static_assert`.
//				 */
//				EEGL_ASSERT(glm::quat(0.0f, 0.0f, 0.0f, 1.0f) == glm::angleAxis(0.0f, 0.0f, 0.0f, 0.0f), "Ensure identity quaternion.");
//				EEGL_ASSERT(glm::quat(0.0f, 0.0f, 0.0f, 1.0f) == glm::angleAxis(0.0f, 1.0f, 0.0f, 0.0f), "Ensure identity quaternion.");
//				EEGL_ASSERT(glm::quat(0.0f, 0.0f, 0.0f, 1.0f) == glm::angleAxis(0.0f, 0.0f, 1.0f, 0.0f), "Ensure identity quaternion.");
//				EEGL_ASSERT(glm::quat(0.0f, 0.0f, 0.0f, 1.0f) == glm::angleAxis(0.0f, 0.0f, 0.0f, 1.0f), "Ensure identity quaternion.");
//
//				EEGL_ASSERT(Quaternion::Utility::identity() == Quaternion::Utility::quaternionWithAxisAngle(AxisAngle(Vector3(0.0f, 0.0f, 0.0f), 0.0f)), "Ensure identity quaternion.");
//			}
		
	public:
		Vector3 const&			translation() const;
		Quaternion const&		rotation() const;
		Vector3 const&			scale() const;
		
	public:
		void					setScale(Vector3 const value);
		void					setRotation(Quaternion const value);
		void					setTranslation(Vector3 const value);
		
		/*!
		 Makes +Z axis to face the target point considering current transform. 
		 If the target point is a camera position, this will create billboard 
		 effectlvely. Of course, all the coordinates should be homogenious.
		 
		 @note
		 +Z is defined as a *up* direction within this engine.
		 */
		void					faceObjectSpaceDirectionToPoint(Vector3 const objectSpaceDirection, Vector3 const point);
		
	public:
		Matrix4 const			resolveProjectionMatrixIgnoringCache() const;
		Matrix4 const			resolveProjectionMatrix() const;		//	Creates a matrix which projects points into derived space defined by SRT parameters.
		Matrix4 const			resolveUnprojectionMatrix() const;		//	Creates a matrix which unprojects points from derived space defined by SRT parameters.
		
		
		
		
	private:
		Vector3					_t		=	Vector3(0.0f, 0.0f, 0.0f);
		Quaternion				_r		=	Quaternion::Utility::identity();
		Vector3					_s		=	Vector3(0.0f, 0.0f, 0.0f);
		
		////
		
		class Cache;
		mutable Cache*			_cache	=	nullptr;
	};
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__Transform__) */








