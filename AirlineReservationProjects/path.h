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
path가 비어있다면 그냥 추가
비어있지 않고, path안의 airline중 마지막의 목적지가 추가될 airline의 출발지가 같고,
추가될 airline의 출발 시간이 airline마지막 airline의 도착 시간보다 나중인 경우에 추가한다.
그 외의 경우는 추가하지 않고 0을 반환한다.
*/
int addToPath(PATH* path, AIRLINE* airline);

CITY* getSource(PATH* path);
CITY* getDestination(PATH* path);
time_t getDepartureTime(PATH* path);
time_t getArrivalTime(PATH* path);
time_t getElapsedTime(PATH* path);

PATH* findPathForShortestFlightTime(time_t departureTime, CITY* source, CITY* destination);