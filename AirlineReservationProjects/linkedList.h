#pragma once

#include <stdio.h>
#include <stdlib.h>

/*
LINKED_LIST�� ���Ǵ� ��� */
typedef struct listnode
{
	void* data;
	struct listnode* next;
} LIST_NODE;

/*
����ü LINKED_LIST�� ó�� ���, ������ ���, ũ�⸦ ���´�. */
typedef struct linkedList
{
	LIST_NODE* first;
	LIST_NODE* last;
	int size;
} LINKED_LIST;


/*
LINKED_LIST ����ü �ϳ��� ����� ���� �������� �ʱ�ȭ�Ͽ� ��ȯ�Ѵ�. */
LINKED_LIST* generateLinkedList();

/*
linkedList�� ���� �ڿ� data�� ���� ��带 �����.*/
void addToList(LINKED_LIST* linkedList, const void* data);

/*
linkedList�κ��� data�� ���� ��带 ã�� �����Ѵ�.*/
void removeFromList(LINKED_LIST* linkedList, const void* data);

/*
����Ʈ���� data�� ã���� 1��
�� ã�Ҵٸ� 0�� ��ȯ�Ѵ�. */
int findFromList(LINKED_LIST* linkedList, const void* data);

/*
linkedList�� ���� ó�� ����� data�� ��ȯ�Ѵ�.
���� ó�� ��尡 NULL�̸� NULL�� ��ȯ�Ѵ�. */
void* getFirstFromList(LINKED_LIST* linkedList);

/*
linkedList�� ���� ������ ����� data�� ��ȯ�Ѵ�.
���� ������ ��尡 NULL�̸� NULL�� ��ȯ�Ѵ�. */
void* getLastFromList(LINKED_LIST* linkedList);

/*
linkedList���� (index + 1)��° ����� data�� ��ȯ�Ѵ�. */
void* getFromList(LINKED_LIST* linkedList, int index);