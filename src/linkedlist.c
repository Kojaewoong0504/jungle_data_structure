//
// Created by 고재웅 on 25. 4. 11.
//
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

Node* create_node(int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void insert_end(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
}

void insert_front(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    new_node->next = *head;
    *head = new_node;
}


void delete_node(Node** head, int data) {
    if (*head == NULL) return;
    Node* cur = *head;
    Node* prev = NULL;

    while (cur != NULL) {
        if (cur->data == data) {
            if (prev == NULL) {
                *head = cur->next;
            }else {
                prev->next = cur->next;
            }
            Node* temp = cur;
            cur = cur->next;
            free(temp);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}


void print_list(Node* head) {
    Node* current = head;
    while (current) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

Node* find_node(Node* head, int data) {
// 원하는 노드를 찾는다.
    if (head == NULL) return NULL;
    Node* cur = head;

    while (cur != NULL) {
        if (cur->data == data) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}


// 링크드 리스트 전체 제거
void free_list(Node* head) {
    // 임시 노드 선언
    Node* temp;
    // head의 값이 NULL이 될 때 까지 반복문 실행
    while (head) {
        // 코드 설명 - 헤드의 연결을 끊고 제거하는 것을 반복한다.
        temp = head;
        head = head->next;
        free(temp);
    }
}