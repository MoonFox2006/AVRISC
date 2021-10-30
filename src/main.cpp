#include <Arduino.h>

#define EXAMPLE 1

const uint16_t STEPS = 10000;

#if EXAMPLE == 1
static uint32_t test() {
  uint32_t result = 0;

  for (uint16_t i = 0; i < STEPS; ++i) {
    result += (1 << (i & 0x07));
  }
  return result;
}
#elif EXAMPLE == 2
static uint32_t test() {
  uint32_t result = 0;
  uint8_t n = 1;

  for (uint16_t i = 0; i < STEPS; ++i) {
    result += n;
    n <<= 1;
    if (! n)
      n = 1;
  }
  return result;
}
#elif EXAMPLE == 3
static uint32_t test(uint8_t a) {
  uint32_t result = 0;
  volatile uint8_t b;

  b = 8;
  for (uint16_t i = 0; i < STEPS; ++i) {
    result += a % b;
  }
  return result;
}
#elif EXAMPLE == 4
static uint32_t test(uint8_t a) {
  uint32_t result = 0;
  volatile uint8_t b;

  b = 7;
  for (uint16_t i = 0; i < STEPS; ++i) {
    result += a & b;
  }
  return result;
}
#endif

void setup() {
  uint32_t time;
  uint32_t sum;

  Serial.begin(115200);

  time = micros();
#if EXAMPLE < 3
  sum = test();
#else
  sum = test(1);
#endif
  time = micros() - time;
  Serial.println(sum);
  Serial.print(time);
  Serial.println(F(" us."));
}

void loop() {}
