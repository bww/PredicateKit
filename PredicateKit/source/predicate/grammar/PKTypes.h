
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

typedef struct PKContext {
  unsigned int  line;
  unsigned int  column;
} PKContext;

#if !defined(YY_EXTRA_TYPE)
#define YY_EXTRA_TYPE PKContext *
#endif

typedef struct PKToken {
  unsigned int  token;
  PKValue       value;
  unsigned int  line;
  unsigned int  column;
  void        * node;
} PKToken;

static inline PKToken PKTokenMake(unsigned int token, PKValue value) {
  return (PKToken){ token, value, 0, 0, NULL };
}

static inline PKToken PKTokenMakeZero() {
  PKValue value;
  bzero(&value, sizeof(PKValue));
  return (PKToken){ 0, value, 0, 0, NULL };
}

