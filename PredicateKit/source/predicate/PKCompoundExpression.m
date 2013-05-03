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

+(PKCompoundExpression *)compoundExpressionWithType:(PKCompoundType)type expressions:(NSArray *)expressions {
  return [[[self alloc] initWithType:type expressions:expressions] autorelease];
}

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

-(id)evaluateWithObject:(id)object {
  return nil;
}

-(NSString *)description {
  NSMutableString *string = [NSMutableString string];
  
  if(_expressions != nil){
    [string appendString:@"("];
    
    int i = 0;
    if([_expressions count] > 1) [string appendString:[[_expressions objectAtIndex:i++] description]];
    for( ; i < [_expressions count]; i++){
      switch(_type){
        case kPKCompoundAnd:  [string appendString:@" && "];  break;
        case kPKCompoundOr:   [string appendString:@" || "];  break;
        case kPKCompoundNot:  [string appendString:@"!"];    break;
      }
      [string appendString:[[_expressions objectAtIndex:i] description]];
    }
    
    [string appendString:@")"];
  }
  
  return string;
}

@end

