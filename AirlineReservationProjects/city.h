/*
city.h

내부에 전역 변수 CITY_GRPTH* cityGraph가 선언되어 있다.
이것은 생성된 모든 CITY를 담는다.
*/

#pragma once

#include <math.h>

#include "linkedList.h"
#include "iterator.h"

/*
구조체 CITY는 도시를 뜻하며, 도시 이름, x위치, y위치, 연결된 도시 리스트를 갖는다.
cityGraph에 추가가 필요한 경우, addToCityGraph함수를 통해 추가한다. */
typedef struct city
{
	char name;
	int x;
	int y;
	LINKED_LIST* adjacencyList;
} CITY;

/*
connectionList에 들어가는 구조체이다. */
typedef struct adjacencyCity
{
	CITY* city;
	int distance;
} ADJACENCY_CITY;

/*
구조체 CITY_GRAPH는 연결리스트를 통해 모든 CITY를 갖는다.
반드시 generateCityGraph함수를 통해 생성한다. */
typedef struct cityGraph
{
	LINKED_LIST* cityList;
} CITY_GRAPH;

/*
구조체 CITY_GRAPH를 생성하고 내부 변수를 초기화하여 반환한다. */
CITY_GRAPH* generateCityGraph();

/*
두 CITY의 connectionList에 서로를 추가하고 1을 반환한다.
이미 연결되어 있다면 아무런 동작도 하지 않고 0을 반환한다.
두 CITY가 같아도 아무런 동작도 하지 않고 0을 반환한다. */
int setConnection(CITY* city1, CITY* city2);

/*
name, x, y 정보가 담긴 CITY 구조체를 만들어 cityGraph에 추가한다. */
CITY* addToCityGraph(CITY_GRAPH* cityGraph, char name, int x, int y);

/*
cityGraph로부터 index가 가르키는 CITY*를 반환한다. */
CITY* getFromCityGraph(CITY_GRAPH* cityGraph, int index);

/*
두 CITY 사이의 거리를 구하여 반환한다. */
int calculateDistanceBetween(CITY* city1, CITY* city2);