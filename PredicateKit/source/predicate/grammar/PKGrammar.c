/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is included that follows the "include" declaration
** in the input grammar file. */
#include <stdio.h>
#line 1 "PKGrammar.y"

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
#line 25 "PKGrammar.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    __PKParserTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is __PKParserTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.  If
**                       zero the stack is dynamically sized using realloc()
**    __PKParserARG_SDECL     A static variable declaration for the %extra_argument
**    __PKParserARG_PDECL     A parameter declaration for the %extra_argument
**    __PKParserARG_STORE     Code to store %extra_argument into yypParser
**    __PKParserARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 57
#define YYACTIONTYPE unsigned char
#define __PKParserTOKENTYPE  PKToken 
typedef union {
  int yyinit;
  __PKParserTOKENTYPE yy0;
  PKToken yy41;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define __PKParserARG_SDECL  PKParserContext *context ;
#define __PKParserARG_PDECL , PKParserContext *context 
#define __PKParserARG_FETCH  PKParserContext *context  = yypParser->context 
#define __PKParserARG_STORE yypParser->context  = context 
#define YYNSTATE 67
#define YYNRULE 43
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* The yyzerominor constant is used to initialize instances of
** YYMINORTYPE objects to zero. */
static const YYMINORTYPE yyzerominor = { 0 };

/* Define the yytestcase() macro to be a no-op if is not already defined
** otherwise.
**
** Applications can choose to define yytestcase() in the %include section
** to a macro that can assist in verifying code coverage.  For production
** code the yytestcase() macro should be turned off.  But it is useful
** for testing.
*/
#ifndef yytestcase
# define yytestcase(X)
#endif


/* Next are the tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
#define YY_ACTTAB_COUNT (230)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */    41,   66,   24,   22,   29,   21,   20,   52,   26,   57,
 /*    10 */    56,   55,   54,   23,  111,   30,   66,   24,   22,   29,
 /*    20 */    21,   20,   52,   26,   57,   56,   55,   54,    3,   67,
 /*    30 */     1,    7,    8,    6,   17,   18,   25,   66,   24,   22,
 /*    40 */    29,   21,   20,   52,   26,   57,   56,   55,   54,   62,
 /*    50 */    20,   52,   26,   57,   56,   55,   54,   58,   28,   49,
 /*    60 */    48,   47,   46,   45,   44,   43,   42,   50,   66,   24,
 /*    70 */    22,   29,   21,   20,   52,   26,   57,   56,   55,   54,
 /*    80 */     3,   51,    1,   65,   22,   29,   21,   20,   52,   26,
 /*    90 */    57,   56,   55,   54,   64,   29,   21,   20,   52,   26,
 /*   100 */    57,   56,   55,   54,   16,   15,   14,   13,    2,   58,
 /*   110 */    27,   49,   48,   47,   46,   45,   44,   43,   42,   31,
 /*   120 */    22,   29,   21,   20,   52,   26,   57,   56,   55,   54,
 /*   130 */    33,   29,   21,   20,   52,   26,   57,   56,   55,   54,
 /*   140 */    32,   29,   21,   20,   52,   26,   57,   56,   55,   54,
 /*   150 */    36,   20,   52,   26,   57,   56,   55,   54,   63,   35,
 /*   160 */    20,   52,   26,   57,   56,   55,   54,   34,   20,   52,
 /*   170 */    26,   57,   56,   55,   54,   61,   52,   26,   57,   56,
 /*   180 */    55,   54,   39,   52,   26,   57,   56,   55,   54,   38,
 /*   190 */    52,   26,   57,   56,   55,   54,   37,   52,   26,   57,
 /*   200 */    56,   55,   54,   60,   26,   57,   56,   55,   54,   53,
 /*   210 */    26,   57,   56,   55,   54,   12,   11,    5,    4,   19,
 /*   220 */    40,   10,   59,   58,  112,  112,  112,  112,  112,    9,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    42,   43,   44,   45,   46,   47,   48,   49,   50,   51,
 /*    10 */    52,   53,   54,   55,   41,   42,   43,   44,   45,   46,
 /*    20 */    47,   48,   49,   50,   51,   52,   53,   54,    1,    0,
 /*    30 */     3,   11,   12,   13,    7,    8,   42,   43,   44,   45,
 /*    40 */    46,   47,   48,   49,   50,   51,   52,   53,   54,   47,
 /*    50 */    48,   49,   50,   51,   52,   53,   54,   30,    5,   32,
 /*    60 */    33,   34,   35,   36,   37,   38,   39,   42,   43,   44,
 /*    70 */    45,   46,   47,   48,   49,   50,   51,   52,   53,   54,
 /*    80 */     1,    4,    3,   44,   45,   46,   47,   48,   49,   50,
 /*    90 */    51,   52,   53,   54,   45,   46,   47,   48,   49,   50,
 /*   100 */    51,   52,   53,   54,   16,   17,   18,   19,   31,   30,
 /*   110 */    27,   32,   33,   34,   35,   36,   37,   38,   39,   44,
 /*   120 */    45,   46,   47,   48,   49,   50,   51,   52,   53,   54,
 /*   130 */    45,   46,   47,   48,   49,   50,   51,   52,   53,   54,
 /*   140 */    45,   46,   47,   48,   49,   50,   51,   52,   53,   54,
 /*   150 */    47,   48,   49,   50,   51,   52,   53,   54,    6,   47,
 /*   160 */    48,   49,   50,   51,   52,   53,   54,   47,   48,   49,
 /*   170 */    50,   51,   52,   53,   54,   48,   49,   50,   51,   52,
 /*   180 */    53,   54,   48,   49,   50,   51,   52,   53,   54,   48,
 /*   190 */    49,   50,   51,   52,   53,   54,   48,   49,   50,   51,
 /*   200 */    52,   53,   54,   49,   50,   51,   52,   53,   54,   49,
 /*   210 */    50,   51,   52,   53,   54,   14,   15,    9,   10,   29,
 /*   220 */     2,   20,   52,   30,   56,   56,   56,   56,   56,   28,
};
#define YY_SHIFT_USE_DFLT (-1)
#define YY_SHIFT_COUNT (30)
#define YY_SHIFT_MIN   (0)
#define YY_SHIFT_MAX   (218)
static const short yy_shift_ofst[] = {
 /*     0 */    27,   27,   27,   27,   27,   27,   27,   27,   27,   27,
 /*    10 */    27,   27,   27,   27,   27,   27,   27,   79,   79,  193,
 /*    20 */    88,  201,   20,   77,  208,  218,  190,  152,   83,   53,
 /*    30 */    29,
};
#define YY_REDUCE_USE_DFLT (-43)
#define YY_REDUCE_COUNT (19)
#define YY_REDUCE_MIN   (-42)
#define YY_REDUCE_MAX   (170)
static const short yy_reduce_ofst[] = {
 /*     0 */   -27,  -42,   25,   -6,   75,   39,   95,   85,   49,  120,
 /*    10 */   112,  103,    2,  148,  141,  134,  127,  160,  154,  170,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
 /*    10 */   110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
 /*    20 */    87,   82,   75,  110,   71,  110,   91,  110,  110,   77,
 /*    30 */   110,   70,   74,   73,   81,   80,   79,   86,   85,   84,
 /*    40 */    98,  101,  109,  108,  107,  106,  105,  104,  103,  102,
 /*    50 */   100,   99,   90,   89,   97,   96,   94,   92,   95,   93,
 /*    60 */    88,   83,   78,   76,   72,   69,   68,
};

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammar, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  YYACTIONTYPE stateno;  /* The state-number */
  YYCODETYPE major;      /* The major token value.  This is the code
                         ** number for the token at this stack level */
  YYMINORTYPE minor;     /* The user-supplied minor token value.  This
                         ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
#ifdef YYTRACKMAXSTACKDEPTH
  int yyidxMax;                 /* Maximum value of yyidx */
