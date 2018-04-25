/* Testing Code */

#include <limits.h>
#include <math.h>

/* Routines used by floation point test code */

/* Convert from bit level representation to floating point number */
float u2f(unsigned u) {
  union {
    unsigned u;
    float f;
  } a;
  a.u = u;
  return a.f;
}

/* Convert from floating point number to bit-level representation */
unsigned f2u(float f) {
  union {
    unsigned u;
    float f;
  } a;
  a.f = f;
  return a.u;
}

int test_modPower2(int x, int n)
{
  int i,k=1;
  for (i=1; i<=n; i++)
     k=k*2;
  return x % k;
}

int test_countzeros(int x)
{
  int result = 0;
  int i;
  for (i = 0; i < 32; i++)
    result +=  !((x >> i) & 1);
  return result;
}

int test_isTmax(int x){
  return x == 0x7FFFFFFF;
}

int test_isGreaterOrEqual(int x, int y)
{
  return x >= y;
}

int test_findHammingDistance(int x, int y){
   int result = 0;
   int i;
   for (i = 0; i < 32; i++){
     result +=  ((x&1) ^ (y&1));
      x>>=1; y>>=1;
   }
   return result;
}

int test_isOne(int x, int n){
  int k= ((1 << n) & x) ? 1 : 0;
  return k;
}

int test_smallerPower2(int x){
  int i=0,k=1;
  for(int j=0; j<=31; j++){
    if (((x>>j) & 1) == 1){
        i=j;
    }
  }
  for(int j=1; j<=i; j++)
    k=k*2;
  return k;
}

//float
unsigned test_float_twice(unsigned uf) {
  float f = u2f(uf);
  float tf = 2*f;
  if (isnan(f))
    return uf;
  else
    return f2u(tf);
}
unsigned test_float_i2f(int x) {
  float f = (float) x;
  return f2u(f);
}
int test_float_f2i(unsigned uf) {
  float f = u2f(uf);
  int x = (int) f;
  return x;
}
