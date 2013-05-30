// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"

/**
 * A parameter list (a list of expressions)
 */
@interface PKParameters : PKExpression

+(PKParameters *)parametersWithExpressions:(NSArray *)expressions;

-(id)initWithWithExpressions:(NSArray *)expressions;

@property (readonly) NSArray * expressions;

@end

/**
 * A mutable parameter list
 */
@interface PKMutableParameters : PKParameters

+(PKMutableParameters *)mutableParameters;
+(PKMutableParameters *)mutableParametersWithExpression:(PKExpression *)expression;

-(PKMutableParameters *)addExpression:(PKExpression *)expression;

@end
