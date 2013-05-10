%include {
#include <assert.h>
#include "PKLexer.h"
#include "PKTypes.h"
#include "PKGrammar.h"
#include "PKPredicate.h"
#include "PKCompoundExpression.h"
#include "PKBitwiseExpression.h"
#include "PKComparisonExpression.h"
#include "PKIdentifierExpression.h"
#include "PKLiteralExpression.h"
}

%name "__PKParser"
%token_prefix T_

%token_type     { PKToken }
%default_type   { PKToken }
%extra_argument { PKParserContext *context }

%parse_accept {
  // ...
}

%parse_failure {
  if(context != NULL && context->state != kPKParserStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"ERROR IN THE PARSER!");
    context->state = kPKParserStateError;
  }
}

%syntax_error {
  if(context != NULL && context->state != kPKParserStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"ERROR IN THE PARSER!");
    context->state = kPKParserStateError;
  }
}

%stack_overflow {
  context = context;
  fprintf(stderr,"Giving up. Parser stack overflow\n");
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

predicate ::= expression(A). {
  if(context != NULL && context->state != kPKParserStateError){
    context->predicate = (PKPredicate *)A.node;
    context->state = kPKParserStateFinished;
  }
}

expression(A) ::= bitwise(B) LAND bitwise(C). { A.node = [PKCompoundExpression compoundExpressionWithType:kPKCompoundAnd expressions:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
expression(A) ::= bitwise(B) LOR bitwise(C). { A.node = [PKCompoundExpression compoundExpressionWithType:kPKCompoundOr expressions:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
expression(A) ::= bitwise(B). { A.node = B.node; }

bitwise(A) ::= modified(B) BOR modified(C). { A.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseOr operands:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
bitwise(A) ::= modified(B) BAND modified(C). { A.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseAnd operands:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
bitwise(A) ::= modified(B) BXOR modified(C). { A.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseExclusiveOr operands:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
bitwise(A) ::= modified(B). { A.node = B.node; }

modified ::= equality LBRACK IDENT RBRACK.
modified(A) ::= equality(B). { A.node = B.node; }

equality(A) ::= relational(B) EQ relational(C). { A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
equality(A) ::= relational(B) NE relational(C). { A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonNotEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
equality(A) ::= relational(B) MATCH relational(C). { A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonMatches operands:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
equality(A) ::= relational(B) IN relational(C). { A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonIn operands:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
equality(A) ::= relational(B). { A.node = B.node; }

relational(A) ::= unary(B) GT unary(C). { A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonGreaterThan operands:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
relational(A) ::= unary(B) GE unary(C). { A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonGreaterThanOrEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
relational(A) ::= unary(B) LT unary(C). { A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonLessThan operands:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
relational(A) ::= unary(B) LE unary(C). { A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonLessThanOrEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]]; }
relational(A) ::= unary(B). { A.node = B.node; }

unary(A) ::= BNOT dereference(B). { A.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseNot operands:[NSArray arrayWithObjects:B.node, nil]]; }
unary(A) ::= LNOT dereference(B). { A.node = [PKCompoundExpression compoundExpressionWithType:kPKCompoundNot expressions:[NSArray arrayWithObjects:B.node, nil]]; }
unary(A) ::= dereference(B). { A.node = B.node; }

dereference ::= dereference DOT IDENT. {  }
dereference(A) ::= primary(B). { A.node = B.node; }

primary(A) ::= literal(B). { A.node = B.node; }
primary ::= collection.
primary(A) ::= LPAREN expression(B) RPAREN. { A.node = B.node; }

collection ::= LBRACE parameters RBRACE.

parameters ::= parameters COMMA expression.
parameters ::= expression.

literal(A) ::= BOOL(B). { A.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithBool:B.value.asBool]]; }
literal(A) ::= INT(B). { A.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithInt:B.value.asInt]]; }
literal(A) ::= LONG(B). { A.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithLongLong:B.value.asLong]]; }
literal(A) ::= FLOAT(B). { A.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithFloat:B.value.asFloat]]; }
literal(A) ::= DOUBLE(B). { A.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithDouble:B.value.asDouble]]; }

literal(A) ::= IDENT(B). {
  A.node = [PKIdentifierExpression identifierExpressionWithIdentifier:[NSString stringWithUTF8String:B.value.asString]];
  free((void *)B.value.asString);
  B.value.asString = NULL;
}

literal(A) ::= QUOTED_STRING(B). {
  A.node = [PKLiteralExpression literalExpressionWithValue:[NSString stringWithUTF8String:B.value.asString]];
  free((void *)B.value.asString);
  B.value.asString = NULL;
}

