// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKLogicalExpression.h"

static NSString * const kPKLogicalTypeNames[] = {
  @"&& (logical AND)", @"|| (logical OR)", @"! (logical NOT)", NULL
};

NSString * PKLogicalTypeGetName(PKLogicalType type) {
  return (type >= kPKLogicalAnd && type <= kPKLogicalNot) ? kPKLogicalTypeNames[type] : nil;
}

@implementation PKLogicalExpression

@synthesize type = _type;
@synthesize expressions = _expressions;

+(PKLogicalExpression *)compoundExpressionWithSpan:(PKSpan *)span type:(PKLogicalType)type expressions:(NSArray *)expressions {
  return [[[self alloc] initWithSpan:span type:type expressions:expressions] autorelease];
}

-(void)dealloc {
  [_expressions release];
  [super dealloc];
}

-(id)initWithSpan:(PKSpan *)span type:(PKLogicalType)type expressions:(NSArray *)expressions {
  if((self = [super initWithSpan:span]) != nil){
    _type = type;
    _expressions = [expressions retain];
  }
  return self;
}

-(NSString *)description {
  NSMutableString *string = [NSMutableString string];
  
  if(_expressions != nil){
    [string appendString:@"("];
    
    int i = 0;
    if([_expressions count] > 1) [string appendString:[[_expressions objectAtIndex:i++] description]];
    for( ; i < [_expressions count]; i++){
      switch(_type){
        case kPKLogicalAnd: [string appendString:@" && "];  break;
        case kPKLogicalOr:  [string appendString:@" || "];  break;
        case kPKLogicalNot: [string appendString:@"!"];     break;
      }
      [string appendString:[[_expressions objectAtIndex:i] description]];
    }
    
    [string appendString:@")"];
  }
  
  return string;
}

@end

