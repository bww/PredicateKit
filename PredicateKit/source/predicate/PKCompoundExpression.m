// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKCompoundExpression.h"

@implementation PKCompoundExpression

@synthesize type = _type;
@synthesize expressions = _expressions;

-(void)dealloc {
  [_expressions release];
  [super dealloc];
}

-(id)initWithType:(PKCompoundType)type expressions:(NSArray *)expressions {
  if((self = [super init]) != nil){
    _type = type;
    _expressions = [expressions retain];
  }
  return self;
}

@end

