// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKCollectionExpression.h"

@implementation PKCollectionExpression

@end

@implementation PKSetExpression

@synthesize parameters = _parameters;

+(PKSetExpression *)setExpressionWithSpan:(PKSpan *)span parameters:(PKParameters *)parameters {
  return [[[self alloc] initWithSpan:span parameters:parameters] autorelease];
}

-(void)dealloc {
  [_parameters release];
  [super dealloc];
}

-(id)initWithSpan:(PKSpan *)span parameters:(PKParameters *)parameters {
  if((self = [super initWithSpan:span]) != nil){
    _parameters = [parameters retain];
  }
  return self;
}

-(NSString *)description {
  return [NSString stringWithFormat:@"{ %@ }", [_parameters description]];
}

@end

