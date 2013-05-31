// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"

@implementation PKExpression

@synthesize span = _span;

-(void)dealloc {
  [_span release];
  [super dealloc];
}

-(id)initWithSpan:(PKSpan *)span {
  if((self = [super init]) != nil){
    _span = [span retain];
  }
  return self;
}

@end

