//
//  _ModelImporter_v2.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/28/13.
//
//

#ifndef __EonilGraphics___ModelImporter_v2__
#define __EonilGraphics___ModelImporter_v2__



#include <string>
#include <vector>

#include "../Rendering/D2014R1/LEGACY_SkinnedForm_v2.h"



namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Transcoding
	{
		using namespace	Eonil::Improvisations::MediaEngine::Graphics;
		using namespace	Eonil::Improvisations::MediaEngine::Graphics::Rendering::D2014R1;
		using namespace	Eonil::Improvisations::MediaEngine::Graphics::Geometry;
		
		
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
		_MeshWithBonePaletteBinding_v2
		{
			_SkinnedForm_v2::Mesh::Ref	meshCore;
			std::vector<std::string>	boneNamesAtPaletteIndexes;						//!	Bone name index must be match target bone in vertex skinning.
			std::vector<Matrix4>		bondBindingPoseMatricesAtPaletteIndexes;		//!	Binding pose.
		};
		
		
		struct
		_Bone_v2
		{
			std::string		name;
			Matrix4			defaultTransformMatrix	=	Matrix4::Utility::signalingNaN();
			
			std::shared_ptr<_MeshWithBonePaletteBinding_v2 const>		meshWithBonePaletteBinding	=	nullptr;
			std::vector<_Bone_v2>										subbones;
		};
		
		
		
		struct
		_Vector3AnimationCurve_v2
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
		_QuaternionAnimationCurve_v2
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
		_TransformAnimation_v2
		{
			_Vector3AnimationCurve_v2		s;
			_QuaternionAnimationCurve_v2	r;
			_Vector3AnimationCurve_v2		t;
		};
		
		
		
		
		
		struct
		_Motion_v2
		{
			using	Mapping			=	std::map<std::string, _TransformAnimation_v2>;		//!	Bone name to animation.
			using	Pair			=	std::pair<std::string, _TransformAnimation_v2>;
			
			std::string		name;
			Mapping			movements;
		};;
		
		
		
		struct
		_Model_v2
		{
			using	MotionMapping	=	std::map<std::string, _Motion_v2>;		//!	Bone name to animation.
			using	MotionPair		=	std::pair<std::string, _Motion_v2>;
			
			using	Ref				=	std::shared_ptr<_Model_v2 const>;
			
			_Bone_v2			skeleton;
			MotionMapping	motions;
		};
		
		
		
		
		
		
		
		
		struct
		_ModelImporter_v2
		{
			static _Model_v2::Ref const		readModelFromFileAtPath(std::string const path);
			static _Model_v2::Ref const		readModelFromStream(std::istream& s);
		};
		
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___ModelImporter_v2__) */
