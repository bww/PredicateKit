// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpressionModifier.h"

@implementation PKExpressionModifier

@synthesize modifier = _modifier;

+(PKExpressionModifier *)expressionModifierWithFlags:(const char *)flags {
  return [[[self alloc] initWithFlags:flags] autorelease];
}

-(void)dealloc {
  [super dealloc];
}

-(id)initWithFlags:(const char *)flags {
  if((self = [super init]) != nil){
    _modifier = kPKModifierNone;
    
    if(flags != NULL){
      size_t length = strlen(flags);
      for(int i = 0; i < length; i++){
        switch(flags[i]){
          case 'c': _modifier |= kPKModifierCaseInsensitive;        break;
          case 'd': _modifier |= kPKModifierDiacriticInsensitive;   break;
          case 'g': _modifier |= kPKModifierGlobal;                 break;
        }
      }
    }
    
  }
  return self;
}

-(NSString *)description {
  return @"MOD";
}

@end

