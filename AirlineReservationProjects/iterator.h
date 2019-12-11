#pragma once

#include <stdlib.h>

#include "linkedList.h"

/*
����ü ITERATOR�� ���� ��带 ���´�.
generateIterator�Լ��� ���� ���� ��, getNextData�Լ��� ����
linkedList�� ���� ù ����� data���� �ϳ��� ������ �� �ִ�. */
typedef struct iterator
{
	LIST_NODE* next;
} ITERATOR;

/*
linkedList�� ���� �ݺ��ڸ� ����� ��ȯ�Ѵ�. */
ITERATOR* generateIterator(LINKED_LIST* linkedList);

/*
iterator�� ���� ��尡 ��ȯ�Ǹ�,
iterator���� next���� �� ���� ���� �ٲ��. */
void* getNextData(ITERATOR* iterator);

/*
iterator�� next ��尡 NULL���� �ƴ��� Ȯ���Ѵ�.
NULL�� �ƴϸ� 1��, NULL�̸� 0�� ��ȯ�Ѵ�. */
int hasNextData(ITERATOR* iterator);

/*
iterator�� �޸𸮸� �����Ѵ�. */
void freeIterator(ITERATOR** iterator);