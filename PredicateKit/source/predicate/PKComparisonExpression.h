// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"

typedef enum {
  kPKComparisonEqualTo,
  kPKComparisonNotEqualTo,
  kPKComparisonLessThan,
  kPKComparisonLessThanOrEqualTo,
  kPKComparisonGreaterThan,
  kPKComparisonGreaterThanOrEqualTo,
  kPKComparisonMatches
} PKComparisonType;

/**
 * A compound expression.
 */
@interface PKComparisonExpression : PKExpression

-(id)initWithType:(PKComparisonType)type operands:(NSArray *)operands;

@property (readonly) PKComparisonType type;
@property (readonly) NSArray        * operands;

@end

