//
// Created by 고재웅 on 25. 4. 12.
//

#include <stdio.h>
#include "stack.h"

#include <linkedlist.h>
#include <stdlib.h>


void init_stack(Stack *stack) {
    stack->top = NULL;
}

int is_empty(Stack *stack) {
    if (stack == NULL|| stack->top == NULL) return 1;
    return 0;
}

void push(Stack *stack, int data) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    if (!newNode) return;
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack *stack) {
    if (is_empty(stack)) {
        printf("stack empty\n");
        return -1;
    }
    StackNode* temp = stack->top;
    int data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

void free_stack(Stack *stack) {
    StackNode* cur = stack->top;
    while (cur != NULL) {
        StackNode* temp = cur;
        cur = cur->next;
        free(temp);
    }
    stack->top = NULL;
}

int peek(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        return INT8_MIN;
    }
    return stack->top->data;
}

int get_size(Stack *stack) {
    if (stack == NULL || stack->top == NULL) return 0;

    StackNode *cur = stack->top;
    int count = 0;
    while (cur != NULL) {
        cur = cur->next;
        count++;
    }
    return count;
}

void reverse_stack(Stack *stack) {
    if (stack == NULL || stack->top == NULL) return;
    StackNode *prev = NULL;
    StackNode *cur = stack->top;
    StackNode *next = NULL;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    stack->top = prev;
}

Stack copy_stack(Stack* stack, Stack* copy) {
    if (stack == NULL || stack->top == NULL) return *copy;
    Stack temp;
    init_stack(&temp);

    StackNode *cur = stack->top;
    while (cur) {
        push(&temp, cur->data);
        cur = cur->next;
    }
    while (!is_empty(&temp)) {
        push(copy, pop(&temp));
    }
    free_stack(&temp);
}