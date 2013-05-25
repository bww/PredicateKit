// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"

/**
 * A literal expression.
 */
@interface PKLiteralExpression : PKExpression

+(PKLiteralExpression *)literalExpressionWithValue:(id)value;

-(id)initWithValue:(id)value;

@property (readonly) id value;

@end
