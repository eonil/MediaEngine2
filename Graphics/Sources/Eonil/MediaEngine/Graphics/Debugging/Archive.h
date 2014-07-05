////
////  Archive.h
////  Graphics
////
////  Created by Hoon H. on 2/5/14.
////
////
//
//#ifndef __Graphics__Archive__
//#define __Graphics__Archive__
//
//#include "../Common.h"
//
//EONIL_MEDIA_ENGINE_GRAPHICS_NAMESPACE_BEGIN
//	
//	namespace
//	Debugging
//	{
//
//	
//		
//		
//		/*!
//		 Object-external debugging data storage.
//		 
//		 @discussion
//		 Sometimes we need to store some data for an object to introspect them. But this kind of
//		 data is only for debugging, and degrades production operational performance and memory
//		 efficiency. So it must not be stored in an object. 
//		 
//		 This class provides all-in-one place to store those data.
//		 */
//		class
//		Archive
//		{
//			std::unordered_map<void const*, str>	_summary_map{};
//			
//		public:
//			auto	summaryForAddress(void const* objectAddress) const -> str const&;
//			auto	setSummaryForAddress(void const* objectAddress, str const& contentString) -> void;
//			auto	unsetSummaryForAddress(void const* objectAddress) -> void;
//			
//		public:
//			struct
//			Utility
//			{
//				static auto	defaultArchive() -> Archive&;
//			};
//		};
//		
//		
//		
//		
//		
//	}
//	
//}}}}
//
//#endif /* defined(__Graphics__Archive__) */
