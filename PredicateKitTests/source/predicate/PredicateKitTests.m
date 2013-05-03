// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import <PredicateKit/PKParser.h>

#import "PredicateKitTests.h"

@implementation PredicateKitTests

-(void)setUp {
  [super setUp];
}

-(void)tearDown {
  [super tearDown];
}

-(void)testExample {
  NSError *error = nil;
  NSString *source;
  
  source = [[NSString alloc] initWithContentsOfFile:@"PredicateKitTests/resources/tests/001.wgpl" encoding:NSUTF8StringEncoding error:&error];
  STAssertNotNil(source, @"Could not load source");
  STAssertTrue([[PKParser parser] parse:source error:&error], @"Could not parse predicate: %@", [error localizedDescription]);
  [source release];
  
}

@end
