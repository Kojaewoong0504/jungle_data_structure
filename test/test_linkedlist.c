//
// Created by 고재웅 on 25. 4. 11.
//
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minunit.h"
#include "linkedlist.h"

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

static char * test_delete_from_empty_list() {
    Node* head = NULL;
    delete_node(&head, 10);  // 아무 일도 없어야 함
    mu_assert("delete_node on empty list should keep head NULL", head == NULL);
    return 0;
}


static char * test_find_node() {
    Node* head = NULL;
    insert_end(&head, 5);
    insert_end(&head, 10);
    insert_end(&head, 15);

    Node* found = find_node(head, 10);
    mu_assert("find_node failed to find 10", found != NULL && found->data == 10);

    Node* not_found = find_node(head, 99);
    mu_assert("find_node should return NULL for 99", not_found == NULL);
    free_list(head);
    return 0;
}

static char * test_find_in_empty_list() {
    Node* head = NULL;
    Node* found = find_node(head, 10);
    mu_assert("find_node on empty list should return NULL", found == NULL);
    return 0;
}


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


static char * test_insert_at_out_of_bounds() {
    Node* head = NULL;
    insert_at(&head, 3, 100);  // 인덱스 3은 잘못된 위치, 아무 일도 없어야 함
    mu_assert("insert_at out of bounds should not modify list", head == NULL);
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


static char * test_reverse_single_node() {
    Node* head = NULL;
    insert_end(&head, 42);
    reverse_list(&head);
    mu_assert("reverse single node failed", head != NULL && head->data == 42 && head->next == NULL);
    free_list(head);
    return 0;
}


static char * test_reverse_empty_list() {
    Node* head = NULL;
    reverse_list(&head);  // 아무 문제 없어야 함
    mu_assert("reverse_list on empty list should keep head NULL", head == NULL);
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
    mu_assert("sort_list failed: list too long", head->next->next->next == NULL);

    free_list(head);
    return 0;
}


static char * test_sort_empty_list() {
    Node* head = NULL;
    sort_list(&head);  // 아무 문제 없어야 함
    mu_assert("sort_list on empty list should keep head NULL", head == NULL);
    return 0;
}


static char * all_tests() {
    mu_run_test(test_insert_end);
    mu_run_test(test_insert_front);
    mu_run_test(test_delete_node);
    mu_run_test(test_find_node);
    mu_run_test(test_insert_at);
    mu_run_test(test_reverse_list);
    mu_run_test(test_sort_list);
    mu_run_test(test_delete_from_empty_list);
    mu_run_test(test_find_in_empty_list);
    mu_run_test(test_insert_at_out_of_bounds);
    mu_run_test(test_reverse_single_node);
    mu_run_test(test_reverse_empty_list);
    mu_run_test(test_sort_empty_list);

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
