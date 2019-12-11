#pragma once

#include <time.h>

#include "city.h"
#include "linkedList.h"
#include "flight.h"
#include "customTime.h"

/*
구조체 PATH는 연속된 FLIGHT을 갖는다.
여러 CITY를 경유해서 가는 경우를 나타내기 위해 구현되었다. */
typedef struct path
{
	LINKED_LIST* flightList;
} PATH;

/*
구조체 PATH를 생성하고 내부 변수를 초기화하여 반환한다. */
PATH* generatePath();


/*
path를 복제하여 반환한다. */
PATH* generateClonePath(PATH* path);

/*
path가 비어있다면 그냥 추가한다.
비어있지 않고, path안의 flight중 마지막의 목적지가 추가될 flight의 출발지가 같고,
추가될 flight의 출발 시간이 flight마지막 flight의 도착 시간보다 나중인 경우에 추가한다.
그 외의 경우는 추가하지 않고 0을 반환한다. */
int addToPath(PATH* path, FLIGHT* flight);

/*
path안의 가장 마지막 FLIGHT를 꺼낸다. */
FLIGHT* popPath(PATH* path);

/*
path로부터 처음 FLIGHT의 출발지를 반환한다. */
CITY* getSource(PATH* path);

/*
path로부터 마지막 FLIGHT의 도착지를 반환한다. */
CITY* getDestination(PATH* path);

/*
path로부터 처음 FLIGHT의 출발 시간을 반환한다.*/
TIME* getDepartureTime(PATH* path);

/*
path로부터 마지막 FLIGHT의 도착 시간을 반환한다. */
TIME* getArrivalTime(PATH* path);

/*
path로부터 마지막 FLIGHT의 도착 시간 - 처음 FLIGHT의 출발 시간을 계산하여 반환한다. */
TIME* getElapsedTime(PATH* path);

/*
경유지의 수를 반환한다. (출발지, 도착지를 제외한 거치는 도시의 수)*/
int getNumberOfTransit(PATH* path);

/*
departureTime에 출발하는 source로부터 destination까지의 모든 경로를 찾아 반환한다. 
어떠한 경로도 못 찾을 경우, NULL을 반환한다. */
LINKED_LIST* findAllPath(LINKED_LIST* flightList[], TIME* departureTime, CITY* source, CITY* destination, int seatClass);

/*
depatureTime보다 늦는 FLIGHT들로부터 출발지가 source이고 도착지가 destination이 되도록
FLIGHT이 구성된 PATH를 만들어 반환한다. 
경로가 없다면 NULL을 반환한다. */
PATH* findPathForShortestFlightTime(LINKED_LIST* flightList[], TIME* departureTime, CITY* source, CITY* destination);

/*
path의 메모리를 해제한다. */
void freePath(PATH** path);

/*
path를 간략하게 문자열로 변환하여 반환한다. 
출발지 출발시간 -- 소요 시간 (경유지 수) --> 도착시간 도착지 좌석등급
seatClassStr이 NULL이면 좌석등급이 표시되지 않는다. */
char* pathToStr(PATH* path, char* seatClassStr);