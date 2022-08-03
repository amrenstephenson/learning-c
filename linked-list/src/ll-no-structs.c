#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA(node) *(int *)node
#define NEXT(node) *(char **)((node + sizeof(int)))

#define SIZE(ll) *(int *)ll
#define HEAD(ll) *(char **)((ll + sizeof(int)))

char *makeLL() {
	char *ll = malloc(sizeof(int) + sizeof(char *));
	if (!ll)
		return NULL;

	SIZE(ll) = 0;
	HEAD(ll) = NULL;

	return ll;
}

char *makeNode(int newData) {
	char *newNode = malloc(sizeof(int) + sizeof(char *));
	if (!newNode)
		return NULL;

	DATA(newNode) = newData;
	NEXT(newNode) = NULL;

	return newNode;
}

char *append(char *ll, int newData) {
	char *newNode = makeNode(newData);
	if (!newNode)
		return NULL;

	// If headless, make new node the head.
	if (!HEAD(ll)) {
		HEAD(ll) = newNode;
		SIZE(ll) = 1;

		return newNode;
	}

	// Loop until 'node' is the last node.
	char *node = HEAD(ll);
	while (NEXT(node)) { // CHECK ME
		node = NEXT(node);
	}

	// Add new node after last node.
	NEXT(node) = newNode;
	SIZE(ll) += 1;

	return newNode;
}

bool removeLast(char *ll) {
	// Can't remove from headless list.
	if (!HEAD(ll)) {
		return false;
	}

	// If the head is the only node, remove the head.
	if (!NEXT(HEAD(ll))) {
		free(HEAD(ll));
		HEAD(ll) = NULL;
		SIZE(ll) = 0;

		return true;
	}

	// Loop until 'node' is the penultimate node.
	char *node = HEAD(ll);
	while (NEXT(NEXT(node))) {
		node = NEXT(node);
	}

	// Remove last node.
	free(NEXT(node));
	NEXT(node) = NULL;
	SIZE(ll) -= 1;

	return true;
}

void printList(char *ll) {
	printf("[%d] ", SIZE(ll));

	char *node = HEAD(ll);
	while (node) {
		printf("%d,", DATA(node));
		node = NEXT(node);
	}

	printf("\n");
}

void freeList(char *ll) {
	char *node = HEAD(ll);
	char *tempNode = NULL;

	while (node) {
		tempNode = NEXT(node);

		free(node);

		node = tempNode;
	}

	HEAD(ll) = NULL;

	free(ll);
}

int main() {
	char *myList = makeLL();

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