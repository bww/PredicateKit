%{

#include <stdio.h>
#include "PKGrammar.h"
#include "PKLexer.h"

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

%}

%option noyywrap
%option reentrant
%option extra-type="PKScannerContext *"
%option yylineno
%option bison-bridge

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
STRING      \"([^"\\\n]|\\['"?\\abfnrtv]|\\[0-7]{1,3}|\\[Xx][0-9a-fA-F]+|{UCN})*\"

/* WHITESPACE: non-newline whitespace (space, tab) */
WS          [ \t]

/* Single-line comments state */
%x S_COMMENT
/* Multi-line comments state */
%x M_COMMENT

%%

"//"            { BEGIN(S_COMMENT); pk_context_increment(yyextra, yytext); }
<S_COMMENT>\n   { BEGIN(INITIAL); pk_context_newline(yyextra); }
"/*"            { BEGIN(M_COMMENT); pk_context_increment(yyextra, yytext); }
<M_COMMENT>"*/" { BEGIN(INITIAL); pk_context_increment(yyextra, yytext); }
<M_COMMENT>\n   { BEGIN(INITIAL); pk_context_newline(yyextra); }
<M_COMMENT>.    { pk_context_increment(yyextra, yytext); }

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

\n              { pk_context_newline(yyextra); }
{WS}+           { pk_context_increment(yyextra, yytext); }

{LONG}          { pk_context_increment(yyextra, yytext); yylval->asLong = strtoll(yytext, NULL, 10); return T_LONG; }
{HEX_LONG}      { pk_context_increment(yyextra, yytext); yylval->asLong = strtoll(yytext, NULL, 16); return T_LONG; }
{INTEGER}       { pk_context_increment(yyextra, yytext); yylval->asInt = (int32_t)strtol(yytext, NULL, 10); return T_INT; }
{HEX_INTEGER}   { pk_context_increment(yyextra, yytext); yylval->asInt = (int32_t)strtol(yytext, NULL, 16); return T_INT; }
{FLOAT}         { pk_context_increment(yyextra, yytext); yylval->asFloat = (float)atof(yytext); return T_FLOAT; }
{DOUBLE}        { pk_context_increment(yyextra, yytext); yylval->asFloat = atof(yytext); return T_DOUBLE; }
{STRING}        { pk_context_increment(yyextra, yytext); yylval->asString = strdup(yytext); return T_QUOTED_STRING; }
{IDENT}         { pk_context_increment(yyextra, yytext); yylval->asString = strdup(yytext); return T_IDENT; }

. {
  pk_context_increment(yyextra, yytext);
  printf("error: unrecognized character at %d:%d '%s'\n", yyextra->line, yyextra->column, yytext);
}

%%