#endif
  int yyerrcnt;                 /* Shifts left before out of the error */
  __PKParserARG_SDECL                /* A place to hold %extra_argument */
#if YYSTACKDEPTH<=0
  int yystksz;                  /* Current side of the stack */
  yyStackEntry *yystack;        /* The parser's stack */
#else
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
#endif
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void __PKParserTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "LPAREN",        "RPAREN",        "LBRACE",      
  "RBRACE",        "LBRACK",        "RBRACK",        "LNOT",        
  "BNOT",          "LAND",          "LOR",           "BAND",        
  "BOR",           "BXOR",          "EQ",            "NE",          
  "GT",            "GE",            "LT",            "LE",          
  "MATCH",         "ADD",           "SUB",           "MUL",         
  "DIV",           "MOD",           "EXP",           "MODIFIER",    
  "IN",            "DOT",           "IDENT",         "COMMA",       
  "BOOL",          "NULL",          "INT",           "LONG",        
  "FLOAT",         "DOUBLE",        "QUOTED_STRING",  "REGEX",       
  "error",         "predicate",     "expression",    "logical",     
  "bitwise",       "modified",      "equality",      "relational",  
  "unary",         "dereference",   "components",    "primary",     
  "identifier",    "literal",       "set",           "parameters",  
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "predicate ::= expression",
 /*   1 */ "expression ::= logical",
 /*   2 */ "logical ::= bitwise LAND bitwise",
 /*   3 */ "logical ::= bitwise LOR bitwise",
 /*   4 */ "logical ::= bitwise",
 /*   5 */ "bitwise ::= modified BOR modified",
 /*   6 */ "bitwise ::= modified BAND modified",
 /*   7 */ "bitwise ::= modified BXOR modified",
 /*   8 */ "bitwise ::= modified",
 /*   9 */ "modified ::= equality LBRACK MODIFIER RBRACK",
 /*  10 */ "modified ::= equality",
 /*  11 */ "equality ::= relational EQ relational",
 /*  12 */ "equality ::= relational NE relational",
 /*  13 */ "equality ::= relational MATCH relational",
 /*  14 */ "equality ::= relational IN relational",
 /*  15 */ "equality ::= relational",
 /*  16 */ "relational ::= unary GT unary",
 /*  17 */ "relational ::= unary GE unary",
 /*  18 */ "relational ::= unary LT unary",
 /*  19 */ "relational ::= unary LE unary",
 /*  20 */ "relational ::= unary",
 /*  21 */ "unary ::= BNOT dereference",
 /*  22 */ "unary ::= LNOT dereference",
 /*  23 */ "unary ::= dereference",
 /*  24 */ "dereference ::= components",
 /*  25 */ "dereference ::= primary",
 /*  26 */ "components ::= components DOT identifier",
 /*  27 */ "components ::= identifier",
 /*  28 */ "identifier ::= IDENT",
 /*  29 */ "primary ::= literal",
 /*  30 */ "primary ::= set",
 /*  31 */ "primary ::= LPAREN expression RPAREN",
 /*  32 */ "set ::= LBRACE parameters RBRACE",
 /*  33 */ "parameters ::= parameters COMMA expression",
 /*  34 */ "parameters ::= expression",
 /*  35 */ "literal ::= BOOL",
 /*  36 */ "literal ::= NULL",
 /*  37 */ "literal ::= INT",
 /*  38 */ "literal ::= LONG",
 /*  39 */ "literal ::= FLOAT",
 /*  40 */ "literal ::= DOUBLE",
 /*  41 */ "literal ::= QUOTED_STRING",
 /*  42 */ "literal ::= REGEX",
};
#endif /* NDEBUG */


