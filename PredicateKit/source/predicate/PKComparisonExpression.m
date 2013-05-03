// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKComparisonExpression.h"

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
    if([_operands count] > 1) [string appendString:[[_operands objectAtIndex:0] description]];
    for(int i = 1; i < [_operands count]; i++){
      switch(_type){
        case kPKComparisonEqualTo:              [string appendString:@" == "];
        case kPKComparisonNotEqualTo:           [string appendString:@" != "];
        case kPKComparisonLessThan:             [string appendString:@" < "];
        case kPKComparisonLessThanOrEqualTo:    [string appendString:@" <= "];
        case kPKComparisonGreaterThan:          [string appendString:@" > "];
        case kPKComparisonGreaterThanOrEqualTo: [string appendString:@" >= "];
        case kPKComparisonMatches:              [string appendString:@" =~ "];
        case kPKComparisonIn:                   [string appendString:@" in "];
      }
      [string appendString:[[_operands objectAtIndex:i] description]];
    }
  }
  
  return string;
}

@end

