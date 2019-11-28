/*
airline.h

���ο� ���� ���� LINKED_LIST* airlineList�� ����Ǿ� �ִ�.
�̰��� ������ ��� AIRLINE�� ��´�.
*/

#pragma once

#include <time.h>

#include "linkedList.h"
#include "city.h"
#include "iterator.h"

/*
����ü AIRLINE�� �װ��� ���� ������ ������, �����, ������, ��߽ð�, �����ð��� ������.
airlineList�� �߰��� �ʿ��� ���, addToAirlineList�Լ��� ����� �߰��Ѵ�. */
typedef struct airline
{
	CITY* source;
	CITY* destination;
	struct tm* departureTime;
	struct tm* arrivalTime;
} AIRLINE;

/*
���ڷ� �����, ������, ��߽ð��� �޴´�.
�����ð��� �����, ������ ������ �Ÿ��� ���� �ӵ��� ���� ���� ��� �ð��� ���Ͽ� ���Ѵ�.*/
AIRLINE* generateAirline(CITY* source, CITY* destination, struct tm* departureTime);

/*
���� ���� airlineList�� AIRLINE�� �߰��Ѵ�. */
void addToAirlineList(LINKED_LIST* airlineList, CITY* source, CITY* destination, struct tm* departureTime);

/*
airlineList�� ���� �����, ������, ��߽ð��� ���� ���� �ִ��� ã�´�.
ã�´ٸ� 1��, �� ã�´ٸ� 0�� ��ȯ�Ѵ�. */
int findFromAirlineList(LINKED_LIST* airlineList, CITY* source, CITY* destination, struct tm* departureTime);