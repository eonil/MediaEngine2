//
//  Animation.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/14/13.
//
//

#include "Animation.h"


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Resource
	{
		template<typename V>
		AnimationCurve<V>::Sampler::Sampler(Channel const channel) : _ch(channel)
		{
			EEGL_ASSERT_WITH_REASON(channel.keys.size() > 0, "Animation channel must have at least 1 key.");
		};
		
		template<typename V> auto
		AnimationCurve<V>::Sampler::sampleAtTime(const Size time) const -> V const
		{
			return	_ch.keys.at(_ch.keys.size()).continuity ? sampleAtTimeWithLooping(time) : sampleAtTimeWithClamping(time);
		}
		
		template<typename V> auto
		AnimationCurve<V>::Sampler::sampleAtTimeWithLooping(const Size time) const -> V const
		{
			Size const	t2	=	time % _ch.keys.size();
			return	_sampleAtTimeWithinRange(t2);
		}
		template<typename V> auto
		AnimationCurve<V>::Sampler::sampleAtTimeWithClamping(const Size time) const -> V const
		{
			Size const	t2	=	std::min(_ch.keys.size()-1, time);
			return	_sampleAtTimeWithinRange(t2);
		}
		template<typename V> auto
		AnimationCurve<V>::Sampler::_sampleAtTimeWithinRange(const Size time) const -> V const
		{
			{
				//	Linear unopt. impl.
				return	_sampleAtTimeUsingForwardSearchFromIndex(time, 0);

				//	Optimized impl.
//					Debug::EEGL_ASSERT(_cache.key_idx_speculation_for_next_ref_speculation <= _ch.keys.size());
//					
//					Size	spec_idx	=	_cache.key_idx_speculation_for_next_ref_speculation;
//					Size	spec_time	=	_ch.keys[spec_idx].time;
//					
//					if (spec_time == timeInTicks)
//					{
//						_cache.key_idx_speculation_for_next_ref_speculation++;
//						if (_cache.key_idx_speculation_for_next_ref_speculation == _ch.keys.size())
//						{
//							_cache.key_idx_speculation_for_next_ref_speculation--;
//						}
//						return	_ch.keys[spec_idx].sample;
//					}
//					else
//					{
//						if (timeInTicks == 0)
//						{
//							return	_sampleAtTimeUsingForwardSearchFromIndex(0);
//						}
//						else
//						{
//							if (spec_time < timeInTicks)
//							{
//								return	_sampleAtTimeUsingForwardSearchFromIndex(spec_idx+1);
//							}
//							else
//							{
//								return	_sampleByPerformingBackwardSearchFromIndexForTime(spec_idx-1);
//							}
//						}
//					}
			}
		}
		
		template<typename V> auto
		AnimationCurve<V>::Sampler::_sampleAtTimeUsingForwardSearchFromIndex(const Size time, const Size index) const -> V const
		{
			Size const	c	=	_ch.keys.size();
			
			for (Size i=index; i<c; i++)
			{
				if (_ch.keys[i].time == time)
				{
					return	_ch.keys[i].sample;
				}
			}
			
			Debugging::Doctor::exceptWithReason("Cannot find animation sample for index.");
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		TransformAnimation::TransformAnimation(SS const ss, RS const rs, TS const ts) : _ss(ss), _rs(rs), _ts(ts)
		{
		}
		
		Transform const
		TransformAnimation::sampleAtTime(const Size time) const
		{
			Transform	t;
			t.setScale(_ss.sampleAtTime(time));
			t.setRotation(_rs.sampleAtTime(time));
			t.setTranslation(_ts.sampleAtTime(time));
			return		t;
		}
		
//			Matrix4 const
//			TransformAnimation::transformMatrixOfSampleAtTime(const Size time) const
//			{
//				
//			}
		
		
		
		
		
		
		template class	AnimationCurve<Scalar>;
		template class	AnimationCurve<Vector2>;
		template class	AnimationCurve<Vector3>;
		template class	AnimationCurve<Vector4>;
		template class	AnimationCurve<Quaternion>;
	}
	
	
	
	
	
	
	
}}}}







