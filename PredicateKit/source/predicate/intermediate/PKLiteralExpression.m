// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKLiteralExpression.h"

@implementation PKLiteralExpression

@synthesize value = _value;

+(PKLiteralExpression *)literalExpressionWithValue:(id)value {
  return [[[self alloc] initWithValue:value] autorelease];
}

-(void)dealloc {
  [_value release];
  [super dealloc];
}

-(id)initWithValue:(id)value {
  if((self = [super init]) != nil){
    _value = [value retain];
  }
  return self;
}

-(id)evaluateWithObject:(id)object {
  return nil;
}

-(NSString *)description {
  return [_value description];
}

@end

