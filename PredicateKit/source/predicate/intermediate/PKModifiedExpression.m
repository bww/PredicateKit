// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKModifiedExpression.h"

@implementation PKModifiedExpression

@synthesize expression = _expression;
@synthesize modifier = _modifier;

+(PKModifiedExpression *)modifiedExpressionWithExpression:(PKExpression *)expression modifier:(PKExpressionModifier *)modifier {
  return [[[self alloc] initWithExpression:expression modifier:modifier] autorelease];
}

-(void)dealloc {
  [_expression release];
  [_modifier release];
  [super dealloc];
}

-(id)initWithExpression:(PKExpression *)expression modifier:(PKExpressionModifier *)modifier {
  if((self = [super init]) != nil){
    _expression = [expression retain];
    _modifier = [modifier retain];
  }
  return self;
}

-(NSString *)description {
  return [_expression desceription];
}

@end

