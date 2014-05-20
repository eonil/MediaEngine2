//
//  ____Eonil_MediaEngine_Controlling_UserGestureCapturingView_iOS.mm
//  TheMagnetismGame
//
//  Created by Hoon H. on 4/16/14.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#import "____Eonil_MediaEngine_Controlling_UserGestureCapturingView_iOS.h"

#if		EONIL_MEDIA_ENGINE_TARGET_IOS
#include "../TouchGestureCapturing.h"
using namespace	Eonil::Improvisations::MediaEngine::Controlling;

@implementation ____Eonil_MediaEngine_Controlling_UserGestureCapturingView_iOS
{
	NSMutableDictionary*	_touch_id_map;
	size_t					_last_touch_id;
}
- (id)initWithCoder:(NSCoder *)aDecoder
{
	[self doesNotRecognizeSelector:_cmd];
	return	nil;
}
- (id)initWithFrame:(CGRect)frameRect
{
	if (self = [super initWithFrame:frameRect])
	{
		_touch_id_map	=	[NSMutableDictionary dictionary];
		_last_touch_id	=	0;
		
		[self.layer setGeometryFlipped:YES];
	}
	return	self;
}



static inline auto
make_touch(UIView* self, UITouch* touch, Touch::CODE const& code) -> Touch
{
	CGSize	s1	=	self.frame.size;
	
	CGPoint	p2	=	[touch locationInView:self];
	Vector2	p3	=	Vector2((Scalar)p2.x, (Scalar)p2.y);
	
	CGFloat	len	=	std::min(s1.width, s1.height);
	p3.x		=	(p2.x - s1.width/2) / len * 2;
	p3.y		=	(p2.y - s1.height/2) / len * 2;
	
	Touch	t1	{};
	t1.code			=	code;
	t1.identifier	=	0;
	t1.coordinate	=	p3;
	
	return	t1;
}


- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	[super touchesBegan:touches withEvent:event];
	self.touchCpaturing->push(make_touch(self, [touches anyObject], Touch::CODE::BEGIN));
}
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
	[super touchesMoved:touches withEvent:event];
	self.touchCpaturing->push(make_touch(self, [touches anyObject], Touch::CODE::CONTINUE));
}
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	[super touchesEnded:touches withEvent:event];
	self.touchCpaturing->push(make_touch(self, [touches anyObject], Touch::CODE::END));
}
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
	[super touchesCancelled:touches withEvent:event];
	self.touchCpaturing->push(make_touch(self, [touches anyObject], Touch::CODE::CANCEL));
}







@end






#endif	//	EONIL_MEDIA_ENGINE_TARGET_IOS