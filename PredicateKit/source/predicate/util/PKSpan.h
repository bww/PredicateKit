// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

@class PKExpression;

/**
 * A text span
 */
@interface PKSpan : NSObject

+(PKSpan *)spanWithDocument:(NSURL *)document source:(NSString *)source range:(NSRange)range;

-(id)initWithDocument:(NSURL *)document source:(NSString *)source range:(NSRange)range;

@property (readonly) NSURL    * document;
@property (readonly) NSString * source;
@property (readonly) NSRange    range;

@end

