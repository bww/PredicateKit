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
#include "PKLiteralExpression.h"
#include "PKPatternExpression.h"
#include "PKExpressionModifier.h"
#line 22 "PKGrammar.c"
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
#define YYNOCODE 55
#define YYACTIONTYPE unsigned char
#define __PKParserTOKENTYPE  PKToken 
typedef union {
  int yyinit;
  __PKParserTOKENTYPE yy0;
  PKToken yy89;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define __PKParserARG_SDECL  PKParserContext *context ;
#define __PKParserARG_PDECL , PKParserContext *context 
#define __PKParserARG_FETCH  PKParserContext *context  = yypParser->context 
#define __PKParserARG_STORE yypParser->context  = context 
#define YYNSTATE 65
#define YYNRULE 41
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
#define YY_ACTTAB_COUNT (204)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */     3,   65,    1,    7,    8,    6,   17,   18,   43,   64,
 /*    10 */    23,   21,   31,   20,   19,   25,   57,   56,   55,   22,
 /*    20 */    63,   21,   31,   20,   19,   25,   57,   56,   55,   46,
 /*    30 */    30,   52,   51,   50,   49,   48,   47,   45,   44,  107,
 /*    40 */    32,   64,   23,   21,   31,   20,   19,   25,   57,   56,
 /*    50 */    55,    3,   61,    1,   24,   64,   23,   21,   31,   20,
 /*    60 */    19,   25,   57,   56,   55,   33,   21,   31,   20,   19,
 /*    70 */    25,   57,   56,   55,   60,   19,   25,   57,   56,   55,
 /*    80 */    46,   29,   52,   51,   50,   49,   48,   47,   45,   44,
 /*    90 */    53,   64,   23,   21,   31,   20,   19,   25,   57,   56,
 /*   100 */    55,   62,   31,   20,   19,   25,   57,   56,   55,   35,
 /*   110 */    31,   20,   19,   25,   57,   56,   55,   34,   31,   20,
 /*   120 */    19,   25,   57,   56,   55,   38,   19,   25,   57,   56,
 /*   130 */    55,   37,   19,   25,   57,   56,   55,   36,   19,   25,
 /*   140 */    57,   56,   55,   59,   25,   57,   56,   55,   41,   25,
 /*   150 */    57,   56,   55,   40,   25,   57,   56,   55,   39,   25,
 /*   160 */    57,   56,   55,   12,   11,   28,   57,   56,   55,   10,
 /*   170 */    16,   15,   14,   13,    5,    4,   54,    9,   26,   57,
 /*   180 */    56,   55,   27,   42,  108,   58,  108,  108,  108,  108,
 /*   190 */   108,  108,  108,  108,  108,  108,  108,  108,  108,  108,
 /*   200 */   108,  108,  108,    2,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    0,    3,   11,   12,   13,    7,    8,   42,   43,
 /*    10 */    44,   45,   46,   47,   48,   49,   50,   51,   52,   53,
 /*    20 */    44,   45,   46,   47,   48,   49,   50,   51,   52,   30,
 /*    30 */     5,   32,   33,   34,   35,   36,   37,   38,   39,   41,
 /*    40 */    42,   43,   44,   45,   46,   47,   48,   49,   50,   51,
 /*    50 */    52,    1,    6,    3,   42,   43,   44,   45,   46,   47,
 /*    60 */    48,   49,   50,   51,   52,   44,   45,   46,   47,   48,
 /*    70 */    49,   50,   51,   52,   47,   48,   49,   50,   51,   52,
 /*    80 */    30,   27,   32,   33,   34,   35,   36,   37,   38,   39,
 /*    90 */    42,   43,   44,   45,   46,   47,   48,   49,   50,   51,
 /*   100 */    52,   45,   46,   47,   48,   49,   50,   51,   52,   45,
 /*   110 */    46,   47,   48,   49,   50,   51,   52,   45,   46,   47,
 /*   120 */    48,   49,   50,   51,   52,   47,   48,   49,   50,   51,
 /*   130 */    52,   47,   48,   49,   50,   51,   52,   47,   48,   49,
 /*   140 */    50,   51,   52,   48,   49,   50,   51,   52,   48,   49,
 /*   150 */    50,   51,   52,   48,   49,   50,   51,   52,   48,   49,
 /*   160 */    50,   51,   52,   14,   15,   49,   50,   51,   52,   20,
 /*   170 */    16,   17,   18,   19,    9,   10,    4,   28,   49,   50,
 /*   180 */    51,   52,   29,    2,   54,   30,   54,   54,   54,   54,
 /*   190 */    54,   54,   54,   54,   54,   54,   54,   54,   54,   54,
 /*   200 */    54,   54,   54,   31,
};
#define YY_SHIFT_USE_DFLT (-9)
#define YY_SHIFT_COUNT (32)
#define YY_SHIFT_MIN   (-8)
#define YY_SHIFT_MAX   (181)
static const short yy_shift_ofst[] = {
 /*     0 */    -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
 /*    10 */    -1,   -1,   -1,   -1,   -1,   -1,   -1,   50,   50,  154,
 /*    20 */   149,   -8,  172,  165,  181,  153,  153,  155,  153,   46,
 /*    30 */    54,   25,    1,
};
#define YY_REDUCE_USE_DFLT (-35)
#define YY_REDUCE_COUNT (18)
#define YY_REDUCE_MIN   (-34)
#define YY_REDUCE_MAX   (129)
static const short yy_reduce_ofst[] = {
 /*     0 */    -2,  -34,   48,   12,   21,  -24,   72,   64,   56,   90,
 /*    10 */    84,   78,   27,  110,  105,  100,   95,  129,  116,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   106,  106,  106,  106,  106,  106,  106,  106,  106,  106,
 /*    10 */   106,  106,  106,  106,  106,  106,  106,  106,  106,   85,
 /*    20 */    80,   73,  106,   69,  106,   88,   87,  106,   86,  106,
 /*    30 */   106,   75,  106,   68,   72,   71,   79,   78,   77,   84,
 /*    40 */    83,   82,   93,   96,  105,  104,  103,  102,  101,  100,
 /*    50 */    99,   98,   97,   95,   94,   92,   91,   90,   89,   81,
 /*    60 */    76,   74,   70,   67,   66,
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
  "unary",         "dereference",   "primary",       "literal",     
  "collection",    "parameters",  
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
 /*  24 */ "dereference ::= dereference DOT IDENT",
 /*  25 */ "dereference ::= primary",
 /*  26 */ "primary ::= literal",
 /*  27 */ "primary ::= collection",
 /*  28 */ "primary ::= LPAREN expression RPAREN",
 /*  29 */ "collection ::= LBRACE parameters RBRACE",
 /*  30 */ "parameters ::= parameters COMMA expression",
 /*  31 */ "parameters ::= expression",
 /*  32 */ "literal ::= BOOL",
 /*  33 */ "literal ::= NULL",
 /*  34 */ "literal ::= INT",
 /*  35 */ "literal ::= LONG",
 /*  36 */ "literal ::= FLOAT",
 /*  37 */ "literal ::= DOUBLE",
 /*  38 */ "literal ::= IDENT",
 /*  39 */ "literal ::= QUOTED_STRING",
 /*  40 */ "literal ::= REGEX",
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
#line 37 "PKGrammar.y"

  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Stack overvlow.");
    context->state = kPKStateError;
  }
