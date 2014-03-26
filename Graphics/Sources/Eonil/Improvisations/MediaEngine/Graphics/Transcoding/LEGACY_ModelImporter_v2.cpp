//
//  _ModelImporter_v2.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/28/13.
//
//

#include "LEGACY_ModelImporter_v2.h"







#include "LEGACY_ModelProxyEditorBoxA.h"
#include "_PackSerializerA.h"

#include <fstream>
#include <Eonil/Improvisations/MediaEngine/Mathematics/Geometry/Conversion/Unions.h>



#define	IMPORT_ASSERT		_PACK_ASSERT


namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Transcoding
	{
		
		
		
		namespace
		{
			using namespace	ProxyEditing;
			
			
			template<typename FROM, typename TO>
			std::vector<TO>
			readValueArrayUsingUnion(ValueArrayPEB<FROM> va0)
			{
				union
				CONV
				{
					FROM	from;
					TO		to;
					
					CONV(FROM const from) : from(from) {}
				};
				
				IMPORT_ASSERT(sizeof(FROM) == sizeof(TO));
				IMPORT_ASSERT(va0.unitSizeInBytes() == sizeof(CONV));
				IMPORT_ASSERT(va0.unitSizeInBytes() == sizeof(FROM));
				IMPORT_ASSERT(va0.unitSizeInBytes() == sizeof(TO));
				
				std::vector<TO>	va1;
				
				FROM const*	ptr		=	va0.values();
				Size		c0		=	va0.count();
				for (Size i=0; i<c0; i++)
				{
					CONV	conv(ptr[i]);
					va1.push_back(conv.to);
				}
				
				return	va1;
			}
			
			
			_TransformAnimation_v2
			readTransformAnimation(TransformAnimationPEB& ta0)
			{
				
				union
				B16
				{
					ProxyEditing::Vector3AnimationSample	s0;
					_Vector3AnimationCurve_v2::TimeSample		s1;
				};
				
				_TransformAnimation_v2	ta1;
				
				ta1.s.samples	=	readValueArrayUsingUnion<ProxyEditing::Vector3AnimationSample, _Vector3AnimationCurve_v2::TimeSample>(ta0.scaleChannel());
				ta1.r.samples	=	readValueArrayUsingUnion<ProxyEditing::QuaternionAnimationSample, _QuaternionAnimationCurve_v2::TimeSample>(ta0.rotationChannel());
				ta1.t.samples	=	readValueArrayUsingUnion<ProxyEditing::Vector3AnimationSample, _Vector3AnimationCurve_v2::TimeSample>(ta0.translationChannel());
				
				return	ta1;
			}
			
			_Motion_v2
			readMotion(MotionPEB& mo0)
			{
				_Motion_v2	mo1;
				mo1.name	=	mo0.name();
				
				for (std::string const& bname0 : mo0.allBoneNames())
				{
					TransformAnimationPEB	ta0	=	mo0.animationForBoneName(bname0);
					_TransformAnimation_v2	v1	=	readTransformAnimation(ta0);
					_Motion_v2::Pair	p1(bname0, v1);
					mo1.movements.insert(p1);
				}
				
				return	mo1;
			}
			
			
			
			
			
			
			
			
			
			_SkinnedForm_v2::Mesh::Ref const
			readMeshCore(MeshPEB mesh0)
			{
				IMPORT_ASSERT(mesh0.texture().format() == "PNG");
				IMPORT_ASSERT(mesh0.vertexes().unitSizeInBytes() == sizeof(_SkinnedForm_v2::Mesh::Vertex));
				IMPORT_ASSERT(mesh0.vertexes().data().length() % mesh0.vertexes().unitSizeInBytes() == 0);
				
				Legacy2013SharedMemory	vm0	=	mesh0.vertexes().data();
				Size	ml0	=	vm0.length();
				Size	vc0	=	ml0 / mesh0.vertexes().unitSizeInBytes();
				Size	fc0	=	vc0 / 3;
				Legacy2013SharedMemory	tm0	=	mesh0.texture().data();
				IMPORT_ASSERT(vc0 % 3 == 0);
				
				_SkinnedForm_v2::Mesh*	m1	=	new _SkinnedForm_v2::Mesh();
				
				m1->faceCount	=	fc0;
				m1->vertexBuffer	=	new Server::ArrayBuffer(mesh0.vertexes().data());
				{
					UInt8*	p1	=	(UInt8*)tm0.address();
					UInt8*	p2	=	p1 + tm0.length();
					
					GenericMemoryRange<UInt8 const>	r1	{p1, p2};
					
					bool flipInY = true;
					m1->colorTexture	=	new Server::PlanarTexture(Server::PlanarTexture::Utility::textureWithMemoryRangeContainingPNGData(r1, flipInY));
				}

				return	_SkinnedForm_v2::Mesh::Ref(m1);
			}				
			
			std::shared_ptr<_MeshWithBonePaletteBinding_v2 const>
			readMesh(MeshPEB mesh0)
			{
				_MeshWithBonePaletteBinding_v2*	mmm1	=	new _MeshWithBonePaletteBinding_v2();
				mmm1->meshCore							=	readMeshCore(mesh0);
				mmm1->boneNamesAtPaletteIndexes			=	mesh0.bonePalette().allBoneNamesAtPaletteIndexes();
				
				Size	c	=	mesh0.bindingPoseMatrices().count();
				float*	vs	=	(float*)mesh0.bindingPoseMatrices().values();
				for (Size i=0; i<c; i++)
				{
					Conversion::FLOAT32x16	conv(vs + (16*i));
					mmm1->bondBindingPoseMatricesAtPaletteIndexes.push_back(conv.EE);
				}
				return	std::shared_ptr<_MeshWithBonePaletteBinding_v2>(mmm1);
			}
			
			
			
			
			
			
			_Bone_v2
			readBoneAndItsSubbones(BonePEB b0)
			{
				_Bone_v2	b1;
				b1.name		=	b0.name();
				b1.meshWithBonePaletteBinding		=	b0.hasMesh() ? readMesh(b0.mesh()) : nullptr;
				
				Conversion::FLOAT32x16		conv(b0.defaultTransform().components);
				b1.defaultTransformMatrix	=	conv.EE;
				
				//!	@todo	Get transform.
				
				Size	c0	=	b0.numberOfSubbones();
				for (Size i=0; i<c0; i++)
				{
					BonePEB	sb0	=	b0.subboneAtIndex(i);
					_Bone_v2	sb1	=	readBoneAndItsSubbones(sb0);
					b1.subbones.push_back(sb1);
				}
				
				return	b1;
			}
			
			
			
			
			_Model_v2::Ref
			readModel(ModelPEB& m0)
			{
				_Model_v2*	model1	=	new _Model_v2;
				model1->skeleton	=	readBoneAndItsSubbones(m0.skeleton());
				
				////
				
				Size	c0	=	m0.motions().numberOfMotions();
				for (Size i=0; i<c0; i++)
				{
					MotionPEB	mo0	=	m0.motions().motionAtIndex(0);
					_Motion_v2	mo1	=	readMotion(mo0);
					
					_Model_v2::MotionPair	p1	=	_Model_v2::MotionPair(mo1.name, mo1);
					model1->motions.insert(p1);
				}
				
				return	_Model_v2::Ref(model1);
			}
			
			
		}
		
		
		
		
		_Model_v2::Ref const
		_ModelImporter_v2::readModelFromFileAtPath(const std::string path)
		{
			std::ifstream	is;
			is.open(path);
			is.seekg(0);
			_Model_v2::Ref	model1	=	readModelFromStream(is);
			is.close();
			
			return	model1;
		}
		
		_Model_v2::Ref const
		_ModelImporter_v2::readModelFromStream(std::istream &s)
		{
			_PackSerializerA	ps;
			ps.verifyHeader(s);
			std::shared_ptr<_PackNodeA>	pn	=	std::shared_ptr<_PackNodeA>(ps.deserialize(s));
			ps.verifyFooter(s);
			
			ModelPEB		m0(*pn);
			_Model_v2::Ref	m1	=	readModel(m0);
			
			return			m1;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	
}}}}

