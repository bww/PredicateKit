
#import <stdint.h>
#import "PKPredicate.h"

/* Values */

typedef union {
  uint8_t       asBool;
  uint8_t       asByte;
  int32_t       asInt;
  int64_t       asLong;
  float         asFloat;
  double        asDouble;
  const char  * asString;
} PKValue;

/* Range */

typedef struct PKRange {
  unsigned int location;
  unsigned int length;
} PKRange;

static inline PKRange PKRangeMake(unsigned int location, unsigned int length) {
  return (PKRange){ location, length };
}

static inline PKRange PKRangeMakeZero() {
  PKRange zero;
  bzero(&zero, sizeof(PKRange));
  return zero;
}

/* Token */

typedef struct PKToken {
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

typedef struct PKScannerContext {
  unsigned int    location;
  unsigned int    line;
  unsigned int    column;
} PKScannerContext;

#if !defined(YY_EXTRA_TYPE)
#define YY_EXTRA_TYPE PKScannerContext *
#endif

static inline PKScannerContext PKScannerContextMake(unsigned int location, unsigned int line, unsigned int column) {
  return (PKScannerContext){ location, line, column };
}

static inline PKScannerContext PKScannerContextMakeZero() {
  PKScannerContext zero;
  bzero(&zero, sizeof(PKScannerContext));
  return zero;
}

/* Parser State */

typedef enum {
  kPKParserStateOk,
  kPKParserStateFinished,
  kPKParserStateError
} PKParserState;

/* Parser Context */

typedef struct PKParserContext {
  PKParserState   state;
  PKPredicate   * predicate;
  NSError       * error;
} PKParserContext;

static inline PKParserContext PKParserContextMakeError(NSError *error) {
  return (PKParserContext){ kPKParserStateError, nil, error };
}

static inline PKParserContext PKParserContextMakePredicate(PKPredicate *predicate) {
  return (PKParserContext){ kPKParserStateFinished, predicate, nil };
}

static inline PKParserContext PKParserContextMakeZero() {
  PKParserContext zero;
  bzero(&zero, sizeof(PKParserContext));
  return zero;
}


