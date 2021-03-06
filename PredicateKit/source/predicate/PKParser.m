// 
// Copyright (c) 2013 Brian William Wolter. All rights reserved.
// 
// @LICENSE@
// 
// Developed in New York City
// 

#import "PKParser.h"
#import "PKLexer.h"
#import "PKTypes.h"
#import "PKGrammar.h"
#import "PKPredicate.h"
#import "PKExpression.h"

typedef struct yy_buffer_state *YY_BUFFER_STATE;
typedef void * yyscan_t;

void    yylex_init(yyscan_t *lexer);
int     yylex(void *token, yyscan_t lexer);
void    yylex_destroy(yyscan_t lexer);

char *  yyget_text(yyscan_t scanner);
int     yyget_lineno(yyscan_t scanner);
void    yyset_extra( YY_EXTRA_TYPE info, yyscan_t scanner);

YY_BUFFER_STATE yy_scan_string(const char *source, void *lexer);
void    yy_delete_buffer(YY_BUFFER_STATE buffer, void *lexer);

void *  __PKParserAlloc(void *(*mallocProc)(size_t));
void    __PKParserFree(void *p, void (*freeProc)(void*));
void    __PKParser(void *yyp, int yymajor, PKToken yyminor, void *info);

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
-(PKExpression *)parse:(NSString *)source error:(NSError **)error {
  PKExpression *expression = nil;
  int z;
  
  YY_BUFFER_STATE buffer = NULL;
  yyscan_t lexer = NULL;
  void *parser = NULL;
  
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
  
  // setup our context objects, which are not optional
  PKParserContext parserContext = PKParserContextMakeZero();
  parserContext.document = nil;
  parserContext.source = source;
  
  PKScannerContext scannerContext = PKScannerContextMakeZero();
  scannerContext.document = nil;
  scannerContext.source = source;
  
  // setup our state
  unsigned int location = 0, tcount = 0;
  PKToken currentToken = PKTokenMakeZero();
  
  // scan our input source
  yylex_init(&lexer);
  yyset_extra(&scannerContext, lexer);
  yy_scan_string([source UTF8String], lexer);
  
  // parser our input source
  YYSTYPE value;
  while((z = yylex(&value, lexer)) > 0){
    
    // determine the start and end offsets of our token
    unsigned int end = scannerContext.location;
    unsigned int start = end - strlen(yyget_text(lexer));
    
    // update our current token
    currentToken = PKTokenMake(z, value, PKRangeMake(start, end - start));
    // parse the token
    __PKParser(parser, z, currentToken, &parserContext);
    
    // check for an error from the parser
    if(parserContext.state == kPKStateError){
      if(error) *error = (parserContext.error != nil) ? parserContext.error : NSERROR(PKPredicateErrorDomain, PKStatusError, @"Could not parse predicate source");
      goto error;
    }
    
    // update the current location and token count
    location = end;
    tcount++;
    
  }
  
  // make sure we didn't finish with an error
  if(z < 0){
    if(error) *error = (scannerContext.error != nil) ? scannerContext.error : NSERROR(PKPredicateErrorDomain, PKStatusError, @"Could not parse predicate source");
    goto error;
  }
  
  // make sure we processed some tokens
  if(tcount < 1){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Predicate source contains no expression");
    goto error;
  }
  
  // end of input (we pass the last token again, which should be ignored)
  __PKParser(parser, 0, PKTokenMakeZero(), &parserContext);
  
  // check for an error from the parser on the last token
  if(parserContext.state == kPKStateError){
    if(error) *error = (parserContext.error != nil) ? parserContext.error : NSERROR(PKPredicateErrorDomain, PKStatusError, @"Could not parse predicate source");
    goto error;
  }
  
  // make sure we wound up with a predicate
  if(parserContext.state != kPKStateFinished || (expression = parserContext.expression) == nil){
    if(error) *error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"No predicate was produced");
    goto error;
  }
  
error:
  if(buffer) yy_delete_buffer(buffer, lexer);
  if(lexer) yylex_destroy(lexer);
  if(parser) __PKParserFree(parser, free);
  
  return expression;
}

@end

