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

enum {
  kPKSpanFormatterOptionNone                = 0,
  kPKSpanFormatterOptionUseANSIHighlighting = 1 << 0
};

typedef NSUInteger PKSpanFormatterOptions;

#define PKSpanLayoutInfoColumnNumberKey     @"PKSpanLayoutInfoColumnNumber"
#define PKSpanLayoutInfoLineNumberKey       @"PKSpanLayoutInfoLineNumber"
#define PKSpanLayoutInfoIsTruncatedKey      @"PKSpanLayoutInfoIsTruncated"
#define PKSpanLayoutInfoUnderlineLengthKey  @"PKSpanLayoutInfoUnderlineLength"
#define PKSpanLayoutInfoSourceExcerptKey    @"PKSpanLayoutInfoSourceExcerpt"

/**
 * A formatter for spans
 */
@interface PKSpanFormatter : NSObject

-(id)init;
-(id)initWithUnderlineCharacter:(UniChar)underline options:(PKSpanFormatterOptions)options;

-(NSDictionary *)layoutInfoForSpan:(PKSpan *)span;
-(NSDictionary *)layoutInfoForSource:(NSString *)source range:(NSRange)range;
-(NSArray *)calloutLinesForSpan:(PKSpan *)span;
-(NSArray *)calloutLinesForLayoutInfo:(NSDictionary *)layoutInfo;

-(void)printCalloutForSpan:(PKSpan *)span stream:(FILE *)stream;
-(void)printCalloutForLayoutInfo:(NSDictionary *)layoutInfo stream:(FILE *)stream;

@property (readonly) UniChar                underlineCharacter;
@property (readonly) PKSpanFormatterOptions options;

@end

