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
  
  NSArray *tests = [[NSArray alloc] initWithContentsOfFile:[[NSBundle bundleForClass:[self class]] pathForResource:@"001_test.plist" ofType:nil]];
  STAssertNotNil(tests, @"Tests must not be nil");
  
  for(NSDictionary *test in tests){
    NSError *error = nil;
    
    NSString *expression = [test objectForKey:@"expression"];
    STAssertNotNil(expression, @"Test expression must not be nil");
    BOOL expectCompilationFailure = [[test objectForKey:@"error:compile"] boolValue];
    BOOL expectEvaluationFailure = [[test objectForKey:@"error:runtime"] boolValue];
    id require = [test objectForKey:@"result"];
    if(!expectCompilationFailure && !expectEvaluationFailure) STAssertNotNil(require, @"Test result must not be nil");
    
    PKPredicate *predicate = [PKPredicate predicateWithSource:expression error:&error];
    if(expectCompilationFailure) STAssertNil(predicate, @"Compliation did not fail as expected: '%@'", expression);
    else STAssertNotNil(predicate, @"Compilation error: %@", [error localizedDescription]);
    if(predicate == nil) continue;
    
    id result = [predicate evaluateWithObject:nil error:&error];;
    if(expectEvaluationFailure) STAssertNil(result, @"Predicate evaluation did not fail as expected: '%@'", predicate);
    else STAssertEqualObjects(require, result, @"Predicate did not evaluate to the expected result: '%@'%@", predicate, (error != nil) ? [NSString stringWithFormat:@": %@", [error localizedDescription]] : @"");
    NSLog(@"P: %@ ==> %@", predicate, (result != nil) ? result : @"<failed>");
    
  }
  
}

@end

