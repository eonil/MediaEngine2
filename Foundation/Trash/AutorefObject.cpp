////
////  AutorefObject.cpp
////  EonilFoundation
////
////  Created by Hoon Hwangbo on 7/29/13.
////
////
//
//#include "AutorefObject.h"
//
//
//
//#include "Doctor.h"
//
//
//namespace
//Eonil
//{
//	namespace
//	Foundation
//	{
//		static size_t	_num_live_obj	=	0;
//		
//		
//		size_t const
//		AutorefObject::TOTAL_LIVE_OBJECT_COUNT()
//		{
//			return	_num_live_obj;
//		}
//		
//		
//		
//		
//		AutorefObject::AutorefObject() : _refc(0)
//		{
//			_num_live_obj++;
//			//			std::cout << this << " ctor\n";
//		}
//		AutorefObject::AutorefObject(AutorefObject const& obj) : _refc(0)	//!	Don't copy ref-count.
//		{
//			_num_live_obj++;
//			//			std::cout << this << " cctor\n";
//		}
//		AutorefObject::~AutorefObject()
//		{
//			_num_live_obj--;
//			//			std::cout << this << " dtor\n";
//		}
//		
//		
//		
//		void
//		AutorefObject::_addref() const
//		{
//			_refc++;
//			//			std::cout << this << " addref\n";
//		}
//		void
//		AutorefObject::_removeref() const
//		{
//			_refc--;
//			//			std::cout << this << " removeref\n";
//			if (_refc==0)
//			{
//				delete	this;
//			}
//		}
//	}
//}
//
//
