//
//  BasicDocumentEditorViewController.h
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import <FoundationExtras/FoundationExtras.h>
#import "BasicViewController.h"

/*!
 Take care that the near-pane means pane at 0 index.
 In vertical separator mode (hotizontally resizable), near pane is at top.
 */
@interface	BasicTriplePaneSplitViewController : BasicViewController
@property	(readwrite,nonatomic,assign, getter = isVertical, setter = setVertical:)	BOOL					verticality;
@property	(readwrite,nonatomic,assign)	NSSplitViewDividerStyle	splitDividerStyle;
@property	(readwrite,nonatomic,strong)	BasicViewController*	nearViewController;
@property	(readwrite,nonatomic,strong)	BasicViewController*	centerViewController;
@property	(readwrite,nonatomic,strong)	BasicViewController*	farViewController;
@property	(readwrite,nonatomic,assign)	CGFloat					nearPaneLength;								//!	It is recommended to set far pane first to resize them stably.
@property	(readwrite,nonatomic,assign)	CGFloat					farPaneLength;
@end

@interface	BasicTriplePaneSplitViewController (BasicDocumentEditorSplitControlling) <NSSplitViewDelegate>
@end