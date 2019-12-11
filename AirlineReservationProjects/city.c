#include "city.h"

CITY* generateCity(char name, int x, int y)
{
	CITY* city = malloc(sizeof(CITY));

	city->adjacencyList = generateLinkedList();
	city->name = name;
	city->x = x;
	city->y = y;

	return city;
}

ADJACENCY_CITY* generateAdjacencyCity(CITY* origin, CITY* target)
{
	ADJACENCY_CITY* adjacencyCity = malloc(sizeof(ADJACENCY_CITY));
	int distance = calculateDistanceBetween(origin, target);

	adjacencyCity->city = target;
	adjacencyCity->distance = distance;

	return adjacencyCity;
	
}

CITY_GRAPH* generateCityGraph()
{
	CITY_GRAPH* cityGraph = malloc(sizeof(CITY_GRAPH));

	cityGraph->cityList = generateLinkedList();

	return cityGraph;
}

int setConnection(CITY* city1, CITY* city2)
{
	if (city1 == city2)
	{
		return 0;
	}

	ITERATOR* iterator = generateIterator(city1->adjacencyList);

	for (ADJACENCY_CITY* adjacencyCity = getNextData(iterator); adjacencyCity != NULL; adjacencyCity = getNextData(iterator))
	{
		if (adjacencyCity->city == city2)
		{
			return 0;
		}
	}

	ADJACENCY_CITY* adjacencyCity1 = generateAdjacencyCity(city1, city2);
	//ADJACENCY_CITY* adjacencyCity2 = generateAdjacencyCity(city2, city1); 양방향일때 주석 제거

	addToList(city1->adjacencyList, adjacencyCity1);
	//addToList(city2->adjacencyList, adjacencyCity2); 양방향일때 주석 제거

	return 1;
}

CITY* addToCityGraph(CITY_GRAPH* cityGraph, char name, int x, int y)
{
	CITY* city = generateCity(name, x, y);

	addToList(cityGraph->cityList, city);

	return city;
}

CITY* getFromCityGraph(CITY_GRAPH* cityGraph, int index)
{
	return getFromList(cityGraph->cityList, index);
}

int calculateDistanceBetween(CITY* city1, CITY* city2)
{
	int xDiff = abs(city1->x - city2->x);
	int yDiff = abs(city1->y - city2->y);

	return sqrt(pow(xDiff, 2) + pow(yDiff, 2));
}

CITY* findCityByChar(CITY_GRAPH* cityGraph, char c)
{
	ITERATOR* iterator = generateIterator(cityGraph->cityList);

	for (CITY* city = getNextData(iterator); city != NULL; city = getNextData(iterator))
	{
		if (city->name == c)
		{
			freeIterator(&iterator);
			return city;
		}
	}

	freeIterator(&iterator);
	return NULL;
}
