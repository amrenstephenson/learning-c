#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *next;
};

struct LL {
	int size;
	struct Node *head;
};

struct LL *makeLL() {
	struct LL *ll = malloc(sizeof(struct LL));
	if (!ll)
		return NULL;

	ll->size = 0;
	ll->head = NULL;

	return ll;
}

struct Node *makeNode(int newData) {
	struct Node *newNode = malloc(sizeof(struct Node));
	if (!newNode)
		return NULL;

	newNode->data = newData;
	newNode->next = NULL;

	return newNode;
}

struct Node *append(struct LL *ll, int newData) {
	struct Node *newNode = makeNode(newData);
	if (!newNode)
		return NULL;

	// If headless, make new node the head.
	if (!ll->head) {
		ll->head = newNode;
		ll->size = 1;

		return newNode;
	}

	// Loop until 'node' is the last node.
	struct Node *node = ll->head;
	while (node->next) {
		node = node->next;
	}

	// Add new node after last node.
	node->next = newNode;
	ll->size += 1;

	return newNode;
}

bool removeLast(struct LL *ll) {
	// Can't remove from headless list.
	if (!ll->head) {
		return false;
	}

	// If the head is the only node, remove the head.
	if (!ll->head->next) {
		free(ll->head);
		ll->head = NULL;
		ll->size = 0;

		return true;
	}

	// Loop until 'node' is the penultimate node.
	struct Node *node = ll->head;
	while (node->next->next) {
		node = node->next;
	}

	// Remove last node.
	free(node->next);
	node->next = NULL;
	ll->size -= 1;

	return true;
}

void printList(struct LL *ll) {
	printf("[%d] ", ll->size);

	struct Node *node = ll->head;
	while (node) {
		printf("%d,", node->data);
		node = node->next;
	}

	printf("\n");
}

void freeList(struct LL *ll) {
	struct Node *node = ll->head;
	struct Node *tempNode = NULL;

	while (node) {
		tempNode = node->next;

		// node->next = NULL; As Tommy (https://github.com/Muirey03) said, I don't need this.
		free(node);

		node = tempNode;
	}

	ll->head = NULL;

	free(ll);
}

int main() {
	struct LL *myList = makeLL();

	append(myList, 1);
	append(myList, 2);
	removeLast(myList);
	append(myList, 3);
	printList(myList);

	freeList(myList);
	myList = NULL;

	getchar();

	return 0;
}