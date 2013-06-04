// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKVariableStack.h"

@implementation PKVariableStack

/**
 * Create an evaluator
 */
+(PKVariableStack *)stack {
  return [[[self alloc] init] autorelease];
}

/**
 * Clean up
 */
-(void)dealloc {
  [_stack release];
  [super dealloc];
}

/**
 * Initialize
 */
-(id)init {
  if((self = [super init]) != nil){
    _stack = [[NSMutableArray alloc] init];
  }
  return self;
}

/**
 * Obtain a value for the provided key by searching the entire stack
 */
-(id)valueForKey:(NSString *)key {
  return [self valueForKey:key maximumDepth:-1];
}

/**
 * Obtain a value for the provided key by searching, at most, @p maximumDepth frames
 * in the stack. Provide a maximum depth of <= 0 to search the entire stack.
 */
-(id)valueForKey:(NSString *)key maximumDepth:(NSInteger)maximumDepth {
  NSInteger depth = 0;
  id value;
  for(NSInteger i = [_stack count] - 1; i >= 0 && (maximumDepth < 1 || depth < maximumDepth); i--, depth++){
    NSDictionary *frame = [_stack objectAtIndex:i];
    if((value = [frame objectForKey:value]) != nil) return value;
  }
  return nil;
}

/**
 * Set the provided value in the top frame of the stack. If the Stack does not yet have
 * any frames, one is created.
 */
-(void)setValue:(id)value forKey:(NSString *)key {
  [self.currentFrame setObject:value forKey:key];
}

/**
 * Push a frame onto the top of the stack.
 */
-(void)pushFrame:(NSDictionary *)frame {
  NSMutableDictionary *mutable = [frame mutableCopy];
  [_stack addObject:mutable];
  [mutable release];
}

/**
 * Push a frame containing a single object onto the stack.
 */
-(void)pushFrameWithObject:(id)object forKey:(NSString *)key {
  [self pushEmptyFrame];
  [self setValue:object forKey:key];
}

/**
 * Push an empty frame onto the top of the stack.
 */
-(void)pushEmptyFrame {
  NSMutableDictionary *mutable = [NSMutableDictionary dictionary];
  [_stack addObject:mutable];
  [mutable release];
}

/**
 * Pop the top frame off the stack.
 */
-(void)popFrame {
  if([_stack count] > 0) [_stack removeLastObject];
}

/**
 * Obtain the current (top) frame on the stack.
 */
-(NSMutableDictionary *)currentFrame {
  if([_stack count] < 1) [self pushEmptyFrame];
  return [_stack lastObject];
}

@end

