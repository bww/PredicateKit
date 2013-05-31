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

+(PKModifiedExpression *)modifiedExpressionWithSpan:(PKSpan *)span expression:(PKExpression *)expression modifier:(PKExpressionModifier *)modifier {
  return [[[self alloc] initWithSpan:span expression:expression modifier:modifier] autorelease];
}

-(void)dealloc {
  [_expression release];
  [_modifier release];
  [super dealloc];
}

-(id)initWithSpan:(PKSpan *)span expression:(PKExpression *)expression modifier:(PKExpressionModifier *)modifier {
  if((self = [super initWithSpan:span]) != nil){
    _expression = [expression retain];
    _modifier = [modifier retain];
  }
  return self;
}

-(NSString *)description {
  return [_expression description];
}

@end

