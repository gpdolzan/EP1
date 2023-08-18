//
//  main.c
//  EP1
//
//  Created by Tulio Padua Dutra and Gabriel Dolzan on 15/08/23.
//

#include <stdio.h>
#include "floatManager.h"

int main(int argc, const char * argv[])
{
    num_t x1, x2, x3, x4, x5; // Input variables
    num_t r1, r2, r3, r4;     // Result variables
    char op1, op2, op3, op4;  // Operations variables
    
    scanf("%f %c %f %c %f %c %f %c %f", &x1.num.f, &op1, &x2.num.f, &op2, &x3.num.f, &op3, &x4.num.f, &op4, &x5.num.f);
    
    calcAfterBefore(&x1);
    calcAfterBefore(&x2);
    calcAfterBefore(&x3);
    calcAfterBefore(&x4);
    calcAfterBefore(&x5);
    
    checkForZeroes(&x1, &x2, &x3, &x4, &x5);
    
    r1 = calcResult(&x1, &x2, op1);
    r2 = calcResult(&r1, &x3, op2);
    r3 = calcResult(&r2, &x4, op3);
    r4 = calcResult(&r3, &x5, op4);
    
    printResults(op1, op2, op3, op4, &r1, &r2, &r3, &r4, &x1, &x2, &x3, &x4, &x5);
    
    return 0;
}
