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

+(PKExpressionModifier *)expressionModifierWithSpan:(PKSpan *)span flags:(const char *)flags {
  return [[[self alloc] initWithSpan:span flags:flags] autorelease];
}

-(void)dealloc {
  [super dealloc];
}

-(id)initWithSpan:(PKSpan *)span flags:(const char *)flags {
  if((self = [super initWithSpan:span]) != nil){
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

-(NSRegularExpressionOptions)regularExpressionOptions {
  NSRegularExpressionOptions options = 0;
  if((_modifier & kPKModifierCaseInsensitive) == kPKModifierCaseInsensitive) options |= NSRegularExpressionCaseInsensitive;
  return options;
}

-(NSString *)description {
  return @"MOD";
}

@end

