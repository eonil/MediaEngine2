//
//  main.cpp
//  Mathematics - Running Test - OSX
//
//  Created by Hoon H. on 2/9/14.
//
//

#include <iostream>

//#import <GLKit/GLKit.h>
//#include "ImplementationOnlyGLM.h"
//#include "Vector.h"
//
//
//namespace
//{
//	using namespace	Eonil::Improvisations::MediaEngine::Mathematics::Value;
//	
//	using	Size	=	size_t;
//	using	Scalar	=	float_t;
//	
//	
//	template <Size const DIM>
//	using	SCALAR_ARRAY		=	std::array<Scalar, DIM>;
//	
//	template <Size const DIM>
//	struct
//	TYPEMAP
//	{
//	};
//	template <>
//	struct
//	TYPEMAP<2>
//	{
//		using	COMPS	=	SCALAR_ARRAY<2>;
//		using	GLK		=	GLKVector2;
//		using	GLM		=	glm::vec2;
//		using	EONIL	=	Vector2;
//	};
//	template <>
//	struct
//	TYPEMAP<3>
//	{
//		using	COMPS	=	SCALAR_ARRAY<3>;
//		using	GLK		=	GLKVector3;
//		using	GLM		=	glm::vec3;
//		using	EONIL	=	Vector3;
//	};
//	template <>
//	struct
//	TYPEMAP<4>
//	{
//		using	COMPS	=	SCALAR_ARRAY<4>;
//		using	GLK		=	GLKVector4;
//		using	GLM		=	glm::vec4;
//		using	EONIL	=	Vector4;
//	};
//	
//	////
//	
//	template <Size const DIM>
//	union
//	Converter
//	{
//		using	ARRAY	=	typename TYPEMAP<DIM>::COMPS;
//		using	GLK		=	typename TYPEMAP<DIM>::GLK;
//		using	GLM		=	typename TYPEMAP<DIM>::GLM;
//		using	EONIL	=	typename TYPEMAP<DIM>::EONIL;
//		
//		ARRAY	array	=	{};
//		GLK		glk		=	{};
//		GLM		glm		=	{};
//		EONIL	eonil	=	{};
//		
//		Converter(ARRAY const& o) : array(o) {}
//		Converter(GLK const& o) : glk(o) {}
//		Converter(GLM const& o) : glm(o) {}
//		Converter(EONIL const& o) : eonil(o) {}
//		
//		Converter(Converter const& o) : array(o.array) {}
//		
//		operator ARRAY() const	{ return array; }
//		operator GLK() const	{ return glk; }
//		operator GLM() const	{ return glm; }
//		operator EONIL() const	{ return eonil; }
//	};
//	
//	using	CONV2	=	Converter<2>;
//	using	CONV3	=	Converter<3>;
//	using	CONV4	=	Converter<4>;
//	
//#define UNARY_VECTOR_OP(dim,opname,rawcall)					inline auto opname(CONV##dim const& a) -> decltype(rawcall(a)) { return rawcall(a); }
//#define BINARY_VECTOR_SCALAR_OP(dim,opname,rawcall)			inline auto opname(CONV##dim const& a, Scalar const& b) -> decltype(rawcall(a,b)) { return rawcall(a,b); }
//#define BINARY_VECTOR_VECTOR_OP(dim,opname,rawcall)			inline auto opname(CONV##dim const& a, CONV##dim const& b) -> decltype(rawcall(a,b)) { return rawcall(a,b); }
//#define TERNARY_VECTOR_VECTOR_SCALAR_OP(dim,opname,rawcall)	inline auto opname(CONV##dim const& a, CONV##dim const& b, Scalar const c) -> decltype(rawcall(a,b,c)) { return rawcall(a,b,c); }
//	
//	BINARY_VECTOR_SCALAR_OP			(2, equal,		GLKVector2AllEqualToScalar);
//	BINARY_VECTOR_VECTOR_OP			(2, equal,		GLKVector2AllEqualToVector2);
//	UNARY_VECTOR_OP					(2, negate,		GLKVector2Negate);
//	BINARY_VECTOR_SCALAR_OP			(2, add,		GLKVector2AddScalar);
//	BINARY_VECTOR_VECTOR_OP			(2, add,		GLKVector2Add);
//	BINARY_VECTOR_SCALAR_OP			(2, subtract,	GLKVector2SubtractScalar);
//	BINARY_VECTOR_VECTOR_OP			(2, subtract,	GLKVector2Subtract);
//	BINARY_VECTOR_SCALAR_OP			(2, multiply,	GLKVector2MultiplyScalar);
//	BINARY_VECTOR_VECTOR_OP			(2, multiply,	GLKVector2Multiply);
//	BINARY_VECTOR_SCALAR_OP			(2, divide,		GLKVector2DivideScalar);
//	BINARY_VECTOR_VECTOR_OP			(2, divide,		GLKVector2Divide);
//	BINARY_VECTOR_VECTOR_OP			(2, dot,		GLKVector2DotProduct);
////	BINARY_VECTOR_VECTOR_OP			(2, cross,		GLKVector2CrossProduct);
//	BINARY_VECTOR_VECTOR_OP			(2, min,		GLKVector2Minimum);
//	BINARY_VECTOR_VECTOR_OP			(2, max,		GLKVector2Maximum);
//	UNARY_VECTOR_OP					(2, normalize,	GLKVector2Normalize);
//	UNARY_VECTOR_OP					(2, length,		GLKVector2Length);
//	BINARY_VECTOR_VECTOR_OP			(2, distance,	GLKVector2Distance);
//	BINARY_VECTOR_VECTOR_OP			(2, project,	GLKVector2Project);
//	TERNARY_VECTOR_VECTOR_SCALAR_OP	(2, lerp,		GLKVector2Lerp);
//	
//	BINARY_VECTOR_SCALAR_OP			(3, equal,		GLKVector3AllEqualToScalar);
//	BINARY_VECTOR_VECTOR_OP			(3, equal,		GLKVector3AllEqualToVector3);
//	UNARY_VECTOR_OP					(3, negate,		GLKVector3Negate);
//	BINARY_VECTOR_SCALAR_OP			(3, add,		GLKVector3AddScalar);
//	BINARY_VECTOR_VECTOR_OP			(3, add,		GLKVector3Add);
//	BINARY_VECTOR_SCALAR_OP			(3, subtract,	GLKVector3SubtractScalar);
//	BINARY_VECTOR_VECTOR_OP			(3, subtract,	GLKVector3Subtract);
//	BINARY_VECTOR_SCALAR_OP			(3, multiply,	GLKVector3MultiplyScalar);
//	BINARY_VECTOR_VECTOR_OP			(3, multiply,	GLKVector3Multiply);
//	BINARY_VECTOR_SCALAR_OP			(3, divide,		GLKVector3DivideScalar);
//	BINARY_VECTOR_VECTOR_OP			(3, divide,		GLKVector3Divide);
//	BINARY_VECTOR_VECTOR_OP			(3, dot,		GLKVector3DotProduct);
//	BINARY_VECTOR_VECTOR_OP			(3, cross,		GLKVector3CrossProduct);
//	BINARY_VECTOR_VECTOR_OP			(3, min,		GLKVector3Minimum);
//	BINARY_VECTOR_VECTOR_OP			(3, max,		GLKVector3Maximum);
//	UNARY_VECTOR_OP					(3, normalize,	GLKVector3Normalize);
//	UNARY_VECTOR_OP					(3, length,		GLKVector3Length);
//	BINARY_VECTOR_VECTOR_OP			(3, distance,	GLKVector3Distance);
//	BINARY_VECTOR_VECTOR_OP			(3, project,	GLKVector3Project);
//	TERNARY_VECTOR_VECTOR_SCALAR_OP	(3, lerp,		GLKVector3Lerp);
//	
//	BINARY_VECTOR_SCALAR_OP			(4, equal,		GLKVector4AllEqualToScalar);
//	BINARY_VECTOR_VECTOR_OP			(4, equal,		GLKVector4AllEqualToVector4);
//	UNARY_VECTOR_OP					(4, negate,		GLKVector4Negate);
//	BINARY_VECTOR_SCALAR_OP			(4, add,		GLKVector4AddScalar);
//	BINARY_VECTOR_VECTOR_OP			(4, add,		GLKVector4Add);
//	BINARY_VECTOR_SCALAR_OP			(4, subtract,	GLKVector4SubtractScalar);
//	BINARY_VECTOR_VECTOR_OP			(4, subtract,	GLKVector4Subtract);
//	BINARY_VECTOR_SCALAR_OP			(4, multiply,	GLKVector4MultiplyScalar);
//	BINARY_VECTOR_VECTOR_OP			(4, multiply,	GLKVector4Multiply);
//	BINARY_VECTOR_SCALAR_OP			(4, divide,		GLKVector4DivideScalar);
//	BINARY_VECTOR_VECTOR_OP			(4, divide,		GLKVector4Divide);
//	BINARY_VECTOR_VECTOR_OP			(4, dot,		GLKVector4DotProduct);
//	BINARY_VECTOR_VECTOR_OP			(4, cross,		GLKVector4CrossProduct);
//	BINARY_VECTOR_VECTOR_OP			(4, min,		GLKVector4Minimum);
//	BINARY_VECTOR_VECTOR_OP			(4, max,		GLKVector4Maximum);
//	UNARY_VECTOR_OP					(4, normalize,	GLKVector4Normalize);
//	UNARY_VECTOR_OP					(4, length,		GLKVector4Length);
//	BINARY_VECTOR_VECTOR_OP			(4, distance,	GLKVector4Distance);
//	BINARY_VECTOR_VECTOR_OP			(4, project,	GLKVector4Project);
//	TERNARY_VECTOR_VECTOR_SCALAR_OP	(4, lerp,		GLKVector4Lerp);
//	
//	
//	
//}









int main(int argc, const char * argv[])
{

	// insert code here...
	std::cout << "Hello, World!\n";
    return 0;
}

