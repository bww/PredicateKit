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

+(PKPatternExpression *)patternExpressionWithPattern:(NSString *)pattern {
  return [[[self alloc] initWithPattern:pattern] autorelease];
}

-(void)dealloc {
  [_pattern release];
  [super dealloc];
}

-(id)initWithPattern:(NSString *)pattern {
  if((self = [super init]) != nil){
    _pattern = [pattern retain];
  }
  return self;
}

-(NSString *)description {
  return [NSString stringWithFormat:@"/%@/", _pattern];
}

@end

