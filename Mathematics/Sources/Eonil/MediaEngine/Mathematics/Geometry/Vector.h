//
//  Vector.h
//  Mathematics
//
//  Created by Hoon Hwangbo on 6/10/13.
//
//

#pragma once
#include "../Common.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN



/*
 Any base classes must be treated as implementation details. It's subject to change at anytime.
 You must use only final concrete classes, and should not depend on subclassing hierarchy.
 */







#pragma mark	-	Hidden primitives.

template<Size C>
struct
VectorState
{
	static_assert(C >= 2 and C <= 4, "Component count `C` must be 2~4.");
	Scalar	v[C];
};










template<>
struct
VectorState<2>
{
	union
	{
		Scalar	components[2];
		struct
		{
			Scalar	x, y;
		};
		struct
		{
			Scalar	s, t;
		};
//					struct
//					{
//						Scalar	r, g;
//					};
	};
}
__attribute__((aligned(8)));

template<>
struct
VectorState<3>
{
	union
	{
		Scalar	components[3];
		struct
		{
			Scalar	x, y, z;
		};
		struct
		{
			Scalar	s, t, p;
		};
//					struct
//					{
//						Scalar	r, g, b;
//					};
	};
};

template<>
struct
VectorState<4>
{
	union
	{
		Scalar	components[4];
		struct
		{
			Scalar	x, y, z, w;
		};
		struct
		{
			Scalar	s, t, p, q;
		};
//					struct
//					{
//						Scalar	r, g, b, a;
//					};
	};
}
__attribute__((aligned(16)));

extern template class	VectorState<2>;
extern template class	VectorState<3>;
extern template class	VectorState<4>;










////


template<Size C, typename V>
struct
VectorAbstraction : public VectorState<C>
{
	static_assert(C >= 2 and C <= 4, "Component count `C` must be 2~4.");
	static_assert(std::is_same<V, Vector2>::value or std::is_same<V, Vector3>::value or std::is_same<V, Vector4>::value, "Vector type `V` must be one of designated vector types.");
};

extern template class	VectorAbstraction<2, Vector2>;
extern template class	VectorAbstraction<3, Vector3>;
extern template class	VectorAbstraction<4, Vector4>;






template<Size C, typename V>
struct
SimpleVectorAbstraction : public VectorAbstraction<C, V>
{
	static_assert(C >= 2 and C <= 4, "Component count `C` must be 2~4.");
	static_assert(std::is_same<V, Vector2>::value or std::is_same<V, Vector3>::value or std::is_same<V, Vector4>::value, "Vector type `V` must be one of designated vector types.");
	
private:
	typedef		Scalar	S;
	
protected:
	struct
	Utility
	{
		static V const	signalingNaN();			//!	A vector with all components are set to signaling NAN.
		static V const	infinity();				//!	A vector with all components are set to INFINITE.
		
//					static S const	lengthOfVector(V const value);
//					static S const	lengthSquareOfVector(V const value);
		
		static S const	distanceBetweenVectors(V const left, V const right);
//					static V const	normalizationOfVector(V const value);
		
		static V const	minimumOfVectors(V const left, V const right);		//!	Creates a vector only with smallest components.
		static V const	maximumOfVectors(V const left, V const right);		//!	Creates a vector only with biggest components.
		static S const	dotProductionOfVectors(V const left, V const right);
		
		static V const	vectorUsingLinearInterpolationBetweenVectors(V const begin, V const end, Scalar const time);
		static V const	vectorUsingCatmullRomSplineBetweenVectors(V const prebegin, V const begin, V const end, V const postend, Scalar const time);
	};
	
public:
	bool const	operator==(V const& other) const;
	bool const	operator!=(V const& other) const;
	
	V const		operator+() const;
	V const		operator-() const;
	
	V const		operator+(V const& other) const;	//	Per-component operation.
	V const		operator-(V const& other) const;	//	Per-component operation.
	V const		operator*(V const& other) const;	//	Per-component operation.
	V const		operator/(V const& other) const;	//	Per-component operation.
	
	V const		operator+(S const& other) const;	//	Per-component operation.
	V const		operator-(S const& other) const;	//	Per-component operation.
	V const		operator*(S const& other) const;	//	Per-component operation.
	V const		operator/(S const& other) const;	//	Per-component operation.
	
	S const		length() const;
	S const		lengthSquare() const;
	V const		norm() const;
	S const		distanceToVector(V const target) const;
	S const		dotProductionWithVector(V const pair) const;
	V const		projectionOntoVector(V const target) const;
};
//			template<Size C, typename V>
//			struct
//			ComplexVectorAbstraction : public SimpleVectorAbstraction<C, V>
//			{
//				static_assert(C >= 3 and C <= 4, "Component count `C` must be 3~4. 2D vector is not supported.");
//				static_assert(std::is_same<V, Vector3>::value or std::is_same<V, Vector4>::value, "Vector type `V` must be one of designated vector types.");
//				
//			protected:
//				struct
//				Utility : public SimpleVectorAbstraction<C, V>::Utility
//				{
//					static V const	crossProductionOfVectors(V const a, V const b);
//				};
//			public:
//				V const		crossProductionWithVector(V const pair) const;
//			};
//			
//

