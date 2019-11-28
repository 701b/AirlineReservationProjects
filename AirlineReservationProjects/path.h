#pragma once

#include <time.h>

#include "city.h"
#include "linkedList.h"
#include "airline.h"

/*
구조체 PATH는 연속된 AIRLINE을 갖는다.
여러 CITY를 경유해서 가는 경우를 나타내기 위해 구현되었다. */
typedef struct path
{
	LINKED_LIST* airlineList;
} PATH;

/*
구조체 PATH를 생성하고 내부 변수를 초기화하여 반환한다. */
PATH* generatePath();

/*
path가 비어있다면 그냥 추가한다.
비어있지 않고, path안의 airline중 마지막의 목적지가 추가될 airline의 출발지가 같고,
추가될 airline의 출발 시간이 airline마지막 airline의 도착 시간보다 나중인 경우에 추가한다.
그 외의 경우는 추가하지 않고 0을 반환한다. */
int addToPath(PATH* path, AIRLINE* airline);

/*
path로부터 처음 AIRLINE의 출발지를 반환한다. */
CITY* getSource(PATH* path);

/*
path로부터 마지막 AIRLINE의 도착지를 반환한다. */
CITY* getDestination(PATH* path);

/*
path로부터 처음 AIRLINE의 출발 시간을 반환한다.*/
time_t getDepartureTime(PATH* path);

/*
path로부터 마지막 AIRLINE의 도착 시간을 반환한다. */
time_t getArrivalTime(PATH* path);

/*
path로부터 마지막 AIRLINE의 도착 시간 - 처음 AIRLINE의 출발 시간을 계산하여 반환한다. */
time_t getElapsedTime(PATH* path);

/*
depatureTime보다 늦는 AIRLINE들로부터 출발지가 source이고 도착지가 destination이 되도록
AIRLINE이 구성된 PATH를 만들어 반환한다. 
경로가 없다면 NULL을 반환한다. */
PATH* findPathForShortestFlightTime(struct tm* departureTime, CITY* source, CITY* destination);