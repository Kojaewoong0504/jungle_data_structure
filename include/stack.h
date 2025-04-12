//
// Created by 고재웅 on 25. 4. 12.
//

#ifndef STACK_H
#define STACK_H

typedef struct StackNode {
    int data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

// 스택 초기화
void init_stack(Stack* stack);

// 값 추가
void push(Stack* stack, int data);

// 가장 위 값 제거 및 반환
int pop(Stack* stack);

// 가장 위 값 확인
int peek(Stack* stack);

// 스택이 비어 있는지 확인
int is_empty(Stack* stack);

// 스택 전체 메모리 해제
void free_stack(Stack* stack);


int get_size(Stack* stack);

void reverse_stack(Stack* stack);

Stack copy_stack(Stack* stack, Stack* copy);

#endif
