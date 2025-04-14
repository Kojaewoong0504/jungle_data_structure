//
// Created by 고재웅 on 25. 4. 14.
//
#include <stdbool.h>
#include <stdlib.h>
#include "b_tree.h"


BTreeNode* createNode(bool isLeaf) {
    BTreeNode *newNode = (BTreeNode *)calloc(1,sizeof(BTreeNode));
    if (newNode == NULL) return NULL;
    newNode->isLeaf = isLeaf;
    return newNode;
}


void freeBTree(BTreeNode *root) {
    if (root == NULL) return;

    if (!root->isLeaf) {
        for (int i = 0; i <= root->numKeys; i++) {
            freeBTree(root->children[i]);
        }
    }
    free(root);
}


void insertNode(BTreeNode *node, int key) {
    if (node == NULL) return;
    if (node->isLeaf) {
        int i = node->numKeys -1;
        while (i >= 0 && node->keys[i] > key) {
            if (node->keys[i] == key) return;
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->numKeys++;
    } else {
        int i = node->numKeys - 1;
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        if (node->children[i]->numKeys == MAX_KEYS) {
            splitNode(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNode(node->children[i], key);
    }
}


void splitNode(BTreeNode *parent, int index, BTreeNode *child) {
    BTreeNode *newChild = createNode(child->isLeaf);
    int mid = MAX_KEYS / 2;
    for (int i = 0; i< MAX_KEYS - mid - 1; i++) {
        newChild->keys[i] = child->keys[mid+1+i];
    }
    newChild->numKeys = MAX_KEYS - mid -1;
    if (!child->isLeaf) {
        for (int i = 0; i <= MAX_KEYS-mid-1; i++) {
            newChild->children[i] = child->children[mid + 1+i];
        }
    }
    child->numKeys = mid;
    for (int i = parent->numKeys; i> index + i; i--) {
        parent->children[i] = parent->children[i-1];
    }
    for (int i = parent->numKeys + 1; i>=index + 1; i--) {
        parent->keys[i] = parent->keys[i - 1];
    }
    parent->children[index + 1] = newChild;
    parent->keys[index] = child->keys[mid];
    parent->numKeys++;
}


BTreeNode* insert(BTreeNode *root, int key) {
    if (root == NULL) {
        root = createNode(true);
        root->keys[0] = key;
        root->numKeys = 1;
        return root;
    } else {
        // 루트가 가득 찼다면 split 필요
        if (root->numKeys == MAX_KEYS) {
            // 1. 새 루트 생성 (리프 아님)
            BTreeNode *newRoot = createNode(false);

            // 2. 기존 루트를 자식으로 연결
            newRoot->children[0] = root;

            // 3. 기존 루트 분할
            splitNode(newRoot, 0, root);

            // 4. 새 루트를 기준으로 삽입
            insertNode(newRoot, key);

            return newRoot;
        } else {
            // 루트가 가득 차지 않았으면 그냥 삽입
            insertNode(root, key);
            return root;
        }
    }
}

BTreeNode* searchNode(BTreeNode *root, int key) {
    if (root == NULL) return NULL;
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) {
        i++;
    }
    if (i < root->numKeys && key == root->keys[i]) {
        return root;
    }
    if (root->isLeaf) {
        return NULL;
    }
    return searchNode(root->children[i], key);
}
