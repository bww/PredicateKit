// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKExpression.h"

typedef enum {
  kPKModifierNone                 = 0,
  kPKModifierCaseInsensitive      = 1 << 0,
  kPKModifierDiacriticInsensitive = 1 << 1,
  kPKModifierGlobal               = 1 << 2
} PKModifierFlags;

typedef unsigned int PKModifier;

/**
 * Expression modifiers
 */
@interface PKExpressionModifier : PKExpression

+(PKExpressionModifier *)expressionModifierWithFlags:(const char *)flags;

-(id)initWithFlags:(const char *)flags;

@property (readonly) PKModifier modifier;

@end

