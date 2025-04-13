//
// Created by 고재웅 on 25. 4. 12.
//

#ifndef BST_H
#define BST_H

typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// 생성 및 삽입
BSTNode* bst_create_node(int data);
BSTNode* bst_insert(BSTNode* root, int data);

// 탐색
BSTNode* bst_search(BSTNode* root, int target);

// 삭제
BSTNode* bst_delete(BSTNode* root, int target);

// 최소, 최대값 찾기
BSTNode* bst_find_min(BSTNode* root);
BSTNode* bst_find_max(BSTNode* root);

// 순회 출력
void bst_inorder(BSTNode* root);
void bst_preorder(BSTNode* root);
void bst_postorder(BSTNode* root);

// 해제
void bst_free(BSTNode* root);

#endif
