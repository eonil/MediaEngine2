//
//  _ModelImporterA.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/27/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#include "_ModelImporterA.h"

#include "_ModelProxyEditorBoxA.h"
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
			
			
			_TransformAnimationA
			readTransformAnimation(TransformAnimationPEB& ta0)
			{
				
				union
				B16
				{
					ProxyEditing::Vector3AnimationSample	s0;
					_Vector3AnimationCurveA::TimeSample		s1;
				};
				
				_TransformAnimationA	ta1;
				
				ta1.s.samples	=	readValueArrayUsingUnion<ProxyEditing::Vector3AnimationSample, _Vector3AnimationCurveA::TimeSample>(ta0.scaleChannel());
				ta1.r.samples	=	readValueArrayUsingUnion<ProxyEditing::QuaternionAnimationSample, _QuaternionAnimationCurveA::TimeSample>(ta0.rotationChannel());
				ta1.t.samples	=	readValueArrayUsingUnion<ProxyEditing::Vector3AnimationSample, _Vector3AnimationCurveA::TimeSample>(ta0.translationChannel());
				
				return	ta1;
			}
			
			_MotionA
			readMotion(MotionPEB& mo0)
			{
				_MotionA	mo1;
				mo1.name	=	mo0.name();
				
				for (std::string const& bname0 : mo0.allBoneNames())
				{
					TransformAnimationPEB	ta0	=	mo0.animationForBoneName(bname0);
					_TransformAnimationA	v1	=	readTransformAnimation(ta0);
					_MotionA::Pair	p1(bname0, v1);
					mo1.movements.insert(p1);
				}
				
				return	mo1;
			}
			
			
			
			
			
			
			
			
			_SkinnedForm::Mesh const
			readMeshCore(MeshPEB mesh0)
			{
				std::vector<_SkinnedForm::Mesh::Vertex>	vs	=	readValueArrayUsingUnion<ProxyEditing::Vertex, _SkinnedForm::Mesh::Vertex>(mesh0.vertexes());
				
				_SkinnedForm::Mesh	m1;
				
				for (Size i=0; i<vs.size()/3; i++)
				{
					_SkinnedForm::Mesh::Face	face1;
					face1.vertexes[0]	=	vs[i*3+0];
					face1.vertexes[1]	=	vs[i*3+1];
					face1.vertexes[2]	=	vs[i*3+2];
					m1.faces.push_back(face1);
				}
				IMPORT_ASSERT(mesh0.texture().format() == "PNG");
				Legacy2013SharedMemory	tm0	=	mesh0.texture().data();
				m1.colorTexture	=	new Server::PlanarTexture(Server::PlanarTexture::Utility::_DEV_textureWithMemory(tm0));
				return	m1;
			}
			
			
			std::shared_ptr<_MeshWithBonePaletteBinding_v1 const>
			readMesh(MeshPEB mesh0)
			{
				_MeshWithBonePaletteBinding_v1*	mmm1	=	new _MeshWithBonePaletteBinding_v1();
				mmm1->meshCore							=	readMeshCore(mesh0);
				mmm1->boneNamesAtPaletteIndexes			=	mesh0.bonePalette().allBoneNamesAtPaletteIndexes();

				Size	c	=	mesh0.bindingPoseMatrices().count();
				float*	vs	=	(float*)mesh0.bindingPoseMatrices().values();
				for (Size i=0; i<c; i++)
				{
					Conversion::FLOAT32x16	conv(vs + (16*i));
					mmm1->bondBindingPoseMatricesAtPaletteIndexes.push_back(conv.EE);
				}
				return	std::shared_ptr<_MeshWithBonePaletteBinding_v1>(mmm1);
			}
			
			
			
			
			
			
			_BoneA
			readBoneAndItsSubbones(BonePEB b0)
			{
				_BoneA	b1;
				b1.name		=	b0.name();
				b1.meshWithBonePaletteBinding		=	b0.hasMesh() ? readMesh(b0.mesh()) : nullptr;
				
				Conversion::FLOAT32x16		conv(b0.defaultTransform().components);
				b1.defaultTransformMatrix	=	conv.EE;
				
				//!	@todo	Get transform.
				
				Size	c0	=	b0.numberOfSubbones();
				for (Size i=0; i<c0; i++)
				{
					BonePEB	sb0	=	b0.subboneAtIndex(i);
					_BoneA	sb1	=	readBoneAndItsSubbones(sb0);
					b1.subbones.push_back(sb1);
				}
				
				return	b1;
			}
			
			
			
			
			_ModelA::Ref
			readModel(ModelPEB& m0)
			{
				_ModelA*	model1	=	new _ModelA;
				model1->skeleton	=	readBoneAndItsSubbones(m0.skeleton());
				
				////
				
				Size	c0	=	m0.motions().numberOfMotions();
				for (Size i=0; i<c0; i++)
				{
					MotionPEB	mo0	=	m0.motions().motionAtIndex(0);
					_MotionA	mo1	=	readMotion(mo0);
					
					_ModelA::MotionPair	p1	=	_ModelA::MotionPair(mo1.name, mo1);
					model1->motions.insert(p1);
				}
				
				return	_ModelA::Ref(model1);
			}
			
			
		}

		
		
		
		_ModelA::Ref const
		_ModelImporterA::readModelFromFileAtPath(const std::string path)
		{
			std::ifstream	is;
			is.open(path);
			is.seekg(0);
			_ModelA::Ref	model1	=	readModelFromStream(is);
			is.close();
			
			return	model1;
		}
		
		_ModelA::Ref const
		_ModelImporterA::readModelFromStream(std::istream &s)
		{
			_PackSerializerA	ps;
			ps.verifyHeader(s);
			std::shared_ptr<_PackNodeA>	pn	=	std::shared_ptr<_PackNodeA>(ps.deserialize(s));
			ps.verifyFooter(s);
			
			ModelPEB		m0(*pn);
			_ModelA::Ref	m1	=	readModel(m0);
			
			return			m1;
		}


		
		
		
		
		
		
		
		
		
		
		


	}
	
	
	
	
	
	
	
	
}}}}




