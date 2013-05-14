// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

@class PKExpression;
@class PKEvaluator;

/**
 * A predicate. PKPredicate encapsulates an expression and evaluator in a more
 * convenient interface.
 */
@interface PKPredicate : NSObject {
  
  PKExpression  * _expression;
  PKEvaluator   * _evaluator;
  
}

+(PKPredicate *)predicateWithSource:(NSString *)source error:(NSError **)error;

-(id)initWithExpression:(PKExpression *)expression evaluator:(PKEvaluator *)evaluator;

-(id)evaluateWithObject:(id)object;
-(id)evaluateWithObject:(id)object error:(NSError **)error;

@end

