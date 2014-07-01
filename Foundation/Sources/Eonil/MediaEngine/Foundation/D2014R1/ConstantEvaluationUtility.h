//
//  ConstantEvaluationUtility.h
//  Foundation
//
//  Created by Hoon H. on 5/11/14.
//
//

#pragma once
#include "../Prelude.h"
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_BEGIN
inline namespace
D2014R1			//	Distribution 2014, revision 1.
{
	namespace
	ConstantEvaluation
	{
		
		
		
		
		
		
		
		template <typename T>
		constexpr inline auto
		void_aware_sizeof() -> sz const
		{
			return	sizeof(T);
		};
		template <>
		constexpr inline auto
		void_aware_sizeof<void>() -> sz const
		{
			return	0;
		};
		template <>
		constexpr inline auto
		void_aware_sizeof<void const>() -> sz const
		{
			return	0;
		};
		
		
		
		
		

		
		
		
		
	}
}
EONIL_MEDIA_ENGINE_FOUNDATION_NAMESPACE_END