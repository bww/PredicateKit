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

