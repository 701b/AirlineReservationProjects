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
			struct tm* time1 = calloc(1, sizeof(struct tm));
			struct tm* time2 = calloc(1, sizeof(struct tm));
			struct tm* time3 = calloc(1, sizeof(struct tm));

			do
			{
				time1->tm_year = 2019;
				time2->tm_year = 2019;
				time3->tm_year = 2019;

				time1->tm_mon = 1;
				time2->tm_mon = 1;
				time3->tm_mon = 1;

				time1->tm_sec = 0;
				time2->tm_sec = 0;
				time3->tm_sec = 0;

				time1->tm_mday = day;
				time2->tm_mday = day;
				time3->tm_mday = day;

				time1->tm_hour = RANDOM_INTEGER(24);
				time2->tm_hour = RANDOM_INTEGER(24);
				time3->tm_hour = RANDOM_INTEGER(24);

				time1->tm_min = RANDOM_INTEGER(60);
				time2->tm_min = RANDOM_INTEGER(60);
				time3->tm_min = RANDOM_INTEGER(60);
			} while (time1->tm_hour != time2->tm_hour
					&& time1->tm_hour != time3->tm_hour
					&& time2->tm_hour != time3->tm_hour);

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