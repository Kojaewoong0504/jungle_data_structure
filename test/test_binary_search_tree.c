//
// Created by 고재웅 on 25. 4. 12.
//
#include "minunit.h"
#include "binary_search_tree.h"

// int tests_run = 0;
// int tests_failed = 0;

static char* test_bst_insert() {
    BSTNode* root = NULL;
    root = bst_insert(root, 10);
    root = bst_insert(root, 5);
    root = bst_insert(root, 15);
    root = bst_insert(root, 3);
    root = bst_insert(root, 7);
    root = bst_insert(root, 12);
    root = bst_insert(root, 17);

    mu_assert("Inserted root should be 10", root->data == 10);
    mu_assert("Left child should be 5", root->left->data == 5);
    mu_assert("Right child should be 15", root->right->data == 15);
    mu_assert("Left->left should be 3", root->left->left->data == 3);
    mu_assert("Right->right should be 17", root->right->right->data == 17);

    bst_free(root);
    return 0;
}


static char* test_bst_search() {
    BSTNode* root = NULL;
    root = bst_insert(root, 20);
    bst_insert(root, 10);
    bst_insert(root, 30);

    mu_assert("Search for 10", bst_search(root, 10) != NULL);
    mu_assert("Search for 30", bst_search(root, 30) != NULL);
    mu_assert("Search for 25 (not found)", bst_search(root, 25) == NULL);

    bst_free(root);
    return 0;
}


static char* test_bst_find_min_max() {
    BSTNode* root = NULL;
    int values[] = {20, 10, 5, 15, 30, 25, 40};
    for (int i = 0; i < 7; i++) root = bst_insert(root, values[i]);

    mu_assert("Min should be 5", bst_find_min(root)->data == 5);
    mu_assert("Max should be 40", bst_find_max(root)->data == 40);

    bst_free(root);
    return 0;
}

static char* test_bst_delete_leaf() {
    BSTNode* root = NULL;
    root = bst_insert(root, 8);
    bst_insert(root, 3);
    bst_insert(root, 10);
    root = bst_delete(root, 10);  // delete leaf

    mu_assert("Delete leaf 10: should not be found", bst_search(root, 10) == NULL);
    bst_free(root);
    return 0;
}



static char* test_bst_delete_one_child() {
    BSTNode* root = NULL;
    root = bst_insert(root, 8);
    bst_insert(root, 3);
    bst_insert(root, 1);
    root = bst_delete(root, 3);

    mu_assert("Delete node 3 with one child: 1 promoted", root->left->data == 1);
    bst_free(root);
    return 0;
}

static char* test_bst_delete_two_children() {
    BSTNode* root = NULL;
    root = bst_insert(root, 8);
    bst_insert(root, 3);
    bst_insert(root, 10);
    bst_insert(root, 9);
    bst_insert(root, 12);

    root = bst_delete(root, 10);
    mu_assert("Delete 10 with two children: 12 or 9 takes place", root->right->data != 10);
    mu_assert("9 or 12 should still be found", bst_search(root, 9) || bst_search(root, 12));
    bst_free(root);
    return 0;
}


static char* all_tests() {
    mu_run_test(test_bst_insert);
    mu_run_test(test_bst_search);
    mu_run_test(test_bst_find_min_max);
    mu_run_test(test_bst_delete_leaf);
    mu_run_test(test_bst_delete_one_child);
    mu_run_test(test_bst_delete_two_children);
    if (tests_failed > 0) return "Some tests failed.";
    return 0;
}
//
// int main(void) {
//     char* result = all_tests();
//     printf("========================================\n");
//     printf("Tests run: %d\n", tests_run);
//     printf("Tests passed: %d\n", tests_run - tests_failed);
//     printf("Tests failed: %d\n", tests_failed);
//     if (result != 0) {
//         printf("❌ TESTS FAILED\n");
//         return 1;
//     }
//     printf("✅ ALL BST TESTS PASSED\n");
//     return 0;
// }