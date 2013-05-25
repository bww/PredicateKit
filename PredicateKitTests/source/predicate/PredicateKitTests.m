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
  
  NSArray *tests = [[NSArray alloc] initWithContentsOfFile:[[NSBundle bundleForClass:[self class]] pathForResource:@"001_test.plist" ofType:nil]];
  STAssertNotNil(tests, @"Tests must not be nil");
  
  for(NSDictionary *test in tests){
    
    NSString *expression = [test objectForKey:@"expression"];
    STAssertNotNil(expression, @"Test expression must not be nil");
    id require = [test objectForKey:@"result"];
    STAssertNotNil(require, @"Test result must not be nil");
    
    PKPredicate *predicate = [PKPredicate predicateWithSource:expression error:&error];
    STAssertNotNil(predicate, @"Compilation error: %@", [error localizedDescription]);
    if(predicate == nil) continue;
    
    id result;
    STAssertNotNil((result = [predicate evaluateWithObject:nil error:&error]), @"Runtime error: %@", [error localizedDescription]);
    STAssertEqualObjects(require, result, @"Predicate did not evaluate to the expected result: %@", predicate);
    NSLog(@"P: %@ ==> %@", predicate, result);
    
  }
  
}

@end

