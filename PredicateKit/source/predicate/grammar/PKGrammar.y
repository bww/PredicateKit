%include {
#include <assert.h>
#include "PKLexer.h"
#include "PKTypes.h"
}

%name "__PKParser"
%token_prefix T_

%token_type     { PKToken }
%default_type   { PKToken }
%extra_argument { PKToken *context }

%parse_accept {
  fprintf(stderr, "OK!\n");
}

%parse_failure {
  fprintf(stderr,"Giving up.  Parser is hopelessly lost...\n");
}

%syntax_error {
  context = context;
  fprintf(stderr, "WHAT THE FUCK?!\n");
}

%stack_overflow {
  context = context;
  fprintf(stderr,"Giving up.  Parser stack overflow\n");
}

/*
%type INT       { PKToken }
%type HEX_INT   { PKToken }
%type LONG      { PKToken }
%type HEX_LONG  { PKToken }
%type FLOAT     { PKToken } 
%type DOUBLE    { PKToken }
%type STRING    { PKToken }
%type IDENT     { PKToken }
*/

%nonassoc LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK.

%left LAND.
%left LOR.
%left BAND.
%left BOR BXOR.

%nonassoc EQ NE GT GE LT LE MATCH QUESTION.

%left ADD SUB.
%left MUL DIV MOD.
%right EXP LNOT BNOT.
%nonassoc COMMA SEMI.

%start_symbol predicate

predicate ::= expr. {
  printf("PREDICATE\n");
  printf("  EXTRA %s\n", context->text);
}

expr ::= expr IDENT(A). {
  printf("EXPRESSION + IDENT\n");
  printf("  TOKEN %s\n", A.text);
}

expr ::= IDENT(A). {
  printf("IDENT\n");
  printf("  TOKEN %s\n", A.text);
}

