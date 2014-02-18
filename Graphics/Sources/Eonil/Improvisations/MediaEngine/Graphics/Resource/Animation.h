//
//  Animation.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/14/13.
//
//

#ifndef __EonilGraphics__Animation__
#define __EonilGraphics__Animation__

#include "../Common.h"
#include "../Transform.h"
#include "Mesh.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Resource
	{
		using namespace Eonil::Improvisations::MediaEngine::Graphics::Value;
		
		/*!
		 @param V
		 Sample type `V` must be one of these types.
		 
		 -	`Scalar`
		 -	`Vector2`
		 -	`Vector3`
		 -	`Vector4`
		 -	`Quaternion`
		 
		 Any other types are not supported, but support may be expanded to some kind of
		 corresponding compressed types.
		 
		 @classdesign
		 `AnimationCurve` abstracts these stuffs.
		 
		 -	A specialized version of Catmull-Rom spline. (scale/translation)
		 -	A specialized version of Spherical quadratic interpolation curve. (a.k.a. squad, rotation)
		 
		 Scalar/vector will be interpolated using 1D Catmull-Rom spline for each component.
		 
		 Quaternion will be interpolated using squad. Quaternion is treated specially because it's a unit
		 of rotation which cannot be decomposed.
		 
		 @note
		 Source vector and quaternion should be interpolated and composed into final matrices intead of
		 interpolating each component of matrices to prevent strange result. Matrix interpolation doesn't
		 offer rigied transform.
		 
		 @ref
		 http://stackoverflow.com/questions/3093455/3d-geometry-how-to-interpolate-a-matrix#3124979
		 */
		template<typename V>
		struct
		AnimationCurve
		{
			static_assert(std::is_same<V, Scalar>::value or
						  std::is_same<V, Vector2>::value or
						  std::is_same<V, Vector3>::value or
						  std::is_same<V, Vector4>::value or
						  std::is_same<V, Quaternion>::value, "Unit type `V` of `AnimationCurve` must be one of pre-defined typed.");
			
			
			
			
			/*!
			 Time must be in range of 0~max(Size).
			 Negative time values are not supported.
			 If key continuity is false, control-tangent is treated as same with the key.
			 
			 @note
				 Keys are regularated by 1/60 interval manner for complete numerical accuracy.
				 If you have all the keys for each ticks, resampling won't be happen. This also
				 can offer better optimization chances.
			 */
			struct
			Key
			{
				Size	time;			//	Time is *tick* unit which is 1/60 second.
				bool	continuity;		//	`true` if curve before/after this key should smoothly continues.
				V		sample;			//	Actual value at this key point.
			};
			
			struct
			Channel
			{
				std::vector<Key>		keys;
			};
			
			/*!
			 @classdesign
			 There are two sampling modes.
			 
			 -	Clamp
			 -	Loop
			 
			 Clamp sampling adjust input time range by clamped within valid range.
			 Underflown/overflown values will become minimum/maximum time value in animation
			 duration.
			 
			 Loop sampling adjust input time value to the position as like the animation repeated
			 infinityly.
			 
			 Sampling mode can be chosen by continuity of the borderline(first/last) keys. Sampler
			 will use loop only if the key is continuous. 
			 
			 Interpolation will be affected properly by each sampling mode.
			 
			 @todo
			 Backward searching is not implemented yet. Implement it.
			 Interpolation is not implemented yet. Implement it.
			 Floating-point time sampling is not implemented yet due to lack of interpolation.
			 Implement it.
			 Search optimization using speculation is not well-test yet. Enable and test it.
			 */
			class
			Sampler
			{
			public:
				/*!
				 @param	channel			
				 Must have at least one key. Asserted no invali value in debug mode.
				 If both of first and last keys are set as continuous, it will be treated as
				 loop animation, and interpolated properly. In this case, both of the borderline 
				 keys should be continuous. Result undefiend if only one is continuous. (asserted
				 in debug build). It's possible to support one-side continuity, but intentionally
				 disabled for easier debugging. (also use-case is mostly none) Can be re-enabled
				 if there's strong request.
				 
				 @note
				 You can perform time stretching by querying subtick time value with floating-point
				 number.
				 */
				Sampler(Channel const channel);
				
//					V const		sampleAtTimeWithClamping(Scalar const time) const;
//					V const		sampleAtTimeWithLooping(Scalar const time) const;
//					V const		sampleAtTime(Scalar const time) const;			
				
				V const		sampleAtTimeWithClamping(Size const time) const;
				V const		sampleAtTimeWithLooping(Size const time) const;
				V const		sampleAtTime(Size const time) const;
				
			private:
				Channel const	_ch;
				
				mutable struct
				{
					/*!
					 @note
					 State sampling needs to search proper keys for the tick.
					 If keys are many, this is time consuming work which affects performance.
					 So we have to optimize this.
					 
					 Animations are mostly played in sequential manner. So if a key is referenced
					 in previous sampling, next sampling highly expected to need keys around it.
					 So storing only last referenced key can cover most cases very efficiently.
					 
					 Also, because client requests sample with integral time, and there's a key exactly
					 for the time, we don't need to perform resampling by interpolation. Just return
					 sample value at the key. 
					 
					 If sampling is done using exact time sample,store key index + 1.
					 If sampling is done using interpolation, store key at *end*.
					 */
					Size	key_idx_speculation_for_next_ref_speculation	=	0;
				}
				_cache;
				
				V const		_sampleAtTimeWithinRange(Size const time) const;
				V const		_sampleAtTimeUsingForwardSearchFromIndex(Size const time, Size const index) const;		//	Exact match, no resampling.
				V const		_sampleAtTimeUsingBackwardSearchFromIndex(Size const time, Size const index) const;		//	Exact match, no resampling.
				
				/*!
				 @param		time	Should be normalized into 0~1 to specify between `begin` and `end`.
				 */
				V const		_sampleWithKeys(Key const pre, Key const begin, Key const end, Key const post, Scalar const time) const;
			};
		};
		
		
		
		
		
		
		
		
		
		
		/*!
		 Full transform animation.
		 Stores all channels without compression.
		 */
		class
		TransformAnimation 
		{
			using				SS	=	AnimationCurve<Vector3>::Sampler;
			using				RS	=	AnimationCurve<Quaternion>::Sampler;
			using				TS	=	AnimationCurve<Vector3>::Sampler;
			
		public:
			TransformAnimation(SS const scaleSampler, RS const rotationSampler, TS const translationSampler);
			
			Transform const		sampleAtTime(Size const time) const;						//	Returns a copy.
//				Matrix4 const		transformMatrixOfSampleAtTime(Size const time) const;		//	Returns a copy.
			
		private:
			SS const			_ss;
			RS const			_rs;
			TS const			_ts;
		};
		
		
		
		
		
		
		/*!
		 Bone animation is highly compressed form of transform animation.
		 This supports only positioning and rotation, and uniform scaling.
		 
		 This is designed mainly to save storage size.
		 
		 @note
		 Bone transform matrix parameter to be passed to vertex shader should be
		 lightweight. So it needs to be limited to rotation quaternion and translation only.
		 Anyway that parameter should be resolved by decomposition of final galobal matrix.
		 */
		class
		BoneAnimation
		{
			using				SS	=	AnimationCurve<Scalar>::Sampler;
			using				RS	=	AnimationCurve<Quaternion>::Sampler;
			using				TS	=	AnimationCurve<Vector3>::Sampler;
			
			struct
			Sample
			{
				Quaternion		r;
				union
				{
					Vector4		ts;
					struct
					{
						Vector3	t;
						Scalar	s;
					};
				};
			};
			
		public:
			BoneAnimation(SS const scaleSampler, RS const rotationSampler, TS const translationSampler);
			
			Sample const		sampleAtTime(Size const time) const;						//	Returns a copy. Mainly for debugging.
		};
	}
	
	
	
	
	
	
	
}}}}


#endif /* defined(__EonilGraphics__Animation__) */















