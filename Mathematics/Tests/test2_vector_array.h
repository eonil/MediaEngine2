





/*!
 Having a long list of vector/matrix is stupid diea because SIMD instructions targets only
 short vectors. (usually 128bits/512bits)
 
 If you want better parallelism, you need threads, and the best choice will be GPU.
 I believe I am already utilizing most of SIMD instructions by using GLKit.
 Just push them into GPU.
 
 Apple's accelerate framework (vecLib) is not designed for game-like job, and it is employing GCD.
 It doesn't seem to be better unless we have massive (I think it's more than 1,000,000) amount
 of data to deal with.
 
 @ref
 http://www.yosefk.com/blog/simd-simt-smt-parallelism-in-nvidia-gpus.html
 
 
 */










////
////  test2_vector_array.h
////  Mathematics
////
////  Created by Hoon H. on 14/5/24.
////
////
//
//#pragma once
//#include "test_common.h"
//
//
//
//
//
//
////class
////Vector4Array
////{
////public:
////	auto	operator+(Vector4Array const&) const -> Vector4Array;
////	auto	operator+=(Vector4Array const&) -> Vector4Array&;
////	
////private:
////	std::vector<Vector4>	_vs	=	{};
////};
//
//
//
//
//
//
//
//
//
//
//template <Size const C>	class	BooleanOperationArray;
//template <Size const C>	class	IntegerOperationArray;
//template <Size const C>	class	Vector4OperationArray;
//template <Size const C>	class	ScalarOperationArray;
//template <Size const C>	class	Vector4OperationArray;
//
//
//
///*!
// This provides better auto-vectorization.
// You also can provide explicit SIMD call optimization.
// */
//template <typename T, Size const C>
//class
//BasicNumericOperationArray
//{
//	using	CLASS	=	BasicNumericOperationArray;
//	
//public:
//	auto	size() const -> Size;
//	
//public:
//	auto	operator==(CLASS const&) const -> BooleanOperationArray<C>;
//	auto	operator!=(CLASS const&) const -> BooleanOperationArray<C>;
//	
//	auto	operator<(CLASS const&) const -> BooleanOperationArray<C>;
//	auto	operator<=(CLASS const&) const -> BooleanOperationArray<C>;
//	
//	auto	operator>(CLASS const&) const -> BooleanOperationArray<C>;
//	auto	operator>=(CLASS const&) const -> BooleanOperationArray<C>;
//	
//	auto	operator+(CLASS const&) const -> CLASS;
//	auto	operator-(CLASS const&) const -> CLASS;
//	auto	operator*(CLASS const&) const -> CLASS;
//	auto	operator/(CLASS const&) const -> CLASS;
//	
//	
//public:
//	struct
//	Utility
//	{
//		auto	minimum(CLASS const& a, CLASS const& b) -> CLASS;
//		auto	maximum(CLASS const& a, CLASS const& b) -> CLASS;
//	};
//	
//private:
//	std::array<T, C>	_atoms	=	{};
//};
//
//
//
//
//
//
//
//
//
//
//
//
//template <typename T, Size const C>
//auto
//BasicNumericOperationArray<T, C>::
//operator+(const CLASS &o1) const -> CLASS
//{
//	CLASS		o2	=	{};
//	for (Size i=0; i<C; i++)
//	{
//		o2._atoms[i]	=	_atoms[i] + o1._atoms[i];
//	}
//	return	o2;
//}
//
//template <typename T, Size const C>
//auto
//BasicNumericOperationArray<T, C>::
//operator-(const CLASS &o1) const -> CLASS
//{
//	CLASS		o2	=	{};
//	for (Size i=0; i<C; i++)
//	{
//		o2._atoms[i]	=	_atoms[i] - o1._atoms[i];
//	}
//	return	o2;
//}
//
//template <typename T, Size const C>
//auto
//BasicNumericOperationArray<T, C>::
//operator*(const CLASS &o1) const -> CLASS
//{
//	CLASS		o2	=	{};
//	for (Size i=0; i<C; i++)
//	{
//		o2._atoms[i]	=	_atoms[i] * o1._atoms[i];
//	}
//	return	o2;
//}
//
//template <typename T, Size const C>
//auto
//BasicNumericOperationArray<T, C>::
//operator/(const CLASS &o1) const -> CLASS
//{
//	CLASS		o2	=	{};
//	for (Size i=0; i<C; i++)
//	{
//		o2._atoms[i]	=	_atoms[i] / o1._atoms[i];
//	}
//	return	o2;
//}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//template <Size const C>
//class
//Vector4OperationArray : public BasicNumericOperationArray<Vector4, C>
//{
//	using	CLASS	=	Vector4OperationArray;
//	
//public:
//	auto	size() const -> Size;
//	
//public:
//	auto	norm() const -> CLASS;
//	auto	length() const -> ScalarOperationArray<C>;
//	auto	lengthSquare() const -> ScalarOperationArray<C>;
//};
//
//
//
//
//
//template <Size const C>
//class
//ScalarOperationArray : public BasicNumericOperationArray<Scalar, C>
//{
//	using	CLASS	=	ScalarOperationArray;
//};
//
//
//
//
//
//
//
//
//
//
//
