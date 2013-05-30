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
  kPKComparisonMatches,
  kPKComparisonIn
} PKComparisonType;

NSString * PKComparisonTypeGetName(PKComparisonType type);

/**
 * A comparison expression.
 */
@interface PKComparisonExpression : PKExpression

+(id)comparisonExpressionWithType:(PKComparisonType)type operands:(NSArray *)operands;

-(id)initWithType:(PKComparisonType)type operands:(NSArray *)operands;

@property (readonly) PKComparisonType type;
@property (readonly) NSArray        * operands;

@end

