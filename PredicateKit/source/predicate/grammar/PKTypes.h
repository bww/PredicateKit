
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
  void        * node;
  PKValue       value;
  unsigned int  token;
} PKToken;

