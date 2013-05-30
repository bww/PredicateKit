// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"
#import "PKExpressionModifier.h"

/**
 * A modified expression.
 */
@interface PKModifiedExpression : PKExpression

+(PKModifiedExpression *)modifiedExpressionWithExpression:(PKExpression *)expression modifier:(PKExpressionModifier *)modifier;

-(id)initWithExpression:(PKExpression *)expression modifier:(PKExpressionModifier *)modifier;

@property (readonly) PKExpression         * expression;
@property (readonly) PKExpressionModifier * modifier;

@end

