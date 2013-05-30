// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import <PredicateKit/PKPredicate.h>

#import "PredicateKitTests.h"

extern char **environ;

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
  
  NSMutableDictionary *context = [NSMutableDictionary dictionary];
  [context setObject:@"value A" forKey:@"a"];
  [context setObject:@"value B" forKey:@"b"];
  [context setObject:@"value C" forKey:@"c"];
  
  for(char **env = environ; *env; env++){
    char *pair = strdup(*env);
    char *value;
    if((value = strchr(pair, '=')) != NULL){
      *value = 0; value++;
      [context setObject:[NSString stringWithUTF8String:value] forKey:[NSString stringWithUTF8String:pair]];
    }
    if(pair) free(pair);
  }
  
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
    
    id result = [predicate evaluateWithObject:context error:&error];
    if(expectEvaluationFailure) STAssertNil(result, @"Predicate evaluation did not fail as expected: '%@'", predicate);
    else STAssertEqualObjects(require, result, @"Predicate did not evaluate to the expected result: '%@'%@", predicate, (error != nil) ? [NSString stringWithFormat:@": %@", [error localizedDescription]] : @"");
    NSLog(@"P: %@ ==> %@", predicate, (result != nil) ? result : @"<failed>");
    
  }
  
}

@end

