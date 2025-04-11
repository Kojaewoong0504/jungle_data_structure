//
// Created by 고재웅 on 25. 4. 11.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minunit.h"
#include "linkedlist.h"

int tests_run = 0;

static char * test_insert_end() {
    Node* head = NULL;
    insert_end(&head, 10);
    insert_end(&head, 20);
    insert_end(&head, 30);

    mu_assert("error: head->data != 10", head->data == 10);
    mu_assert("error: head->next->data != 20", head->next->data == 20);
    mu_assert("error: head->next->next->data != 30", head->next->next->data == 30);

    free_list(head);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_insert_end);
    return 0;
}

int main(void) {
    char *result = all_tests();
    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
