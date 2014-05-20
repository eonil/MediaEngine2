//
//  VertexTranscoder.cpp
//  EonilGraphics
//
//  Created by Hoon Hwangbo on 6/13/13.
//
//

#include "VertexTranscoder.h"

namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
	
	namespace
	Transcoding
	{
		using namespace	Server::Machinery;
		
		namespace
		{
			Size const
			SizeOfType(VertexComponent::TYPE::CODE const t)
			{
				switch (t)
				{
					case	VertexComponent::TYPE::CODE::UINT8:		return 	1;
					case	VertexComponent::TYPE::CODE::SINT8:		return 	1;
					case	VertexComponent::TYPE::CODE::UINT16:	return 	2;
					case	VertexComponent::TYPE::CODE::SINT16:	return 	2;
					case	VertexComponent::TYPE::CODE::FLOAT:		return 	4;
				}
			}
		}
		
		VertexComponent::VertexComponent(std::string const name, TYPE::CODE const type, Size const count) : name(name), type(type), count(count)
		{
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		void	VertexFormat::addVector1OfFloat32(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::FLOAT, 1)); }
		void	VertexFormat::addVector2OfFloat32(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::FLOAT, 2)); }
		void	VertexFormat::addVector3OfFloat32(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::FLOAT, 3)); }
		void	VertexFormat::addVector4OfFloat32(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::FLOAT, 4)); }
		
		void	VertexFormat::addVector1OfUInt16(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::UINT16, 1)); }
		void	VertexFormat::addVector2OfUInt16(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::UINT16, 2)); }
		void	VertexFormat::addVector3OfUInt16(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::UINT16, 3)); }
		void	VertexFormat::addVector4OfUInt16(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::UINT16, 4)); }
		
		void	VertexFormat::addVector1OfSInt16(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::SINT16, 1)); }
		void	VertexFormat::addVector2OfSInt16(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::SINT16, 2)); }
		void	VertexFormat::addVector3OfSInt16(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::SINT16, 3)); }
		void	VertexFormat::addVector4OfSInt16(std::string const name)	{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::SINT16, 4)); }
		
		void	VertexFormat::addVector1OfUInt8(std::string const name)		{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::UINT8, 1)); }
		void	VertexFormat::addVector2OfUInt8(std::string const name)		{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::UINT8, 2)); }
		void	VertexFormat::addVector3OfUInt8(std::string const name)		{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::UINT8, 3)); }
		void	VertexFormat::addVector4OfUInt8(std::string const name)		{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::UINT8, 4)); }
		
		void	VertexFormat::addVector1OfSInt8(std::string const name)		{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::SINT8, 1)); }
		void	VertexFormat::addVector2OfSInt8(std::string const name)		{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::SINT8, 2)); }
		void	VertexFormat::addVector3OfSInt8(std::string const name)		{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::SINT8, 3)); }
		void	VertexFormat::addVector4OfSInt8(std::string const name)		{ _comps.push_back(VertexComponent(name, VertexComponent::TYPE::SINT8, 4)); }
		
		

		Size const
		VertexFormat::unitSizeInBytes() const
		{
			Size	vertexSize	=	0;
			for(Size i=0; i<_comps.size(); i++)
			{
				vertexSize	+=	SizeOfType(_comps[i].type) * _comps[i].count;
			}
			return	vertexSize;
		}

		std::vector<VertexAttributeChannel::Format> const
		VertexFormat::vertexAttributeChannelFormats() const
		{
			std::vector<VertexAttributeChannel::Format>	fs;
			fs.resize(_comps.size());
			
			Size	offsets[_comps.size()];
			GLsizei	countedSize	=	0;
			
			for(Size i=0; i<_comps.size(); i++)
			{
				offsets[i]	=	countedSize;
				countedSize	+=	SizeOfType(_comps[i].type) * _comps[i].count;
			}
			
			for(Size i=0; i<_comps.size(); i++)
			{
				fs[i].dataOffset		=	offsets[i];
				fs[i].componentCount	=	(VertexAttributeChannel::ComponentSize)_comps[i].count;
				fs[i].componentType		=	(VertexAttributeChannel::ComponentType)_comps[i].type;
				fs[i].normalization		=	GL_FALSE;
				fs[i].strideSizeInBytes	=	countedSize;
				
//					src.channelingFormats[i].setBufferOffsetInBytes(offsets[i]);
//					src.channelingFormats[i].componentCount		=	(Server::VertexChannelingFormat::SIZE)_comps[i].count;
//					src.channelingFormats[i].componentType		=	(Server::VertexChannelingFormat::TYPE)_comps[i].type;
//					src.channelingFormats[i].normalization		=	GL_FALSE;
//					src.channelingFormats[i].strideSizeInBytes	=	countedSize;
			}
			
			return	fs;
		}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
	}
	
	
	
	
	
	
	
	
}}}}

