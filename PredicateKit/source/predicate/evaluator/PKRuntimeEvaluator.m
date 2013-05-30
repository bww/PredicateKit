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
#import "PKLogicalExpression.h"
#import "PKIdentifierExpression.h"
#import "PKLiteralExpression.h"
#import "PKPatternExpression.h"

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
  if(type == [PKLogicalExpression class]){
    return [self evaluateLogicalExpression:(PKLogicalExpression *)expression object:object error:error];
  }else if(type == [PKComparisonExpression class]){
    return [self evaluateComparisonExpression:(PKComparisonExpression *)expression object:object error:error];
  }else if(type == [PKBitwiseExpression class]){
    return [self evaluateBitwiseExpression:(PKBitwiseExpression *)expression object:object error:error];
  }else if(type == [PKIdentifierExpression class]){
    return [self evaluateIdentifierExpression:(PKIdentifierExpression *)expression object:object error:error];
  }else if(type == [PKLiteralExpression class]){
    return [self evaluateLiteralExpression:(PKLiteralExpression *)expression object:object error:error];
  }else{
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Unsupported expression type: %@", [expression class]);
    return nil;
  }
}

#pragma mark - Logical expression

/**
 * Evaluate a logical expression
 */
-(id)evaluateLogicalExpression:(PKLogicalExpression *)expression object:(id)object error:(NSError **)error {
  switch(expression.type){
    case kPKLogicalAnd:
    case kPKLogicalOr:
      return [self evaluateLogicalInfixExpression:expression object:object error:error];
    case kPKLogicalNot:
      return [self evaluateLogicalUnaryExpression:expression object:object error:error];
    default:
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Unsupported logical expression type: %d", expression.type);
      return nil;
  }
}

/**
 * Evaluate a logical expression
 */
-(id)evaluateLogicalInfixExpression:(PKLogicalExpression *)expression object:(id)object error:(NSError **)error {
  id left, right;
  
  if([expression.expressions count] != 2){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"%@ must have exactly two operands", PKLogicalTypeGetName(expression.type));
    return nil;
  }
  
  if((left = [self evaluateExpression:[expression.expressions objectAtIndex:0] object:object error:error]) == nil)
    return nil;
  if((right = [self evaluateExpression:[expression.expressions objectAtIndex:1] object:object error:error]) == nil)
    return nil;
  
  if(![left isKindOfClass:[NSNumber class]]){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to %@ must evaluate to boolean", PKLogicalTypeGetName(expression.type));
    return nil;
  }
  
  if(![right isKindOfClass:[NSNumber class]]){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to %@ must evaluate to boolean", PKLogicalTypeGetName(expression.type));
    return nil;
  }
  
  switch(expression.type){
    case kPKLogicalAnd:
      return [NSNumber numberWithBool:([left boolValue] && [right boolValue])];
    case kPKLogicalOr:
      return [NSNumber numberWithBool:([left boolValue] || [right boolValue])];
    default:
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Unsupported logical infix expression type: %d", expression.type);
      return nil;
  }
  
}

/**
 * Evaluate a logical expression
 */
-(id)evaluateLogicalUnaryExpression:(PKLogicalExpression *)expression object:(id)object error:(NSError **)error {
  id right;
  
  if([expression.expressions count] != 1){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"%@ must have exactly two operands", PKLogicalTypeGetName(expression.type));
    return nil;
  }
  
  if((right = [self evaluateExpression:[expression.expressions objectAtIndex:0] object:object error:error]) == nil){
    return nil;
  }
  
  if(![right isKindOfClass:[NSNumber class]]){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to %@ must evaluate to boolean", PKLogicalTypeGetName(expression.type));
    return nil;
  }
  
  switch(expression.type){
    case kPKLogicalNot:
      return [NSNumber numberWithBool:![right boolValue]];
    default:
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Unsupported logical unary expression type: %d", expression.type);
      return nil;
  }
  
}

