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

+(PKIdentifierExpression *)identifierExpressionWithSpan:(PKSpan *)span identifier:(NSString *)identifier {
  return [[[self alloc] initWithSpan:span identifier:identifier] autorelease];
}

-(void)dealloc {
  [_identifier release];
  [super dealloc];
}

-(id)initWithSpan:(PKSpan *)span identifier:(NSString *)identifier {
  if((self = [super initWithSpan:span]) != nil){
    _identifier = [identifier retain];
  }
  return self;
}

-(NSString *)description {
  return _identifier;
}

@end

