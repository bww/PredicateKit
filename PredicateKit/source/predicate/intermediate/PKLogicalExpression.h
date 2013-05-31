// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"

typedef enum {
  kPKLogicalAnd,
  kPKLogicalOr,
  kPKLogicalNot
} PKLogicalType;

NSString * PKLogicalTypeGetName(PKLogicalType type);

/**
 * A logical expression.
 */
@interface PKLogicalExpression : PKExpression

+(PKLogicalExpression *)compoundExpressionWithSpan:(PKSpan *)span type:(PKLogicalType)type expressions:(NSArray *)expressions;

-(id)initWithSpan:(PKSpan *)span type:(PKLogicalType)type expressions:(NSArray *)expressions;

@property (readonly) PKLogicalType  type;
@property (readonly) NSArray      * expressions;

@end

