/*
airline.h

���ο� ���� ���� LINKED_LIST* airlineList�� ����Ǿ� �ִ�.
�̰��� ������ ��� AIRLINE�� ��´�.
*/

#pragma once

#include "linkedList.h"
#include "city.h"
#include "iterator.h"
#include "customTime.h"

/*
����ü AIRLINE�� �װ��� ���� ������ ������, �����, ������, ��߽ð�, �����ð��� ������.
airlineList�� �߰��� �ʿ��� ���, addToAirlineList�Լ��� ����� �߰��Ѵ�. */
typedef struct airline
{
	CITY* source;
	CITY* destination;
	TIME* departureTime;
	TIME* arrivalTime;
} AIRLINE;

/*
���ڷ� �����, ������, ��߽ð��� �޴´�.
�����ð��� �����, ������ ������ �Ÿ��� ���� �ӵ��� ���� ���� ��� �ð��� ���Ͽ� ���Ѵ�.*/
AIRLINE* generateAirline(CITY* source, CITY* destination, TIME* departureTime);

/*
���� ���� airlineList�� AIRLINE�� �߰��Ѵ�. */
void addToAirlineList(LINKED_LIST* airlineList, CITY* source, CITY* destination, TIME* departureTime);

/*
airlineList�� ���� �����, ������, ��߽ð��� ���� ���� �ִ��� ã�´�.
ã�´ٸ� 1��, �� ã�´ٸ� 0�� ��ȯ�Ѵ�. */
int findFromAirlineList(LINKED_LIST* airlineList, CITY* source, CITY* destination, TIME* departureTime);