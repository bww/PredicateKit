%{

#include <stdio.h>
#include "PKGrammar.h"
#include "PKLexer.h"

int pk_line = 1, pk_col = 1;

%}

%option noyywrap
%option reentrant
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

/* COMMENT: any c style comment */
COMMENT     ("/*"([^*]|[\r\n]|(\*+([^*/]|[\r\n])))*"*"+"/")|("//".*)

/* WHITESPACE: non-newline whitespace (space, tab) */
WS          [ \t]

%%

"&&"  { return T_LAND; }
"||"  { return T_LOR; }
"=="  { return T_EQ; }
"!="  { return T_NE; }
"=~"  { return T_MATCH; }
">="  { return T_GE; }
"<="  { return T_LE; }
">"   { return T_GT; }
"<"   { return T_LT; }
"!"   { return T_LNOT; }

"("   { return T_LPAREN; }
")"   { return T_RPAREN; }
"{"   { return T_LBRACE; }
"}"   { return T_RBRACE; }
"["   { return T_LBRACK; }
"]"   { return T_RBRACK; }

"&"   { return T_BAND; }
"|"   { return T_BOR; }
"^"   { return T_BXOR; }
"~"   { return T_BNOT; }

"%"   { return T_MOD; }
"/"   { return T_DIV; }
"*"   { return T_MUL; }
"+"   { return T_ADD; }
"-"   { return T_SUB; }

"?"   { return T_QUESTION; }
","   { return T_COMMA; }
";"   { return T_SEMI; }

\n            { pk_col = 0; ++pk_line; }
{WS}+         { pk_col += strlen(yytext); }

{LONG}        { yylval->asLong = strtoll(yytext, NULL, 10); return T_LONG; }
{HEX_LONG}    { yylval->asLong = strtoll(yytext, NULL, 16); return T_LONG; }
{INTEGER}     { yylval->asInt = (int32_t)strtol(yytext, NULL, 10); return T_INT; }
{HEX_INTEGER} { yylval->asInt = (int32_t)strtol(yytext, NULL, 16); return T_INT; }
{FLOAT}       { yylval->asFloat = (float)atof(yytext); return T_FLOAT; }
{DOUBLE}      { yylval->asFloat = atof(yytext); return T_DOUBLE; }
{STRING}      { printf("STR: %s\n", yytext); }
{IDENT}       { yylval->asString = yytext; return T_IDENT; }
{COMMENT}     { /* ignore comments */ }

. {
  pk_col += strlen(yytext);
  printf("error: unrecognized character at %d:%d '%s'\n", pk_line, pk_col, yytext);
}

%%