#if YYSTACKDEPTH<=0
/*
** Try to increase the size of the parser stack.
*/
static void yyGrowStack(yyParser *p){
  int newSize;
  yyStackEntry *pNew;

  newSize = p->yystksz*2 + 100;
  pNew = realloc(p->yystack, newSize*sizeof(pNew[0]));
  if( pNew ){
    p->yystack = pNew;
    p->yystksz = newSize;
#ifndef NDEBUG
    if( yyTraceFILE ){
      fprintf(yyTraceFILE,"%sStack grows to %d entries!\n",
              yyTracePrompt, p->yystksz);
    }
#endif
  }
}
#endif

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to __PKParser and __PKParserFree.
*/
void *__PKParserAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
#ifdef YYTRACKMAXSTACKDEPTH
    pParser->yyidxMax = 0;
#endif
#if YYSTACKDEPTH<=0
    pParser->yystack = NULL;
    pParser->yystksz = 0;
    yyGrowStack(pParser);
#endif
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(
  yyParser *yypParser,    /* The parser */
  YYCODETYPE yymajor,     /* Type code for object to destroy */
  YYMINORTYPE *yypminor   /* The object to be destroyed */
){
  __PKParserARG_FETCH;
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor(pParser, yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from __PKParserAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void __PKParserFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
#if YYSTACKDEPTH<=0
  free(pParser->yystack);
#endif
  (*freeProc)((void*)pParser);
}

/*
** Return the peak depth of the stack for a parser.
*/
#ifdef YYTRACKMAXSTACKDEPTH
int __PKParserStackPeak(void *p){
  yyParser *pParser = (yyParser*)p;
  return pParser->yyidxMax;
}
#endif

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_COUNT
   || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    if( iLookAhead>0 ){
#ifdef YYFALLBACK
      YYCODETYPE iFallback;            /* Fallback token */
      if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
             && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
             yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
        }
#endif
        return yy_find_shift_action(pParser, iFallback);
      }
