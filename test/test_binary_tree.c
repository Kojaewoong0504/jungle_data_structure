//
// Created by 고재웅 on 25. 4. 12.
//

#include "minunit.h"
#include "binary_tree.h"

static char* test_create_and_insert() {
    TreeNode* root = create_node(1);
    insert_left(root, 2);
    insert_right(root, 3);
    insert_left(root->left, 4);
    insert_right(root->left, 5);

    mu_assert("root should be 1", root->data == 1);
    mu_assert("left child should be 2", root->left->data == 2);
    mu_assert("right child should be 3", root->right->data == 3);
    mu_assert("left->left should be 4", root->left->left->data == 4);
    mu_assert("left->right should be 5", root->left->right->data == 5);

    free_tree(root);
    return 0;
}

static TreeNode* build_sample_tree() {
    TreeNode* root = create_node(1);
    insert_left(root, 2);
    insert_right(root, 3);
    insert_left(root->left, 4);
    insert_right(root->left, 5);
    insert_left(root->right, 6);
    insert_right(root->right, 7);
    return root;
}


static char* test_count_nodes() {
    TreeNode* root = build_sample_tree();
    mu_assert("Total nodes should be 7", count_nodes(root) == 7);
    free_tree(root);
    return 0;
}

static char* test_tree_height() {
    TreeNode* root = build_sample_tree();
    mu_assert("Tree height should be 2", tree_height(root) == 2);  // 루트~리프 거리
    free_tree(root);
    return 0;
}


static char* test_count_leaves() {
    TreeNode* root = build_sample_tree();
    mu_assert("Leaf count should be 4", count_leaves(root) == 4);  // 4,5,6,7
    free_tree(root);
    return 0;
}


static char* test_is_full_tree() {
    TreeNode* root = build_sample_tree();
    mu_assert("Tree should be full", is_full_tree(root) == 1);
    free_tree(root);
    return 0;
}

static char* test_edge_case_empty_tree() {
    TreeNode* root = NULL;

    mu_assert("Empty tree: count_nodes == 0", count_nodes(root) == 0);
    mu_assert("Empty tree: tree_height == -1", tree_height(root) == -1);  // 간선 기준
    mu_assert("Empty tree: count_leaves == 0", count_leaves(root) == 0);
    mu_assert("Empty tree: is_full_tree == 1", is_full_tree(root) == 1);  // by definition

    return 0;
}

static char* test_single_node_tree() {
    TreeNode* root = create_node(42);

    mu_assert("Single node: count_nodes == 1", count_nodes(root) == 1);
    mu_assert("Single node: tree_height == 0", tree_height(root) == 0);  // 루트만 있으면 높이 0
    mu_assert("Single node: count_leaves == 1", count_leaves(root) == 1);
    mu_assert("Single node: is_full_tree == 1", is_full_tree(root) == 1);

    free_tree(root);
    return 0;
}

static char* test_non_full_tree() {
    TreeNode* root = create_node(1);
    insert_left(root, 2); // 오른쪽 없음 → full tree 아님

    mu_assert("Non-full tree: is_full_tree == 0", is_full_tree(root) == 0);
    mu_assert("Non-full tree: count_nodes == 2", count_nodes(root) == 2);
    mu_assert("Non-full tree: count_leaves == 1", count_leaves(root) == 1);  // node 2

    free_tree(root);
    return 0;
}

static char* test_unbalanced_tree() {
    TreeNode* root = create_node(1);
    insert_left(root, 2);
    insert_left(root->left, 3);
    insert_left(root->left->left, 4);

    mu_assert("Unbalanced tree: height == 3", tree_height(root) == 3);
    mu_assert("Unbalanced tree: count_nodes == 4", count_nodes(root) == 4);
    mu_assert("Unbalanced tree: count_leaves == 1", count_leaves(root) == 1);  // node 4
    mu_assert("Unbalanced tree: is_full_tree == 0", is_full_tree(root) == 0);  // 자식 한쪽만 있음

    free_tree(root);
    return 0;
}

static char* all_tests() {
    mu_run_test(test_create_and_insert);
    mu_run_test(test_count_nodes);
    mu_run_test(test_tree_height);
    mu_run_test(test_count_leaves);
    mu_run_test(test_is_full_tree);
    mu_run_test(test_edge_case_empty_tree);
    mu_run_test(test_single_node_tree);
    mu_run_test(test_non_full_tree);
    mu_run_test(test_unbalanced_tree);
    if (tests_failed > 0) {
        return "Some tests failed.";
    }
    return 0;
}
//
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
//
