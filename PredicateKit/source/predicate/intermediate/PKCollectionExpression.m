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

+(PKSetExpression *)setExpressionWithParameters:(PKParameters *)parameters {
  return [[[self alloc] initWithParameters:parameters] autorelease];
}

-(void)dealloc {
  [_parameters release];
  [super dealloc];
}

-(id)initWithParameters:(PKParameters *)parameters {
  if((self = [super init]) != nil){
    _parameters = [parameters retain];
  }
  return self;
}

-(NSString *)description {
  return [NSString stringWithFormat:@"{ %@ }", [_parameters description]];
}

@end

