// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKSpan.h"

/**
 * An expression.
 */
@interface PKExpression : NSObject

-(id)initWithSpan:(PKSpan *)span;

@property (readonly) PKSpan * span;

@end

