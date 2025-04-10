//
// Created by 고재웅 on 25. 4. 10.
//
#include <stdio.h>
#include <string.h>

int main() {
    char ss[100];
    int count, i;
    char *p;
    p = ss;

    printf("문자열을 입력하세요 : ");
    scanf("%s", ss);

    count = strlen(ss);

    printf("\n내용을 거꾸로 출력 --> ");
    for (i = count - 1; i >= 0; i--)
    {
        printf("%c", *(p + i));
    }
    printf("\n");

    return 0;
}