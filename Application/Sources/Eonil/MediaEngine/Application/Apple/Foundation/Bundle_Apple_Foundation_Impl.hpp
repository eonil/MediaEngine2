//
//  Bundle_Apple_Foundation_Impl.hpp
//  Application
//
//  Created by Hoon H. on 2/26/14.
//
//


#import <Foundation/Foundation.h>

EONIL_MEDIA_ENGINE_APPLICATION_NAMESPACE_BEGIN







class
Bundle::Core
{
public:
	str		rootDirectoryPath;
};


Bundle::Bundle()
{
}
Bundle::Bundle(str const& rootDirectoryPath) : _core_ptr(new Core{rootDirectoryPath})
{
}

auto Bundle::
pathForResource(str const& location, str const& name, str const& type) const -> str
{
	@autoreleasepool
	{
		NSString*		s1		=	[NSString stringWithUTF8String:location.c_str()];
		NSString*		s2		=	[NSString stringWithUTF8String:name.c_str()];
		NSString*		s3		=	[NSString stringWithUTF8String:type.c_str()];
		
		NSString*		p1		=	[s1 stringByAppendingPathComponent:s2];
		NSString*		fp0		=	[[NSBundle mainBundle] pathForResource:p1 ofType:s3];
		
		return			fp0.UTF8String;		//	Copies the string.
	}
}

auto Bundle::
Bundle::main() -> Bundle const&
{
	static Bundle*	_main	=	nullptr;
	
	if (_main == nullptr)
	{
		_main	=	new Bundle();
	}
	
	return	*_main;
}







EONIL_MEDIA_ENGINE_APPLICATION_NAMESPACE_END