#pragma mark - Comparison expression

/**
 * Evaluate a comparison expression
 */
-(id)evaluateComparisonExpression:(PKComparisonExpression *)expression object:(id)object error:(NSError **)error {
  
  switch(expression.type){
    case kPKComparisonEqualTo:
    case kPKComparisonNotEqualTo:
    case kPKComparisonLessThan:
    case kPKComparisonLessThanOrEqualTo:
    case kPKComparisonGreaterThan:
    case kPKComparisonGreaterThanOrEqualTo:
      return [self evaluateRelativeComparisonExpression:expression object:object error:error];
    case kPKComparisonMatches:
      return [self evaluateMatchingComparisonExpression:expression object:object error:error];
    case kPKComparisonIn:;
    //  return [self evaluateCollectionComparisonExpression:expression object:object error];
  }
  
  if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Unsupported comparison expression type: %d", expression.type);
  return nil;
  
}

/**
 * Evaluate a comparison expression
 */
-(id)evaluateRelativeComparisonExpression:(PKComparisonExpression *)expression object:(id)object error:(NSError **)error {
  NSComparisonResult result;
  id left, right;
  
  if([expression.operands count] != 2){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"%@ must have exactly two operands", PKComparisonTypeGetName(expression.type));
    return nil;
  }
  
  if((left = [self evaluateExpression:[expression.operands objectAtIndex:0] object:object error:error]) == nil){
    // use the error from the left expression evaluation
    return nil;
  }else if(![left respondsToSelector:@selector(compare:)]){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to %@ must evaulate to an object which implements the selector -compare:", PKComparisonTypeGetName(expression.type));
    return nil;
  }
  
  if((right = [self evaluateExpression:[expression.operands objectAtIndex:1] object:object error:error]) == nil){
    // use the error from the right expression evaluation
    return nil;
  }else if(![right respondsToSelector:@selector(compare:)]){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to %@ must evaulate to an object which implements the selector -compare:", PKComparisonTypeGetName(expression.type));
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
    default:
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Unsupported equality comparison expression type: %d", expression.type);
      return nil;
  }
  
}

/**
 * Evaluate a matching expression
 */
-(id)evaluateMatchingComparisonExpression:(PKComparisonExpression *)expression object:(id)object error:(NSError **)error {
  PKPatternExpression *pattern = nil;
  NSRegularExpression *regex = nil;
  NSError *inner = nil;
  id left;//, right;
  
  if([expression.operands count] != 2){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"%@ must have exactly two operands", PKComparisonTypeGetName(expression.type));
    return nil;
  }
  
  if((pattern = [expression.operands objectAtIndex:1]) == nil || object_getClass(pattern) != [PKPatternExpression class]){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to %@ must be a pattern", PKComparisonTypeGetName(expression.type));
    return nil;
  }
  
  if((regex = [NSRegularExpression regularExpressionWithPattern:pattern.pattern options:0 error:&inner]) == nil){
    if(error) *error = NSERROR_WITH_CAUSE(PKPredicateErrorDomain, PKStatusError, inner, @"Pattern operand to %@ is invalid", PKComparisonTypeGetName(expression.type));
    return nil;
  }
  
  if((left = [self evaluateExpression:[expression.operands objectAtIndex:0] object:object error:error]) == nil){
    return nil;
  }else if(![left isKindOfClass:[NSString class]]){
    if(error) *error = NSERROR_WITH_CAUSE(PKPredicateErrorDomain, PKStatusError, inner, @"Left operand to %@ must be a string", PKComparisonTypeGetName(expression.type));
    return nil;
  }
  
  switch(expression.type){
    case kPKComparisonMatches:
      return [NSNumber numberWithBool:[regex numberOfMatchesInString:left options:0 range:NSMakeRange(0, [left length])] > 0];
    default:
      if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Unsupported matching comparison expression type: %d", expression.type);
      return nil;
  }
  
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

