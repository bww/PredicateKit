// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKComparisonExpression.h"

@implementation PKComparisonExpression

@synthesize type = _type;
@synthesize operands = _operands;

-(void)dealloc {
  [_operands release];
  [super dealloc];
}

-(id)initWithType:(PKCompoundType)type operands:(NSArray *)operands {
  if((self = [super init]) != nil){
    _type = type;
    _operands = [operands retain];
  }
  return self;
}

@end

