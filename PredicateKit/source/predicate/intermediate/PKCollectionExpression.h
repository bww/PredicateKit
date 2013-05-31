// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"
#import "PKParameters.h"

/**
 * Abstract collection expression
 */
@interface PKCollectionExpression : PKExpression

@end

/**
 * A set expression.
 */
@interface PKSetExpression : PKCollectionExpression

+(PKSetExpression *)setExpressionWithSpan:(PKSpan *)span parameters:(PKParameters *)parameters;

-(id)initWithSpan:(PKSpan *)span parameters:(PKParameters *)parameters;

@property (readonly) PKParameters * parameters;

@end

