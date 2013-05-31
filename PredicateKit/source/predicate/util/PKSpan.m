// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKSpan.h"

@implementation PKSpan

@synthesize document = _document;
@synthesize source = _source;
@synthesize range = _range;

+(PKSpan *)spanWithDocument:(NSURL *)document source:(NSString *)source range:(NSRange)range {
  return [[[self alloc] initWithDocument:document source:source range:range] autorelease];
}

-(void)dealloc {
  [_document release];
  [_source release];
  [super dealloc];
}

-(id)initWithDocument:(NSURL *)document source:(NSString *)source range:(NSRange)range {
  if((self = [super init]) != nil){
    _document = [document retain];
    _source = [source retain];
    _range = range;
  }
  return self;
}

@end

@implementation PKSpanFormatter

@synthesize underlineCharacter = _underlineCharacter;

-(id)init {
  return [self initWithUnderlineCharacter:'^' options:kPKSpanFormatterOptionNone];
}

-(id)initWithUnderlineCharacter:(UniChar)underline options:(PKSpanFormatterOptions)options {
  if((self = [super init]) != nil){
    _underlineCharacter = underline;
    _options = options;
  }
  return self;
}

-(NSDictionary *)layoutInfoForSpan:(PKSpan *)span {
  return [self layoutInfoForSource:span.source range:span.range];
}

-(NSDictionary *)layoutInfoForSource:(NSString *)source range:(NSRange)range {
  UniChar c;
  
  NSInteger length = [source length];
  NSInteger end = MIN(range.location, length - 1);
  
  CFStringInlineBuffer buffer;
  CFStringInitInlineBuffer((CFStringRef)source, &buffer, CFRangeMake(0, length));
  
  while(end < length){
    c = CFStringGetCharacterFromInlineBuffer(&buffer, end);
    if(c != '\n') end++;
    else break;
  }
  
  NSInteger loc, start = -1, line = 1;
  for(loc = MAX(0, MIN(length - 1, range.location)); loc >= 0; loc--){
    c = CFStringGetCharacterFromInlineBuffer(&buffer, loc);
    if((end - loc) > 0 && c == '\n'){
      if(start < 0) start = loc + 1;
      line++; // increment our line count
    }
  }
  
  start = (start < 0) ? 0 : start;
  
  BOOL truncated = range.location + range.length > end;
  NSUInteger columnNumber = range.location - start;
  NSUInteger underline = MIN(range.length, end - range.location);
  NSString *excerpt = [[source substringWithRange:NSMakeRange(start, end - start)] retain];
  
  return [NSDictionary dictionaryWithObjectsAndKeys:
    [NSNumber numberWithInteger:columnNumber], PKSpanLayoutInfoColumnNumberKey,
    [NSNumber numberWithInteger:line], PKSpanLayoutInfoLineNumberKey,
    [NSNumber numberWithInteger:underline], PKSpanLayoutInfoUnderlineLengthKey,
    [NSNumber numberWithBool:truncated], PKSpanLayoutInfoIsTruncatedKey,
    excerpt, PKSpanLayoutInfoSourceExcerptKey,
    nil
  ];
  
}

-(NSArray *)calloutLinesForSpan:(PKSpan *)span {
  return [self calloutLinesForLayoutInfo:[self layoutInfoForSpan:span]];
}

-(NSArray *)calloutLinesForLayoutInfo:(NSDictionary *)layoutInfo {
  NSMutableArray *lines = [NSMutableArray array];
  UniChar space = ' ', pointer = self.underlineCharacter;
  
  // obtain our layout info for the span
  NSUInteger ncolumn = [[layoutInfo objectForKey:PKSpanLayoutInfoColumnNumberKey] integerValue];
  NSUInteger nuline = [[layoutInfo objectForKey:PKSpanLayoutInfoUnderlineLengthKey] integerValue];
  NSString *excerpt = [layoutInfo objectForKey:PKSpanLayoutInfoSourceExcerptKey];
  
  // add the source line itself
  if((self.options & kPKSpanFormatterOptionUseANSIHighlighting) == kPKSpanFormatterOptionUseANSIHighlighting){
    NSMutableString *line = [NSMutableString string];
    NSUInteger upper = ncolumn + nuline;
    NSUInteger length = [excerpt length];
    if(ncolumn > 0) [line appendString:[excerpt substringWithRange:NSMakeRange(0, ncolumn)]];
    if(nuline > 0){
      [line appendString:[NSString stringWithFormat:@"%c[1m", 27]];
      [line appendString:[excerpt substringWithRange:NSMakeRange(ncolumn, nuline)]];
      [line appendString:[NSString stringWithFormat:@"%c[0m", 27]];
    }
    if(length - upper > 0) [line appendString:[excerpt substringWithRange:NSMakeRange(upper, length - upper)]];
    [lines addObject:line];
  }else{
    [lines addObject:excerpt];
  }
  
  // create our underline line
  NSMutableString *underline = [NSMutableString string];
  for(NSUInteger i = 0; i < ncolumn; i++) CFStringAppendCharacters((CFMutableStringRef)underline, &space, 1);
  if((self.options & kPKSpanFormatterOptionUseANSIHighlighting) == kPKSpanFormatterOptionUseANSIHighlighting) [underline appendString:[NSString stringWithFormat:@"%c[1m", 27]];
  for(NSUInteger i = 0; i < MAX(1, nuline); i++) CFStringAppendCharacters((CFMutableStringRef)underline, &pointer, 1);
  if((self.options & kPKSpanFormatterOptionUseANSIHighlighting) == kPKSpanFormatterOptionUseANSIHighlighting) [underline appendString:[NSString stringWithFormat:@"%c[0m", 27]];
  [lines addObject:underline];
  
  return lines;
}

-(void)printCalloutForSpan:(PKSpan *)span stream:(FILE *)stream {
  [self printCalloutForLayoutInfo:[self layoutInfoForSpan:span] stream:stream];
}

-(void)printCalloutForLayoutInfo:(NSDictionary *)layoutInfo stream:(FILE *)stream {
  NSArray *lines;
  if((lines = [self calloutLinesForLayoutInfo:layoutInfo]) != nil){
    for(NSString *line in lines){
      fputs([line UTF8String], stream);
      fputc('\n', stream);
    }
  }
}

@end

