#include <assert.h>
#include <stdio.h>
#include "assignment1.h"

#define CHECK(cond) printf("checking line %d: ", __LINE__); assert(cond); printf("passed\n");

int main(){

  uint16_t x = 0xBEEF;
  CHECK(getLow(x) == 0xEF);
  CHECK(getHigh(x) == 0xBE);

  setLow(&x, 0x42);
  CHECK(getLow(x) == 0x42);
  CHECK(getHigh(x) == 0xBE);

  setHigh(&x, 0x87);
  CHECK(getLow(x) == 0x42);
  CHECK(getHigh(x) == 0x87);

  clearBit(&x, 15);
  CHECK(x == 0x742);
  clearBit(&x, 0);
  CHECK(x == 0x742);
  clearBit(&x, 1);
  CHECK(x == 0x740);

  setBit(&x, 0);
  CHECK(x == 0x741);
  setBit(&x, 1);
  CHECK(x == 0x743);
  setBit(&x, 8);
  CHECK(x == 0x743);
  setBit(&x, 15);
  CHECK(x == 0x8743);


}
