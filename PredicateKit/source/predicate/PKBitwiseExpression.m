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

-(id)evaluateWithObject:(id)object {
  return nil;
}

-(NSString *)description {
  NSMutableString *string = [NSMutableString string];
  
  if(_operands != nil){
    [string appendString:@"("];
    
    int i = 0;
    if([_operands count] > 1) [string appendString:[[_operands objectAtIndex:i++] description]];
    for( ; i < [_operands count]; i++){
      switch(_type){
        case kPKBitwiseAnd:         [string appendString:@" & "]; break;
        case kPKBitwiseOr:          [string appendString:@" | "]; break;
        case kPKBitwiseExclusiveOr: [string appendString:@" ^ "]; break;
        case kPKBitwiseNot:         [string appendString:@"~"];  break;
      }
      [string appendString:[[_operands objectAtIndex:i] description]];
    }
    
    [string appendString:@")"];
  }
  
  return string;
}

@end

