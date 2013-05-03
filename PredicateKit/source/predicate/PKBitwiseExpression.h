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

/**
 * A bitwise expression.
 */
@interface PKBitwiseExpression : PKExpression

+(PKBitwiseExpression *)bitwiseExpressionWithType:(PKBitwiseType)type operands:(NSArray *)operands;

-(id)initWithType:(PKBitwiseType)type operands:(NSArray *)operands;

@property (readonly) PKBitwiseType  type;
@property (readonly) NSArray      * operands;

@end

