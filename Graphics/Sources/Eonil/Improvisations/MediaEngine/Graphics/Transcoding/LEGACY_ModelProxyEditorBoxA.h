//
//  _ModelProxyEditorBoxA.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 7/26/13.
//  Copyright (c) 2013 Eonil. All rights reserved.
//

#ifndef __EonilGraphics___ModelProxyEditorBoxA__
#define __EonilGraphics___ModelProxyEditorBoxA__





#include "../Common.h"
#include "_PackNodeA.h"





namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Transcoding
	{
		namespace
		ProxyEditing
		{
			
			
			struct
			Vertex
			{
				struct
				{
					float	x, y, z, w;		//!	w always 1.
				}
				location;
				
				struct
				{
					float	bones[4];
					float	intensities[4];
				}
				skinning;
				
				struct
				{
					float	x, y;
				}
				mapping;
				
			}
			__attribute__((__packed__));
			
			static_assert(sizeof(Eonil::Improvisations::MediaEngine::Graphics::Transcoding::ProxyEditing::Vertex) == 4*(4+4+4+2), "");
			
			struct
			TransformMatrix
			{
				float	components[16];
			};
			
			
			
			
			
			
			
			
			
			
			
			
			/*!
			 A temporal proxy editor.
			 */
			struct
			ProxyEditorBox
			{
			public:
				ProxyEditorBox(_PackNodeA& core) : _node(&core)
				{
					_PACK_ASSERT(_node != nullptr);
				}
				
				_PackNodeA&	core()
				{
					return	*_node;
				}
				
			 private:
					 _PackNodeA*		_node	=	nullptr;
			};
			
			
			
			
			
			
			struct
			StringEnum
			{
				std::vector<std::string>	values;
				
				StringEnum(std::initializer_list<std::string> const vs) : values(vs)
				{
				}
				
				bool const
				contains(std::string const v) const
				{
					return	std::find(values.begin(), values.end(), v) != values.end();
				}
			};
			
			
			
			
			
			
			
						
			
			template<typename T>
			struct
			ValueArrayPEB : public ProxyEditorBox
			{
				using	ProxyEditorBox::ProxyEditorBox;
				
				Legacy2013SharedMemory const
				data()
				{
					return	core().dataForSubpackWithName("values");
				}
//					void
//					setData(Memory const m)
//					{
//						
//					}
				
				Size const
				unitSizeInBytes()
				{
					return	core().uint32ForSubpackWithName("unitSizeInBytes");
				}
				Size const
				count()
				{
					return	core().uint32ForSubpackWithName("count");
				}
				T const* const
				values()
				{
					_PACK_ASSERT(sizeof(T) == unitSizeInBytes());
//					_PACK_ASSERT(count() > 0);
					
					Legacy2013SharedMemory const&	m	=	core().dataForSubpackWithName("values");
					_PACK_ASSERT(m.length() == count() * unitSizeInBytes());
					return	(T const*)m.address();
				}
				
				void
				setValues(T const* const values, uint32_t const count)
				{
					core().setUInt32ForSubpackWithName(sizeof(T), "unitSizeInBytes");
					core().setUInt32ForSubpackWithName(count, "count");
					
					Legacy2013SharedMemory	m	=	Legacy2013SharedMemory::Factory::memoryByCopyingRange(values, count * sizeof(T));
					core().setDataForSubpackWithName(m, "values");
				}
			};
			
			
			
			
						
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			struct
			TexturePEB : public ProxyEditorBox
			{
				StringEnum const	FORMATS	=
				{
					"PNG",
				};
				
				using	ProxyEditorBox::ProxyEditorBox;
				
				TexturePEB(_PackNodeA& p) : ProxyEditorBox(p)
				{
					_PACK_ASSERT(core().name() == "texture");
				}
				
				std::string const
				format()
				{
					return	core().stringForSubpackWithName("format");
				}
				Legacy2013SharedMemory const
				data()
				{
					return	core().dataForSubpackWithName("data");
				}
//				UniqueByteMemoryBlock
//				data2()
//				{
//					return	core().dataForSubpackWithName2("data");
//				}

				bool const
				flippedInYAxis()		//!	If true, then image flipped when compared to GL space. So it's Y-up system. Most images are flipped in GL space.
				{
					return	core().uint32ForSubpackWithName("flippedInYAxis") == 1;
				}
				
				void
				setDataWithFormatAndFlippingInYAxis(Legacy2013SharedMemory const m, std::string const f, bool const flip = false)
				{
					_PACK_ASSERT(FORMATS.contains(f));
					core().setDataForSubpackWithName(m, "data");
					core().setUInt32ForSubpackWithName(flip ? 1 : 0, "flippedInYAxis");
					core().setStringForSubpackWithName(f, "format");
				}
			};
			
			
			
			struct
			MeshBonePalettePEB : public ProxyEditorBox
			{
				using	ProxyEditorBox::ProxyEditorBox;
				
				MeshBonePalettePEB(_PackNodeA& p) : ProxyEditorBox(p)
				{
					_PACK_ASSERT(core().name() == "bonePalette");
				}
				
				std::vector<std::string> const
				allBoneNamesAtPaletteIndexes()
				{
					std::vector<std::string>	ss1;
					Size						c	=	numberOfBoneNames();
					
					for (Size i=0; i<c; i++)
					{
						std::string	s0	=	boneNameAtIndex(i);
						ss1.push_back(s0);
					}
					return	ss1;
				}
				
				Size const
				numberOfBoneNames()
				{
					return	core().numberOfSubpacks();
				}
				
				std::string const
				boneNameAtIndex(Size const index)
				{
					return	core().subpackAtIndex(index).name();
				}
				void
				addBoneName(std::string const name)
				{
					_PACK_ASSERT(not core().hasSubpackForName(name));		//!	Ambiguous bone name is prohibited.
					core().addSubpack().name()	=	name;
				}
			};
			struct
			MeshPEB : public ProxyEditorBox
			{
				using	ProxyEditorBox::ProxyEditorBox;
				
				MeshPEB(_PackNodeA& p) : ProxyEditorBox(p)
				{
					_PACK_ASSERT(core().name() == "mesh");
				}
				
				
				ValueArrayPEB<Vertex>
				vertexes()
				{
					return	core().subpackForName("vertexes", true);
				}
				MeshBonePalettePEB
				bonePalette()
				{
					return	core().subpackForName("bonePalette", true);
				}
				ValueArrayPEB<TransformMatrix>
				bindingPoseMatrices()	//!	Has same index with bone palette.
				{
					return	core().subpackForName("bindingPoseMatrices", true);
				}
				
				bool const
				hasTexture()
				{
					return	core().hasSubpackForName("texture");
				}
				TexturePEB
				texture()
				{
					return	core().subpackForName("texture");
				}
				TexturePEB
				setTexture()
				{
					return	core().addSubpackForName("texture");
				}
				void
				unsetTexture()
				{
					core().removeSubpackForName("texture");
				}
			};
			
			
			
			
			
			struct
			BonePEB : public ProxyEditorBox
			{
				using	ProxyEditorBox::ProxyEditorBox;
				
				BonePEB(_PackNodeA& p) : ProxyEditorBox(p)
				{
					_PACK_ASSERT(core().name() == "bone");
					core().subpackForName("subbones", true);
				}
				
				std::string const
				name()
				{
					return	core().stringForSubpackWithName("name");
				}
				void
				setName(std::string const name)
				{
					_PACK_ASSERT(name.length() != 0);
					return	core().setStringForSubpackWithName(name, "name");
				}
				
				
				TransformMatrix const
				defaultTransform()
				{
					if (not core().hasSubpackForName("defaultTransform"))
					{
						TransformMatrix	tm;
						for (size_t i=0; i<16; i++)
						{
							tm.components[i]	=	std::numeric_limits<float>::signaling_NaN();
						}
						return	tm;
					}
					else
					{
						Legacy2013SharedMemory			m0	=	core().dataForSubpackWithName("defaultTransform");
						TransformMatrix	tm1	=	*(TransformMatrix*)m0.address();
						return			tm1;
					}
				}
				void
				setDefaultTransform(TransformMatrix m)
				{
					Legacy2013SharedMemory	m1	=	Legacy2013SharedMemory::Factory::memoryByCopyingRange(&m, sizeof(TransformMatrix));
					core().setDataForSubpackWithName(m1, "defaultTransform");
				}
				
				
				
				bool const
				hasMesh()
				{
					return	core().hasSubpackForName("mesh");
				}
				MeshPEB
				mesh()
				{
					return	MeshPEB(core().subpackForName("mesh"));
				}
				MeshPEB
				setMesh()
				{
					return	core().addSubpackForName("mesh");
				}
				void
				unsetMesh()
				{
					core().removeSubpackForName("mesh");
				}
				
				
				
				
				Size const
				numberOfSubbones()
				{
					return	core().subpackForName("subbones").numberOfSubpacks();
				}
				BonePEB
				subboneAtIndex(Size const index)
				{
					return	core().subpackForName("subbones").subpackAtIndex(index);
				}
				BonePEB
				addSubbone()
				{
					_PackNodeA&	p	=	core().subpackForName("subbones").addSubpack();
					p.name()		=	"bone";
					return	p;
				}
				void
				removeAllSubbones()
				{
					if (core().hasSubpackForName("subbones"))
					{
						core().removeSubpackForName("subbones");
					}
				}
			};
			
			
			

			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			struct
			Vector3AnimationSample
			{
				struct
				{
					float	x, y, z;
				}
				value;
				uint32_t	time;
			}
			__attribute((__packed__));
			static_assert(sizeof(Vector3AnimationSample) == 4*(3+1), "");
//			struct
//			Axis3AngleAnimationSample
//			{
//				uint32_t	time;
//				
//				struct
//				{
//					float	x, y, z, a;
//				}
//				value;
//			};
			struct
			QuaternionAnimationSample
			{
				struct
				{
					float	x, y, z, w;
				}
				value;
				
				uint32_t	time;
				
				uint32_t	empty[3];
			}
			__attribute((__packed__));
			static_assert(sizeof(QuaternionAnimationSample) == 4*(4+1+3), "");
						
			struct
			TransformAnimationPEB : public ProxyEditorBox
			{
				using	ProxyEditorBox::ProxyEditorBox;
				
				std::string const
				name()
				{
					return	core().name();
				}
				
				ValueArrayPEB<Vector3AnimationSample>
				scaleChannel()
				{
					return	core().subpackForName("S", true);
				}
				ValueArrayPEB<QuaternionAnimationSample>
				rotationChannel()
				{
					return	core().subpackForName("R", true);
				}
				ValueArrayPEB<Vector3AnimationSample>
				translationChannel()
				{
					return	core().subpackForName("T", true);
				}
			};
			
			/*!
			 You can't change once set name. Because the name is being used as a key in a map.
			 */
			struct
			MotionPEB : public ProxyEditorBox
			{
				using	ProxyEditorBox::ProxyEditorBox;
				
				std::string const
				name()
				{
					return	core().name();
				}
				
				std::vector<std::string>
				allBoneNames()
				{
					std::vector<std::string>	sv;
					
					_PackNodeA	bmp0	=	core().subpackForName("boneAnimationMapping");
					Size		c		=	bmp0.numberOfSubpacks();
					
					for (Size i=0; i<c; i++)
					{
						_PackNodeA	sp1		=	bmp0.subpackAtIndex(i);
						std::string	name	=	sp1.name();
						sv.push_back(name);
					}
					
					return	sv;
				}
				
				TransformAnimationPEB
				animationForBoneName(std::string const boneName)
				{
					return	core().subpackForName("boneAnimationMapping", true).subpackForName(boneName);
				}
				TransformAnimationPEB
				addAnimationForBoneName(std::string const boneName)
				{
					return	core().subpackForName("boneAnimationMapping", true).addSubpackForName(boneName);
				}
				void
				removeAnimationForBoneName(std::string const boneName)
				{
					core().subpackForName("boneAnimationMapping", true).removeSubpackForName(boneName);
				}
			};
			
			struct
			MotionMapPEB : public ProxyEditorBox
			{
				using	ProxyEditorBox::ProxyEditorBox;
				
				MotionMapPEB(_PackNodeA& p) : ProxyEditorBox(p)
				{
					_PACK_ASSERT(core().name() == "motions");
				}
				
				Size const
				numberOfMotions()
				{
					return	core().numberOfSubpacks();
				}
				MotionPEB
				motionAtIndex(Size const index)
				{
					return	core().subpackAtIndex(index);
				}
				MotionPEB
				motionForName(std::string const name)
				{
					return	core().subpackForName(name);
				}
				MotionPEB
				addMotionForName(std::string const name)
				{
					return	core().addSubpackForName(name);
				}
				void
				removeMotionForName(std::string const name)
				{
					core().removeSubpackForName(name);
				}
			};
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			struct
			ModelPEB : public ProxyEditorBox
			{
				using	ProxyEditorBox::ProxyEditorBox;
				
				ModelPEB(_PackNodeA& p) : ProxyEditorBox(p)
				{
					core().setStringForSubpackWithName("_DEV_::Model (Form A)", "comment");
					core().name()	=	"model";
				}
				
				BonePEB
				skeleton()
				{
					return	BonePEB(core().subpackForName("bone", true));
				}
				
				MotionMapPEB
				motions()
				{
					return	core().subpackForName("motions", true);
				}
				
			};
			
			
			

				
				
				
				
			
			

	
					
		
		}
		
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics___ModelProxyEditorBoxA__) */
