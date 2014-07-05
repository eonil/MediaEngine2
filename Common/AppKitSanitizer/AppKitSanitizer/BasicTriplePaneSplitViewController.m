//
//  BasicDocumentEditorViewController.m
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import <FoundationExtras/FoundationExtras.h>
#import "BasicTriplePaneSplitViewController.h"
#import "BasicView.h"
#import "BasicViewController.h"

#import "UniverseViewFactory.h"
#import "UniverseLayoutFactory.h"






static CGFloat
round_cgfloat(CGFloat const f1)
{
	return	round(f1);
}

@interface	BasicDocumentEditorViewController_single_axis_rect : BasicObject
@property	(readwrite,nonatomic,assign)	NSSplitView*			verticalitySourceSplitView;
@property	(readwrite,nonatomic,assign)	CGRect					value;
@property	(readwrite,nonatomic,assign)	CGFloat					origin;
@property	(readwrite,nonatomic,assign)	CGFloat					size;
@property	(readwrite,nonatomic,assign)	CGFloat					theOtherOrigin;
@property	(readwrite,nonatomic,assign)	CGFloat					theOtherSize;
@end
@implementation BasicDocumentEditorViewController_single_axis_rect
@dynamic	value;
- (CGFloat)origin
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(_verticalitySourceSplitView, NSSplitView);
	}
	
	////
	
	BOOL	vert	=	self.verticalitySourceSplitView.isVertical;
	CGRect	_value	=	self.value;
	return	vert ? _value.origin.x : _value.origin.y;
}
- (void)setOrigin:(CGFloat)origin
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(_verticalitySourceSplitView, NSSplitView);
	}
	
	////
	
	BOOL	vert	=	self.verticalitySourceSplitView.isVertical;
	CGRect	_value	=	self.value;
	*(vert ? &_value.origin.x : &_value.origin.y)	=	round_cgfloat(origin);
	self.value	=	_value;
}
- (CGFloat)size
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(_verticalitySourceSplitView, NSSplitView);
	}
	
	////
	
	BOOL	vert	=	self.verticalitySourceSplitView.isVertical;
	CGRect	_value	=	self.value;
	return	vert ? _value.size.width : _value.size.height;
}
- (void)setSize:(CGFloat)size
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(_verticalitySourceSplitView, NSSplitView);
	}
	
	////
	
	BOOL	vert	=	self.verticalitySourceSplitView.isVertical;
	CGRect	_value	=	self.value;
	*(vert ? &_value.size.width : &_value.size.height)	=	round_cgfloat(size);
	self.value	=	_value;
}
- (CGFloat)theOtherOrigin
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(_verticalitySourceSplitView, NSSplitView);
	}
	
	////
	
	BOOL	hori	=	! self.verticalitySourceSplitView.isVertical;
	CGRect	_value	=	self.value;
	return	hori ? _value.origin.x : _value.origin.y;
}
- (void)setTheOtherOrigin:(CGFloat)theOtherOrigin
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(_verticalitySourceSplitView, NSSplitView);
	}
	
	////
	
	BOOL	hori	=	! self.verticalitySourceSplitView.isVertical;
	CGRect	_value	=	self.value;
	*(hori ? &_value.origin.x : &_value.origin.y)	=	round_cgfloat(theOtherOrigin);
	self.value	=	_value;
}
- (CGFloat)theOtherSize
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(_verticalitySourceSplitView, NSSplitView);
	}
	
	////
	
	BOOL	hori	=	! self.verticalitySourceSplitView.isVertical;
	CGRect	_value	=	self.value;
	return	hori ? _value.size.width : _value.size.height;
}
- (void)setTheOtherSize:(CGFloat)theOtherSize
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(_verticalitySourceSplitView, NSSplitView);
	}
	
	////
	
	BOOL	hori	=	! self.verticalitySourceSplitView.isVertical;
	CGRect	_value	=	self.value;
	*(hori ? &_value.size.width : &_value.size.height)	=	round_cgfloat(theOtherSize);
	self.value	=	_value;
}
@end
@interface	BasicDocumentEditorViewController_single_axis_rect_link_to_frame : BasicDocumentEditorViewController_single_axis_rect
@property	(readwrite,nonatomic,assign)	NSView*					frameLinkTarget;
@end
@implementation BasicDocumentEditorViewController_single_axis_rect_link_to_frame
- (CGRect)value
{
	return	_frameLinkTarget.frame;
}
- (void)setValue:(CGRect)value
{
	_frameLinkTarget.frame	=	value;
}
@end
@interface	BasicDocumentEditorViewController_single_axis_rect_link_to_bounds : BasicDocumentEditorViewController_single_axis_rect
@property	(readwrite,nonatomic,assign)	NSView*					boundsLinkTarget;
@end
@implementation BasicDocumentEditorViewController_single_axis_rect_link_to_bounds
- (CGRect)value
{
	return	_boundsLinkTarget.bounds;
}
- (void)setValue:(CGRect)value
{
	_boundsLinkTarget.bounds	=	value;
}
@end
typedef		BasicDocumentEditorViewController_single_axis_rect_link_to_frame	FRAME_LINK;
typedef		BasicDocumentEditorViewController_single_axis_rect_link_to_bounds	BOUNDS_LINK;











