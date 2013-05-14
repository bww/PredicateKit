// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import <PredicateKit/PKPredicate.h>

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
  NSArray *lines = [source componentsSeparatedByCharactersInSet:[NSCharacterSet newlineCharacterSet]];
  STAssertNotNil(lines, @"Could not parse source lines");
  for(NSString *line in lines){
    NSLog(@"VV> %@", line);
    PKPredicate *predicate;
    STAssertNotNil((predicate = [PKPredicate predicateWithSource:line error:&error]), @"Error: %@", [error localizedDescription]);
    NSLog(@"<PP %@", predicate);
    id result;
    STAssertNotNil((result = [predicate evaluateWithObject:nil error:&error]), @"Error: %@", [error localizedDescription]);
  }
  [source release];
  
}

@end

