// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"

typedef enum {
  kPKCompoundAnd,
  kPKCompoundOr,
  kPKCompoundNot
} PKCompoundType;

/**
 * A compound expression.
 */
@interface PKCompoundExpression : PKExpression

-(id)initWithType:(PKCompoundType)type expressions:(NSArray *)expressions;

@property (readonly) PKCompoundType type;
@property (readonly) NSArray      * expressions;

@end

