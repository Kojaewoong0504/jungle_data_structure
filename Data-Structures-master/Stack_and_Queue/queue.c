#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

// ---[구현할 기능 정의]--- //
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
// --- [링크드 리스트 구현] --- //

// --- [메인 & 테스트 코드] --- //
static char * all_tests() {
    if (tests_failed > 0) {
        return "Some tests failed.";
    }

    return 0;
}

// int tests_run = 0;
// int tests_failed = 0;
//
// int main(void) {
//     char *result = all_tests();
//
//     printf("========================================\n");
//     printf("Tests run: %d\n", tests_run);
//     printf("Tests passed: %d\n", tests_run - tests_failed);
//     printf("Tests failed: %d\n", tests_failed);
//
//     if (result != 0) {
//         printf("❌ TESTS FAILED\n");
//         return 1;
//     }
//     printf("✅ ALL TESTS PASSED\n");
//     return 0;
// }
