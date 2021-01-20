//
//  main.c
//  operation(#)
//
//  Created by 王潇 on 2021/1/20.
//

#include <stdio.h>
#include <string.h>

#define ADD(A, B) printf("A + B = %d\n", ((A) + (B)));
//#define ADD(A, B) printf(#A " + " #B " = %f\n", ((A) + (B)));
//#define ADD(A, B) printf( "A + B = %D", (A+B));
#define XNAME(n) x ## n
#define PRINT_XN(n) printf("x" #n " = %d\n", x ## n);

int main(int argc, const char * argv[]) {
    ADD(5, 20);
    ADD(13, 14);
    
    int XNAME(1) = 14;
    int XNAME(2) = 20;
    int x3 = 30;
    PRINT_XN(1);
    PRINT_XN(2);
    PRINT_XN(3);
    return 0;
}