#endif
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          yy_lookahead[j]==YYWILDCARD
        ){
#ifndef NDEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[YYWILDCARD]);
          }
#endif /* NDEBUG */
          return yy_action[j];
        }
      }
#endif /* YYWILDCARD */
    }
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  YYCODETYPE iLookAhead     /* The look-ahead token */
){
  int i;
#ifdef YYERRORSYMBOL
  if( stateno>YY_REDUCE_COUNT ){
    return yy_default[stateno];
  }
#else
  assert( stateno<=YY_REDUCE_COUNT );
#endif
  i = yy_reduce_ofst[stateno];
  assert( i!=YY_REDUCE_USE_DFLT );
  assert( iLookAhead!=YYNOCODE );
  i += iLookAhead;
#ifdef YYERRORSYMBOL
  if( i<0 || i>=YY_ACTTAB_COUNT || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }
#else
  assert( i>=0 && i<YY_ACTTAB_COUNT );
  assert( yy_lookahead[i]==iLookAhead );
#endif
  return yy_action[i];
}

/*
** The following routine is called if the stack overflows.
*/
static void yyStackOverflow(yyParser *yypParser, YYMINORTYPE *yypMinor){
   __PKParserARG_FETCH;
   yypParser->yyidx--;
#ifndef NDEBUG
   if( yyTraceFILE ){
     fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
   }
#endif
   while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
   /* Here code is inserted which will execute if the parser
   ** stack every overflows */
#line 34 "PKGrammar.y"

  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Stack overflow");
    context->state = kPKStateError;
  }
#line 657 "PKGrammar.c"
   __PKParserARG_STORE; /* Suppress warning about unused %extra_argument var */
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer to the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
#ifdef YYTRACKMAXSTACKDEPTH
  if( yypParser->yyidx>yypParser->yyidxMax ){
    yypParser->yyidxMax = yypParser->yyidx;
  }
#endif
#if YYSTACKDEPTH>0 
  if( yypParser->yyidx>=YYSTACKDEPTH ){
    yyStackOverflow(yypParser, yypMinor);
    return;
  }
#else
  if( yypParser->yyidx>=yypParser->yystksz ){
    yyGrowStack(yypParser);
    if( yypParser->yyidx>=yypParser->yystksz ){
      yyStackOverflow(yypParser, yypMinor);
      return;
    }
  }
#endif
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = (YYACTIONTYPE)yyNewState;
  yytos->major = (YYCODETYPE)yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 41, 1 },
  { 42, 1 },
  { 43, 3 },
  { 43, 3 },
  { 43, 1 },
  { 44, 3 },
  { 44, 3 },
  { 44, 3 },
  { 44, 1 },
  { 45, 4 },
  { 45, 1 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 3 },
  { 46, 1 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 3 },
  { 47, 1 },
  { 48, 2 },
  { 48, 2 },
  { 48, 1 },
  { 49, 1 },
  { 49, 1 },
  { 50, 3 },
  { 50, 1 },
  { 52, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 3 },
  { 54, 3 },
  { 55, 3 },
  { 55, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 1 },
  { 53, 1 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  __PKParserARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<(int)(sizeof(yyRuleName)/sizeof(yyRuleName[0])) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  **
  ** 2007-01-16:  The wireshark project (www.wireshark.org) reports that
  ** without this code, their parser segfaults.  I'm not sure what there
  ** parser is doing to make this happen.  This is the second bug report
  ** from wireshark this week.  Clearly they are stressing Lemon in ways
  ** that it has not been previously stressed...  (SQLite ticket #2172)
  */
  /*memset(&yygotominor, 0, sizeof(yygotominor));*/
  yygotominor = yyzerominor;


  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 0: /* predicate ::= expression */
#line 65 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    context->expression = yymsp[0].minor.yy41.node;
    context->state = kPKStateFinished;
  }
}
#line 819 "PKGrammar.c"
        break;
      case 1: /* expression ::= logical */
      case 4: /* logical ::= bitwise */ yytestcase(yyruleno==4);
      case 8: /* bitwise ::= modified */ yytestcase(yyruleno==8);
      case 10: /* modified ::= equality */ yytestcase(yyruleno==10);
      case 15: /* equality ::= relational */ yytestcase(yyruleno==15);
      case 20: /* relational ::= unary */ yytestcase(yyruleno==20);
      case 23: /* unary ::= dereference */ yytestcase(yyruleno==23);
      case 25: /* dereference ::= primary */ yytestcase(yyruleno==25);
      case 29: /* primary ::= literal */ yytestcase(yyruleno==29);
      case 30: /* primary ::= set */ yytestcase(yyruleno==30);
