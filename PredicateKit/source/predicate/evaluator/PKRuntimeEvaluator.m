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
#import "PKExpressionModifier.h"
#import "PKModifiedExpression.h"
#import "PKCollectionExpression.h"

#define UNSUPPORTED_EXPRESSION(expression, error) __UNSUPPORTED_EXPRESSION(expression, error, __PRETTY_FUNCTION__, __LINE__)

static inline id __UNSUPPORTED_EXPRESSION(PKExpression *expression, NSError **error, const char *where, int line) {
  if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Unsupported expression '%@' at %s line %d", expression, where, line);
  return nil;
}

static inline id RUNTIME_ERROR(NSError **output, NSError *input) {
  if(output) *output = input;
  return nil;
}

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
    return [self evaluateComparisonExpression:(PKComparisonExpression *)expression modifier:nil object:object error:error];
  }else if(type == [PKBitwiseExpression class]){
    return [self evaluateBitwiseExpression:(PKBitwiseExpression *)expression object:object error:error];
  }else if(type == [PKIdentifierExpression class]){
    return [self evaluateIdentifierExpression:(PKIdentifierExpression *)expression object:object error:error];
  }else if(type == [PKLiteralExpression class]){
    return [self evaluateLiteralExpression:(PKLiteralExpression *)expression object:object error:error];
  }else if(type == [PKModifiedExpression class]){
    return [self evaluateModifiedExpression:(PKModifiedExpression *)expression object:object error:error];
  }else if(type == [PKSetExpression class]){
    return [self evaluateSetExpression:(PKSetExpression *)expression object:object error:error];
  }else{
    return UNSUPPORTED_EXPRESSION(expression, error);
  }
}

#pragma mark - Modified expression

/**
 * Evaluate a logical expression
 */
-(id)evaluateModifiedExpression:(PKModifiedExpression *)expression object:(id)object error:(NSError **)error {
  PKExpression *modified = expression.expression;
  if(object_getClass(modified) == [PKComparisonExpression class]){
    return [self evaluateComparisonExpression:(PKComparisonExpression *)modified modifier:expression.modifier object:object error:error];
  }else{
    return UNSUPPORTED_EXPRESSION(expression, error);
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
      return UNSUPPORTED_EXPRESSION(expression, error);
  }
}

/**
 * Evaluate a logical expression
 */
-(id)evaluateLogicalInfixExpression:(PKLogicalExpression *)expression object:(id)object error:(NSError **)error {
  id left, right;
  
  if([expression.expressions count] != 2)
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"%@ must have exactly two operands", PKLogicalTypeGetName(expression.type)));
  if((left = [self evaluateExpression:[expression.expressions objectAtIndex:0] object:object error:error]) == nil)
    return nil;
  if((right = [self evaluateExpression:[expression.expressions objectAtIndex:1] object:object error:error]) == nil)
    return nil;
  if(![left isKindOfClass:[NSNumber class]])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to %@ must evaluate to boolean", PKLogicalTypeGetName(expression.type)));
  if(![right isKindOfClass:[NSNumber class]])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to %@ must evaluate to boolean", PKLogicalTypeGetName(expression.type)));
  
  switch(expression.type){
    case kPKLogicalAnd:
      return [NSNumber numberWithBool:([left boolValue] && [right boolValue])];
    case kPKLogicalOr:
      return [NSNumber numberWithBool:([left boolValue] || [right boolValue])];
    default:
      return UNSUPPORTED_EXPRESSION(expression, error);
  }
  
}

/**
 * Evaluate a logical expression
 */
-(id)evaluateLogicalUnaryExpression:(PKLogicalExpression *)expression object:(id)object error:(NSError **)error {
  id right;
  
  if([expression.expressions count] != 1)
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"%@ must have exactly two operands", PKLogicalTypeGetName(expression.type)));
  if((right = [self evaluateExpression:[expression.expressions objectAtIndex:0] object:object error:error]) == nil)
    return nil;
  if(![right isKindOfClass:[NSNumber class]])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to %@ must evaluate to boolean", PKLogicalTypeGetName(expression.type)));
  
  switch(expression.type){
    case kPKLogicalNot:
      return [NSNumber numberWithBool:![right boolValue]];
    default:
      return UNSUPPORTED_EXPRESSION(expression, error);
  }
  
}

#pragma mark - Comparison expression

/**
 * Evaluate a comparison expression
 */
-(id)evaluateComparisonExpression:(PKComparisonExpression *)expression object:(id)object error:(NSError **)error {
  return [self evaluateComparisonExpression:expression modifier:nil object:object error:error];
}

/**
 * Evaluate a comparison expression
 */
