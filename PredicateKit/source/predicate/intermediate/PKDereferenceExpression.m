// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKDereferenceExpression.h"

@implementation PKDereferenceExpression

@synthesize identifiers = _identifiers;

+(PKDereferenceExpression *)dereferenceExpressionWithSpan:(PKSpan *)span identifiers:(NSArray *)identifiers {
  return [[[self alloc] initWithSpan:span identifiers:identifiers] autorelease];
}

-(void)dealloc {
  [_identifiers release];
  [super dealloc];
}

-(id)initWithSpan:(PKSpan *)span identifiers:(NSArray *)identifiers {
  if((self = [super initWithSpan:span]) != nil){
    _identifiers = [identifiers retain];
  }
  return self;
}

-(NSString *)description {
  NSMutableString *string = [NSMutableString string];
  
  for(int i = 0; i < [_identifiers count]; i++){
    if(i > 0) [string appendString:@"."];
    [string appendString:[[_identifiers objectAtIndex:i] description]];
  }
  
  return string;
}

@end

