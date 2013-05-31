// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"

typedef enum {
  kPKBitwiseAnd,
  kPKBitwiseOr,
  kPKBitwiseExclusiveOr,
  kPKBitwiseNot
} PKBitwiseType;

NSString * PKBitwiseTypeGetName(PKBitwiseType type);

/**
 * A bitwise expression.
 */
@interface PKBitwiseExpression : PKExpression

+(PKBitwiseExpression *)bitwiseExpressionWithSpan:(PKSpan *)span type:(PKBitwiseType)type operands:(NSArray *)operands;

-(id)initWithSpan:(PKSpan *)span type:(PKBitwiseType)type operands:(NSArray *)operands;

@property (readonly) PKBitwiseType  type;
@property (readonly) NSArray      * operands;

@end