-(id)evaluateComparisonExpression:(PKComparisonExpression *)expression modifier:(PKExpressionModifier *)modifier object:(id)object error:(NSError **)error {
  switch(expression.type){
    case kPKComparisonEqualTo:
    case kPKComparisonNotEqualTo:
    case kPKComparisonLessThan:
    case kPKComparisonLessThanOrEqualTo:
    case kPKComparisonGreaterThan:
    case kPKComparisonGreaterThanOrEqualTo:
      return [self evaluateRelativeComparisonExpression:expression modifier:modifier object:object error:error];
    case kPKComparisonMatches:
      return [self evaluateMatchingComparisonExpression:expression modifier:modifier object:object error:error];
    case kPKComparisonIn:
      return [self evaluateCollectionComparisonExpression:expression modifier:modifier object:object error:error];
    default:
      return UNSUPPORTED_EXPRESSION(expression, error);
  }
}

/**
 * Evaluate a comparison expression
 */
-(id)evaluateRelativeComparisonExpression:(PKComparisonExpression *)expression modifier:(PKExpressionModifier *)modifier object:(id)object error:(NSError **)error {
  NSComparisonResult result;
  id left, right;
  
  if([expression.operands count] != 2)
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"%@ must have exactly two operands", PKComparisonTypeGetName(expression.type)));
  if((left = [self evaluateExpression:[expression.operands objectAtIndex:0] object:object error:error]) == nil)
    return nil;
  if(![left respondsToSelector:@selector(compare:)])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to %@ must evaulate to an object which implements the selector -compare:", PKComparisonTypeGetName(expression.type)));
  if((right = [self evaluateExpression:[expression.operands objectAtIndex:1] object:object error:error]) == nil)
    return nil;
  if(![right respondsToSelector:@selector(compare:)])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to %@ must evaulate to an object which implements the selector -compare:", PKComparisonTypeGetName(expression.type)));
  
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
      return UNSUPPORTED_EXPRESSION(expression, error);
  }
  
}

/**
 * Evaluate a matching expression
 */
-(id)evaluateMatchingComparisonExpression:(PKComparisonExpression *)expression modifier:(PKExpressionModifier *)modifier object:(id)object error:(NSError **)error {
  NSRegularExpressionOptions options = (modifier != nil) ? modifier.regularExpressionOptions : 0;
  PKPatternExpression *pattern = nil;
  NSRegularExpression *regex = nil;
  NSError *inner = nil;
  id left;
  
  if([expression.operands count] != 2)
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"%@ must have exactly two operands", PKComparisonTypeGetName(expression.type)));
  if((pattern = [expression.operands objectAtIndex:1]) == nil || object_getClass(pattern) != [PKPatternExpression class])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to %@ must be a pattern", PKComparisonTypeGetName(expression.type)));
  if((regex = [NSRegularExpression regularExpressionWithPattern:pattern.pattern options:options error:&inner]) == nil)
    return RUNTIME_ERROR(error, NSERROR_WITH_CAUSE(PKPredicateErrorDomain, PKStatusError, inner, @"Pattern operand to %@ is invalid", PKComparisonTypeGetName(expression.type)));
  if((left = [self evaluateExpression:[expression.operands objectAtIndex:0] object:object error:error]) == nil)
    return nil;
  if(![left isKindOfClass:[NSString class]])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to %@ must be a string", PKComparisonTypeGetName(expression.type)));
  
  switch(expression.type){
    case kPKComparisonMatches:
      return [NSNumber numberWithBool:[regex numberOfMatchesInString:left options:0 range:NSMakeRange(0, [left length])] > 0];
    default:
      return UNSUPPORTED_EXPRESSION(expression, error);
  }
  
}

/**
 * Evaluate a collection expression
 */
-(id)evaluateCollectionComparisonExpression:(PKComparisonExpression *)expression modifier:(PKExpressionModifier *)modifier object:(id)object error:(NSError **)error {
  PKCollectionExpression *collection = nil;
  id left, right;
  
  if([expression.operands count] != 2)
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"%@ must have exactly two operands", PKComparisonTypeGetName(expression.type)));
  if((collection = [expression.operands objectAtIndex:1]) == nil || ![collection isKindOfClass:[PKCollectionExpression class]])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to %@ must be a collection", PKComparisonTypeGetName(expression.type)));
  if((left = [self evaluateExpression:[expression.operands objectAtIndex:0] object:object error:error]) == nil)
    return nil;
  if((right = [self evaluateExpression:[expression.operands objectAtIndex:1] object:object error:error]) == nil)
    return nil;
  if(![right isKindOfClass:[NSSet class]] && ![right isKindOfClass:[NSArray class]] && ![right isKindOfClass:[NSDictionary class]])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to %@ must be a collection", PKComparisonTypeGetName(expression.type)));
  
  switch(expression.type){
    case kPKComparisonIn:
      return [self evaluateSubsetComparisonExpression:expression modifier:modifier left:left right:right object:object error:error];
    default:
      return UNSUPPORTED_EXPRESSION(expression, error);
  }
  
}

/**
 * Evaluate a collection expression
 */
