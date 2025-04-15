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


BTreeNode* deleteNode(BTreeNode *root, int key){
    if (root == NULL) return NULL;

    int idx = 0;
    while (idx < root->numKeys && key > root->keys[idx]) idx++;

    if (idx < root->numKeys && root->keys[idx] == key) {
        // Key found in current node
        if (root->isLeaf) {
            deleteValFromNode(root, key);
        } else {
            deleteInnerNode(root, key);
        }
    } else {
        // Key not in this node
        if (root->isLeaf) return root; // Key not found

        // 자식이 최소 키 개수일 경우 밸런스 조정
        if (root->children[idx]->numKeys == MIN_KEYS) {
            balanceNode(root, idx);
        }

        // 재귀적으로 자식에서 삭제
        root->children[idx] = deleteNode(root->children[idx], key);
    }

    // 루트가 키를 잃고 자식이 하나뿐일 경우 → 트리 높이 감소
    if (root->numKeys == 0 && !root->isLeaf) {
        BTreeNode* oldRoot = root;
        root = root->children[0];
        free(oldRoot);
    }

    return root;
}


void deleteValFromNode(BTreeNode *node, int key) {
    int i = 0;
    while (i < node->numKeys && node->keys[i] != key) i++;
    if (i == node->numKeys) return; // key not found (안정성)

    for (; i < node->numKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }
    node->numKeys--;
}


void deleteInnerNode(BTreeNode *node, int key) {
    int idx = 0;
    while (idx < node->numKeys && node->keys[idx] != key) idx++;

    if (node->children[idx]->numKeys > MIN_KEYS) {
        int pred = findPredecessor(node, idx);
        node->keys[idx] = pred;
        node->children[idx] = deleteNode(node->children[idx], pred);
    } else if (node->children[idx + 1]->numKeys > MIN_KEYS) {
        int succ = findSuccessor(node, idx);
        node->keys[idx] = succ;
        node->children[idx + 1] = deleteNode(node->children[idx + 1], succ);
    } else {
        mergeChildNode(node, idx);
        node->children[idx] = deleteNode(node->children[idx], key);
    }
}


void balanceNode(BTreeNode *node, int index) {
    if (index > 0 && node->children[index - 1]->numKeys > MIN_KEYS) {
        borrowFromLeft(node, index);
    } else if (index < node->numKeys && node->children[index + 1]->numKeys > MIN_KEYS) {
        borrowFromRight(node, index);
    } else {
        if (index < node->numKeys) {
            mergeChildNode(node, index);
        } else {
            mergeChildNode(node, index - 1);
        }
    }
}

void borrowFromLeft(BTreeNode *node, int index) {
    BTreeNode *child = node->children[index];
    BTreeNode *leftSibling = node->children[index - 1];

    // 오른쪽 child 키들을 한 칸 오른쪽으로 이동
    for (int i = child->numKeys; i > 0; i--) {
        child->keys[i] = child->keys[i - 1];
    }
    if (!child->isLeaf) {
        for (int i = child->numKeys + 1; i > 0; i--) {
            child->children[i] = child->children[i - 1];
        }
    }

    // 부모로부터 키를 child로 내려줌
    child->keys[0] = node->keys[index - 1];
    if (!child->isLeaf) {
        child->children[0] = leftSibling->children[leftSibling->numKeys];
    }

    // 왼쪽 형제의 마지막 키를 부모로 올림
    node->keys[index - 1] = leftSibling->keys[leftSibling->numKeys - 1];
    leftSibling->numKeys--;
    child->numKeys++;
}

void borrowFromRight(BTreeNode *node, int index) {
    BTreeNode *child = node->children[index];
    BTreeNode *rightSibling = node->children[index + 1];

    // 부모의 키를 child로 내려줌
    child->keys[child->numKeys] = node->keys[index];
    if (!child->isLeaf) {
        child->children[child->numKeys + 1] = rightSibling->children[0];
    }

    // 오른쪽 형제의 첫 번째 키를 부모로 올림
    node->keys[index] = rightSibling->keys[0];

    // 오른쪽 형제의 키들과 자식들을 앞으로 shift
    for (int i = 0; i < rightSibling->numKeys - 1; i++) {
        rightSibling->keys[i] = rightSibling->keys[i + 1];
    }
    if (!rightSibling->isLeaf) {
        for (int i = 0; i < rightSibling->numKeys; i++) {
            rightSibling->children[i] = rightSibling->children[i + 1];
        }
    }

    child->numKeys++;
    rightSibling->numKeys--;
}

int findPredecessor(BTreeNode *node, int index) {
    BTreeNode *cur = node->children[index];
    while (!cur->isLeaf) {
        cur = cur->children[cur->numKeys];
    }
    return cur->keys[cur->numKeys - 1];
}

int findSuccessor(BTreeNode *node, int index) {
    BTreeNode *cur = node->children[index + 1];
    while (!cur->isLeaf) {
        cur = cur->children[0];
    }
    return cur->keys[0];
}

void mergeChildNode(BTreeNode *node, int index) {
    BTreeNode *leftChild = node->children[index];
    BTreeNode *rightChild = node->children[index + 1];

    // 가운데 키를 왼쪽 자식에 삽입
    leftChild->keys[leftChild->numKeys] = node->keys[index];

    // 오른쪽 자식의 키들과 자식들을 왼쪽에 이어붙임
    for (int i = 0; i < rightChild->numKeys; i++) {
        leftChild->keys[leftChild->numKeys + 1 + i] = rightChild->keys[i];
    }
    if (!leftChild->isLeaf) {
        for (int i = 0; i <= rightChild->numKeys; i++) {
            leftChild->children[leftChild->numKeys + 1 + i] = rightChild->children[i];
        }
    }

    leftChild->numKeys += rightChild->numKeys + 1;

    // 부모에서 키와 자식 포인터 제거
    for (int i = index; i < node->numKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }
    for (int i = index + 1; i < node->numKeys; i++) {
        node->children[i] = node->children[i + 1];
    }

    node->numKeys--;
    free(rightChild);
}