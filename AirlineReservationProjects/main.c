#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>

#include "path.h"
#include "reservation.h"
#include "init.h"

#define DAY_OF_MONTH 31

CITY_GRAPH* cityGraph;
LINKED_LIST* airlineList[DAY_OF_MONTH];
RESERVATION_RECORD* record;

void init()
{
	cityGraph = initCityGraph();

	record = initReservationRecord();

	for (int i = 0; i < DAY_OF_MONTH; i++)
	{
		airlineList[i] = initAirlineList(cityGraph, i + 1);
	}
}

int main()
{
	init();

	ITERATOR* iterator = generateIterator(cityGraph->cityList);

	for (CITY* city = getNextData(iterator); city != NULL; city = getNextData(iterator))
	{
		ITERATOR* adjacencyIterator = generateIterator(city->adjacencyList);

		printf("���ø� : %c\n", city->name);
		printf("�� �� �ִ� ����\n");

		for (ADJACENCY_CITY* adjacencyCity = getNextData(adjacencyIterator); adjacencyCity != NULL; adjacencyCity = getNextData(adjacencyIterator))
		{
			printf("%c ����, �Ÿ� : %dkm\n", adjacencyCity->city->name, adjacencyCity->distance);
		}
	}

	printf("\n\n\n");

	for (int i = 0; i < DAY_OF_MONTH; i++)
	{
		ITERATOR* iterator = generateIterator(airlineList[i]);

		for (AIRLINE* airline = getNextData(iterator); airline != NULL; airline = getNextData(iterator))
		{
			char* departureTime = timeToStr(airline->departureTime);
			char* arrivalTime = timeToStr(airline->arrivalTime);

			printf("����� : %c, ������ : %c, ", airline->source->name, airline->destination->name);
			printf("��� �ð� : %s, ", departureTime);
			printf("���� �ð� : %s\n", arrivalTime);

			free(departureTime);
			free(arrivalTime);
		}
	}



	

	return 0;
}