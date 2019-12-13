#define _CRT_SECURE_NO_WARNINGS

#include "init.h"

#define INITIAL_NUMBER_OF_RESERVATION 500
#define INITIAL_NUMBER_OF_CITY 26
#define INITIAL_NUMBER_OF_DIRECT_PATH 100

#define RANDOM_LENGTH_OF_STR rand() % 6 + 4
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

	// ������ ������ CITY ����
	for (int i = 0; i < INITIAL_NUMBER_OF_CITY; i++)
	{
		ITERATOR* iterator = generateIterator(cityGraph->cityList);

		name = 'a' + i;
		x = (rand() % MAX_VALUE_OF_POSITION) - (MAX_VALUE_OF_POSITION / 2);
		y = (rand() % MAX_VALUE_OF_POSITION) - (MAX_VALUE_OF_POSITION / 2);

		for (CITY* city = getNextData(iterator); city != NULL; city = getNextData(iterator))
		{
			// ��ġ�� ���� ���� �ִ� ��� �ٽ� ����
			if (city->x == x && city->y == y)
			{
				i--;
				freeIterator(iterator);
				continue;
			}
		}

		addToCityGraph(cityGraph, name, x, y);
		freeIterator(&iterator);
	}

	for (int i = 0; i < INITIAL_NUMBER_OF_DIRECT_PATH; i++)
	{
		CITY* city1 = getFromCityGraph(cityGraph, RANDOM_INTEGER(INITIAL_NUMBER_OF_CITY));
		CITY* city2 = getFromCityGraph(cityGraph, RANDOM_INTEGER(INITIAL_NUMBER_OF_CITY));

		// ������ ���� �ʴ� ��� �ٽ� 
		if (!setConnection(city1, city2))
		{
			i--;
			continue;
		}
	}

	return cityGraph;
}

LINKED_LIST* initflightList(CITY_GRAPH* cityGraph, int day)
{
	LINKED_LIST* flightList = generateLinkedList();

	srand(time(NULL));

	for (int i = 0; i < INITIAL_NUMBER_OF_CITY; i++)
	{
		CITY* source = getFromCityGraph(cityGraph, i);
		ITERATOR* iterator = generateIterator(source->adjacencyList);

		for (ADJACENCY_CITY* adjacencyCity = getNextData(iterator); adjacencyCity != NULL; adjacencyCity = getNextData(iterator))
		{
			CITY* destination = adjacencyCity->city;
			TIME* times[6] = { NULL, NULL, NULL, NULL, NULL, NULL };

			for (int j = 0; j < RANDOM_INTEGER(4) + 2; j++)
			{
				TIME* time = generateTime(1, day, RANDOM_INTEGER(24), RANDOM_INTEGER(60));
				int regenerate = 0;

				for (int k = 0; k < j; k++)
				{
					if (calculateTimeDifference(time, times[k]) <= 90)
					{
						regenerate = 1;
						break;
					}
				}

				if (regenerate)
				{
					j--;
					free(time);
					continue;
				}
				
				times[j] = time;
				AIRPLANE* airplane = generateAirplane(RANDOM_INTEGER(6));
				addToFlightList(flightList, source, destination, time, airplane);
			}
		}

		freeIterator(&iterator);
	}

	return flightList;
}

RESERVATION_RECORD* initReservationRecord(LINKED_LIST* flightList[], CITY_GRAPH* cityGraph)
{
	RESERVATION_RECORD* record = generateReservationRecord();
	RESERVATION* reservations[500];

	srand(time(NULL));

	for (int i = 0; i < INITIAL_NUMBER_OF_RESERVATION; i++)
	{
		char* firstName;
		char* lastName;
		int sex;
		TIME* departureTime;
		CITY* source = getFromCityGraph(cityGraph, RANDOM_INTEGER('z' - 'a'));
		CITY* destination = getFromCityGraph(cityGraph, RANDOM_INTEGER('z' - 'a'));
		int seatClass;
		PATH* path;

		if (source == destination)
		{
			i--;
			continue;
		}

		departureTime = generateTime(1, RANDOM_INTEGER(30) + 1, 0, 0);
		seatClass = RANDOM_INTEGER(3);
		path = findPathForShortestFlightTime(flightList, departureTime, source, destination, seatClass);

		if (path == NULL)
		{
			i--;
			freePath(&path);
			continue;
		}

		firstName = generateRandomStr(RANDOM_LENGTH_OF_STR);
		lastName = generateRandomStr(RANDOM_LENGTH_OF_STR);
		sex = RANDOM_INTEGER(2) + 1;

		{
			PATH* temp = path;
			ITERATOR* iterator;

			path = generateDeepClonePath(temp);
			freePath(&temp);

			iterator = generateIterator(path->flightList);

			for (FLIGHT* flight = getNextData(iterator); flight != NULL; flight = getNextData(iterator))
			{
				int maxRow = getRowOfAirplaneSeat(flight->airplane, seatClass);
				int maxCol = getColumnOfAirplaneSeat(flight->airplane, seatClass);
				int row;
				int col;
				
				do
				{
					row = RANDOM_INTEGER(maxRow);
					col = RANDOM_INTEGER(maxCol);
				} while (getSeatAvailable(flight->airplane, seatClass, row, col) == NO_SEAT);

				setSeat(flight, seatClass, row, col, NO_SEAT);
			}
		}

		reservations[i] = addToRecord(record, firstName, lastName, sex, path);

		gotoxy(25, 3);
		printf("%d/500", i + 1);
	}

	return record;
}