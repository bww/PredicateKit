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

+(PKLiteralExpression *)literalExpressionWithSpan:(PKSpan *)span value:(id)value {
  return [[[self alloc] initWithSpan:span value:value] autorelease];
}

-(void)dealloc {
  [_value release];
  [super dealloc];
}

-(id)initWithSpan:(PKSpan *)span value:(id)value {
  if((self = [super initWithSpan:span]) != nil){
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