#line 74 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy41.node = yymsp[0].minor.yy41.node;
  }
}
#line 837 "PKGrammar.c"
        break;
      case 2: /* logical ::= bitwise LAND bitwise */
#line 82 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKLogicalExpression compoundExpressionWithSpan:span type:kPKLogicalAnd expressions:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 847 "PKGrammar.c"
        break;
      case 3: /* logical ::= bitwise LOR bitwise */
#line 88 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKLogicalExpression compoundExpressionWithSpan:span type:kPKLogicalOr expressions:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 857 "PKGrammar.c"
        break;
      case 5: /* bitwise ::= modified BOR modified */
#line 102 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKBitwiseExpression bitwiseExpressionWithSpan:span type:kPKBitwiseOr operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 867 "PKGrammar.c"
        break;
      case 6: /* bitwise ::= modified BAND modified */
#line 108 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKBitwiseExpression bitwiseExpressionWithSpan:span type:kPKBitwiseAnd operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 877 "PKGrammar.c"
        break;
      case 7: /* bitwise ::= modified BXOR modified */
#line 114 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKBitwiseExpression bitwiseExpressionWithSpan:span type:kPKBitwiseExclusiveOr operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 887 "PKGrammar.c"
        break;
      case 9: /* modified ::= equality LBRACK MODIFIER RBRACK */
#line 128 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span;
    span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy0.range.location, (yymsp[0].minor.yy0.range.location + yymsp[0].minor.yy0.range.length) - yymsp[-2].minor.yy0.range.location)];
    PKExpressionModifier *modifier = [PKExpressionModifier expressionModifierWithSpan:span flags:yymsp[-1].minor.yy0.value.asString];
    span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-3].minor.yy41.range.location, (yymsp[0].minor.yy0.range.location + yymsp[0].minor.yy0.range.length) - yymsp[-3].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKModifiedExpression modifiedExpressionWithSpan:span expression:yymsp[-3].minor.yy41.node modifier:modifier];
    if(yymsp[-2].minor.yy0.value.asString) free((void *)yymsp[-2].minor.yy0.value.asString);
  }
}
#line 901 "PKGrammar.c"
        break;
      case 11: /* equality ::= relational EQ relational */
#line 146 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 911 "PKGrammar.c"
        break;
      case 12: /* equality ::= relational NE relational */
#line 152 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonNotEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 921 "PKGrammar.c"
        break;
      case 13: /* equality ::= relational MATCH relational */
#line 158 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonMatches operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 931 "PKGrammar.c"
        break;
      case 14: /* equality ::= relational IN relational */
#line 164 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonIn operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 941 "PKGrammar.c"
        break;
      case 16: /* relational ::= unary GT unary */
#line 178 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonGreaterThan operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 951 "PKGrammar.c"
        break;
      case 17: /* relational ::= unary GE unary */
#line 184 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonGreaterThanOrEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 961 "PKGrammar.c"
        break;
      case 18: /* relational ::= unary LT unary */
#line 190 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonLessThan operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 971 "PKGrammar.c"
        break;
      case 19: /* relational ::= unary LE unary */
