//
//  BasicDocument.h
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import <AppKit/NSDocument.h>

@interface BasicDocument : NSDocument
+ (id)allocWithZone:(struct _NSZone *)zone UNIVERSE_UNAVAILABLE_METHOD;
+ (id)copyWithZone:(struct _NSZone *)zone UNIVERSE_UNAVAILABLE_METHOD;
- (NSString *)windowNibName UNIVERSE_UNAVAILABLE_METHOD;
- (void)windowControllerDidLoadNib:(NSWindowController *)windowController UNIVERSE_UNAVAILABLE_METHOD;
- (void)windowControllerWillLoadNib:(NSWindowController *)windowController UNIVERSE_UNAVAILABLE_METHOD;
- (void)setWindow:(NSWindow *)window UNIVERSE_UNAVAILABLE_METHOD;
@end
