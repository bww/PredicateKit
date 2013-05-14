// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKPredicate.h"
#import "PKParser.h"
#import "PKExpression.h"
#import "PKEvaluator.h"
#import "PKRuntimeEvaluator.h"

@implementation PKPredicate

/**
 * Create a predicate from the provided source which is evaluated
 * by the default runtime evaluator.
 */
+(PKPredicate *)predicateWithSource:(NSString *)source error:(NSError **)error {
  PKExpression *expression;
  if((expression = [[PKParser parser] parse:source error:error]) != nil){
    return [[[self alloc] initWithExpression:expression evaluator:[PKRuntimeEvaluator evaluator]] autorelease];
  }else{
    return nil;
  }
}

/**
 * Clean up
 */
-(void)dealloc {
  [_expression release];
  [_evaluator release];
  [super dealloc];
}

/**
 * Initialize with an expression
 */
-(id)initWithExpression:(PKExpression *)expression evaluator:(PKEvaluator *)evaluator {
  if((self = [super init]) != nil){
    _expression = [expression retain];
    _evaluator = [evaluator retain];
  }
  return self;
}

/**
 * Evaluate this predicate
 */
-(id)evaluateWithObject:(id)object {
  return [self evaluateWithObject:object error:nil];
}

/**
 * Evaluate this predicate
 */
-(id)evaluateWithObject:(id)object error:(NSError **)error {
  return [_evaluator evaluate:_expression object:object error:error];
}

/**
 * String description
 */
-(NSString *)description {
  return [_expression description];
}

@end

