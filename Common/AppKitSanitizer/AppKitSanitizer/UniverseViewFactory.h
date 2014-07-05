//
//  UniverseViewFactory.h
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import <FoundationExtras/FoundationExtras.h>
#import "BasicView.h"

@interface UniverseViewFactory : BasicObject
//+ (BasicView*)emptyView;
+ (BasicView*)viewWithSolidColor:(NSColor*)color;
+ (NSTableColumn*)tableColumnWithIdentifier:(NSString*)identifier title:(NSString*)title;
+ (NSTableColumn*)smallTableColumnWithIdentifier:(NSString*)identifier title:(NSString*)title;
+ (NSToolbarItem*)toolbarItemWithIdentifier:(NSString*)identifier label:(NSString*)label target:(id)target action:(SEL)action;
@end

@interface UniverseViewFactory (Debugging)
+ (BasicView*)viewWithRandomColorForDebugging;
+ (BasicView*)viewWithRandomDarkColorForDebugging;
@end