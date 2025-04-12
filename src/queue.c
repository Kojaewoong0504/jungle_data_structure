//
// Created by 고재웅 on 25. 4. 12.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


void init_queue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

void enqueue(Queue* q, int data) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    if (newNode == NULL) return;
    newNode->data = data;
    if (q->front == NULL) {
        q->front = newNode;
        q->rear = newNode;
    }else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    
}

int dequeue(Queue* q){
    if (q==NULL || q->front == NULL) return -1;
    QueueNode *temp = q->front;
    int data = temp->data;

    q->front = q->front->next;

    if (q->front == NULL){
        q->rear = NULL;
    }
    free(temp);
    return data;
}

int is_empty_queue(Queue* q) {
    if (q == NULL || q->front == NULL) return 1;
    return 0;
}

// 전체 해제
void free_queue(Queue* q) {
    QueueNode *cur = q->front;
    while (cur != NULL) {
        QueueNode *temp = cur;
        cur = cur->next;
        free(temp);
    }
    q->front = NULL;
    q->rear = NULL;
}

int peek_queue(Queue* q) {
    if (q == NULL || q->front == NULL) return -1;

    return q->front->data;
}