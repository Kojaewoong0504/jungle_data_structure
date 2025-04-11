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

static char * test_insert_front() {
    Node* head = NULL;
    insert_front(&head, 10);
    insert_front(&head, 20);
    insert_front(&head, 30);
    // 리스트: 30 -> 20 -> 10

    mu_assert("insert_front failed at head", head->data == 30);
    mu_assert("insert_front failed at 2nd", head->next->data == 20);
    mu_assert("insert_front failed at 3rd", head->next->next->data == 10);
    free_list(head);
    return 0;
}

static char * test_delete_node() {
    Node* head = NULL;
    insert_end(&head, 10);
    insert_end(&head, 20);
    insert_end(&head, 30);
    delete_node(&head, 20);
    // 리스트: 10 -> 30

    mu_assert("delete_node failed at head", head->data == 10);
    mu_assert("delete_node failed at 2nd", head->next->data == 30);
    mu_assert("delete_node failed: list too long", head->next->next == NULL);
    free_list(head);
    return 0;
}


static char * test_find_node() {
    Node* head = NULL;
    insert_end(&head, 5);
    insert_end(&head, 10);
    insert_end(&head, 15);

    Node* found = find_node(head, 10);
    mu_assert("find_node failed to find 10", found != NULL && found->data == 10);


    // 현재 이 부분의 문제가 있다. 값이 없는 경우 반환 값이 없다.
    Node* not_found = find_node(head, 99);
    mu_assert("find_node should return NULL for 99", not_found == NULL);
    free_list(head);
    return 0;
}

/*
static char * test_insert_at() {
    Node* head = NULL;
    insert_end(&head, 1);
    insert_end(&head, 3);
    insert_at(&head, 1, 2);  // 1 -> 2 -> 3

    mu_assert("insert_at failed at 1", head->data == 1);
    mu_assert("insert_at failed at 2", head->next->data == 2);
    mu_assert("insert_at failed at 3", head->next->next->data == 3);
    free_list(head);
    return 0;
}

static char * test_reverse_list() {
    Node* head = NULL;
    insert_end(&head, 1);
    insert_end(&head, 2);
    insert_end(&head, 3);
    reverse_list(&head);  // 3 -> 2 -> 1

    mu_assert("reverse_list failed at 1", head->data == 3);
    mu_assert("reverse_list failed at 2", head->next->data == 2);
    mu_assert("reverse_list failed at 3", head->next->next->data == 1);
    free_list(head);
    return 0;
}

static char * test_sort_list() {
    Node* head = NULL;
    insert_end(&head, 30);
    insert_end(&head, 10);
    insert_end(&head, 20);
    sort_list(&head);  // 10 -> 20 -> 30

    mu_assert("sort_list failed at 1", head->data == 10);
    mu_assert("sort_list failed at 2", head->next->data == 20);
    mu_assert("sort_list failed at 3", head->next->next->data == 30);
    free_list(head);
    return 0;
}
*/

static char * all_tests() {
    mu_run_test(test_insert_end);
    mu_run_test(test_insert_front);
    mu_run_test(test_delete_node);
    mu_run_test(test_find_node);
    // mu_run_test(test_insert_at);
    // mu_run_test(test_reverse_list);
    // mu_run_test(test_sort_list);
    return 0;
}



int main(void) {
    char *result = all_tests();
    if (result != 0) {
        printf("❌ %s\n", result);
    } else {
        printf("✅ ALL TESTS PASSED\n");
    }
    printf("Tests run: %d\n", tests_run);
    return result != 0;
}
