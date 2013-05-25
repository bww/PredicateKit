// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import <objc/runtime.h>

#import "PKRuntimeEvaluator.h"
#import "PKExpression.h"
#import "PKBitwiseExpression.h"
#import "PKComparisonExpression.h"
#import "PKCompoundExpression.h"
#import "PKIdentifierExpression.h"
#import "PKLiteralExpression.h"

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
  return [self evaluateExpression:expression object:object error:error];
}

/**
 * Evaluate an expression
 */
-(id)evaluateExpression:(PKExpression *)expression object:(id)object error:(NSError **)error {
  id type = object_getClass(expression);
  
  if(type == [PKCompoundExpression class]){
    return [self evaluateCompoundExpression:(PKCompoundExpression *)expression object:object error:error];
  }else if(type == [PKComparisonExpression class]){
    return [self evaluateComparisonExpression:(PKComparisonExpression *)expression object:object error:error];
  }else if(type == [PKBitwiseExpression class]){
    return [self evaluateBitwiseExpression:(PKBitwiseExpression *)expression object:object error:error];
  }else if(type == [PKIdentifierExpression class]){
    return [self evaluateIdentifierExpression:(PKIdentifierExpression *)expression object:object error:error];
  }else if(type == [PKLiteralExpression class]){
    return [self evaluateLiteralExpression:(PKLiteralExpression *)expression object:object error:error];
  }
  
  if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Unsupported expression type: %@", [expression class]);
  return nil;
  
}

/**
 * Evaluate a compound expression
 */
-(id)evaluateCompoundExpression:(PKCompoundExpression *)expression object:(id)object error:(NSError **)error {
  id left, right;
  
  if(expression.type == kPKCompoundAnd){
    
    if([expression.expressions count] != 2){
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Expression && must have exactly two operands");
      return nil;
    }
    
    if((left = [self evaluateExpression:[expression.expressions objectAtIndex:0] object:object error:error]) == nil) return nil;
    if((right = [self evaluateExpression:[expression.expressions objectAtIndex:1] object:object error:error]) == nil) return nil;
    
    if(![left isKindOfClass:[NSNumber class]]){
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to expression && must evaluate to boolean");
      return nil;
    }
    
    if(![right isKindOfClass:[NSNumber class]]){
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to expression && must evaluate to boolean");
      return nil;
    }
    
    return [NSNumber numberWithBool:([left boolValue] && [right boolValue])];
    
  }else if(expression.type == kPKCompoundOr){
    
    if([expression.expressions count] != 2){
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Expression || must have exactly two operands");
      return nil;
    }
    
    if((left = [self evaluateExpression:[expression.expressions objectAtIndex:0] object:object error:error]) == nil) return nil;
    if((right = [self evaluateExpression:[expression.expressions objectAtIndex:1] object:object error:error]) == nil) return nil;
    
    if(![left isKindOfClass:[NSNumber class]]){
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to expression || must evaluate to boolean");
      return nil;
    }
    
    if(![right isKindOfClass:[NSNumber class]]){
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to expression || must evaluate to boolean");
      return nil;
    }
    
    return [NSNumber numberWithBool:([left boolValue] || [right boolValue])];
    
  }else if(expression.type == kPKCompoundNot){
    
    if([expression.expressions count] != 1){
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Expression ! must have exactly two operands");
      return nil;
    }
    
    if((left = [self evaluateExpression:[expression.expressions objectAtIndex:0] object:object error:error]) == nil) return nil;
    
    if(![left isKindOfClass:[NSNumber class]]){
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to expression || must evaluate to boolean");
      return nil;
    }
    
    return [NSNumber numberWithBool:[left boolValue]];
    
  }
  
  if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Unsupported logical expression type: %d", expression.type);
  return nil;
  
}

/**
 * Evaluate a comparison expression
 */
-(id)evaluateComparisonExpression:(PKComparisonExpression *)expression object:(id)object error:(NSError **)error {
  NSComparisonResult result;
  id left, right;
  
  if([expression.operands count] != 2){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Comparison expressions must have exactly two operands");
    return nil;
  }
  
  if((left = [self evaluateExpression:[expression.operands objectAtIndex:0] object:object error:error]) == nil) return nil;
  if((right = [self evaluateExpression:[expression.operands objectAtIndex:1] object:object error:error]) == nil) return nil;
  
  if(![left respondsToSelector:@selector(compare:)]){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to comparison expressions must implement -compare:");
    return nil;
  }
  
  if(![right respondsToSelector:@selector(compare:)]){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to comparison expressions must implement -compare:");
    return nil;
  }
  
  result = [left compare:right];
  
  switch(expression.type){
    case kPKComparisonEqualTo:
      return [NSNumber numberWithBool:result == NSOrderedSame];
    case kPKComparisonNotEqualTo:
      return [NSNumber numberWithBool:result != NSOrderedSame];
    case kPKComparisonLessThan:
      return [NSNumber numberWithBool:result < NSOrderedSame];
    case kPKComparisonLessThanOrEqualTo:
      return [NSNumber numberWithBool:result <= NSOrderedSame];
    case kPKComparisonGreaterThan:
      return [NSNumber numberWithBool:result > NSOrderedSame];
    case kPKComparisonGreaterThanOrEqualTo:
      return [NSNumber numberWithBool:result >= NSOrderedSame];
    case kPKComparisonMatches:
      break;
    case kPKComparisonIn:
      break;
  }
  
  if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Unsupported comparison expression type: %d", expression.type);
  return nil;
  
}

/**
 * Evaluate a bitwise expression
 */
-(id)evaluateBitwiseExpression:(PKBitwiseExpression *)expression object:(id)object error:(NSError **)error {
  return [NSNumber numberWithBool:FALSE];
}

/**
 * Evaluate an identifier expression
 */
-(id)evaluateIdentifierExpression:(PKIdentifierExpression *)expression object:(id)object error:(NSError **)error {
  return [NSNumber numberWithBool:FALSE];
}

/**
 * Evaluate a literal expression
 */
-(id)evaluateLiteralExpression:(PKLiteralExpression *)expression object:(id)object error:(NSError **)error {
  return expression.value;
}

@end

