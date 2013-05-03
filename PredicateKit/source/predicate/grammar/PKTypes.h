
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

typedef struct PKToken {
  unsigned int  token;
  PKValue       value;
  void        * node;
} PKToken;

static inline PKToken PKTokenMake(unsigned int token, PKValue value) {
  return (PKToken){ token, value, NULL };
}

static inline PKToken PKTokenMakeZero() {
  PKValue value;
  bzero(&value, sizeof(PKValue));
  return (PKToken){ 0, value, NULL };
}

