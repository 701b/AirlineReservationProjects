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
�� CITY�� connectionList�� ���θ� �߰��ϰ� 1�� ��ȯ�Ѵ�.
�̹� ����Ǿ� �ִٸ� �ƹ��� ���۵� ���� �ʰ� 0�� ��ȯ�Ѵ�.
*/
int setConnection(CITY* city1, CITY* city2);

/*
name, x, y ������ ��� CITY ����ü�� ����� cityGraph�� �߰��Ѵ�.
*/
CITY* addToCityGraph(CITY_GRAPH* cityGraph, char* name, int x, int y);

/*
�� City ������ �Ÿ��� ���Ͽ� ��ȯ�Ѵ�.
*/
int calculateDistanceBetween(CITY* city1, CITY* city2);