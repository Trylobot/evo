// Tyler Cole
// EVO Project Module Header
// random.h

// Credit: Takuji Nishimura and Makoto Matsumoto
// http://www.math.sci.hiroshima-u.ac.jp/~m-mat/eindex.html

#ifndef _RANDOM_H_
#define _RANDOM_H_

// generates a random integer on [lo,hi]
int random( int lo, int hi );

// Period parameters 
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   // constant vector a
#define UPPER_MASK 0x80000000UL // most significant w-r bits
#define LOWER_MASK 0x7fffffffUL // least significant r bits

static unsigned long mt[N]; // the array for the state vector
static int mti=N+1; // mti==N+1 means mt[N] is not initialized

void seed(unsigned long s);
unsigned long genrand_int32();
double genrand_real2();

#endif
// end of file
