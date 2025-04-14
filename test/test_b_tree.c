// test_b_tree.c
// Created by 고재웅 on 25. 4. 14.

#include <stdio.h>
#include "minunit.h"
#include "b_tree.h"

int tests_run = 0;
int tests_failed = 0;


static char* test_create_and_free_node() {
    BTreeNode *root = createNode(true);
    mu_assert("Root should not be NULL", root != NULL);
    mu_assert("Root should be leaf", root->isLeaf == true);
    mu_assert("Root should have 0 keys", root->numKeys == 0);

    freeBTree(root); // 메모리 해제 테스트
    return 0;
}


static char* test_btree_insert() {
    BTreeNode *root = NULL;
    // 처음 삽입은 빈 트리에서 시작: insert 함수는 내부에서 createNode를 호출할 것으로 예상
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 12);

    mu_assert("Inserted key 10 should be found", searchNode(root, 10) != NULL);
    mu_assert("Inserted key 20 should be found", searchNode(root, 20) != NULL);
    mu_assert("Inserted key 5 should be found", searchNode(root, 5) != NULL);
    mu_assert("Inserted key 6 should be found", searchNode(root, 6) != NULL);
    mu_assert("Inserted key 12 should be found", searchNode(root, 12) != NULL);

    freeBTree(root);
    return 0;
}


/*
static char* test_btree_search() {
    BTreeNode *root = NULL;
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 40);
    root = insert(root, 25);

    mu_assert("Search for 15 should succeed", searchNode(root, 15) != NULL);
    mu_assert("Search for 40 should succeed", searchNode(root, 40) != NULL);
    mu_assert("Search for 50 (non-existent) should fail", searchNode(root, 50) == NULL);

    freeBTree(root);
    return 0;
}

static char* test_btree_delete() {
    BTreeNode *root = NULL;
    root = insert(root, 50);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 30);
    root = insert(root, 70);

    // 삭제 테스트: leaf 또는 내부 노드에서 키 삭제
    root = deleteNode(root, 30);
    mu_assert("After deletion, key 30 should not be found", searchNode(root, 30) == NULL);

    root = deleteNode(root, 50);
    mu_assert("After deletion, key 50 should not be found", searchNode(root, 50) == NULL);

    freeBTree(root);
    return 0;
}
*/

static char* all_tests() {
    mu_run_test(test_create_and_free_node);
    mu_run_test(test_btree_insert);
    // mu_run_test(test_btree_search);
    // mu_run_test(test_btree_delete);
    if (tests_failed > 0) return "Some tests failed.";
    return 0;
}

int main(void) {
    char* result = all_tests();
    printf("========================================\n");
    printf("Tests run: %d\n", tests_run);
    printf("Tests passed: %d\n", tests_run - tests_failed);
    printf("Tests failed: %d\n", tests_failed);
    if (result != 0) {
        printf("❌ TESTS FAILED\n");
        return 1;
    }
    printf("✅ ALL B-TREE TESTS PASSED\n");
    return 0;
}
