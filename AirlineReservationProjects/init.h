#pragma once

#include <string.h>

#include "reservation.h"
#include "flight.h"
#include "iterator.h"

/*
CITY_GRAPH를 만들어 초기화하고,
랜덤으로 생성된 24개의 도시와 도시 간에 연결된 경로를 무작위로 300개 추가하여 반환한다. */
CITY_GRAPH* initCityGraph();

/*
LINKED_LIST를 만들어 초기화하고,
모든 연결 경로에 */
LINKED_LIST* initflightList(CITY_GRAPH* cityGraph, int day);

/*
RESERVATION_RECORD를 만들어 초기화하고,
랜덤으로 생성된 500개의 RESERVATION을 추가하여 반환한다.*/
RESERVATION_RECORD* initReservationRecord(LINKED_LIST* flightList[], CITY_GRAPH* cityGraph);