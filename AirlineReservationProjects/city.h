#pragma once

#include <math.h>

#include "linkedList.h"

typedef struct city
{
	char* name;
	int x;
	int y;
	LINKED_LIST* connectionList;
} CITY;

typedef struct cityGraph
{
	LINKED_LIST* cityList;
} CITY_GRAPH;

CITY* generateCity(char* name, int x, int y);
CITY_GRAPH* generateCityGraph();

/*
두 CITY의 connectionList에 서로를 추가하고 1을 반환한다.
이미 연결되어 있다면 아무런 동작도 하지 않고 0을 반환한다.
*/
int setConnection(CITY* city1, CITY* city2);

/*
name, x, y 정보가 담긴 CITY 구조체를 만들어 cityGraph에 추가한다.
*/
CITY* addToCityGraph(CITY_GRAPH* cityGraph, char* name, int x, int y);

/*
두 City 사이의 거리를 구하여 반환한다.
*/
int calculateDistanceBetween(CITY* city1, CITY* city2);