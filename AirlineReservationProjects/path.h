#pragma once

#include <time.h>

#include "city.h"
#include "linkedList.h"
#include "airline.h"

typedef struct path
{
	LINKED_LIST* airlineList;
} PATH;

PATH* generatePath();

/*
path�� ����ִٸ� �׳� �߰�
������� �ʰ�, path���� airline�� �������� �������� �߰��� airline�� ������� ����,
�߰��� airline�� ��� �ð��� airline������ airline�� ���� �ð����� ������ ��쿡 �߰��Ѵ�.
�� ���� ���� �߰����� �ʰ� 0�� ��ȯ�Ѵ�.
*/
int addToPath(PATH* path, AIRLINE* airline);

CITY* getSource(PATH* path);
CITY* getDestination(PATH* path);
time_t getDepartureTime(PATH* path);
time_t getArrivalTime(PATH* path);
time_t getElapsedTime(PATH* path);

PATH* findPathForShortestFlightTime(time_t departureTime, CITY* source, CITY* destination);