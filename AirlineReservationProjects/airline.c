#include "airline.h"

// 500 km/h
#define VELOCITY 500.0

#define MONTH_TO_DAY 31
#define DAY_TO_HOUR 24
#define HOUR_TO_MINUTE 60

AIRLINE* generateAirline(CITY* source, CITY* destination, TIME* departureTime)
{
	AIRLINE* airline = malloc(sizeof(AIRLINE));
	// 단위 : 분
	int elapsedTime = (calculateDistanceBetween(source, destination) / VELOCITY) * HOUR_TO_MINUTE;
	TIME* arrivalTime = generateCloneTime(departureTime);

	addToTimeByMinute(arrivalTime, elapsedTime);

	airline->source = source;
	airline->destination = destination;
	airline->departureTime = departureTime;
	airline->arrivalTime = arrivalTime;

	return airline;
}

void addToAirlineList(LINKED_LIST* airlineList, CITY* source, CITY* destination, TIME* departureTime)
{
	AIRLINE* airline = generateAirline(source, destination, departureTime);

	if (airlineList == NULL)
	{
		airlineList = generateLinkedList();
	}

	addToList(airlineList, airline);
}

int findFromAirlineList(LINKED_LIST* airlineList, CITY* source, CITY* destination, TIME* departureTime)
{
	ITERATOR* iterator = generateIterator(airlineList);
	
	for (AIRLINE* airline = getNextData(iterator); airline != NULL; airline = getNextData(airlineList))
	{
		//비교 부분 수정 필요
		if (airline->source == source
			&& airline->destination == destination
			&& compareTime(airline->departureTime, departureTime) == 0)
		{
			return 1;
		}
	}

	return 0;
}
