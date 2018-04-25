#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TMin INT_MIN
#define TMax INT_MAX

#include "btest.h"
#include "bits.h"

test_rec test_set[] = {
//1
 {"modPower2", (funct_t) modPower2, (funct_t) test_modPower2, 2, "! ~ & ^ | + << >>", 10, 4,
  {{0, TMax},{0,31},{TMin,TMax}}},
//2
 {"countzeros", (funct_t) countzeros, (funct_t) test_countzeros, 1, "! ~ & ^ | + << >>", 30, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//3
 {"isTmax", (funct_t) isTmax, (funct_t) test_isTmax, 1, "! ~ & ^ | +", 10, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//4
 {"isGreaterOrEqual", (funct_t) isGreaterOrEqual, (funct_t) test_isGreaterOrEqual, 2, "! ~ & ^ | + << >>", 24, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//5
 {"findHammingDistance", (funct_t) findHammingDistance, (funct_t) test_findHammingDistance, 2, "! ~ & ^ | + << >>", 30, 4,
  {{TMin, TMax},{TMin,TMax},{TMin,TMax}}},
//6
 {"isOne", (funct_t) isOne, (funct_t) test_isOne, 2, "! ~ & ^ | + << >>", 26, 4,
  {{TMin, TMax},{0,31},{TMin,TMax}}},
//7
 {"smallerPower2", (funct_t) smallerPower2, (funct_t) test_smallerPower2, 1, "! ~ & ^ | + << >>", 30, 4,
  {{0, TMax},{TMin,TMax},{TMin,TMax}}},

//float
 {"float_twice", (funct_t) float_twice, (funct_t) test_float_twice, 1,
    "$", 30, 4,
     {{1, 1},{1,1},{1,1}}},
 {"float_i2f", (funct_t) float_i2f, (funct_t) test_float_i2f, 1,
    "$", 30, 4,
     {{1, 1},{1,1},{1,1}}},
 {"float_f2i", (funct_t) float_f2i, (funct_t) test_float_f2i, 1,
    "$", 30, 4,
     {{1, 1},{1,1},{1,1}}},
  {"", NULL, NULL, 0, "", 0, 0,
   {{0, 0},{0,0},{0,0}}}
};
