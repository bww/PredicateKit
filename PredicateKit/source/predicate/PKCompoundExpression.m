// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKCompoundExpression.h"

@implementation PKCompoundExpression

@synthesize type = _type;
@synthesize expressions = _expressions;

+(PKCompoundExpression *)compoundExpressionWithType:(PKCompoundType)type expressions:(NSArray *)expressions {
  return [[[self alloc] initWithType:type expressions:expressions] autorelease];
}

-(void)dealloc {
  [_expressions release];
  [super dealloc];
}

-(id)initWithType:(PKCompoundType)type expressions:(NSArray *)expressions {
  if((self = [super init]) != nil){
    _type = type;
    _expressions = [expressions retain];
  }
  return self;
}

-(NSString *)description {
  NSMutableString *string = [NSMutableString string];
  
  if(_expressions != nil){
    if([_expressions count] > 1) [string appendString:[[_expressions objectAtIndex:0] description]];
    for(int i = 1; i < [_expressions count]; i++){
      switch(_type){
        case kPKCompoundAnd:  [string appendString:@" && "];
        case kPKCompoundOr:   [string appendString:@" || "];
        case kPKCompoundNot:  [string appendString:@" !"];
      }
      [string appendString:[[_expressions objectAtIndex:i] description]];
    }
  }
  
  return string;
}

@end

