// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"

/**
 * An identifier expression.
 */
@interface PKIdentifierExpression : PKExpression

+(PKIdentifierExpression *)identifierExpressionWithSpan:(PKSpan *)span identifier:(NSString *)identifier;

-(id)initWithSpan:(PKSpan *)span identifier:(NSString *)identifier;

@property (readonly) NSString * identifier;

@end

