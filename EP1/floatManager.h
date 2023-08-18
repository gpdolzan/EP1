//
//  floatManager.h
//  EP1
//
//  Created by Tulio Padua Dutra and Gabriel Dolzan on 15/08/23.
//

#ifndef floatManager_h
#define floatManager_h

#include <stdio.h>
#include <math.h>
#include <fenv.h>
#include <stdlib.h>
#include <float.h>

// Create an struct that has a union inside of it with a float and int
// This way we can access the float as an int and vice-versa
typedef union {
    float f;
    int i;
} union_t;

typedef struct {
    union_t num;
    union_t before;
    union_t after;
    float absError;
    float relError;
    uint32_t ULPs;
} num_t;

int checkIsZero(num_t x);
void checkForZeroes(num_t *x1, num_t *x2, num_t *x3, num_t *x4, num_t *x5);
void initFloatType(num_t *f);
void calcAfterBefore(num_t *f);
void add(num_t *f1, num_t *f2, num_t *r);
void sub(num_t *f1, num_t *f2, num_t *r);
void mult(num_t *f1, num_t *f2, num_t *r);
void division(num_t *f1, num_t *f2, num_t *r);
float calcAbsError(num_t *f1);
float calcRelError(num_t *f1);
uint32_t calcULPs(num_t *f1);
num_t calcResult(num_t *f1, num_t *f2, char op);
void printResults(char op1, char op2, char op3, char op4, num_t *r1, num_t *r2, num_t *r3, num_t *r4, num_t *x1, num_t *x2, num_t *x3, num_t *x4, num_t *x5);

#endif /* floatManager_h */
