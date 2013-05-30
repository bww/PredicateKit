// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKParameters.h"

@implementation PKParameters

@synthesize expressions = _expressions;

+(PKParameters *)parametersWithExpressions:(NSArray *)expressions {
  return [[[self alloc] initWithWithExpressions:expressions] autorelease];
}

-(void)dealloc {
  [_expressions release];
  [super dealloc];
}

-(id)initWithWithExpressions:(NSArray *)expressions {
  if((self = [super init]) != nil){
    _expressions = [expressions retain];
  }
  return self;
}

-(NSString *)description {
  NSMutableString *string = [NSMutableString string];
  
  if(_expressions != nil){
    for(int i = 0; i < [_expressions count]; i++){
      if(i > 0) [string appendString:@", "];
      [string appendString:[[_expressions objectAtIndex:i] description]];
    }
  }
  
  return string;
}

@end

@implementation PKMutableParameters

+(PKMutableParameters *)mutableParameters {
  return [[[self alloc] init] autorelease];
}

+(PKMutableParameters *)mutableParametersWithExpression:(PKExpression *)expression {
  PKMutableParameters *params = [self mutableParameters];
  [params addExpression:expression];
  return params;
}

-(id)init {
  return [self initWithWithExpressions:[NSMutableArray array]];
}

-(PKMutableParameters *)addExpression:(PKExpression *)expression {
  [(NSMutableArray *)self.expressions addObject:expression];
  return self;
}

@end

