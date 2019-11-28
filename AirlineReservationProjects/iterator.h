#pragma once

#include <stdlib.h>

#include "linkedList.h"

/*
구조체 ITERATOR는 다음 노드를 갖는다.
generateIterator함수를 통해 생성 후, getNextData함수를 통해
linkedList의 가장 첫 노드의 data부터 하나씩 가져올 수 있다. */
typedef struct iterator
{
	LIST_NODE* next;
} ITERATOR;

/*
linkedList로 부터 반복자를 만들어 반환한다. */
ITERATOR* generateIterator(LINKED_LIST* linkedList);

/*
iterator의 다음 노드가 반환되며,
iterator안의 next노드는 그 다음 노드로 바뀐다. */
void* getNextData(ITERATOR* iterator);