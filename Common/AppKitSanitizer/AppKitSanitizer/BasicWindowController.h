//
//  BasicWindowController.h
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import <FoundationExtras/FoundationExtras.h>
#import <AppKit/NSWindowController.h>
#import "BasicWindow.h"
#import "BasicDocument.h"

@interface BasicWindowController : NSWindowController
+ (id)allocWithZone:(struct _NSZone *)zone UNIVERSE_UNAVAILABLE_METHOD;
+ (id)copyWithZone:(struct _NSZone *)zone UNIVERSE_UNAVAILABLE_METHOD;
- (id)init UNIVERSE_UNAVAILABLE_METHOD;										
- (id)initWithCoder:(NSCoder *)aDecoder UNIVERSE_UNAVAILABLE_METHOD;
- (id)initWithWindowNibName:(NSString *)windowNibName UNIVERSE_UNAVAILABLE_METHOD;
- (id)initWithWindowNibName:(NSString *)windowNibName owner:(id)owner UNIVERSE_UNAVAILABLE_METHOD;
- (id)initWithWindowNibPath:(NSString *)windowNibPath owner:(id)owner UNIVERSE_UNAVAILABLE_METHOD;
- (BOOL)isWindowLoaded UNIVERSE_UNAVAILABLE_METHOD;
- (void)windowWillLoad UNIVERSE_UNAVAILABLE_METHOD;
- (void)windowDidLoad UNIVERSE_UNAVAILABLE_METHOD UNIVERSE_NON_RETURNING_METHOD;
- (void)loadWindow UNIVERSE_UNAVAILABLE_METHOD;
- (id)owner UNIVERSE_UNAVAILABLE_METHOD;
- (NSString *)windowNibName UNIVERSE_UNAVAILABLE_METHOD;
- (NSString *)windowNibPath UNIVERSE_UNAVAILABLE_METHOD;
- (id)initWithWindow:(BasicWindow *)window;						//!	Designated initializer.
- (BasicWindow *)window;
- (void)setWindow:(BasicWindow *)window;
- (BasicDocument*)document;
- (void)setDocument:(BasicDocument *)document;
@end






