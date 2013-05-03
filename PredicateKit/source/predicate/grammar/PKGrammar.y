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

predicate ::= expression. {
  printf("PREDICATE\n");
}

expression ::= expression BOR expression. { printf("|\n"); }
expression ::= expression BAND expression. { printf("&\n"); }
expression ::= expression BXOR expression. { printf("^\n"); }
expression ::= expression LAND expression. { printf("&&\n"); }
expression ::= expression LOR expression. { printf("||\n"); }
expression ::= LPAREN expression RPAREN. { printf("(\n"); }
expression ::= primary.

primary ::= INT(A). { printf("I %d\n", A.value.asInt); }
primary ::= LONG(A). { printf("L %ld\n", A.value.asLong); }
primary ::= FLOAT(A). { printf("F %f\n", A.value.asFloat); }
primary ::= DOUBLE(A). { printf("D %f\n", A.value.asDouble); }
primary ::= IDENT(A). { printf("? %s\n", A.value.asString); }

