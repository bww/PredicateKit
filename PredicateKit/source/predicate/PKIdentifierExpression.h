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

+(PKIdentifierExpression *)identifierExpressionWithIdentifier:(NSString *)identifier;

-(id)initWithIdentifier:(NSString *)identifier;

@property (readonly) NSString * identifier;

@end

