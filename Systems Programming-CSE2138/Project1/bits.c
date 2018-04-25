
// Hilal EKİNCİ - 150114057


/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif

/*
 * modPower2 - x mod pow(2,n)
 *   Example: modPower2(40, 5) = 8
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */

int modPower2(int x,int n){
    int a =  1;
    int b = ~1 + 1; // -1
    a = a << n;
    x =  x & ( a + b);   
   return x;
}

/*
 * countzeros - returns count of number of 0's in word
 *   Examples: countzeros(5) = 30, countzeros(7) = 29
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */

int countzeros(int x) {
  int a = 0x11 | (0x11 << 8);
  int b = a | (a << 16);
  int countOnes = x & b; // Counting 1s firstly
  countOnes = countOnes + ((x >> 1) & b);
  countOnes = countOnes + ((x >> 2) & b);
  countOnes = countOnes + ((x >> 3) & b);
  countOnes = countOnes + (countOnes >> 16);
  a = 0xF | (0xF << 8);
  countOnes = (countOnes & a) + ((countOnes >> 4) & a);
  return 33  + ~((countOnes + (countOnes >> 8)) & 0x3F); // 32 - ones
}

/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 4
 */
int isTmax(int x) { 
     int num = x + 1;   // Remind Tmin = Tmax + 1
     x = x + num; // Umax = 2Tmax + 1
     num = !(num);
     x = ~x;   // This is -1, it is 0 when take negation of x
     x = x | num;
     return !x;
}

/*
 * isGreaterOrEqual - if x >= y  then return 1, else return 0
 *   Example: isGreaterOrEqual(8,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 4
 */

int isGreaterOrEqual(int x, int y) {
  int signOfX = x >> 31; //Get the sign of x
  int signOfY = y >> 31; //Get the sign of y
  int check1 = ((!signOfY) & signOfX); //In case that x and y have different sign
  int check2 = !(x ^ y); //Determine whether x=y
  //x<y when x and y have the same sign, that is x - y
  int check3 = (!(signOfX ^ signOfY)) & ((x + (~y + 1)) >> 31 & 1);
  return ((!(check1 | check3))| check2);
}
/*
 * findHammingDistance - Count the number of positions at which the corresponding bits of x and y are different
 *   Example: findHammingDistance(5,10) = 4.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int findHammingDistance(int x, int y){
int k  =  x ^ y; // Find where the bits are different using xOR
int a = 0x11 | (0x11 << 8);
int b = a | (a << 16);
int countOnes = k & b; // Counting 1s 
countOnes = countOnes + ((k >> 1) & b);
countOnes = countOnes + ((k >> 2) & b);
countOnes = countOnes + ((k >> 3) & b);
countOnes = countOnes + (countOnes >> 16);
a = 0xF | (0xF << 8);
countOnes = (countOnes & a) + ((countOnes >> 4) & a);
return ((countOnes + (countOnes >> 8)) & 0x3F);
}

/*
 * isOne - return 1 if the nth bit of x is a 1
 *   Example: isOne(4,0) = 0.
 *            isOne(-100,31) = 1.
 *            isOne(5,2) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 26
 *   Rating: 4
 */

int isOne(int x, int n) {
    int a =  x >> n; // Get nth bit
    return a & 1;    // Check whether that bit is one or not
}

/*
 * smallerPower - Compute the largest power of 2, which is less than or equal to x
 *   Example: smallerPower(24) = 16, smallerPower(4) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */

int smallerPower2(int x) {
    int a;
    int signX = x >> 31; // Get sign of x
    int neg = 1 << 31; // If the number is negative, it will be shown
    //Find the smaller power of x, in case that it is positive
    x |= (x >>  1);
    x |= (x >>  2);
    x |= (x >>  4);
    x |= (x >>  8);
    x |= (x >> 16);
    a= x + 1 + ~(x >> 1);
    return (a) | (signX & neg); // If x is positive, return a, else return reg value
}

//float
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */

unsigned float_twice(unsigned uf) {
  int final_exponent = 0;
  int fraction = uf & 0x07FFFFF;  // Get fraction part's bits
  int signBit = uf & 0x80000000; // Get sign bit
  int exponent  = (uf & 0x7F800000) >> 23; // Get exponent part's bits  
  
  if (exponent == 0xFF){ // Check if it is NaN?
    return uf;}  
	 
  if((uf & 0x7fffffff) == 0){ // Check if it is 0
    return uf;}
    
  if (!exponent){ // Check it is denormalized or normalized
    if( uf << 9 >> 31){
        return (uf << 9 >> 8) + signBit;
    }
        else{
        return (uf << 1) + signBit;}
   } else {
    final_exponent = (exponent + 1) << 23; // Norm, adding 1
    if (final_exponent == 0x7f800000) // in case NaN
      fraction = 0;
    return ((exponent + 1) << 23) + fraction + signBit;
   }      
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
      if(!x){ //Check if it is 0
          return 0; }
	
      int signBit = x & 0x80000000;       // Get sign bit
      int fraction = 0, exponent = 0;  	// Fraction and exponent part are 0 in the beginning 
    
      int left = 0;
      int leftCount = 0;
     
      int mid = 0;
      int shift = 0;
      int inter = 0;
       
      if(x == 0x80000000) { //in case that tmin, 10000...
          return 0xcf000000;}   
    
      if(signBit == 0x80000000) { // check x is negative or not 
          x = -x;  }  // Set it to be positive

       while( (x >> exponent) != 1){ // Get the most left bit one
          exponent += 1; }
 
    // Checking all the bits can be stored in bits on hand
      if (exponent > 23){
          leftCount = exponent - 23;
          shift = 1 << leftCount;
          left = (shift - 1) & x;
          fraction = (x >> leftCount) & 0x7fffff;
          mid = shift>>1;
          if(left > mid ){
          inter = 1;
          } else if (left == mid) {
               inter = fraction & 1;
          }
          fraction = fraction + inter;
      } else{
          fraction = ((1 << exponent) ^ x) << (23 - exponent);}
      if(fraction == 0x800000) {
          exponent = exponent + 1;
          fraction = 0;
      }
      exponent = exponent + 127;
      exponent = exponent << 23;
      return signBit + exponent + fraction;
}

/*
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  int signBit = uf & 0x80000000; //Get sign bit
  int result = 0;
  int exponent = (uf & 0x7f800000) >> 23; // Get exponent part's bits
  int fraction = uf & 0x7fffff;  //Get fraction part's bits
  int bias = 0x7F;  // bias
  int e = 0;

  if(exponent  == 0xff) // Check if uf is NaN or not finite
    return 0x80000000u;
 
  if((exponent < bias) || !(uf << 1)) //round to 0
    return 0;
 
  e = exponent - bias;
  if (e >= 31)  return 0x80000000u; // if E > 31, overflow occurs
 
  fraction = fraction | 0x800000;

  if(e < 23) result = fraction >> (23 - e); // If e < 23, do right shift
  else result = fraction << (e - 23); // else, do left shift

  if (signBit < 0)
    return -result;
  else
    return result;  
}
