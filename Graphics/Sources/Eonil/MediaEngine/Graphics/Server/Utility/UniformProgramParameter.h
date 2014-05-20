//
//  UniformProgramParameter.h
//  Graphics
//
//  Created by Hoon H. on 2/23/14.
//
//

#ifndef __Graphics__UniformProgramParameter__
#define __Graphics__UniformProgramParameter__

#include "../../Common.h"
#include "../../Server/Declarations.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Server
	{
		namespace
		Utility
		{
			
			
			
			
			
			
			
			/*!
			 @classdesign
			 All the values of passed pointer must be alive the drawing finishes.
			 */
			class
			UniformProgramParameter
			{
			public:
				enum class
				TYPE
				{
					NONE,
					SCALAR,
					VECTOR4,
					MATRIX4,
					SAMPLER,
				};
				
				
			public:
				UniformProgramParameter() {}
				UniformProgramParameter(Size index, Scalar const* pointer) : _index(index), _type(TYPE::SCALAR), _pointer(pointer) {}
				UniformProgramParameter(Size index, Vector4 const* pointer) : _index(index), _type(TYPE::VECTOR4), _pointer(pointer) {}
				UniformProgramParameter(Size index, Matrix4 const* pointer) : _index(index), _type(TYPE::MATRIX4), _pointer(pointer) {}
				UniformProgramParameter(Size index, Machinery::TextureSampler* pointer) : _index(index), _type(TYPE::SAMPLER), _pointer(pointer) {}
				
			public:
				auto	index() const -> Size;
				auto	type() const -> TYPE;
				auto	scalar() const -> Scalar const*;
				auto	vector4() const -> Vector4 const*;
				auto	matrix4() const -> Matrix4 const*;
				auto	sampler() const -> Machinery::TextureSampler*;
				
			private:
				Size			_index		{std::numeric_limits<Size>::max()};
				TYPE			_type		{TYPE::NONE};
				void const*		_pointer	{nullptr};
			};
			
			
			
			
			
			
			
			
		}
	}
	
}}}}

#endif /* defined(__Graphics__UniformProgramParameter__) */
