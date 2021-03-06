%{

#include <stdio.h>
#include <iconv.h>
#include <machine/endian.h>

#include "PKGrammar.h"
#include "PKLexer.h"
#include "PKTypes.h"
#include "PKSpan.h"

static inline void pk_context_increment(PKScannerContext *context, const char *text) {
  if(context != NULL && text != NULL){
    context->location += strlen(text);
    context->column += strlen(text);
  }
}

static inline void pk_context_newline(PKScannerContext *context) {
  if(context != NULL){
    context->location += 1;
    context->column = 0;
    context->line++;
  }
}

char * pk_string_copy_literal(const char *string, size_t length, const char delim);

%}

%option noyywrap
%option reentrant
%option extra-type="PKScannerContext *"
%option yylineno
%option bison-bridge

/* Single-line comments state */
%x S_COMMENT
/* Multi-line comments state */
%x M_COMMENT

/* Universal Character Name: the naming conventions for UCS defined by International Standard ISO/IEC 10646 */
UCN         (\\u[0-9a-fA-F]{4}|\\U[0-9a-fA-F]{8})

/* DIGIT: any number from 0 to 9 */
DIGIT       [0-9]

/* HEX DIGIT */
HEX_DIGIT   [0-9a-fA-F]

/* LETTER: any uppercase or lowercase letter */
LETTER      [A-Za-z]

/* IDENT: starting with a letter; following by any occurence of letter, digit or underscore */
IDENT       ([_$a-zA-Z]|{UCN})([_$a-zA-Z0-9]|{UCN})*

/* EXPONENT: an exponent component of a number */
EXPONENT    (e|E)(\+|\-)[0-9]+

/* NUMBER: a number part */
NUMBER      0|([1-9][0-9]*)

/* HEX NUMBER: a hexadecimal number part (disambiguates with '0x' prefix) */
HEX_NUMBER  0(x|X)(0|([1-9a-fA-F][0-9a-fA-F]*))

/* INTEGER: an integer */
INTEGER     {NUMBER}{EXPONENT}?

/* HEX INTEGER: a hexadecimal integer */
HEX_INTEGER {HEX_NUMBER}{EXPONENT}?

/* LONG: an integer with a long suffix */
LONG        {NUMBER}{EXPONENT}?(l|L)

/* HEX LONG: a hexadecimal long */
HEX_LONG    {HEX_NUMBER}{EXPONENT}?(l|L)

/* FLOAT: a floating point number */
FLOAT       {NUMBER}\.{NUMBER}{EXPONENT}?

/* DOUBLE: a double precision floating point number */
DOUBLE      {NUMBER}\.{NUMBER}{EXPONENT}?(d|D)

