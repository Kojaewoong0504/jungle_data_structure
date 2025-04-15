//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// test_code ///////////////////////////////////////////

int tests_run = 0;
int tests_failed = 0;

char *test_insert_no_duplicates() {
	LinkedList ll = {0, NULL};
	int index;

	printf("\n--- [TEST] insertSortedLL: case 1 ---\n");

	index = insertSortedLL(&ll, 2);
	mu_assert_eq_int(0, index);
	index = insertSortedLL(&ll, 3);
	mu_assert_eq_int(1, index);
	index = insertSortedLL(&ll, 5);
	mu_assert_eq_int(2, index);
	index = insertSortedLL(&ll, 7);
	mu_assert_eq_int(3, index);
	index = insertSortedLL(&ll, 9);
	mu_assert_eq_int(4, index);
	printf("---------- [insertSortedLL] ----------\n");
	printf("Calling insertSortedLL() with a value of 8\n");
	index = insertSortedLL(&ll, 8);
	mu_assert_eq_int(4, index);
	printf("---------- [result] ----------\n");
	printf("Final linked list : ");
	removeAllItems(&ll);
	return 0;
}

char *test_insert_no_duplicates2() {
	LinkedList ll = {0, NULL};
	int index;

	printf("\n--- [TEST] insertSortedLL: case 2 ---\n");

	index = insertSortedLL(&ll, 5);
	mu_assert_eq_int(0, index);
	index = insertSortedLL(&ll, 7);
	mu_assert_eq_int(1, index);
	index = insertSortedLL(&ll, 9);
	mu_assert_eq_int(2, index);
	index = insertSortedLL(&ll, 11);
	mu_assert_eq_int(3, index);
	index = insertSortedLL(&ll, 15);
	mu_assert_eq_int(4, index);
	printf("---------- [insertSortedLL] ----------\n");
	printf("Calling insertSortedLL() with a value of 7\n");
	index = insertSortedLL(&ll, 7);
	printf("---------- [result] ----------\n");
	printf("Inserted 7 at index %d\n", index);
	mu_assert_eq_int(-1, index);
	removeAllItems(&ll);
	return 0;
}
//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	mu_run_test(test_insert_no_duplicates);
	mu_run_test(test_insert_no_duplicates2);
	printf("✅ Tests run: %d\n", tests_run);
	printf("❌ Tests failed: %d\n", tests_failed);

	return tests_failed;
	/*
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
	*/
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	ListNode *newNode, *cur = ll->head, *prev = NULL;
	int index = 0;

	printf("\n[INSERT] Trying to insert %d into linked list...\n", item);

	// 삽입 위치 탐색 + 중복 확인
	while (cur != NULL && cur->item < item) {
		prev = cur;
		cur = cur->next;
		index++;
	}

	if (cur != NULL && cur->item == item) {
		printf("❌ Duplicate detected: %d already exists at index %d\n", item, index);
		return -1;
	}

	newNode = (ListNode *) malloc(sizeof(ListNode));
	if (newNode == NULL) {
		printf("❌ Memory allocation failed for %d\n", item);
		return -1;
	}

	newNode->item = item;
	newNode->next = cur;

	if (prev == NULL) {
		printf("🔗 Inserting %d at the head\n", item);
		ll->head = newNode;
	} else {
		printf("🔗 Inserting %d after %d\n", item, prev->item);
		prev->next = newNode;
	}

	ll->size++;
	printf("✅ Inserted %d at index %d | New size: %d\n", item, index, ll->size);

	// 현재 리스트 상태 출력
	printf("📌 Current list: ");
	ListNode *temp = ll->head;
	while (temp != NULL) {
		printf("%d ", temp->item);
		temp = temp->next;
	}
	printf("\n");

	return index;
}


///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