#line 648 "PKGrammar.c"
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
  { 49, 3 },
  { 49, 1 },
  { 50, 1 },
  { 50, 1 },
  { 50, 3 },
  { 52, 3 },
  { 53, 3 },
  { 53, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
  { 51, 1 },
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
#line 61 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    context->expression = yymsp[0].minor.yy89.node;
    context->state = kPKStateFinished;
  }
}
#line 808 "PKGrammar.c"
        break;
      case 1: /* expression ::= logical */
      case 4: /* logical ::= bitwise */ yytestcase(yyruleno==4);
      case 8: /* bitwise ::= modified */ yytestcase(yyruleno==8);
      case 10: /* modified ::= equality */ yytestcase(yyruleno==10);
      case 15: /* equality ::= relational */ yytestcase(yyruleno==15);
      case 20: /* relational ::= unary */ yytestcase(yyruleno==20);
      case 23: /* unary ::= dereference */ yytestcase(yyruleno==23);
      case 25: /* dereference ::= primary */ yytestcase(yyruleno==25);
      case 26: /* primary ::= literal */ yytestcase(yyruleno==26);
#line 70 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = yymsp[0].minor.yy89.node;
  }
}
#line 825 "PKGrammar.c"
        break;
      case 2: /* logical ::= bitwise LAND bitwise */
#line 78 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKLogicalExpression compoundExpressionWithType:kPKLogicalAnd expressions:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 834 "PKGrammar.c"
        break;
      case 3: /* logical ::= bitwise LOR bitwise */
#line 83 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKLogicalExpression compoundExpressionWithType:kPKLogicalOr expressions:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 843 "PKGrammar.c"
        break;
      case 5: /* bitwise ::= modified BOR modified */
#line 96 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseOr operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 852 "PKGrammar.c"
        break;
      case 6: /* bitwise ::= modified BAND modified */
#line 101 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseAnd operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 861 "PKGrammar.c"
        break;
      case 7: /* bitwise ::= modified BXOR modified */
#line 106 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseExclusiveOr operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 870 "PKGrammar.c"
        break;
      case 9: /* modified ::= equality LBRACK MODIFIER RBRACK */
#line 119 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    PKExpressionModifier *modifier = [PKExpressionModifier expressionModifierWithFlags:yymsp[-1].minor.yy0.value.asString];
    if(yymsp[-1].minor.yy0.value.asString) free((void *)yymsp[-1].minor.yy0.value.asString);
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Language feature is not supported.");
    context->state = kPKStateError;
  }
}
#line 882 "PKGrammar.c"
        break;
      case 11: /* equality ::= relational EQ relational */
#line 135 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 891 "PKGrammar.c"
        break;
      case 12: /* equality ::= relational NE relational */
#line 140 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonNotEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 900 "PKGrammar.c"
        break;
      case 13: /* equality ::= relational MATCH relational */
