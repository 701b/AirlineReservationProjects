#include "iterator.h"

ITERATOR* generateIterator(LINKED_LIST* linkedList)
{
	ITERATOR* iterator = malloc(sizeof(ITERATOR));

	iterator->next = linkedList->first;

	return iterator;
}

void* getNextData(ITERATOR* iterator)
{
	if (iterator->next == NULL)
	{
		return NULL;
	}

	void* data = iterator->next->data;

	iterator->next = iterator->next->next;

	return data;
}
