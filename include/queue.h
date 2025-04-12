//
// Created by 고재웅 on 25. 4. 12.
//

#ifndef QUEUE_H
#define QUEUE_H

typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// 초기화
void init_queue(Queue* q);

// 삽입
void enqueue(Queue* q, int data);

// 제거
int dequeue(Queue* q);

// front 값 확인
int peek_queue(Queue* q);

// 비었는지 확인
int is_empty_queue(Queue* q);

// 전체 해제
void free_queue(Queue* q);

#endif
