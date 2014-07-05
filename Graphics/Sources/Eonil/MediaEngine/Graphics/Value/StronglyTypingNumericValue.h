//
//  StronglyTypingNumericValue.h
//  Graphics
//
//  Created by Hoon H. on 3/26/14.
//
//

#pragma once
#include "../Common.h"
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN

namespace
Value
{
	/*!
	 @classdesign
	 This class is designed to be subclassed. Do not use this class with just an alias.
	 This class should semantically equal to the type `V`, and must behave exactly same.
	 
	 @discussion
	 This class is designed to provide compile-time type check for numeric variables with
	 different semantics. Type-local range dynamic assertion is allowed for each subclasses.
	 
	 Well-implemented compiler is highly expected to eliminate all the overhead of using of
	 this class instead of primitive numeric types. But if you want to be sure, then you
	 can just use conditional compilation macro.
	 
	 @param
	 T
	 Must be type of the final class.
	 */
	template <typename T, typename V>
	class
	StronglyTypingNumericValue
	{
		V	_v	{};
		
	public:
		StronglyTypingNumericValue(V const v) : _v(v) {}
		
		StronglyTypingNumericValue() {};
		StronglyTypingNumericValue(StronglyTypingNumericValue const& o) : _v(o._v) {}
		StronglyTypingNumericValue(StronglyTypingNumericValue&& o) = delete;				//	Move prohibited.
		~StronglyTypingNumericValue() {}
		
		operator V() const;
		
		auto	operator=(T const& o) -> T&;
		
		auto	operator==(T const& o) const -> bool;
		auto	operator!=(T const& o) const -> bool;
		
		auto	operator<=(T const& o) const -> bool;
		auto	operator>=(T const& o) const -> bool;
		
		auto	operator<(T const& o) const -> bool;
		auto	operator>(T const& o) const -> bool;
		
		auto	operator+(T const& o) const -> T;
		auto	operator-(T const& o) const -> T;
		auto	operator*(T const& o) const -> T;
		auto	operator/(T const& o) const -> T;
	};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	template <typename T, typename V>
	StronglyTypingNumericValue<T,V>::
	operator V() const
	{
		return	_v;
	}
	
	
	
	template <typename T, typename V> auto
	StronglyTypingNumericValue<T,V>::
	operator==(T const& o) const -> bool
	{
		return	_v == o._v;
	}
	template <typename T, typename V> auto
	StronglyTypingNumericValue<T,V>::
	operator!=(T const& o) const -> bool
	{
		return	_v != o._v;
	}
	
	
	
	template <typename T, typename V> auto
	StronglyTypingNumericValue<T,V>::
	operator<=(T const& o) const -> bool
	{
		return	_v <= o._v;
	}
	template <typename T, typename V> auto
	StronglyTypingNumericValue<T,V>::
	operator>=(T const& o) const -> bool
	{
		return	_v >= o._v;
	}
	
		
		
	template <typename T, typename V> auto
	StronglyTypingNumericValue<T,V>::
	operator<(T const& o) const -> bool
	{
		return	_v < o._v;
	}
	template <typename T, typename V> auto
	StronglyTypingNumericValue<T,V>::
	operator>(T const& o) const -> bool
	{
		return	_v > o._v;
	}
	
		
		
	template <typename T, typename V> auto
	StronglyTypingNumericValue<T,V>::
	operator+(T const& o) const -> T
	{
		return	_v + o._v;
	}
	template <typename T, typename V> auto
	StronglyTypingNumericValue<T,V>::
	operator-(T const& o) const -> T
	{
		return	_v - o._v;
	}
	template <typename T, typename V> auto
	StronglyTypingNumericValue<T,V>::
	operator*(T const& o) const -> T
	{
		return	_v * o._v;
	}
	template <typename T, typename V> auto
	StronglyTypingNumericValue<T,V>::
	operator/(T const& o) const -> T
	{
		return	_v / o._v;
	}
		
		
		
		
		
		
		
}
EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_END
	
