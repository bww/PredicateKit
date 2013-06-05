// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

@class PKExpression;

/**
 * A stack of variable frames
 */
@interface PKVariableStack : NSObject <NSCopying> {
  
  NSMutableArray  * _stack;
  
}

+(PKVariableStack *)stack;
+(PKVariableStack *)stackWithVariables:(PKVariableStack *)stack;

-(id)valueForKey:(NSString *)key;
-(id)valueForKey:(NSString *)key maximumDepth:(NSInteger)maximumDepth;
-(void)setValue:(id)value forKey:(NSString *)key;

-(void)pushFrame:(NSDictionary *)frame;
-(void)pushFrameWithObject:(id)object forKey:(NSString *)key;
-(void)pushEmptyFrame;
-(void)popFrame;

-(NSMutableDictionary *)currentFrame;

@property (readonly, getter=isEmpty)  BOOL        empty;
@property (readonly)                  NSUInteger  frames;

@end

