// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

@class PKExpression;

/**
 * A predicate evaluator.
 */
@interface PKEvaluator : NSObject

+(PKEvaluator *)evaluator;

-(id)evaluate:(PKExpression *)expression object:(id)object error:(NSError **)error;

@end