static CGFloat const	MAX_BOUND_PROPERTION	=	0.25;
static CGFloat const	PANE_MIN_SIZE			=	200;

//static CGFloat
//cgfloat_max(CGFloat const a, CGFloat const b)
//{
//	return	a > b ? a : b;
//}
static CGFloat
cgfloat_min(CGFloat const a, CGFloat const b)
{
	return	a < b ? a : b;
}

@interface	BasicDocumentEditorViewController_internal_pane_slot : BasicObject
@property	(readonly,nonatomic,strong)		FRAME_LINK*				layoutRectEditor;
@property	(readwrite,nonatomic,assign)	CGFloat					minimumLength;
@property	(readonly,nonatomic,strong)		BasicView*				paneContainerView;
@property	(readwrite,nonatomic,strong)	BasicViewController*	paneContentViewController;
@end
@implementation BasicDocumentEditorViewController_internal_pane_slot
{
	NSArray*	_pane_subview_layout_constraints;
}
@synthesize paneContainerView			=	_container_v;
@synthesize paneContentViewController	=	_external_content_vc;
- (id)init
{
	self	=	[super init];
	if (self)
	{
		_container_v		=	[UniverseViewFactory viewWithRandomDarkColorForDebugging];
//		_container_v		=	[BasicView instantiation];
		_layoutRectEditor	=	[FRAME_LINK instantiation];
		
		_layoutRectEditor.frameLinkTarget	=	_container_v;
	}
	return	self;
}
- (void)setPaneContentViewController:(BasicViewController *)new_content_vc
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		if (new_content_vc != nil)
		{
			UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(new_content_vc, BasicViewController);
			UNIVERSE_DEBUG_ASSERT_OBJECT_TYPE(new_content_vc.view, NSView);			//	If the view-controller is not nil, it should have a view.
		}
		if (new_content_vc != _external_content_vc)
		{
			if (_external_content_vc != nil)
			{
				/*
				 Once assigned view shouldn't be changed while it is bound to here.
				 */
				UNIVERSE_DEBUG_ASSERT(_container_v.subviews.count == 1);
				UNIVERSE_DEBUG_ASSERT(_external_content_vc.view == _container_v.subviews.lastObject);
			}
		}
//		UNIVERSE_DEBUG_ASSERT(new_content_vc.view.translatesAutoresizingMaskIntoConstraints == NO);
	}
	
	////
	
	if (_external_content_vc != new_content_vc)
	{
		if (_external_content_vc != nil)
		{
			[_container_v removeConstraints:_pane_subview_layout_constraints];
			_pane_subview_layout_constraints	=	nil;
			[_external_content_vc.view removeFromSuperview];
		}
		
		_external_content_vc	=	new_content_vc;
		
		if (_external_content_vc != nil)
		{
			[_container_v addSubview:_external_content_vc.view];
			_pane_subview_layout_constraints	=	[UniverseLayoutFactory layoutSubview:_external_content_vc.view toFillSuperview:_container_v];
			[_container_v addConstraints:_pane_subview_layout_constraints];
		}
	}
}
@end


































@interface BasicTriplePaneSplitViewController ()
@end

