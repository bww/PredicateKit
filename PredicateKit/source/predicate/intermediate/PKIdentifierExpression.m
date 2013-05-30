// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKIdentifierExpression.h"

@implementation PKIdentifierExpression

@synthesize identifier = _identifier;

+(PKIdentifierExpression *)identifierExpressionWithIdentifier:(NSString *)identifier {
  return [[[self alloc] initWithIdentifier:identifier] autorelease];
}

-(void)dealloc {
  [_identifier release];
  [super dealloc];
}

-(id)initWithIdentifier:(NSString *)identifier {
  if((self = [super init]) != nil){
    _identifier = [identifier retain];
  }
  return self;
}

-(NSString *)description {
  return _identifier;
}

@end

