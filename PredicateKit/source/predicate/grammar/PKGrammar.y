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
#include "PKDereferenceExpression.h"
#include "PKLiteralExpression.h"
#include "PKPatternExpression.h"
#include "PKExpressionModifier.h"
#include "PKModifiedExpression.h"
#include "PKCollectionExpression.h"
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
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKLogicalExpression compoundExpressionWithSpan:span type:kPKLogicalAnd expressions:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
logical(A) ::= bitwise(B) LOR bitwise(C). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKLogicalExpression compoundExpressionWithSpan:span type:kPKLogicalOr expressions:[NSArray arrayWithObjects:B.node, C.node, nil]];
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
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKBitwiseExpression bitwiseExpressionWithSpan:span type:kPKBitwiseOr operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
bitwise(A) ::= modified(B) BAND modified(C). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKBitwiseExpression bitwiseExpressionWithSpan:span type:kPKBitwiseAnd operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
bitwise(A) ::= modified(B) BXOR modified(C). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKBitwiseExpression bitwiseExpressionWithSpan:span type:kPKBitwiseExclusiveOr operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
bitwise(A) ::= modified(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

/* Modified expressions */

modified(A) ::= equality(B) LBRACK(C) MODIFIER(D) RBRACK(E). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span;
    span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(C.range.location, (E.range.location + E.range.length) - C.range.location)];
    PKExpressionModifier *modifier = [PKExpressionModifier expressionModifierWithSpan:span flags:D.value.asString];
    span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (E.range.location + E.range.length) - B.range.location)];
    A.node = [PKModifiedExpression modifiedExpressionWithSpan:span expression:B.node modifier:modifier];
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
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
equality(A) ::= relational(B) NE relational(C). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonNotEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
equality(A) ::= relational(B) MATCH relational(C). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonMatches operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
equality(A) ::= relational(B) IN relational(C). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonIn operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
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
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonGreaterThan operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
relational(A) ::= unary(B) GE unary(C). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonGreaterThanOrEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
relational(A) ::= unary(B) LT unary(C). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonLessThan operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
relational(A) ::= unary(B) LE unary(C). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonLessThanOrEqualTo operands:[NSArray arrayWithObjects:B.node, C.node, nil]];
  }
}
relational(A) ::= unary(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

/* Unary */

unary(A) ::= BNOT(B) dereference(C). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKBitwiseExpression bitwiseExpressionWithSpan:span type:kPKBitwiseNot operands:[NSArray arrayWithObjects:C.node, nil]];
  }
}
unary(A) ::= LNOT(B) dereference(C). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (C.range.location + C.range.length) - B.range.location)];
    A.node = [PKLogicalExpression compoundExpressionWithSpan:span type:kPKLogicalNot expressions:[NSArray arrayWithObjects:C.node, nil]];
  }
}
unary(A) ::= dereference(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

/* Dereference */

dereference(A) ::= components(B). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(B.range)];
    A.node = [PKDereferenceExpression dereferenceExpressionWithSpan:span identifiers:B.node]; // B.node is an NSArray of identifier expressions
  }
}
dereference(A) ::= primary(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = B.node;
  }
}

components(A) ::= components(B) DOT identifier(C). {
  if(context != NULL && context->state != kPKStateError){
    [(NSMutableArray *)(A.node = B.node) addObject:C.node];
  }
}
components(A) ::= identifier(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [NSMutableArray arrayWithObject:B.node];
  }
}

/* Identifier */

identifier(A) ::= IDENT(B). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(B.range)];
    A.node = [PKIdentifierExpression identifierExpressionWithSpan:span identifier:[NSString stringWithUTF8String:B.value.asString]];
    free((void *)B.value.asString); B.value.asString = NULL;
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

set(A) ::= LBRACE(B) parameters(C) RBRACE(D). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(B.range.location, (D.range.location + D.range.length) - B.range.location)];
    A.node = [PKSetExpression setExpressionWithSpan:span parameters:C.node];
  }
}

/* Parameters */

parameters(A) ::= parameters(B) COMMA expression(C). {
  if(context != NULL && context->state != kPKStateError){
    [(NSMutableArray *)(A.node = B.node) addObject:C.node];
  }
}
parameters(A) ::= expression(B). {
  if(context != NULL && context->state != kPKStateError){
    A.node = [NSMutableArray arrayWithObject:B.node];
  }
}

/* Literals */

literal(A) ::= BOOL(B). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(B.range)];
    A.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNumber numberWithBool:B.value.asBool]];
  }
}
literal(A) ::= NULL(B). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(B.range)];
    A.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNull null]];
  }
}
literal(A) ::= INT(B). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(B.range)];
    A.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNumber numberWithInt:B.value.asInt]];
  }
}
literal(A) ::= LONG(B). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(B.range)];
    A.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNumber numberWithLongLong:B.value.asLong]];
  }
}
literal(A) ::= FLOAT(B). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(B.range)];
    A.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNumber numberWithFloat:B.value.asFloat]];
  }
}
literal(A) ::= DOUBLE(B). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(B.range)];
    A.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNumber numberWithDouble:B.value.asDouble]];
  }
}
literal(A) ::= QUOTED_STRING(B). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(B.range)];
    A.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSString stringWithUTF8String:B.value.asString]];
    free((void *)B.value.asString); B.value.asString = NULL;
  }
}
literal(A) ::= REGEX(B). {
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(B.range)];
    A.node = [PKPatternExpression patternExpressionWithSpan:span pattern:[NSString stringWithUTF8String:B.value.asString]];
    free((void *)B.value.asString); B.value.asString = NULL;
  }
}