@implementation BasicTriplePaneSplitViewController
{
	NSSplitView*	_split_v;
	BOUNDS_LINK*	_bounds_of_splt;
	
	BasicDocumentEditorViewController_internal_pane_slot*	_near_pane_slot;
	BasicDocumentEditorViewController_internal_pane_slot*	_center_pane_slot;
	BasicDocumentEditorViewController_internal_pane_slot*	_far_pane_slot;
	
	NSArray*		_bottom_subview_layout_constraints;
	
	BOOL			_it_was_zero;
}
- (id)init
{
	self	=	[super init];
	if (self)
	{
		_split_v			=	[NSSplitView instantiation];
		_bounds_of_splt		=	[BOUNDS_LINK instantiation];
		
		_near_pane_slot		=	[BasicDocumentEditorViewController_internal_pane_slot instantiation];
		_far_pane_slot		=	[BasicDocumentEditorViewController_internal_pane_slot instantiation];
		_center_pane_slot	=	[BasicDocumentEditorViewController_internal_pane_slot instantiation];
		
		_split_v.autosaveName	=	@"split.positions";
		_bounds_of_splt.boundsLinkTarget								=	_split_v;
		_bounds_of_splt.verticalitySourceSplitView						=	_split_v;
		_near_pane_slot.layoutRectEditor.verticalitySourceSplitView		=	_split_v;
		_center_pane_slot.layoutRectEditor.verticalitySourceSplitView	=	_split_v;
		_far_pane_slot.layoutRectEditor.verticalitySourceSplitView		=	_split_v;
		_near_pane_slot.minimumLength		=	PANE_MIN_SIZE;
		_far_pane_slot.minimumLength		=	PANE_MIN_SIZE;
		
		////
		
		[super setView:_split_v];
		[_split_v setTranslatesAutoresizingMaskIntoConstraints:NO];
		[_split_v addSubview:_near_pane_slot.paneContainerView];
		[_split_v addSubview:_center_pane_slot.paneContainerView];
		[_split_v addSubview:_far_pane_slot.paneContainerView];
//		[_split_v setHoldingPriority:(NSLayoutPriorityFittingSizeCompression) forSubviewAtIndex:1];
//		[_split_v setHoldingPriority:(NSLayoutPriorityDefaultHigh) forSubviewAtIndex:0];
//		[_split_v setHoldingPriority:(NSLayoutPriorityDefaultHigh) forSubviewAtIndex:2];
		
		////
		
		_split_v.delegate	=	self;
		_it_was_zero		=	YES;
	}
	return	self;
}
- (void)dealloc
{
	_split_v.delegate	=	nil;
}
- (BOOL)isVertical
{
	return	[_split_v isVertical];
}
- (void)setVertical:(BOOL)verticality
{
	[_split_v setVertical:verticality];
	[_split_v adjustSubviews];				//	required to re-position splitters for the orientation. re-orientation will not be performed without this.
}
- (NSSplitViewDividerStyle)splitDividerStyle
{
	return	_split_v.dividerStyle;
}
- (void)setSplitDividerStyle:(NSSplitViewDividerStyle)splitDividerStyle
{
	[_split_v setDividerStyle:splitDividerStyle];
}
- (BasicViewController *)nearViewController
{
	return	_near_pane_slot.paneContentViewController;
}
- (void)setNearViewController:(BasicViewController *)new_content_vc
{
	_near_pane_slot.paneContentViewController	=	new_content_vc;
}
- (BasicViewController *)farViewController
{
	return	_far_pane_slot.paneContentViewController;
}
- (void)setFarViewController:(BasicViewController *)new_content_vc
{
	_far_pane_slot.paneContentViewController	=	new_content_vc;
}
- (void)setNearPaneLength:(CGFloat)nearPaneLength
{
	_nearPaneLength	=	nearPaneLength;
	[_split_v setPosition:_nearPaneLength ofDividerAtIndex:0];
	[_split_v adjustSubviews];
}
- (void)setFarPaneLength:(CGFloat)farPaneLength
{
	_farPaneLength	=	farPaneLength;
	[_split_v setPosition:_bounds_of_splt.size - _farPaneLength ofDividerAtIndex:1];
	[_split_v adjustSubviews];
}
- (BasicViewController *)centerViewController
{
	return	_center_pane_slot.paneContentViewController;
}
- (void)setCenterViewController:(BasicViewController *)new_content_vc
{
	_center_pane_slot.paneContentViewController	=	new_content_vc;
}
@end




























