// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKPatternExpression.h"

@implementation PKPatternExpression

@synthesize pattern = _pattern;

+(PKPatternExpression *)patternExpressionWithSpan:(PKSpan *)span pattern:(NSString *)pattern {
  return [[[self alloc] initWithSpan:span pattern:pattern] autorelease];
}

-(void)dealloc {
  [_pattern release];
  [super dealloc];
}

-(id)initWithSpan:(PKSpan *)span pattern:(NSString *)pattern {
  if((self = [super initWithSpan:span]) != nil){
    _pattern = [pattern retain];
  }
  return self;
}

-(NSString *)description {
  return [NSString stringWithFormat:@"/%@/", _pattern];
}

@end

