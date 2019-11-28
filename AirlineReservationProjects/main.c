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
			printf("����� : %c, ������ : %c, ", airline->source->name, airline->destination->name);
			printf("��� �ð� : %d�� %d�� %d:%d, ", airline->departureTime->tm_mon, airline->departureTime->tm_mday, airline->departureTime->tm_hour, airline->departureTime->tm_min);
			printf("���� �ð� : %d�� %d�� %d:%d\n", airline->arrivalTime->tm_mon, airline->arrivalTime->tm_mday, airline->arrivalTime->tm_hour, airline->arrivalTime->tm_min);
		}
	}



	

	return 0;
}