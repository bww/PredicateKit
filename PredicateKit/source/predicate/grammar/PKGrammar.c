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
#include "PKPredicate.h"
#include "PKCompoundExpression.h"
#include "PKBitwiseExpression.h"
#include "PKComparisonExpression.h"
#include "PKIdentifierExpression.h"
#include "PKLiteralExpression.h"
#line 20 "PKGrammar.c"
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
#define YYNOCODE 51
#define YYACTIONTYPE unsigned char
#define __PKParserTOKENTYPE  PKToken 
typedef union {
  int yyinit;
  __PKParserTOKENTYPE yy0;
  PKToken yy53;
} YYMINORTYPE;
#ifndef YYSTACKDEPTH
#define YYSTACKDEPTH 100
#endif
#define __PKParserARG_SDECL  PKPredicate **context ;
#define __PKParserARG_PDECL , PKPredicate **context 
#define __PKParserARG_FETCH  PKPredicate **context  = yypParser->context 
#define __PKParserARG_STORE yypParser->context  = context 
#define YYNSTATE 62
#define YYNRULE 38
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
#define YY_ACTTAB_COUNT (184)
static const YYACTIONTYPE yy_action[] = {
 /*     0 */     3,   52,    1,    7,    8,    6,   17,   18,   43,   23,
 /*    10 */    21,   31,   20,   19,   25,   55,   54,   53,   22,   58,
 /*    20 */    19,   25,   55,   54,   53,   62,   45,    2,    5,    4,
 /*    30 */    50,   49,   48,   47,   46,   44,  101,   32,   23,   21,
 /*    40 */    31,   20,   19,   25,   55,   54,   53,   24,   23,   21,
 /*    50 */    31,   20,   19,   25,   55,   54,   53,   51,   23,   21,
 /*    60 */    31,   20,   19,   25,   55,   54,   53,    3,   30,    1,
 /*    70 */    29,   61,   21,   31,   20,   19,   25,   55,   54,   53,
 /*    80 */    33,   21,   31,   20,   19,   25,   55,   54,   53,   16,
 /*    90 */    15,   14,   13,   45,   27,   59,   56,   50,   49,   48,
 /*   100 */    47,   46,   44,   60,   31,   20,   19,   25,   55,   54,
 /*   110 */    53,   35,   31,   20,   19,   25,   55,   54,   53,   34,
 /*   120 */    31,   20,   19,   25,   55,   54,   53,   38,   19,   25,
 /*   130 */    55,   54,   53,   28,   55,   54,   53,   37,   19,   25,
 /*   140 */    55,   54,   53,   36,   19,   25,   55,   54,   53,   57,
 /*   150 */    25,   55,   54,   53,   41,   25,   55,   54,   53,   40,
 /*   160 */    25,   55,   54,   53,   39,   25,   55,   54,   53,   12,
 /*   170 */    11,   26,   55,   54,   53,   10,   42,  102,  102,  102,
 /*   180 */   102,  102,  102,    9,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */     1,    4,    3,   11,   12,   13,    7,    8,   39,   40,
 /*    10 */    41,   42,   43,   44,   45,   46,   47,   48,   49,   43,
 /*    20 */    44,   45,   46,   47,   48,    0,   27,   30,    9,   10,
 /*    30 */    31,   32,   33,   34,   35,   36,   38,   39,   40,   41,
 /*    40 */    42,   43,   44,   45,   46,   47,   48,   39,   40,   41,
 /*    50 */    42,   43,   44,   45,   46,   47,   48,   39,   40,   41,
 /*    60 */    42,   43,   44,   45,   46,   47,   48,    1,    5,    3,
 /*    70 */    27,   40,   41,   42,   43,   44,   45,   46,   47,   48,
 /*    80 */    40,   41,   42,   43,   44,   45,   46,   47,   48,   16,
 /*    90 */    17,   18,   19,   27,   29,    6,   27,   31,   32,   33,
 /*   100 */    34,   35,   36,   41,   42,   43,   44,   45,   46,   47,
 /*   110 */    48,   41,   42,   43,   44,   45,   46,   47,   48,   41,
 /*   120 */    42,   43,   44,   45,   46,   47,   48,   43,   44,   45,
 /*   130 */    46,   47,   48,   45,   46,   47,   48,   43,   44,   45,
 /*   140 */    46,   47,   48,   43,   44,   45,   46,   47,   48,   44,
 /*   150 */    45,   46,   47,   48,   44,   45,   46,   47,   48,   44,
 /*   160 */    45,   46,   47,   48,   44,   45,   46,   47,   48,   14,
 /*   170 */    15,   45,   46,   47,   48,   20,    2,   50,   50,   50,
 /*   180 */    50,   50,   50,   28,
};
#define YY_SHIFT_USE_DFLT (-9)
#define YY_SHIFT_COUNT (32)
#define YY_SHIFT_MIN   (-8)
#define YY_SHIFT_MAX   (174)
static const short yy_shift_ofst[] = {
 /*     0 */    -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
 /*    10 */    -1,   -1,   -1,   -1,   -1,   -1,   -1,   66,   66,   73,
 /*    20 */   155,   -8,   -3,   19,  174,   65,   65,   69,   65,   89,
 /*    30 */    43,   63,   25,
};
#define YY_REDUCE_USE_DFLT (-32)
#define YY_REDUCE_COUNT (18)
#define YY_REDUCE_MIN   (-31)
#define YY_REDUCE_MAX   (126)
static const signed char yy_reduce_ofst[] = {
 /*     0 */    -2,  -31,   18,    8,   40,   31,   78,   70,   62,  100,
 /*    10 */    94,   84,  -24,  120,  115,  110,  105,  126,   88,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   100,  100,  100,  100,  100,  100,  100,  100,  100,  100,
 /*    10 */   100,  100,  100,  100,  100,  100,  100,  100,  100,   81,
 /*    20 */    76,   69,  100,   65,  100,   84,   83,  100,   82,  100,
 /*    30 */   100,   71,  100,   64,   68,   67,   75,   74,   73,   80,
 /*    40 */    79,   78,   89,   92,   99,   98,   97,   96,   95,   94,
 /*    50 */    93,   91,   90,   88,   87,   86,   85,   77,   72,   70,
 /*    60 */    66,   63,
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
  "DIV",           "MOD",           "EXP",           "IDENT",       
  "IN",            "DOT",           "COMMA",         "BOOL",        
  "INT",           "LONG",          "FLOAT",         "DOUBLE",      
  "QUOTED_STRING",  "error",         "predicate",     "expression",  
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
 /*   1 */ "expression ::= bitwise LAND bitwise",
 /*   2 */ "expression ::= bitwise LOR bitwise",
 /*   3 */ "expression ::= bitwise",
 /*   4 */ "bitwise ::= modified BOR modified",
 /*   5 */ "bitwise ::= modified BAND modified",
 /*   6 */ "bitwise ::= modified BXOR modified",
 /*   7 */ "bitwise ::= modified",
 /*   8 */ "modified ::= equality LBRACK IDENT RBRACK",
 /*   9 */ "modified ::= equality",
 /*  10 */ "equality ::= relational EQ relational",
 /*  11 */ "equality ::= relational NE relational",
 /*  12 */ "equality ::= relational MATCH relational",
 /*  13 */ "equality ::= relational IN relational",
 /*  14 */ "equality ::= relational",
 /*  15 */ "relational ::= unary GT unary",
 /*  16 */ "relational ::= unary GE unary",
 /*  17 */ "relational ::= unary LT unary",
 /*  18 */ "relational ::= unary LE unary",
 /*  19 */ "relational ::= unary",
 /*  20 */ "unary ::= BNOT dereference",
 /*  21 */ "unary ::= LNOT dereference",
 /*  22 */ "unary ::= dereference",
 /*  23 */ "dereference ::= dereference DOT IDENT",
 /*  24 */ "dereference ::= primary",
 /*  25 */ "primary ::= literal",
 /*  26 */ "primary ::= collection",
 /*  27 */ "primary ::= LPAREN expression RPAREN",
 /*  28 */ "collection ::= LBRACE parameters RBRACE",
 /*  29 */ "parameters ::= parameters COMMA expression",
 /*  30 */ "parameters ::= expression",
 /*  31 */ "literal ::= BOOL",
 /*  32 */ "literal ::= INT",
 /*  33 */ "literal ::= LONG",
 /*  34 */ "literal ::= FLOAT",
 /*  35 */ "literal ::= DOUBLE",
 /*  36 */ "literal ::= IDENT",
 /*  37 */ "literal ::= QUOTED_STRING",
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

  context = context;
  fprintf(stderr,"Giving up.  Parser stack overflow\n");
#line 636 "PKGrammar.c"
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
  { 38, 1 },
  { 39, 3 },
  { 39, 3 },
  { 39, 1 },
  { 40, 3 },
  { 40, 3 },
  { 40, 3 },
  { 40, 1 },
  { 41, 4 },
  { 41, 1 },
  { 42, 3 },
  { 42, 3 },
  { 42, 3 },
  { 42, 3 },
  { 42, 1 },
  { 43, 3 },
  { 43, 3 },
  { 43, 3 },
  { 43, 3 },
  { 43, 1 },
  { 44, 2 },
  { 44, 2 },
  { 44, 1 },
  { 45, 3 },
  { 45, 1 },
  { 46, 1 },
  { 46, 1 },
  { 46, 3 },
  { 48, 3 },
  { 49, 3 },
  { 49, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
  { 47, 1 },
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
#line 54 "PKGrammar.y"
{
  if(context != NULL) *context = (PKPredicate *)yymsp[0].minor.yy53.node;
}
#line 790 "PKGrammar.c"
        break;
      case 1: /* expression ::= bitwise LAND bitwise */
#line 58 "PKGrammar.y"
{ yygotominor.yy53.node = [PKCompoundExpression compoundExpressionWithType:kPKCompoundAnd expressions:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 795 "PKGrammar.c"
        break;
      case 2: /* expression ::= bitwise LOR bitwise */
#line 59 "PKGrammar.y"
{ yygotominor.yy53.node = [PKCompoundExpression compoundExpressionWithType:kPKCompoundOr expressions:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 800 "PKGrammar.c"
        break;
      case 3: /* expression ::= bitwise */
      case 7: /* bitwise ::= modified */ yytestcase(yyruleno==7);
      case 9: /* modified ::= equality */ yytestcase(yyruleno==9);
      case 14: /* equality ::= relational */ yytestcase(yyruleno==14);
      case 19: /* relational ::= unary */ yytestcase(yyruleno==19);
      case 22: /* unary ::= dereference */ yytestcase(yyruleno==22);
      case 24: /* dereference ::= primary */ yytestcase(yyruleno==24);
      case 25: /* primary ::= literal */ yytestcase(yyruleno==25);
#line 60 "PKGrammar.y"
{ yygotominor.yy53.node = yymsp[0].minor.yy53.node; }
#line 812 "PKGrammar.c"
        break;
      case 4: /* bitwise ::= modified BOR modified */
#line 62 "PKGrammar.y"
{ yygotominor.yy53.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseOr operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 817 "PKGrammar.c"
        break;
      case 5: /* bitwise ::= modified BAND modified */
#line 63 "PKGrammar.y"
{ yygotominor.yy53.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseAnd operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 822 "PKGrammar.c"
        break;
      case 6: /* bitwise ::= modified BXOR modified */
#line 64 "PKGrammar.y"
{ yygotominor.yy53.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseExclusiveOr operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 827 "PKGrammar.c"
        break;
      case 10: /* equality ::= relational EQ relational */
#line 70 "PKGrammar.y"
{ yygotominor.yy53.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 832 "PKGrammar.c"
        break;
      case 11: /* equality ::= relational NE relational */
#line 71 "PKGrammar.y"
{ yygotominor.yy53.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonNotEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 837 "PKGrammar.c"
        break;
      case 12: /* equality ::= relational MATCH relational */
#line 72 "PKGrammar.y"
{ yygotominor.yy53.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonMatches operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 842 "PKGrammar.c"
        break;
      case 13: /* equality ::= relational IN relational */
#line 73 "PKGrammar.y"
{ yygotominor.yy53.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonIn operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 847 "PKGrammar.c"
        break;
      case 15: /* relational ::= unary GT unary */
#line 76 "PKGrammar.y"
{ yygotominor.yy53.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonGreaterThan operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 852 "PKGrammar.c"
        break;
      case 16: /* relational ::= unary GE unary */
#line 77 "PKGrammar.y"
{ yygotominor.yy53.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonGreaterThanOrEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 857 "PKGrammar.c"
        break;
      case 17: /* relational ::= unary LT unary */
#line 78 "PKGrammar.y"
{ yygotominor.yy53.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonLessThan operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 862 "PKGrammar.c"
        break;
      case 18: /* relational ::= unary LE unary */
#line 79 "PKGrammar.y"
{ yygotominor.yy53.node = [PKComparisonExpression comparisonExpressionWithType:kPKComparisonLessThanOrEqualTo operands:[NSArray arrayWithObjects:yymsp[-2].minor.yy53.node, yymsp[0].minor.yy53.node, nil]]; }
#line 867 "PKGrammar.c"
        break;
      case 20: /* unary ::= BNOT dereference */
#line 82 "PKGrammar.y"
{ yygotominor.yy53.node = [PKBitwiseExpression bitwiseExpressionWithType:kPKBitwiseNot operands:[NSArray arrayWithObjects:yymsp[0].minor.yy53.node, nil]]; }
#line 872 "PKGrammar.c"
        break;
      case 21: /* unary ::= LNOT dereference */
#line 83 "PKGrammar.y"
{ yygotominor.yy53.node = [PKCompoundExpression compoundExpressionWithType:kPKCompoundNot expressions:[NSArray arrayWithObjects:yymsp[0].minor.yy53.node, nil]]; }
#line 877 "PKGrammar.c"
        break;
      case 23: /* dereference ::= dereference DOT IDENT */
#line 86 "PKGrammar.y"
{  }
#line 882 "PKGrammar.c"
        break;
      case 27: /* primary ::= LPAREN expression RPAREN */
#line 91 "PKGrammar.y"
{ yygotominor.yy53.node = yymsp[-1].minor.yy53.node; }
#line 887 "PKGrammar.c"
        break;
      case 31: /* literal ::= BOOL */
#line 98 "PKGrammar.y"
{ yygotominor.yy53.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithBool:yymsp[0].minor.yy0.value.asBool]]; }
#line 892 "PKGrammar.c"
        break;
      case 32: /* literal ::= INT */
#line 99 "PKGrammar.y"
{ yygotominor.yy53.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithInt:yymsp[0].minor.yy0.value.asInt]]; }
#line 897 "PKGrammar.c"
        break;
      case 33: /* literal ::= LONG */
#line 100 "PKGrammar.y"
{ yygotominor.yy53.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithLongLong:yymsp[0].minor.yy0.value.asLong]]; }
#line 902 "PKGrammar.c"
        break;
      case 34: /* literal ::= FLOAT */
#line 101 "PKGrammar.y"
{ yygotominor.yy53.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithFloat:yymsp[0].minor.yy0.value.asFloat]]; }
#line 907 "PKGrammar.c"
        break;
      case 35: /* literal ::= DOUBLE */
#line 102 "PKGrammar.y"
{ yygotominor.yy53.node = [PKLiteralExpression literalExpressionWithValue:[NSNumber numberWithDouble:yymsp[0].minor.yy0.value.asDouble]]; }
#line 912 "PKGrammar.c"
        break;
      case 36: /* literal ::= IDENT */
#line 104 "PKGrammar.y"
{
  yygotominor.yy53.node = [PKIdentifierExpression identifierExpressionWithIdentifier:[NSString stringWithUTF8String:yymsp[0].minor.yy0.value.asString]];
  free((void *)yymsp[0].minor.yy0.value.asString);
  yymsp[0].minor.yy0.value.asString = NULL;
}
#line 921 "PKGrammar.c"
        break;
      case 37: /* literal ::= QUOTED_STRING */
#line 110 "PKGrammar.y"
{
  yygotominor.yy53.node = [PKLiteralExpression literalExpressionWithValue:[NSString stringWithUTF8String:yymsp[0].minor.yy0.value.asString]];
  free((void *)yymsp[0].minor.yy0.value.asString);
  yymsp[0].minor.yy0.value.asString = NULL;
}
#line 930 "PKGrammar.c"
        break;
      default:
      /* (8) modified ::= equality LBRACK IDENT RBRACK */ yytestcase(yyruleno==8);
      /* (26) primary ::= collection */ yytestcase(yyruleno==26);
      /* (28) collection ::= LBRACE parameters RBRACE */ yytestcase(yyruleno==28);
      /* (29) parameters ::= parameters COMMA expression */ yytestcase(yyruleno==29);
      /* (30) parameters ::= expression */ yytestcase(yyruleno==30);
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
#line 25 "PKGrammar.y"

  fprintf(stderr,"Giving up.  Parser is hopelessly lost...\n");
#line 986 "PKGrammar.c"
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
#line 29 "PKGrammar.y"

  context = context;
  fprintf(stderr, "Syntax error: %d\n", TOKEN.token);
#line 1005 "PKGrammar.c"
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
#line 21 "PKGrammar.y"

  // ...
#line 1027 "PKGrammar.c"
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
