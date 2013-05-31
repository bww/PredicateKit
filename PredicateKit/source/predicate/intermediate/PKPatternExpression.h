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

+(PKPatternExpression *)patternExpressionWithSpan:(PKSpan *)span pattern:(NSString *)pattern;

-(id)initWithSpan:(PKSpan *)span pattern:(NSString *)pattern;

@property (readonly) NSString * pattern;

@end

