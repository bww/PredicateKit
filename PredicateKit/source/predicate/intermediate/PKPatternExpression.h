// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"

/**
 * A pattern expression.
 */
@interface PKPatternExpression : PKExpression

+(PKPatternExpression *)patternExpressionWithPattern:(NSString *)pattern;

-(id)initWithPattern:(NSString *)pattern;

@property (readonly) NSString * pattern;

@end

