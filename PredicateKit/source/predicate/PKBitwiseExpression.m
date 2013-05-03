// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKBitwiseExpression.h"

@implementation PKBitwiseExpression

@synthesize type = _type;
@synthesize operands = _operands;

+(PKBitwiseExpression *)bitwiseExpressionWithType:(PKBitwiseType)type operands:(NSArray *)operands {
  return [[[self alloc] initWithType:type operands:operands] autorelease];
}

-(void)dealloc {
  [_operands release];
  [super dealloc];
}

-(id)initWithType:(PKBitwiseType)type operands:(NSArray *)operands {
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
        case kPKBitwiseAnd:         [string appendString:@" & "];
        case kPKBitwiseOr:          [string appendString:@" | "];
        case kPKBitwiseExclusiveOr: [string appendString:@" ^ "];
        case kPKBitwiseNot:         [string appendString:@" ~"];
      }
      [string appendString:[[_operands objectAtIndex:i] description]];
    }
  }
  
  return string;
}

@end

