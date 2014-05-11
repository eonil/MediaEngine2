//
//  ConstantEvaluationUtility.h
//  Foundation
//
//  Created by Hoon H. on 5/11/14.
//
//

#ifndef __Foundation__ConstantEvaluationUtility__
#define __Foundation__ConstantEvaluationUtility__
#include "../Common.h"
#include "../Numerics.h"
namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Foundation {
	inline namespace
	D2014R1			//	Distribution 2014, revision 1.
	{

	
		
		
		
		
		
		
		namespace
		ConstantEvaluation
		{
			
			
			
			
			
			
			
			template <typename T>
			constexpr inline auto
			void_aware_sizeof() -> Size const
			{
				return	sizeof(T);
			};
			template <>
			constexpr inline auto
			void_aware_sizeof<void>() -> Size const
			{
				return	0;
			};
			template <>
			constexpr inline auto
			void_aware_sizeof<void const>() -> Size const
			{
				return	0;
			};
			
			
			
			
			
			
			
			
		}
		
		
		
		
		
		
		

	}
}}}}
#endif /* defined(__Foundation__ConstantEvaluationUtility__) */
