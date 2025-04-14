//
// Created by 고재웅 on 25. 4. 14.
//
// b_tree.h
#ifndef B_TREE_H
#define B_TREE_H

#include <stdbool.h>
#include <stdlib.h>

#define B_TREE_ORDER 5           // 5차 B-트리: 자식 최대 개수
#define MAX_KEYS (B_TREE_ORDER-1)  // 키 최대 개수
#define MIN_KEYS ((B_TREE_ORDER+1)/2 - 1)  // 키 최소 개수: ceil(B_TREE_ORDER/2)-1

typedef struct BTreeNode {
    bool isLeaf;                        // leaf 여부: true이면 리프 노드
    int numKeys;                        // 현재 저장된 키의 개수
    int keys[MAX_KEYS];                 // 키를 저장하는 배열 (정렬되어 있음)
    struct BTreeNode *children[B_TREE_ORDER]; // 자식 노드에 대한 포인터 배열
} BTreeNode;

// 노드 생성: isLeaf 값에 따라 리프여부 설정, numKeys 초기화
BTreeNode* createNode(bool isLeaf);

// 삽입 관련 함수들
BTreeNode* insert(BTreeNode *root, int key);
void insertNode(BTreeNode *node, int key);
void splitNode(BTreeNode *parent, int index, BTreeNode *child);

// 삭제 관련 함수들
BTreeNode* deleteNode(BTreeNode *root, int key);         // 전체 삭제 동작
void deleteValFromNode(BTreeNode *node, int key);          // 노드 내에서 값 삭제
void balanceNode(BTreeNode *node, int index);              // 삭제 후 노드 균형 맞추기 (병합, 빌리기)
void borrowFromRight(BTreeNode *node, int index);
void borrowFromLeft(BTreeNode *node, int index);
void mergeNode(BTreeNode *node, int index);
void deleteInnerNode(BTreeNode *node, int key);
void overrideWithPredecessor(BTreeNode *node, int index);
int findPredecessor(BTreeNode *node, int index);
void overrideWithSuccessor(BTreeNode *node, int index);
int findSuccessor(BTreeNode *node, int index);
void mergeChildNode(BTreeNode *node, int index);

// 탐색 함수
BTreeNode* searchNode(BTreeNode *root, int key);

// 메모리 해제 함수
void freeBTree(BTreeNode *root);

#endif // B_TREE_H
