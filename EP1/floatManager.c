//
//  floatManager.c
//  EP1
//
//  Created by Tulio Padua Dutra and Gabriel Dolzan on 15/08/23.
//

#include "floatManager.h"

int checkIsZero(num_t x)
{
    // Calculate the difference.
    union_t diff, largest, relEpsilon;
    diff.f = fabs(x.num.f - 0.0f);
    x.num.f = fabs(x.num.f);
    // Find the largest
    largest.f = (0.0f > x.num.f) ? 0.0f : x.num.f;
    relEpsilon.f = largest.f * FLT_EPSILON;
    
    if (diff.f <= relEpsilon.f)
        return 1;
    return 0;
}

void checkForZeroes(num_t *x1, num_t *x2, num_t *x3, num_t *x4, num_t *x5)
{
    if(checkIsZero(*x1) == 1)
    {
        initFloatType(x1);
    }
    if(checkIsZero(*x2) == 1)
    {
        initFloatType(x2);
    }
    if(checkIsZero(*x3) == 1)
    {
        initFloatType(x3);
    }
    if(checkIsZero(*x4) == 1)
    {
        initFloatType(x4);
    }
    if(checkIsZero(*x5) == 1)
    {
        initFloatType(x5);
    }
}


void initFloatType(num_t *f)
{
    f->num.i = 0;
    f->after.i = 0;
    f->before.i = 0;
    f->absError = 0.0f;
    f->relError = 0.0f;
    f->ULPs = 0;
}

void calcAfterBefore(num_t *f)
{
    f->after.f = nextafterf(f->num.f, INFINITY);
    f->before.f = nextafterf(f->num.f, -INFINITY);
}

void add(num_t *f1, num_t *f2, num_t *r)
{
    r->num.f = f1->num.f + f2->num.f;
    //fesetround(FE_DOWNWARD);
    r->before.f = f1->before.f + f2->before.f;
    //fesetround(FE_UPWARD);
    r->after.f = f1->after.f + f2->after.f;
}

void sub(num_t *f1, num_t *f2, num_t *r)
{
    r->num.f = f1->num.f - f2->num.f;
    fesetround(FE_DOWNWARD);
    r->before.f = f1->before.f - f2->after.f;
    fesetround(FE_UPWARD);
    r->after.f = f1->after.f - f2->before.f;
}

void mult(num_t *f1, num_t *f2, num_t *r)
{
    fesetround(FE_DOWNWARD);
    float vec_down[4] = {f1->before.f * f2->before.f, f1->before.f * f2->after.f, f1->after.f * f2->before.f, f1->after.f * f2->after.f};
    
    fesetround(FE_UPWARD);
    float vec_up[4] = {f1->before.f * f2->before.f, f1->before.f * f2->after.f, f1->after.f * f2->before.f, f1->after.f * f2->after.f};
    
    r->before.f = vec_down[0];
    // Find the smallest value
    for (int i = 1; i < 4; i++)
    {
        if (vec_down[i] < r->before.f)
        {
            r->before.f = vec_down[i];
        }
    }
    
    r->after.f = vec_up[0];
    // Find the biggest value
    for (int i = 1; i < 4; i++)
    {
        if (vec_up[i] > r->after.f)
        {
            r->after.f = vec_up[i];
        }
    }
}

void division(num_t *f1, num_t *f2, num_t *r)
{
    fesetround(FE_DOWNWARD);
    float vec_down[4] = {f1->before.f * (1 /f2->before.f), f1->before.f * (1 / f2->after.f), f1->after.f * (1 / f2->before.f), f1->after.f * (1/ f2->after.f)};
    
    fesetround(FE_UPWARD);
    float vec_up[4] = {f1->before.f * (1 / f2->before.f), f1->before.f * (1 / f2->after.f), f1->after.f * (1 / f2->before.f), f1->after.f * (1 / f2->after.f)};
    
    if(checkIsZero(*f2) == 1)
    {
        r->before.f = -INFINITY;
        r->after.f = INFINITY;
        return;
    }
    
    r->before.f = vec_down[0];
    // Find the smallest value
    for (int i = 1; i < 4; i++)
    {
        if (vec_down[i] < r->before.f)
        {
            r->before.f = vec_down[i];
        }
    }
    
    r->after.f = vec_up[0];
    // Find the biggest value
    for (int i = 1; i < 4; i++)
    {
        if (vec_up[i] > r->after.f)
        {
            r->after.f = vec_up[i];
        }
    }
}

float calcAbsError(num_t *f1)
{
    float absError = 0.0f;
    
    fesetround(FE_TONEAREST);
    absError = fabsf(f1->after.f - f1->before.f);
    
    return absError;
}

float calcRelError(num_t *f1)
{
    float relError = 0.0f;
    
    fesetround(FE_TONEAREST);
    relError = (f1->absError / fabsf(f1->before.f));
    
    return relError;
}

uint32_t calcULPs(num_t *f1)
{
    uint32_t ULPs = 0;
    
    // Calculate ULPs based on after and before
    ULPs = (uint32_t) (abs(f1->after.i - f1->before.i) - 1);
    
    return ULPs;
}

num_t calcResult(num_t *f1, num_t *f2, char op)
{
    num_t result;
    initFloatType(&result);
    
    // Switch case using operation
    switch (op) {
        case '+':
            add(f1, f2, &result);
            break;
        case '-':
            sub(f1, f2, &result);
            break;
        case '*':
            mult(f1, f2, &result);
            break;
        case '/':
            division(f1, f2, &result);
            break;
    }
    
    // Calculate absolute, relative and ULPs
    result.absError = calcAbsError(&result);
    result.relError = calcRelError(&result);
    result.ULPs = calcULPs(&result);
    
    return result;
}

void printResults(char op1, char op2, char op3, char op4, num_t *r1, num_t *r2, num_t *r3, num_t *r4, num_t *x1, num_t *x2, num_t *x3, num_t *x4, num_t *x5) {
    printf("\n1:\n");
    printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] =\n[%1.8e,%1.8e]\n", x1->before.f, x1->after.f, op1, x2->before.f, x2->after.f, r1->before.f, r1->after.f);
    printf("EA: %1.8e; ER: %1.8e; ULPs: %d\n\n", r1->absError, r1->relError, r1->ULPs);
    
    printf("\n2:\n");
    printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] =\n[%1.8e,%1.8e]\n", r1->before.f, r1->after.f, op2, x3->before.f, x3->after.f, r2->before.f, r2->after.f);
    printf("EA: %1.8e; ER: %1.8e; ULPs: %u\n\n", r2->absError, r2->relError, r2->ULPs);
    
    printf("\n3:\n");
    printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] =\n[%1.8e,%1.8e]\n", r2->before.f, r2->after.f, op3, x4->before.f, x4->after.f, r3->before.f, r3->after.f);
    printf("EA: %1.8e; ER: %1.8e; ULPs: %u\n\n", r3->absError, r3->relError, r3->ULPs);
    
    printf("\n4:\n");
    printf("[%1.8e,%1.8e] %c [%1.8e,%1.8e] =\n[%1.8e,%1.8e]\n", r3->before.f, r3->after.f, op4, x5->before.f, x5->after.f, r4->before.f, r4->after.f);
    printf("EA: %1.8e; ER: %1.8e; ULPs: %u\n\n", r4->absError, r4->relError, r4->ULPs);
}
