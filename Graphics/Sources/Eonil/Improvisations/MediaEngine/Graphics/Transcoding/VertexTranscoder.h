//
//  VertexTranscoder.h
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/13/13.
//
//

#ifndef __EonilGraphics__VertexTranscoder__
#define __EonilGraphics__VertexTranscoder__

#include <cstdlib>
#include "../Common.h"
#include "../Debugging/Doctor.h"
#include "../Server/Buffer.h"
#include "../Server/Machinery/VertexAttributeChannel.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {

	namespace
	Transcoding
	{
		struct
		VertexComponent
		{
			struct
			TYPE
			{
				TYPE() = delete;
				
				enum
				CODE : GLenum
				{
					UINT8	=	GLenum(Server::Machinery::VertexAttributeChannel::ComponentType::UBYTE),
					SINT8	=	GLenum(Server::Machinery::VertexAttributeChannel::ComponentType::BYTE),
					UINT16	=	GLenum(Server::Machinery::VertexAttributeChannel::ComponentType::USHORT),
					SINT16	=	GLenum(Server::Machinery::VertexAttributeChannel::ComponentType::SHORT),
					FLOAT	=	GLenum(Server::Machinery::VertexAttributeChannel::ComponentType::FLOAT),
				};
			};
			
			std::string		name;
			TYPE::CODE		type;
			Size			count;
			
			VertexComponent(std::string const name, TYPE::CODE const type, Size const count);
		};
		
		/*!
		 Describes dense interleaved vertex list.
		 */
		class
		VertexFormat
		{
		public:
			std::vector<VertexComponent> const&		components() const;
			std::vector<VertexComponent>&			components();
			
			void	addVector4OfFloat32(std::string const name = "");
			void	addVector3OfFloat32(std::string const name = "");
			void	addVector2OfFloat32(std::string const name = "");
			void	addVector1OfFloat32(std::string const name = "");
			
			void	addVector4OfSInt16(std::string const name = "");
			void	addVector3OfSInt16(std::string const name = "");
			void	addVector2OfSInt16(std::string const name = "");
			void	addVector1OfSInt16(std::string const name = "");
			
			void	addVector4OfUInt16(std::string const name = "");
			void	addVector3OfUInt16(std::string const name = "");
			void	addVector2OfUInt16(std::string const name = "");
			void	addVector1OfUInt16(std::string const name = "");
			
			void	addVector4OfUInt8(std::string const name = "");
			void	addVector3OfUInt8(std::string const name = "");
			void	addVector2OfUInt8(std::string const name = "");
			void	addVector1OfUInt8(std::string const name = "");
			
			void	addVector4OfSInt8(std::string const name = "");
			void	addVector3OfSInt8(std::string const name = "");
			void	addVector2OfSInt8(std::string const name = "");
			void	addVector1OfSInt8(std::string const name = "");
			
			Size const																unitSizeInBytes() const;
			std::vector<Server::Machinery::VertexAttributeChannel::Format> const	vertexAttributeChannelFormats() const;
			
		private:
			std::vector<VertexComponent>			_comps;
		};
		
		
		
		
		
		
		
		
		
		
		/*!
		 Debug version asserts mismatched vertex size to format.
		 */
		template<typename V>
		class
		VertexPackage
		{
			static_assert(sizeof(V) % 4 == 0, "Size of vertex type `V` must be aligned in 4-byte boundaries.");
			static_assert(std::is_standard_layout<V>::value, "Vertex type `V` memory layout must be standard.");
			
		public:
			VertexPackage(VertexFormat const format);
			
			VertexFormat const&		format() const;
			
			std::vector<V> const&	vertexes() const;
			std::vector<V>&			vertexes();
			void					setVertexes(std::vector<V> const vs);
			
			Legacy2013SharedMemory const			asMemory() const;	//	Copies whole vertex data.
			
		private:
			VertexFormat const		_f;
			std::vector<V>			_vs;
		};
		
		
//			
//			template<Size const C, typename T>
//			class
//			VertexUnit
//			{
//				static_assert(C % 4 == 0, "Vertex must be aligned to 128-bit.");
//				
//			public:
//				union
//				{
//					Scalar	scalars[C];
//					UInt32	quantums[C];
//				};
//			}
//			__attribute__((aligned(16)));	//	Enforced to be aligned to 128-bit.
//			
//			
//			
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
//			
//			
//			template<Size const C, typename T>
//			class
//			VertexTranscoder
//			{
//			public:
//				VertexTranscoder(VertexFormat const foramt);
//				
//				std::vector<VertexUnit<C, T>> const&	units() const;
//				std::vector<VertexUnit<C, T>>&			units();
//				
//			private:
//				VertexTranscoder	_vf;
//			};
	}
	
	
	
	
	
	
	
}}}}


























namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Transcoding
	{
		template<typename V>
		VertexPackage<V>::VertexPackage(VertexFormat const format) : _f(format)
		{
			EEGL_ASSERT_WITH_REASON(_f.unitSizeInBytes() == sizeof(V), "Size of vertex type `V` doesn't match to size specified by the format.");
		}
		
		
		template<typename V>
		VertexFormat const&
		VertexPackage<V>::format() const
		{
			return	_f;
		}
		template<typename V>
		std::vector<V> const&
		VertexPackage<V>::vertexes() const
		{
			return	_vs;
		}
		
		template<typename V>
		std::vector<V>&
		VertexPackage<V>::vertexes()
		{
			return	_vs;
		}
		
		
		template<typename V>
		void
		VertexPackage<V>::setVertexes(std::vector<V> const vs)
		{
			_vs	=	vs;
		}
		
		template<typename V>
		Eonil::Improvisations::MediaEngine::Foundation::_Legacy2013::SharedMemory const
		VertexPackage<V>::asMemory() const
		{
			Size	len		=	sizeof(V) * _vs.size();
			V*		mem		=	(V*)malloc(len);
			for(Size i=0; i<_vs.size(); i++)
			{
				mem[i]	=	_vs[i];
			}
			return	Eonil::Improvisations::MediaEngine::Foundation::_Legacy2013::SharedMemory::Factory::memoryByOwningRange(mem, len);
		}
	}
	
	
	
	
	
	
	
	
}}}}

#endif /* defined(__EonilGraphics__VertexTranscoder__) */