extern template class	SimpleVectorAbstraction<2, Vector2>;
extern template class	SimpleVectorAbstraction<3, Vector3>;
extern template class	SimpleVectorAbstraction<4, Vector4>;





































#pragma mark	-	Final derivations.




struct
Vector2 final : public SimpleVectorAbstraction<2, Vector2>
{
	Vector2() = default;
	Vector2(Scalar const x, Scalar const y);
	
	struct
	Utility : public SimpleVectorAbstraction<2, Vector2>::Utility
	{
	};
}
__attribute__((aligned(8)));

static_assert(sizeof(Vector2) == sizeof(Scalar) * 2, "Size of Vector4 must be 8 bytes.");
static_assert(sizeof(Vector2) == 8, "Size of Vector4 must be 8 bytes.");

struct
Vector3 final : public SimpleVectorAbstraction<3, Vector3>
{
	Vector3() = default;
	Vector3(Vector2 const v2, Scalar const z);
	Vector3(Scalar const x, Scalar const y, Scalar const z);
	
	Vector3 const		crossProductionWithVector(Vector3 const pair) const;
	
	struct
	Utility : public SimpleVectorAbstraction<3, Vector3>::Utility
	{
		static Scalar const		angleBetweenVectorsOnPlane(Vector3 const a, Vector3 const b, Vector3 const planeAxis);			//!	Parameters should be normalized.
		static Vector3 const	crossProductionOfVectors(Vector3 const a, Vector3 const b);
	};
};
static_assert(sizeof(Vector3) == sizeof(Scalar) * 3, "Size of Vector3 must be 12 bytes.");
static_assert(sizeof(Vector3) == 12, "Size of Vector3 must be 12 bytes.");

struct
Vector4 final : public SimpleVectorAbstraction<4, Vector4>
{
	Vector4() = default;
	Vector4(Vector3 const v3, Scalar const w);
	Vector4(Vector2 const v2, Scalar const z, Scalar const w);
	Vector4(Scalar const x, Scalar const y, Scalar const z, Scalar const w);
	
	struct
	Utility : public SimpleVectorAbstraction::Utility
	{
	};
}
__attribute__((aligned(16)));


























#pragma mark	-	Short-form free functions.

template<typename V>	V const			min(V const left, V const right);
template<typename V>	V const			max(V const left, V const right);

//		template<typename V>	V const			add(V const left, V const right);
//		template<typename V>	V const			mul(V const left, V const right);

template<typename V>	Scalar const	dot(V const left, V const right);
template<typename V>	V const			cross(V const left, V const right);
template<typename V>	V const			lerp(V const begin, V const end, Scalar const time);




















EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END