#line 145 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonMatches operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 909 "PKGrammar.c"
        break;
      case 14: /* equality ::= relational IN relational */
#line 150 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonIn operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 918 "PKGrammar.c"
        break;
      case 16: /* relational ::= unary GT unary */
#line 163 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonGreaterThan operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 927 "PKGrammar.c"
        break;
      case 17: /* relational ::= unary GE unary */
#line 168 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonGreaterThanOrEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 936 "PKGrammar.c"
        break;
      case 18: /* relational ::= unary LT unary */
#line 173 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonLessThan operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 945 "PKGrammar.c"
        break;
      case 19: /* relational ::= unary LE unary */
#line 178 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonLessThanOrEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy89.node, yymsp[0].minor.yy89.node, nil]];
  }
}
#line 954 "PKGrammar.c"
        break;
      case 21: /* unary ::= BNOT dereference */
#line 191 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseNot operands:[NSArray arrayWithObjects:yymsp[0].minor.yy89.node, nil]];
  }
}
#line 963 "PKGrammar.c"
        break;
      case 22: /* unary ::= LNOT dereference */
#line 196 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKLogicalExpression compoundExpressionWithType:kPKLogicalNot expressions:[NSArray arrayWithObjects:yymsp[0].minor.yy89.node, nil]];
  }
}
#line 972 "PKGrammar.c"
        break;
      case 24: /* dereference ::= dereference DOT IDENT */
      case 29: /* collection ::= LBRACE parameters RBRACE */ yytestcase(yyruleno==29);
      case 30: /* parameters ::= parameters COMMA expression */ yytestcase(yyruleno==30);
      case 31: /* parameters ::= expression */ yytestcase(yyruleno==31);
#line 209 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Language feature is not supported.");
    context->state = kPKStateError;
  }
}
#line 985 "PKGrammar.c"
        break;
      case 28: /* primary ::= LPAREN expression RPAREN */
#line 229 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = yymsp[-1].minor.yy89.node;
  }
}
#line 994 "PKGrammar.c"
        break;
      case 32: /* literal ::= BOOL */
#line 261 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithBool:yymsp[0].minor.yy0.value.asBool]];
  }
}
#line 1003 "PKGrammar.c"
        break;
      case 33: /* literal ::= NULL */
#line 266 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKLiteralExpression literalExpressionWithValue:[NSNull null]];
  }
}
#line 1012 "PKGrammar.c"
        break;
      case 34: /* literal ::= INT */
#line 271 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithInt:yymsp[0].minor.yy0.value.asInt]];
  }
}
#line 1021 "PKGrammar.c"
        break;
      case 35: /* literal ::= LONG */
#line 276 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithLongLong:yymsp[0].minor.yy0.value.asLong]];
  }
}
#line 1030 "PKGrammar.c"
        break;
      case 36: /* literal ::= FLOAT */
#line 281 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithFloat:yymsp[0].minor.yy0.value.asFloat]];
  }
}
#line 1039 "PKGrammar.c"
        break;
      case 37: /* literal ::= DOUBLE */
#line 286 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithDouble:yymsp[0].minor.yy0.value.asDouble]];
  }
}
#line 1048 "PKGrammar.c"
        break;
      case 38: /* literal ::= IDENT */
#line 291 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKIdentifierExpression identifierExpressionWithIdentifier:[NSString stringWithUTF8String:yymsp[0].minor.yy0.value.asString]];
    free((void *)yymsp[0].minor.yy0.value.asString); yymsp[0].minor.yy0.value.asString = NULL;
  }
}
#line 1058 "PKGrammar.c"
        break;
      case 39: /* literal ::= QUOTED_STRING */
#line 297 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKLiteralExpression literalExpressionWithValue:[NSString stringWithUTF8String:yymsp[0].minor.yy0.value.asString]];
    free((void *)yymsp[0].minor.yy0.value.asString); yymsp[0].minor.yy0.value.asString = NULL;
  }
}
#line 1068 "PKGrammar.c"
        break;
      case 40: /* literal ::= REGEX */
#line 303 "PKGrammar.y"
{
  if(context != NULL && context->state != kPKStateError){
    yygotominor.yy89.node = [PKPatternExpression patternExpressionWithPattern:[NSString stringWithUTF8String:yymsp[0].minor.yy0.value.asString]];
    free((void *)yymsp[0].minor.yy0.value.asString); yymsp[0].minor.yy0.value.asString = NULL;
  }
}
#line 1078 "PKGrammar.c"
        break;
      default:
      /* (27) primary ::= collection */ yytestcase(yyruleno==27);
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
#line 23 "PKGrammar.y"

  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Confused by errors; bailing out.");
    context->state = kPKStateError;
  }
#line 1133 "PKGrammar.c"
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
#line 30 "PKGrammar.y"

  if(context != NULL && context->state != kPKStateError){
    context->error = NSERROR(PKPredicateErrorDomain, PKStatusError, @"Syntax error.");
    context->state = kPKStateError;
  }
#line 1154 "PKGrammar.c"
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
