/*
flight.h

내부에 전역 변수 LINKED_LIST* flightList가 선언되어 있다.
이것은 생성된 모든 FLIGHT을 담는다.
*/

#pragma once

#include "linkedList.h"
#include "city.h"
#include "iterator.h"
#include "customTime.h"
#include "airplane.h"

/*
구조체 FLIGHT은 항공기 운행 정보를 가지며, 출발지, 도착지, 출발시간, 도착시간을 가진다.
flightList에 추가가 필요한 경우, addToflightList함수를 사용해 추가한다. */
typedef struct flight
{
	CITY* source;
	CITY* destination;
	TIME* departureTime;
	TIME* arrivalTime;
	AIRPLANE* airplane;
	int seatClass;
	int seatRowNumber;
	int seatColumnNumber;
} FLIGHT;

/*
인자로 출발지, 도착지, 출발시간을 받는다.
도착시간은 출발지, 도착지 사이의 거리를 비행 속도로 나눈 것을 출발 시간에 더하여 구한다.*/
FLIGHT* generateFlight(CITY* source, CITY* destination, TIME* departureTime, AIRPLANE* airplane);

/*
flight을 복제하여 반환한다. 예약을 만들 때 쓰인다. */
FLIGHT* generateCloneFlight(FLIGHT* flight);

/*
전역 변수 flightList에 FLIGHT을 추가한다. */
void addToFlightList(LINKED_LIST* flightList, CITY* source, CITY* destination, TIME* departureTime, AIRPLANE* airplane);

/*
flightList에 같은 출발지, 도착지, 출발시간을 갖는 것이 있는지 찾는다.
찾는다면 1을, 못 찾는다면 0을 반환한다. */
int findFromFlightList(LINKED_LIST* flightList, CITY* source, CITY* destination, TIME* departureTime);

/*
좌석을 지정하고, 해당 항공기의 지정 좌석을 자리 없음으로 바꾼다. */
void setSeat(FLIGHT* flight, int seatClass, int seatRowNumber, int seatColumnNumber);

/*
*/
char* flightToStr(FLIGHT* flight, FLIGHT* previousFlight, int seatClass);