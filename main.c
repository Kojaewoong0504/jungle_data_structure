//
// Created by 고재웅 on 2025. 4. 3..
//
#include <stdio.h>



int main(void) {
    int a = 5;
    int *p = &a;
    *p = 10;
    printf("%d\n", a);
}
