//
//  Interpolation.h
//  TheMagnetismGame
//
//  Created by Hoon H. on 14/5/22.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#pragma once
#include "../../Common.h"
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_BEGIN
namespace
_ImmatureFeaturesD1
{

	
	
	
	
		
	template <typename T>
	struct
	Interpolation
	{
		Interpolation() = delete;
		
		////
		
		static_assert(std::is_floating_point<T>::value, "The type T must be a floating-point number type.");
		
		static T const	ZERO	=	T(0);
		static T const	HALF	=	T(0.5);
		static T const	ONE		=	T(1);
		static T const	TWO		=	T(2);
		
		struct
		AsymmetricInfinite
		{
			/*!
			 @code
			 y = (base^x-1) / (base-1)
			 
			 @param
			 base
			 Must be larger then zero.
			 Set base > 1 to make ease-in style interpolation.
			 Set 0 < base < 1 to make ease-out style interpolation.
			 
			 @ref
			 http://fooplot.com/#W3sidHlwZSI6MCwiZXEiOiIoKDJeeCktMSkvKDItMSkiLCJjb2xvciI6IiNFMENENzAifSx7InR5cGUiOjAsImVxIjoiKCgxMF54KS0xKS8oMTAtMSkiLCJjb2xvciI6IiNGRkQ1MDAifSx7InR5cGUiOjAsImVxIjoiKCgxMDBeeCktMSkvKDEwMC0xKSIsImNvbG9yIjoiI0ZGQTgyNiJ9LHsidHlwZSI6MCwiZXEiOiIoKDEwMDAwXngpLTEpLygxMDAwMC0xKSIsImNvbG9yIjoiI0I1MDAwMCJ9LHsidHlwZSI6MCwiZXEiOiIoKCgxLzIpXngpLTEpLygoMS8yKS0xKSIsImNvbG9yIjoiIzZFOUU5MCJ9LHsidHlwZSI6MCwiZXEiOiIoKCgxLzEwKV54KS0xKS8oKDEvMTApLTEpIiwiY29sb3IiOiIjMTJBOEZGIn0seyJ0eXBlIjowLCJlcSI6IigoKDEvMTAwKV54KS0xKS8oKDEvMTAwKS0xKSIsImNvbG9yIjoiIzA1NUFFRCJ9LHsidHlwZSI6MCwiZXEiOiIoKCgxLzEwMDAwKV54KS0xKS8oKDEvMTAwMDApLTEpIiwiY29sb3IiOiIjMDAwNDgyIn0seyJ0eXBlIjoxMDAwLCJ3aW5kb3ciOlsiLTAuNSIsIjEuNSIsIi0wLjUiLCIxLjUiXSwiZ3JpZCI6WyIxIiwiMSJdLCJzaXplIjpbMzAwLDMwMF19XQ--
			 */
			static auto
			regularExponentiation(T const& value, T const& base) -> T
			{
				EONIL_DEBUG_ASSERT(base > ZERO);
				return	(std::pow(base, value)-ONE) / (base-ONE);
			}
			
			/*!
			 @code
			 y = x^2

			 @ref
			 http://fooplot.com/#W3sidHlwZSI6MCwiZXEiOiIiLCJjb2xvciI6IiMwMDAwMDAifSx7InR5cGUiOjIsImVxeCI6InMiLCJlcXkiOiJzXjIiLCJjb2xvciI6IiNmZjAwMDAiLCJzbWluIjoiLTEwIiwic21heCI6IjEwIiwic3N0ZXAiOiIuMDEifSx7InR5cGUiOjEwMDAsIndpbmRvdyI6WyItMS41MzU5OTk5OTk5OTk5OTk0IiwiMS41MzU5OTk5OTk5OTk5OTk0IiwiLTEuNTM1OTk5OTk5OTk5OTk5NCIsIjEuNTM1OTk5OTk5OTk5OTk5NCJdLCJncmlkIjpbIjEiLCIxIl0sInNpemUiOlszMDAsMzAwXSwiYXhlc2NvbG9yIjoiI0EzQTNBMyIsImdyaWRjb2xvciI6IiNFOEU4RTgifV0-
			 */
			static auto
			quadratic(T const& value) -> T
			{
				return	value * value;
			}
		};
		
		/*!
		 Interpolations which are symmetric by `y=-x` axis.
		 Also input/output ranges are exactly mapped to regaulr range `-1 ~ +1`.
		 
		 @discussion
		 Symmetricity and regularity provide several nice features.
		 You can derive many things by just multiplying `-1` or adding `+/-1`.
		 */
		struct
		SymmetricInfinite
		{
			/*!
			 Sine function remapped to `-1 ~ +1` output range to make interpolation which passes `0,0` point.
			 
			 @code
			 y = sin(x/2 * PI)
			 
			 @discussion
			 This is an infinite, symmetric function.
			 
			 @note
			 Regular cosine graph is equal to regular sine.
			 
			 @ref
			 http://fooplot.com/#W3sidHlwZSI6MCwiZXEiOiJzaW4oeC8yKnBpKSIsImNvbG9yIjoiIzAwMDAwMCJ9LHsidHlwZSI6MTAwMCwid2luZG93IjpbIi0xLjUiLCIxLjUiLCItMS41IiwiMS41Il0sImdyaWQiOlsiMSIsIjEiXSwic2l6ZSI6WzMwMCwzMDBdLCJheGVzY29sb3IiOiIjQTNBM0EzIiwiZ3JpZGNvbG9yIjoiI0U4RThFOCJ9XQ--
			 */
			static auto
			regularSine(T const& value) -> T
			{
				return		std::sin(value * M_PI_2);
			}
			
			/*!
			 Tangent function remapped to `-1 ~ +1` output range to make interpolation which passes `0,0` point.
			 
			 @code
			 y = tan(x/4 * PI)
			 
			 @discussion
			 This is an infinite, symmetric function.
			 
			 @ref
			 http://fooplot.com/#W3sidHlwZSI6MCwiZXEiOiJ0YW4oeCpwaS80KSIsImNvbG9yIjoiIzAwMDAwMCJ9LHsidHlwZSI6MTAwMCwid2luZG93IjpbIi0xLjUiLCIxLjUiLCItMS41IiwiMS41Il0sImdyaWQiOlsiMSIsIjEiXSwic2l6ZSI6WzMwMCwzMDBdLCJheGVzY29sb3IiOiIjQTNBM0EzIiwiZ3JpZGNvbG9yIjoiI0U4RThFOCJ9XQ--
			 */
			static auto
			regularTangent(T const& value) -> T
			{
				return	std::tan(value * M_PI_4);
			}
			
			/*!
			 @code
			 f	x
			 |	x == 0		=	0
			 |	x > 0		=	x^2
			 |	x < 0		=	-(x^2)
			 
			 @discussion
			 This is nice for fast-slow-fast animation.

			 @ref
			 http://fooplot.com/#W3sidHlwZSI6MCwiZXEiOiIiLCJjb2xvciI6IiMwMDAwMDAifSx7InR5cGUiOjIsImVxeCI6InMiLCJlcXkiOiJzXjIiLCJjb2xvciI6IiNmZjAwMDAiLCJzbWluIjoiMCIsInNtYXgiOiIxMCIsInNzdGVwIjoiLjAxIn0seyJ0eXBlIjoyLCJlcXgiOiJzIiwiZXF5IjoiLShzXjIpIiwiY29sb3IiOiIjZmYwMDAwIiwic21pbiI6Ii0xMCIsInNtYXgiOiIwIiwic3N0ZXAiOiIuMDEifSx7InR5cGUiOjEwMDAsIndpbmRvdyI6WyItMS41MzU5OTk5OTk5OTk5OTk0IiwiMS41MzU5OTk5OTk5OTk5OTk0IiwiLTEuNTM1OTk5OTk5OTk5OTk5NCIsIjEuNTM1OTk5OTk5OTk5OTk5NCJdLCJncmlkIjpbIjEiLCIxIl0sInNpemUiOlszMDAsMzAwXSwiYXhlc2NvbG9yIjoiI0EzQTNBMyIsImdyaWRjb2xvciI6IiNFOEU4RTgifV0-
			 */
			static auto
			quadraticWithMirroringAtZero(T const& value) -> T
			{
				return	value > ZERO ? AsymmetricInfinite::quadratic(value) : -AsymmetricInfinite::quadratic(value);
			}
			
			/*!
			 A exponentiation interpolation where x > 0, and mirrored interpolation by y=x axis where x<0.
			 
			 @code
			 f	x
			 |	x == 0		=	0
			 |	x > 0		=	regularExponentiation(x,b)
			 |	x < 0		=	regularExponentiation(x+1,b)-1
			 
			 @ref	
			 http://fooplot.com/#W3sidHlwZSI6MiwiZXF4IjoicyIsImVxeSI6IigoMjBecyktMSkvKDIwLTEpIiwiY29sb3IiOiIjRTNDQzdGIiwic21pbiI6IjAiLCJzbWF4IjoiMTAwIiwic3N0ZXAiOiIuMDEifSx7InR5cGUiOjIsImVxeCI6InMiLCJlcXkiOiIoKCgxLzIwKV4ocysxKSktMSkvKCgxLzIwKS0xKS0xIiwiY29sb3IiOiIjNzU4Q0JEIiwic21pbiI6Ii0xMDAiLCJzbWF4IjoiMCIsInNzdGVwIjoiLjAxIn0seyJ0eXBlIjoxMDAwLCJ3aW5kb3ciOlsiLTEuNSIsIjEuNSIsIi0xLjUiLCIxLjUiXSwiZ3JpZCI6WyIxIiwiMSJdLCJzaXplIjpbMzAwLDMwMF19XQ--
			 */
			static auto
			exponentiationWithMirroringAtZero(T const value, T const base) -> T
			{
				return	value < ZERO ? (AsymmetricInfinite::regularExponentiation(value, base)) : (AsymmetricInfinite::regularExponentiation(value+ONE, ONE/base))-ONE;
			}
		};
		
		
		
		
		
		
		
		struct
		ClampingNormalization
		{
			/*!
			 Normalize a value into `0 ~ 1` range by clamping out overflow/undeflow.
			 */
			static auto
			normalizeAsTimeByClamping(T const value) -> T
			{
				return	std::min(std::max(value, 0), 1);
			}
			
			struct
			Sine
			{
				/*!
				 Ease in function.
				 
				 @discussion
				 This is a transformed (inverted) regular-sine function with clamping normalization.
				 This is not a symmetric function. Input value will be normalized into `0 ~ 1` range.
				 
				 @ref
				 http://fooplot.com/#W3sidHlwZSI6MCwiZXEiOiIxLXNpbigoMS14KS8yKnBpKSIsImNvbG9yIjoiI0ZGRThFOCJ9LHsidHlwZSI6MiwiZXF4IjoicyIsImVxeSI6IjEtc2luKCgxLXMpLzIqcGkpIiwiY29sb3IiOiIjZmYwMDAwIiwic21pbiI6IjAiLCJzbWF4IjoiMSIsInNzdGVwIjoiLjAxIn0seyJ0eXBlIjoxMDAwLCJ3aW5kb3ciOlsiLTAuNSIsIjEuNSIsIi0wLjUiLCIxLjUiXSwiZ3JpZCI6WyIxIiwiMSJdLCJzaXplIjpbMzAwLDMwMF0sImF4ZXNjb2xvciI6IiNBM0EzQTMiLCJncmlkY29sb3IiOiIjRThFOEU4In1d
				 */
				static auto
				easeIn(T const& value) -> T
				{
					T const		time	=	normalizeAsTime(value);
					return		ONE - regularSine(ONE - value);
				}
				
				/*!
				 Ease out function.
				 
				 @discussion
				 This is a regular-sine function with clamping normalization.
				 This is not a symmetric function. Input value will be normalized into `0 ~ 1` range.
				 
				 @ref
				 http://fooplot.com/#W3sidHlwZSI6MCwiZXEiOiJzaW4oeC8yKnBpKSIsImNvbG9yIjoiI0ZGRThFOCJ9LHsidHlwZSI6MiwiZXF4IjoicyIsImVxeSI6InNpbihzLzIqcGkpIiwiY29sb3IiOiIjZmYwMDAwIiwic21pbiI6IjAiLCJzbWF4IjoiMSIsInNzdGVwIjoiLjAxIn0seyJ0eXBlIjoxMDAwLCJ3aW5kb3ciOlsiLTAuNSIsIjEuNSIsIi0wLjUiLCIxLjUiXSwiZ3JpZCI6WyIxIiwiMSJdLCJzaXplIjpbMzAwLDMwMF0sImF4ZXNjb2xvciI6IiNBM0EzQTMiLCJncmlkY29sb3IiOiIjRThFOEU4In1d
				 */
				static auto
				easeOut(T const& value) -> T
				{
					T const		time	=	normalizeAsTime(value);
					return		regularSine(value);
				}
				
				/*!
				 Ease in/out function.
				 
				 @discussion
				 This is a regular-sine function transforms by `+0.5, +0.5`.
				 This is not a symmetric function. Input value will be normalized into `0 ~ 1` range.
				 
				 @ref
				 http://fooplot.com/#W3sidHlwZSI6MCwiZXEiOiJzaW4oKHgtMC41KSoyLzIqcGkpLzIrMC41IiwiY29sb3IiOiIjRkZFOEU4In0seyJ0eXBlIjoyLCJlcXgiOiJzIiwiZXF5Ijoic2luKChzLTAuNSkqMi8yKnBpKS8yKzAuNSIsImNvbG9yIjoiI2ZmMDAwMCIsInNtaW4iOiIwIiwic21heCI6IjEiLCJzc3RlcCI6Ii4wMSJ9LHsidHlwZSI6MTAwMCwid2luZG93IjpbIi0wLjUiLCIxLjUiLCItMC41IiwiMS41Il0sImdyaWQiOlsiMSIsIjEiXSwic2l6ZSI6WzMwMCwzMDBdLCJheGVzY29sb3IiOiIjQTNBM0EzIiwiZ3JpZGNvbG9yIjoiI0U4RThFOCJ9XQ--
				 */
				static auto
				easeInOut(T const& value) -> T
				{
					T const		time	=	normalizeAsTime(value);
					return		regularSine((value - HALF) * TWO) / TWO + HALF;
				}
			};
			
			struct
			Quadratic
			{
				/*!
				 */
				static auto
				easeIn(T const& value) -> T
				{
					T const		time	=	normalizeAsTime(value);
					return		AsymmetricInfinite::quadratic(value);
				}
				
				/*!
				 */
				static auto
				easeOut(T const& value) -> T
				{
					T const		time	=	normalizeAsTime(value);
					return		-AsymmetricInfinite::quadratic(value-1)+1;
				}
				
				/*!
				 */
				static auto
				easeInOut(T const& value) -> T
				{
					T const		time	=	normalizeAsTime(value);
					return		SymmetricInfinite::quadraticWithMirroringAtZero((value - HALF) * TWO) / TWO + HALF;
				}
			};
			
			struct
			Exponentiation
			{
				/*!
				 */
				static auto
				easeIn(T const& value, T const& base) -> T
				{
					T const		time	=	normalizeAsTime(value);
					return		AsymmetricInfinite::regularExponentiation(value, base);
				}
				
				/*!
				 */
				static auto
				easeOut(T const& value, T const& base) -> T
				{
					T const		time	=	normalizeAsTime(value);
					return		AsymmetricInfinite::regularExponentiation(value+ONE, ONE/base)-ONE;
				}
				
				/*!
				 */
				static auto
				easeInOut(T const& value, T const& base) -> T
				{
					T const		time	=	normalizeAsTime(value);
					return		SymmetricInfinite::exponentiationWithMirroringAtZero((value - HALF) * TWO, base) / TWO + HALF;
				}
			};
		};
		
		

	};











}
EONIL_MEDIA_ENGINE_MATHEMATICS_GEOMETRY_NAMESPACE_END
