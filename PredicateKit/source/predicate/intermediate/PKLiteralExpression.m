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

-(NSString *)description {
  if([_value isKindOfClass:[NSString class]]){
    return [NSString stringWithFormat:@"\"%@\"", _value];
  }else{
    return [_value description];
  }
}

@end

