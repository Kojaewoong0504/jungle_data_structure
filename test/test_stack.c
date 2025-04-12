//
// Created by 고재웅 on 25. 4. 12.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minunit.h"
#include "stack.h"

static char * test_push_and_peek() {
    Stack s;
    init_stack(&s);

    push(&s, 10);
    mu_assert("peek after 1 push", peek(&s) == 10);

    push(&s, 20);
    mu_assert("peek after 2 pushes", peek(&s) == 20);

    free_stack(&s);
    return 0;
}
static char * test_pop() {
    Stack s;
    init_stack(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);

    mu_assert("pop 1", pop(&s) == 3);
    mu_assert("pop 2", pop(&s) == 2);
    mu_assert("pop 3", pop(&s) == 1);
    mu_assert("stack should be empty", is_empty(&s) == 1);

    free_stack(&s);
    return 0;
}

static char * test_pop_on_empty_stack() {
    Stack s;
    init_stack(&s);

    int result = pop(&s);  // 구현 시 비정상 값 반환 (예: -1) 또는 assert
    mu_assert("pop on empty stack should return -1", result == -1);

    free_stack(&s);
    return 0;
}


static char * test_get_size() {
    Stack s;
    init_stack(&s);
    mu_assert("initial size != 0", get_size(&s) == 0);

    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    mu_assert("size after 3 pushes", get_size(&s) == 3);

    pop(&s);
    mu_assert("size after pop", get_size(&s) == 2);

    free_stack(&s);
    return 0;
}


static char * test_reverse_stack() {
    Stack s;
    init_stack(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);  // top = 3

    reverse_stack(&s);   // top = 1

    mu_assert("top after reverse", peek(&s) == 1);
    pop(&s);
    mu_assert("2nd after reverse", peek(&s) == 2);
    pop(&s);
    mu_assert("3rd after reverse", peek(&s) == 3);
    pop(&s);
    mu_assert("stack should now be empty", is_empty(&s) == 1);

    free_stack(&s);
    return 0;
}


static char * test_copy_stack() {
    Stack src, dest;
    init_stack(&src);
    init_stack(&dest);

    push(&src, 10);
    push(&src, 20);
    push(&src, 30);  // top = 30

    copy_stack(&src, &dest);

    mu_assert("src top", peek(&src) == 30);
    mu_assert("dest top", peek(&dest) == 30);

    pop(&dest);
    mu_assert("dest second", peek(&dest) == 20);
    pop(&dest);
    mu_assert("dest third", peek(&dest) == 10);

    free_stack(&src);
    free_stack(&dest);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_push_and_peek);
    mu_run_test(test_pop);
    mu_run_test(test_pop_on_empty_stack);
    mu_run_test(test_get_size);
    mu_run_test(test_reverse_stack);
    mu_run_test(test_copy_stack);
    if (tests_failed > 0) {
        return "Some tests failed.";
    }

    return 0;
}


// int tests_run = 0;
// int tests_failed = 0;

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
