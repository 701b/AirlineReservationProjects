/*
city.h

���ο� ���� ���� CITY_GRPTH* cityGraph�� ����Ǿ� �ִ�.
�̰��� ������ ��� CITY�� ��´�.
*/

#pragma once

#include <math.h>

#include "linkedList.h"
#include "iterator.h"

/*
����ü CITY�� ���ø� ���ϸ�, ���� �̸�, x��ġ, y��ġ, ����� ���� ����Ʈ�� ���´�.
cityGraph�� �߰��� �ʿ��� ���, addToCityGraph�Լ��� ���� �߰��Ѵ�. */
typedef struct city
{
	char name;
	int x;
	int y;
	LINKED_LIST* adjacencyList;
} CITY;

/*
connectionList�� ���� ����ü�̴�. */
typedef struct adjacencyCity
{
	CITY* city;
	int distance;
} ADJACENCY_CITY;

/*
����ü CITY_GRAPH�� ���Ḯ��Ʈ�� ���� ��� CITY�� ���´�.
�ݵ�� generateCityGraph�Լ��� ���� �����Ѵ�. */
typedef struct cityGraph
{
	LINKED_LIST* cityList;
} CITY_GRAPH;

/*
����ü CITY_GRAPH�� �����ϰ� ���� ������ �ʱ�ȭ�Ͽ� ��ȯ�Ѵ�. */
CITY_GRAPH* generateCityGraph();

/*
�� CITY�� connectionList�� ���θ� �߰��ϰ� 1�� ��ȯ�Ѵ�.
�̹� ����Ǿ� �ִٸ� �ƹ��� ���۵� ���� �ʰ� 0�� ��ȯ�Ѵ�.
�� CITY�� ���Ƶ� �ƹ��� ���۵� ���� �ʰ� 0�� ��ȯ�Ѵ�. */
int setConnection(CITY* city1, CITY* city2);

/*
name, x, y ������ ��� CITY ����ü�� ����� cityGraph�� �߰��Ѵ�. */
CITY* addToCityGraph(CITY_GRAPH* cityGraph, char name, int x, int y);

/*
cityGraph�κ��� index�� ����Ű�� CITY*�� ��ȯ�Ѵ�. */
CITY* getFromCityGraph(CITY_GRAPH* cityGraph, int index);

/*
�� CITY ������ �Ÿ��� ���Ͽ� ��ȯ�Ѵ�. */
int calculateDistanceBetween(CITY* city1, CITY* city2);