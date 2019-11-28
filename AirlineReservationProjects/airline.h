/*
airline.h

내부에 전역 변수 LINKED_LIST* airlineList가 선언되어 있다.
이것은 생성된 모든 AIRLINE을 담는다.
*/

#pragma once

#include <time.h>

#include "linkedList.h"
#include "city.h"
#include "iterator.h"

/*
구조체 AIRLINE은 항공기 운행 정보를 가지며, 출발지, 도착지, 출발시간, 도착시간을 가진다.
airlineList에 추가가 필요한 경우, addToAirlineList함수를 사용해 추가한다. */
typedef struct airline
{
	CITY* source;
	CITY* destination;
	struct tm* departureTime;
	struct tm* arrivalTime;
} AIRLINE;

/*
인자로 출발지, 도착지, 출발시간을 받는다.
도착시간은 출발지, 도착지 사이의 거리를 비행 속도로 나눈 것을 출발 시간에 더하여 구한다.*/
AIRLINE* generateAirline(CITY* source, CITY* destination, struct tm* departureTime);

/*
전역 변수 airlineList에 AIRLINE을 추가한다. */
void addToAirlineList(LINKED_LIST* airlineList, CITY* source, CITY* destination, struct tm* departureTime);

/*
airlineList에 같은 출발지, 도착지, 출발시간을 갖는 것이 있는지 찾는다.
찾는다면 1을, 못 찾는다면 0을 반환한다. */
int findFromAirlineList(LINKED_LIST* airlineList, CITY* source, CITY* destination, struct tm* departureTime);