-(id)evaluateSubsetComparisonExpression:(PKComparisonExpression *)expression modifier:(PKExpressionModifier *)modifier left:(id)left right:(id)right object:(id)object error:(NSError **)error {
  if([left isKindOfClass:[NSSet class]] && [right isKindOfClass:[NSSet class]]){
    return [NSNumber numberWithBool:[left isSubsetOfSet:right]];
  }else if([right isKindOfClass:[NSSet class]]){
    return [NSNumber numberWithBool:[right containsObject:left]];
  }else if([right isKindOfClass:[NSArray class]]){
    return [NSNumber numberWithBool:[right containsObject:left]];
  }else if([right isKindOfClass:[NSDictionary class]]){
    return [NSNumber numberWithBool:[right objectForKey:left] != nil];
  }else{
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to %@ must be a collection", PKComparisonTypeGetName(expression.type)));
  }
}

/**
 * Evaluate a bitwise expression
 */
-(id)evaluateBitwiseExpression:(PKBitwiseExpression *)expression object:(id)object error:(NSError **)error {
  switch(expression.type){
    case kPKBitwiseAnd:
    case kPKBitwiseOr:
    case kPKBitwiseExclusiveOr:
      return [self evaluateBitwiseInfixExpression:expression object:object error:error];
    case kPKBitwiseNot:
      return [self evaluateBitwiseUnaryExpression:expression object:object error:error];
    default:
      return UNSUPPORTED_EXPRESSION(expression, error);
  }
}

/**
 * Evaluate a bitwise expression
 */
-(id)evaluateBitwiseInfixExpression:(PKBitwiseExpression *)expression object:(id)object error:(NSError **)error {
  id left, right;
  
  if([expression.operands count] != 2)
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"%@ must have exactly two operands", PKBitwiseTypeGetName(expression.type)));
  if((left = [self evaluateExpression:[expression.operands objectAtIndex:0] object:object error:error]) == nil)
    return nil;
  if((right = [self evaluateExpression:[expression.operands objectAtIndex:1] object:object error:error]) == nil)
    return nil;
  if(![left isKindOfClass:[NSNumber class]])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to %@ must evaluate to integer", PKBitwiseTypeGetName(expression.type)));
  if(![right isKindOfClass:[NSNumber class]])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Right operand to %@ must evaluate to integer", PKBitwiseTypeGetName(expression.type)));
  
  switch(expression.type){
    case kPKBitwiseAnd:
      return [NSNumber numberWithLong:([left longValue] & [right longValue])];
    case kPKBitwiseOr:
      return [NSNumber numberWithLong:([left longValue] | [right longValue])];
    case kPKBitwiseExclusiveOr:
      return [NSNumber numberWithLong:([left longValue] ^ [right longValue])];
    default:
      return UNSUPPORTED_EXPRESSION(expression, error);
  }
  
}

/**
 * Evaluate a bitwise expression
 */
-(id)evaluateBitwiseUnaryExpression:(PKBitwiseExpression *)expression object:(id)object error:(NSError **)error {
  id right;
  
  if([expression.operands count] != 1)
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"%@ must have exactly two operands", PKBitwiseTypeGetName(expression.type)));
  if((right = [self evaluateExpression:[expression.operands objectAtIndex:0] object:object error:error]) == nil)
    return nil;
  if(![right isKindOfClass:[NSNumber class]])
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Left operand to %@ must evaluate to integer", PKBitwiseTypeGetName(expression.type)));
  
  switch(expression.type){
    case kPKBitwiseNot:
      return [NSNumber numberWithLong:~[right longValue]];
    default:
      return UNSUPPORTED_EXPRESSION(expression, error);
  }
  
}

/**
 * Evaluate a set expression
 */
-(id)evaluateSetExpression:(PKSetExpression *)expression object:(id)object error:(NSError **)error {
  NSMutableSet *set = [NSMutableSet set];
  
  for(PKExpression *parameter in [expression.parameters expressions]){
    id result;
    if((result = [self evaluateExpression:parameter object:object error:error]) != nil){
      [set addObject:result];
    }else{
      return nil;
    }
  }
  
  return set;
}

/**
 * Evaluate an identifier expression
 */
-(id)evaluateIdentifierExpression:(PKIdentifierExpression *)expression object:(id)object error:(NSError **)error {
  id value;
  
  if(object == nil){
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"Runtime context object is nil; cannot evaluate variable '%@'", expression.identifier));
  }
  
  @try {
    value = [object valueForKey:expression.identifier];
  }@catch(NSException *exception){
    return RUNTIME_ERROR(error, NSERROR(PKPredicateErrorDomain, PKStatusError, @"No such property '%@' of %@", expression.identifier, [object class]));
  }
  
  return (value != nil) ? value : [NSNull null];
}

/**
 * Evaluate a literal expression
 */
-(id)evaluateLiteralExpression:(PKLiteralExpression *)expression object:(id)object error:(NSError **)error {
  return expression.value;
}

@end