@implementation BasicTriplePaneSplitViewController (BasicDocumentEditorSplitControlling)
- (CGFloat)splitView:(NSSplitView *)splitView constrainMinCoordinate:(CGFloat)proposedMinimumPosition ofSubviewAt:(NSInteger)dividerIndex
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT(splitView == _split_v);
	}
	
	////
	
	if (dividerIndex == 0)
	{
		CGFloat	f1	=	_near_pane_slot.minimumLength;
		CGFloat	f2	=	cgfloat_min(f1, _bounds_of_splt.size * MAX_BOUND_PROPERTION);
		return	f2;
	}
	return	proposedMinimumPosition;
}
- (CGFloat)splitView:(NSSplitView *)splitView constrainMaxCoordinate:(CGFloat)proposedMaximumPosition ofSubviewAt:(NSInteger)dividerIndex
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT(splitView == _split_v);
	}
	
	////
	
	if (dividerIndex == 1)
	{
		CGFloat	f1	=	_far_pane_slot.minimumLength;
		CGFloat	f2	=	cgfloat_min(f1, _bounds_of_splt.size * MAX_BOUND_PROPERTION);
		return	_bounds_of_splt.size - f2;
	}
	return	proposedMaximumPosition;
}
//- (CGFloat)splitView:(NSSplitView *)splitView constrainSplitPosition:(CGFloat)proposedPosition ofSubviewAt:(NSInteger)dividerIndex
//{
//}
- (BOOL)splitView:(NSSplitView *)splitView canCollapseSubview:(NSView *)subview
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT(splitView == _split_v);
	}
	
	////
	
	return	subview != _center_pane_slot.paneContainerView;
}
- (BOOL)splitView:(NSSplitView *)splitView shouldCollapseSubview:(NSView *)subview forDoubleClickOnDividerAtIndex:(NSInteger)dividerIndex
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT(splitView == _split_v);
	}
	
	////
	
	return	YES;
}
//- (BOOL)splitView:(NSSplitView *)splitView shouldAdjustSizeOfSubview:(NSView *)view
//{
//}
- (void)splitView:(NSSplitView *)splitView resizeSubviewsWithOldSize:(NSSize)oldSize
{
	if (EONIL_APPKITSAN_USE_DEBUGGING_ASSERTIONS)
	{
		UNIVERSE_DEBUG_ASSERT(splitView == _split_v);
	}
	
	////
	
	[_near_pane_slot.layoutRectEditor setTheOtherSize:_bounds_of_splt.theOtherSize];
	[_center_pane_slot.layoutRectEditor setTheOtherSize:_bounds_of_splt.theOtherSize];
	[_far_pane_slot.layoutRectEditor setTheOtherSize:_bounds_of_splt.theOtherSize];

	if (_bounds_of_splt.size > 2)
	{
		if (_it_was_zero)
		{
			NSLog(@"A split-view size has expanded from zero...");
			
			_it_was_zero	=	NO;
			
			CGFloat	len1	=	_bounds_of_splt.size - 2;
			CGFloat	len2	=	len1 / 3;
			CGFloat	x1		=	0;
			CGFloat	x2		=	1 + len2;
			CGFloat	x3		=	2 + len2 + len2;
			[_near_pane_slot.layoutRectEditor setOrigin:x1];
			[_near_pane_slot.layoutRectEditor setSize:len2];
			[_center_pane_slot.layoutRectEditor setOrigin:x2];
			[_center_pane_slot.layoutRectEditor setSize:len2];
			[_far_pane_slot.layoutRectEditor setOrigin:x3];
			[_far_pane_slot.layoutRectEditor setSize:len2];
		}
		else
		{
			[_split_v adjustSubviews];
		}
	}
	else
	{
		[_near_pane_slot.layoutRectEditor setOrigin:0];
		[_near_pane_slot.layoutRectEditor setSize:0];
		[_center_pane_slot.layoutRectEditor setOrigin:0];
		[_center_pane_slot.layoutRectEditor setSize:0];
		[_far_pane_slot.layoutRectEditor setOrigin:0];
		[_far_pane_slot.layoutRectEditor setSize:0];
		
		_it_was_zero	=	YES;
		
		NSLog(@"A split-view size has gone to zero...");
	}
}
@end

















