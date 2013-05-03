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
  fprintf(stderr, "Syntax error: %d\n", TOKEN.token);
}

%stack_overflow {
  context = context;
  fprintf(stderr,"Giving up.  Parser stack overflow\n");
}

%nonassoc LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK.

%right LNOT BNOT.

%left LAND.
%left LOR.
%left BAND.
%left BOR BXOR.

%nonassoc EQ NE GT GE LT LE MATCH.

%left ADD SUB.
%left MUL DIV MOD.
%right EXP.

predicate ::= expression. { printf("PREDICATE\n"); }

expression ::= bitwise LAND bitwise. { printf("&&\n"); }
expression ::= bitwise LOR bitwise. { printf("||\n"); }
expression ::= bitwise LNOT bitwise. { printf("!\n"); }
expression ::= bitwise.

bitwise ::= modified BOR modified. { printf("|\n"); }
bitwise ::= modified BAND modified. { printf("&\n"); }
bitwise ::= modified BXOR modified. { printf("^\n"); }
bitwise ::= modified.

modified ::= equality LBRACK IDENT RBRACK.
modified ::= equality.

equality ::= relational EQ relational. { printf("==\n"); }
equality ::= relational NE relational. { printf("!=\n"); }
equality ::= relational MATCH relational. { printf("=~\n"); }
equality ::= relational IN relational. { printf("in\n"); }
equality ::= relational.

relational ::= unary GT unary. { printf(">\n"); }
relational ::= unary GE unary. { printf(">=\n"); }
relational ::= unary LT unary. { printf("<\n"); }
relational ::= unary LE unary. { printf("<=\n"); }
relational ::= unary.

unary ::= BNOT dereference.
unary ::= LNOT dereference.
unary ::= dereference.

dereference ::= primary DOT IDENT(A). { printf(". %s\n", A.value.asString); }
dereference ::= primary.

primary ::= literal.
primary ::= collection.
primary ::= LPAREN expression RPAREN. { printf("()\n"); }

collection ::= LBRACE parameters RBRACE.

parameters ::= parameters COMMA expression.
parameters ::= expression.

literal ::= BOOL(A). { printf("B %d\n", A.value.asBool); }
literal ::= INT(A). { printf("I %d\n", A.value.asInt); }
literal ::= LONG(A). { printf("L %ld\n", A.value.asLong); }
literal ::= FLOAT(A). { printf("F %f\n", A.value.asFloat); }
literal ::= DOUBLE(A). { printf("D %f\n", A.value.asDouble); }
literal ::= IDENT(A). { printf("~ %s\n", A.value.asString); }

