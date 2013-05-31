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
  UniChar c;
  
  NSRange range = span.range;
  NSInteger length = [span.source length];
  NSInteger end = MIN(range.location, length - 1);
  
  CFStringInlineBuffer buffer;
  CFStringInitInlineBuffer((CFStringRef)span.source, &buffer, CFRangeMake(0, length));
  
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
  NSString *excerpt = [[span.source substringWithRange:NSMakeRange(start, end - start)] retain];
  
  return [NSDictionary dictionaryWithObjectsAndKeys:
    [NSNumber numberWithInteger:columnNumber, PKSpanLayoutInfoColumnNumberKey,
    [NSNumber numberWithInteger:line, PKSpanLayoutInfoLineNumberKey,
    [NSNumber numberWithInteger:underline, PKSpanLayoutInfoUnderlineLengthKey,
    [NSNumber numberWithBool:truncated], PKSpanLayoutInfoIsTruncatedKey,
    excerpt, PKSpanLayoutInfoSourceExcerptKey,
    nil
  ];
  
}

-(NSArray *)calloutLinesForSpan:(PKSpan *)span {
  UniChar c;
  
  NSRange range = span.range;
  NSInteger length = [span.source length];
  NSInteger end = MIN(range.location, length - 1);
  
  CFStringInlineBuffer buffer;
  CFStringInitInlineBuffer((CFStringRef)span.source, &buffer, CFRangeMake(0, length));
  
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
  
  //NSUInteger lineNumber = line;
  //BOOL truncated = range.location + range.length > end;
  NSUInteger columnNumber = range.location - start;
  NSUInteger underline = MIN(range.length, end - range.location);
  NSString *excerpt = [[span.source substringWithRange:NSMakeRange(start, end - start)] retain];
  
  NSMutableArray *calloutLines = [NSMutableArray array];
  UniChar space = ' ', pointer = self.underlineCharacter;
  
  // add the source line itself
  if((self.options & kPKSpanFormatterOptionUseANSIHighlighting) == kPKSpanFormatterOptionUseANSIHighlighting){
    NSMutableString *calloutLine = [NSMutableString string];
    NSUInteger upper = columnNumber + underline;
    length = [excerpt length];
    if(columnNumber > 0) [calloutLine appendString:[excerpt substringWithRange:NSMakeRange(0, columnNumber)]];
    if(underline > 0){
      [calloutLine appendString:[NSString stringWithFormat:@"%c[1m", 27]];
      [calloutLine appendString:[excerpt substringWithRange:NSMakeRange(columnNumber, underline)]];
      [calloutLine appendString:[NSString stringWithFormat:@"%c[0m", 27]];
    }
    if(length - upper > 0) [calloutLine appendString:[excerpt substringWithRange:NSMakeRange(upper, length - upper)]];
    [calloutLines addObject:calloutLine];
  }else{
    [calloutLines addObject:excerpt];
  }
  
  // create our underline line
  NSMutableString *underlineLine = [NSMutableString string];
  for(NSUInteger i = 0; i < columnNumber; i++) CFStringAppendCharacters((CFMutableStringRef)underlineLine, &space, 1);
  if((self.options & kPKSpanFormatterOptionUseANSIHighlighting) == kPKSpanFormatterOptionUseANSIHighlighting) [underlineLine appendString:[NSString stringWithFormat:@"%c[1m", 27]];
  for(NSUInteger i = 0; i < MAX(1, underline); i++) CFStringAppendCharacters((CFMutableStringRef)underlineLine, &pointer, 1);
  if((self.options & kPKSpanFormatterOptionUseANSIHighlighting) == kPKSpanFormatterOptionUseANSIHighlighting) [underlineLine appendString:[NSString stringWithFormat:@"%c[0m", 27]];
  [calloutLines addObject:underlineLine];
  
  return calloutLines;
}

-(void)printCalloutForSpan:(PKSpan *)span stream:(FILE *)stream {
  NSArray *lines;
  if((lines = [self calloutLinesForSpan:span]) != nil){
    for(NSString *line in lines){
      fputs([line UTF8String], stream);
      fputc('\n', stream);
    }
  }
}

@end

