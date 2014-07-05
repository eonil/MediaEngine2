//
//  ____Eonil_MediaEngine_Controlling_UserGestureCapturingView_OSX.mm
//  TheMagnetismGame
//
//  Created by Hoon H. on 4/16/14.
//  Copyright (c) 2014 Eonil Company. All rights reserved.
//

#import "____Eonil_MediaEngine_Controlling_UserGestureCapturingView_OSX.h"

#if		EONIL_MEDIA_ENGINE_TARGET_OSX
#include "../TouchGestureCapturing.h"
#include "Common.h"
using namespace	Eonil::MediaEngine::Controlling;


@implementation ____Eonil_MediaEngine_Controlling_UserGestureCapturingView_OSX
{
	NSMutableDictionary*	_touch_id_map;
	size_t					_last_touch_id;
}
- (id)initWithCoder:(NSCoder *)aDecoder
{
	[self doesNotRecognizeSelector:_cmd];
	return	nil;
}
- (id)initWithFrame:(NSRect)frameRect
{
	if (self = [super initWithFrame:frameRect])
	{
		_touch_id_map	=	[NSMutableDictionary dictionary];
		_last_touch_id	=	0;
		
		[self setAcceptsTouchEvents:YES];
		[self setWantsRestingTouches:YES];
	}
	return	self;
}



static inline auto
make_touch(NSView* self, NSEvent* event, Touch::CODE const& code) -> Touch
{
	CGSize	s1	=	self.frame.size;
	
	CGPoint	p1	=	[event locationInWindow];
	CGPoint	p2	=	[self convertPoint:p1 fromView:nil];
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

- (void)mouseMoved:(NSEvent *)theEvent
{
	[super mouseMoved:theEvent];
}
- (void)mouseDown:(NSEvent *)theEvent
{
	[super mouseDown:theEvent];
	self.touchCpaturing->push(make_touch(self, theEvent, Touch::CODE::BEGIN));
}
- (void)mouseDragged:(NSEvent *)theEvent
{
	[super mouseDragged:theEvent];
	self.touchCpaturing->push(make_touch(self, theEvent, Touch::CODE::CONTINUE));
}
- (void)mouseUp:(NSEvent *)theEvent
{
	[super mouseUp:theEvent];
	self.touchCpaturing->push(make_touch(self, theEvent, Touch::CODE::END));
}





//- (void)touchesBeganWithEvent:(NSEvent *)event
//{
//	[super touchesBeganWithEvent:event];
//}
//- (void)touchesMovedWithEvent:(NSEvent *)event
//{
//	[super touchesMovedWithEvent:event];
//}
//- (void)touchesEndedWithEvent:(NSEvent *)event
//{
//	[super touchesEndedWithEvent:event];
//}
//- (void)touchesCancelledWithEvent:(NSEvent *)event
//{
//	[super touchesCancelledWithEvent:event];
//}
//- (void)scrollWheel:(NSEvent *)event
//{
//	EONIL_DEBUG_ASSERT(self.touchCpaturing != nullptr);
//	
//	[super scrollWheel:event];
////	NSLog(@"%@, %@", NSStringFromSelector(_cmd), event);
//	
//	auto
//	get_code	=	[&](NSTouchPhase p)
//	{
//		switch (p)
//		{
//			case	NSEventPhaseBegan:			return	Touch::CODE::BEGIN;
//			case	NSEventPhaseChanged:		return	Touch::CODE::CONTINUE;
//			case	NSEventPhaseStationary:		return	Touch::CODE::CONTINUE;
//			case	NSEventPhaseEnded:			return	Touch::CODE::END;
//			case	NSEventPhaseCancelled:		return	Touch::CODE::CANCEL;
//				
//			case	NSEventPhaseNone:		return	Touch::CODE::NONE;
//			case	NSEventPhaseMayBegin:		return	Touch::CODE::NONE;
//		}
//		EONIL_UNREACHABLE_CODE();
//	};
//
//	////
//	
//	CGPoint	p1	=	[event locationInWindow];
//	CGPoint	p2	=	[self convertPoint:p1 fromView:nil];
//	
//	Touch::CODE	c3	=	get_code(event.phase);
//	
//	if (c3 != Touch::CODE::NONE)
//	{
//		Touch		t4	=	{c3, 0};
//		t4.coordinate	=	{(Scalar)(p2.x), (Scalar)(p2.y)};
//		
//		self.touchCpaturing->push(std::move(t4));		
//	}
//	
//	////
////	
////	auto
////	get_new_id		=	[&]()
////	{
////		_last_touch_id++;				//	Touch ID is fine to be overflown. Let it overflow.
////		return	_last_touch_id;
////	};
////	
////	auto
////	renew_all_touch_ids	=	[&]()
////	{
////		NSMutableDictionary*	d1		=	[NSMutableDictionary dictionary];
////		NSSet*					ts1		=	[event touchesMatchingPhase:(NSTouchPhaseAny) inView:self];
////		
////		for (NSTouch* t2 in ts1)
////		{
////			NSNumber*	tid2	=	_touch_id_map[t2.identity];
////			
////			if (tid2 == nil)
////			{
////				d1[t2.identity]		=	@(get_new_id());
////			}
////			else
////			{
////				d1[t2.identity]		=	tid2;
////			}
////		}
////		
////		_touch_id_map	=	d1;
////	};
////	
////
////	////
////	
////	renew_all_touch_ids();
////	
////	//	Now you have proper IDs for all touch objects.
////	
////	NSSet*	ts1		=	[event touchesMatchingPhase:(NSTouchPhaseAny) inView:self];
////	for (NSTouch* t2 in ts1)
////	{
////		NSNumber*	tid2	=	_touch_id_map[t2.identity];
////		size_t		tid3	=	[tid2 unsignedIntegerValue];
////		
////		NSPoint	p3	=	[t2 normalizedPosition];
////		Vector2	p4	=	{(Scalar)(p3.x), (Scalar)(p3.y)};
////		Touch	t5	=	{get_code(t2.phase), tid3};
////		
////		self.touchCpaturing->push(std::move(t5));
////	}
//}
//- (void)swipeWithEvent:(NSEvent *)event
//{
//	[super swipeWithEvent:event];
//	NSLog(@"%@, %@", NSStringFromSelector(_cmd), event);
//}
//- (void)magnifyWithEvent:(NSEvent *)event
//{
//	[super magnifyWithEvent:event];
//	NSLog(@"%@, %@", NSStringFromSelector(_cmd), event);
//}
@end


#endif	//	EONIL_MEDIA_ENGINE_TARGET_OSX