// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKRuntimeEvaluator.h"
#import "PKExpression.h"

@implementation PKRuntimeEvaluator

/**
 * Clean up
 */
-(void)dealloc {
  [super dealloc];
}

/**
 * Initialize
 */
-(id)init {
  if((self = [super init]) != nil){
  }
  return self;
}

/**
 * Evaluate a predicate
 */
-(id)evaluate:(PKExpression *)expression object:(id)object error:(NSError **)error {
  if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Not implemented.");
  return nil;
}

@end