#line 196 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy41.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-2].minor.yy41.range.location)];
    yygotominor.yy41.node = [PKComparisonExpression comparisonExpressionWithSpan:span type:kPKComparisonLessThanOrEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy41.node, yymsp[0].minor.yy41.node, nil]];
  }
}
#line 981 "PKGrammar.c"
        break;
      case 21: /* unary ::= BNOT dereference */
#line 210 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-1].minor.yy0.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-1].minor.yy0.range.location)];
    yygotominor.yy41.node = [PKBitwiseExpression bitwiseExpressionWithSpan:span type:kPKBitwiseNot operands:[NSArray arrayWithObjects:yymsp[0].minor.yy41.node, nil]];
  }
}
#line 991 "PKGrammar.c"
        break;
      case 22: /* unary ::= LNOT dereference */
#line 216 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-1].minor.yy0.range.location, (yymsp[0].minor.yy41.range.location + yymsp[0].minor.yy41.range.length) - yymsp[-1].minor.yy0.range.location)];
    yygotominor.yy41.node = [PKLogicalExpression compoundExpressionWithSpan:span type:kPKLogicalNot expressions:[NSArray arrayWithObjects:yymsp[0].minor.yy41.node, nil]];
  }
}
#line 1001 "PKGrammar.c"
        break;
      case 24: /* dereference ::= components */
#line 230 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(yymsp[0].minor.yy41.range)];
    yygotominor.yy41.node = [PKDereferenceExpression dereferenceExpressionWithSpan:span identifiers:yymsp[0].minor.yy41.node]; // yymsp[0].minor.yy41.node is an NSArray of identifier expressions
  }
}
#line 1011 "PKGrammar.c"
        break;
      case 26: /* components ::= components DOT identifier */
      case 33: /* parameters ::= parameters COMMA expression */ yytestcase(yyruleno==33);
#line 242 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    [(NSMutableArray *)(yygotominor.yy41.node = yymsp[-2].minor.yy41.node) addObject:yymsp[0].minor.yy41.node];
  }
}
#line 1021 "PKGrammar.c"
        break;
      case 27: /* components ::= identifier */
      case 34: /* parameters ::= expression */ yytestcase(yyruleno==34);
#line 247 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy41.node = [NSMutableArray arrayWithObject:yymsp[0].minor.yy41.node];
  }
}
#line 1031 "PKGrammar.c"
        break;
      case 28: /* identifier ::= IDENT */
#line 255 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(yymsp[0].minor.yy0.range)];
    yygotominor.yy41.node = [PKIdentifierExpression identifierExpressionWithSpan:span identifier:[NSString stringWithUTF8String:yymsp[0].minor.yy0.value.asString]];
    free((void *)yymsp[0].minor.yy0.value.asString); yymsp[0].minor.yy0.value.asString = NULL;
  }
}
#line 1042 "PKGrammar.c"
        break;
      case 31: /* primary ::= LPAREN expression RPAREN */
#line 275 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy41.node = yymsp[-1].minor.yy41.node;
  }
}
#line 1051 "PKGrammar.c"
        break;
      case 32: /* set ::= LBRACE parameters RBRACE */
#line 283 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSMakeRange(yymsp[-2].minor.yy0.range.location, (yymsp[0].minor.yy0.range.location + yymsp[0].minor.yy0.range.length) - yymsp[-2].minor.yy0.range.location)];
    yygotominor.yy41.node = [PKSetExpression setExpressionWithSpan:span parameters:yymsp[-1].minor.yy41.node];
  }
}
#line 1061 "PKGrammar.c"
        break;
      case 35: /* literal ::= BOOL */
#line 305 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(yymsp[0].minor.yy0.range)];
    yygotominor.yy41.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNumber numberWithBool:yymsp[0].minor.yy0.value.asBool]];
  }
}
#line 1071 "PKGrammar.c"
        break;
      case 36: /* literal ::= NULL */
#line 311 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(yymsp[0].minor.yy0.range)];
    yygotominor.yy41.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNull null]];
  }
}
#line 1081 "PKGrammar.c"
        break;
      case 37: /* literal ::= INT */
#line 317 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(yymsp[0].minor.yy0.range)];
    yygotominor.yy41.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNumber numberWithInt:yymsp[0].minor.yy0.value.asInt]];
  }
}
#line 1091 "PKGrammar.c"
        break;
      case 38: /* literal ::= LONG */
