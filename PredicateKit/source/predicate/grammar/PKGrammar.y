%include {
#include <assert.h>
#include "PKLexer.h"
#include "PKTypes.h"
#include "PKGrammar.h"
#include "PKExpression.h"
#include "PKLogicalExpression.h"
#include "PKBitwiseExpression.h"
#include "PKComparisonExpression.h"
#include "PKIdentifierExpression.h"
#include "PKLiteralExpression.h"
#include "PKPatternExpression.h"
#include "PKExpressionModifier.h"
#include "PKModifiedExpression.h"
#include "PKCollectionExpression.h"
#include "PKParameters.h"
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

/* Predicate */

predicate ::= expression(A). {
  if(context != NULL && context->state != kPKStateError){
    context->expression = A.node;
    context->state = kPKStateFinished;
  }
}

/* Expression */

expression(A) ::= logical(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

/* Logical */

logical(A) ::= bitwise(B) LAND bitwise(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKLogicalExpression compoundExpressionWithType:kPKLogicalAnd expressions:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
logical(A) ::= bitwise(B) LOR bitwise(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKLogicalExpression compoundExpressionWithType:kPKLogicalOr expressions:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
logical(A) ::= bitwise(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

/* Bitwise */

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

/* Modified expressions */

modified(A) ::= equality(B) LBRACK MODIFIER(C) RBRACK. {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKModifiedExpression modifiedExpressionWithExpression:B.node modifier:[PKExpressionModifier expressionModifierWithFlags:C.value.asString]];
    if(C.value.asString) free((void *)C.value.asString);
  }
}
modified(A) ::= equality(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

/* Equality */

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

/* Relational */

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

/* Unary */

unary(A) ::= BNOT dereference(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseNot operands:[NSArray arrayWithObjects:B.node, nil]];
  }
}
unary(A) ::= LNOT dereference(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKLogicalExpression compoundExpressionWithType:kPKLogicalNot expressions:[NSArray arrayWithObjects:B.node, nil]];
  }
}
unary(A) ::= dereference(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

/* Dereference */

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

/* Primary expressions */

primary(A) ::= literal(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}
primary(A) ::= set(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}
primary(A) ::= LPAREN expression(B) RPAREN. {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

/* Collections */

set(A) ::= LBRACE parameters(B) RBRACE. {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKSetExpression setExpressionWithParameters:B.node];
  }
}

/* Parameters */

parameters(A) ::= parameters(B) COMMA expression(C). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [(PKMutableParameters *)B.node addExpression:C.node];
  }
}
parameters(A) ::= expression(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKMutableParameters mutableParametersWithExpression:B.node];
  }
}

/* Literals */

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
literal(A) ::= REGEX(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [PKPatternExpression patternExpressionWithPattern:[NSString stringWithUTF8String:B.value.asString]];
    free((void *)B.value.asString); B.value.asString = NULL;
  }
}

