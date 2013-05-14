%include {
#include <assert.h>
#include "PKLexer.h"
#include "PKTypes.h"
#include "PKGrammar.h"
#include "PKExpression.h"
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

%parse_failure {
  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Confused by errors; bailing out.");
    context->state = kPKStateError;
  }
}

%syntax_error {
  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Syntax error.");
    context->state = kPKStateError;
  }
}

%stack_overflow {
  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Stack overvlow.");
    context->state = kPKStateError;
  }
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
  if(context != NULL && context->state != kPKStateError){
    context->expression = A.node;
    context->state = kPKStateFinished;
  }
}

expression(A) ::= bitwise(B) LAND bitwise(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKCompoundExpression compoundExpressionWithType:kPKCompoundAnd expressions:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
expression(A) ::= bitwise(B) LOR bitwise(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKCompoundExpression compoundExpressionWithType:kPKCompoundOr expressions:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
expression(A) ::= bitwise(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

bitwise(A) ::= modified(B) BOR modified(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseOr operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
bitwise(A) ::= modified(B) BAND modified(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseAnd operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
bitwise(A) ::= modified(B) BXOR modified(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseExclusiveOr operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
bitwise(A) ::= modified(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

modified ::= equality LBRACK IDENT RBRACK. {
  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Language feature is not supported.");
    context->state = kPKStateError;
  }
}
modified(A) ::= equality(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

equality(A) ::= relational(B) EQ relational(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
equality(A) ::= relational(B) NE relational(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonNotEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
equality(A) ::= relational(B) MATCH relational(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonMatches operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
equality(A) ::= relational(B) IN relational(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonIn operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
equality(A) ::= relational(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

relational(A) ::= unary(B) GT unary(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonGreaterThan operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
relational(A) ::= unary(B) GE unary(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonGreaterThanOrEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
relational(A) ::= unary(B) LT unary(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonLessThan operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
relational(A) ::= unary(B) LE unary(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonLessThanOrEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
relational(A) ::= unary(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

unary(A) ::= BNOT dereference(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseNot operands:[NSArray arrayWithObjects:B.node, nil]];
  }
}
unary(A) ::= LNOT dereference(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKCompoundExpression compoundExpressionWithType:kPKCompoundNot expressions:[NSArray arrayWithObjects:B.node, nil]];
  }
}
unary(A) ::= dereference(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

dereference ::= dereference DOT IDENT. {
  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Language feature is not supported.");
    context->state = kPKStateError;
  }
}
dereference(A) ::= primary(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

primary(A) ::= literal(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}
primary ::= collection.
primary(A) ::= LPAREN expression(B) RPAREN. {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

collection ::= LBRACE parameters RBRACE. {
  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Language feature is not supported.");
    context->state = kPKStateError;
  }
}

parameters ::= parameters COMMA expression. {
  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Language feature is not supported.");
    context->state = kPKStateError;
  }
}
parameters ::= expression. {
  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Language feature is not supported.");
    context->state = kPKStateError;
  }
}

literal(A) ::= BOOL(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithBool:B.value.asBool]];
  }
}
literal(A) ::= NULL. {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKLiteralExpression literalExpressionWithValue:[NSNull null]];
  }
}
literal(A) ::= INT(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithInt:B.value.asInt]];
  }
}
literal(A) ::= LONG(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithLongLong:B.value.asLong]];
  }
}
literal(A) ::= FLOAT(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithFloat:B.value.asFloat]];
  }
}
literal(A) ::= DOUBLE(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithDouble:B.value.asDouble]];
  }
}
literal(A) ::= IDENT(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKIdentifierExpression identifierExpressionWithIdentifier:[NSString stringWithUTF8String:B.value.asString]];
    free((void *)B.value.asString); B.value.asString = NULL;
  }
}
literal(A) ::= QUOTED_STRING(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKLiteralExpression literalExpressionWithValue:[NSString stringWithUTF8String:B.value.asString]];
    free((void *)B.value.asString); B.value.asString = NULL;
  }
}

