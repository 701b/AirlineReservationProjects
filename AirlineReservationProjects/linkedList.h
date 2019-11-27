#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct listnode
{
	void* data;
	struct listnode* next;
} LIST_NODE;

typedef struct linkedList
{
	LIST_NODE* first;
	LIST_NODE* last;
	int size;
} LINKED_LIST;

typedef struct iterator
{
	LIST_NODE* next;
} ITERATOR;

LINKED_LIST* generateLinkedList();
ITERATOR* generateIterator(LINKED_LIST* linkedList);

void addToList(LINKED_LIST* linkedList, const void* data);
void removeFromList(LINKED_LIST* linkedList, const void* data);

/*
����Ʈ���� data�� ã���� �ε�����,
�� ã�Ҵٸ� -1�� ��ȯ�Ѵ�.
 */
int findFromList(LINKED_LIST* linkedList, const void* data);

void* getFirstFromList(LINKED_LIST* linkedList);
void* getLastFromList(LINKED_LIST* linkedList);

void* getNextData(ITERATOR* iterator);