#line 323 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(yymsp[0].minor.yy0.range)];
    yygotominor.yy41.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNumber numberWithLongLong:yymsp[0].minor.yy0.value.asLong]];
  }
}
#line 1101 "PKGrammar.c"
        break;
      case 39: /* literal ::= FLOAT */
#line 329 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(yymsp[0].minor.yy0.range)];
    yygotominor.yy41.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNumber numberWithFloat:yymsp[0].minor.yy0.value.asFloat]];
  }
}
#line 1111 "PKGrammar.c"
        break;
      case 40: /* literal ::= DOUBLE */
#line 335 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(yymsp[0].minor.yy0.range)];
    yygotominor.yy41.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSNumber numberWithDouble:yymsp[0].minor.yy0.value.asDouble]];
  }
}
#line 1121 "PKGrammar.c"
        break;
      case 41: /* literal ::= QUOTED_STRING */
#line 341 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(yymsp[0].minor.yy0.range)];
    yygotominor.yy41.node = [PKLiteralExpression literalExpressionWithSpan:span value:[NSString stringWithUTF8String:yymsp[0].minor.yy0.value.asString]];
    free((void *)yymsp[0].minor.yy0.value.asString); yymsp[0].minor.yy0.value.asString = NULL;
  }
}
#line 1132 "PKGrammar.c"
        break;
      case 42: /* literal ::= REGEX */
#line 348 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(yymsp[0].minor.yy0.range)];
    yygotominor.yy41.node = [PKPatternExpression patternExpressionWithSpan:span pattern:[NSString stringWithUTF8String:yymsp[0].minor.yy0.value.asString]];
    free((void *)yymsp[0].minor.yy0.value.asString); yymsp[0].minor.yy0.value.asString = NULL;
  }
}
#line 1143 "PKGrammar.c"
        break;
      default:
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,(YYCODETYPE)yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = (YYACTIONTYPE)yyact;
      yymsp->major = (YYCODETYPE)yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else{
    assert( yyact == YYNSTATE + YYNRULE + 1 );
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
#ifndef YYNOERRORRECOVERY
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  __PKParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
#line 41 "PKGrammar.y"

  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Confused by errors; bailing out");
    context->state = kPKStateError;
  }
#line 1197 "PKGrammar.c"
  __PKParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}
#endif /* YYNOERRORRECOVERY */

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  __PKParserARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 26 "PKGrammar.y"

  if(context != NULL && context->state != kPKStateError){
    PKSpan *span = [PKSpan spanWithDocument:context->document source:context->source range:NSRangeFromPKRange(TOKEN.range)];
    context->error = NSERROR_WITH_SPAN(PKPredicateErrorDomain, PKStatusError, span, @"Syntax error");
    context->state = kPKStateError;
  }
#line 1219 "PKGrammar.c"
  __PKParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  __PKParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  __PKParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "__PKParserAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void __PKParser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  __PKParserTOKENTYPE yyminor       /* The value for the token */
  __PKParserARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
#ifdef YYERRORSYMBOL
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
#endif
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
#if YYSTACKDEPTH<=0
    if( yypParser->yystksz <=0 ){
      /*memset(&yyminorunion, 0, sizeof(yyminorunion));*/
      yyminorunion = yyzerominor;
      yyStackOverflow(yypParser, &yyminorunion);
      return;
    }
#endif
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  __PKParserARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,(YYCODETYPE)yymajor);
    if( yyact<YYNSTATE ){
      assert( !yyendofinput );  /* Impossible to shift the $ token */
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      yymajor = YYNOCODE;
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else{
      assert( yyact == YY_ERROR_ACTION );
#ifdef YYERRORSYMBOL
      int yymx;
#endif
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yypParser, (YYCODETYPE)yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_reduce_action(
                        yypParser->yystack[yypParser->yyidx].stateno,
                        YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#elif defined(YYNOERRORRECOVERY)
      /* If the YYNOERRORRECOVERY macro is defined, then do not attempt to
      ** do any kind of error recovery.  Instead, simply invoke the syntax
      ** error routine and continue going as if nothing had happened.
      **
      ** Applications can set this macro (for example inside %include) if
      ** they intend to abandon the parse upon the first syntax error seen.
      */
      yy_syntax_error(yypParser,yymajor,yyminorunion);
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      yymajor = YYNOCODE;
      
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yypParser,(YYCODETYPE)yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
