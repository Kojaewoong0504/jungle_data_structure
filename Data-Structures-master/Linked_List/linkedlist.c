#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

// ---[구현할 기능 정의]--- //
typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct linkedlist {
    Node* head;
    int size;
} ll;


Node* create_node(int data);
void insert_end(ll* list, int data);
void print_list(ll* list);
void free_list(ll* list);
void insert_front(ll* list, int data);
void delete_node(ll* list, int data);
Node* find_node(ll* list, int data);
void insert_at(ll* list, int index, int data);
void reverse_list(ll* list);
void sort_list(ll* list);

// --- [링크드 리스트 구현] --- //

Node* create_node(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insert_end(ll* list, int data) {
    Node* new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    if (list->head == NULL) {
        list->head = new_node;
        return;
    }
    Node* cur = list->head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = new_node;
}

void free_list(ll* list) {
    if (list == NULL ||list->head == NULL) {
        return;
    }
    Node* temp = NULL;
    Node* cur = list->head;
    while (cur) {
        temp = cur;
        cur = cur->next;
        free(temp);
    }
    list->head = NULL;
}

void print_list(ll* list) {
    Node* cur = list->head;

    while (cur) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

void insert_front(ll* list, int data) {
    Node* new_node = create_node(data);
    if (new_node == NULL) {
        return;
    }
    if (list == NULL) {
        list->head = new_node;
        return;
    }
    new_node->next = list->head;
    list->head = new_node;
}

Node* find_node(ll* list, int data) {
    if (list == NULL) return NULL;
    Node* cur = list->head;

    while (cur != NULL) {
        if (cur->data == data) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void insert_at(ll* list, int index, int data) {
    Node* newNode = create_node(data);
    if (newNode == NULL) {
        return;
    }
    if (index == 0){
        newNode->next = list->head;
        list->head = newNode;
        return;
    }
    int count = 0;
    Node* cur = list->head;

    while (cur != NULL && count < index - 1) {
        cur = cur->next;
        count++;
    }

    // index가 리스트 길이보다 클 경우 처리
    if (cur == NULL) {
        printf("[insert_at] Invalid index %d: out of bounds.\n", index);
        free(newNode);  // 사용 안 하므로 메모리 해제
        return;
    }

    newNode->next = cur->next;
    cur->next = newNode;
}

void reverse_list(ll* list) {
    if (list == NULL) return;

    Node *prev = NULL;
    Node *cur = list->head;
    Node *next = NULL;

    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    list->head = prev;
}

void delete_node(ll* list, int data) {
    if (list == NULL) return;
    Node* cur = list->head;
    Node* prev = NULL;

    while (cur != NULL) {
        if (cur->data == data) {
            if (prev == NULL) {
                list->head = cur->next;
            }else {
                prev->next = cur->next;
            }
            Node* temp = cur;
            cur->next = NULL;
            free(temp);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

Node* merge(Node *left, Node *right) {
    Node dummy;
    dummy.next = NULL;
    Node* tail = &dummy;

    while (left && right) {
        if (left->data < right->data) {
            tail->next = left;
            left = left->next;
        }else {
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }
    if (left != NULL) tail->next = left;
    if (right != NULL) tail->next = right;
    return dummy.next;
}


void sort_list(ll* list) {
    if (list == NULL || list->head == NULL || list->head->next == NULL) {
        return;
    }
    Node* slow = list->head;
    Node* fast = list->head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* left = list->head;
    Node* right = slow->next;
    slow->next = NULL;

    ll left_list = { .head = left };
    ll right_list = { .head = right };

    sort_list(&left_list);
    sort_list(&right_list);

    list->head = merge(left_list.head, right_list.head);
}

// --- [메인 & 테스트 코드] --- //
static char * test_insert_end() {
    ll list = { .head = NULL, .size = 0 };
    insert_end(&list, 10);
    insert_end(&list, 20);
    insert_end(&list, 30);
    print_list(&list);
    mu_assert("error: head->data != 10", list.head->data == 10);
    mu_assert("error: head->next->data != 20", list.head->next->data == 20);
    mu_assert("error: head->next->next->data != 30", list.head->next->next->data == 30);

    free_list(&list);
    return 0;
}

static char * test_insert_front() {
    ll list = { .head = NULL, .size = 0 };
    insert_front(&list, 10);
    insert_front(&list, 20);
    insert_front(&list, 30);
    // 리스트: 30 -> 20 -> 10
    print_list(&list);
    mu_assert("insert_front failed at head", list.head->data == 30);
    mu_assert("insert_front failed at 2nd", list.head->next->data == 20);
    mu_assert("insert_front failed at 3rd", list.head->next->next->data == 10);
    free_list(&list);
    return 0;
}


static char * test_delete_node() {
    ll list = { .head = NULL, .size = 0 };
    insert_end(&list, 10);
    insert_end(&list, 20);
    insert_end(&list, 30);
    delete_node(&list, 20);
    // 리스트: 10 -> 30

    mu_assert("delete_node failed at head", list.head->data == 10);
    mu_assert("delete_node failed at 2nd", list.head->next->data == 30);
    mu_assert("delete_node failed: list too long", list.head->next->next == NULL);
    free_list(&list);
    return 0;
}

static char * test_delete_from_empty_list() {
    ll list = { .head = NULL, .size = 0 };
    delete_node(&list, 10);  // 아무 일도 없어야 함
    mu_assert("delete_node on empty list should keep head NULL", list.head == NULL);
    return 0;
}

static char * test_find_node() {
    ll list = { .head = NULL, .size = 0 };
    insert_end(&list, 5);
    insert_end(&list, 10);
    insert_end(&list, 15);
    Node* found = find_node(&list, 10);
    mu_assert("find_node failed to find 10", found != NULL && found->data == 10);

    Node* not_found = find_node(&list, 99);
    mu_assert("find_node should return NULL for 99", not_found == NULL);
    free_list(&list);
    return 0;
}

static char * test_find_in_empty_list() {
    ll list = { .head = NULL, .size = 0 };
    Node* found = find_node(&list, 10);
    mu_assert("find_node on empty list should return NULL", found == NULL);
    return 0;
}

static char * test_insert_at() {
    ll list = { .head = NULL, .size = 0 };
    insert_end(&list, 1);
    insert_end(&list, 3);
    insert_at(&list, 1, 2);  // 1 -> 2 -> 3

    mu_assert("insert_at failed at 1", list.head->data == 1);
    mu_assert("insert_at failed at 2", list.head->next->data == 2);
    mu_assert("insert_at failed at 3", list.head->next->next->data == 3);
    free_list(&list);
    return 0;
}


static char * test_insert_at_out_of_bounds() {
    ll list = { .head = NULL, .size = 0 };
    insert_at(&list, 3, 100);  // 인덱스 3은 잘못된 위치, 아무 일도 없어야 함
    mu_assert("insert_at out of bounds should not modify list", list.head == NULL);
    return 0;
}



static char * test_reverse_list() {
    ll list = { .head = NULL, .size = 0 };
    insert_end(&list, 1);
    insert_end(&list, 2);
    insert_end(&list, 3);
    reverse_list(&list);  // 3 -> 2 -> 1

    mu_assert("reverse_list failed at 1", list.head->data == 3);
    mu_assert("reverse_list failed at 2", list.head->next->data == 2);
    mu_assert("reverse_list failed at 3", list.head->next->next->data == 1);
    free_list(&list);
    return 0;
}


static char * test_reverse_single_node() {
    ll list = { .head = NULL, .size = 0 };
    insert_end(&list, 42);
    reverse_list(&list);
    mu_assert("reverse single node failed", list.head != NULL && list.head->data == 42 && list.head->next == NULL);
    free_list(&list);
    return 0;
}


static char * test_reverse_empty_list() {
    ll list = { .head = NULL, .size = 0 };
    reverse_list(&list);  // 아무 문제 없어야 함
    mu_assert("reverse_list on empty list should keep head NULL", list.head == NULL);
    return 0;
}

static char * test_sort_list() {
    ll list = { .head = NULL, .size = 0 };
    insert_end(&list, 30);
    insert_end(&list, 10);
    insert_end(&list, 20);
    sort_list(&list);  // 10 -> 20 -> 30

    mu_assert("sort_list failed at 1", list.head->data == 10);
    mu_assert("sort_list failed at 2", list.head->next->data == 20);
    mu_assert("sort_list failed at 3", list.head->next->next->data == 30);
    mu_assert("sort_list failed: list too long", list.head->next->next->next == NULL);

    free_list(&list);
    return 0;
}


static char * test_sort_empty_list() {
    ll list = { .head = NULL, .size = 0 };
    sort_list(&list);  // 아무 문제 없어야 함
    mu_assert("sort_list on empty list should keep head NULL", list.head == NULL);
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
