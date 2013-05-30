// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKComparisonExpression.h"

static NSString * const kPKComparisonTypeNames[] = {
  @"== (equal to)", @"!= (not equal to)", @"< (less than)", @"<= (less than or equal to)", @"> (greater than)", @">= (greater than or equal to)", @"=~ (matches)", @"'in' (subset)", NULL
};

NSString * PKComparisonTypeGetName(PKComparisonType type) {
  return (type >= kPKComparisonEqualTo && type <= kPKComparisonIn) ? kPKComparisonTypeNames[type] : nil;
}

@implementation PKComparisonExpression

@synthesize type = _type;
@synthesize operands = _operands;

+(PKComparisonExpression *)comparisonExpressionWithType:(PKComparisonType)type operands:(NSArray *)operands {
  return [[[self alloc] initWithType:type operands:operands] autorelease];
}

-(void)dealloc {
  [_operands release];
  [super dealloc];
}

-(id)initWithType:(PKComparisonType)type operands:(NSArray *)operands {
  if((self = [super init]) != nil){
    _type = type;
    _operands = [operands retain];
  }
  return self;
}

-(NSString *)description {
  NSMutableString *string = [NSMutableString string];
  
  if(_operands != nil){
    [string appendString:@"("];
    
    int i = 0;
    if([_operands count] > 1) [string appendString:[[_operands objectAtIndex:i++] description]];
    for( ; i < [_operands count]; i++){
      switch(_type){
        case kPKComparisonEqualTo:              [string appendString:@" == "];  break;
        case kPKComparisonNotEqualTo:           [string appendString:@" != "];  break;
        case kPKComparisonLessThan:             [string appendString:@" < "];   break;
        case kPKComparisonLessThanOrEqualTo:    [string appendString:@" <= "];  break;
        case kPKComparisonGreaterThan:          [string appendString:@" > "];   break;
        case kPKComparisonGreaterThanOrEqualTo: [string appendString:@" >= "];  break;
        case kPKComparisonMatches:              [string appendString:@" =~ "];  break;
        case kPKComparisonIn:                   [string appendString:@" in "];  break;
      }
      [string appendString:[[_operands objectAtIndex:i] description]];
    }
    
    [string appendString:@")"];
  }
  
  return string;
}

@end

