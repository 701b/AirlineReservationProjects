#pragma once

#include <stdio.h>
#include <stdlib.h>

/*
LINKED_LIST에 사용되는 노드 */
typedef struct listnode
{
	void* data;
	struct listnode* next;
} LIST_NODE;

/*
구조체 LINKED_LIST는 처음 노드, 마지막 노드, 크기를 갖는다. */
typedef struct linkedList
{
	LIST_NODE* first;
	LIST_NODE* last;
	int size;
} LINKED_LIST;


/*
LINKED_LIST 구조체 하나를 만들고 내부 변수들을 초기화하여 반환한다. */
LINKED_LIST* generateLinkedList();

/*
linkedList의 가장 뒤에 data를 가진 노드를 만든다.*/
void addToList(LINKED_LIST* linkedList, const void* data);

/*
linkedList로부터 data를 가진 노드를 찾아 제거한다.*/
void removeFromList(LINKED_LIST* linkedList, const void* data);

/*
리스트에서 data를 찾으면 1을
못 찾았다면 0을 반환한다. */
int findFromList(LINKED_LIST* linkedList, const void* data);

/*
linkedList의 가장 처음 노드의 data를 반환한다.
가장 처음 노드가 NULL이면 NULL을 반환한다. */
void* getFirstFromList(LINKED_LIST* linkedList);

/*
linkedList의 가장 마지막 노드의 data를 반환한다.
가장 마지막 노드가 NULL이면 NULL을 반환한다. */
void* getLastFromList(LINKED_LIST* linkedList);

/*
linkedList에서 (index + 1)번째 노드의 data를 반환한다. */
void* getFromList(LINKED_LIST* linkedList, int index);