/* STRING: anything between double quote except newlines; just considers \" and \\ characters */
STRING      \"([^"\\\n]|\\['"?\\abfnrtv]|{UCN})*\"

/* MODIFIERS: modifier flags */
MODIFIER    [cdg]+

/* PATTERN: a regular expression pattern */
PATTERN     [^\*\/]([^\/\\\n]|\\['\/?\\abfnrtv]|{UCN})*

/* MATCHER: a regular expression pattern */
MATCHER     \/{PATTERN}\/

/* REPLACE: a regular expression pattern with a replacement component */
REPLACE     {MATCHER}{PATTERN}\/

/* WHITESPACE: non-newline whitespace (space, tab) */
WS          [ \t]

%%

"//"            { BEGIN(S_COMMENT); pk_context_increment(yyextra, yytext); }
<S_COMMENT>.    { pk_context_increment(yyextra, yytext); }
<S_COMMENT>\n   { BEGIN(INITIAL); pk_context_newline(yyextra); }

"/*"            { BEGIN(M_COMMENT); pk_context_increment(yyextra, yytext); }
<M_COMMENT>"*/" { BEGIN(INITIAL); pk_context_increment(yyextra, yytext); }
<M_COMMENT>.    { pk_context_increment(yyextra, yytext); }
<M_COMMENT>\n   { pk_context_newline(yyextra); }

"&&"            { pk_context_increment(yyextra, yytext); return T_LAND; }
"||"            { pk_context_increment(yyextra, yytext); return T_LOR; }
"=="            { pk_context_increment(yyextra, yytext); return T_EQ; }
"!="            { pk_context_increment(yyextra, yytext); return T_NE; }
"=~"            { pk_context_increment(yyextra, yytext); return T_MATCH; }
">="            { pk_context_increment(yyextra, yytext); return T_GE; }
"<="            { pk_context_increment(yyextra, yytext); return T_LE; }
">"             { pk_context_increment(yyextra, yytext); return T_GT; }
"<"             { pk_context_increment(yyextra, yytext); return T_LT; }
"!"             { pk_context_increment(yyextra, yytext); return T_LNOT; }

"("             { pk_context_increment(yyextra, yytext); return T_LPAREN; }
")"             { pk_context_increment(yyextra, yytext); return T_RPAREN; }
"{"             { pk_context_increment(yyextra, yytext); return T_LBRACE; }
"}"             { pk_context_increment(yyextra, yytext); return T_RBRACE; }
"["             { pk_context_increment(yyextra, yytext); return T_LBRACK; }
"]"             { pk_context_increment(yyextra, yytext); return T_RBRACK; }

"&"             { pk_context_increment(yyextra, yytext); return T_BAND; }
"|"             { pk_context_increment(yyextra, yytext); return T_BOR; }
"^"             { pk_context_increment(yyextra, yytext); return T_BXOR; }
"~"             { pk_context_increment(yyextra, yytext); return T_BNOT; }

"%"             { pk_context_increment(yyextra, yytext); return T_MOD; }
"/"             { pk_context_increment(yyextra, yytext); return T_DIV; }
"*"             { pk_context_increment(yyextra, yytext); return T_MUL; }
"+"             { pk_context_increment(yyextra, yytext); return T_ADD; }
"-"             { pk_context_increment(yyextra, yytext); return T_SUB; }

"."             { pk_context_increment(yyextra, yytext); return T_DOT; }
","             { pk_context_increment(yyextra, yytext); return T_COMMA; }

"in"            { pk_context_increment(yyextra, yytext); return T_IN; }
"true"          { pk_context_increment(yyextra, yytext); yylval->asBool = 1; return T_BOOL; }
"false"         { pk_context_increment(yyextra, yytext); yylval->asBool = 0; return T_BOOL; }
"null"          { pk_context_increment(yyextra, yytext); bzero(yylval, sizeof(PKValue)); return T_NULL; }

\n              { pk_context_newline(yyextra); }
{WS}+           { pk_context_increment(yyextra, yytext); }

{INTEGER}       { pk_context_increment(yyextra, yytext); yylval->asInt = (int32_t)strtol(yytext, NULL, 10); return T_INT; }
{HEX_INTEGER}   { pk_context_increment(yyextra, yytext); yylval->asInt = (int32_t)strtol(yytext, NULL, 16); return T_INT; }
{LONG}          { pk_context_increment(yyextra, yytext); yylval->asLong = strtoll(yytext, NULL, 10); return T_LONG; }
{HEX_LONG}      { pk_context_increment(yyextra, yytext); yylval->asLong = strtoll(yytext, NULL, 16); return T_LONG; }
{FLOAT}         { pk_context_increment(yyextra, yytext); yylval->asFloat = (float)atof(yytext); return T_FLOAT; }
{DOUBLE}        { pk_context_increment(yyextra, yytext); yylval->asFloat = atof(yytext); return T_DOUBLE; }
{MODIFIER}      { pk_context_increment(yyextra, yytext); yylval->asString = strdup(yytext); return T_MODIFIER; }
{IDENT}         { pk_context_increment(yyextra, yytext); yylval->asString = strdup(yytext); return T_IDENT; }
{STRING}        { pk_context_increment(yyextra, yytext); yylval->asString = pk_string_copy_literal(yytext + 1, strlen(yytext) - 2, '"'); return T_QUOTED_STRING; }
{MATCHER}       { pk_context_increment(yyextra, yytext); yylval->asString = pk_string_copy_literal(yytext + 1, strlen(yytext) - 2, '/'); return T_MATCHER; }

. {
  PKSpan *where = [PKSpan spanWithDocument:yyextra->document source:yyextra->source range:NSMakeRange(yyextra->location, 1)];
  pk_context_increment(yyextra, yytext); // increment our location after we setup the error text span
  yyextra->error = NSERROR_WITH_SPAN(PKPredicateErrorDomain, PKStatusError, where, @"Syntax error: unrecognized character '%s'.", yytext);
  yyextra->state = kPKStateError;
  return -1;
}

%%

/**
 * Copy a string literal by unescaping. The provided string must not include any
 * bounding delimiters (e.g., quotation marks). To process a quoted string, for
 * example, use:
 *  
 *  pk_string_copy_literal(yytext + 1, strlen(yytext) - 2, '"').
 *  
 */
char * pk_string_copy_literal(const char *string, size_t length, const char delim) {
  BOOL status = FALSE;
  const char escape = '\\';
  const char *sp;
  int esc = 0;
  
  // the unescaped string cannot be larger (in bytes) than the escaped string, so we can
  // just allocate the same number of bytes as the escaped string.
  char *ep = malloc(length);
  
  // short-circuit for an empty string
  if(length < 1){
    ep[0] = 0;
    return ep;
  }
  
  // skip past the leading delimiter and adjust the length accordingly
  sp = string;
  
  size_t j = 0;
  for(size_t i = 0; i < length; i++){
    char c = sp[i];
    if((esc % 2) == 1){
      esc++;
      
      if(c == escape){
        ep[j++] = escape;
      }else if(c == delim){
        ep[j++] = delim;
      }else if(c == 'a'){
        ep[j++] = 0x07;
      }else if(c == 'b'){
        ep[j++] = 0x08;
      }else if(c == 'f'){
        ep[j++] = 0x0c;
      }else if(c == 'n'){
        ep[j++] = 0x0a;
      }else if(c == 'r'){
        ep[j++] = 0x0d;
      }else if(c == 't'){
        ep[j++] = 0x09;
      }else if(c == 'v'){
        ep[j++] = 0x0b;
      }else if(c == 'u' || c == 'U'){
        size_t dcount = (c == 'u') ? 4 : 8;
        if(length - i < (dcount + 1)) goto error; // require 'u' + 4 hex digits or 'U' + 8 hex digits
        
        char digits[dcount + 1];
        strncpy(digits, sp + i + 1, dcount); digits[dcount] = 0;
        uint32_t val = strtol(digits, NULL, 16);
        
        char *ip = (char *)&val;
        char *op = ep + j;
        size_t ivbytes = 4;
        size_t inbytes = ivbytes, outbytes = ivbytes;
        
#       if !defined(BYTE_ORDER)
#         error BYTE_ORDER is not defined
#       endif
        
        iconv_t iv;
#       if (BYTE_ORDER == BIG_ENDIAN)
          iv = iconv_open("UTF-8", "UTF-32BE");
#       else
          iv = iconv_open("UTF-8", "UTF-32LE");
#       endif
        assert(iv >= 0);
        
        size_t cv = iconv(iv, &ip, &inbytes, &op, &outbytes);
        if(cv == (size_t)-1){
          if(c == 'u'){
            fprintf(stderr, "Could not convert \\u%4X: %s\n", val, strerror(errno));
          }else{
            fprintf(stderr, "Could not convert \\U%8X: %s\n", val, strerror(errno));
          }
          abort();
        }
        
        iconv_close(iv);
        
        ivbytes = ivbytes - outbytes;
        digits[ivbytes] = 0;
        
        i += dcount; j += ivbytes;
      }else{
        ep[j++] = c;
      }
      
    }else if(c == escape){
      esc++;
    }else{
      ep[j++] = c;
    }
  }
  
  ep[j] = 0;
  status = TRUE;
error:
  if(ep && !status){
    free(ep); ep = NULL;
  }

  return ep;
}

