#include "city.h"

CITY* generateCity(char* name, int x, int y)
{
	CITY* city = malloc(sizeof(CITY));

	city->connectionList = generateLinkedList();
	city->name = name;
	city->x = x;
	city->y = y;

	return city;
}

CITY_GRAPH* generateCityGraph()
{
	CITY_GRAPH* cityGraph = malloc(sizeof(CITY_GRAPH));

	cityGraph->cityList = generateLinkedList();

	return cityGraph;
}

int setConnection(CITY* city1, CITY* city2)
{
	if (findFromList(city1->connectionList, city2) >= 0)
	{
		return 0;
	}

	addToList(city1->connectionList, city2);
	addToList(city2->connectionList, city1);

	return 1;
}

CITY* addToCityGraph(CITY_GRAPH* cityGraph, char* name, int x, int y)
{
	CITY* city = generateCity(name, x, y);

	addToList(cityGraph, city);

	return city;
}

int calculateDistanceBetween(CITY* city1, CITY* city2)
{
	int xDiff = abs(city1->x - city2->x);
	int yDiff = abs(city1->y - city2->y);

	return sqrt(pow(xDiff, 2) + pow(yDiff, 2));
}