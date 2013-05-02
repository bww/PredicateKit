// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKParser.h"
#import "PKError.h"
#import "PKLexer.h"
#import "PKTypes.h"
#import "PKGrammar.h"

typedef struct yy_buffer_state *YY_BUFFER_STATE;
typedef void * yyscan_t;

void yylex_init(yyscan_t *lexer);
int  yylex(void *token, yyscan_t lexer);
void yylex_destroy(yyscan_t lexer);

char *yyget_text(yyscan_t scanner);

YY_BUFFER_STATE yy_scan_string(const char *source, void *lexer);
void yy_delete_buffer(YY_BUFFER_STATE buffer, void *lexer);

void * __PKParserAlloc(void *(*mallocProc)(size_t));
void __PKParserFree(void *p, void (*freeProc)(void*));
void __PKParser(void *yyp, int yymajor, PKToken yyminor, void *info);

@implementation PKParser

/**
 * Create a parser
 */
+(PKParser *)parser {
  return [[[self alloc] init] autorelease];
}

/**
 * Clean up
 */
-(void)dealloc {
  [super dealloc];
}

/**
 * Initialize
 */
-(id)init {
  if((self = [super init]) != nil){
    // ...
  }
  return self;
}

/**
 * Parse a predicate
 */
-(BOOL)parse:(NSString *)source error:(NSError **)error {
  YY_BUFFER_STATE buffer = NULL;
  yyscan_t lexer = NULL;
  void *parser = NULL;
  BOOL status = FALSE;
  PKToken token;
  int z;
  
  // make sure our input is valid
  if(source == nil || [source length] < 1){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Source must not be null or empty");
    goto error;
  }
  
  // setup our parser
  if((parser = __PKParserAlloc(malloc)) == NULL){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Could not create parser");
    goto error;
  }
  
  // scan our input source
  yylex_init(&lexer);
  yy_scan_string([source UTF8String], lexer);
  
  // parser our input source
  YYSTYPE value;
  while((z = yylex(&value, lexer)) > 0){
    
    token.text = yyget_text(lexer);
    token.value = value;
    token.token = z;
    
    __PKParser(parser, z, token, &token);
    
  }
  
  // end of input (we pass the last token again, which should be ignored)
  __PKParser(parser, 0, token, &token);
  
  // make sure we didn't finish with an error
  if(z < 0){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Could not parse source");
    goto error;
  }
  
  status = TRUE;
error:
  if(buffer) yy_delete_buffer(buffer, lexer);
  if(lexer) yylex_destroy(lexer);
  if(parser) __PKParserFree(parser, free);
  
  return status;
}

@end

