//
// Created by 고재웅 on 25. 4. 12.
//

#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

TreeNode* create_node(int data) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    if (newNode == NULL) return NULL;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


void insert_left(TreeNode* parent, int data) {
    if (parent == NULL || parent->left != NULL) return;
    TreeNode *leftNode = create_node(data);
    parent->left = leftNode;
}

void insert_right(TreeNode* parent, int data) {
    if (parent == NULL || parent->right != NULL) return;
    TreeNode *rightNode = create_node(data);
    parent->right = rightNode;
}

void free_tree(TreeNode* root) {
    if (root == NULL) return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}


int count_nodes(TreeNode* root) {
    if (root == NULL) return 0;

    int left = count_nodes(root->left);
    int right = count_nodes(root->right);
    return left + right + 1;
}


int tree_height(TreeNode* root) {
    if (root == NULL) return -1;

    int left = tree_height(root->left);
    int right = tree_height(root->right);
    return ((left >= right) ? left : right) + 1;
}

int count_leaves(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return count_leaves(root->left) + count_leaves(root->right);
}

int is_full_tree(TreeNode* root) {
    if (root == NULL) return 1;
    if (root->left == NULL && root->right == NULL) return 1;
    if (root->left != NULL && root->right != NULL) {
        return is_full_tree(root->left) && is_full_tree(root->right);
    }

    return 0;  // 자식이 1개만 있는 경우
}

