//
//  CommonStuffsForC__Tests.m
//  CommonStuffsForC++Tests
//
//  Created by Hoon H. on 2014/06/28.
//  Copyright (c) 2014 Eonil. All rights reserved.
//

#import <XCTest/XCTest.h>
#include "all____test.h"

@interface CommonStuffsForC__Tests : XCTestCase
@end






@implementation CommonStuffsForC__Tests
- (void)setUp
{
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown
{
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
}

- (void)testExample
{
//    XCTFail(@"No implementation for \"%s\"", __PRETTY_FUNCTION__);
	
	Eonil::Common::age2::test_all::run();
}

@end
