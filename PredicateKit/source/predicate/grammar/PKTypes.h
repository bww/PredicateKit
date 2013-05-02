
#import <stdint.h>

typedef union {
  uint8_t       asByte;
  int32_t       asInt;
  int64_t       asLong;
  float         asFloat;
  double        asDouble;
  const char  * asString;
} PKValue;

typedef struct PKToken {
  const char  * text;
  PKValue       value;
  unsigned int  token;
} PKToken;

