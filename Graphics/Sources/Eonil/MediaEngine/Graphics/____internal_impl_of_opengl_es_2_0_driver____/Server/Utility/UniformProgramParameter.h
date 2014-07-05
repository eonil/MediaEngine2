//
//  UniformProgramParameter.h
//  Graphics
//
//  Created by Hoon H. on 2/23/14.
//
//

#pragma once
#include "../Declarations.h"
#include "../../Server/Declarations.h"
INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_BEGIN

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
			UniformProgramParameter(sz index, Scalar const* pointer) : _index(index), _type(TYPE::SCALAR), _pointer(pointer) {}
			UniformProgramParameter(sz index, Vector4 const* pointer) : _index(index), _type(TYPE::VECTOR4), _pointer(pointer) {}
			UniformProgramParameter(sz index, Matrix4 const* pointer) : _index(index), _type(TYPE::MATRIX4), _pointer(pointer) {}
			UniformProgramParameter(sz index, Machinery::TextureSampler* pointer) : _index(index), _type(TYPE::SAMPLER), _pointer(pointer) {}
			
		public:
			auto	index() const -> sz;
			auto	type() const -> TYPE;
			auto	scalar() const -> Scalar const*;
			auto	vector4() const -> Vector4 const*;
			auto	matrix4() const -> Matrix4 const*;
			auto	sampler() const -> Machinery::TextureSampler*;
			
		private:
			sz				_index		{std::numeric_limits<sz>::max()};
			TYPE			_type		{TYPE::NONE};
			void const*		_pointer	{nullptr};
		};
		
		
		
		
		
		
		
		
	}
}

INTERNAL_IMPL_GLES20_DRIVER_NAMESPACE_END
