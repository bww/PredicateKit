
#import <stdint.h>
#import "PKPredicate.h"

/* Match/Replace */

typedef struct {
  const char  * pattern;
  const char  * replace;
} PKMatchReplace;

/* Values */

typedef union {
  uint8_t         asBool;
  uint8_t         asByte;
  int32_t         asInt;
  int64_t         asLong;
  float           asFloat;
  double          asDouble;
  const char    * asString;
  PKMatchReplace  asMatchReplace;
} PKValue;

/* Range */

typedef struct {
  unsigned int location;
  unsigned int length;
} PKRange;

static inline PKRange PKRangeMake(unsigned int location, unsigned int length) {
  return (PKRange){ location, length };
}

static inline NSRange NSRangeFromPKRange(PKRange range) {
  return NSMakeRange(range.location, range.length);
}

/* State */

typedef enum {
  kPKStateOk,
  kPKStateFinished,
  kPKStateError
} PKState;

/* Token */

typedef struct {
  unsigned int  token;
  PKValue       value;
  PKRange       range;
  void        * node;
} PKToken;

static inline PKToken PKTokenMake(unsigned int token, PKValue value, PKRange range) {
  return (PKToken){ token, value, range, NULL };
}

static inline PKToken PKTokenMakeZero() {
  PKValue value;
  bzero(&value, sizeof(PKValue));
  return (PKToken){ 0, value, 0, 0, NULL };
}

/* Scanner Context */

typedef struct {
  NSURL         * document;
  NSString      * source;
  PKState         state;
  NSError       * error;
  unsigned int    location;
  unsigned int    line;
  unsigned int    column;
} PKScannerContext;

#if !defined(YY_EXTRA_TYPE)
#define YY_EXTRA_TYPE PKScannerContext *
#endif

static inline PKScannerContext PKScannerContextMakeZero() {
  PKScannerContext zero;
  bzero(&zero, sizeof(PKScannerContext));
  return zero;
}

/* Parser Context */

typedef struct {
  NSURL         * document;
  NSString      * source;
  PKState         state;
  PKExpression  * expression;
  NSError       * error;
} PKParserContext;

static inline PKParserContext PKParserContextMakeZero() {
  PKParserContext zero;
  bzero(&zero, sizeof(PKParserContext));
  return zero;
}


