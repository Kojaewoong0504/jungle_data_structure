//
// Created by 고재웅 on 25. 4. 12.
//

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

// 이진 트리 노드 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 노드 생성
TreeNode* create_node(int data);

// 왼쪽 자식 삽입
void insert_left(TreeNode* parent, int data);

// 오른쪽 자식 삽입
void insert_right(TreeNode* parent, int data);

// 전위 순회 (루트 -> 좌 -> 우)
void preorder_traversal(TreeNode* root);

// 중위 순회 (좌 -> 루트 -> 우)
void inorder_traversal(TreeNode* root);

// 후위 순회 (좌 -> 우 -> 루트)
void postorder_traversal(TreeNode* root);

// 트리 메모리 해제
void free_tree(TreeNode* root);

int count_nodes(TreeNode* root);

int tree_height(TreeNode* root);

int count_leaves(TreeNode* root);

int is_full_tree(TreeNode* root);


#endif
