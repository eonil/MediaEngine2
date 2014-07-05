//
//  BasicViewController.h
//  Spacetime
//
//  Created by Hoon H. on 14/5/26.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import <FoundationExtras/FoundationExtras.h>




@interface BasicViewController : NSViewController
- (id)init;					//!	Now this is designated initializer. Override this in subclass.
- (id)initWithCoder:(NSCoder *)aDecoder UNIVERSE_UNAVAILABLE_METHOD;
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil UNIVERSE_UNAVAILABLE_METHOD;
- (void)loadView UNIVERSE_UNAVAILABLE_METHOD;
- (NSBundle *)nibBundle UNIVERSE_UNAVAILABLE_METHOD;
- (NSString *)nibName UNIVERSE_UNAVAILABLE_METHOD;
@end




@interface	BasicViewController (ProhibitUnexpectedMethods)
- (void)setLocalizedKey:(NSString *)localizedKey UNIVERSE_UNAVAILABLE_METHOD;
- (NSString *)localizedKey UNIVERSE_UNAVAILABLE_METHOD;
- (void)setKey:(NSString *)key UNIVERSE_UNAVAILABLE_METHOD;
- (NSString *)key UNIVERSE_UNAVAILABLE_METHOD;
- (void)setValue:(id)value UNIVERSE_UNAVAILABLE_METHOD;
- (id)value UNIVERSE_UNAVAILABLE_METHOD;
- (BOOL)isExplicitlyIncluded UNIVERSE_UNAVAILABLE_METHOD;

+ (BOOL)accessInstanceVariablesDirectly UNIVERSE_UNAVAILABLE_METHOD;
- (id)valueForKey:(NSString *)key UNIVERSE_UNAVAILABLE_METHOD;
- (void)setValue:(id)value forKey:(NSString *)key UNIVERSE_UNAVAILABLE_METHOD;
- (BOOL)validateValue:(inout id *)ioValue forKey:(NSString *)inKey error:(out NSError **)outError UNIVERSE_UNAVAILABLE_METHOD;
- (NSMutableArray *)mutableArrayValueForKey:(NSString *)key UNIVERSE_UNAVAILABLE_METHOD;
- (NSMutableOrderedSet *)mutableOrderedSetValueForKey:(NSString *)key NS_AVAILABLE(10_7, 5_0) UNIVERSE_UNAVAILABLE_METHOD;
- (NSMutableSet *)mutableSetValueForKey:(NSString *)key UNIVERSE_UNAVAILABLE_METHOD;
- (id)valueForKeyPath:(NSString *)keyPath UNIVERSE_UNAVAILABLE_METHOD;
- (void)setValue:(id)value forKeyPath:(NSString *)keyPath UNIVERSE_UNAVAILABLE_METHOD;
- (BOOL)validateValue:(inout id *)ioValue forKeyPath:(NSString *)inKeyPath error:(out NSError **)outError UNIVERSE_UNAVAILABLE_METHOD;
- (NSMutableArray *)mutableArrayValueForKeyPath:(NSString *)keyPath UNIVERSE_UNAVAILABLE_METHOD;
- (NSMutableOrderedSet *)mutableOrderedSetValueForKeyPath:(NSString *)keyPath NS_AVAILABLE(10_7, 5_0) UNIVERSE_UNAVAILABLE_METHOD;
- (NSMutableSet *)mutableSetValueForKeyPath:(NSString *)keyPath UNIVERSE_UNAVAILABLE_METHOD;
- (id)valueForUndefinedKey:(NSString *)key UNIVERSE_UNAVAILABLE_METHOD;
- (void)setValue:(id)value forUndefinedKey:(NSString *)key UNIVERSE_UNAVAILABLE_METHOD;
- (void)setNilValueForKey:(NSString *)key UNIVERSE_UNAVAILABLE_METHOD;
- (NSDictionary *)dictionaryWithValuesForKeys:(NSArray *)keys UNIVERSE_UNAVAILABLE_METHOD;
- (void)setValuesForKeysWithDictionary:(NSDictionary *)keyedValues UNIVERSE_UNAVAILABLE_METHOD;
@end
