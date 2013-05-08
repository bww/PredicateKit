
#import <stdint.h>

typedef union {
  uint8_t       asBool;
  uint8_t       asByte;
  int32_t       asInt;
  int64_t       asLong;
  float         asFloat;
  double        asDouble;
  const char  * asString;
} PKValue;

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

typedef struct PKContext {
  unsigned int  location;
  unsigned int  line;
  unsigned int  column;
} PKContext;

#if !defined(YY_EXTRA_TYPE)
#define YY_EXTRA_TYPE PKContext *
#endif

static inline PKContext PKContextMake(unsigned int location, unsigned int line, unsigned int column) {
  return (PKContext){ location, line, column };
}

static inline PKContext PKContextMakeZero() {
  PKContext zero;
  bzero(&zero, sizeof(PKContext));
  return zero;
}

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

