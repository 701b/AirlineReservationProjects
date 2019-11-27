#include "linkedList.h"

LIST_NODE* generateNode(const void* data)
{
	LIST_NODE* node = malloc(sizeof(LIST_NODE));

	node->data = data;
	node->next = NULL;

	return node;
}

LINKED_LIST* generateLinkedList()
{
	LINKED_LIST* linkedList = malloc(sizeof(LINKED_LIST));

	linkedList->first = NULL;
	linkedList->last = NULL;
	linkedList->size = 0;
}

ITERATOR* generateIterator(LINKED_LIST* linkedList)
{
	ITERATOR* iterator = malloc(sizeof(ITERATOR));

	iterator->next = linkedList->first;

	return iterator;
}

void addToList(LINKED_LIST* linkedList, const void* data)
{
	LIST_NODE* node = generateNode(data);

	if (linkedList->size == 0)
	{
		linkedList->first = node;
		linkedList->last = node;
		linkedList->size++;
	}
	else
	{
		linkedList->last->next = node;
		linkedList->last = node;
		linkedList->size++;
	}
}

void removeFromList(LINKED_LIST* linkedList, void* data)
{
	LIST_NODE* targetNode = linkedList->first;
	LIST_NODE* previousNode = NULL;

	for (; targetNode != NULL; targetNode = targetNode->next)
	{
		if (targetNode->data == data)
		{
			if (previousNode == NULL)
			{
				linkedList->first = targetNode->next;
				free(targetNode);
			}
			else
			{
				previousNode->next = targetNode->next;
				free(targetNode);
			}

			linkedList->size--;
			break;
		}
	}
}

int findFromList(LINKED_LIST* linkedList, void* data)
{
	LIST_NODE* targetNode = linkedList->first;

	for (int index = 0; targetNode != NULL; index++, targetNode = targetNode->next)
	{
		if (targetNode->data == data)
		{
			return index;
		}
	}
}

void* getFirstFromList(LINKED_LIST* linkedList)
{
	if (linkedList->first == NULL)
	{
		return NULL;
	}

	return linkedList->first->data;
}

void* getLastFromList(LINKED_LIST* linkedList)
{
	if (linkedList->last == NULL)
	{
		return NULL;
	}

	return linkedList->last->data;
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

