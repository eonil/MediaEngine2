////
////  AssociativeExternalData.h
////  Graphics
////
////  Created by Hoon H. on 2/8/14.
////
////
//
//#ifndef __Graphics__AssociativeExternalData__
//#define __Graphics__AssociativeExternalData__
//
////#include <unordered_map>
////#include <map>
//#include "../Common.h"
//
//namespace Eonil { namespace Improvisations { namespace MediaEngine { namespace Graphics {
//	
//	namespace
//	Debugging
//	{
//
//		
//		
//		class
//		AssociativeExternalData
//		{			
//			std::unordered_map<void const*, std::unordered_map<str, str>>		_str_map{};
//			std::unordered_map<void const*, std::unordered_map<str, int64_t>>	_int_map{};
//			
//		public:
//			auto	stringAssociativeDataForObjectAtAddress(void const* pointerToTheObject, str const& dataKey) -> str const&;
//			auto	integerAssociativeDataForObjectAtAddress(void const* pointerToTheObject, str const& dataKey) -> int64_t const&;
//
//			auto	setAssociativeDataForObjectAtAddress(void const* pointerToTheObject, str const& dataKey, str const& dataValue) -> void;
//			auto	setAssociativeDataForObjectAtAddress(void const* pointerToTheObject, str const& dataKey, int64_t const& dataValue) -> void;
//			auto	unsetAssociativeDataForObjectAtAddress(void const* pointerToTheObject, str const& dataKey) -> void;
//			auto	unsetAllAssociativeDataForObject(void const* pointerToTheObject) -> void;
//
//		};
//		
//		
//		
//		
//		auto AssociativeExternalData::
//		stringAssociativeDataForObjectAtAddress(void const* pointerToTheObject, str const& dataKey) -> str const&
//		{
//			return	_str_map.at(pointerToTheObject).at(dataKey);
//		}
//		auto AssociativeExternalData::
//		integerAssociativeDataForObjectAtAddress(void const* pointerToTheObject, str const& dataKey) -> int64_t const&
//		{
//			return	_int_map.at(pointerToTheObject).at(dataKey);
//		}
//		
//		auto AssociativeExternalData::
//		setAssociativeDataForObjectAtAddress(void const* pointerToTheObject, str const& dataKey, str const& dataValue) -> void
//		{
//			unsetAssociativeDataForObjectAtAddress(pointerToTheObject, dataKey);
//			_str_map[pointerToTheObject][dataKey]	=	dataValue;
//		}
//		auto AssociativeExternalData::
//		setAssociativeDataForObjectAtAddress(void const* pointerToTheObject, str const& dataKey, int64_t const& dataValue) -> void
//		{
//			unsetAssociativeDataForObjectAtAddress(pointerToTheObject, dataKey);
//			_int_map[pointerToTheObject][dataKey]	=	dataValue;
//		}
//		auto AssociativeExternalData::
//		unsetAssociativeDataForObjectAtAddress(void const* pointerToTheObject, str const& dataKey) -> void
//		{
//			if (_str_map.at(pointerToTheObject).find(dataKey) != _str_map.at(pointerToTheObject).end())
//			{
//				_str_map.erase(pointerToTheObject);
//			}
//			if (_int_map.at(pointerToTheObject).find(dataKey) != _int_map.at(pointerToTheObject).end())
//			{
//				_int_map.erase(pointerToTheObject);
//			}
//		}
//		auto AssociativeExternalData::
//		unsetAllAssociativeDataForObject(void const* pointerToTheObject) -> void
//		{
//			if (_str_map.find(pointerToTheObject) != _str_map.end())
//			{
//				_str_map.erase(pointerToTheObject);
//			}
//			if (_int_map.find(pointerToTheObject) != _int_map.end())
//			{
//				_int_map.erase(pointerToTheObject);
//			}
//		}
//	}
//	
//}}}}
//
//#endif /* defined(__Graphics__AssociativeExternalData__) */
