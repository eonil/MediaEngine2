//
//  Matrix.h
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/11/13.
//
//

#pragma once
#include "../Common.h"
#include "Vector.h"
#include "Quaternion.h"
#include "AxisAngle.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN
//		namespace
//		Matrix
//		{
//			template<typename M> auto	identity() -> M const;
//			
//			template<typename M> auto	invert(M const m) -> M const;
//			template<typename M> auto	transpose(M const m) -> M const;
//			
//			template<typename M> auto	scale(Scalar const f) -> M const;
//			template<typename M> auto	scale(Vector3 const f) -> M const;
//			template<typename M> auto	rotation(Quaternion const q) -> M const;
//			template<typename M> auto	rotation(AxisAngle const aa) -> M const;
//			template<typename M> auto	translation(Vector3 const v) -> M const;
//		};


template<size_t C>
struct
MatrixState
{
	Scalar		components[C*C];
};

extern template class	MatrixState<4>;











template<size_t C, typename M>
struct
SimpleMatrixAbstraction : public MatrixState<C>
{
	using	S	=	Scalar;
	
//	bool const	operator==(M const& other) const;
//	bool const	operator!=(M const& other) const;
	
	M const		operator+(M const& other) const;
	M const		operator-(M const& other) const;
	M const		operator*(M const& other) const;

	M const		operator*(S const&) const;
	
//				M const		inversion(bool* isInvertible = nullptr) const;		//!	@todo	Implement determinant parameter.
	M const		inversion() const;
	M const		transposition() const;
	
	bool const	hasNaN() const;
	
protected:
	struct
	Utility
	{
		Utility() = delete;
		
		static M const		zero();			//!	A 4x4 matrix with all zeros.
		static M const		identity();
		static M const		signalingNaN();
		
//		static M const		matrixWithScalars(Scalar const value[16]);
//		static M const		matrixWithRowVectors(Vector4 const value[4]);
//		static M const		matrixWithRowVectors(Vector4 const row0, Vector4 const row1, Vector4 const row2, Vector4 const row3);
//		static M const		matrixWithColumnVectors(Vector4 const value[4]);
//		static M const		matrixWithColumnVectors(Vector4 const column0, Vector4 const column1, Vector4 const column2, Vector4 const column3);
		
		static M const		scaleWithUniformScalar(Scalar const factor);
		static M const		scaleWithScalar(Scalar const x, Scalar const y, Scalar const z);
		static M const		scaleWithVector(Vector3 const factor);
		
		/*!
		 Creates a matrix which performs rotation transform.
		 
		 @param
		 factor
		 Positive angle result counter-clockwise direction rotation.
		 */
		static M const		rotationWithAxisAngle(AxisAngle const factor);
		static M const		rotationWithQuaternion(Quaternion const factor);
//		static M const		rotationByAngleAroundXAxis(Vector3 const angle);
//		static M const		rotationByAngleAroundYAxis(Vector3 const angle);
//		static M const		rotationByAngleAroundZAxis(Vector3 const angle);
		
		static M const		translationWithScalars(Scalar const x, Scalar const y, Scalar const z);
		static M const		translationWithVector(Vector3 const factor);
	};
	
private:
	friend class	Debugging::Doctor;
};

extern template class	SimpleMatrixAbstraction<4, Matrix4>;
























struct
Matrix4 : public SimpleMatrixAbstraction<4, Matrix4>
{
	/*
	 Decompositions.
	 */
	Vector3 const		scaleComponent() const;
	Quaternion const	rotationComponent() const;
	Vector3 const		translationComponent() const;
	
	
	/*!
	 Transform a spatial positioning point.
	 
	 @note
	 By default, transformation is all about position.
	 Anything else is special case.
	 
	 For example, if you want to transform normal-vector as well as
	 like its vertex position. Actually what you want to do is just
	 rotation only. Because normal vector must be placed at tangent
	 space origin, and have 1.0 length. So you will want to ignore
	 translation and scaling. Ideal solution is making a dedicated
	 matrix which performs only rotation, but usually that causes
	 extra memory and processing. And if matrices are multiplied several
	 times, it becomes more complicated. You need to build separated
	 rotation-only all over the hierarchy.
	 
	 General solution to save resources is just setting `w` component
	 to trigger ignoring translation. And normalizing result to get
	 length of 1. If you are sure that the matrix doesn't contain
	 scailing, normalization can be omitted.
	 
	 In skinned animation case, usually all the bones are just rotated.
	 So you can use same matrix for transforming vertex position and
	 normal without extra processing.
	 
	 @ref
	 http://gamedev.stackexchange.com/questions/14115/do-i-need-the-w-component-in-my-vector-class
	 */
	auto	transform(Vector3 const point) const -> Vector3;
	auto	transform(Vector4 const vector) const -> Vector4;
	auto	transform(Vector2 const point) const -> Vector2;
	
	struct
	Utility : public SimpleMatrixAbstraction<4, Matrix4>::Utility
	{
		Utility() = delete;
		
		
		
		
		/*!
		 Creates orthographic projection.
		 
		 @note
		 Same with `glOrtho`. Creates a orthographic projection matrix.
		 */
		static Matrix4 const	orthograph(Scalar const left, Scalar const right, Scalar const bottom, Scalar const top, Scalar const front, Scalar const back);
		
		
		
		
		/*!
		 Creates perspective projection.
		 
		 @discussion
		 The volume of visible area is defined by near plane. Size of far plane is defined relatively
		 by the near plane and distance.
		 
		 @note
		 Same with `glFrustum`. Creates a perspective projection matrix.
		 
		 Maybe you expect another type of function which accepts FOV value.
		 Anyway this is less ambiguous, more generic form of perspective projection, 
		 so this is the default form.
		 
		 @ref
		 See the picture at this site for illustration.
		 http://www.songho.ca/opengl/gl_transform.html#projection
		 */
		static Matrix4 const	perspective(Scalar const left, Scalar const right, Scalar const bottom, Scalar const top, Scalar const front, Scalar const back);

//		static Matrix4 const	perspectiveWithFieldOfView(Scalar const fieldOfViewInY, Scalar const aspectRatio, Scalar const nearZ, Scalar const farZ);
//		static Matrix4 const	observation(Vector3 const eye, Vector3 const center, Vector3 const up);																	//	Same with `gluLookAt`. Creates a transform matrix for a camera.

		
		
	};
}
__attribute__((aligned(16)));













EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END
