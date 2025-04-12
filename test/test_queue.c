//
// Created by 고재웅 on 25. 4. 12.
//

#include "minunit.h"
#include "queue.h"

static char * test_enqueue_dequeue() {
    Queue q;
    init_queue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    mu_assert("dequeue 1", dequeue(&q) == 10);
    mu_assert("dequeue 2", dequeue(&q) == 20);
    mu_assert("dequeue 3", dequeue(&q) == 30);
    mu_assert("queue should be empty", is_empty_queue(&q) == 1);

    free_queue(&q);
    return 0;
}


static char * test_peek_queue() {
    Queue q;
    init_queue(&q);

    enqueue(&q, 100);
    mu_assert("peek 100", peek_queue(&q) == 100);

    enqueue(&q, 200);
    mu_assert("peek still 100", peek_queue(&q) == 100);

    dequeue(&q);
    mu_assert("peek after dequeue", peek_queue(&q) == 200);

    free_queue(&q);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_enqueue_dequeue);
    mu_run_test(test_peek_queue);
    if (tests_failed > 0) {
        return "Some tests failed.";
    }

    return 0;
}


int tests_run = 0;
int tests_failed = 0;

int main(void) {
    char *result = all_tests();

    printf("========================================\n");
    printf("Tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_run - tests_failed);
    printf("Tests failed: %d\n", tests_failed);

    if (result != 0) {
        printf("❌ TESTS FAILED\n");
        return 1;
    }
    printf("✅ ALL TESTS PASSED\n");
    return 0;
}
