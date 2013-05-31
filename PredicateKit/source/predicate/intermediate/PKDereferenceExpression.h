// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"

/**
 * A dereference expression
 */
@interface PKDereferenceExpression : PKExpression

+(PKDereferenceExpression *)dereferenceExpressionWithSpan:(PKSpan *)span identifiers:(NSArray *)identifiers;

-(id)initWithSpan:(PKSpan *)span identifiers:(NSArray *)identifiers;

@property (readonly) NSArray * identifiers;

@end

