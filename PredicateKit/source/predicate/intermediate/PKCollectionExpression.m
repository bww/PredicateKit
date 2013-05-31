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

+(PKSetExpression *)setExpressionWithSpan:(PKSpan *)span parameters:(NSArray *)parameters {
  return [[[self alloc] initWithSpan:span parameters:parameters] autorelease];
}

-(void)dealloc {
  [_parameters release];
  [super dealloc];
}

-(id)initWithSpan:(PKSpan *)span parameters:(NSArray *)parameters {
  if((self = [super initWithSpan:span]) != nil){
    _parameters = [parameters retain];
  }
  return self;
}

-(NSString *)description {
  NSMutableString *string = [NSMutableString string];
  [string appendString:@"{ "];
  
  for(int i = 0; i < [_parameters count]; i++){
    if(i > 0) [string appendString:@", "];
    [string appendString:[[_parameters objectAtIndex:i] description]];
  }
  
  [string appendString:@" }"];
  return string;
}

@end

