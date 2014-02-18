//
//  _ModelImporterA.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/27/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics___ModelImporterA__
#define __EonilGraphics___ModelImporterA__

#include <string>
#include <vector>

#include "../_DEV_/_SkinnedMeshForm.h"



namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Transcoding
	{
		using namespace	Eonil::Improvisations::MediaEngine::Graphics;
		using namespace	Eonil::Improvisations::MediaEngine::Graphics::_DEV_;
		using namespace	Eonil::Improvisations::MediaEngine::Graphics::Value;
		
		
//		struct
//		_TransformA
//		{
//			Vector3		s	=	Vector3(1,1,1);
//			Quaternion	r	=	Quaternion::Utility::identity();
//			Vector3		t	=	Vector3(0,0,0);
//			
//			Matrix4 const		projectionMatrix() const;
//			Matrix4 const		unprojectionMatrix() const;
//		};
		
		
		/*!
		 @discussion
		 
		 Binding-pose is global transforms when the skinning is created.
		 Because skinning affection is calcuated by the control point's global transforms,
		 skinned mesh shouldn't be transformed before skinning. To get untransformed mesh, 
		 it should be untransformed with an inverted global transform matrix when the skinning
		 is being applied. The *binding pose* is the matrix.
		 
		 So, just apply the inversion of the pose-matrix before applying global transform.
		 
			skinning_transform	=		global_transform * invert(pose_transform)
		 
		 Take care stored binding pose is not pre-inverted. You need to invert it yourself.
		 */
		struct
		_MeshWithBonePaletteBinding_v1
		{
			_SkinnedForm::Mesh			meshCore;
			std::vector<std::string>	boneNamesAtPaletteIndexes;						//!	Bone name index must be match target bone in vertex skinning.
			std::vector<Matrix4>		bondBindingPoseMatricesAtPaletteIndexes;		//!	Binding pose.
		};
		
		
		struct
		_BoneA
		{
			std::string		name;
			Matrix4			defaultTransformMatrix	=	Matrix4::Utility::signalingNaN();

			std::shared_ptr<_MeshWithBonePaletteBinding_v1 const>		meshWithBonePaletteBinding	=	nullptr;
			std::vector<_BoneA>										subbones;
		};
		
		
		
		struct
		_Vector3AnimationCurveA
		{
			struct
			TimeSample
			{
				Vector3		value;
				uint32_t	time;
			}
			__attribute__((__packed__));
			std::vector<TimeSample>		samples;
			static_assert(sizeof(TimeSample) == (4*(3+1)),"");
		};
		struct
		_QuaternionAnimationCurveA
		{
			struct
			TimeSample
			{
				Quaternion	value;
				uint32_t	time;
				
				uint32_t	empty[3];
			}
			__attribute__((__packed__));
			std::vector<TimeSample>		samples;
			static_assert(sizeof(TimeSample) == (4*(4+1+3)),"");
		};
		struct
		_TransformAnimationA
		{
			_Vector3AnimationCurveA		s;
			_QuaternionAnimationCurveA	r;
			_Vector3AnimationCurveA		t;
		};
		
		
		
		
		
		struct
		_MotionA
		{
			using	Mapping			=	std::map<std::string, _TransformAnimationA>;		//!	Bone name to animation.
			using	Pair			=	std::pair<std::string, _TransformAnimationA>;
			
			std::string		name;
			Mapping			movements;
		};;
		
		
		
		struct
		_ModelA
		{
			using	MotionMapping	=	std::map<std::string, _MotionA>;		//!	Bone name to animation.
			using	MotionPair		=	std::pair<std::string, _MotionA>;
			
			using	Ref				=	std::shared_ptr<_ModelA const>;

			_BoneA			skeleton;
			MotionMapping	motions;
		};
		
		
		
		
		
		
		
		
		/*!
		 DEPRECATED. DO NOT USE THIS ANYMORE.
		 
		 Any way kept for archiving purpose. Because this is very bare-bone, straight implementation,
		 it's easest to know, understand, and modify from.
		 */
		struct
		_ModelImporterA
		{
			static _ModelA::Ref const		readModelFromFileAtPath(std::string const path);
			static _ModelA::Ref const		readModelFromStream(std::istream& s);
		};
		
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___ModelImporterA__) */



