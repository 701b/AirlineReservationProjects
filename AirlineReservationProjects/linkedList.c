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

	return linkedList;
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

	for (; targetNode != NULL; previousNode = targetNode, targetNode = targetNode->next)
	{
		if (targetNode->data == data)
		{
			if (previousNode == NULL)
			{
				linkedList->first = targetNode->next;
			}
			else
			{
				previousNode->next = targetNode->next;
			}

			if (linkedList->last == targetNode)
			{
				linkedList->last = previousNode;
			}

			free(targetNode);
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
			//return index;
			return 1;
		}
	}

	// return -1;
	return 0;
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

void* getFromList(LINKED_LIST* linkedList, int index)
{
	LIST_NODE* node = linkedList->first;

	if (index >= linkedList->size)
	{
		return NULL;
	}

	for (int i = 0; i < index; i++, node = node->next);

	return node->data;
}

void freeLinkedList(LINKED_LIST** linkedList)
{
	if (*linkedList != NULL)
	{
		if ((*linkedList)->size == 0)
		{
			free(*linkedList);
			return;
		}

		LIST_NODE* node = (*linkedList)->first;
		LIST_NODE* nextNode = node->next;

		for (; nextNode != NULL; node = nextNode, nextNode = nextNode->next)
		{
			free(node);
		}

		free(node);
		free(*linkedList);
	}
}
