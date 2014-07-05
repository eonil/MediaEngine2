////
////  _ModelRendererA.cpp
////  EonilGraphics
////
////  Created by Hoon Hwangbo on 7/27/13.
////  Copyright (c) 2013 Eonil. All rights reserved.
////
//
//#include "_ModelRendererA.h"
//
//#include "../Common.h"
//#include "../Debugging/Doctor.h"
//#include "../_DEV_/_Regulator.h"
//#include "../_DEV_/_DevRenderer.h"
//#include "../Transcoding/_ModelImporterA.h"
//
//
//
//#define	RENDER_ASSERT				EEGL_ASSERT
//#define	RENDER_DEBUG_RUN			EEGL_RUN_AS_ASSERTION
//
//
//
//EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
//	
//	namespace
//	Rendering
//	{
//	
//		
//		
//		using namespace	Debugging;
//		using namespace	Transcoding;
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
//		namespace
//		{
//			Vector3 const
//			sampleVector3AtTimeInCurve(_Vector3AnimationCurveA const curve, Size const time)
//			{
//				for (Size i=0; i<curve.samples.size(); i++)
//				{
//					if (curve.samples.at(i).time == time)
//					{
//						Vector3	v	=	curve.samples.at(i).value;
//						RENDER_DEBUG_RUN(Doctor::assertVector4Validity(Vector4(v, 0)));
//						return	v;
//					}
//				}
//				Doctor::exceptWithReason("Actualy sampling is not currently supported. This will be added later.");
//			}
//			Quaternion const
//			sampleQuaternionAtTimeInCurve(_QuaternionAnimationCurveA const curve, Size const time)
//			{
//				for (Size i=0; i<curve.samples.size(); i++)
//				{
//					if (curve.samples.at(i).time == time)
//					{
//						Quaternion	v	=	curve.samples.at(i).value;
//						//							RENDER_DEBUG_RUN(Doctor::assertVector4Validity(Vector4(v.asAxisAngle().axis, 0)));
//						//							RENDER_DEBUG_RUN(Doctor::assertVector4Validity(Vector4(v.asAxisAngle().angle, 0,0,0)));
//						return		v;
//					}
//				}
//				Doctor::exceptWithReason("Actualy sampling is not currently supported. This will be added later.");
//			}
//			
//			
//			
//			struct
//			BoneMomentResolver
//			{
//				_TransformAnimationA const&		movement;
//				
//				BoneMomentResolver(_TransformAnimationA const& movement) : movement(movement)
//				{
//				}
//				
//				Vector3 const
//				sampleScaleAtTime(Size const time)
//				{
//					Vector3		v	=	sampleVector3AtTimeInCurve(movement.s, time);
//					RENDER_DEBUG_RUN(Doctor::assertVector4Validity(Vector4(v, 1)));
//					return		v;
//				}
//				Quaternion const
//				sampleRotationAtTime(Size const time)
//				{
//					Quaternion	q	=	sampleQuaternionAtTimeInCurve(movement.r, time);
//					RENDER_DEBUG_RUN(Doctor::assertVector4Validity(*(Vector4*)&q));
//					return		q;
//				}
//				Vector3 const
//				sampleTranslationAtTime(Size const time)
//				{
//					Vector3		v	=	sampleVector3AtTimeInCurve(movement.t, time);
//					RENDER_DEBUG_RUN(Doctor::assertVector4Validity(Vector4(v, 1)));
//					return		v;
//				}
//				
//				Matrix4 const
//				sampleTransformMatrixAtTime(Size const time)
//				{
//					Matrix4		s_tm	=	Matrix4::Utility::scaleWithVector(sampleScaleAtTime(time));
//					Matrix4		r_tm	=	Matrix4::Utility::rotationWithQuaternion(sampleRotationAtTime(time));
//					Matrix4		t_tm	=	Matrix4::Utility::translationWithVector(sampleTranslationAtTime(time));
//					
//					Matrix4		all_tm	=	t_tm * r_tm * s_tm;
//					
//					RENDER_DEBUG_RUN(Doctor::assertMatrix4Validity(s_tm));
//					RENDER_DEBUG_RUN(Doctor::assertMatrix4Validity(r_tm));
//					RENDER_DEBUG_RUN(Doctor::assertMatrix4Validity(t_tm));
//					RENDER_DEBUG_RUN(Doctor::assertMatrix4Validity(all_tm));
//					return		all_tm;
//				}
//			};
//			
//			struct
//			ModelMomentResolver
//			{
//				_MotionA const&	motion;
//				
//				ModelMomentResolver(_MotionA const& motion) : motion(motion)
//				{
//				}
//				
//				Matrix4 const
//				transformAtTimeForBoneName(Size const time, _BoneA const& bone)
//				{
//					RENDER_ASSERT(bone.name.length() > 0);
//					
//					/*!
//					 Some bones don't have animation. In that case treat default transform
//					 is being kept.
//					 */
//					if (motion.movements.find(bone.name) == motion.movements.end())
//					{
//						Matrix4 const				tm	=	bone.defaultTransformMatrix;
//						
//						RENDER_DEBUG_RUN(Doctor::assertMatrix4Validity(tm));
//						return						tm;
//					}
//					else
//					{
//						_TransformAnimationA const&	ta	=	motion.movements.at(bone.name);
//						Matrix4 const				tm	=	BoneMomentResolver(ta).sampleTransformMatrixAtTime(time);
//						
//						RENDER_DEBUG_RUN(Doctor::assertMatrix4Validity(tm));
//						return						tm;
//					}
//				}
//				
//				//				TransformPalette
//				//				transformPaletteAtTimeWithNamePalette(Size const time, NamePalette const namePalette)
//				//				{
//				//					RENDER_ASSERT(namePalette.size() > 0);
//				//
//				//					TransformPalette	tm_pal;
//				//					Size	c	=	namePalette.size();
//				//					for (Size i=0; i<c; i++)
//				//					{
//				//						std::string	bname		=	namePalette.at(i);
//				//						Matrix4		b_local_tm	=	transformAtTimeForBoneName(time, bname);
//				//
//				//						tm_pal.push_back(b_local_tm);
//				//					}
//				//					return	tm_pal;
//				//				}
//			};
//		}
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
//		namespace
//		{
//			using	NamedBonePalette		=	std::map<std::string, Matrix4>;
//			using	NamedBonePair			=	std::pair<std::string, Matrix4>;
//			
//			using	BoneTransformResolver	=	std::function<Matrix4 const(_BoneA const& bone)>;
//			
//			void
//			ResolveBoneTransformMatrices(_BoneA const& bone, NamedBonePalette& pal, BoneTransformResolver const get_local_tm, Matrix4 const& parent_global_tm)
//			{
//				RENDER_ASSERT(&bone != nullptr);
//				RENDER_ASSERT(&pal != nullptr);
//				RENDER_ASSERT(get_local_tm != nullptr);
//				
//				Matrix4	const	current_local_tm	=	get_local_tm(bone);
//				Matrix4	const	current_global_tm	=	parent_global_tm * current_local_tm;
//				
//				pal.insert(NamedBonePair(bone.name, current_global_tm));
//				
//				for (_BoneA const& sb1 : bone.subbones)
//				{
//					ResolveBoneTransformMatrices(sb1, pal, get_local_tm, current_global_tm);
//				}
//			}
//			
//			void
//			ResolveBoneDefaultTransformMatrices(_BoneA const& bone, NamedBonePalette& pal, Matrix4 const& parent_global_tm = Matrix4::Utility::identity())
//			{
//				auto	getter	=	[](_BoneA const& bone)
//				{
//					return	bone.defaultTransformMatrix;
//				};
//				ResolveBoneTransformMatrices(bone, pal, getter, parent_global_tm);
//				
////				Matrix4	const	current_local_tm	=	bone.defaultTransformMatrix;
////				Matrix4	const	current_global_tm	=	parent_global_tm * current_local_tm;
////				
////				pal.insert(NamedBonePair(bone.name, current_global_tm));
////				
////				for (_BoneA const& sb1 : bone.subbones)
////				{
////					ResolveBoneDefaultTransformMatrices(sb1, pal, current_global_tm);
////				}
//			}
//			
//			
//			
//			
//			using	NamePalette			=	std::vector<std::string>;
//			using	TransformPalette	=	std::vector<Matrix4>;
//			
//			using	GlobalBoneTransformPaletteResolver	=	std::function<TransformPalette(NamePalette const& boneNamePalette, TransformPalette const& bindingPosePalette)>;
//			
//			
//			
//			
//			void
//			AddDrawingOfBoneToList(_BoneA const& bone, std::vector<_SkinnedForm>& list, GlobalBoneTransformPaletteResolver transformResolver)
//			{
//				if (bone.meshWithBonePaletteBinding != nullptr)
//				{
//					NamePalette			name_pal			=	bone.meshWithBonePaletteBinding->boneNamesAtPaletteIndexes;
//					TransformPalette	binding_pose_pal	=	bone.meshWithBonePaletteBinding->bondBindingPoseMatricesAtPaletteIndexes;
//					
//					_SkinnedForm	f1;
//					f1.mesh				=	bone.meshWithBonePaletteBinding->meshCore;
//					f1.transform		=	Matrix4::Utility::identity();
//					f1.bonePalette		=	transformResolver(name_pal, binding_pose_pal);
//					
//					list.push_back(f1);
//				}
//
//				for (_BoneA const& b2 : bone.subbones)
//				{
//					AddDrawingOfBoneToList(b2, list, transformResolver);
//				}
//			}
//		}
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
//		void
//		_ModelRendererA::addToList(const Rendering::_ModelRendererA::Moment moment, std::vector<_DEV_::_SkinnedForm> &list)
//		{
//			_ModelA const&	model	=	*(moment.model);
//			
//			{
//				auto				b_local_tm_res	=	[&moment](_BoneA const& bone) -> Matrix4
//				{
//					ModelMomentResolver	mmr(*(moment.motion));
//					return	mmr.transformAtTimeForBoneName(moment.time, bone);
//				};
//				
//				NamedBonePalette	pal;
//				ResolveBoneTransformMatrices(model.skeleton, pal, b_local_tm_res, Matrix4::Utility::identity());
//				//				ResolveBoneDefaultTransformMatrices(model.skeleton, pal);
//				
//				////
//				
//				auto	tres	=	[&pal](NamePalette const& bone_name_palette, TransformPalette const& binding_pose_palette) -> TransformPalette
//				{
//					RENDER_ASSERT(bone_name_palette.size() == binding_pose_palette.size());
//					
//					TransformPalette	btp;
//					Size				c	=	bone_name_palette.size();
//					for (Size i=0; i<c; i++)
//					{
//						std::string	bname	=	bone_name_palette.at(i);
//						Matrix4		bpose	=	binding_pose_palette.at(i);
//						
//						Matrix4	bone_global_tm		=	pal.at(bname);
//						Matrix4	skinning_global_tm	=	bone_global_tm * bpose.inversion();
//						
//						btp.push_back(skinning_global_tm);
//					}
//					return	btp;
//				};
//				
//				////
//				
//				AddDrawingOfBoneToList(model.skeleton, list, tres);
//			}
//			
//		}
//		
//		
//		
//		
//		void
//		_ModelRendererA::draw(const Value::Bounds2 bounds, const _DEV_::_DevCamera camera, const Moment moment)
//		{
//			using namespace Eonil::MediaEngine::Graphics::_DEV_;
//			
//			Bounds2		vpb1	=	bounds;
//			_Regulator	vp		=	_Regulator(vpb1, 0.5);
//			
//			////
//			
//			_DevRenderer::_DevScene		s;
//			
//			s.viewport				=	vp;
//			s.switches.depthTesting	=	true;
//			s.camera				=	camera;
//			addToList(moment, s.skinnedForms);
//			
//			_DevRenderer				r;
//			r.render(s);
//		}
//		
//
//
//
//		
//		
//		
//	}
//
//	
//	
//	
//	
//	
//	
//	
//	
//}}}}
//
//
//
//
//
//
