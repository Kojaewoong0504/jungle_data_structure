//
// Created by 고재웅 on 25. 4. 13.
//
#include <stdio.h>
#include <stdlib.h>
#include "binary_search_tree.h"


BSTNode* bst_create_node(int data){
    BSTNode *newNode = (BSTNode *)malloc(sizeof(BSTNode));
    if (newNode == NULL) return NULL;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

BSTNode* bst_insert(BSTNode* root, int data) {
    if (root == NULL) {
        BSTNode *new_node = bst_create_node(data);
        root = new_node;
        return root;
    }
    if (root->data > data) {
        root->left = bst_insert(root->left, data);
    }else if (data > root->data) {
        root->right = bst_insert(root->right, data);
    }

    return root;
}

void bst_free(BSTNode* root) {
    if (root == NULL) return;

    bst_free(root->left);
    bst_free(root->right);

    free(root);
}

BSTNode* bst_search(BSTNode* root, int target) {
    if (root == NULL) return NULL;

    if (target < root->data) {
        return bst_search(root->left, target);
    } else if (target > root->data) {
        return bst_search(root->right, target);
    }else {
        return root;
    }
}

BSTNode* bst_find_min(BSTNode* root) {
    if (root == NULL) return NULL;
    BSTNode *cur = root;
    while (cur->left != NULL) {
        cur = cur->left;
    }
    return cur;
}


BSTNode* bst_find_max(BSTNode* root) {
    if (root == NULL) return NULL;
    BSTNode *cur = root;
    while (cur->right != NULL) {
        cur = cur->right;
    }
    return cur;
}


BSTNode* bst_delete(BSTNode* root, int target) {
    if (root == NULL) return NULL;

    if (target < root->data) {
        root->left = bst_delete(root->left, target);
    } else if (target > root->data) {
        root->right = bst_delete(root->right, target);
    } else {
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if (root->left == NULL || root->right == NULL) {
            BSTNode* child = (root->left) ? root->left : root->right;
            free(root);
            return child;
        } else {
            BSTNode* minRight = bst_find_min(root->right);
            root->data = minRight->data;
            root->right = bst_delete(root->right, minRight->data);
        }

    }

    return root;
}