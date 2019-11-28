#define _CRT_SECURE_NO_WARNINGS

#include "init.h"

#define INITIAL_NUMBER_OF_RESERVATION 500
#define INITIAL_NUMBER_OF_CITY 26
#define INITIAL_NUMBER_OF_DIRECT_PATH 100

#define RANDOM_LENGTH_OF_STR rand() % 10 + 4
#define RANDOM_INTEGER(max) rand() % max
#define RANDOM_CHARACTER (rand() % ('z' - 'a')) + 'a'

#define MAX_VALUE_OF_POSITION 6000


char* generateRandomStr(int length)
{
	char* str = calloc(length + 1, sizeof(char));
	char* str_temp = str;

	for (int i = 0; i < length; i++)
	{
		*str_temp++ = RANDOM_CHARACTER;
	}

	return str;
}

CITY_GRAPH* initCityGraph()
{
	CITY_GRAPH* cityGraph = generateCityGraph();
	char* name;
	int x, y;

	srand(time(NULL));

	// 정해진 개수의 CITY 생성
	for (int i = 0; i < INITIAL_NUMBER_OF_CITY; i++)
	{
		ITERATOR* iterator = generateIterator(cityGraph->cityList);

		name = 'a' + i;
		x = (rand() % MAX_VALUE_OF_POSITION) - (MAX_VALUE_OF_POSITION / 2);
		y = (rand() % MAX_VALUE_OF_POSITION) - (MAX_VALUE_OF_POSITION / 2);

		for (CITY* city = getNextData(iterator); city != NULL; city = getNextData(iterator))
		{
			// 위치가 같은 것이 있는 경우 다시 생성
			if (city->x == x && city->y == y)
			{
				i--;
				continue;
			}
		}

		addToCityGraph(cityGraph, name, x, y);
	}

	for (int i = 0; i < INITIAL_NUMBER_OF_DIRECT_PATH; i++)
	{
		CITY* city1 = getFromCityGraph(cityGraph, RANDOM_INTEGER(INITIAL_NUMBER_OF_CITY));
		CITY* city2 = getFromCityGraph(cityGraph, RANDOM_INTEGER(INITIAL_NUMBER_OF_CITY));

		// 연결이 되지 않는 경우 다시 
		if (!setConnection(city1, city2))
		{
			i--;
			continue;
		}
	}

	return cityGraph;
}

LINKED_LIST* initAirlineList(CITY_GRAPH* cityGraph, int day)
{
	LINKED_LIST* airlineList = generateLinkedList();

	srand(time(NULL));

	for (int i = 0; i < INITIAL_NUMBER_OF_CITY; i++)
	{
		CITY* source = getFromCityGraph(cityGraph, i);
		ITERATOR* iterator = generateIterator(source->adjacencyList);

		for (ADJACENCY_CITY* adjacencyCity = getNextData(iterator); adjacencyCity != NULL; adjacencyCity = getNextData(iterator))
		{
			CITY* destination = adjacencyCity->city;
			TIME* time1;
			TIME* time2;
			TIME* time3;

			do
			{
				time1 = generateTime(1, day, RANDOM_INTEGER(24), RANDOM_INTEGER(60));
				time2 = generateTime(1, day, RANDOM_INTEGER(24), RANDOM_INTEGER(60));
				time3 = generateTime(1, day, RANDOM_INTEGER(24), RANDOM_INTEGER(60));
			} while (time1->hour != time2->hour
					&& time1->hour != time3->hour
					&& time2->hour != time3->hour);

			AIRLINE* airline1 = generateAirline(source, destination, time1);
			AIRLINE* airline2 = generateAirline(source, destination, time2);
			AIRLINE* airline3 = generateAirline(source, destination, time3);

			addToList(airlineList, airline1);
			addToList(airlineList, airline2);
			addToList(airlineList, airline3);
		}
	}

	return airlineList;
}

RESERVATION_RECORD* initReservationRecord()
{
	RESERVATION_RECORD* record = generateReservationRecord();

	srand(time(NULL));

	for (int i = 0; i < INITIAL_NUMBER_OF_RESERVATION; i++)
	{
		char* name = generateRandomStr(RANDOM_LENGTH_OF_STR);
		PATH* path = generatePath();

		//path 랜덤 설정해야함.

		addToRecord(record, name, path);
	}

	return record;
}